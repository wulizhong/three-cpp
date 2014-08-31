#ifndef THREE_PACKAGES_SDL_SDL_EVENT_MAPPER_H
#define THREE_PACKAGES_SDL_SDL_EVENT_MAPPER_H

#include "three/utils/noncopyable.h"

#include <SDL_events.h>

using namespace three;

namespace three {
namespace packages {

class SdlEventMapper : NonCopyable {
public:

  SdlEventMapper() {}

  inline EventType mapEventType( const SDL_Event sdlEvent ) const {

    switch(sdlEvent.type) {

      case SDL_MOUSEMOTION:
        return MouseEvent::MOUSE_MOVE;
      case SDL_MOUSEBUTTONDOWN:
        return MouseEvent::MOUSE_DOWN;
      case SDL_MOUSEBUTTONUP:
        return MouseEvent::MOUSE_UP;
      case SDL_MOUSEWHEEL:
        return MouseEvent::MOUSE_WHEEL;
      case SDL_WINDOWEVENT:
        switch (sdlEvent.window.event) {
          // SIZE_CHANGED?
          case SDL_WINDOWEVENT_RESIZED:
              return WindowEvent::WINDOW_RESIZED;
          case SDL_WINDOWEVENT_ENTER:
              return WindowEvent::WINDOW_ENTER;
          case SDL_WINDOWEVENT_LEAVE:
              return WindowEvent::WINDOW_LEAVE;
          case SDL_WINDOWEVENT_FOCUS_GAINED:
              return WindowEvent::WINDOW_FOCUS_GAINED;
          case SDL_WINDOWEVENT_FOCUS_LOST:
              return WindowEvent::WINDOW_FOCUS_LOST;
          case SDL_WINDOWEVENT_SHOWN:
              return WindowEvent::WINDOW_SHOWN;
          case SDL_WINDOWEVENT_HIDDEN:
              return WindowEvent::WINDOW_HIDDEN;
          case SDL_WINDOWEVENT_EXPOSED:
              return WindowEvent::WINDOW_EXPOSED;
          case SDL_WINDOWEVENT_MOVED:
              return WindowEvent::WINDOW_MOVED;
          case SDL_WINDOWEVENT_MINIMIZED:
              return WindowEvent::WINDOW_MINIMIZED;
          case SDL_WINDOWEVENT_MAXIMIZED:
              return WindowEvent::WINDOW_MAXIMIZED;
          case SDL_WINDOWEVENT_RESTORED:
              return WindowEvent::WINDOW_RESTORED;
          case SDL_WINDOWEVENT_CLOSE:
              return WindowEvent::WINDOW_CLOSE;
          }
        break;
    }

    return Event::UNKNOWN;
  }

  inline MouseEvent mapMouseEvent( const SDL_Event& sdlEvent, const EventType type) const {

    // TODO Map properly
    auto me = MouseEvent(type, sdlEvent.common.timestamp, MouseButton::NONE, sdlEvent.motion.state,
          sdlEvent.motion.x, sdlEvent.motion.y, sdlEvent.motion.xrel, sdlEvent.motion.yrel);
    return me;

    // switch(sdlEvent.type) {

    //   case SDL_MOUSEMOTION: {
    //     return me;
    //   }
    //   case SDL_MOUSEBUTTONDOWN: {
    //     return Event();
    //   }
    //   case SDL_MOUSEBUTTONUP: {
    //     return Event();
    //   }
    //   case SDL_MOUSEWHEEL: {
    //     return Event();
    //   }
    //   default: {
    //     return Event();
    //   }
    // }

    // return Event(); 
  }

  inline WindowEvent mapWindowEvent( const SDL_Event& sdlEvent, const EventType type ) const {

    WindowEvent event = WindowEvent(type, (unsigned int)sdlEvent.common.timestamp);

    switch (sdlEvent.window.event) {
      case SDL_WINDOWEVENT_RESIZED:
        event.width = sdlEvent.window.data1;
        event.height = sdlEvent.window.data2;
          break;
      case SDL_WINDOWEVENT_ENTER:
          break;
      case SDL_WINDOWEVENT_LEAVE:
          break;
      case SDL_WINDOWEVENT_FOCUS_GAINED:
          break;
      case SDL_WINDOWEVENT_FOCUS_LOST:
          break;
      case SDL_WINDOWEVENT_SHOWN:
          break;
      case SDL_WINDOWEVENT_HIDDEN:
          break;
      case SDL_WINDOWEVENT_EXPOSED:
          break;
      case SDL_WINDOWEVENT_MOVED:
          break;
      case SDL_WINDOWEVENT_MINIMIZED:
          break;
      case SDL_WINDOWEVENT_MAXIMIZED:
          break;
      case SDL_WINDOWEVENT_RESTORED:
          break;
      case SDL_WINDOWEVENT_CLOSE:
          break;
      default:
          break;
    }

    return event;
  }

};

} // end namespace packages
} // end namespace three

#endif // THREE_PACKAGES_SDL_SDL_WINDOW_H
