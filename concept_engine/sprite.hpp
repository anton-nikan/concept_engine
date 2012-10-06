//
//  sprite.hpp
//  concept_engine
//
//  Created by Anton Nikolaienko on 10/5/12.
//  Copyright (c) 2012 Anton Nikolaienko. All rights reserved.
//

#ifndef concept_engine_sprite_hpp
#define concept_engine_sprite_hpp

#include "context.hpp"

using sprite_t = char;

// learning to draw stuff
template<typename Stream, typename Context>
void draw(const sprite_t& x, Stream& stream, Context context)
{ stream << context << x << std::endl; }


#endif
