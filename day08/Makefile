
target := lm.bin
all: $(target)

CC := g++
LIBS += -lpthread
CPPFLAGS += -std=c++11 -g

src := $(shell find -name "*.cpp")
# .d文件
dep := $(src:.cpp=.d)

-include $(dep)
%.d: %.cpp
	$(CC) -MM $< > $@

obj += $(src:.cpp=.o)

$(target): $(obj) cJSON.o
	$(CC) -o $@ $^ $(LIBS)

clean:
	rm *.o $(target) -rf
