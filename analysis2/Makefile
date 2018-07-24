TARGET = event
TARGETR = recon
TARGETS = spillhist

ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)
ROOTGLIBS = $(shell root-config --glibs)

CXXFLAGS = $(ROOTFLAGS) -std=c++11 -Wall -fPIC
CXXLIBS	= $(ROOTLIBS)
CC = g++

OBJDIR = ./obj
SRCDIR = ./src
OUTDIR = ./Analysis
INCDIR = -I./include

PROG := $(OUTDIR)/$(TARGET)
PROGR := $(OUTDIR)/$(TARGETR)	
PROGS := $(OUTDIR)/$(TARGETS)		

all: $(PROG) $(PROGR) $(PROGS)

SRCS := $(TARGET).cc
OBJS  = $(addprefix $(SRCDIR)/, $(SRCS:.cc=.o))

$(PROG): $(OBJS)
	$(CC) $(OBJS) -o $@ $(CXXLIBS)

$(SRCDIR)/%.o : $(SRCDIR)/%.cc
	@[ -d $(OBJDIR) ]
	$(CC) $(CXXFLAGS) $(INCDIR) -o $@ -c $<


SRCSR := $(TARGETR).cc
OBJSR  = $(addprefix $(SRCDIR)/, $(SRCSR:.cc=.o))
$(PROGR): $(OBJSR)
	$(CC) $(OBJSR) -o $@ $(CXXLIBS)

$(SRCDIR)/%.o : $(SRCDIR)/%.cc
	@[ -d $(OBJDIR) ]
	$(CC) $(CXXFLAGS) $(INCDIR) -o $@ -c $<

SRCSS := $(TARGETS).cc
OBJSS  = $(addprefix $(SRCDIR)/, $(SRCSS:.cc=.o))
$(PROGS): $(OBJSS)
	$(CC) $(OBJSS) -o $@ $(CXXLIBS)

$(SRCDIR)/%.o : $(SRCDIR)/%.cc
	@[ -d $(OBJDIR) ]
	$(CC) $(CXXFLAGS) $(INCDIR) -o $@ -c $<




