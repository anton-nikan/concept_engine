//
//  scene.hpp
//  concept_engine
//
//  Created by Anton Nikolaienko on 10/5/12.
//  Copyright (c) 2012 Anton Nikolaienko. All rights reserved.
//

#ifndef concept_engine_scene_hpp
#define concept_engine_scene_hpp

#include <vector>
#include "types.hpp"
#include "context.hpp"
#include "object.hpp"

// common scene type as a collection of objects
template<typename S>
using scene_t = std::vector<object_t<S>>;

// specialization for scene drawing
template<typename S>
void draw(const scene_t<S>& s, S& stream, context_t context)
{
    for (const auto& o : s) draw(o, stream, context);
}

template<typename S>
void animate(scene_t<S>& s, animation_time_t time)
{
    for (auto& o : s) animate(o, time);
}


#endif
