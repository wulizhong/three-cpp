#ifndef THREE_CORE_WINDOW_INTERFACE_H
#define THREE_CORE_WINDOW_INTERFACE_H

#include <three/common.h>
#include <three/core/event_dispatcher.h>
#include <three/utils/noncopyable.h>

namespace three {

class WindowInterface : public NonCopyable, public EventDispatcher {
public:

  virtual ~WindowInterface();

  virtual void animate( Update update ) = 0;
  virtual bool valid() const = 0;
};

#endif // THREE_CORE_WINDOW_INTERFACE_H
