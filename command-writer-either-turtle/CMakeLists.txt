add_executable(command-writer-either-turtle command-writer-either-turtle.cpp turtle.cpp)
target_link_libraries(command-writer-either-turtle CATCH)

add_test(NAME command-writer-either-turtle COMMAND command-writer-either-turtle)