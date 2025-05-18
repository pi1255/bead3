cmake_minimum_required( VERSION 3.13 )

project( poker )
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
#set(CMAKE_EXE_LINKER_FLAGS "-static")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")



find_package( SDL2 REQUIRED )


link_libraries (
  SDL2
  SDL2_ttf
)

add_library( graphics graphics.cpp )
# //include_directories(SYSTEM )
#add_subdirectory(widgets/)
#add_library(widgets widgets/widgets.cpp widgets/numberwidget.cpp widgets/dropdownwidget.cpp)


add_library(APP app.cpp Widgets/widget.cpp Widgets/button.cpp Widgets/card.cpp Widgets/numericin.cpp)
link_libraries(APP graphics)

add_executable(bead3 main.cpp) 

target_link_libraries(bead3 graphics )
target_link_libraries(bead3 APP)
