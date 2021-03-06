project(plotfx)
add_definitions("-DPLOTFX_VERSION='\"v0.2.0\"'")


# CMake Setup
# -----------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8.8)
enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/extra/cmake")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source/utils)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


# Dependencies
# -----------------------------------------------------------------------------
find_package(Threads)
find_package(Cairo)
find_package(Freetype)
find_package(HarfBuzz)
find_package(Fontconfig)
find_package(PNG)
include_directories(${CAIRO_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS} ${HARFBUZZ_INCLUDE_DIRS} ${PNG_INCLUDE_DIRS})


# Build: PlotFX Library
# -----------------------------------------------------------------------------
file(GLOB source_files "source/**/*.cc" "source/*.cc")
list(REMOVE_ITEM source_files "source/plotfx_cli.cc")
add_library(plotfx STATIC ${source_files})
set_target_properties(plotfx PROPERTIES PUBLIC_HEADER "source/plotfx.h;source/plotfx_sdl.h")
set(PLOTFX_LDFLAGS plotfx ${CAIRO_LIBRARIES} ${FREETYPE_LIBRARIES} ${HARFBUZZ_LIBRARIES} ${HARFBUZZ_ICU_LIBRARIES} ${PNG_LIBRARIES} ${FONTCONFIG_LIBRARIES})


# Build: CLI
# -----------------------------------------------------------------------------
add_executable(plotfx-cli source/plotfx_cli.cc)
target_link_libraries(plotfx-cli ${PLOTFX_LDFLAGS})
set_target_properties(plotfx-cli PROPERTIES OUTPUT_NAME plotfx)


# Installation
# -----------------------------------------------------------------------------
install(TARGETS plotfx ARCHIVE DESTINATION lib PUBLIC_HEADER DESTINATION include/plotfx)
install(TARGETS plotfx-cli DESTINATION bin)


# Testing
# -----------------------------------------------------------------------------
file(GLOB unit_test_files "tests/unit/**/test_*.cc")
foreach(unit_test_path ${unit_test_files})
  get_filename_component(unit_test_name ${unit_test_path} NAME_WE)
  get_filename_component(unit_test_srcdir ${unit_test_path} DIRECTORY)

  add_executable(${unit_test_name} ${unit_test_path})
  target_link_libraries(${unit_test_name} ${PLOTFX_LDFLAGS})

  add_test(
      NAME ${unit_test_name}
      COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${unit_test_name})
endforeach()

file(GLOB spec_test_files "tests/spec/**/test_*.ptx")
foreach(spec_test_path ${spec_test_files})
  get_filename_component(spec_test_name ${spec_test_path} NAME_WE)
  get_filename_component(spec_test_srcdir ${spec_test_path} DIRECTORY)
  add_test(
      NAME ${spec_test_name}_svg
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/tests/spec/test_runner.sh ${CMAKE_CURRENT_BINARY_DIR}/plotfx ${spec_test_path} ${CMAKE_CURRENT_BINARY_DIR}/${spec_test_name}.svg ${spec_test_srcdir}/${spec_test_name}.svg)
endforeach()

file(GLOB example_test_files "examples/**/*.ptx")
foreach(example_test_path ${example_test_files})
  get_filename_component(example_test_name ${example_test_path} NAME_WE)
  get_filename_component(example_test_srcdir ${example_test_path} DIRECTORY)
  add_test(
      NAME test_example_${example_test_name}_svg
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/tests/spec/test_runner.sh ${CMAKE_CURRENT_BINARY_DIR}/plotfx ${example_test_path} ${CMAKE_CURRENT_BINARY_DIR}/example_${example_test_name}.svg ${example_test_srcdir}/${example_test_name}.svg)
endforeach()

file(GLOB doc_test_files "manual/figures/*.ptx")
foreach(doc_test_path ${doc_test_files})
  get_filename_component(doc_test_name ${doc_test_path} NAME_WE)
  get_filename_component(doc_test_srcdir ${doc_test_path} DIRECTORY)
  add_test(
      NAME test_doc_${doc_test_name}_svg
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/tests/spec/test_runner.sh ${CMAKE_CURRENT_BINARY_DIR}/plotfx ${doc_test_path} ${CMAKE_CURRENT_BINARY_DIR}/figure_${doc_test_name}.svg ${doc_test_srcdir}/${doc_test_name}.svg)
endforeach()
