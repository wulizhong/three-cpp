#ifndef THREE_EVENTS_INPUT_EVENT_H
#define THREE_EVENTS_INPUT_EVENT_H

#include <three/common.h>
#include <three/events/ui_event.h>

namespace three {

class InputEvent : public UiEvent {
public:

  InputEvent( const EventType type, unsigned int timestamp, bool altKey = false, bool ctrlKey = false, bool metaKey = false, bool shiftKey = false)
  : UiEvent( type, timestamp ),
      altKey( altKey ),
      ctrlKey( ctrlKey ),
      metaKey( metaKey ),
      shiftKey( shiftKey ) {}

  bool altKey;
  bool ctrlKey;
  bool metaKey;
  bool shiftKey;

};

} // end namespace three

#endif // THREE_EVENTS_INPUT_EVENT_H
