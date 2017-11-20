target := ans_server
all: $(target)

CC := g++
LIBS += -lpthread -lmysqlclient #在此处指定动态库
LIB_PATH+= -L/usr/lib/    #在此处指定动态库的路径
CPPFLAGS += -std=c++11 -g


src := $(shell find -name "*.cpp")
# .d文件
dep := $(src:.cpp=.d)

-include $(dep)
%.d: %.cpp
	$(CC) -MM $< > $@

obj += $(src:.cpp=.o)

$(target): $(obj) 
	$(CC) -o $@ $^ $(LIBS) $(LIB_PATH)

clean:
	rm *.o *.d -rf
