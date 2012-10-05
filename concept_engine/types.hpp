//
//  types.h
//  concept_engine
//
//  Created by Anton Nikolaienko on 10/5/12.
//  Copyright (c) 2012 Anton Nikolaienko. All rights reserved.
//

#ifndef concept_engine_types_hpp
#define concept_engine_types_hpp

#include <iostream>
#include <chrono>
#include <iomanip>

using coordinate_t = int;
using animation_time_t = std::chrono::time_point<std::chrono::high_resolution_clock>;
using render_stream_t = std::ostream;

#endif
