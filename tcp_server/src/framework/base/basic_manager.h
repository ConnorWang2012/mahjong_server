/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    basic_manager.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-10
@ description:  manager base.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_FRAMEWORK_BASIC_MANAGER_H_
#define CONNOR_GAME_SRC_FRAMEWORK_BASIC_MANAGER_H_

#include <string>

#include "base/macros.h"

namespace gamer {

template <typename Drived>
class BasicManager {
  public:
      BasicManager& operator=(const BasicManager&) = delete;

      BasicManager(const BasicManager&) = delete;

      BasicManager() = default;

      void *operator new(std::size_t) = delete;

    static Drived* instance() {
        static Drived s_mgr;
        return &s_mgr;
    }
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_FRAMEWORK_BASIC_MANAGER_H_

