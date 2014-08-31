three.cpp
=========

### Status
[![Build Status](https://travis-ci.org/three-x/three-cpp.svg)](https://travis-ci.org/three-x/three-cpp)

#### A port of three.js to C++ #####

[three.js](http://mrdoob.github.com/three.js/) is a popular and accessible 3D library (credits to the three.js authors for the original library and to jdduke for the initial port to C++). The goal with three.cpp is to fully implement the relevant portions of the library in C++11, up to and including revision 65.

## Usage ##

### Setup ###
* `git clone git://github.com/three-x/three-cpp`
* `cd three-cpp`
* `./tpm install` (tpm requires python)
* `./tpm make`

## Sample code ##

This code creates a renderer, scene and camera, adds the camera and cube to the scene, then starts the rendering loop.

```c++

void scene() {

  using namespace three;

  auto renderer = GLRenderer::create();

  auto camera = PerspectiveCamera::create(
    75, renderer->width() / renderer->height(), 1, 10000
  );
  camera->position.z = 1000;

  auto scene = Scene::create();

  auto geometry = CubeGeometry::create( 200, 200, 200 );
  auto material = MeshBasicMaterial::create(
    Material::Paramaters().add( "color", Color(0xff0000) )
                          .add( "wireframe", true )
  );

  auto mesh = Mesh::create( geometry, material );
  scene->add( mesh );

  anim::gameLoop( [&]( float dt ) {

    mesh->rotation.x += 0.1f * dt;
    mesh->rotation.y += 0.2f * dt;

    renderer->render( *scene, *camera );

  } );

}

```

## Working examples ##

<img src="https://raw.github.com/three-x/three-cpp/master/data/thumbs/webgl_custom_attributes_particles.png">
<img src="https://raw.github.com/three-x/three-cpp/master/data/thumbs/webgl_custom_attributes_particles2.png">
<img src="https://raw.github.com/three-x/three-cpp/master/data/thumbs/webgl_custom_attributes_particles3.png">
<img src="https://raw.github.com/three-x/three-cpp/master/data/thumbs/webgl_geometry_hierarchy.png">
<img src="https://raw.github.com/three-x/three-cpp/master/data/thumbs/webgl_geometry_hierarchy2.png">
<img src="https://raw.github.com/three-x/three-cpp/master/data/thumbs/webgl_geometry_minecraft.png">
<img src="https://raw.github.com/three-x/three-cpp/master/data/thumbs/webgl_lines_colors.png">
<img src="https://raw.github.com/three-x/three-cpp/master/data/thumbs/webgl_lines_cubes.png">
<img src="https://raw.github.com/three-x/three-cpp/master/data/thumbs/webgl_lines_sphere.png">
<img src="https://raw.github.com/three-x/three-cpp/master/data/thumbs/webgl_particles_billboards.png">
<img src="https://raw.github.com/three-x/three-cpp/master/data/thumbs/webgl_particles_billboards_colors.png">
<img src="https://raw.github.com/three-x/three-cpp/master/data/thumbs/webgl_particles_random.png">
<img src="https://raw.github.com/three-x/three-cpp/master/data/thumbs/webgl_particles_sprites.png">
<img src="https://raw.github.com/three-x/three-cpp/master/data/thumbs/webgl_shader.png">
<img src="https://raw.github.com/three-x/three-cpp/master/data/thumbs/webgl_shader2.png">
<img src="https://raw.github.com/three-x/three-cpp/master/data/thumbs/webgl_shader_lava.png">
<img src="https://raw.github.com/three-x/three-cpp/master/data/thumbs/webgl_test_memory.png">

## Status ##

three-x is currently undergoing a major refactoring.

## Dependencies ##
* CMake
* Python
* Optional: Vagrant for provisioning the vm linux box

## Supported Platforms ##

You need a modern C++11 compiler:
* >= Clang 3.4
* >= GCC 4.8
* MSVC 2013

## Troubleshooting ##

* Why is it complaining about SDL on 64-bit Win builds?
    * CMake is likely pulling in 32-bit libraries. You can manually change the *${SDL_LIBRARY}* and *${SDLMAIN_LIBRARY}* CMake variables to refer to the proper libraries; simply change the **lib** directory reference to **lib64** if using the provided SDL implementation in **externals**.
