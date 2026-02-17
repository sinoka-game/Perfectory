cmake_minimum_required(VERSION 3.10)
project(Perfectory CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(include ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

# 라이브러리 링크
target_link_libraries(${PROJECT_NAME} 
    ${SDL2_LIBRARIES} 
    SDL2_image  # 직접 이름 지정
)
