cmake_minimum_required(VERSION 3.10)
project(crow_dashboard)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

include(FetchContent)

# ✅ 1. Fetch Asio manually (header-only)
FetchContent_Declare(
  asio
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
  GIT_TAG master
)
FetchContent_MakeAvailable(asio)

# ✅ 2. Disable Crow’s own find_package(asio)
set(CMAKE_DISABLE_FIND_PACKAGE_asio TRUE)
add_definitions(-DASIO_STANDALONE)

# ✅ 3. Fetch Crow
FetchContent_Declare(
  crow
  GIT_REPOSITORY https://github.com/CrowCpp/crow.git
  GIT_TAG master
)
FetchContent_MakeAvailable(crow)

# ✅ 4. Define Asio include path manually
set(ASIO_INCLUDE_DIR "${asio_SOURCE_DIR}/asio/include")

# ✅ 5. Build dashboard app
add_executable(crow_dashboard src/main.cpp)

target_include_directories(crow_dashboard PRIVATE
  ${crow_SOURCE_DIR}/include
  ${ASIO_INCLUDE_DIR}
)

find_package(Threads REQUIRED)
target_link_libraries(crow_dashboard PRIVATE Threads::Threads)

