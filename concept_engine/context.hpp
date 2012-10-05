//
//  context.hpp
//  concept_engine
//
//  Created by Anton Nikolaienko on 10/5/12.
//  Copyright (c) 2012 Anton Nikolaienko. All rights reserved.
//

#ifndef concept_engine_context_hpp
#define concept_engine_context_hpp

#include "types.hpp"
#include "interpolator.hpp"

// context describes the state for object to draw
class context_t {
    interpolator_t<coordinate_t> position_;
    context_t(interpolator_t<coordinate_t> const& v) : position_(v) { }
public:
    context_t() : position_{} { }
    context_t(coordinate_t pos) : position_{pos} { }
    
    context_t& operator = (const context_t& v)
    { position_ = v.position_; return *this; }
    
    friend context_t operator + (const context_t& op1, const context_t& op2)
    { return context_t(op1.position_ + op2.position_); }
    
    friend void animate(context_t& x, animation_time_t time)
    { animate(x.position_, time); }
    
    template<class Rep, class Period = std::ratio<1>>
    friend context_t move_to(context_t object, coordinate_t pos, std::chrono::duration<Rep, Period> duration)
    { object.position_ = move_to(object.position_, pos, duration); return object; }
    
    // learning to apply context
    friend render_stream_t& operator << (render_stream_t& out, const context_t& x)
    { out << std::setw(x.position_.value()); return out; }
};

#endif
