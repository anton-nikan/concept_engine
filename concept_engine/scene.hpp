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
#include "object.hpp"

// common scene type as a collection of objects
template<typename Object>
using scene_t = std::vector<Object>;

// specialization for scene drawing
template<typename Object, typename Stream = typename Object::stream, typename Context = typename Object::context, typename Time = typename Object::time>
void draw(const scene_t<Object>& s, Stream& stream, Context context)
{
    for (const auto& o : s) draw(o, stream, context);
}

template<typename Object, typename Time = typename Object::time>
void animate(scene_t<Object>& s, Time time)
{
    for (auto& o : s) animate(o, time);
}


#endif
