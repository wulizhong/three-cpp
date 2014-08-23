#ifndef THREE_EVENTS_CORE_EVENT_H
#define THREE_EVENTS_CORE_EVENT_H

#include <three/common.h>

#include <three/constants.h>

namespace three {

class CoreEvent : public Event {
public:

  CoreEvent( const std::string& typeIn, void* targetIn = nullptr )
  : type( std::move( typeIn ) ),
    target( targetIn ) {}

  virtual ~CoreEvent() {}

  const std::string type;

  void* target;

};

} // end namespace three

#endif // THREE_EVENTS_CORE_EVENT_H
