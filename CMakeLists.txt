cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

project(
    GuideAlignment
    VERSION 1.0
    LANGUAGES CXX
)

set(SOURCES
    src/main.cpp
    src/fasta_sequence.cpp
    src/fasta_parser.cpp
    src/align_algorithms.cpp
)

set(HEADERS
    include/fasta_sequence.hpp
    include/fasta_parser.hpp
    include/sub_matrix.hpp
    include/align_algorithms.hpp
)

find_package(Boost REQUIRED COMPONENTS 
        program_options 
        filesystem
)

# Create the executable from the source files
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link the Boost libraries to the executable
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

# Set the output directory for the built executable
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build)

# Set the output directory for the built libraries (if you have any)
# set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build)