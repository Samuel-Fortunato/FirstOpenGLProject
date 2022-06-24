cmake_minimum_required(VERSION 3.10.2)

project(opengl_test)

add_executable(${PROJECT_NAME} src/main.cpp deps/stb_img.cpp deps/glad.c)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)

add_subdirectory(./deps/glfw/)

target_include_directories(${PROJECT_NAME} PUBLIC
	./src/include/
	./deps/include/
	./deps/glfw/include/
)

target_link_directories(${PROJECT_NAME} PUBLIC
	./glfw/src/
)

# libraries for windows or linux
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")		# linux
	target_link_libraries(${PROJECT_NAME} glfw GL X11 pthread Xrandr Xi dl)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")		# windows
	target_link_libraries(${PROJECT_NAME} glfw.lib opengl32.lib)
endif()
