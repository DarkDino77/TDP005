cmake_minimum_required ( VERSION 3.10)
project (sfml)

# Använd C++ 17.
set( CMAKE_CXX_STANDARD 17)

# Välj vilka delar av SFML som ska användas .
set( SFML_MODULES network graphics window system)

# Lägg till lämpliga bibliotek till kompileringen .
foreach (i ${SFML_MODULES})
	list(APPEND SFML_LIBRARIES "sfml-${i}")
endforeach (i)

# Ange källfiler , lägg till de filer som ni behöver !
set( SOURCE_FILES game.cc)

# Säg till CMake att skapa en körbar fil som heter 'sfml '.
add_executable (game ${SOURCE_FILES})

# Länka med biblioteken som vi hittade tidigare .
target_link_libraries (game ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
