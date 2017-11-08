
add_executable(writer-either-monad-turtle writer-either-monad-turtle.cpp turtle.cpp)
target_link_libraries(writer-either-monad-turtle CATCH)

add_test(NAME writer-either-monad-turtle COMMAND writer-either-monad-turtle)