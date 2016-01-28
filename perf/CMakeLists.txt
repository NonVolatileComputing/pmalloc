
add_executable(struct_objs_write struct_objs_write.c common.c)
add_executable(struct_objs_read struct_objs_read.c common.c)

target_link_libraries (struct_objs_write LINK_PUBLIC pmalloc
                         $<$<BOOL:${LIBRT_LIBRARIES}>:${LIBRT_LIBRARIES}>)
target_link_libraries (struct_objs_read LINK_PUBLIC pmalloc
                         $<$<BOOL:${LIBRT_LIBRARIES}>:${LIBRT_LIBRARIES}>)

