file( GLOB knapsack_SRCS "knapsack*.cxx" )

add_library( knapsack SHARED ${knapsack_SRCS} )
