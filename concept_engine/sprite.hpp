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
#include "context.hpp"

using sprite_t = char;

// learning to draw stuff
template<typename Stream, typename Context>
void draw(const sprite_t& x, Stream& stream, Context context)
{ stream << context << x << std::endl; }

// missing decl (should come from concepts.hpp)
template <typename T>
std::future<T> load(const char* resource_name);

// learning to load sprites
template<>
std::future<sprite_t> load<sprite_t>(const char* resource_name)
{
    std::promise<sprite_t> promise;
    try {
        promise.set_value(resource_name[0]);         // don't forget to move when actually loading something
    } catch (...) {
        promise.set_exception(std::current_exception());
    }
    return promise.get_future();
}

#endif
