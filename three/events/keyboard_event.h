#ifndef THREE_EVENTS_KEYBOARD_EVENT_H
#define THREE_EVENTS_KEYBOARD_EVENT_H

#include <three/common.h>
#include <three/core/keycodes.h>
#include <three/events/input_event.h>

namespace three {

class KeyboardEvent : public InputEvent {
public:

  static const EventType KEY_PRESS;
  static const EventType KEY_UP;
  static const EventType KEY_DOWN;

  KeyboardEvent( const EventType type, unsigned int timestamp, unsigned int key, bool repeat = false )
    : InputEvent( type, timestamp ),
      key( key ),
      repeat( repeat ) {}

  unsigned int key;

  bool repeat;

};

} // end namespace three

#endif // THREE_EVENTS_KEYBOARD_EVENT_H
