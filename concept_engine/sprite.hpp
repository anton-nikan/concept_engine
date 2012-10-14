//
//  sprite.hpp
//  concept_engine
//
//  Created by Anton Nikolaienko on 10/5/12.
//  Copyright (c) 2012 Anton Nikolaienko. All rights reserved.
//

#ifndef concept_engine_sprite_hpp
#define concept_engine_sprite_hpp

#include <future>
#include "concepts.hpp"
#include "context.hpp"

class sprite_t
{
public:
    using data_type = char;

    sprite_t(data_type x) : data_(x), width_(1), height_(1) { }
    sprite_t(data_type x, int width, int height) : data_(x), width_(width), height_(height) { }

    sprite_t(const sprite_t& x) : data_(x.data_), width_(x.width_), height_(x.height_) { }
    sprite_t(sprite_t&&) = default;
    sprite_t& operator = (sprite_t x) {
        data_ = std::move(x.data_);
        width_ = x.width_;
        height_ = x.height_;
        return *this;
    }
    
    template<typename Stream, typename Context>
    friend void draw(const sprite_t& x, Stream& stream, Context context)
    { stream << context << x.data_ << std::endl; }
    
private:
    data_type data_;
    int width_, height_;
};

template<> template<typename ...Args>
std::future<sprite_t> resource<sprite_t>::load(Args... args)
{
    std::promise<sprite_t> promise;
    try {
        sprite_t obj(args...);
        promise.set_value(std::move(obj));
    } catch (...) {
        promise.set_exception(std::current_exception());
    }
    return promise.get_future();
}

template<> template<>
std::future<sprite_t> resource<sprite_t>::load(const char* file_name)
{
    return resource<sprite_t>::load(file_name, 1, 1);
}

#endif
