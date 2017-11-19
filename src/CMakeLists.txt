# Source Files
set(
	2DOOM_SRCS 
	Component.cpp
	Entity.cpp
	Graphics.cpp
	Renderer.cpp
	Scene.cpp
	Sprite.cpp
	Main.cpp
	Engine.cpp
	Input.cpp
	Shader.cpp
	Material.cpp
	Transform.cpp
	SpriteRenderer.cpp
	Mesh.cpp
	Utilities.cpp
	Camera.cpp
	ThreadPool.cpp
	Snek.cpp
	glad.c
)
	
# Header files
set(
	2DOOM_HDRS
	Component.hpp
	Entity.hpp
	Graphics.hpp
	Renderer.hpp
	Scene.hpp
	Sprite.hpp
	Engine.hpp
	Input.hpp
	Shader.hpp
	Material.hpp
	Transform.hpp
	SpriteRenderer.hpp
	Mesh.hpp
	Utilities.hpp
	Camera.hpp
	ThreadPool.hpp
	Snek.hpp
)

# Executable
add_executable (Snek ${2DOOM_SRCS} ${2DOOM_HDRS})

# Includes
include_directories(${CMAKE_SOURCE_DIR}/dependencies)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/src)

# Libraries
target_link_libraries(Snek ${SDL2_LIBRARY} ${OPENGL_LIBRARY})