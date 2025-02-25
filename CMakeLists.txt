add_library(UARTProtocolLinux STATIC src/UARTProtocol.cpp)
target_include_directories(my_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
