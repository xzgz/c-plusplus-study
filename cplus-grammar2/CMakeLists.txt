# collect source files
file(GLOB_RECURSE srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(cplus_grammar_file main_file.cpp auxiliary1.cpp)
target_link_libraries(cplus_grammar_file ${Boost_LINKER_LIBS})
set_target_properties(cplus_grammar_file PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/cplus-grammar2)
set_target_properties(cplus_grammar_file PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)
install(TARGETS cplus_grammar_file DESTINATION ${PROJECT_BINARY_DIR}/install/bin)
