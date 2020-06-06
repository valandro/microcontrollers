TARGET=hello
SRCS=$(TARGET).cpp

FLAGS=-O2 -Wall -g -MMD
INCLUDE=-I.
LIBDIR=
LIBS=

CPP=$(CROSS_COMPILE)g++
CFLAGS=$(FLAGS) $(INCLUDE)
LDFLAGS=$(LIBDIR) $(LIBS)

all: $(TARGET)

$(TARGET): $(SRCS:.cpp=.out)
		$(CPP) -o $@ $^ $(LDFLAGS)

%.out: %.cpp
		$(CPP) $(CFLAGS) -c -o $@ $<

-include $(SRCS:.cpp=.d) 22

clean:
		rm -f *~ *.out *.d

distclean: clean
		rm -f $(TARGET)
