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

// promise class to implement then() for immediate move_to
class immediate_then_t
{
public:
    using func_type = std::function<void()>;

    void then(func_type func)
    { func(); }
};


// immediate move_to
template<typename Stream, typename Value, typename Time>
immediate_then_t move_to(object_t<Stream, context_t<Value>, Time>& x, Value to)
{ x.set_context(to); return immediate_then_t(); }


// promise class to implement then() for animated move_to
class deferred_then_t
{
public:
    using func_type = std::function<void()>;

    deferred_then_t() : callback_{} { }
    
    void then(func_type func)
    { callback_ = func; }
    void operator() ()
    { if (callback_) callback_(); }
    
private:
    func_type callback_;
};

// animated move_to
template<typename Stream, typename Value, typename Time>
deferred_then_t& move_to(object_t<Stream, context_t<Value>, Time>& x, Value to, typename Time::duration duration)
{
    const auto from = x.get_context().get_transformation();
    const auto step = (to - from) / duration.count();
    const auto end_time = Time::clock::now() + duration;
    
    auto then = std::make_shared<deferred_then_t>();      // shared state
    apply(x, [=](context_t<Value>& c, Time t) -> bool {
        
        const auto cnt = (end_time - t).count();
        const auto delta = step * cnt;
        c = to - delta;
        
        if (t >= end_time) {
            (*then)();
            return true;
        }
        
        return false;
    });
    
    return *then;
}

#endif
