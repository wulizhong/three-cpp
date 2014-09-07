#ifndef THREE_EVENTS_INPUT_EVENT_H
#define THREE_EVENTS_INPUT_EVENT_H

#include <three/common.h>
#include <three/events/ui_event.h>

namespace three {

class InputEvent : public UiEvent {
public:

  InputEvent( const EventType type, unsigned int timestamp )
  : UiEvent( type, timestamp ) {}

};

} // end namespace three

#endif // THREE_EVENTS_INPUT_EVENT_H
