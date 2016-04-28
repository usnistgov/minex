# This software was developed at the National Institute of Standards and
# Technology (NIST) by employees of the Federal Government in the course
# of their official duties. Pursuant to title 17 Section 105 of the
# United States Code, this software is not subject to copyright protection
# and is in the public domain. NIST assumes no responsibility whatsoever for
# its use by other parties, and makes no guarantees, expressed or implied,
# about its quality, reliability, or any other characteristic.

LOCALLIB := lib

# Generate -l flag for the core library in LOCALLIB
ifeq ($(shell ls $(LOCALLIB) | grep -E libminexiii_[A-Za-z0-9]\+_\([0-9A-Fa-f]\+\|[0-9A-Fa-f]\{4\}\)\.\(a\|so\) | wc -l | awk '{print $$1}'),1)
        CORE_LIB := $(shell ls $(LOCALLIB) | grep -E libminexiii_[A-Za-z0-9]\+_\([0-9A-Fa-f]\+\|[0-9A-Fa-f]\{4\}\)\.\(a\|so\))
        LIB_ARGS := -l$(patsubst lib%.so,%, $(CORE_LIB:%.a=%.so))
else
        ifeq ($(shell ls $(LOCALLIB) | grep -E libminexiii_[A-Za-z0-9]\+_\([0-9A-Fa-f]\+\|[0-9A-Fa-f]\{4\}\)\.\(a\|so\) | wc -l | awk '{print $$1}'),0)
                $(error No core library found in $(LOCALLIB). Please review MINEX III naming conventions)
        else
                $(error More than one core library found in $(LOCALLIB). Please review MINEX III naming conventions)
        endif
endif
ifeq ($(LIB_ARGS), )
        $(error You did not place your libraries in $(LOCALLIB))
endif
PARTICIPANT_LIB_OPT := -L$(LOCALLIB) $(LIB_ARGS)

PROGRAM := minexiii_validation
SOURCES := minexiii_validation.cpp
OBJECTS := $(SOURCES:%.cpp=%.o)

DISPOSABLEFILES := $(PROGRAM) *.o .gdb_history *.dylib *.so *.a
DISPOSABLEDIRS := validation_output* *.dSYM

CXXFLAGS += -I. -g -std=c++11
LDFLAGS += $(PARTICIPANT_LIB_OPT)

CC := $(CXX)

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) $(DISPOSABLEFILES) 
	$(RM) -r $(DISPOSABLEDIRS)

