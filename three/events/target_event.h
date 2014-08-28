#ifndef THREE_EVENTS_TARGET_EVENT_H
#define THREE_EVENTS_TARGET_EVENT_H

#include <three/common.h>

#include <three/events/core_event.h>

namespace three {

class TargetEvent : public CoreEvent {
public:

  static const EventType TARGET_DISPOSE;
  static const EventType TARGET_UPDATE;
  static const EventType TARGET_ADDED;
  static const EventType TARGET_REMOVED;
  static const EventType TARGET_ADDED_TO_SCENE;

  TargetEvent( const EventType type, void* targetIn = nullptr )
  : CoreEvent( type ),
    target( targetIn ) {}

  virtual ~TargetEvent() {}

  void* target;

};

} // end namespace three

#endif // THREE_EVENTS_TARGET_EVENT_H
