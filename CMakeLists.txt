CMAKE_MINIMUM_REQUIRED (VERSION 3.12)
PROJECT (nXORE)

#Program Version
SET (nXORE_VERSION_MAJOR 1)
SET (nXORE_VERSION_MINOR 0.0)

#Find Boost Library
set (Boost_USE_STATIC_LIBS	ON)
set (Boost_USE_DEBUG_LIBS	OFF)
set (Boost_USE_RELEASE_LIBS	ON)
set (Boost_USE_MULTITHREADED	ON)
set (Boost_USE_STATIC_RUNTIME	OFF)

find_package (Boost 1.65.0 REQUIRED COMPONENTS
		 system filesystem)

if (Boost_FOUND)
	include_directories (${Boost_INCLUDE_DIRS})
else()
	Message ("Boost Library not found...")
	RETURN()
endif()

#Find Curses Library
find_package (Curses REQUIRED)

if (CURSES_FOUND)
	include_directories (${CURSES_INCLUDE_DIRS})
else()
	Message ("nCurses library not found...")
	RETURN()
endif()

#Set up program
include_directories (src)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set (EXECUTABLE_OUTPUT ${CMAKE_BINARY_DIR})
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

#Add executable program
FILE (GLOB xoreSrc src/*.cpp)
add_executable (nXORE ${xoreSrc})

#Linking the main program
target_link_libraries (nXORE ${Boost_LIBRARIES} ${CURSES_LIBRARIES}
						-lboost_system -lboost_filesystem -lncurses
						-lform -lmenu)
