cmake_minimum_required( VERSION 3.13 )

project( poker )
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")



find_package( SDL2 REQUIRED )


link_libraries (
  SDL2
  SDL2_ttf
)

add_library( graphics graphics.cpp )


add_library(APP app.cpp Widgets/widget.cpp Widgets/button.cpp Widgets/card.cpp Widgets/numericin.cpp Widgets/statictext.cpp)
link_libraries(APP graphics)

add_executable(bead3 main.cpp) 

target_link_libraries(bead3 graphics )
target_link_libraries(bead3 APP)
