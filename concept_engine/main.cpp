//
//  main.cpp
//  concept_engine
//
//  Created by Anton Nikolaienko on 9/29/12.
//  Copyright (c) 2012 Anton Nikolaienko. All rights reserved.
//


// Drawbacks:
// 1. The need to represent the scene as a collection requires add run-time polymorphism to object (virtual function calls).
// 2. Handle-Body forces to use indirect call (through unique_ptr).
// 3. Handle-Body requires pointer to implementation (body) so objects can be scattered in memory (although processing is sequential).
// 4. Context always copies along drawing sequence.
// 5. Operation is performed over the context (operator +) to move to more local context even if nothing has changed.
// 6. Render stream gets filled with anonymous calls from objects and contexts on every loop.


#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <memory>

// basic types
using sprite_t = char;


// context describes current state for object to draw
struct context_t
{
    context_t(int pos) : position_(pos) { }
    
    friend context_t operator + (const context_t& op1, const context_t& op2)
    { return context_t(op1.position_ + op2.position_); }
    
    int position_;
};


// render system definition
using render_stream_t = decltype(std::cout);

// learn to apply context
render_stream_t& operator << (render_stream_t& out, const context_t& x)
{ out << std::string(x.position_, ' '); return out; }

// learn drawing stuff
template<typename T>
void draw(const T& x, render_stream_t& stream, context_t context)
{ stream << context << x << std::endl; }


// common object type
class object_t {
public:
    template<typename T>
    object_t(const T& x, context_t c) : object_(new model_t_<T>(x)), context_(c)
    { }
    
    object_t(const object_t& x) : object_(x.object_->copy()), context_(x.context_) { }
    object_t(object_t&&) = default;
    object_t& operator = (object_t x)
    { object_ = std::move(x.object_); context_ = x.context_; return *this; }
    
    friend void draw(const object_t& x, render_stream_t& stream, context_t parent_context)
    {
        context_t local_context = parent_context + x.context_;
        x.object_->draw_object(stream, local_context);
    }
    
private:
    struct concept_t_ {
        virtual ~concept_t_() = default;
        virtual concept_t_* copy() const = 0;
        virtual void draw_object(render_stream_t& stream, context_t context) const = 0;
    };
    
    template<typename T>
    struct model_t_ : concept_t_ {
        model_t_(const T& v) : data_(v) { }
        
        concept_t_* copy() const override
        { return new model_t_(*this); }
        
        void draw_object(render_stream_t& stream, context_t context) const override
        { draw(data_, stream, context); }
        
        T data_;
    };
    
    std::unique_ptr<concept_t_> object_;
    context_t context_;
};


// common scene type as a collection of objects
using scene_t = std::vector<object_t>;

// specialization for scene drawing
void draw(const scene_t& s, render_stream_t& stream, context_t context)
{ for (const auto& o : s) draw(o, stream, context); }



int main()
{
    render_stream_t& cout_render = std::cout;
    context_t context{0};
    
    scene_t mini_scene;
    mini_scene.emplace_back(sprite_t('^'), 2);
    mini_scene.emplace_back(sprite_t('-'), 2);
    
    scene_t scene;
    scene.emplace_back(sprite_t('*'), 1);
    scene.emplace_back(sprite_t('@'), 2);
    scene.emplace_back(sprite_t('$'), 3);
    scene.emplace_back(sprite_t('#'), 4);
    scene.emplace_back(sprite_t('%'), 5);
    scene.emplace_back(mini_scene, 1);
    
    // render loop
    while (true) {
        draw(scene, cout_render, context);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    return 0;
}
