#ifndef THREE_EVENTS_MOUSE_EVENT_H
#define THREE_EVENTS_MOUSE_EVENT_H

#include <three/common.h>
#include <three/events/input_event.h>

#define MOUSE_BUTTON_NONE       0
#define MOUSE_BUTTON_LEFT       1
#define MOUSE_BUTTON_MIDDLE     2
#define MOUSE_BUTTON_RIGHT      4
#define MOUSE_BUTTON_X1         8
#define MOUSE_BUTTON_X2         16

namespace three {

class MouseEvent : public InputEvent {
public:

  static const char* MOUSE_MOVE;
  static const char* MOUSE_DOWN;
  static const char* MOUSE_UP;

  MouseEvent( const EventType& type, unsigned int timestamp, unsigned char button, unsigned char buttons,
              float screenX, float screenY, float movementX = 0.f, float movementY = 0.f )
    : InputEvent( type, timestamp ),
      button( button ),
      buttons( buttons ),
      screenX( screenX ),
      screenY( screenY ),
      movementX( movementX ),
      movementY( movementY ) {}

  unsigned char button;

  unsigned char buttons;

  float screenX;

  float screenY;

  float movementX;

  float movementY;

};

const char* MouseEvent::MOUSE_MOVE = "mouseMove";
const char* MouseEvent::MOUSE_DOWN = "mouseDown";
const char* MouseEvent::MOUSE_UP = "mouseUp";

} // end namespace three

#endif // THREE_EVENTS_MOUSE_EVENT_H
