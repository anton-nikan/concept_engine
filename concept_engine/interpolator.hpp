//
//  interpolator.hpp
//  concept_engine
//
//  Created by Anton Nikolaienko on 10/5/12.
//  Copyright (c) 2012 Anton Nikolaienko. All rights reserved.
//

#ifndef concept_engine_interpolator_hpp
#define concept_engine_interpolator_hpp

#include <chrono>

template<typename Value, typename Time>
struct interpolator_t
{
    Time start_time;
    Time end_time;
    Time curr_time;
    Value start_value;
    Value end_value;
    
    interpolator_t() : start_value{}, end_value{}, start_time{}, end_time{}, curr_time{} { }
    explicit interpolator_t(Value v) : start_value(v), end_value(v), start_time{}, end_time{}, curr_time{} { }
    interpolator_t(Value start, Value end, Time tstart, Time tend) :
    start_value(start), end_value(end), start_time(tstart), end_time(tend)
    { }
    
    Value value() const
    {
        if (curr_time < start_time) return start_value;
        if (curr_time >= end_time) return end_value;
        
        auto duration = end_time - start_time;
        auto delta = curr_time - start_time;
        
        typedef typename Time::period tperiod;
        auto double_delta = std::chrono::duration_cast<std::chrono::duration<double, tperiod>>(delta);
        double a = double_delta / duration;
        
        return (1.0 - a) * start_value + a * end_value;
    }
    
    friend interpolator_t operator + (const interpolator_t& op1, const interpolator_t& op2)
    {
        // Taking snapshot from op
        Value op_value = op1.value();
        
        interpolator_t res(op2);
        res.start_value = op_value + op2.start_value;
        res.end_value = op_value + op2.end_value;
        
        return res;
    }
};

// animation
template<typename Value, typename Time>
void animate(interpolator_t<Value, Time>& inter, Time time)
{
    inter.curr_time = time;
}

// manipulators
template<typename Value, typename Time>
interpolator_t<Value, Time> move_to(interpolator_t<Value, Time> const& inter, Value pos)
{
    return interpolator_t<Value, Time>(pos);
}

template<typename Value, typename Time, typename Duration = typename Time::duration>
interpolator_t<Value, Time> move_to(interpolator_t<Value, Time> const& inter, Value pos, Duration duration)
{
    if (duration == Duration::zero()) {
        return move_to(inter, pos);
    } else {
        auto now = Time::clock::now();
        interpolator_t<Value, Time> new_inter{inter.value(), pos, now, now + duration};
        new_inter.curr_time = new_inter.start_time;
        
        return new_inter;
    }
}


#endif
