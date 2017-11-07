
add_executable(oo-turtle oo-turtle.cpp OOTurtle.cpp)
target_link_libraries(oo-turtle CATCH Pose)

add_test(NAME oo-turtle COMMAND oo-turtle)