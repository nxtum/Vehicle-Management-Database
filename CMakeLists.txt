cmake_minimum_required(VERSION 3.2)
project(Management_System)

set(CMAKE_CXX_STANDARD 17)

# Find SQLite3 package
find_package(SQLite3 REQUIRED)

# Include directories
include_directories(include)

# Add executable
add_executable(Management_System
        src/main.cpp
        src/Vehicle.cpp
        src/Car.cpp
        src/Dealership.cpp
        src/Human.cpp
        src/AuthenticationManager.cpp
        src/Employee.cpp
        src/Admin.cpp
        src/Customer.cpp
        src/Motorbike.cpp
        src/DatabaseHandler.cpp
        src/UtilityFunctions.cpp)

# Link against SQLite3 library
target_link_libraries(Management_System SQLite::SQLite3)
