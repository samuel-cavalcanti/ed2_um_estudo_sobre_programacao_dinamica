cmake_minimum_required(VERSION 3.19)
project(ed2_um_estudo_sobre_programacao_dinamica)

set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage") #codecov
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/.travis/cmake) # modulo para codecov


include(CodeCoverage)

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 11)

add_executable(ed2_um_estudo_sobre_programacao_dinamica main.cpp)


target_link_libraries(ed2_um_estudo_sobre_programacao_dinamica GTest::GTest GTest::Main)

setup_target_for_coverage(coverage  ed2_um_estudo_sobre_programacao_dinamica  coverage)