project( knapsack )

cmake_minimum_required( VERSION 2.8.6 )

set( CMAKE_AUTOMOC true )

find_package( Qt4 REQUIRED QtGui QtCore )

include( ${QT_USE_FILE} )

add_definitions( -std=c++0x )

file( GLOB SOURCES "*.cpp" )
add_subdirectory( "lib" )

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

qt4_wrap_ui( mainWindowFORM "mainwindow.ui" )

add_executable( GAKnapsack ${SOURCES} ${mainWindowFORM} )
target_link_libraries( GAKnapsack ${QT_LIBRARIES} knapsack )
