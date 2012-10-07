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
#include <array>
#include "object.hpp"
#include "concepts.hpp"

// common scene type as a collection of objects
template<typename Object>
using scene_t = std::vector<Object>;

// specialization for scene drawing
template<typename Object, typename Stream = typename Object::stream_type, typename Context = typename Object::context_type>
void draw(const scene_t<Object>& s, Stream& stream, Context context)
{
    for (const auto& o : s) draw(o, stream, context);
}

template<typename Object, typename Time = typename Object::time_type>
void animate(scene_t<Object>& s, Time time)
{
    for (auto& o : s) animate(o, time);
}


template<size_t SZ, typename Object>
using static_scene_t = std::array<Object, SZ>;

template<size_t SZ, typename Object, typename Stream = typename Object::stream_type, typename Context = typename Object::context_type>
void draw(const static_scene_t<SZ, Object>& s, Stream& stream, Context context)
{
    for (const auto& o : s) draw(o, stream, context);
}

template<size_t SZ, typename Object, typename Time = typename Object::time_type>
void animate(static_scene_t<SZ, Object>& s, Time time)
{
    for (auto& o : s) animate(o, time);
}

#endif
