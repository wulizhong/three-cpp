#ifndef THREE_EVENTS_INPUT_EVENT_H
#define THREE_EVENTS_INPUT_EVENT_H

#include <three/common.h>
#include <three/events/event.h>

namespace three {

class InputEvent : public Event {
public:

  InputEvent( const EventType& type )
    : Event( type ) {}

};

} // end namespace three

#endif // THREE_EVENTS_INPUT_EVENT_H
