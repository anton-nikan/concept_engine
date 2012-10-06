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
    using stream = Stream;
    using context = Context;
    using time = Time;
    using action_t = std::function<bool(Context&, Time)>;
    
public:
    template<typename T>
    object_t(const T& x) : object_(new model_t_<T>(x)), context_{}
    { }
    template<typename T>
    object_t(const T& x, Context c) : object_(new model_t_<T>(x)), context_(c)
    { }
    
    object_t(object_t const& x) : object_(x.object_->copy()), context_(x.context_) { }
    object_t(object_t&& x) = default;
    object_t& operator = (object_t x)
    { object_ = std::move(x.object_); context_ = x.context_; return *this; }
    
    friend void draw(object_t const& x, Stream& out, Context parent_context) {
        const Context local_context = parent_context + x.context_;
        x.object_->draw_object(out, local_context);
    }
    friend void animate(object_t& x, Time time) {
        if (x.action_) { if (x.action_(x.context_, time)) x.action_ = nullptr; }
        // TODO: animate T data_
    }
    friend void apply(object_t& x, action_t a) {
        x.action_ = a;
    }
    
    const Context& get_context() const { return context_; }
    
private:
    struct concept_t_ {
        virtual ~concept_t_() = default;
        virtual concept_t_* copy() const = 0;
        virtual void draw_object(Stream& stream, Context context) const = 0;
        virtual void animate_object(Time time) = 0;
    };
    
    template<typename T>
    struct model_t_ : concept_t_ {
        model_t_(T const& v) : data_(v) { }
        concept_t_* copy() const
        { return new model_t_(*this); }
        
        void draw_object(Stream& stream, Context context) const /* override - doesn't parse right? */
        { draw(data_, stream, context); }
        
        virtual void animate_object(Time time) override
        { animate(data_, time); }
        
        T data_;
    };
    
    std::unique_ptr<concept_t_> object_;
    Context context_;
    action_t action_;
};


#endif
