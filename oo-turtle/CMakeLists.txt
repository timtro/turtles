get_filename_component(target ${CMAKE_CURRENT_LIST_DIR} NAME)

add_executable(${target} ${target}.cpp OOTurtle.cpp)
target_link_libraries(${target} CATCH)

add_test(NAME ${target} COMMAND ${target})