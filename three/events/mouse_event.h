#ifndef THREE_EVENTS_MOUSE_EVENT_H
#define THREE_EVENTS_MOUSE_EVENT_H

#include <three/common.h>
#include <three/events/input_event.h>

namespace three {

class MouseEvent : public InputEvent {
public:

  static const char* MOUSE_MOVE = "mouseMove";
  static const char* MOUSE_DOWN = "mouseDown";
  static const char* MOUSE_UP = "mouseUp";

  MouseEvent( const EventType& type, unsigned char which, float clientX, float clientY)
    : InputEvent( type ),
      which( which ),
      clientX( clientX ),
      clientY( clie) {}

  unsigned char which;

  float clientX, clientY;
};

} // end namespace three

#endif // THREE_EVENTS_MOUSE_EVENT_H
