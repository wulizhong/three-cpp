#ifndef THREE_EXAMPLES_CONTROLS_FIRST_PERSON_H
#define THREE_EXAMPLES_CONTROLS_FIRST_PERSON_H

#include <three/common.h>
#include <three/core/object3d.h>
#include <three/core/interfaces.h>
#include <three/events/events.h>
#include <three/utils/noncopyable.h>

using namespace three;
using namespace std::placeholders;

namespace three {

class FirstPersonControls : NonCopyable {
public:

  static std::shared_ptr<FirstPersonControls> create( 
    const std::shared_ptr<Object3D>& object, IWindow& window ) 
  {
    return std::shared_ptr<FirstPersonControls>( 
      new FirstPersonControls( object, window ) );
  }

  std::shared_ptr<Object3D> object;
  IWindow& window;

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

  bool noFly;

  bool freeze;

  bool mouseDragOn;

  float viewHalfX;
  float viewHalfY;

  void handleResize();

  void onMouseDown( const Event& event );

  void onMouseUp( const Event& event );

  void onMouseMove( const Event& event );

  void onKeyDown( const Event& event );

  void onKeyUp( const Event& event );

  void update ( float delta );

protected:
  explicit FirstPersonControls( const std::shared_ptr<Object3D>& object, 
    IWindow& window );

private:
  struct {
    std::shared_ptr<EventListener> mouseMoveListener;
    std::shared_ptr<EventListener> mouseUpListener;
    std::shared_ptr<EventListener> mouseDownListener;
    std::shared_ptr<EventListener> keyUpListener;
    std::shared_ptr<EventListener> keyDownListener;
  } listeners;

};

} // end namespace three

#endif // THREE_EXAMPLES_CONTROLS_FIRST_PERSON_H
