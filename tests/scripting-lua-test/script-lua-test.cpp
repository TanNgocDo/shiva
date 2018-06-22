//
// Created by roman Sztergbaum on 21/06/2018.
//

#include <gtest/gtest.h>
#include <shiva/world/world.hpp>
#include <shiva/lua/lua_system.hpp>
#include <shiva/ecs/components/all.hpp>
#include <systems/all_systems.hpp>

class fixture_world : public ::shiva::world, public ::testing::Test
{
public:
    using systems_list = shiva::meta::type_list<shiva::scripting::lua_system,
        shiva::examples::post_system,
        shiva::examples::pre_system>;
protected:
    void SetUp() override
    {
        shiva::fs::copy(
            shiva::fs::current_path().parent_path() / shiva::fs::path("tests/scripting-lua-test/scripts_lua_tests"),
            shiva::fs::current_path() / shiva::fs::path("scripts_lua_tests"),
            shiva::fs::copy_options::overwrite_existing | shiva::fs::copy_options::recursive);
        system_ptr = std::addressof(system_manager_.create_system<shiva::scripting::lua_system>("scripts_lua_tests"));
        system_ptr->register_entity_registry();
        system_ptr->register_components(shiva::ecs::common_components{});
        system_ptr->register_types_list(fixture_world::systems_list{});
        system_ptr->register_world();
        system_ptr->load_script("basic_tests.lua");
        system_ptr->update();
    }

    void TearDown() override
    {
        spdlog::drop_all();
    }

protected:
    shiva::scripting::lua_system *system_ptr{nullptr};
};

TEST_F(fixture_world, create_entity)
{
    sol::state &state = system_ptr->get_state();
    shiva::entt::entity_registry::entity_type id = state["test_create_entity"]();
    ASSERT_EQ(id, 0);
}

TEST_F(fixture_world, destroy_entity)
{
    sol::state &state = system_ptr->get_state();
    bool res = state["test_destroy_entity"]();
    ASSERT_TRUE(res);
}

TEST_F(fixture_world, components)
{
    sol::state &state = system_ptr->get_state();
    bool res = state["test_component"]();
    ASSERT_TRUE(res);
}