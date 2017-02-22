#pragma once
#include <future>
#include <functional>
#include <type_traits>
#include <utility>
template <class Fn, class... ArgTypes> class AsyncWrapper
{
public:
	AsyncWrapper(int size);
	~AsyncWrapper();
	
	void addAsyncTask(Fn && fn, int i,ArgTypes&&... args);
	typename std::result_of<Fn(ArgTypes...)>::type getAsyncData(int i);

private:
	std::vector<std::future<typename std::result_of<Fn(ArgTypes...)>::type>> futures;
};

