#ifndef THREE_EVENTS_INPUT_EVENT_H
#define THREE_EVENTS_INPUT_EVENT_H

#include <three/common.h>
#include <three/events/core_event.h>

namespace three {

class InputEvent : public CoreEvent {
public:

  InputEvent( const EventType& type )
    : CoreEvent( type ) {}

};

} // end namespace three

#endif // THREE_EVENTS_INPUT_EVENT_H
