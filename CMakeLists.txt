cmake_minimum_required(VERSION 3.10)
project(crow_dashboard)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  crow
  GIT_REPOSITORY https://github.com/CrowCpp/crow.git
  GIT_TAG 0.3
)
FetchContent_MakeAvailable(crow)

add_executable(crow_dashboard src/main.cpp)
target_include_directories(crow_dashboard PRIVATE ${crow_SOURCE_DIR}/include)
find_package(Threads REQUIRED)
target_link_libraries(crow_dashboard PRIVATE Threads::Threads)

