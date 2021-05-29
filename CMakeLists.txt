cmake_minimum_required(VERSION 3.17)
project(CarrierFromTheVoid)

set(CMAKE_CXX_STANDARD 20)

add_executable(CarrierFromTheVoid main.cpp Bullet.cpp Bullet.h Unit.cpp Unit.h Effect.cpp Effect.h Background.cpp Background.h Animation.cpp Animation.h Menu.cpp Menu.h MainMenu.cpp MainMenu.h Particle.cpp Particle.h DeathMenu.cpp DeathMenu.h)

set(SFML_ROOT c:/SFML) # SFML directory
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules") # FindSFML.cmake directory
find_package(SFML REQUIRED system window graphics network audio) # packages to include
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    include_directories(c:/SFML/include)
endif()
# Copy dlls to build
if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()