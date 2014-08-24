#ifndef THREE_EVENTS_INPUT_EVENT_H
#define THREE_EVENTS_INPUT_EVENT_H

#include <three/common.h>

namespace three {

class InputEvent : public CoreEvent {
public:

  InputEvent( const EventType& type, unsigned int timestamp, bool altKey = false, bool ctrlKey = false, bool metaKey = false, bool shiftKey = false)
    : CoreEvent( type ),
      timestamp( timestamp ),
      altKey( altKey ),
      ctrlKey( ctrlKey ),
      metaKey( metaKey ),
      shiftKey( shiftKey ) {}

  unsigned int timestamp;

  bool altKey;
  bool ctrlKey;
  bool metaKey;
  bool shiftKey;

};

} // end namespace three

#endif // THREE_EVENTS_INPUT_EVENT_H
