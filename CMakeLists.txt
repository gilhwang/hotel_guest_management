cmake_minimum_required(VERSION 3.0.0)
project(hotelbooking VERSION 0.1.0)

include(CTest)
enable_testing()

# Find package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0 gtkmm-3.0)

include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS})
add_definitions(${GTK_CFLAGS_OTHER})

# Source files
set(MAIN_SRC src/main/main.cpp)
set(CLASS_SRC src/class/MainWindow.cpp
              src/class/LoginWindow.cpp
              src/class/AddWindow.cpp
              src/class/GuestStack.cpp
              src/class/GuestTreeView.cpp
              src/class/DateEntry.cpp
              src/class/Date.cpp
              src/class/Customer.cpp
              src/class/CustomerInfo.cpp)
set(HELPER_SRC src/helper/helper.cpp
               src/helper/globals.cpp
               src/helper/graphics.cpp
               src/helper/events.cpp)

# Create executable
add_executable(hotelbooking ${MAIN_SRC} ${HELPER_SRC} ${CLASS_SRC})

# Include path
target_include_directories(hotelbooking PUBLIC includes includes/class)

# Link libraries
target_link_libraries(hotelbooking ${GTK_LIBRARIES})



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)