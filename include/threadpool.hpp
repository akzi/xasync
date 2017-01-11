#pragma once
namespace xipc
{
	class threadpool
	{
	public:
		threadpool()
		{

		}

		template<T>
		void add(T &&action)
		{
			std::async(action);
		}
	private:

	};
}