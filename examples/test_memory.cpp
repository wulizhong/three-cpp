#include "common.h"

#include "three/cameras/perspective_camera.h"
#include "three/core/geometry.h"
#include "three/lights/point_light.h"
#include "three/materials/mesh_basic_material.h"
#include "three/materials/mesh_phong_material.h"
#include "three/materials/mesh_lambert_material.h"
#include "three/objects/mesh.h"
#include "three/renderers/renderer_parameters.h"
#include "three/renderers/gl_renderer.h"
#include "three/scenes/fog.h"

#include "three/extras/geometries/sphere_geometry.h"

using namespace three;
using namespace three_examples;

Image createImage( int width = 256, int height = 256 ) {
  const auto canvasSize = width * height * 3;
  std::vector<unsigned char> canvas;
  canvas.reserve( canvasSize );

  std::generate_n( std::back_inserter(canvas), canvasSize, []{
    return static_cast<unsigned char>(Math::randomT<unsigned int>(0, 255));
  } );

  return Image( std::move(canvas), width, height );
}

void test_memory( GLWindow& window, GLRenderer& renderer ) {


  //////////////////////////////////////////////////////////////////////////

  auto camera = PerspectiveCamera::create(
    60, (float)renderer.width() / renderer.height(), 1, 10000
  );
  camera->position().z = 200;

  auto scene = Scene::create();

  // Lights
  auto pointLight = PointLight::create( 0xFFFFFF );
  pointLight->position() = Vector3( 10, 50, 130 );
  scene->add( pointLight );

/////////////////////////////////////////////////////////////////////////

  auto mouseX = 0.f, mouseY = 0.f;
  window.addEventListener( MouseEvent::MOUSE_MOVE, [&]( const Event& event ) {

    auto mouseEvent = static_cast<const MouseEvent&>( event );

    mouseX = 2.f * ( mouseEvent.movementX / renderer.width()  - 0.5f );
    mouseY = 2.f * ( mouseEvent.movementY / renderer.height() - 0.5f );

  });

  window.addEventListener( WindowEvent::WINDOW_RESIZED, [&]( const Event& event ) {

    auto windowEvent = static_cast<const WindowEvent&>( event );

    camera->aspect = (float)windowEvent.width / (float)windowEvent.height;
    camera->updateProjectionMatrix();

    renderer.setSize( windowEvent.width, windowEvent.height );

  });

  /////////////////////////////////////////////////////////////////////////

  window.animate ( [&]( float ) -> bool {

    auto geometry = SphereGeometry::create( 50,
                                            Math::random() * 64,
                                            Math::random() * 32 );

    auto texture = Texture::create( TextureDesc( createImage(), THREE::RGBFormat ) );
    texture->needsUpdate( true );

    auto material = //MeshPhongMaterial::create(
                    //MeshLambertMaterial::create(
                    MeshBasicMaterial::create(
      Material::Parameters().add( "map", texture )
                            .add( "wireframe", true )
    );

    auto mesh = Mesh::create( geometry, material );

    scene->add( mesh );
    renderer.render( *scene, *camera );
    scene->remove( mesh );

    renderer.deallocateGeometry( *geometry );
    renderer.deallocateTexture( *texture );
    renderer.deallocateMaterial( *material );

    return true;

  } );

}

int main ( int argc, char* argv[] ) {

  return RunExample( test_memory );

}
