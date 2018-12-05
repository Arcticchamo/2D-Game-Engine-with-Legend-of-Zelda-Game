cmake_minimum_required(VERSION 2.6)
project(LoZ)

include_directories(
  contrib
)

if(MSVC)
  include_directories(
    contrib/msvc-windows-x86/glew/include
    contrib/msvc-windows-x86/SDL2/include
  )

  link_directories(
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/lib
  )
endif()

if(MSVC)
  add_definitions(-DSDL_MAIN_HANDLED)
endif()

add_executable(LoZ

src/engine/Camera.h
src/engine/Component.h
src/engine/EngineCore.h
src/engine/GameObject.h
src/engine/MeshRenderer.h
src/engine/Object.h
src/engine/Player.h
src/engine/Resources.h
src/engine/Texture.h
src/engine/Transform.h
src/engine/VertexArray.h
src/engine/VertexBuffer.h

src/engine/Camera.cpp
src/engine/EngineCore.cpp
src/engine/main.cpp
src/engine/MeshRenderer.cpp
src/engine/Player.cpp
src/engine/Resources.cpp
src/engine/Texture.cpp
src/engine/Transform.cpp
src/engine/VertexArray.cpp
src/engine/VertexBuffer.cpp 

contrib/stb_image/stb_image.cpp
)

add_executable(MapGenerator

src/mapgenerator/main.cpp
src/mapgenerator/GenerateTileMap.cpp

src/mapgenerator/GenerateTileMap.h

contrib/stb_image/stb_image.cpp
contrib/miniz/miniz_zip.c
contrib/miniz/miniz.c
contrib/miniz/miniz_tinfl.c
contrib/miniz/miniz_tdef.c
)

if(MSVC)
  target_link_libraries(LoZ
    SDL2 glew32 opengl32
  )
else()
  target_link_libraries(LoZ
    SDL2 GLU GLEW GL
  )
endif()

if(MSVC)
  add_custom_command(TARGET LoZ POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/bin/SDL2.dll"
      "$<TARGET_FILE_DIR:LoZ>"
  )

  add_custom_command(TARGET LoZ POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/bin/glew32.dll"
      "$<TARGET_FILE_DIR:LoZ>"
  )
endif()
