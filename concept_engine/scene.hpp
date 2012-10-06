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
#include "context.hpp"
#include "object.hpp"

// common scene type as a collection of objects
template<typename Stream, typename Context, typename Time>
using scene_t = std::vector<object_t<Stream, Context, Time>>;

// specialization for scene drawing
template<typename Stream, typename Context, typename Time>
void draw(const scene_t<Stream, Context, Time>& s, Stream& stream, Context context)
{
    for (const auto& o : s) draw(o, stream, context);
}

template<typename Stream, typename Context, typename Time>
void animate(scene_t<Stream, Context, Time>& s, Time time)
{
    for (auto& o : s) animate(o, time);
}


#endif
