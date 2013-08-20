project (pelly)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set (pelly_SRCS
	src/main.cpp
	src/Application.cpp
	src/AssetContainer.cpp
	src/Player.cpp
	src/LevelWorld.cpp
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set (pelly_SRCS "${pelly_SRCS} src/ResourceDirectory.mm")
endif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

set (pelly_LIBS
	sfml-graphics
	sfml-window
	sfml-audio
	sfml-system
)

add_executable(pelly ${pelly_SRCS})
target_link_libraries(pelly ${pelly_LIBS})