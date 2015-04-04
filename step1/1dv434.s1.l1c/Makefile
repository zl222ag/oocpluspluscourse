CXX=g++
CFLAGS=-Wall -std=c++11

OBJDIR = obj/
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

all: miserable

miserable: ${OBJS}
	${CXX} -g ${CFLAGS} ${OBJS} ${LDFLAGS} -o miserable

$(OBJDIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	${CXX} ${CFLAGS} ${LDFLAGS} -c $< -o $@

clean:
	rm -f ${OBJS} miserable
