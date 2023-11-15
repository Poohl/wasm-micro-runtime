
set (PLATFORM_SHARED_DIR ${CMAKE_CURRENT_LIST_DIR})

add_definitions(-DBH_PLATFORM_RODOS)
add_definitions(-DBH_PLATFORM_RODOS_DIR)

include_directories(${PLATFORM_SHARED_DIR})
include_directories(${PLATFORM_SHARED_DIR}/../include)
include_directories(/home/paul/projects/master/rodos/api)

file (GLOB_RECURSE source_all ${PLATFORM_SHARED_DIR}/*.cpp)

set (PLATFORM_SHARED_SOURCE ${source_all} ${PLATFORM_COMMON_MATH_SOURCE})
