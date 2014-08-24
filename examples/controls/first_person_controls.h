#ifndef THREE_EXAMPLES_CONTROLS_FIRST_PERSON_H
#define THREE_EXAMPLES_CONTROLS_FIRST_PERSON_H

#include <three/common.h>
#include <three/core/object3d.h>
#include <three/events/event.h>
#include <three/events/mouse_event.h>
#include <three/events/keyboard_event.h>

using namespace three;
using namespace three_examples;
using namespace std::placeholders;

class FirstPersonControls {
public:

  static std::shared_ptr<FirstPersonControls> create( std::shared_ptr<Object3D> object, GLWindow& window ) {
    return three::make_shared<FirstPersonControls>( object, window );
  }

  std::shared_ptr<Object3D> object;
  GLWindow& window;

  std::array<std::shared_ptr<EventListener>, 5> listeners;

  Vector3 target;

  float movementSpeed;
  float lookSpeed;
  bool lookVertical;

  bool autoForward;

  bool activeLook;

  bool heightSpeed;
  float heightCoef;
  float heightMin;
  float heightMax;

  bool constrainVertical;

  float verticalMin;
  float verticalMax;

  float autoSpeedFactor;

  float mouseX;
  float mouseY;

  float lat;
  float lon;
  float phi;
  float theta;

  bool moveForward;
  bool moveBackward;
  bool moveLeft;
  bool moveRight;
  bool moveUp;
  bool moveDown;

  bool freeze;

  bool mouseDragOn;

  float viewHalfX;
  float viewHalfY;

  virtual ~FirstPersonControls() {

    // window->removeEventListener( MouseEvent::MOUSE_MOVE, bind( this, &FirstPersonControls::onMouseMove ) );
    // window->removeEventListener( MouseEvent::MOUSE_DOWN, bind( this, &FirstPersonControls::onMouseDown ) );
    // window->removeEventListener( MouseEvent::MOUSE_Up, bind( this, &FirstPersonControls::onMouseUp ) );

    // window->removeEventListener( KeyboardEvent::KEY_DOWN, bind( this, &FirstPersonControls::onKeyDown ) );
    // window->removeEventListener( KeyboardEvent::KEY_UP, bind( this, &FirstPersonControls::onKeyUp ) );

  }

  void handleResize() {
      // viewHalfX = window->width() / 2.f;
      // viewHalfY = window->height() / 2.f;
  }

  void onMouseDown( const Event& event ) {

    auto mouseEvent = static_cast<const MouseEvent&>( event );

    if ( activeLook ) {

      switch ( mouseEvent.button ) {

        case 0: moveForward = true; break;
        case 2: moveBackward = true; break;

      }

    }

    mouseDragOn = true;
  }

  void onMouseUp( const Event& event ) {

    auto mouseEvent = static_cast<const MouseEvent&>( event );

    if ( activeLook ) {

      switch ( mouseEvent.button ) {

        case 0: moveForward = false; break;
        case 2: moveBackward = false; break;

      }

    }

    mouseDragOn = false;

  }

  void onMouseMove( const Event& event ) {

    auto mouseEvent = static_cast<const MouseEvent&>( event );

    mouseX = mouseEvent.screenX - viewHalfX;
    mouseY = mouseEvent.screenY - viewHalfY;

  }

  void onKeyDown( const Event& event ) {

    auto keyboardEvent = static_cast<const KeyboardEvent&>( event );

    //event.preventDefault();

    switch ( keyboardEvent.key ) {

      case 38: /*up*/
      case 87: /*W*/ moveForward = true; break;

      case 37: /*left*/
      case 65: /*A*/ moveLeft = true; break;

      case 40: /*down*/
      case 83: /*S*/ moveBackward = true; break;

      case 39: /*right*/
      case 68: /*D*/ moveRight = true; break;

      case 82: /*R*/ moveUp = true; break;
      case 70: /*F*/ moveDown = true; break;

      case 81: /*Q*/ freeze = !freeze; break;

    }

  };

