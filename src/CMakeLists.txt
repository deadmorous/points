cmake_minimum_required (VERSION 3.0.0)
project (points)
include (../cmake/qt5_executable.cmake)
target_link_libraries(${PROJECT_NAME}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Core_LIBRARIES}
)
