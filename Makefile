#################################
# HAM Makefile
#################################

#HAMDIR = /home/gui/Coding/GBA/devkit/ham-271-linux-full
HAMDIR = /home/gui/programmation/gba/soft/hamlinux
include $(HAMDIR)/system/master.mak

#
# Set the name of your desired GBA image name here
#
PROGNAME = picoloop

#
# Set a list of files you want to compile 
# 
OFILES += codesource/main.o codesource/soundApi/soundApi.o

######################################
# Standard Makefile targets start here
######################################

all : $(PROGNAME).$(EXT) clean

#
# Most Makefile targets are predefined for you, suchas
# vba, clean ... in the following file
#
include $(HAMDIR)/system/standard-targets.mak

######################################
# custom  Makefile targets start here
######################################


gfx: makefile
	gfx2gba -t8 -m -fsrc gfx\\*.bmp
	gfx2gba -t8 -m -rs -fsrc gfx\\facerot.bmp
	



