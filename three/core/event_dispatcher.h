#ifndef THREE_EVENT_DISPATCHER_H
#define THREE_EVENT_DISPATCHER_H

#include <three/common.h>
#include <three/core/event_listener.h>
#include <three/events/event.h>
#include <three/events/core_event.h>

#include <unordered_map>
#include <vector>
#include <algorithm>
#include <functional>
#include <typeinfo>
#include <typeindex>

namespace three {

template<typename TKey>
class EventDispatcher {
public:

  virtual ~EventDispatcher() {}

  std::shared_ptr<EventListener> addEventListener( const TKey& type, const std::function<void(const Event&)>& func ) {

    auto listener = EventListener::create( func );

    listeners[ type ].emplace_back( listener );

    return listener;
  }

  void addEventListener( const TKey& type, const std::shared_ptr<EventListener>& listener ) {
    if(!hasEventListener(type, listener)) {
      listeners[ type ].emplace_back( listener );
    }
  }

  bool hasEventListener( const TKey& type ) const {
    return listeners.find( type ) != listeners.cend() ;
  }

  bool hasEventListener( const TKey& type, const std::shared_ptr<EventListener>& listener ) const {

    auto typeListeners = listeners.find( type );
    if( typeListeners  == listeners.end() ) {
      return false;
    } else {
      return std::find(typeListeners->second.cbegin(), typeListeners->second.cend(), listener) != typeListeners->second.end();
    }

  }

  void removeEventListeners() {
    listeners.clear();
  }

  void removeEventListener( const TKey& type ) {
    auto it = listeners.find( type );

    if(it != listeners.end()) {
      it->second.clear();
      listeners.erase(it);
    }

  }

  void removeEventListener( const TKey& type, const std::shared_ptr<EventListener>& listener ) {

    auto& typeListeners = listeners[ type ];
    auto it = std::find(typeListeners.cbegin(), typeListeners.cend(), listener);

    if( it != typeListeners.cend() ) {

      typeListeners.erase( it );

      if( typeListeners.empty() ){
        removeEventListener( type );
      }

    }

  }

  void dispatchEvent( const TKey& type, const Event& event ) {

    auto typeListeners = listeners.find( type );

    if(typeListeners != listeners.cend()) {

      for ( const auto& listener : typeListeners->second ) {

        (*listener)( event );

      }

    }

  }

  void dispatchEvent( const CoreEvent& event ) {

    auto typeListeners = listeners.find( event.type );

    if(typeListeners != listeners.cend()) {

      for ( const auto& listener : typeListeners->second ) {

        (*listener)( event );

      }

    }

  }

  void dispatchEvent( const TKey& eventName ) {
    auto ev = CoreEvent( eventName );
    dispatchEvent( ev );
  }

protected:

  std::unordered_map<TKey, std::vector<std::shared_ptr<EventListener>>> listeners;

};

typedef EventDispatcher<std::string> CoreEventDispatcher;

} // namespace three

#endif // THREE_EVENT_DISPATCHER_H
