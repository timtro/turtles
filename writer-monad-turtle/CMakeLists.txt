
add_executable(writer-monad-turtle writer-monad-turtle.cpp turtle.cpp)
target_link_libraries(writer-monad-turtle CATCH)

add_test(NAME writer-monad-turtle COMMAND writer-monad-turtle)