  void onKeyUp( const Event& event ) {

    auto keyboardEvent = static_cast<const KeyboardEvent&>( event );

    switch( keyboardEvent.key ) {

      case 38: /*up*/
      case 87: /*W*/ moveForward = false; break;

      case 37: /*left*/
      case 65: /*A*/ moveLeft = false; break;

      case 40: /*down*/
      case 83: /*S*/ moveBackward = false; break;

      case 39: /*right*/
      case 68: /*D*/ moveRight = false; break;

      case 82: /*R*/ moveUp = false; break;
      case 70: /*F*/ moveDown = false; break;

    }

  };

  void update ( float delta ) {

    if ( freeze ) {

      return;

    }

    if ( heightSpeed ) {

      float y = Math::clamp( object->position().y, heightMin, heightMax );
      float heightDelta = y - heightMin;

      autoSpeedFactor = delta * ( heightDelta * heightCoef );

    } else {

      autoSpeedFactor = 0.0;

    }

    float actualMoveSpeed = delta * movementSpeed;

    if ( moveForward || ( autoForward && !moveBackward ) ) object->translateZ( - ( actualMoveSpeed + autoSpeedFactor ) );
    if ( moveBackward ) object->translateZ( actualMoveSpeed );

    if ( moveLeft ) object->translateX( - actualMoveSpeed );
    if ( moveRight ) object->translateX( actualMoveSpeed );

    if ( moveUp ) object->translateY( actualMoveSpeed );
    if ( moveDown ) object->translateY( - actualMoveSpeed );

    float actualLookSpeed = delta * lookSpeed;

    if ( !activeLook ) {

      actualLookSpeed = 0.f;

    }

    float verticalLookRatio = 1.f;

    if ( constrainVertical ) {

      verticalLookRatio = Math::PI() / ( verticalMax - verticalMin );

    }

    lon += mouseX * actualLookSpeed;
    if( lookVertical ) lat -= mouseY * actualLookSpeed * verticalLookRatio;

    lat = Math::max( - 85.f, Math::min( 85.f, lat ) );
    phi = Math::degToRad( 90.f - lat );

    theta = Math::degToRad( lon );

    if ( constrainVertical ) {

      phi = Math::mapLinear( phi, 0.f, Math::PI(), verticalMin, verticalMax );

    }

    auto targetPosition = target;
    const auto& position = object->position();

    targetPosition.x = position.x + 100 * Math::sin( phi ) * Math::cos( theta );
    targetPosition.y = position.y + 100 * Math::cos( phi );
    targetPosition.z = position.z + 100 * Math::sin( phi ) * Math::sin( theta );

    object->lookAt( targetPosition );

  };

protected:
  explicit FirstPersonControls( std::shared_ptr<Object3D> object, GLWindow& window )
    : object( object ),
      window( window ),
      target( Vector3() ),
      movementSpeed ( 1.0 ),
      lookSpeed( 0.005 ),
      lookVertical( true ),
      autoForward( false ),
      activeLook( true),
      heightSpeed( false),
      heightCoef( 1.0 ),
      heightMin( 0.0 ),
      heightMax( 1.0 ),
      constrainVertical( false ),
      verticalMin( 0 ),
      verticalMax( Math::PI() ),
      autoSpeedFactor( 0.0 ),
      mouseX( 0 ),
      mouseY( 0 ),
      lat( 0 ),
      lon( 0 ),
      phi( 0 ),
      theta( 0),
      moveForward( false ),
      moveBackward( false ),
      moveLeft( false ),
      moveRight( false ),
      freeze( false ),
      mouseDragOn( false ),
      viewHalfX( 0 ),
      viewHalfY( 0 ) {

        window.addEventListener( MouseEvent::MOUSE_MOVE, std::bind( &FirstPersonControls::onMouseMove, this, _1 ) );
        window.addEventListener( MouseEvent::MOUSE_DOWN, std::bind( &FirstPersonControls::onMouseDown, this, _1 ) );
        window.addEventListener( MouseEvent::MOUSE_Up, std::bind( &FirstPersonControls::onMouseUp, this, _1 ) );

        window.addEventListener( KeyboardEvent::KEY_DOWN, std::bind( &FirstPersonControls::onKeyDown, this, _1 ) );
        window.addEventListener( KeyboardEvent::KEY_UP, std::bind( &FirstPersonControls::onKeyUp, this, _1 ) );

        this->handleResize();

      }
};
