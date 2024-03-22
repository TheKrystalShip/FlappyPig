cmake_minimum_required(VERSION 3.28)
project(FlappyPig VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall")

# Specify output directories for different types of compile targets
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)



include(CTest)
enable_testing()

add_executable(FlappyPig src/main.cpp
                         src/AudioManager.cpp
                         src/Cloud.cpp
                         src/GameDirector.cpp
                         src/Hud.cpp
                         src/Pipe.cpp
                         src/Player.cpp
                         src/TextureManager.cpp
)
target_include_directories(FlappyPig PRIVATE ${CMAKE_SOURCE_DIR}/include /usr/local/include /usr/local/include/TKS)
target_link_libraries(FlappyPig PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)

file(COPY ${CMAKE_SOURCE_DIR}/src/assets DESTINATION ${CMAKE_SOURCE_DIR}/bin)

if(WIN32)
    add_custom_command(
        TARGET FlappyPig
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
        VERBATIM)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
