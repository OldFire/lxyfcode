target := ans_server
all: $(target)

CC := g++
LIBS += -lpthread -lmysqlclient
CPPFLAGS += -std=c++11 -g

src := $(shell find -name "*.cpp")
# .d文件
dep := $(src:.cpp=.d)

-include $(dep)
%.d: %.cpp
	$(CC) -MM $< > $@

obj += $(src:.cpp=.o)

$(target): $(obj) 
	$(CC) -o $@ $^ $(LIBS)

clean:
	rm *.o *.d -rf
