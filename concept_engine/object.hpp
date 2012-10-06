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

// common object type
template<typename Stream, typename Context, typename Time>
class object_t {
public:
    using stream_type = Stream;
    using context_type = Context;
    using time_type = Time;
    using action_type = std::function<bool(Context&, Time)>;
    
public:
    template<typename T>
    object_t(T const& x) : object_(new model_t_<T>(x)), context_{}, action_{}
    { }
    template<typename T>
    object_t(T const& x, context_type c) : object_(new model_t_<T>(x)), context_(c), action_{}
    { }
    
    object_t(object_t const& x) : object_(x.object_->copy()), context_(x.context_), action_(x.action_) { }
    object_t(object_t&& x) : object_(std::move(x.object_)), context_(std::move(x.context_)), action_(std::move(x.action_)) { }
    object_t& operator = (object_t x)
    { object_ = std::move(x.object_); context_ = x.context_; action_ = x.action_; return *this; }
    
    friend void draw(object_t const& x, stream_type& out, context_type parent_context) {
        const context_type local_context = parent_context + x.context_;
        x.object_->draw_object(out, local_context);
    }
    friend void animate(object_t& x, time_type time) {
        if (x.action_) { if (x.action_(x.context_, time)) x.action_ = nullptr; }
        // TODO: animate T data_
    }
    friend void apply(object_t& x, action_type a) {
        x.action_ = a;
    }
    
    const context_type& get_context() const { return context_; }
    
private:
    struct concept_t_ {
        virtual ~concept_t_() = default;
        virtual concept_t_* copy() const = 0;
        virtual void draw_object(Stream& stream, Context context) const = 0;
    };
    
    template<typename T>
    struct model_t_ : concept_t_ {
        model_t_(T const& v) : data_(v) { }
        concept_t_* copy() const
        { return new model_t_(*this); }
        
        void draw_object(stream_type& stream, context_type context) const /* override - doesn't parse right? */
        { draw(data_, stream, context); }
                
        T data_;
    };
    
    std::unique_ptr<concept_t_> object_;
    context_type context_;
    action_type action_;
};


#endif
