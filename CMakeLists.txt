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
  src/main.cpp
  src/VertexBuffer.h
  src/VertexBuffer.cpp
  src/VertexArray.h
  src/VertexArray.cpp
  src/ShaderProgram.h
  src/ShaderProgram.cpp
  src/Camera.h
  src/Camera.cpp
  src/Player.h
  src/Player.cpp
  src/Component.h
  src/Component.cpp
  src/EngineCore.h
  src/EngineCore.cpp
  src/GameObject.h
  src/GameObject.cpp
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
