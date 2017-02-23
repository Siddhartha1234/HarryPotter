#include "AsyncWrapper.h"

template <class Fn, class... ArgTypes> 
AsyncWrapper<Fn, ArgTypes...> ::AsyncWrapper(int size)
{
	futures.resize(size);
}


template <class Fn, class... ArgTypes> 
AsyncWrapper<Fn,ArgTypes...> ::~AsyncWrapper()
{

}

template <class Fn, class... ArgTypes> 
void AsyncWrapper<Fn, ArgTypes...>::addAsyncTask(Fn && fn , int i ,ArgTypes&&... args)
{
	futures[i] = (std::async(std::launch::async ,fn,args));
}

template <class Fn, class... ArgTypes> 
typename std::result_of<Fn(ArgTypes...)>::type AsyncWrapper<Fn, ArgTypes...>::getAsyncData(int i)
{
	return futures[i].get();
}
