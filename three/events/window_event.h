#ifndef THREE_EVENTS_WINDOW_EVENT_H
#define THREE_EVENTS_WINDOW_EVENT_H

#include <three/common.h>
#include <three/events/ui_event.h>
#include <three/math/vector2.h>

namespace three {

class WindowEvent : public UiEvent {
public:

  static const EventType WINDOW_SHOWN;
  static const EventType WINDOW_HIDDEN;
  static const EventType WINDOW_EXPOSED;
  static const EventType WINDOW_MOVED;
  static const EventType WINDOW_RESIZED;
  static const EventType WINDOW_SIZE_CHANGED;
  static const EventType WINDOW_MINIMIZED;
  static const EventType WINDOW_MAXIMIZED;
  static const EventType WINDOW_RESTORED;
  static const EventType WINDOW_ENTER;
  static const EventType WINDOW_LEAVE;
  static const EventType WINDOW_FOCUS_GAINED;
  static const EventType WINDOW_FOCUS_LOST;
  static const EventType WINDOW_CLOSE;

  WindowEvent( const EventType type, unsigned int timestamp, unsigned int width = 0, unsigned int height = 0,
                Vector2 position = Vector2() )
    : UiEvent( type, timestamp ),
      width( width ),
      height( height ),
      position( position ) {}

  unsigned int width;
  unsigned int height;

  Vector2 position;

};

} // end namespace three

#endif // THREE_EVENTS_WINDOW_EVENT_H
