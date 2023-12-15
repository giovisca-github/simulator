
add_executable(Test_dynamic Test_dynamic.cpp)
target_link_libraries(Test_dynamic ${PROJECT_NAME})

add_executable(Test_kinematic Test_kinematic.cpp)
target_link_libraries(Test_kinematic ${PROJECT_NAME})

add_executable(Test_jsonSerialization Test_serialization.cpp)
target_link_libraries(Test_jsonSerialization ${PROJECT_NAME})

add_executable(prove proveVarie.cpp)
target_link_libraries(prove ${OpenCV_LIBS})