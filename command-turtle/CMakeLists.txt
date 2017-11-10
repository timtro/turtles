add_executable(command-turtle command-turtle.cpp turtle.cpp)
target_link_libraries(command-turtle CATCH)

add_test(NAME command-turtle COMMAND command-turtle)