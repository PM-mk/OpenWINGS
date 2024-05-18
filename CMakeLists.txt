cmake_minimum_required(VERSION 3.29.0)
project(OpenWINGS VERSION 1.1.0 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
configure_file(config.hpp.in ../include/config.hpp)

# set up wxWidgets package
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets REQUIRED gl core base xml OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})

# set normalized paths to other libraries (helps with path delimiter issues)
cmake_path(SET EIGEN_ROOT NORMALIZE $ENV{LIB}/eigen-3.4.0)
cmake_path(SET WXMATHPLOT_ROOT NORMALIZE $ENV{LIB}/wxMathPlot_0.2.0/mathplot)

# set up Eigen3 package
list(APPEND CMAKE_PREFIX_PATH ${EIGEN_ROOT})
find_package(Eigen3 REQUIRED NO_MODULE)

add_executable(${PROJECT_NAME} WIN32)
add_subdirectory(src)

target_include_directories(${PROJECT_NAME} PUBLIC
    include
    $ENV{WXWIN}/include
    ${WXMATHPLOT_ROOT}
)
target_link_libraries(${PROJECT_NAME}
    ${wxWidgets_LIBRARIES}
    Eigen3::Eigen
    ${WXMATHPLOT_ROOT}/lib/libmathplot.dll
)