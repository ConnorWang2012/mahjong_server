/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    data_manager.cc
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-20
@ description:  see the header.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#include "data_manager.h"

#include <vector>

#include "framework/util/google/absl/strings/numbers.h"
#include "framework/util/google/absl/strings/str_join.h"
#include "framework/cache/cache_proxy.h"
#include "framework/util/myutil.h"
#include "customer/player/player.h"
#include "customer/player/player_manager.h"
#include "customer/msg/protocol/my_login_msg_protocol.pb.h"

#ifdef _WIN32
#include <direct.h> 
#include <io.h> 
#include <windows.h>
#elif defined(__linux__)
#include <sys/stat.h>
#elif defined(__unix__)

#endif

namespace gamer {

DataManager::DataManager() {
	//this->Init();
}

void DataManager::Init() {
	redis_client_ = CacheProxy::instance()->redis_client();
	this->UpdateAvailablePlayerID();

	this->InitWritablePath();
}

void DataManager::CacheAccountData(const std::string& account, 
	                               id_t player_id, 
	                               const std::string& password) {
	std::string key = account;
	//std::string field1 = "playerid";
	//std::string field2 = "password";
	std::vector<std::pair<std::string, std::string>> vec{ 
		std::make_pair(std::string("playerid"), std::to_string(player_id)),
		std::make_pair(std::string("password"), password) };

	redis_client_->hmset(key, vec);
}

void DataManager::GetCacheAccountData(const std::string& account, 
	                                 id_t* player_id,
	                                 std::string* password) {
	std::string key = account;
	//std::string field1 = "playerid";
	//std::string field2 = "password";
	std::vector<std::string> fields{ std::string("playerid"), std::string("password") };
	redis_client_->hmget(key, fields, [&](cpp_redis::reply& rep) {
		if (rep.is_array()) {
			auto arr = rep.as_array();
			auto rep1 = arr.at(0);
			std::string str_player_id = "";
			if (rep1.is_string()) {
				str_player_id = rep1.as_string();
			}
			if ("" != str_player_id) {
				absl::SimpleAtoi(str_player_id, player_id);
				*password = arr.at(1).as_string();
			}
		}
	});

	redis_client_->sync_commit();
}

void DataManager::CachePlayerPersonalData(id_t player_id, const std::string& serialized_data) {
	auto key = absl::StrJoin(std::make_tuple("id", player_id), ":");
	auto field = "data";
	redis_client_->hset(key, field, serialized_data);
	redis_client_->commit();
}

void DataManager::GetCachedPlayerPersonalData(id_t player_id, std::string* serialized_data) {
	auto key = absl::StrJoin(std::make_tuple("id", player_id), ":");
	auto field = "data";
	redis_client_->hget(key, field, [&](cpp_redis::reply& rep) {
        if (rep.is_string()) {
            *serialized_data = rep.as_string();
        }
	});

	redis_client_->sync_commit();
}

void DataManager::CacheCreateRoomData(id_t room_id, const std::string& serialized_data) {
	auto key = "room.create:" + std::to_string(room_id);
	redis_client_->set(key, serialized_data);
	redis_client_->sync_commit();
}

void DataManager::GetCachedCreateRoomData(id_t room_id, std::string& serialized_data) {
	auto key = "room.create:" + std::to_string(room_id);
	redis_client_->get(key, [&](cpp_redis::reply& reply) {
		if (reply.is_string()) {
			serialized_data = reply.as_string();
		}
	});
	redis_client_->sync_commit();
}

void DataManager::CacheGameStartData(id_t room_id, const std::string& serialized_data) {
	auto key = "room:" + std::to_string(room_id);
	auto field = "round0";
	redis_client_->hset(key, field, serialized_data);
}

void DataManager::GetCachedGameStartData(id_t room_id, std::string& serialized_data) {
	auto key = "room:" + std::to_string(room_id);
	auto field = "round0";
	redis_client_->hget(key, field, [&](cpp_redis::reply& reply) {
		if (reply.is_string()) {
			serialized_data = reply.as_string();
		}
	});
}

void DataManager::CacheRoomData(id_t room_id, int round, const std::string& serialized_data) {
	auto key = "room:" + std::to_string(room_id);
	auto field = "round:" + std::to_string(round);
	redis_client_->hset(key, field, serialized_data);
}

void DataManager::GetCachedRoomData(id_t room_id, int round, std::string& serialized_data) {
	auto key = "room:" + std::to_string(room_id);
	auto field = "round:" + std::to_string(round);
	redis_client_->hget(key, field, [&](cpp_redis::reply& reply) {
		if (reply.is_string()) {
			serialized_data = reply.as_string();
		}
	});
}

id_t DataManager::GeneratePlayerID() {
	++available_player_id_;
	redis_client_->set("player.id:available", std::to_string(available_player_id_));
	redis_client_->commit();
	return available_player_id_;
}

void DataManager::UpdateAvailablePlayerID() {
	redis_client_->get("player.id:available", [&](cpp_redis::reply& rep) {
		if (rep.is_string()) {
			 absl::SimpleAtoi<id_t>(rep.as_string(), &available_player_id_);
		}
	});
	redis_client_->sync_commit();
}

void DataManager::CacheAccountByID(id_t player_id, const std::string& player_account) {
	if (player_id > 0) {
		redis_client_->set(std::to_string(player_id), player_account);
		redis_client_->commit();
	}
}

void DataManager::GetCachedAccountByID(id_t player_id, std::string* player_account) {
	if (player_id > 0) {
		redis_client_->get(std::to_string(player_id), [&](cpp_redis::reply& rep) {
			if (rep.is_string()) {
				*player_account = rep.as_string();
			}
		});
		redis_client_->sync_commit();
	}
}

void DataManager::SetGold(id_t player_id, score_t gold) {
	auto key = absl::StrJoin(std::make_tuple("account", player_id), ":");
	auto field = "account";
	redis_client_->hget(key, field, [&](cpp_redis::reply& rep) {
		if (rep.is_string()) {
			protocol::MyLoginMsgProtocol proto;
			if (proto.ParseFromString(rep.as_string())) {
				proto.mutable_player()->set_score_gold(gold);

				std::string s;
				if (proto.SerializeToString(&s)) {
					this->CachePlayerPersonalData(player_id, s);
				}
			}
		}
	});

	redis_client_->commit();
}

void DataManager::GetGold(id_t player_id, score_t& gold) const {
	auto key   = "player:" + std::to_string(player_id);
	auto field = "gold";
	redis_client_->hget(key, field, [&](cpp_redis::reply& rep) {
		absl::string_view s = rep.as_string();
		if ("" != s) {
			absl::SimpleAtoi<score_t>(s, &gold);
		}
	});
}

void DataManager::SetDiamond(id_t player_id, score_t diamond) {
	auto key = "player:" + std::to_string(player_id);
	auto field = "diamond";
	redis_client_->hset(key, field, std::to_string(diamond));
}

void DataManager::GetDiamond(id_t player_id, score_t& diamond) const {
	auto key = "player:" + std::to_string(player_id);
	auto field = "diamond";
	redis_client_->hget(key, field, [&](cpp_redis::reply& rep) {
		absl::string_view s = rep.as_string();
		if ("" != s) {
			absl::SimpleAtoi<score_t>(s, &diamond);
		}
	});
}

void DataManager::AddGold(id_t player_id, score_t gold) {
	if (gold > 0) {
		score_t gold_old = 0;
		this->GetGold(player_id, gold_old);
		this->SetGold(player_id, gold_old + gold);
	}
}

void DataManager::AddDiamond(id_t player_id, score_t diamond) {
	if (diamond > 0) {
		score_t gold_diamond = 0;
		this->GetDiamond(player_id, gold_diamond);
		this->SetDiamond(player_id, gold_diamond + diamond);
	}
}

void DataManager::SetNickname(id_t player_id, const std::string& nickanme) {
}

void DataManager::InitWritablePath() {
	writable_path_ = gamer::GetPathOfApp();
	if ( !writable_path_.empty() ) {
#if defined(_WIN32)
		cfg_file_path_ = writable_path_ + "cfg";
		if (_access(cfg_file_path_.c_str(), 0) < 0) {
			_mkdir(cfg_file_path_.c_str());
		}
#elif defined(__linux__)
		cfg_file_path_ = writable_path_ + "cfg/";
		/*
		if (access(buf, 0) < 0) {
			mkdir(buf);
	    }
		*/
		struct stat st;
		stat(cfg_file_path_.c_str(), &st);
		if ( !S_ISDIR(st.st_mode) ) {
			mkdir(cfg_file_path_.c_str(), 0744);
		}
#elif defined(__unix__)
		// TODO
#endif
	}
}

} // namespace gamer