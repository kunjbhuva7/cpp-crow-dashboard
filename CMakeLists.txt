cmake_minimum_required(VERSION 3.10)
project(crow_dashboard)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

include(FetchContent)

# ✅ 1. Fetch ASIO first (Crow needs it)
FetchContent_Declare(
  asio
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
  GIT_TAG master
)
FetchContent_MakeAvailable(asio)

# ✅ 2. Fetch Crow (use master, not tag 0.3)
FetchContent_Declare(
  crow
  GIT_REPOSITORY https://github.com/CrowCpp/crow.git
  GIT_TAG master
)
FetchContent_MakeAvailable(crow)

# ✅ 3. Build the app
add_executable(crow_dashboard src/main.cpp)

# Include both Crow + Asio headers
target_include_directories(crow_dashboard PRIVATE
  ${crow_SOURCE_DIR}/include
  ${asio_SOURCE_DIR}/asio/include
)

# ✅ 4. Link threads
find_package(Threads REQUIRED)
target_link_libraries(crow_dashboard PRIVATE Threads::Threads)

