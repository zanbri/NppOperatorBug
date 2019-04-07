#
#  Make file for main_script
#

#
# Macros
#
CUDA_PATH     = /usr/local/cuda
CUDA_LIB_PATH = $(CUDA_PATH)/samples/7_CUDALibraries

INCLUDES    = -I$(CUDA_PATH)/samples/common/inc # cuda
INCLUDES   += -I$(CUDA_LIB_PATH)/common/UtilNPP # npp

LIBRARIES   = -lpng -lm
LIBRARIES  += -lculibos -lnppc -lnppial -lnppicc -lnppidei -lnppif -lnppig -lnppim -lnppist -lnppisu -lnppitc # npp
LIBRARIES  += `pkg-config --cflags --libs opencv` # opencv

CC		= nvcc
CFLAGS	= -gencode arch=compute_30,code=sm_30 \
		  -gencode arch=compute_52,code=sm_52 \
		  -gencode arch=compute_61,code=sm_61 \
		  --fmad=false \
		  -O3 -std=c++11

CPP_SRCS	= main_script.cpp \
			  class1.cpp \
			  class2.cpp

CPP_HDRS	= class1.h \
			  class2.h

CU_SRCS		= class1_kernel.cu \
			  class2_kernel.cu

CU_HDRS		= class1_kernel.h \
			  class2_kernel.h

#
# Create variable of src files in both current dir and include dir
#

CPP_OBJS	= $(CPP_SRCS:.cpp=.o) 
CU_OBJS		= $(CU_SRCS:.cu=.o)
TARGET		= main_script

CPP_DEPS	= $(CPP_SRCS:.cpp=.d)
CU_DEPS		= $(CU_SRCS:.cu=.d)
DEP_FILE	= Makefile.dep

#
# Suffix rules
#
.SUFFIXES: .cpp
.cpp.o:
	$(CC) $(INCLUDES) $(CFLAGS)  -c $<

.SUFFIXES: .cu
.cu.o:
	$(CC) $(INCLUDES) $(CFLAGS)  -c $<

.SUFFIXES: .d
.cpp.d:
	$(CC) $(INCLUDES) -M $< > $*.d
.cu.d:
	$(CC) $(INCLUDES) -M $< > $*.d

#
# Generating the target
#
all: $(DEP_FILE) $(TARGET) 

#
# Linking the execution file
#
$(TARGET) : $(CU_OBJS) $(CPP_OBJS)
	$(CC) -o $@ $(CU_OBJS) $(CPP_OBJS) $(LIBRARIES)

#
# Generating and including dependencies
#
depend: $(DEP_FILE)
$(DEP_FILE) : $(CPP_DEPS) $(CU_DEPS)
	cat $(CPP_DEPS) $(CU_DEPS) > $(DEP_FILE)
ifeq ($(wildcard $(DEP_FILE)),$(DEP_FILE))
include $(DEP_FILE)
endif

#
# cleaning the files
#
clean:
	rm -f $(CU_OBJS) $(CPP_OBJS) $(CPP_DEPS) $(CU_DEPS) $(DEP_FILE) $(TARGET)
