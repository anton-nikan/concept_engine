//
//  loading.hpp
//  concept_engine
//
//  Created by Anton Nikolaienko on 10/9/12.
//  Copyright (c) 2012 Anton Nikolaienko. All rights reserved.
//

#ifndef concept_engine_loading_hpp
#define concept_engine_loading_hpp

#include <future>
#include "concepts.hpp"

template<typename T, typename ...Args>
std::future<T> load(Args... args)
{
    std::promise<T> promise;
    try {
        T obj(args...);
        promise.set_value(std::move(obj));
    } catch (...) {
        promise.set_exception(std::current_exception());
    }
    return promise.get_future();
}

#endif
