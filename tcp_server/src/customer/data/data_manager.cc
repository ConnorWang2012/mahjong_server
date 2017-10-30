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

#include "util/google/absl/strings/numbers.h"
#include "framework/cache/cache_proxy.h"

namespace gamer {

DataManager::DataManager() {
	this->Init();
}

void DataManager::CachePlayerPersonalData(const std::string& player_account, 
										  const std::string& serialized_data) {
	redis_client_->set(player_account, serialized_data);
	redis_client_->sync_commit();
}

void DataManager::GetCachedPlayerPersonalData(const std::string& player_account, 
										      std::string& serialized_data) {
	redis_client_->get(player_account, [&](cpp_redis::reply& reply) {
		if (reply.is_string()) {
			serialized_data = reply.as_string();
		}
	});
	redis_client_->sync_commit();
}

void DataManager::CacheCreateRoomData(int room_id, const std::string& serialized_data) {
	auto key = "room.create:" + std::to_string(room_id);
	redis_client_->set(key, serialized_data);
	redis_client_->sync_commit();
}

void DataManager::GetCachedCreateRoomData(int room_id, std::string& serialized_data) {
	auto key = "room.create:" + std::to_string(room_id);
	redis_client_->get(key, [&](cpp_redis::reply& reply) {
		if (reply.is_string()) {
			serialized_data = reply.as_string();
		}
	});
	redis_client_->sync_commit();
}

void DataManager::CacheGameStartData(int room_id, const std::string& serialized_data) {
	auto key = "room:" + std::to_string(room_id);
	auto field = "round0";
	redis_client_->hset(key, field, serialized_data);
}

void DataManager::GetCachedGameStartData(int room_id, std::string& serialized_data) {
	auto key = "room:" + std::to_string(room_id);
	auto field = "round0";
	redis_client_->hget(key, field, [&](cpp_redis::reply& reply) {
		if (reply.is_string()) {
			serialized_data = reply.as_string();
		}
	});
}

void DataManager::CacheRoomData(int room_id, int round, const std::string& serialized_data) {
	auto key = "room:" + std::to_string(room_id);
	auto field = "round:" + std::to_string(round);
	redis_client_->hset(key, field, serialized_data);
}

void DataManager::GetCachedRoomData(int room_id, int round, std::string& serialized_data) {
	auto key = "room:" + std::to_string(room_id);
	auto field = "round:" + std::to_string(round);
	redis_client_->hget(key, field, [&](cpp_redis::reply& reply) {
		if (reply.is_string()) {
			serialized_data = reply.as_string();
		}
	});
}

int DataManager::GeneratePlayerID() {
	++available_player_id_;
	redis_client_->set("player.id:available", std::to_string(available_player_id_));
	redis_client_->sync_commit();
	return available_player_id_;
}

void DataManager::UpdateAvailablePlayerID() {
	redis_client_->get("player.id:available", [&](cpp_redis::reply& reply) {
		if (reply.is_integer()) {
			available_player_id_ = (int)reply.as_integer();
		}
	});
	redis_client_->sync_commit();
}

void DataManager::SetGold(id_t player_id, score_t gold) {
	auto key   = "player:" + std::to_string(player_id);
	auto field = "gold";
	redis_client_->hset(key, field, std::to_string(gold));
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

void DataManager::Init() {
	redis_client_ = CacheProxy::instance()->redis_client();
}

} // namespace gamer