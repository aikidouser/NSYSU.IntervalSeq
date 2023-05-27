project(${LIBRARY_NAME})

add_library(${LIBRARY_NAME} SHARED
  interval.cpp
  full.cpp
  sub.cpp
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  ${INC_DIR}
)
