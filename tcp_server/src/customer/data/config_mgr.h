/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    config_mgr.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-11-17
@ description:  cfg manager.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_CONFIG_MGR_H_
#define CONNOR_GAME_SRC_CONFIG_MGR_H_

#include <string>

#include "base/basic_manager.h"
#include "base/macros.h"

namespace tinyxml2 {
class XMLDocument;
};

namespace gamer {

class ConfigMgr : public BasicManager<ConfigMgr> {
  public:
	ConfigMgr() = default;

	void GetNewPlayerCfg();

  private:

};

}

#endif // CONNOR_GAME_SRC_CONFIG_MGR_H_