include_directories(./hdr) 

set(PREF_SRC "src")
set(PREF_HDR "hdr")
set(NAME_EXE "cpu")

FILE(GLOB SRC ${PREF_SRC}/*.cpp)
FILE(GLOB HDR ${PREF_HDR}/*.h)

find_package(SDL2 REQUIRED)

add_executable(${NAME_EXE} ${SRC} ${HDR})

target_link_libraries(${NAME_EXE} SDL2::SDL2 SDL2::SDL2main)