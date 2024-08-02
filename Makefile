
CC=g++
BOOST_THREAD=boost_thread
CC+=-g -Wall -std=c++17 -Wno-deprecated-declarations

# List of source files

SOURCES = HashTest.cpp ColtzHash.cpp

# Generate the names of the object files
OBJS=${SOURCES:.cpp=.o}

all: hash

# Compile the hash tests
#
# Remember to set the CPLUS_INCLUDE_PATH, LIBRARY_PATH, and LD_LIBRARY_PATH
# environment variables to include your Boost installation directory.
hash: ${OBJS}
	${CC} -o $@ $^ -l${BOOST_THREAD} -lboost_system -pthread -lboost_regex -ldl

# Generic rules for compiling a source file to an object file
%.o: %.cpp
	${CC} -lboost_thread -lboost_system -pthread -c $<
%.o: %.cc
	${CC} -lboost_thread -lboost_system -pthread -c $<

clean:
	rm -f ${OBJS}
