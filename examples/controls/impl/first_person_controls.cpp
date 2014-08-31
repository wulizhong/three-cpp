#include "examples/controls/first_person_controls.h"

#include <three/common.h>
#include <three/core/object3d.h>
#include <three/core/interfaces.h>
#include <three/events/event.h>
#include <three/events/mouse_event.h>
#include <three/events/keyboard_event.h>
#include <three/utils/noncopyable.h>

using namespace three;
using namespace std::placeholders;

namespace three {

void FirstPersonControls::handleResize() {
  viewHalfX = window.width() / 2.f;
  viewHalfY = window.height() / 2.f;
}

void FirstPersonControls::onMouseDown( const Event& event ) {

  auto mouseEvent = static_cast<const MouseEvent&>( event );

  if ( activeLook ) {

    switch ( mouseEvent.button ) {
      case MouseButton::LEFT: moveForward = true; break;
      case MouseButton::RIGHT: moveBackward = true; break;
      default:
        break;

    }

  }

  mouseDragOn = true;
}

void FirstPersonControls::onMouseUp( const Event& event ) {

  auto mouseEvent = static_cast<const MouseEvent&>( event );

  if ( activeLook ) {

    switch ( mouseEvent.button ) {
      case MouseButton::LEFT: moveForward = false; break;
      case MouseButton::RIGHT: moveBackward = false; break;
      default:
        break;
    }

  }

  mouseDragOn = false;

}

void FirstPersonControls::onMouseMove( const Event& event ) {

  auto mouseEvent = static_cast<const MouseEvent&>( event );

  mouseX = mouseEvent.screenX - viewHalfX;
  mouseY = mouseEvent.screenY - viewHalfY;

}

void FirstPersonControls::onKeyDown( const Event& event ) {

  auto keyboardEvent = static_cast<const KeyboardEvent&>( event );

  switch ( keyboardEvent.key ) {

    case KeyCode::KEY_UP:
    case KeyCode::KEY_w: moveForward = true; break;

    case KeyCode::KEY_LEFT:
    case KeyCode::KEY_a: moveLeft = true; break;

    case KeyCode::KEY_DOWN:
    case KeyCode::KEY_s: moveBackward = true; break;

    case KeyCode::KEY_RIGHT:
    case KeyCode::KEY_d: moveRight = true; break;

    case KeyCode::KEY_r: moveUp = true; break;
    case KeyCode::KEY_f: moveDown = true; break;

    case KeyCode::KEY_q: freeze = !freeze; break;
    default:
      break;

  }

};

void FirstPersonControls::onKeyUp( const Event& event ) {

  auto keyboardEvent = static_cast<const KeyboardEvent&>( event );

  switch( keyboardEvent.key ) {

    case KeyCode::KEY_UP:
    case KeyCode::KEY_w: moveForward = false; break;

    case KeyCode::KEY_LEFT:
    case KeyCode::KEY_a: moveLeft = false; break;

    case KeyCode::KEY_DOWN:
    case KeyCode::KEY_s: moveBackward = false; break;

    case KeyCode::KEY_RIGHT:
    case KeyCode::KEY_d: moveRight = false; break;

    case KeyCode::KEY_r: moveUp = false; break;
    case KeyCode::KEY_f: moveDown = false; break;
    default:
      break;

  }

};

void FirstPersonControls::update( float delta ) {

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

  if ( moveForward || ( autoForward && !moveBackward ) ) {
    object->translateZ( - ( actualMoveSpeed + autoSpeedFactor ) );
  }
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

FirstPersonControls::FirstPersonControls( 
  const std::shared_ptr<Object3D>& object, IWindow& window )
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
    noFly( true ),
    freeze( false ),
    mouseDragOn( false ),
    viewHalfX( 0 ),
    viewHalfY( 0 ) {

  listeners.mouseMoveListener = window.addEventListener( MouseEvent::MOUSE_MOVE, 
    std::bind( &FirstPersonControls::onMouseMove, this, _1 ) );

  listeners.mouseDownListener = window.addEventListener( MouseEvent::MOUSE_DOWN, 
    std::bind( &FirstPersonControls::onMouseDown, this, _1 ) );

  listeners.mouseUpListener = window.addEventListener( MouseEvent::MOUSE_UP, 
    std::bind( &FirstPersonControls::onMouseUp, this, _1 ) );

  listeners.keyDownListener = window.addEventListener( KeyboardEvent::KEY_DOWN, 
    std::bind( &FirstPersonControls::onKeyDown, this, _1 ) );

  listeners.keyUpListener = window.addEventListener( KeyboardEvent::KEY_UP, 
    std::bind( &FirstPersonControls::onKeyUp, this, _1 ) );

  this->handleResize();

}

} // end namespace three
