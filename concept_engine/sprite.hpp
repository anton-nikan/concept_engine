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
    sprite_t(char x) : data_(x), width_(1), height_(1) { }
    sprite_t(char x, int width, int height) : data_(x), width_(width), height_(height) { }
    sprite_t(const char* file_name) : data_(file_name[0]), width_(1), height_(1) { }
    sprite_t(const char* file_name, int width, int height) : data_(file_name[0]), width_(width), height_(height) { }

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
    char data_;
    int width_, height_;
};

#endif
