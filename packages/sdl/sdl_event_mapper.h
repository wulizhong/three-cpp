#ifndef THREE_PACKAGES_SDL_SDL_EVENT_MAPPER_H
#define THREE_PACKAGES_SDL_SDL_EVENT_MAPPER_H

#include "three/utils/noncopyable.h"

namespace three {

namespace package {

using namespace three;

class SdlEventMapper : three::NonCopyable {
public:

  SdlEventMapper();

  MouseEvent mapMouseEvent( const SDL_Event& sdlEvent, const EventType type) const;
  WindowEvent mapWindowEvent( const SDL_Event& sdlEvent, const EventType type) const;

};


} // end namespace packages
} // end namespace three

#endif // THREE_PACKAGES_SDL_SDL_WINDOW_H
