#ifndef THREE_EVENT_LISTENER_H
#define THREE_EVENT_LISTENER_H

#include <three/common.h>

#include <three/events/event.h>
#include <three/utils/noncopyable.h>
#include <three/utils/memory.h>
#include <functional>

namespace three {

class EventListener : NonCopyable {
public:

  typedef std::function<void(const Event&)> EventListenerFunc;

  virtual ~EventListener() {}

  static std::shared_ptr<EventListener> create( const EventListenerFunc& funcIn ) {
    return three::make_shared<EventListener>( std::move(funcIn) );
  }

  void operator()( const Event& event ) const { func(event); }

protected:

  EventListener( const EventListenerFunc& funcIn )
  : func( std::move(funcIn) ) {}

private:

  EventListenerFunc func;

};

} // end namespace three

#endif // THREE_EVENT_LISTENER_H
