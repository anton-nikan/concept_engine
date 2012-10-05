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
// 3. Handle-Body requires pointer to implementation (body) so objects can be scattered in memory (although processing is sequential).
// 4. Context always copies along drawing sequence.
// 5. Operation is performed over the context (operator +) to move to more local context even if nothing has changed.
// 6. Render stream gets filled with anonymous calls from objects and contexts on every loop.
// 7. Complex dependencies between elements (will be hard to put apart).


#include <sstream>
#include <thread>
#include "sprite.hpp"
#include "scene.hpp"

// learning to draw batches
void draw(const std::ostringstream& in, render_stream_t& out, context_t context)
{ out << context << in.str() << std::endl; }


scene_t scene;

void init()
{
    scene_t mini_scene;
    mini_scene.emplace_back(sprite_t('^'), 2);
    mini_scene.emplace_back(sprite_t('-'), 2);
    
    scene.emplace_back(sprite_t('*'), move_to(context_t(1), -7, std::chrono::seconds(8)));
    scene.emplace_back(sprite_t('@'), move_to(context_t(2), 2, std::chrono::seconds(3)));
    scene.emplace_back(sprite_t('$'), move_to(context_t(3), -2, std::chrono::seconds(3)));
    scene.emplace_back(sprite_t('#'), 4);
    scene.emplace_back(sprite_t('%'), move_to(context_t(5), -4, std::chrono::seconds(1)));
    scene.emplace_back(mini_scene, move_to(context_t(0), 5, std::chrono::seconds(10)));
    
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
//        draw(batch_scene, render_batch, {0});
//        
//        // ...and adding to the main scene
//        scene.emplace_back(std::move(render_batch), 0);
//    }
}

int main()
{
    init();
    
    context_t context = move_to(context_t{0}, 10, std::chrono::seconds(20));
    animation_time_t current_time;
    
    // render loop
    render_stream_t cout_render(std::cout.rdbuf());
    while (true) {
        current_time = std::chrono::high_resolution_clock::now();

        animate(context, current_time);
        animate(scene, current_time);

        draw(scene, cout_render, context);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    return 0;
}