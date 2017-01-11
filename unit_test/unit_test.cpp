#pragma once
#include "../include/xipc.hpp"
#include "../../xtest/include/xtest.hpp"

xtest_run;



template<typename Ret, typename ...Args, typename ...Params>
Ret ipc(const std::function<Ret(Args...)> &action, Params &&...params)
{
	return action(std::forward<Params>(params)...);
}


template<typename Ret, typename ...Args, typename ...Params>
Ret ipc(Ret(action)(Args...), Params && ...params)
{
	return action(std::forward<Params>(params)...);
}


template<typename Ret, typename Class, typename ...Args, typename ...Params >
Ret ipc(Ret(Class::*action)(Args...), Class &inst, Params && ...params)
{
	return (inst.*action)(std::forward<Params>(params)...);
}


struct add_functor 
{
	int add(int a, int b)
	{
		return a + b;
	}

	int change_value(int &val)
	{
		auto old = val;
		val = 3;
		return old;
	}
};


int add(int a, int b)
{
	return a + b;
}


int change_value(int &val)
{
	auto old = val;
	val = 3;
	return old;
}

XTEST_SUITE(xipc)
{
	XUNIT_TEST(call)
	{
		auto b = ipc(xutil::to_function(add), 1, 2);
		xassert(b == 2 + 1);
		b = ipc(add, 1, 1);
		xassert(b == 1 + 1);

		add_functor obj;
		b = ipc(&add_functor::add, obj, 1, 2);

		b = ipc(xutil::to_function([](int a, int b) {return a + b; }), 1, 2);


		auto value = 0;
		auto old = ipc(change_value, value);
		xassert(value == 3);;


		value = 0;
		old = ipc(&add_functor::change_value, obj, value);
		xassert(value == 3);;

		b = ipc(xutil::to_function([](int &value) {
			auto old = value;
			value = 3;
			return old; 
		}), value);

		xassert(value == 3);;
	}
}