#if __cplusplus >= 201703L

#include "test144_t.h"
#include "test355_t.h"
#include "test364_t.h"
#include "test372_t.h"
#include "test412_t.h"
#include "test504_t.h"
#include "test505_t.h"
#include "test506_t.h"
#include "test533_t.h"
#include "test570_t.h"
#include "test375_t.h"
#include "test376_t.h"
#include "test377_t.h"
#include "test378_t.h"
#include "test576_t.h"
#include "event_list_t.h"
#include "event_tokens_t.h"
#include "conditional_t.h"
#include "../examples/timer_switch_t.h"
#include <gtest/gtest.h>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

namespace threadsafe {

#include "all-tests.h"

TEST(timer_switch, 1)
{
	sc_timer_switch::user_model m;
	sc_timer_switch sc(&m);
	sc.init();

	EXPECT_EQ(typeid(sc_timer_switch::state_off), typeid(*sc.cur_state));

	std::thread t([&sc]{ sc.dispatch_loop(); });
	std::this_thread::sleep_for(10ms); // Give time for dispatch_loop to be entered...

	sc.model.push_event(&sc_timer_switch::state::event_button);
	std::this_thread::sleep_for(10ms);
	EXPECT_EQ(typeid(sc_timer_switch::state_on), typeid(*sc.cur_state));
	sc.model.push_event(&sc_timer_switch::state::event_button);
	std::this_thread::sleep_for(10ms);
	EXPECT_EQ(typeid(sc_timer_switch::state_off), typeid(*sc.cur_state));
	sc.model.push_event(&sc_timer_switch::state::event_button);

	sc.model.cancel_wait();
	t.join();

	EXPECT_EQ(typeid(sc_timer_switch::state_on), typeid(*sc.cur_state));

	sc.model.push_event(&sc_timer_switch::state::event_timer);
	sc.model.push_event(&sc_timer_switch::state::event_timer);
	sc.model.push_event(&sc_timer_switch::state::event_timer);
	sc.model.push_event(&sc_timer_switch::state::event_timer);
	sc.model.push_event(&sc_timer_switch::state::event_timer);

	auto e = sc.model.pop_event();
	if (e) sc.dispatch(*e);

	EXPECT_EQ(typeid(sc_timer_switch::state_off), typeid(*sc.cur_state));
}

}

#endif

