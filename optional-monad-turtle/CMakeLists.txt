
add_executable(optional-monad-turtle optional-monad-turtle.cpp turtle.cpp)
target_link_libraries(optional-monad-turtle CATCH)

add_test(NAME optional-monad-turtle COMMAND optional-monad-turtle)