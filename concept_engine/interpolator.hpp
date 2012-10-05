//
//  interpolator.hpp
//  concept_engine
//
//  Created by Anton Nikolaienko on 10/5/12.
//  Copyright (c) 2012 Anton Nikolaienko. All rights reserved.
//

#ifndef concept_engine_interpolator_hpp
#define concept_engine_interpolator_hpp

#include "types.hpp"

template<typename T>
struct interpolator_t
{
    animation_time_t start_time;
    animation_time_t end_time;
    animation_time_t curr_time;
    T start_value;
    T end_value;
    
    interpolator_t() : start_value{}, end_value{}, start_time{}, end_time{}, curr_time{} { }
    explicit interpolator_t(T v) : start_value(v), end_value(v), start_time{}, end_time{}, curr_time{} { }
    interpolator_t(T start, T end, animation_time_t tstart, animation_time_t tend) :
    start_value(start), end_value(end), start_time(tstart), end_time(tend)
    { }
    
    T value() const
    {
        if (curr_time < start_time) return start_value;
        if (curr_time >= end_time) return end_value;
        
        auto duration = end_time - start_time;
        auto delta = curr_time - start_time;
        
        auto double_delta = std::chrono::duration_cast<std::chrono::duration<double, animation_time_t::period>>(delta);
        double a = double_delta / duration;
        
        return (1.0 - a) * start_value + a * end_value;
    }
    
    friend interpolator_t operator + (const interpolator_t& op1, const interpolator_t& op2)
    {
        // Taking snapshot from op
        T op_value = op1.value();
        
        interpolator_t res(op2);
        res.start_value = op_value + op2.start_value;
        res.end_value = op_value + op2.end_value;
        
        return res;
    }
};

// animation
template<typename T>
void animate(interpolator_t<T>& inter, animation_time_t time)
{
    inter.curr_time = time;
}

// manipulators
interpolator_t<coordinate_t> move_to(interpolator_t<coordinate_t> const& inter, coordinate_t pos)
{
    return interpolator_t<coordinate_t>(pos);
}

template<class Rep, class Period = std::ratio<1>>
interpolator_t<coordinate_t> move_to(interpolator_t<coordinate_t> const& inter, coordinate_t pos, std::chrono::duration<Rep, Period> duration)
{
    if (duration == std::chrono::duration<Rep, Period>::zero()) {
        return move_to(inter, pos);
    } else {
        auto now = animation_time_t::clock::now();
        interpolator_t<coordinate_t> new_inter{inter.value(), pos, now, now + duration};
        new_inter.curr_time = new_inter.start_time;
        
        return new_inter;
    }
}


#endif
