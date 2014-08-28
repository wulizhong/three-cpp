#include "common.h"

#include "three/cameras/perspective_camera.h"
#include "three/core/geometry.h"
#include "three/extras/geometries/plane_geometry.h"
#include "three/extras/geometries/sphere_geometry.h"
#include "examples/controls/first_person_controls.h"
#include "three/renderers/renderer_parameters.h"
#include "three/lights/directional_light.h"
#include "three/materials/mesh_lambert_material.h"
#include "three/objects/mesh.h"
#include "three/renderers/gl_renderer.h"
#include "three/scenes/fog_exp2.h"

#include "three/extras/image_utils.h"

using namespace three;
using namespace three_examples;

void misc_sound( GLWindow& window, GLRenderer& renderer ) {

  auto camera = PerspectiveCamera::create(
    50, ( float )renderer.width() / renderer.height(), 2.f, 2000
  );
  camera->position().set(0, 25, 0);

  const auto& cameraObject = std::dynamic_pointer_cast<Object3D>(camera);

  auto controls = FirstPersonControls::create( cameraObject, window );
  controls->movementSpeed = 70;
  controls->lookSpeed = 0.05;
  controls->noFly = true;
  controls->lookVertical = false;

  auto scene = Scene::create();
  scene->fog = FogExp2::create( 0x000000, .001f );


  auto light = DirectionalLight::create( 0xfffff );
  light->position().set( 0, 0.5, 1).normalize();
  scene->add( light );

  auto sphere = SphereGeometry::create( 20, 32, 16 );

  auto material_sphere1 = MeshLambertMaterial::create(
    Material::Parameters().add( "shading", THREE::FlatShading )
                          .add( "color", 0xffaa00 )
  );

  auto material_sphere2 = MeshLambertMaterial::create(
    Material::Parameters().add( "shading", THREE::FlatShading )
                          .add( "color", 0xff2200 )
  );

  float s = 1;

  auto mesh1 = Mesh::create( sphere, material_sphere1 );
  mesh1->scale().set( s, s, s);
  scene->add( mesh1 );

  // sound1 = new Sound( [ 'sounds/358232_j_s_song.mp3', 'sounds/358232_j_s_song.ogg' ], 275, 1 );
  //       sound1.position.copy( mesh1.position );
  //       sound1.play();

  auto mesh2 = Mesh::create( sphere, material_sphere2 );
  mesh2->position().set( 250, 30, 0);
  mesh2->scale().set( s, s, s);
  scene->add( mesh1 );

  // sound2 = new Sound( [ 'sounds/376737_Skullbeatz___Bad_Cat_Maste.mp3', 'sounds/376737_Skullbeatz___Bad_Cat_Maste.ogg' ], 275, 1 );
  //       sound2.position.copy( mesh2.position );
  //       sound2.play();

  // ground
  auto material = MeshLambertMaterial::create(
    Material::Parameters()
            .add("color", 0x7f7566)
            .add("wireframe", true)
            .add("wireframeLinewidth", 1)
  );

  auto mesh = Mesh::create( PlaneGeometry::create(1000,1000,100,100), material);
  mesh->position().x = 0.1;
  mesh->rotation().x = - Math::PI() / 2;
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

  auto time = 0.f;

  window.animate( [&]( float dt ) -> bool {

    time += dt * .05f;

    controls->update( dt );

    // material_sphere1->color.setHSL( 0.0, 0.3 + 0.7 * (1 + Math::cos(time) ) / 2, 0.5 );
    // material_sphere2->color.setHSL( 0.0, 0.3 + 0.7 * (1 + Math::sin(time) ) / 2, 0.5 );

    renderer.render( *scene, *camera );

    return true;

  } );

}

int main( int argc, char* argv[] ) {

  RendererParameters parameters;
  parameters.clearAlpha = 1;

  return RunExample( misc_sound, parameters );

}
