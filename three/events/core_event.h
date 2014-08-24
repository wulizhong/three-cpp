#ifndef THREE_EVENTS_CORE_EVENT_H
#define THREE_EVENTS_CORE_EVENT_H

#include <three/common.h>
#include <three/events/event.h>
#include <string>

namespace three {

class CoreEvent : public Event {
public:

  CoreEvent( const EventType type )
  : type( type ) {}

  virtual ~CoreEvent() {}

  const EventType type;

};

} // end namespace three

#endif // THREE_EVENTS_CORE_EVENT_H
