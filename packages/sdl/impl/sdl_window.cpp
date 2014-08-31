#include "packages/sdl/sdl_window.h"
#include "packages/sdl/sdl_event_mapper.h"

#include "three/console.h"
#include "three/core/clock.h"
#include "three/renderers/renderer_parameters.h"
#include "three/renderers/gl_renderer.h"
#include "three/events/events.h"

#include "examples/extras/stats.h"

// TODO(jdduke): Include gles where appropriate.
#include <SDL_assert.h>
#include <SDL_timer.h>
#include <sstream>

#define M_CONC(A, B) M_CONC_(A, B)
#define M_CONC_(A, B) A##B

using namespace three;
using namespace three::packages;

namespace three {
namespace packages {
namespace {

struct SDLGLInterface : public GLInterface {
  SDLGLInterface() {
#define GL_FUNC_DECL(PFUNC, FUNC) FUNC = gl ## FUNC;
#if defined(__APPLE__) || defined(THREE_GLES)
#define GL_FUNC_EXT_DECL(PFUNC, FUNC) GL_FUNC_DECL(PFUNC, FUNC)
#else
#define GL_FUNC_EXT_DECL(PFUNC, FUNC) FUNC = (PFUNC) SDL_GL_GetProcAddress("gl" #FUNC);
#endif
#include "three/gl_functions.h"
#undef GL_FUNC_DECL
#undef GL_FUNC_EXT_DECL
  }
};

} // namepace

SdlWindow::SdlWindow( const RendererParameters& parameters )
    : window( nullptr ),
      context( nullptr ),
      renderStats( true ) {

  if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS ) < 0 ) {
    console().error() << "Unable to initialize SDL: " << SDL_GetError();
    return;
  }

  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY );
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );

  if ( parameters.vsync )
    SDL_GL_SetSwapInterval( 1 );

  /*
  if ( parameters.antialias ) {
    SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 );
    SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, 4 );
  }
  */

  unsigned flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
  window = SDL_CreateWindow( "three.cpp",
                             SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED,
                             parameters.width,
                             parameters.height,
                             flags );
  if ( !window ) {
    console().error() << "Error creating window: " << SDL_GetError();
    return;
  }

  context = SDL_GL_CreateContext( window );
  if ( !context ) {
    console().error() << "Error creating GL context: " << SDL_GetError();
    return;
  }

  eventMapper = std::unique_ptr<SdlEventMapper>(new SdlEventMapper());

  console().log() << "SDL initialized";
}

SdlWindow::~SdlWindow() {
  if ( context )
    SDL_GL_DeleteContext( context );
  if ( window )
    SDL_DestroyWindow( window );
}

three::GLInterface SdlWindow::createGLInterface() {
  return SDLGLInterface();
}

void SdlWindow::animate( Update update ) {
  SDL_assert( valid() );

/*
  RendererParameters statsRendererParams;
  statsRendererParams.preserveDrawingBuffer = true;
  auto statsRenderer = GLRenderer::create( statsRendererParams, createGLInterface() );
  Stats stats( *statsRenderer );
*/
  Clock clock;

  auto lastUpdateTime = clock.getElapsedTime();

  while ( true ) {

    const auto currentTime = clock.getElapsedTime();
    const auto deltaTime = currentTime - lastUpdateTime;
    lastUpdateTime = currentTime;

    if ( !processEvents() )
      return;

    if ( !update( deltaTime ) )
      return;

    // stats.update( deltaTime, renderStats );

    swapBuffers();
  }
}

bool SdlWindow::valid() const {
  return window && context;
}

void SdlWindow::swapBuffers() {
  SDL_GL_SwapWindow( window );
}

bool SdlWindow::processEvents() {

  if(listeners.empty()) {
    return true;
  }

  SDL_Event sdlEvent;

  while ( SDL_PollEvent( &sdlEvent ) ) {
    if ( sdlEvent.type == SDL_QUIT )
      return false;

    if ( sdlEvent.type == SDL_KEYDOWN ) {
      switch ( sdlEvent.key.keysym.sym ) {
        case SDLK_q:
        case SDLK_ESCAPE:
          return false;
        default:
          renderStats = !renderStats;
          break;
      };
    }

    EventType type = eventMapper->mapEventType(sdlEvent);
    if( type == Event::UNKNOWN ) {
      console().warn("SDL event not mapped");
      continue;
    }

    if ( listeners.find( type ) == listeners.cend() ) {
      continue;
    }

    switch(sdlEvent.type) {
      case SDL_MOUSEMOTION: {
      case SDL_MOUSEBUTTONDOWN: 
      case SDL_MOUSEBUTTONUP: 
      case SDL_MOUSEWHEEL: 
        auto mouseEvent = eventMapper->mapMouseEvent( sdlEvent, type );
        dispatchEvent(mouseEvent);
        break;
      }
      case SDL_WINDOWEVENT: {
        auto windowEvent = eventMapper->mapWindowEvent( sdlEvent, type );
        dispatchEvent(windowEvent);
        break;
      }
      default:
        continue;
    }

  }

  return true;
}

} // end namespace packages

} // end namespace three
