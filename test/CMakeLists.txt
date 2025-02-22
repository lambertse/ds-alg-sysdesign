macro(add_test_executable name)
  add_executable(${name} ${name}_test.cpp)
  target_link_libraries(${name} gtest_main datastructures)
  add_test(${name} ${name})
endmacro()

add_test_executable(geohash)
add_test_executable(skip_list)
add_test_executable(countmin_sketch)
