set(LIB_OUTPUT_NAME pmalloc)

aux_source_directory(. DIR_LIB_SRCS)

add_library(${LIB_OUTPUT_NAME} SHARED ${DIR_LIB_SRCS})
set_target_properties(${LIB_OUTPUT_NAME} PROPERTIES VERSION 1.8.0 SOVERSION 1)
target_include_directories(${LIB_OUTPUT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


install(TARGETS ${LIB_OUTPUT_NAME} LIBRARY DESTINATION lib)
install(FILES pmalloc.h DESTINATION include)
