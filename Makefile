

# ============================= compile settings =============================


CXX       = g++
CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic -fPIC -ggdb
CXXFLAGS += -I.
LIBS      = -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_features2d


# ============================= main targets =============================


.PHONY: all
all:find-nodes approve-nodes


approve-nodes: approve-nodes.o
	$(CXX) $^ $(LIBS) -o $@


find-nodes: find-nodes.o
	$(CXX) $^ $(LIBS) -o $@


%.o: %.c $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -f *.a *.o *.so
	rm -f find-nodes approve-nodes
	rm -f output.png output.points
