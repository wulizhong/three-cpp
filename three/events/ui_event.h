#ifndef THREE_EVENTS_UI_EVENT_H
#define THREE_EVENTS_UI_EVENT_H

#include <three/common.h>
#include <three/events/core_event.h>

namespace three {

class UiEvent : public CoreEvent {
public:

  UiEvent( const EventType type, unsigned int timestamp )
    : CoreEvent( type ),
      timestamp( timestamp ) {}

  unsigned int timestamp;

};

} // end namespace three

#endif // THREE_EVENTS_UI_EVENT_H
