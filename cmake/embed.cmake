# Generates a C++ source file holding the contents of all files that
# `cpplings init` writes out. Run with -DSOURCE_DIR=... -DOUTPUT=...

file(GLOB_RECURSE files RELATIVE ${SOURCE_DIR}
  ${SOURCE_DIR}/exercises/*
  ${SOURCE_DIR}/solutions/*
  ${SOURCE_DIR}/include/*)
list(APPEND files info.toml)
list(SORT files)

set(delimiter "cpplings")
set(out "#include \"embedded.hpp\"\n\nconst EmbeddedFile embedded_files[] = {\n")
foreach(file IN LISTS files)
  file(READ ${SOURCE_DIR}/${file} content)
  string(FIND "${content}" ")${delimiter}\"" collision)
  if(NOT collision EQUAL -1)
    message(FATAL_ERROR "${file} contains the raw string delimiter `)${delimiter}\"`")
  endif()
  string(APPEND out "    {\"${file}\", R\"${delimiter}(${content})${delimiter}\"},\n")
endforeach()
string(APPEND out "};\n\nconst std::size_t embedded_files_count = std::size(embedded_files);\n")

file(WRITE ${OUTPUT}.tmp "${out}")
file(COPY_FILE ${OUTPUT}.tmp ${OUTPUT} ONLY_IF_DIFFERENT)
file(REMOVE ${OUTPUT}.tmp)
