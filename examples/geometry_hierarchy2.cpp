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
#include "three/extras/scene_utils.h"

using namespace three;
using namespace three_examples;

void geometry_hierarchy_2( SdlWindow& window, GLRenderer& renderer ) {

  renderer.sortObjects = false;

  auto camera = PerspectiveCamera::create(
    60, (float)renderer.width() / renderer.height(), 1, 10000
  );
  camera->position().z = 3000;

  auto scene = Scene::create();
  auto material = MeshNormalMaterial::create();
  auto geometry = CubeGeometry::create( 100, 100, 100 );

  auto root = Object3D::create();
  root->position().x = 1000;
  scene->add( root );

  auto amount = 100;
  auto parent = root;

  auto add = [&geometry, &material]( Object3D::Ptr parent,
                                     int amount,
                                     Vector3 offset ) {
    for ( int i = 0; i < amount; i ++ ) {

      auto object = Mesh::create( geometry, material );
      object->position() = offset;

      parent->add( object );
      parent = object;

    }
  };

  add( root, amount, Vector3(-100,    0,    0) );
  add( root, amount, Vector3( 100,    0,    0) );
  add( root, amount, Vector3(   0, -100,    0) );
  add( root, amount, Vector3(   0,  100,    0) );
  add( root, amount, Vector3(   0,    0, -100) );
  add( root, amount, Vector3(   0,    0,  100) );

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
  auto frame = 0;
  const auto maxFrames = 50000;

  window.animate ( [&]( float dt ) -> bool {

    time += dt;
    ++frame;

    camera->position().x += (-3000.f * mouseX - camera->position().x ) * 3 * dt;
    camera->position().y += ( 3000.f * mouseY - camera->position().y ) * 3 * dt;
    camera->lookAt( scene->position() );

    auto rx = Math::sin( time * 0.7f ) * 0.2f,
         ry = Math::sin( time * 0.3f ) * 0.1f,
         rz = Math::sin( time * 0.2f ) * 0.1f;

    root->position().x = Math::sin( time ) * 1000;

    SceneUtils::traverseHierarchy( *root, [rx,ry,rz]( Object3D& object ) {
      object.rotation() = Euler( rx, ry, rz );
    } );

    renderer.render( *scene, *camera );

    return frame < maxFrames;

  } );

}

int main ( int argc, char* argv[] ) {

  RendererParameters parameters;
  parameters.vsync = false;

  return RunExample( geometry_hierarchy_2, parameters );

}
