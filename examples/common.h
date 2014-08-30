#ifndef THREE_EXAMPLES_COMMON_H
#define THREE_EXAMPLES_COMMON_H

#include "three/config.h"
#include "three/gl.h"

#include "three/renderers/gl_renderer.h"
#include "three/renderers/renderer_parameters.h"

#include "three/utils/conversion.h"
#include "three/utils/template.h"

#include "packages/sdl/sdl_window.h"
#include "examples/extras/stats.h"

#include "three/events/events.h"

namespace three_examples {

using namespace three::packages;

template <typename Example>
int RunExample( Example example,
                three::RendererParameters parameters = three::RendererParameters() ) {
  SdlWindow window( parameters );
  if ( !window.valid() )
    return EXIT_FAILURE;

  three::GLInterface interface = window.createGLInterface();
  if ( !interface.validate() )
    return EXIT_FAILURE;

  auto renderer = three::GLRenderer::create( parameters, interface );
  if ( !renderer )
    return EXIT_FAILURE;

  example( window, *renderer );
  return EXIT_SUCCESS;
}

} // namespace three_examples

#endif // THREE_EXAMPLES_COMMON_H
