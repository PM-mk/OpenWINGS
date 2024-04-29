cmake_minimum_required(VERSION 3.29.0)
project(OpenWINGS VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})

list(APPEND CMAKE_PREFIX_PATH $ENV:{LIB}/eigen-3.4.0)
find_package(Eigen3 REQUIRED NO_MODULE)

add_executable(${PROJECT_NAME} WIN32)
add_subdirectory(src)
target_include_directories(${PROJECT_NAME} PUBLIC include $ENV{WXWIN}/include)
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} Eigen3::Eigen)