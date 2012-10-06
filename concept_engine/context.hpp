//
//  context.hpp
//  concept_engine
//
//  Created by Anton Nikolaienko on 10/5/12.
//  Copyright (c) 2012 Anton Nikolaienko. All rights reserved.
//

#ifndef concept_engine_context_hpp
#define concept_engine_context_hpp

#include <iostream>
#include <iomanip>
#include "interpolator.hpp"

// context describes the state for object to draw
template<typename Coordinate, typename Time>
class context_t {
    interpolator_t<Coordinate, Time> position_;
    context_t(interpolator_t<Coordinate, Time> const& v) : position_(v) { }
public:
    context_t() : position_{} { }
    context_t(Coordinate pos) : position_{pos} { }
    
    context_t& operator = (const context_t& v)
    { position_ = v.position_; return *this; }
    
    friend context_t operator + (const context_t& op1, const context_t& op2)
    { return context_t(op1.position_ + op2.position_); }
    
    friend void animate(context_t& x, Time time)
    { animate(x.position_, time); }
    
    template<typename Duration = typename Time::duration>
    friend context_t move_to(context_t object, Coordinate pos, Duration duration)
    { object.position_ = move_to(object.position_, pos, duration); return object; }
    
    // learning to apply context
    template<typename S>
    friend S& operator << (S& out, const context_t& x)
    { out << std::setw(x.position_.value()); return out; }
};

#endif
