
add_executable(either-monad-turtle either-monad-turtle.cpp turtle.cpp)
target_link_libraries(either-monad-turtle CATCH)

add_test(NAME either-monad-turtle COMMAND either-monad-turtle)