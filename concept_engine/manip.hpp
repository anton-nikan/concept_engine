//
//  manip.hpp
//  concept_engine
//
//  Created by Anton Nikolaienko on 10/6/12.
//  Copyright (c) 2012 Anton Nikolaienko. All rights reserved.
//

#ifndef concept_engine_manip_hpp
#define concept_engine_manip_hpp

#include "object.hpp"
#include "context.hpp"
#include "concepts.hpp"

template<typename Stream, typename Value, typename Time>
void move_to(object_t<Stream, context_t<Value>, Time>& x, Value to, typename Time::duration duration)
{
    const auto from = x.get_context().get_transformation();
    const auto step = (to - from) / duration.count();
    const auto end_time = Time::clock::now() + duration;
    apply(x, [=](context_t<Value>& c, Time t) -> bool {
        
        const auto cnt = (end_time - t).count();
        const auto delta = step * cnt;
        c = to - delta;
        
        return t >= end_time;
    });
}

#endif
