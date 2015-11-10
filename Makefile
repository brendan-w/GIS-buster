

# ============================= compile settings =============================


CXX       = g++
CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic -fPIC -ggdb
CXXFLAGS += -I.
LIBS      = -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_features2d


# ============================= files and paths =============================

OBJS += find-nodes.o

# ============================= main targets =============================


.PHONY: all
all:find-nodes


find-nodes: $(OBJS)
	$(CXX) $^ $(LIBS) -o $@


%.o: %.c $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -f *.a *.o *.so
	rm -f find-nodes output.png
