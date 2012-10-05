//
//  sprite.hpp
//  concept_engine
//
//  Created by Anton Nikolaienko on 10/5/12.
//  Copyright (c) 2012 Anton Nikolaienko. All rights reserved.
//

#ifndef concept_engine_sprite_hpp
#define concept_engine_sprite_hpp

#include "types.hpp"
#include "context.hpp"

using sprite_t = char;

void animate(sprite_t& s, animation_time_t time)
{ }

// learning to draw stuff
void draw(const sprite_t& x, render_stream_t& stream, context_t context)
{ stream << context << x << std::endl; }


#endif
