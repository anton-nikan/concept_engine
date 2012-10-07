//
//  concepts.hpp
//  concept_engine
//
//  Created by Anton Nikolaienko on 10/7/12.
//  Copyright (c) 2012 Anton Nikolaienko. All rights reserved.
//

#ifndef concept_engine_concepts_hpp
#define concept_engine_concepts_hpp

// drawing concept
template<typename Object, typename Stream, typename Context>
void draw(const Object& x, Stream& stream, Context context);

// animating concept
template<typename Object, typename Time>
void animate(Object& s, Time time);

// action application concept
template<typename Object, typename Context, typename Time, typename Action = std::function<bool(Context&, Time)>>
void apply(Object& x, Action a);

#include <future>

// future loading concept
template<typename Type>
std::future<Type> load(const char* resource_name);

#endif
