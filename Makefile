ifeq ($(strip $(PVSNESLIB_HOME)),)
$(error "Please create an environment variable PVSNESLIB_HOME with path to its folder and restart application. (you can do it on windows with <setx PVSNESLIB_HOME "/c/snesdev">)")
endif

# export PVSNESLIB_DEBUG = 1

include ${PVSNESLIB_HOME}/devkitsnes/snes_rules

#---------------------------------------------------------------------------------
# ROMNAME is used in snes_rules file
export ROMNAME := rgc2024demo

#---------------------------------------------------------------------------------
# Name of text file containing build number.
BUILD_NUMBER_FILE=src/buildnumber.txt
BUILD_INCLUD_FILE=src/buildnum.h

#---------------------------------------------------------------------------------
export OFILES	:=	$(BINFILES:.bin=.obj) $(CFILES:.c=.obj) $(SFILES:.asm=.obj)
 
export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
					-I$(CURDIR)/$(BUILD)
GTITLE 		:= -ht"RGC2024 20 ANS       "
 
.PHONY: musics bitmaps all

#---------------------------------------------------------------------------------  
all	: musics bitmaps $(ROMNAME).sfc
	$(SNTOOLS) -hi! -hr0B $(GTITLE) $(ROMNAME).sfc
	sed 's/://' <$(ROMNAME).sym >$(ROMNAME).tmp
	rm -f $(ROMNAME).sym
	mv $(ROMNAME).sfc out/$(ROMNAME).sfc
	mv $(ROMNAME).tmp out/$(ROMNAME).sym
	@echo Generate new build number ... $(notdir $@)
	@if ! test -f $(BUILD_NUMBER_FILE); then echo 0 > $(BUILD_NUMBER_FILE); fi
	@echo $$(($$(cat $(BUILD_NUMBER_FILE)) + 1)) > $(BUILD_NUMBER_FILE)
	@echo "#define BUILDID \"V"$$(date +'%y%m%d')"B"$$(cat $(BUILD_NUMBER_FILE))\" > $(BUILD_INCLUD_FILE)
	
clean:
	@echo clean ...
	@rm -f $(OFILES) $(ROMNAME).sfc $(ROMNAME).sym *.pic *.map *.pal *.brr *.bnk
	@rm -f gfxs/*.pic gfxs/*.map gfxs/*.pal gfxs/*.pc7 gfxs/*.mp7
	@rm -f gfxs/sprites/*.pic gfxs/sprites/*.map gfxs/sprites/*.pal
	@rm -f snds/soundbank.* soundbank.* snd/*.brr *.brr

#---------------------------------------------------------------------------------
snds/matilda.bnk: snds/matilda.it
	$(SMCONV) -f -s -o snds/soundbank -V snds/matilda.it
	cp snds/soundbank.bnk snds/matilda.bnk

musics: snds/matilda.bnk 

#---------------------------------------------------------------------------------
gfxs/fonts.pic: gfxs/fonts.png
	@echo convert fonts with no tile reduction ... $(notdir $@)
	$(GFXCONV) -s 8 -o 16 -u 16 -e 0 -R -p -i $<

gfxs/stars.pic: gfxs/stars.png
	@echo convert starfield bitmap to graphics... $(notdir $@)
	$(GFXCONV) -s 8 -o 16 -u 16 -e 1 -p -m -i $<

gfxs/logo.pic: gfxs/logo.png
	@echo convert logo bitmap to graphics with high priority ... $(notdir $@)
	$(GFXCONV) -s 8 -o 32 -u 16 -e 2 -g -p -m -i $<

gfxs/sprites.pic: gfxs/sprites.png
	@echo convert sprite 32px bitmap to graphics... $(notdir $@)
	$(GFXCONV) -s 32 -o 32 -u 16 -e 0 -p -i $<

gfxs/firstone.pic: gfxs/firstone.png
	@echo first meeting bitmap ... $(notdir $@)
	$(GFXCONV) -s 8 -o 80 -u 16 -e 2 -p -m -i $<

gfxs/lastone.pic: gfxs/lastone.png
	@echo first meeting bitmap ... $(notdir $@)
	$(GFXCONV) -s 8 -o 80 -u 16 -e 2 -p -m -i $<

gfxs/rgc2006.pic: gfxs/rgc2006.png
	@echo first meeting bitmap ... $(notdir $@)
	$(GFXCONV) -s 8 -o 80 -u 16 -e 2 -p -m -i $<

gfxs/rgc2007.pic: gfxs/rgc2007.png
	@echo first meeting bitmap ... $(notdir $@)
	$(GFXCONV) -s 8 -o 80 -u 16 -e 2 -p -m -i $<

gfxs/rgc2008.pic: gfxs/rgc2008.png
	@echo first meeting bitmap ... $(notdir $@)
	$(GFXCONV) -s 8 -o 80 -u 16 -e 2 -p -m -i $<

gfxs/rgc2010.pic: gfxs/rgc2010.png
	@echo first meeting bitmap ... $(notdir $@)
	$(GFXCONV) -s 8 -o 80 -u 16 -e 2 -p -m -i $<

gfxs/rgc2011.pic: gfxs/rgc2011.png
	@echo first meeting bitmap ... $(notdir $@)
	$(GFXCONV) -s 8 -o 80 -u 16 -e 2 -p -m -i $<

gfxs/rgc2012.pic: gfxs/rgc2012.png
	@echo first meeting bitmap ... $(notdir $@)
	$(GFXCONV) -s 8 -o 80 -u 16 -e 2 -p -m -i $<

gfxs/rgc2016.pic: gfxs/rgc2016.png
	@echo first meeting bitmap ... $(notdir $@)
	$(GFXCONV) -s 8 -o 80 -u 16 -e 2 -p -m -i $<

gfxs/rgc2018.pic: gfxs/rgc2018.png
	@echo first meeting bitmap ... $(notdir $@)
	$(GFXCONV) -s 8 -o 80 -u 16 -e 2 -p -m -i $<

bitmaps : gfxs/fonts.pic gfxs/stars.pic gfxs/logo.pic gfxs/sprites.pic gfxs/firstone.pic gfxs/lastone.pic \
	gfxs/rgc2006.pic gfxs/rgc2007.pic gfxs/rgc2008.pic gfxs/rgc2010.pic gfxs/rgc2011.pic \
	gfxs/rgc2012.pic gfxs/rgc2016.pic gfxs/rgc2018.pic 

#---------------------------------------------------------------------------------
$(OUTPUT).sfc	: $(OFILES)
