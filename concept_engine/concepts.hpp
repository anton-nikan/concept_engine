//
//  concepts.hpp
//  concept_engine
//
//  Created by Anton Nikolaienko on 10/7/12.
//  Copyright (c) 2012 Anton Nikolaienko. All rights reserved.
//

#ifndef concept_engine_concepts_hpp
#define concept_engine_concepts_hpp

#warning "If you include this file nothing works"

template<typename Object, typename Stream, typename Context>
void draw(const Object& x, Stream& stream, Context context)
{
    static_assert(false, "Specialization not implemented. Implement your own draw() for these types.");
}

template<typename Object, typename Time>
void animate(Object& s, Time time)
{
    static_assert(false, "Specialization not implemented. Implement your own animate() for these types.");
}

template<typename Object, typename Action>
void apply(Object& x, Action a)
{
    static_assert(false, "Specialization not implemented. Implement your own apply() for these types.");
}

#include <future>

template<typename Type>
std::future<Type> load(const char* resource_name)
{
    static_assert(false, "Specialization not implemented. Implement your own load() for these types.");
}

#endif
