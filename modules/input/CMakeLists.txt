include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
CREATE_MODULE(shiva::input "${MODULE_SOURCES}" ${MODULE_PATH})
target_link_libraries(input INTERFACE shiva::enums)
AUTO_TARGETS_MODULE_INSTALL(input)
