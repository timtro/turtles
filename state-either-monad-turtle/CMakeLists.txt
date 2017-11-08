
add_executable(state-either-monad-turtle state-either-monad-turtle.cpp turtle.cpp)
target_link_libraries(state-either-monad-turtle CATCH)

add_test(NAME state-either-monad-turtle COMMAND state-either-monad-turtle)