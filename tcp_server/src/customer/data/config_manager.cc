/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    config_manager.cc
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-11-17
@ description:  see the header.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#include "config_manager.h"

#include "framework/log/mylog.h"
#include "framework/util/tinyxml/tinyxml2.h"
#include "framework/util/myutil.h"
#include "customer/data/data_manager.h"
#include "customer/msg/protocol/room_list_msg_protocol.pb.h"

namespace gamer {
	
ConfigManager::ConfigManager() 
	: room_list_proto_(nullptr) {
}

void ConfigManager::Init() {
	auto cfg_path = DataManager::instance()->room_cfg_file_path();
	tinyxml2::XMLDocument xmldoc;
	auto ret = xmldoc.LoadFile(cfg_path.c_str());
	if (ret != tinyxml2::XML_SUCCESS) {
		gamer::log::printferror("[ConfigManager::Init] read room config failed!");
		return;
	}

	auto root_node = xmldoc.RootElement();
	if (nullptr == root_node) {
		gamer::log::printferror("[ConfigManager::Init] nullptr == root_node!");
		return;
	}

	if (nullptr == room_list_proto_) {
		room_list_proto_ = new (std::nothrow) gamer::protocol::RoomListMsgProtocol();
		room_list_proto_->set_player_id(0);
	}

	auto cur_node = root_node->FirstChildElement();
	while (nullptr != cur_node) {
		int room_id         = 0;
		int room_type       = 0;
		int sub_room_type   = 0;
		int score_type      = 0;
		int cost_score      = 0;
		int min_score       = 0;
		int base_score      = 0;
		int cur_players_num = 0;

		if (tinyxml2::XML_SUCCESS != cur_node->QueryIntAttribute("room_id", &room_id) ||
			tinyxml2::XML_SUCCESS != cur_node->QueryIntAttribute("room_type", &room_type) ||
			tinyxml2::XML_SUCCESS != cur_node->QueryIntAttribute("sub_room_type", &sub_room_type) ||
			tinyxml2::XML_SUCCESS != cur_node->QueryIntAttribute("score_type", &score_type) ||
			tinyxml2::XML_SUCCESS != cur_node->QueryIntAttribute("cost_score", &cost_score) ||
			tinyxml2::XML_SUCCESS != cur_node->QueryIntAttribute("min_score", &min_score) ||
			tinyxml2::XML_SUCCESS != cur_node->QueryIntAttribute("base_score", &base_score) ||
			tinyxml2::XML_SUCCESS != cur_node->QueryIntAttribute("cur_players_num", &cur_players_num)) {
			gamer::log::printferror("[ConfigManager::Init] error happen while reading room config!");
			break;
		}

		auto room_item_proto = room_list_proto_->add_room_items();
		room_item_proto->set_room_id(room_id);
		room_item_proto->set_room_type(room_type);
		room_item_proto->set_sub_room_type(sub_room_type);
		room_item_proto->set_score_type(score_type);
		room_item_proto->set_cost_score(cost_score);
		room_item_proto->set_min_score(min_score);
		room_item_proto->set_base_score(base_score);
		room_item_proto->set_cur_players_num(cur_players_num);

		cur_node = cur_node->NextSiblingElement();
	}
}

} // namespace gamer