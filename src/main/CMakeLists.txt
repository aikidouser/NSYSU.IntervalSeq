project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
  main.cpp 
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)
target_link_libraries(${PROJECT_NAME} ${LIBRARY_NAME})

