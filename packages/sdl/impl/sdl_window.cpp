
#include "packages/sdl/sdl_window.h"

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

    EventType type;

    switch(sdlEvent.type) {

      case SDL_MOUSEMOTION:
        type = MouseEvent::MOUSE_MOVE;
        break;
      case SDL_MOUSEBUTTONDOWN:
        type = MouseEvent::MOUSE_DOWN;
        break;

      case SDL_MOUSEBUTTONUP:
        type = MouseEvent::MOUSE_UP;
        break;

      case SDL_MOUSEWHEEL:
        type = MouseEvent::MOUSE_WHEEL;
        break;

      case SDL_WINDOWEVENT:

        switch (sdlEvent.window.event) {
        // SIZE_CHANGED?
        case SDL_WINDOWEVENT_RESIZED:
            type = WindowEvent::WINDOW_RESIZED;
            break;
        case SDL_WINDOWEVENT_ENTER:
            type = WindowEvent::WINDOW_ENTER;
            break;
        case SDL_WINDOWEVENT_LEAVE:
            type = WindowEvent::WINDOW_LEAVE;
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            type = WindowEvent::WINDOW_FOCUS_GAINED;
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            type = WindowEvent::WINDOW_FOCUS_LOST;
            break;
        case SDL_WINDOWEVENT_SHOWN:
            type = WindowEvent::WINDOW_SHOWN;
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            type = WindowEvent::WINDOW_HIDDEN;
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            type = WindowEvent::WINDOW_EXPOSED;
            break;
        case SDL_WINDOWEVENT_MOVED:
            type = WindowEvent::WINDOW_MOVED;
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            type = WindowEvent::WINDOW_MINIMIZED;
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            type = WindowEvent::WINDOW_MAXIMIZED;
            break;
        case SDL_WINDOWEVENT_RESTORED:
            type = WindowEvent::WINDOW_RESTORED;
            break;
        case SDL_WINDOWEVENT_CLOSE:
            type = WindowEvent::WINDOW_CLOSE;
            break;
        default:
            continue;
        }

        break;

      default:
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
        auto mouseEvent = mapMouseEvent( sdlEvent, type );
        dispatchEvent(mouseEvent);
        break;
      }
      case SDL_WINDOWEVENT: {
        auto windowEvent = mapWindowEvent( sdlEvent, type );
        dispatchEvent(windowEvent);
        break;
      }
      default:
        continue;
    }

  }

  return true;
}

MouseEvent SdlWindow::mapMouseEvent( const SDL_Event& sdlEvent, const EventType type) const {

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

WindowEvent SdlWindow::mapWindowEvent( const SDL_Event& sdlEvent, const EventType type ) const {

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

} // end namespace packages

} // end namespace three
