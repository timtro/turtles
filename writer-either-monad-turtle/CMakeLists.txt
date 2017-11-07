
add_executable(writer-either-monad-turtle writer-either-monad-turtle.cpp turtle.cpp)
target_link_libraries(writer-either-monad-turtle CATCH Pose)

add_test(NAME writer-either-monad-turtle COMMAND writer-either-monad-turtle)