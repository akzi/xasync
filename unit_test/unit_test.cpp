#pragma once
#include "../include/xasync.hpp"
#include "../../xtest/include/xtest.hpp"
#include "../../xutil/include/function_traits.hpp"

xtest_run;



template<typename Ret, typename ...Args, typename ...Params>
Ret async(const std::function<Ret(Args...)> &action, Params &&...params)
{
	Ret ret;
	auto action_wrap = [&](){
		ret = std::move(action(std::forward<Params>(params)...));
	};

	return ret;
}

template<typename Ret, typename ...Args, typename ...Params>
Ret async(Ret(action)(Args...), Params && ...params)
{
	Ret ret;
	auto action_wrap = [&]{
		ret = std::move(action(std::forward<Params>(params)...));
	};
	return ret;
}


template<typename Ret, typename Class, typename ...Args, typename ...Params >
Ret async(Ret(Class::*action)(Args...), Class &inst, Params && ...params)
{
	Ret ret;
	auto action_wrap = [&]()->Ret{
		ret = std::move((inst.*action)(std::forward<Params>(params)...));
	};
	return ret;
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

int move_test(std::string &&str)
{
	str.clear();
	return 0;
}

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
		auto b = async(xutil::to_function(add), 1, 2);
		xassert(b == 2 + 1);
		b = async(add, 1, 1);
		xassert(b == 1 + 1);

		add_functor obj;
		b = async(&add_functor::add, obj, 1, 2);

		b = async(xutil::to_function([](int a, int b) {return a + b; }), 1, 2);


		auto value = 0;
		auto old = async(change_value, value);
		xassert(value == 3);;


		value = 0;
		old = async(&add_functor::change_value, obj, value);
		xassert(value == 3);;

		b = async(xutil::to_function([](int &value) {
			auto old = value;
			value = 3;
			return old; 
		}), value);

		xassert(value == 3);;


		std::string str {"hello world"};
		auto res = async(move_test, std::move(str));

	}
}