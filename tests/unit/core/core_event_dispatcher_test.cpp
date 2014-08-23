#include "gtest/gtest.h"
#include <tests/test_constants.h>

#include <three/core/event_dispatcher.h>
#include <three/events/event.h>
#include <three/events/core_event.h>

using namespace three;

class TestEvent : public CoreEvent {
public:

    TestEvent( int valIn ) : CoreEvent("testEvent"), val(valIn) {

    }

    int val;
};

void onSomeGlobalEvent( const Event& ev) {
    LOG("onSomeGlobalEvent called with event of type", static_cast<const CoreEvent&>(ev).type);
}

class Button : public CoreEventDispatcher {
public:

  Button() {}

  void dispose() {
    dispatchEvent("dispose");
  }

  void onSomeEvent( const Event& ev ) {
    LOG("Button::onSomeEvent called with event type", static_cast<const CoreEvent&>(ev).type);
  }

    void onTestEventHandler( const Event& ev ) {
        LOG("Button::onTestEventHandler called with event", static_cast<const CoreEvent&>(ev).type);
        auto te = static_cast<const TestEvent&>(ev);
        LOG("Button:onTestEventHandler TestEvent has value", static_cast<const TestEvent&>(ev).val);
    }

};

TEST(core_event_listener_test, constructor) {

    auto a = Button();
    auto ev = CoreEvent("testConstructor");

    std::function<void(const Event&)> func = std::bind(&Button::onSomeEvent, a, std::placeholders::_1);
    auto funcListener = EventListener::create( func );

    auto bindExpression = std::bind(&Button::onSomeEvent, a, std::placeholders::_1);
    auto bindListener = EventListener::create( bindExpression );

    auto lambdaListener = EventListener::create([](const Event& ev) {
        LOG("Lambda called with event type", static_cast<const CoreEvent&>(ev).type);
    });

    auto functionPointerListener = EventListener::create( onSomeGlobalEvent );

    EXPECT_NO_FATAL_FAILURE( (*funcListener)(ev) );
    EXPECT_NO_FATAL_FAILURE( (*lambdaListener)(ev) );
    EXPECT_NO_FATAL_FAILURE( (*bindListener)(ev) );
    EXPECT_NO_FATAL_FAILURE( (*functionPointerListener)(ev) );
}

TEST(core_event_dispatcher_test, addEventListener) {

    auto a = Button();

    a.addEventListener("click", EventListener::create([](const Event& ev) {
        LOG("addEventListener 1 click event", static_cast<const CoreEvent&>(ev).type);
    }));

    a.addEventListener("click", EventListener::create( onSomeGlobalEvent ) );
    auto listener = a.addEventListener("update", std::bind(&Button::onSomeEvent, a, std::placeholders::_1) );

    EXPECT_TRUE(a.hasEventListener("click"));
    EXPECT_TRUE(a.hasEventListener("update"));
    EXPECT_TRUE(listener != nullptr);
    EXPECT_TRUE(a.hasEventListener("update", listener));
}

TEST(core_event_dispatcher_test, removeEventListener) {

    auto a = Button();

    auto listener = a.addEventListener("click", [](const Event& ev) {} );
    a.removeEventListener("click", listener);

    EXPECT_FALSE(a.hasEventListener("click", listener));
    EXPECT_FALSE(a.hasEventListener("click"));

    // This will result in has click is TRUE, because the two passed event listeners
    // are differint instantiations and thus have different ids
    a.addEventListener("click", EventListener::create( [](const Event& ev) {} ) );
    a.removeEventListener("click", EventListener::create( [](const Event& ev) {} ) );

    EXPECT_TRUE(a.hasEventListener("click"));

    a.removeEventListener("click");

    EXPECT_FALSE(a.hasEventListener("click"));

    auto listener1 = EventListener::create( [](const Event& ev) {} );
    a.addEventListener("update", listener1);
    a.removeEventListener("update", listener1);

    EXPECT_FALSE(a.hasEventListener("update", listener1));
    EXPECT_FALSE(a.hasEventListener("update"));
}

TEST(core_event_dispatcher_test, removeEventListeners) {

    auto a = Button();

    a.addEventListener("click", EventListener::create( [](const Event& ev) { } ) );

    EXPECT_TRUE(a.hasEventListener("click"));

    a.removeEventListeners();

    EXPECT_FALSE(a.hasEventListener("click"));
}
