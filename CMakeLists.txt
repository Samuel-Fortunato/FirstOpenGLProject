cmake_minimum_required(VERSION 3.10.2)

project(opengl_test)

add_executable(${PROJECT_NAME} src/main.cpp deps/stb_img.cpp deps/glad.c)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
add_subdirectory(./deps/glfw/)

set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "If the test suite for Assimp is built in addition to the library.")
set(ASSIMP_INSTALL OFF CACHE BOOL "Disable this if you want to use assimp as a submodule.")
add_subdirectory(./deps/assimp/)

target_include_directories(${PROJECT_NAME} PUBLIC
	./src/include/
	./deps/include/
	./deps/assimp/include/
	./build/deps/assimp/include/
)

target_link_directories(${PROJECT_NAME} PUBLIC
	./glfw/src/
	./assimp/bin/
)

# libraries for windows or linux
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")		# linux
	target_link_libraries(${PROJECT_NAME} glfw GL X11 pthread Xrandr Xi dl)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")		# windows
	target_link_libraries(${PROJECT_NAME} glfw.lib opengl32.lib)
endif()
