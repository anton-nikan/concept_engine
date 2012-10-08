//
//  main.cpp
//  concept_engine
//
//  Created by Anton Nikolaienko on 9/29/12.
//  Copyright (c) 2012 Anton Nikolaienko. All rights reserved.
//


#include <sstream>
#include <thread>
#include "sprite.hpp"
#include "scene.hpp"
#include "manip.hpp"


// === These are engine-dependent specializations ===

using transformation_t = double;
using render_stream_t = std::ostream;
using animation_time_t = std::chrono::time_point<std::chrono::high_resolution_clock>;

using render_context_t = context_t<transformation_t>;
using scene_object_t = object_t<render_stream_t, render_context_t, animation_time_t>;
using scene = scene_t<scene_object_t>;
template<size_t SZ>
using static_scene = static_scene_t<SZ, scene_object_t>;


// === Client code goes below ===


// learning to draw batches
void draw(const std::ostringstream& in, render_stream_t& out, render_context_t ctxt)
{ out << ctxt << in.str() << std::endl; }

scene main_scene;

void init()
{
    // static scene initialization
    static_scene<3> static_scn =
    {
        sprite_t('#'),
        sprite_t('#'),
        sprite_t('#')
    };
    main_scene.emplace_back(static_scn);
    
    // just adding stuff
    main_scene.emplace_back(sprite_t('*'), 1);
    main_scene.emplace_back(sprite_t('@'), 2);
    main_scene.emplace_back(sprite_t('$'), 3);
    main_scene.emplace_back(sprite_t('#'), 4);
    main_scene.emplace_back(sprite_t('%'), 5);

    // sub-scenes support
    scene mini_scene;
    mini_scene.emplace_back(sprite_t('^'));
    mini_scene.emplace_back(sprite_t('^'), 2);
    main_scene.emplace_back(std::move(mini_scene));
    
    // synchronous loading:
    sprite_t loaded_sprite = load<sprite_t>("hello.txt").get();
    main_scene.emplace_back(loaded_sprite, 15);
    
    // (possibly) async loading:
    auto f_sprite1 = load<sprite_t>("1.txt");
    auto f_sprite2 = load<sprite_t>("2.txt");
    auto f_sprite3 = load<sprite_t>("3.txt");
    auto f_sprite4 = load<sprite_t>("4.txt");
    main_scene.emplace_back(f_sprite1.get(), 20);
    main_scene.emplace_back(f_sprite2.get(), 20);
    main_scene.emplace_back(f_sprite3.get(), 20);
    main_scene.emplace_back(f_sprite4.get(), 20);
    
    // pre-baking scene
//    // NOTE: does not work because ostringstream can't be copied, only moved. Need move support in object_t.
//    {
//        scene batch_scene;
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

    // applying some animations
    move_to(main_scene[0], 1.0, std::chrono::seconds(10));
    move_to(main_scene[1], 7.0, std::chrono::seconds(1));
    move_to(main_scene[2], 3.0, std::chrono::seconds(3));
    move_to(main_scene[3], 4.0, std::chrono::seconds(9));
    move_to(main_scene[4], 6.0, std::chrono::seconds(4));
    move_to(main_scene[5], 30.0, std::chrono::seconds(4));
    move_to(main_scene[6], 20.0, std::chrono::seconds(1)).then([]{ move_to(main_scene[6], 0.0); });
    
    render_context_t cntxt{};
    render_stream_t cout_render(std::cout.rdbuf());
    animation_time_t current_time{};

    // render loop
    while (true) {
        current_time = animation_time_t::clock::now();

        animate(main_scene, current_time);
        draw(main_scene, cout_render, cntxt);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    return 0;
}
