//
// Created by roman Sztergbaum on 18/06/2018.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <shiva/ecs/system.hpp>
#include <shiva/sfml/event/set_render_window.hpp>

namespace shiva::plugins
{
    class input_system : public shiva::ecs::pre_update_system<input_system>
    {
    public:
        void receive(const shiva::sfml::event::set_render_window &evt)
        {
            win_ = evt.win;
        }

        ~input_system() noexcept override = default;

        input_system(shiva::entt::dispatcher &dispatcher, shiva::entt::entity_registry &registry,
                     const float &fixed_delta_time) noexcept :
            system(dispatcher, registry, fixed_delta_time)
        {
            dispatcher_.sink<shiva::sfml::event::set_render_window>().connect(this);
        }

        static std::unique_ptr<shiva::ecs::base_system> system_creator(entt::dispatcher &dispatcher,
                                                                       entt::entity_registry &registry,
                                                                       const float &fixed_delta_time) noexcept;
        void update() noexcept final;

    public:
        reflect_class(input_system)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap(reflect_function(&input_system::update));
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap();
        }

    private:
        sf::RenderWindow *win_{nullptr};
    };
}