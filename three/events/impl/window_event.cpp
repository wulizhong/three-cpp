#include <three/common.h>
#include <three/events/window_event.h>

namespace three {

  const EventType WindowEvent::WINDOW_SHOWN         = 1000;
  const EventType WindowEvent::WINDOW_HIDDEN        = 1001;
  const EventType WindowEvent::WINDOW_EXPOSED       = 1002;
  const EventType WindowEvent::WINDOW_MOVED         = 1003;
  const EventType WindowEvent::WINDOW_RESIZED       = 1004;
  const EventType WindowEvent::WINDOW_SIZE_CHANGED  = 1005;
  const EventType WindowEvent::WINDOW_MINIMIZED     = 1006;
  const EventType WindowEvent::WINDOW_MAXIMIZED     = 1007;
  const EventType WindowEvent::WINDOW_RESTORED      = 1008;
  const EventType WindowEvent::WINDOW_ENTER         = 1009;
  const EventType WindowEvent::WINDOW_LEAVE         = 1010;
  const EventType WindowEvent::WINDOW_FOCUS_GAINED  = 1011;
  const EventType WindowEvent::WINDOW_FOCUS_LOST    = 1012;
  const EventType WindowEvent::WINDOW_CLOSE         = 1013;

} // end namespace three
