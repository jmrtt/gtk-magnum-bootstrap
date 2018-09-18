cmake_minimum_required(VERSION 3.10)

project(GtkMagnum)

# ================
# Compiler options
# ================
set(CMAKE_CXX_STANDARD 17) # Use C++17
set(CMAKE_CXX_EXTENSIONS OFF) # Use -std=c++17 instead of -std=gnu++17
add_compile_options(-Wall -Wextra -Wpedantic)
add_compile_options(-Wfatal-errors -Werror) # Stop at first error


# =====================
# External dependencies
# =====================
# Use the package PkgConfig to detect GTK+ headers/library files (gtkmm: C++ bindings)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
include_directories(SYSTEM ${GTKMM_INCLUDE_DIRS})

# Magnum v2018.04
find_package(Magnum REQUIRED GL GlxContext Shaders)


# =====================
# Application
# =====================
add_executable(GtkMagnum main.cpp ApplicationWindow.h ApplicationWindow.cpp GtkMagnum.h GtkMagnum.cpp)
target_include_directories(GtkMagnum PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(GtkMagnum ${GTKMM_LIBRARIES} ${MAGNUM_LIBRARIES} ${MAGNUM_GLXCONTEXT_LIBRARIES} ${MAGNUM_SHADERS_LIBRARIES})

