#ifndef THREE_PACKAGES_SDL_SDL_WINDOW_H
#define THREE_PACKAGES_SDL_SDL_WINDOW_H

#include "three/gl.h"
#include "three/core/interfaces.h"
#include "three/renderers/renderer_parameters.h"
#include "packages/sdl/sdl_event_mapper.h"

#include <SDL.h>
#include <SDL_events.h>

namespace three {
namespace packages {

using namespace three;

typedef SDL_EventType SdlEventType;

class SdlWindow : public IWindow {
public:

  SdlWindow( const three::RendererParameters& );
  virtual ~SdlWindow();

  virtual three::GLInterface createGLInterface();

  virtual void animate( Update update );

  virtual bool valid() const;

  virtual int width() const;
  virtual int height() const;

private:
  void swapBuffers();
  bool processEvents();

  SDL_Window* window;

  SDL_GLContext context;

  std::unique_ptr<SdlEventMapper> eventMapper;

  bool renderStats;

  int size[2];

};


} // end namespace packages
} // end namespace three

#endif // THREE_PACKAGES_SDL_SDL_WINDOW_H
