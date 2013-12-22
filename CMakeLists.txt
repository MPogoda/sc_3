project( knapsack )

cmake_minimum_required( VERSION 2.8.6 )

add_definitions( -std=c++0x )
file( GLOB knapsack_SRCS "knapsack*.cxx" )

add_library( knapsack SHARED ${knapsack_SRCS} )

add_executable( test "test.cxx" )
target_link_libraries( test knapsack )
