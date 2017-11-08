
add_executable(state-monad-turtle state-monad-turtle.cpp turtle.cpp)
target_link_libraries(state-monad-turtle CATCH)

add_test(NAME state-monad-turtle COMMAND state-monad-turtle)