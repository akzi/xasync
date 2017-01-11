#pragma once
namespace xasync
{
	class xworker_pool
	{
	public:
		xworker_pool()
		{

		}
	private:
		std::vector<std::unique_ptr<xworker>> workers_;
	};
}