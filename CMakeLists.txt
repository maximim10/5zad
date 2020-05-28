project(Rtracing)

set(Rtr_SRC main.cpp)
set(Rtr_HDR tetr.hpp screen.hpp functions.hpp)
add_executable(${PROJECT_NAME} ${Rtr_SRC} ${Rtr_HDR})