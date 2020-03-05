COMPILER  = g++
ifeq "$(shell getconf LONG_BIT)" "64"
  LDFLAGS = -pthread 
	CPP_DEFS = -D__USE_64BITOS
else
  LDFLAGS = -pthread
endif
CFLAGS    = $(CPP_DEFS) -g -MMD -MP -Wall -Wextra -Winit-self -Wno-missing-field-initializers -std=c++11 -O0 -fpermissive 
LIBS      =
INCLUDE   = \
						-I./Inc

TARGET    = ./build/$(shell basename `readlink -f .`)

SOURCES   = \
$(wildcard Src/*.cpp) 

OBJDIR    = ./build
OBJECTS = $(addprefix $(OBJDIR)/,$(notdir $(SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(SOURCES)))
DEPENDS   = $(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS) $(LIBS)
	$(COMPILER) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o:%.cpp
	-mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(TARGET)

run:
	$(TARGET)

clean:
	-rm -rf $(OBJDIR)

-include $(DEPENDS)