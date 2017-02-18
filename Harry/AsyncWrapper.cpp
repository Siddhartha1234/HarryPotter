#include "AsyncWrapper.h"

template <class Fn, class... ArgTypes> 
AsyncWrapper<Fn,ArgTypes...>::AsyncWrapper()
{

}


template <class Fn, class... ArgTypes> 
AsyncWrapper<Fn,ArgTypes...>::~AsyncWrapper()
{

}

template <class Fn, class... ArgTypes> 
void AsyncWrapper<Fn,ArgTypes...>::addAsyncTask(Fn && fn , ArgTypes&&... args)
{
	futures.push_back(std::async(std::launch::async ,fn,args));
}

template <class Fn, class... ArgTypes> 
typename std::result_of<Fn(ArgTypes...)>::type  AsyncWrapper<Fn,ArgTypes...>::getAsyncData(int i)
{
	return futures[i].get();
}
