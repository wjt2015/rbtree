aux_source_directory(. rb_src)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
add_library(rb_tree SHARED ${rb_src})
