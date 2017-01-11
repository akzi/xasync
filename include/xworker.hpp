#pragma once
namespace xasync
{
	class xworker
	{
	public:
		xworker()
		{

		}

		template<typename T>
		void add(T &&action)
		{
			std::async(action);
		}
	private:

	};
}