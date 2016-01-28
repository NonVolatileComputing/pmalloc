enable_testing()
find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CHECK_LIBRARIES} pmalloc $<$<BOOL:${LIBRT_LIBRARIES}>:${LIBRT_LIBRARIES}>)
include_directories(. ../src)

add_executable(check_pmsimulate check_pmsimulate.c check_common.c)
target_link_libraries(check_pmsimulate ${LIBS})
add_test(check_pmsimulate ${CMAKE_CURRENT_BINARY_DIR}/check_pmsimulate)

add_executable(check_pmrecycle check_pmrecycle.c check_common.c)
target_link_libraries(check_pmrecycle ${LIBS})
add_test(check_pmrecycle ${CMAKE_CURRENT_BINARY_DIR}/check_pmrecycle)

add_executable(check_pmclear check_pmclear.c check_common.c)
target_link_libraries(check_pmclear ${LIBS})
add_test(check_pmclear ${CMAKE_CURRENT_BINARY_DIR}/check_pmclear)

add_executable(check_pmalloc check_pmalloc.c check_common.c)
target_link_libraries(check_pmalloc ${LIBS})
add_test(check_pmalloc ${CMAKE_CURRENT_BINARY_DIR}/check_pmalloc)

