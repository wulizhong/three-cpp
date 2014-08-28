#include "common.h"

#include "three/cameras/perspective_camera.h"
#include "three/core/geometry.h"
#include "three/lights/directional_light.h"
#include "three/materials/mesh_normal_material.h"
#include "three/objects/mesh.h"
#include "three/renderers/renderer_parameters.h"
#include "three/renderers/gl_renderer.h"
#include "three/scenes/fog.h"

#include "three/extras/geometries/cube_geometry.h"

using namespace three;
using namespace three_examples;

void geometry_hierarchy( GLWindow& window, GLRenderer& renderer ) {

  renderer.sortObjects = false;

  auto camera = PerspectiveCamera::create(
    60, ( float )renderer.width() / renderer.height(), 1, 10000
  );
  camera->position().z = 500;

  auto scene = Scene::create();
  scene->fog = Fog::create( 0xffffff, 1, 10000 );

  auto material = MeshNormalMaterial::create();
  auto geometry = CubeGeometry::create( 100, 100, 100 );

  auto group = Object3D::create();
  for ( int i = 0; i < 1000; i ++ ) {

    auto mesh = Mesh::create( geometry, material );
    mesh->position() = Vector3( Math::random() * 2000 - 1000,
                                Math::random() * 2000 - 1000,
                                Math::random() * 2000 - 1000 );

    mesh->rotation() = Euler( Math::random() * 2 * Math::PI(),
                              Math::random() * 2 * Math::PI(),
                              0 );

    mesh->matrixAutoUpdate = false;
    mesh->updateMatrix();

    group->add( mesh );

  }
  scene->add( group );

  auto light = DirectionalLight::create( 0xFFFFFF );
  light->target = group;
  scene->add( light );

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

  auto time = 0.f;
  int benchmarkFrames = 100000;

  window.animate( [&]( float dt ) -> bool {

    time += dt;

    camera->position().x += ( -3000.f * mouseX - camera->position().x ) * 3 * dt;
    camera->position().y += ( 3000.f * mouseY - camera->position().y ) * 3 * dt;
    camera->lookAt( scene->position() );

    auto rx = Math::sin( time * 0.7f ) * 0.5f,
    ry = Math::sin( time * 0.3f ) * 0.5f,
    rz = Math::sin( time * 0.2f ) * 0.5f;

    group->rotation() = Euler( rx, ry, rz );

    renderer.render( *scene, *camera );

    return --benchmarkFrames > 0;

  } );

}

int main( int argc, char* argv[] ) {

  RendererParameters parameters;
  parameters.clearAlpha = 1.f;
  parameters.clearColor = Color(0xFFFFFF);

  parameters.vsync = false;

  return RunExample( geometry_hierarchy, parameters );

}
