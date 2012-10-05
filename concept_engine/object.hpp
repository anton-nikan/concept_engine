//
//  object.hpp
//  concept_engine
//
//  Created by Anton Nikolaienko on 10/5/12.
//  Copyright (c) 2012 Anton Nikolaienko. All rights reserved.
//

#ifndef concept_engine_object_hpp
#define concept_engine_object_hpp

#include <memory>
#include "context.hpp"

// common object type
class object_t {
public:
    template<typename T>
    object_t(const T& x, context_t c) : object_(new model_t_<T>(x)), context_(c)
    { }
    
    object_t(const object_t& x) : object_(x.object_->copy()), context_(x.context_) { }
    object_t(object_t&& x) = default;
    object_t& operator = (object_t x)
    { object_ = std::move(x.object_); context_ = x.context_; return *this; }
    
    friend void draw(const object_t& x, render_stream_t& stream, context_t parent_context) {
        context_t local_context = parent_context + x.context_;
        x.object_->draw_object(stream, local_context);
    }
    friend void animate(object_t& x, animation_time_t time) {
        animate(x.context_, time);
        x.object_->animate_object(time);
    }
    
private:
    struct concept_t_ {
        virtual ~concept_t_() = default;
        virtual concept_t_* copy() const = 0;
        virtual void draw_object(render_stream_t& stream, context_t context) const = 0;
        virtual void animate_object(animation_time_t time) = 0;
    };
    
    template<typename T>
    struct model_t_ : concept_t_ {
        model_t_(const T& v) : data_(v) { }
        concept_t_* copy() const override
        { return new model_t_(*this); }
        
        void draw_object(render_stream_t& stream, context_t context) const override
        { draw(data_, stream, context); }
        
        virtual void animate_object(animation_time_t time) override
        { animate(data_, time); }
        
        T data_;
    };
    
    std::unique_ptr<concept_t_> object_;
    context_t context_;
};


#endif
