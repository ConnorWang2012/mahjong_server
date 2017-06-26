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

#include "framework/cache/cache_proxy.h"

namespace gamer {

DataManager::DataManager() {
	redis_client_ = CacheProxy::instance()->redis_client();
}

void DataManager::SetPlayerPersonalData(const std::string& player_account, 
										const std::string& serialized_data) {
	redis_client_->set(player_account, serialized_data);
	redis_client_->sync_commit();
}

void DataManager::GetPlayerPersonalData(const std::string& player_account, 
										std::string& serialized_data) {
	redis_client_->get(player_account, [&](cpp_redis::reply& reply) {
		if (reply.is_string()) {
			serialized_data = reply.as_string();
		}
	});
	redis_client_->sync_commit();
}

void DataManager::SetCreateRoomData(int room_id, const std::string& serialized_data) {
	auto key = "room.create:" + std::to_string(room_id);
	redis_client_->set(key, serialized_data);
	redis_client_->sync_commit();
}

void DataManager::GetCreateRoomData(int room_id, std::string& serialized_data) {
	auto key = "room.create:" + std::to_string(room_id);
	redis_client_->get(key, [&](cpp_redis::reply& reply) {
		if (reply.is_string()) {
			serialized_data = reply.as_string();
		}
	});
	redis_client_->sync_commit();
}

void DataManager::SetGameStartData(int room_id, int round, const std::string& serialized_data) {
	auto key = "room:" + std::to_string(room_id);
	auto field = "round:" + std::to_string(round);
	redis_client_->hset(key, field, serialized_data);
}

void DataManager::GetGameStartData(int room_id, int round, std::string& serialized_data) {
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

} // namespace gamer