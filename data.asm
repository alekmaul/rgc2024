.include "hdr.asm"

.section ".rogener1" superfree

fontg: .incbin "gfxs/fonts.pic"
fontg_end:
fontp: .incbin "gfxs/fonts.pal"

starsg: .incbin "gfxs/stars.pic"
starsg_end:
starsp: .incbin "gfxs/stars.pal"
starsm: .incbin "gfxs/stars.map"

logog: .incbin "gfxs/logo.pic"
logog_end:
logop: .incbin "gfxs/logo.pal"
logom: .incbin "gfxs/logo.map"

spriteg: .incbin "gfxs/sprites.pic"
spriteg_end:
spritep: .incbin "gfxs/sprites.pal"

.ends

.section ".rogener2" superfree

firstonesg: .incbin "gfxs/firstone.pic"
firstonesg_end:

firstonesp: .incbin "gfxs/firstone.pal"
firstonesm: .incbin "gfxs/firstone.map"

lastonesp: .incbin "gfxs/lastone.pal"
lastonesm: .incbin "gfxs/lastone.map"

.ends

.section ".rogener3" superfree

lastonesg: .incbin "gfxs/lastone.pic"
lastonesg_end:

.ends

.section ".rorgc2006" superfree
rgc2006g: .incbin "gfxs/rgc2006.pic"
rgc2006g_end:
rgc2006m: .incbin "gfxs/rgc2006.map"
rgc2006p: .incbin "gfxs/rgc2006.pal"
.ends

.section ".rorgc2007" superfree
rgc2007g: .incbin "gfxs/rgc2007.pic"
rgc2007g_end:
rgc2007m: .incbin "gfxs/rgc2007.map"
rgc2007p: .incbin "gfxs/rgc2007.pal"
.ends

.section ".rorgc2008" superfree
rgc2008g: .incbin "gfxs/rgc2008.pic"
rgc2008g_end:
rgc2008m: .incbin "gfxs/rgc2008.map"
rgc2008p: .incbin "gfxs/rgc2008.pal"
.ends

.section ".rorgc2010" superfree
rgc2010g: .incbin "gfxs/rgc2010.pic"
rgc2010g_end:
rgc2010m: .incbin "gfxs/rgc2010.map"
rgc2010p: .incbin "gfxs/rgc2010.pal"
.ends

.section ".rorgc2011" superfree
rgc2011g: .incbin "gfxs/rgc2011.pic"
rgc2011g_end:
rgc2011m: .incbin "gfxs/rgc2011.map"
rgc2011p: .incbin "gfxs/rgc2011.pal"
.ends

.section ".rorgc2012" superfree
rgc2012g: .incbin "gfxs/rgc2012.pic"
rgc2012g_end:
rgc2012m: .incbin "gfxs/rgc2012.map"
rgc2012p: .incbin "gfxs/rgc2012.pal"
.ends

.section ".rorgc2016" superfree
rgc2016g: .incbin "gfxs/rgc2016.pic"
rgc2016g_end:
rgc2016m: .incbin "gfxs/rgc2016.map"
rgc2016p: .incbin "gfxs/rgc2016.pal"
.ends

.section ".rorgc2018" superfree
rgc2018g: .incbin "gfxs/rgc2018.pic"
rgc2018g_end:
rgc2018m: .incbin "gfxs/rgc2018.map"
rgc2018p: .incbin "gfxs/rgc2018.pal"
.ends

; --------------------------  Sound + Music
.bank 5
.section "SOUNDBANK0" ; need dedicated bank(s)

SOUNDBANK__0:
.incbin "snds/matilda.bnk" 
.ends


