cmake_minimum_required(VERSION 3.10)
project(TaskScheduler)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Collect source files
file(GLOB_RECURSE SOURCES
    "main.cpp"
    "src/Logger.cpp"
    "src/Scheduler.cpp"
    "src/Task.cpp"
    "sc/Timer.cpp"
)

# Define the executable
add_executable(Scheduler ${SOURCES})

# Include header directory
target_include_directories(Scheduler PRIVATE include)
