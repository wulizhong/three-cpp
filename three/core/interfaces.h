#ifndef THREE_INTERFACES_H
#define THREE_INTERFACES_H

#include <three/fwd.h>
#include <three/constants.h>
#include <three/gl.h>
#include <three/core/event_dispatcher.h>
#include <three/utils/noncopyable.h>

#include <memory>

namespace three {

class THREE_DECL IFog {
public:
  typedef std::shared_ptr<IFog> Ptr;
  virtual THREE::FogType type() const = 0;
  virtual Ptr clone() const = 0;
  virtual ~IFog() { }
};

class THREE_DECL IGeometry {
public:
  virtual void applyMatrix( Matrix4& ) = 0;
  virtual void computeBoundingBox() = 0;
  virtual void computeBoundingSphere() = 0;
  virtual void computeVertexNormals( bool areaWeighted = false ) = 0;
  virtual void computeTangents() = 0;
  virtual ~IGeometry() { }
};

class THREE_DECL IPlugin {
public:
  typedef std::shared_ptr<IPlugin> Ptr;
  virtual void init( GLRenderer& renderer ) = 0;
  virtual void update( Scene& scene, Camera& camera ) = 0;
  virtual void render( Scene& scene, Camera& camera, int width, int height ) = 0;
  virtual ~IPlugin() { }
};

class THREE_DECL IWindow : public NonCopyable, public EventDispatcher {
public:

  virtual ~IWindow() {};
  // TODO Refactor the gl mess
  virtual GLInterface createGLInterface();
  virtual void animate( Update update ) = 0;
  virtual bool valid() const = 0;

  virtual int width() const = 0;
  virtual int height() const = 0;
};

}

#endif // THREE_INTERFACES_H
