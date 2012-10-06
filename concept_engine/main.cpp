//
//  main.cpp
//  concept_engine
//
//  Created by Anton Nikolaienko on 9/29/12.
//  Copyright (c) 2012 Anton Nikolaienko. All rights reserved.
//


// Drawbacks:
// 1. The need to represent the scene as a collection requires add run-time polymorphism to object (virtual function calls).
// 2. Handle-Body forces to use indirect call (through unique_ptr).
// 3. Handle-Body requires pointer to implementation (body) so objects can be scattered in memory (while processing is sequential).
// 4. Context always copies along drawing sequence.
// 5. Operation is performed over the context (operator +, copy) to move to more local context even if nothing has changed.
// 6. Render stream gets filled with anonymous calls from objects and contexts on every loop.
// 7. Complex dependencies between elements (will be hard to put apart).


#include <sstream>
#include <thread>
#include "sprite.hpp"
#include "scene.hpp"


using transformation_t = double;
using render_stream_t = std::ostream;
using animation_time_t = std::chrono::time_point<std::chrono::high_resolution_clock>;
using render_context_t = context_t<transformation_t, animation_time_t>;
using scene_object_t = object_t<render_stream_t, render_context_t, animation_time_t>;
using scene = scene_t<scene_object_t>;

void move_to(scene_object_t& x, transformation_t to, animation_time_t::duration duration)
{
    const transformation_t from = x.get_context().get_transformation();
    const double step = static_cast<double>(to - from) / duration.count();
    const animation_time_t end_time = animation_time_t::clock::now() + duration;
    apply(x, [to, step, end_time](render_context_t& c, animation_time_t t)->bool {
        
        const double cnt = (end_time - t).count();
        const double delta = step * cnt;
        c = to - delta;
        
        return t >= end_time;
    });
}


// === Client code goes below ===


// learning to draw batches
void draw(const std::ostringstream& in, render_stream_t& out, render_context_t ctxt)
{ out << ctxt << in.str() << std::endl; }

scene main_scene;

void init()
{
    scene mini_scene;
    mini_scene.emplace_back(sprite_t('^'));
    mini_scene.emplace_back(sprite_t('-'), 2);
    
    main_scene.emplace_back(sprite_t('*'), 1);
    main_scene.emplace_back(sprite_t('@'), 2);
    main_scene.emplace_back(sprite_t('$'), 3);
    main_scene.emplace_back(sprite_t('#'), 4);
    main_scene.emplace_back(sprite_t('%'), 5);
    main_scene.emplace_back(mini_scene);
    
//    // pre-baking some scene
//    // NOTE: does not work because ostringstream can't be copied only moved
//    // TODO: allow moving
//    {
//        scene_t batch_scene;
//        batch_scene.emplace_back(sprite_t('+'), 10);
//        batch_scene.emplace_back(sprite_t('|'), 10);
//        batch_scene.emplace_back(sprite_t('+'), 10);
//        
//        std::ostringstream render_batch;
//        draw(batch_scene, render_batch, {});
//        
//        // ...and adding to the main scene
//        main_scene.emplace_back(std::move(render_batch), 0);
//    }
}

int main()
{
    init();
    
    render_context_t cntxt{};
    animation_time_t current_time;
    
    move_to(main_scene[0], 5, std::chrono::seconds(2));
    move_to(main_scene[1], 7, std::chrono::seconds(1));
    move_to(main_scene[2], 3, std::chrono::seconds(3));
    move_to(main_scene[3], 4, std::chrono::seconds(9));
    move_to(main_scene[4], 6, std::chrono::seconds(4));
    move_to(main_scene[5], 30, std::chrono::seconds(4));
    
    // render loop
    std::ostream cout_render(std::cout.rdbuf());
    while (true) {
        current_time = animation_time_t::clock::now();

        animate(main_scene, current_time);
        draw(main_scene, cout_render, cntxt);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    return 0;
}
