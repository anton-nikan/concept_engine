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

// context describes the state for object to draw
template<typename Transformation>
class context_t {
public:
    using transformation_type = Transformation;
    
public:
    context_t() : transform_{} { }
    context_t(transformation_type t) : transform_{t} { }
    
    context_t& operator = (const context_t& v)
    { transform_ = v.transform_; return *this; }
    
    friend context_t operator + (const context_t& op1, const context_t& op2)
    { return context_t(op1.transform_ + op2.transform_); }
    
    // learning to apply context
    template<typename S>
    friend S& operator << (S& out, const context_t& x)
    { out << x.transform_; return out; }

    // specialization for ostream and int
    friend std::ostream& operator << (std::ostream& out, const context_t<int>& x)
    { out << std::setw(x.transform_); return out; }
    // specialization for ostream and double
    friend std::ostream& operator << (std::ostream& out, const context_t<double>& x)
    { out << std::setw(static_cast<int>(x.transform_)); return out; }
    
    const transformation_type& get_transformation() const { return transform_; }
    
private:
    transformation_type transform_;
};

#endif
