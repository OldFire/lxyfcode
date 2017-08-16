
target := a.out
all: $(target)

CC := g++
LIBPATH := -L/home/ruan/Downloads/OpenCV-2.4.3/build/lib

LIBVAR:=-lopencv_contrib \
	-lopencv_core \
	-lopencv_features2d \
	-lopencv_flann \
	-lopencv_gpu \
	-lopencv_highgui \
	-lopencv_imgproc \
	-lopencv_legacy \
	-lopencv_ml \
	-lopencv_nonfree \
	-lopencv_objdetect \
	-lopencv_photo \
	-lopencv_stitching \
	-lopencv_ts \
	-lopencv_video \
	-lopencv_videostab


INC  += -I/home/ruan/Downloads/OpenCV-2.4.3/build/include/

CPPFLAGS += -std=c++11 -g

src := $(shell find -name "*.cpp")
# .d文件
dep := $(src:.cpp=.d)

-include $(dep)
%.d: %.cpp
	$(CC) -MM $< > $@

obj += $(src:.cpp=.o)

$(target): $(obj)
	$(CC) -o $@ $^ $(LIBPATH) $(LIBVAR)

clean:
	rm *.o *.d $(target) -rf
