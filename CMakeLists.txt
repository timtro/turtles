cmake_minimum_required (VERSION 2.9)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER /usr/bin/clang-8)
set(CMAKE_CXX_COMPILER /usr/bin/clang++-8)
# set(CMAKE_C_COMPILER /usr/bin/gcc-7)
# set(CMAKE_CXX_COMPILER /usr/bin/g++-7)
# set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

project(turtles)
set(CMAKE_BUILD_TYPE Debug)
enable_testing()

set(c++std "-std=c++17")
# set(c++std "-std=c++17 -stdlib=libc++")
set(linker-flags "-lc++abi")
# set(c++std "-std=c++17 -stdlib=libstdc++")
set(common "-fno-omit-frame-pointer -fno-rtti")
set(warnings "-Wall -Wextra -pedantic") # -Werror
set(optimizations_debug "-O2")
set(optimizations_release "-O3 -ffast-math")
set(debug "-g -pg")
set(perf_bench "-fno-omit-frame-pointer")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${c++std} ${common} ${debug} ${warnings} ${optimizations_debug}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${c++std} ${common} ${warnings} ${optimizations_release}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${linker-flags}")

message("Compiler is " ${CMAKE_CXX_COMPILER_ID})
message("Build type is " ${CMAKE_BUILD_TYPE})

# for clang++ use -fuse-ld=gold to avoid LD error "File format not recognized"
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "[cC][lL][aA][nN][gG]")
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    # message("USING CLANG SANITIZERS")
    # set(sanitizer "-fsanitize=address")
    # set(sanitizer "-fsanitize=memory")
    # set(sanitizer "-fsanitize=memory -fsanitize-memory-track-origins")
    # set(sanitizer "-fsanitize=thread")
    # set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${sanitizer}")
    # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=gold")
  endif()
endif()


# set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/" $CMAKE_MODULE_PATH)
# find_package(SFML 2 REQUIRED COMPONENTS graphics window system)
# target_link_libraries(circle ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
find_package(units)

add_subdirectory(lib)
add_subdirectory(oo-turtle)
add_subdirectory(pipes-turtle)
add_subdirectory(optional-monad-turtle)
add_subdirectory(either-monad-turtle)
add_subdirectory(writer-monad-turtle)
add_subdirectory(writer-either-monad-turtle)
add_subdirectory(state-monad-turtle)
add_subdirectory(state-either-monad-turtle)
add_subdirectory(command-turtle)
add_subdirectory(command-writer-either-turtle)
add_subdirectory(writer-class-turtle)

IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
  EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
  )
ENDIF()
