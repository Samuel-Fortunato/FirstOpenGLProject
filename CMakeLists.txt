cmake_minimum_required(VERSION 3.10.2)

project(opengl_test)

add_executable(${PROJECT_NAME} src/main.cpp src/stb_img.cpp src/glad.c)
target_include_directories(${PROJECT_NAME} PUBLIC src/include)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	target_link_libraries(${PROJECT_NAME} glfw3 GL X11 pthread Xrandr Xi dl)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	target_link_libraries(${PROJECT_NAME} glfw3.lib opengl32.lib)
endif()

#target_link_libraries(${PROJECT_NAME} glfw3 GL X11 pthread Xrandr Xi dl)
