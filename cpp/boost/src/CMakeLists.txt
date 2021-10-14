set(Boost_INCLUDE_DIR /opt/homebrew/Cellar/boost/1.76.0/include)
set(Boost_LIBRARY_DIR /opt/homebrew/Cellar/boost/1.76.0/lib)
FIND_PACKAGE( Boost COMPONENTS system filesystem REQUIRED )
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
add_executable(example1 chap2/example1.cpp)
target_link_libraries(example1 LINK_PUBLIC ${Boost_LIBRARY_DIR})

add_executable(unique_ptr1 chap3/unique_ptr1.cpp)
target_link_libraries(unique_ptr1 LINK_PUBLIC ${Boost_LIBRARY_DIR})

add_executable(bitamp example_bitmap.cpp)
target_link_libraries(bitamp LINK_PUBLIC ${Boost_LIBRARY_DIR})

add_executable(phoenix example_phoenix.cpp)
target_link_libraries(phoenix LINK_PUBLIC ${Boost_LIBRARY_DIR})