#ifndef THREE_EXAMPLES_SDL_H
#define THREE_EXAMPLES_SDL_H

#include "three/gl.h"
#include "three/math/color.h"
#include "three/utils/noncopyable.h"
#include "three/core/event_dispatcher.h"
#include "three/renderers/renderer_parameters.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

#include <functional>
#include <map>
#include <vector>

namespace three_examples {

using namespace three;

class SdlEvent : public Event {
public:

  SdlEvent(const SDL_Event& eventData)
  : data( std::move(eventData) ) {}

  SDL_Event data;
};

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
  Event mapEvent(const SDL_Event& sdlEvent, const EventType type);

  SDL_Window* window;
  SDL_GLContext context;
  bool renderStats;
};



} // namespace three_examples

#endif // THREE_EXAMPLES_SDL_H
