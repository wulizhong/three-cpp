#include "common.h"

#include "three/cameras/perspective_camera.h"
#include "three/core/geometry.h"
#include "three/materials/particle_system_material.h"
#include "three/objects/particle_system.h"
#include "three/renderers/renderer_parameters.h"
#include "three/renderers/gl_renderer.h"

using namespace three;
using namespace three_examples;

void trails( SdlWindow& window, GLRenderer& renderer ) {

  renderer.sortObjects = false;
  renderer.autoClearColor = false;

  // Camera
  auto camera = PerspectiveCamera::create(
    60,
    (float)renderer.width() / renderer.height(),
    1, 10000
  );
  camera->position().set( 100000, 0, 3200 );

  // Scene
  auto scene = Scene::create();

  // Geometries
  std::array<Color, 4> colors = { Color(0x000000), Color(0xff0080), Color(0x8000ff), Color(0xffffff) };
  auto geometry = Geometry::create();

  for ( int i = 0; i < 2000; i ++ ) {
    Vertex vertex;
    vertex.x = Math::random(-2000.f, 2000.f);
    vertex.y = Math::random(-2000.f, 2000.f);
    vertex.z = Math::random(-2000.f, 2000.f);
    geometry->vertices.push_back( vertex );
    geometry->colors.push_back( colors[ (int)Math::floor( Math::random() * colors.size() ) ] );
  }

  // Materials
  auto material = ParticleSystemMaterial::create(
    Material::Parameters().add("color", Color(0xcccccc))
                          .add("size", 1.0f)
                          .add("vertexColors", THREE::VertexColors)
                          .add("depthTest", false)
                          .add("opacity", 0.5f)
                          .add("sizeAttenuation", false)
  );

  auto mesh = ParticleSystem::create( geometry, material );
  scene->add( mesh );

  /////////////////////////////////////////////////////////////////////////

  auto mouseX = 0.f, mouseY = 0.f;
  window.addEventListener( MouseEvent::MOUSE_MOVE, [&]( const Event& event ) {

    auto mouseEvent = static_cast<const MouseEvent&>( event );

    mouseX = 2.f * ( mouseEvent.screenX / renderer.width()  - 0.5f );
    mouseY = 2.f * ( mouseEvent.screenY / renderer.height() - 0.5f );

  });

  window.addEventListener( WindowEvent::WINDOW_RESIZED, [&]( const Event& event ) {

    auto windowEvent = static_cast<const WindowEvent&>( event );

    camera->aspect = (float)windowEvent.width / (float)windowEvent.height;
    camera->updateProjectionMatrix();

    renderer.setSize( windowEvent.width, windowEvent.height );

  });

  /////////////////////////////////////////////////////////////////////////

  // Rendering
  window.animate ( [&]( float dt ) -> bool {

    camera->position().x += ( 1000.f * mouseX - camera->position().x ) * 5 * dt;
    camera->position().y += ( 1000.f * mouseY - camera->position().y ) * 5 * dt;
    camera->lookAt( scene->position() );

    renderer.render( *scene, *camera );

    return true;

  } );

}

int main ( int argc, char* argv[] ) {

  RendererParameters parameters;
  parameters.preserveDrawingBuffer = true;

  return RunExample( trails, parameters );

}
