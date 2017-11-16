/*******************************************************************************
  @ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
  @ filename:	  event_manager.h
  @ author:		  Connor
  @ version:	  1.0.0
  @ date:		  2015-01-18
  @ description:  1.offer function to manager events : add event listener, 
                    dispatch event, etc.
				  2.not support lua listener.
  @ others:  
  @ history: 
     1.date:
       author:
       modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_EVENT_MANAGER_H_
#define CONNOR_GAME_SRC_EVENT_MANAGER_H_

#include <map>
#include <string>
#include <vector>

#include "framework/base/macros.h"

namespace gamer {

class Command;
class Event;
class EventListener;

class EventManager {
  public:
	EventManager& operator=(const EventManager&) = delete;

	EventManager(const EventManager&) = delete;

	~EventManager();

	static EventManager* instance();

	static void DestoryInstance();

	// add event listener
	void AddEventListener(EventListener* listener);

	// dispatch event
    void Dispatch(const Event& event);

	// dispatch event
    void Dispatch(id_t event_id, void* optional_user_data = nullptr);

    // remove the event listener from the instance of event manager but do not delete it.
	void RemoveEventListener(EventListener* listener);

    // remove the event listener from the instance of event manager and delete it.
    void RemoveEventListenerWithCleanup(EventListener* listener);

    // remove the event listener from the instance of event manager but do not delete it.
	void RemoveEventListener(const std::string& listener_name);

    // remove the event listener from the instance of event manager and delete it.
    void RemoveEventListenerWithCleanup(const std::string& listener_name);

    // remove all event listeners from the instance of event manager but do not delete any.
	void RemoveAllEventListeners();

    // remove all event listeners from the instance of event manager and delete all.
    void RemoveAllEventListenersWithCleanup();

	void SetPriority(EventListener* listener, int priority);

    inline void set_enabled(bool enabled) { is_enabled_ = enabled; }

    inline bool enabled() const { return is_enabled_; }

  private:
    typedef std::map<id_t, std::vector<EventListener*>>	EventListenerMap;

    enum class DirtyFlag {
        DIRTY_FLAG_NONE                     = 0,
        DIRTY_FLAG_LISTENER_PRIORITY_CHANGE = 1,
        DIRTY_FLAG_LISTENER_NUM_CHANGE      = 2,
        DIRTY_FLAG_ALL                      = 10
    };

	EventManager();
    
    bool Init();

    void AddEventListener(EventListener* listener, int priority);

	void AddEventListenerImpl(EventListener* listener, int priority);

    void RemoveEventListenerImpl(EventListener* listener, bool cleanup);

    void RemoveEventListenerImpl(const std::string& listener_name, bool cleanup);

    void RemoveAllEventListenersImpl(bool cleanup);

	void SortEventListeners(std::vector<EventListener*>* listeners);

	void SortEventListeners(id_t event_id);

	void DispatchEvent(std::vector<EventListener*> listeners, const Event& event);

    // use for command manager.
    void DispatchCommand(Command* cmd);

    // use for command manager.
    void DispatchCommand(int cmd_id, void* optional_user_data = nullptr);

    // use for command manager.
    void DispatchCommandImpl(std::vector<EventListener*> listeners, Command* cmd);

	bool SetPriority(std::vector<EventListener*> listener_list, 
                     EventListener* listener, 
                     int priority);

	void UpdateEventListeners();

    inline bool is_dispatching() { return 0 < dispatch_count_; }

	inline void set_dirty_flag(DirtyFlag flag) { dirty_flag_ = flag; }

	inline void set_dirty_flag(DirtyFlag flag, id_t event_id) {
        set_dirty_flag(flag);
        dirty_event_id_ = event_id;
    };

    inline DirtyFlag dirty_flag() const { return dirty_flag_; }

	inline bool is_dirty() const { return DirtyFlag::DIRTY_FLAG_NONE != dirty_flag_; }

	static EventManager* s_event_manager_;

	EventListenerMap event_listener_;

	std::vector<EventListener*> listeners_to_add_;

	// Whether the event manager is dispatching event(0 mean not) 
	int dispatch_count_;

	bool is_enabled_;
	DirtyFlag dirty_flag_;
	int dirty_event_id_;
	std::string dirty_event_name_;

    friend class CommandManager;
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_EVENT_MANAGER_H_