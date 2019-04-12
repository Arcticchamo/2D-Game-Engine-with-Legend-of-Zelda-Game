cmake_minimum_required(VERSION 2.6)
project(Game)

include_directories(
  contrib
  src
)

#if(MSVC)
  include_directories(
    contrib/msvc-windows-x86/glew/include
    contrib/msvc-windows-x86/SDL2/include
	)

  link_directories(
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/lib
  )
#endif()

if(MSVC)
  add_definitions(-DSDL_MAIN_HANDLED -D_CRT_SECURE_NO_WARNINGS)
endif()

add_library(Miniz
contrib/stb_image/stb_image.cpp
contrib/miniz/miniz.c
contrib/miniz/miniz_tinfl.c
contrib/miniz/miniz_tdef.c
contrib/miniz/miniz_zip.c
)

add_library(Engine

src/engine/BackGroundMap.h
src/engine/Camera.h
src/engine/Component.h
src/engine/CompressedMapLoader.h
src/engine/CompressedSpriteLoader.h
src/engine/engine.h
src/engine/EngineCore.h
src/engine/GameObject.h
src/engine/MapChunks.h
src/engine/Material.h
src/engine/Mesh.h
src/engine/MeshRenderer.h
src/engine/Object.h
src/engine/Resource.h
src/engine/Resources.h
src/engine/Screen.h
src/engine/Shader.h
src/engine/Texture.h
src/engine/Transform.h
src/engine/VertexArray.h
src/engine/VertexBuffer.h

src/engine/BackGroundMap.cpp
src/engine/Camera.cpp
src/engine/Component.cpp
src/engine/CompressedMapLoader.cpp
src/engine/CompressedSpriteLoader.cpp
src/engine/EngineCore.cpp
src/engine/GameObject.cpp
src/engine/MapChunks.cpp
src/engine/Material.cpp
src/engine/Mesh.cpp
src/engine/MeshRenderer.cpp
src/engine/Screen.cpp
src/engine/Shader.cpp
src/engine/Texture.cpp
src/engine/Transform.cpp
src/engine/VertexArray.cpp
src/engine/VertexBuffer.cpp
)

target_link_libraries(Engine 
Miniz
)

add_executable(Game
src/game/Player.h

src/game/main.cpp
src/game/Player.cpp
)

if(MSVC)
  target_link_libraries(Game
    SDL2 glew32 opengl32 Engine
  )
else()
  target_link_libraries(Game
    SDL2 GLU GLEW GL Engine
  )
endif()

add_executable(MapCompressor

src/mapCompressor/main.cpp
src/mapCompressor/GenerateTileMap.cpp
src/mapCompressor/GenerateTileMap.h

)
target_link_libraries(MapCompressor
Miniz
)

if(MSVC)
  add_custom_command(TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/bin/SDL2.dll"
      "$<TARGET_FILE_DIR:Game>"
  )

  add_custom_command(TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/bin/glew32.dll"
      "$<TARGET_FILE_DIR:Game>"
  )
endif()
