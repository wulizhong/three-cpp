#ifndef THREE_EVENTS_KEYBOARD_EVENT_H
#define THREE_EVENTS_KEYBOARD_EVENT_H

#include <three/common.h>
#include <three/events/input_event.h>

namespace three {

class KeyboardEvent : public InputEvent {
public:

  static const char* KEY_PRESS = "keyPress";
  static const char* KEY_UP = "keyUp";
  static const char* KEY_DOWN = "keyDown";

  KeyboardEvent( const EventType& type )
    : InputEvent( type ) {}

  unsigned char keyCode;

  unsigned char which;

  bool shiftKey, ctrlKey, altKey, metaKey;
};

} // end namespace three

#endif // THREE_EVENTS_KEYBOARD_EVENT_H
