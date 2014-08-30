#ifndef THREE_EXAMPLES_SDL_H
#define THREE_EXAMPLES_SDL_H

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

namespace three_examples {

using namespace three;

typedef SDL_EventType                     SdlEventType;

class GLWindow : public three::NonCopyable, public EventDispatcher {
public:

  GLWindow( const three::RendererParameters& );
  ~GLWindow();

  three::GLInterface createGLInterface();

  typedef std::function<bool(float)> Update;
  void animate( Update update );

  bool valid() const;

private:
  void swapBuffers();
  bool processEvents();
  MouseEvent mapMouseEvent( const SDL_Event& sdlEvent, const EventType type) const;
  WindowEvent mapWindowEvent( const SDL_Event& sdlEvent, const EventType type) const;

  SDL_Window* window;
  SDL_GLContext context;
  bool renderStats;
};



} // namespace three_examples

#endif // THREE_EXAMPLES_SDL_H
