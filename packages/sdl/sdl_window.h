#ifndef THREE_PACKAGES_SDL_SDL_WINDOW_H
#define THREE_PACKAGES_SDL_SDL_WINDOW_H

#include "three/gl.h"
#include "three/math/color.h"
#include "three/utils/noncopyable.h"
#include "three/core/event_dispatcher.h"
#include "three/renderers/renderer_parameters.h"

#include <SDL.h>
#include <SDL_events.h>

#include <functional>
#include <map>
#include <vector>

namespace three {
namespace packages {

using namespace three;

typedef SDL_EventType                     SdlEventType;

class SdlWindow : public three::NonCopyable, public EventDispatcher {
public:

  SdlWindow( const three::RendererParameters& );
  virtual ~SdlWindow();

  three::GLInterface createGLInterface();

  virtual void animate( Update update );

  virtual bool valid() const;

private:
  void swapBuffers();
  bool processEvents();
  MouseEvent mapMouseEvent( const SDL_Event& sdlEvent, const EventType type) const;
  WindowEvent mapWindowEvent( const SDL_Event& sdlEvent, const EventType type) const;

  SDL_Window* window;

  SDL_GLContext context;

  bool renderStats;

};


} // end namespace packages
} // end namespace three

#endif // THREE_PACKAGES_SDL_SDL_WINDOW_H
