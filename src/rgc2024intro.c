/*---------------------------------------------------------------------------------

	RGC2024 - a new Snes intro for Retro Gaming Connexion event
			
			main functions
			
	-- alekmaul (2024/09/12)

---------------------------------------------------------------------------------*/
#include <snes.h>

#include "rgc2024intro.h"


//---------------------------------------------------------------------------------
extern u8 fontg,fontg_end,fontp;														// graphic for font
extern u8 starsg,starsg_end,starsp,starsm;									// graphic for starfield
extern u8 logog,logog_end,logop,logom;											// graphic for logo
extern u8 spriteg, spriteg_end, spritep;										// graphic for sprites

extern u8 firstonesg,firstonesg_end,firstonesp,firstonesm;	// 1st RGC (JAG CNX 2004)
extern u8 lastonesg,lastonesg_end,lastonesp,lastonesm;		// last RGC in 2023

extern u8 SOUNDBANK__0;										// music

extern u8 rgc2006m,rgc2006g,rgc2006g_end,rgc2006p; // 2006
extern u8 rgc2007m,rgc2007g,rgc2007g_end,rgc2007p; // 2007
extern u8 rgc2008m,rgc2008g,rgc2008g_end,rgc2008p; // 2008
extern u8 rgc2010m,rgc2010g,rgc2010g_end,rgc2010p; // 2010
extern u8 rgc2011m,rgc2011g,rgc2011g_end,rgc2011p; // 2011
extern u8 rgc2012m,rgc2012g,rgc2012g_end,rgc2012p; // 2012
extern u8 rgc2016m,rgc2016g,rgc2016g_end,rgc2016p; // 2016
extern u8 rgc2018m,rgc2018g,rgc2018g_end,rgc2018p; // 2018
	
//---------------------------------------------------------------------------------
// From my friend Stef and his SGDK for Megadrive :)
typedef s16 fix16;
#define sinFix16(value)             sintab16[(value) & 1023]
#define cosFix16(value) sintab16[((value) + 256) & 1023]

const fix16 sintab16[1024] =
{
    0, 0, 1, 1, 2, 2, 2, 3,
    3, 4, 4, 4, 5, 5, 5, 6,
    6, 7, 7, 7, 8, 8, 9, 9,
    9, 10, 10, 11, 11, 11, 12, 12,
    12, 13, 13, 14, 14, 14, 15, 15,
    16, 16, 16, 17, 17, 17, 18, 18,
    19, 19, 19, 20, 20, 20, 21, 21,
    22, 22, 22, 23, 23, 23, 24, 24,
    24, 25, 25, 26, 26, 26, 27, 27,
    27, 28, 28, 28, 29, 29, 29, 30,
    30, 31, 31, 31, 32, 32, 32, 33,
    33, 33, 34, 34, 34, 35, 35, 35,
    36, 36, 36, 37, 37, 37, 37, 38,
    38, 38, 39, 39, 39, 40, 40, 40,
    41, 41, 41, 42, 42, 42, 42, 43,
    43, 43, 44, 44, 44, 44, 45, 45,
    45, 46, 46, 46, 46, 47, 47, 47,
    47, 48, 48, 48, 48, 49, 49, 49,
    49, 50, 50, 50, 50, 51, 51, 51,
    51, 52, 52, 52, 52, 53, 53, 53,
    53, 53, 54, 54, 54, 54, 54, 55,
    55, 55, 55, 55, 56, 56, 56, 56,
    56, 57, 57, 57, 57, 57, 58, 58,
    58, 58, 58, 58, 59, 59, 59, 59,
    59, 59, 59, 60, 60, 60, 60, 60,
    60, 60, 61, 61, 61, 61, 61, 61,
    61, 61, 61, 62, 62, 62, 62, 62,
    62, 62, 62, 62, 62, 63, 63, 63,
    63, 63, 63, 63, 63, 63, 63, 63,
    63, 63, 63, 63, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 63, 63, 63,
    63, 63, 63, 63, 63, 63, 63, 63,
    63, 63, 63, 63, 62, 62, 62, 62,
    62, 62, 62, 62, 62, 62, 61, 61,
    61, 61, 61, 61, 61, 61, 61, 60,
    60, 60, 60, 60, 60, 60, 59, 59,
    59, 59, 59, 59, 59, 58, 58, 58,
    58, 58, 58, 57, 57, 57, 57, 57,
    56, 56, 56, 56, 56, 55, 55, 55,
    55, 55, 54, 54, 54, 54, 54, 53,
    53, 53, 53, 53, 52, 52, 52, 52,
    51, 51, 51, 51, 50, 50, 50, 50,
    49, 49, 49, 49, 48, 48, 48, 48,
    47, 47, 47, 47, 46, 46, 46, 46,
    45, 45, 45, 44, 44, 44, 44, 43,
    43, 43, 42, 42, 42, 42, 41, 41,
    41, 40, 40, 40, 39, 39, 39, 38,
    38, 38, 37, 37, 37, 37, 36, 36,
    36, 35, 35, 35, 34, 34, 34, 33,
    33, 33, 32, 32, 32, 31, 31, 31,
    30, 30, 29, 29, 29, 28, 28, 28,
    27, 27, 27, 26, 26, 26, 25, 25,
    24, 24, 24, 23, 23, 23, 22, 22,
    22, 21, 21, 20, 20, 20, 19, 19,
    19, 18, 18, 17, 17, 17, 16, 16,
    16, 15, 15, 14, 14, 14, 13, 13,
    12, 12, 12, 11, 11, 11, 10, 10,
    9, 9, 9, 8, 8, 7, 7, 7,
    6, 6, 5, 5, 5, 4, 4, 4,
    3, 3, 2, 2, 2, 1, 1, 0,
    0, 0, -1, -1, -2, -2, -2, -3,
    -3, -4, -4, -4, -5, -5, -5, -6,
    -6, -7, -7, -7, -8, -8, -9, -9,
    -9, -10, -10, -11, -11, -11, -12, -12,
    -12, -13, -13, -14, -14, -14, -15, -15,
    -16, -16, -16, -17, -17, -17, -18, -18,
    -19, -19, -19, -20, -20, -20, -21, -21,
    -22, -22, -22, -23, -23, -23, -24, -24,
    -24, -25, -25, -26, -26, -26, -27, -27,
    -27, -28, -28, -28, -29, -29, -29, -30,
    -30, -31, -31, -31, -32, -32, -32, -33,
    -33, -33, -34, -34, -34, -35, -35, -35,
    -36, -36, -36, -37, -37, -37, -37, -38,
    -38, -38, -39, -39, -39, -40, -40, -40,
    -41, -41, -41, -42, -42, -42, -42, -43,
    -43, -43, -44, -44, -44, -44, -45, -45,
    -45, -46, -46, -46, -46, -47, -47, -47,
    -47, -48, -48, -48, -48, -49, -49, -49,
    -49, -50, -50, -50, -50, -51, -51, -51,
    -51, -52, -52, -52, -52, -53, -53, -53,
    -53, -53, -54, -54, -54, -54, -54, -55,
    -55, -55, -55, -55, -56, -56, -56, -56,
    -56, -57, -57, -57, -57, -57, -58, -58,
    -58, -58, -58, -58, -59, -59, -59, -59,
    -59, -59, -59, -60, -60, -60, -60, -60,
    -60, -60, -61, -61, -61, -61, -61, -61,
    -61, -61, -61, -62, -62, -62, -62, -62,
    -62, -62, -62, -62, -62, -63, -63, -63,
    -63, -63, -63, -63, -63, -63, -63, -63,
    -63, -63, -63, -63, -64, -64, -64, -64,
    -64, -64, -64, -64, -64, -64, -64, -64,
    -64, -64, -64, -64, -64, -64, -64, -64,
    -64, -64, -64, -64, -64, -64, -64, -64,
    -64, -64, -64, -64, -64, -64, -64, -64,
    -64, -64, -64, -64, -64, -63, -63, -63,
    -63, -63, -63, -63, -63, -63, -63, -63,
    -63, -63, -63, -63, -62, -62, -62, -62,
    -62, -62, -62, -62, -62, -62, -61, -61,
    -61, -61, -61, -61, -61, -61, -61, -60,
    -60, -60, -60, -60, -60, -60, -59, -59,
    -59, -59, -59, -59, -59, -58, -58, -58,
    -58, -58, -58, -57, -57, -57, -57, -57,
    -56, -56, -56, -56, -56, -55, -55, -55,
    -55, -55, -54, -54, -54, -54, -54, -53,
    -53, -53, -53, -53, -52, -52, -52, -52,
    -51, -51, -51, -51, -50, -50, -50, -50,
    -49, -49, -49, -49, -48, -48, -48, -48,
    -47, -47, -47, -47, -46, -46, -46, -46,
    -45, -45, -45, -44, -44, -44, -44, -43,
    -43, -43, -42, -42, -42, -42, -41, -41,
    -41, -40, -40, -40, -39, -39, -39, -38,
    -38, -38, -37, -37, -37, -37, -36, -36,
    -36, -35, -35, -35, -34, -34, -34, -33,
    -33, -33, -32, -32, -32, -31, -31, -31,
    -30, -30, -29, -29, -29, -28, -28, -28,
    -27, -27, -27, -26, -26, -26, -25, -25,
    -24, -24, -24, -23, -23, -23, -22, -22,
    -22, -21, -21, -20, -20, -20, -19, -19,
    -19, -18, -18, -17, -17, -17, -16, -16,
    -16, -15, -15, -14, -14, -14, -13, -13,
    -12, -12, -12, -11, -11, -11, -10, -10,
    -9, -9, -9, -8, -8, -7, -7, -7,
    -6, -6, -5, -5, -5, -4, -4, -4,
    -3, -3, -2, -2, -2, -1, -1, 0
};


//---------------------------------------------------------------------------------
#define FIRSTDISPAGAIN 43

typedef struct {
	u8 *mapL1; 				                                // current map layer 1
	u8 *gfx, *gfxend,*gfxp;                                 // current graphics tileset and palette
} _rgcevent;

const _rgcevent events[8] =
{
	{ (u8 *) &rgc2006m,(u8 *) & rgc2006g,(u8 *) &rgc2006g_end,(u8 *) &rgc2006p}, // 2006
	{ (u8 *) &rgc2007m,(u8 *) & rgc2007g,(u8 *) &rgc2007g_end,(u8 *) &rgc2007p}, // 2007
	{ (u8 *) &rgc2008m,(u8 *) & rgc2008g,(u8 *) &rgc2008g_end,(u8 *) &rgc2008p}, // 2008
	{ (u8 *) &rgc2010m,(u8 *) & rgc2010g,(u8 *) &rgc2010g_end,(u8 *) &rgc2010p}, // 2010
	{ (u8 *) &rgc2011m,(u8 *) & rgc2011g,(u8 *) &rgc2011g_end,(u8 *) &rgc2011p}, // 2011
	{ (u8 *) &rgc2012m,(u8 *) & rgc2012g,(u8 *) &rgc2012g_end,(u8 *) &rgc2012p}, // 2012
	{ (u8 *) &rgc2016m,(u8 *) & rgc2016g,(u8 *) &rgc2016g_end,(u8 *) &rgc2016p}, // 2016
	{ (u8 *) &rgc2018m,(u8 *) & rgc2018g,(u8 *) &rgc2018g_end,(u8 *) &rgc2018p}, // 2018
};

const char *demo_strings[] = 
{
	/*
	"<------- MAX HEADROOM --------->\0"
	*/
    "OYEZ, OYEZ, LES GAMERS (EUSES)\0",
    "LES 2 & 3 NOVEMBRE PROCHAINS\0",
    "L ASSO RGC VOUS DONNE\0",
    "RENDEZ-VOUS POUR PARTAGER\0",
    "OU DECOUVRIR DES MACHINES, \0",
    "DES JEUX ET DES PROJETS\0",
    "INSOLITES ET DIVERS \0",
    "SUR NOS MACHINES RETROS\0",
    "MAIS AUSSI NEXT GEN.\0",
    "CETTE MANIFESTATION HISTORIQUE \0",
    "VOUS PERMETTRA DE RAMENER ...\0",
    "VOS VIEILLES CONSOLES ET ...\0",
    "JV PREFERES POUR\0",
    "DECOUVRIR DE SUPERS JEUX OU\0",
    "D'AUTRES MECONNUS.\0",

    "ET BIEN ENTENDU,\0",
    "CETTE DEMO OLDSCHOOL, YEAAAH !!\0",

    "NOUS VOUS ATTENDONS AVEC\0",
    "IMPATIENCE POUR CET EVENEMENT\0",
    "CONVIVIAL ET SPECIALISE ! \0",
    "IL AURA LIEU EN SEINE ET MARNE,\0",
    "A LIZY SUR OURCQ, PRES DE MEAUX.\0",
    "L ASSO RGC A ETE CREE A CONGIS,\0",
    "EN 2004 PAR QUELQUES PASSIONNES,\0",
    "POCKET, ODIE ONE, ARETHIUS,\0",
    "FLORIAN, LBM41 ET XIRIUS THIR,\0", 
    "CE SERA L OCCASION DE FETER,\0",
    "LES 20 ANS DE L ASSOCIATION\0",
    "LES INSCRIPTIONS SONT OUVERTES !\0",
    "N'OUBLIEZ PAS DE VOUS INSCRIRE,\0",
    "LES PLACES SONT LIMITEES !\0",
    "REMERCIEMENTS POUR CETTE INTRO\0",
    "MUSIQUE DE RETRO (MATILDA)\0",
    "CODE D'ALEKMAUL EN 6 HEURES :)\0",

    "--- REMERCIEMENTS POUR ---\0",
    "LES MEMBRES ACTIFS DE LA RGC,\0",
    "OTAKUFOU, RAPH BENDER, JEGOUGOU,\0",
    "INES, RITON, CHEZMOA, NHUT\0",
    "JAARDHEM, MARUKU, DACOBAH\0",
    "RITA,NTRS, BJORN, AMELIE, JANSKY\0",
    "FADEST, VINCE, DR WATSON, XEL\0",
    "TOSMO, MANUELLA, LESARTHOIS\0",
    "GEORGE LUCAS, TERIAK ET ISOBEL\0",
    "UNE PENSEE POUR BORIS747 - RIP,\0",
    "SANS OUBLIER ...\0",
    "LA MAIRIE DE LIZY SUR OURCQ :) !\0",

	//"LE TEXTE VA RECOMMENCER ...\0",
	" \0",
	/*	Do not remove the next line */
	"\0"
};

const u8 sprIdx[16] =
{
	0x00, 0x04, 0x08, 0x0C, 0x40, 0x44, 0x48, 0x4C, 0x80, 0x84, 0x88, 0x8C, 0xC0, 0xC4, 0xC8, 0xCC,
};

//---------------------------------------------------------------------------------
u16 i, ns, s;
char c;
u16 fade, faded_idx;

u16 figure_counter;
u8 figure_mode;
u8 demo_phase;
u8 vblrefresh;
u16 phase_counter;
u8 rgc_counter;

u8 scroll_bg2[(3*TABLE_LEN)+1];
u8 scroll_speed[TABLE_LEN];
u8 *ptscr,*ptspd;
dmaMemory  data_to_transfert;

u16 txtLine[32];

u16 writer_state;
u16 writer_switch;
u16 current_string_idx;
u16 current_string_len;
u16 current_char_idx;
u16 current_char_x;
u16 writer_timer;

_rgcevent *pEvent;								// pointer to current event information

//---------------------------------------------------------------------------------
u16 charToTileIndex(char c) {
	if (c >= 'A' && c <= 'Z')
		return (u16) (c - 'A' + FONT_OFFSET); 

	if (c >= '0' && c <= '9')
		return (u16)(c - '0') + 26 + FONT_OFFSET;

	switch(c)	{
		case '!':
			return FONT_PUNCT_OFFSET;
		case '\"':
			return FONT_PUNCT_OFFSET + 1;
		case '#':
			return FONT_PUNCT_OFFSET + 2;
		case '$':
			return FONT_PUNCT_OFFSET + 3;
		case '%':
			return FONT_PUNCT_OFFSET + 4;
		case '&':
			return FONT_PUNCT_OFFSET + 5;
		case '\'':
			return FONT_PUNCT_OFFSET + 6;
		case '(':
			return FONT_PUNCT_OFFSET + 7;
		case ')':
			return FONT_PUNCT_OFFSET + 8;
		case '*':
			return FONT_PUNCT_OFFSET + 9;
		case '+':
			return FONT_PUNCT_OFFSET + 10;
		case ',':
			return FONT_PUNCT_OFFSET + 11;
		case '-':
			return FONT_PUNCT_OFFSET + 12;
		case '.':
			return FONT_PUNCT_OFFSET + 13;
		case '/':
			return FONT_PUNCT_OFFSET + 14;
		case ':':
			return FONT_PUNCT_OFFSET + 15;
		case ';':
			return FONT_PUNCT_OFFSET + 16;
		case '<':
			return FONT_PUNCT_OFFSET + 17;
		case '=':
			return FONT_PUNCT_OFFSET + 18;
		case '>':
			return FONT_PUNCT_OFFSET + 19;
		case '?':
			return FONT_PUNCT_OFFSET + 20;
		case '[':
			return FONT_PUNCT_OFFSET + 21;
		case '\\':
			return FONT_PUNCT_OFFSET + 22;
		case ']':
			return FONT_PUNCT_OFFSET + 23;
		case '^':
			return FONT_PUNCT_OFFSET + 24;									
		case '_':
			return FONT_PUNCT_OFFSET + 25;									
	};

	/* if no character was found,
		we return a special code */
	return 0xFF;
}

//---------------------------------------------------------------------------------
u8 drawString(const char *str) {
	for (fade = 0; fade < 3; fade++) {
		faded_idx = current_char_idx + fade;
		c = str[faded_idx];

		if (fade == 0 && c == 0)
			return 0;

		if (c != ' ') {
			i = charToTileIndex(c);
			if ( (faded_idx < current_string_len) && (i != 0xFF) ) {
				txtLine[current_char_x + fade]=i+ (FONT_LINE_OFFSET * fade) + (1<<13); // priority high
			}
			vblrefresh=1;
		}
	}

	current_char_x++;
	current_char_idx++;
	return 1;
}

//---------------------------------------------------------------------------------
void updateLineWriter(void) {
	switch(writer_state) {
		case WRT_CENTER_CUR_LINE:
			current_string_len = strlen(demo_strings[current_string_idx]);
			current_char_x = ((256 / 8) - current_string_len) >> 1;
			writer_state = WRT_WRITE_CUR_LINE;
			break;

		case WRT_WRITE_CUR_LINE:
			if (drawString(demo_strings[current_string_idx])==0)  {
				writer_timer = 0;
				writer_state = WRT_WAIT;
			}
			break;

		case WRT_WAIT:
			if (writer_timer++ > 50) {
				writer_state = WRT_CLEAR_LINE;
				current_char_x = 0;
			}
			break;

		case WRT_CLEAR_LINE:
			txtLine[current_char_x]=0x0000;
			vblrefresh=1;
			current_char_x++;
			if (current_char_x > (256 >> 3) ) {
				current_char_x = 0;
				current_char_idx = 0;
				current_string_idx++;
				if (demo_strings[current_string_idx][0] == '\0')
					current_string_idx = 0;

				writer_state = WRT_CENTER_CUR_LINE;
			}
			break;
	}		
}

//---------------------------------------------------------------------------------
void hdmaScroll(void) {
	REG_HDMAEN = 0; // Disable HDMA

	REG_DMAP6 = 0x02; // Meaning write twice 010
	REG_BBAD6 = 0x0F; // BG2 horizontal scrolling
	data_to_transfert.mem.p = (u8 *) scroll_bg2;
	REG_A1T6LH = data_to_transfert.mem.c.addr; // DMA channel x source address offset low $4712 and high $4717 optimisation)
	REG_A1B6 = data_to_transfert.mem.c.bank; // DMA channel x source address bank

	REG_HDMAEN = 0x40; // Enable DMA channel 6
}

//---------------------------------------------------------------------------------
void myconsoleVblank(void) {
	// Put screen regarding how to put it
	if (vblrefresh ==1) {
		dmaCopyVram((u8 *) (txtLine), MAP0ADR+32*27,32*2);
		vblrefresh=0;
	}
}

//---------------------------------------------------------------------------------
// Main init of sound
void soundInit(void) {
	// Set give soundbank
	//spcSetBank(&__SOUNDBANK__1);
	spcSetBank(&SOUNDBANK__0);
	
	// allocate around 10K of sound ram (39 256-byte blocks)
	spcAllocateSoundRegion(0);
	spcStop(); 
}

//---------------------------------------------------------------------------------
// Main init of snes graphics
void gfxInit(void) {
	// init sprites 
	oamInit();
	vblrefresh=0;
	
	nmiSet(myconsoleVblank); 

	spcProcess();
	setBrightness(0); // Force VBlank
}

//---------------------------------------------------------------------------------
// display a screen regarding the current progress
// 16-17->2006 19-20->2007 22-23->2008 25-26->2010 28-29->2011 31-32->2012 34-35->2016 37-38-> 2018
void showCurrentRGC(void) {
	// flip flop to know if we do the fade or the display
	if (rgc_counter & 1) {
		setFadeEffect(FADE_IN);
		figure_counter=640; // to go quickly to next step
		rgc_counter++;
	}
	else {
		// display current event
		pEvent=(_rgcevent *) &events[rgc_counter>>1];

		setFadeEffect(FADE_OUT);
		spcProcess();	setBrightness(0); // Force VBlank
		bgSetDisable(1);
		dmaCopyVram(pEvent->gfx, GFXMAP0ADR, (pEvent->gfxend-pEvent->gfx));
		dmaCopyCGram(pEvent->gfxp, 2 * 16, 16*2*5);
		dmaCopyVram(pEvent->mapL1, MAP0ADR, 32*32*2);
		figure_counter=640; // to go quickly to next step
		rgc_counter++;
	}
}

//---------------------------------------------------------------------------------
int main(void) {
	// Initialize SNES 
	consoleInit();

	// Initialize sound engine (take some time)
	spcBoot();
	
	// Init sound & graphic mode for SNES
	soundInit();
	gfxInit();
	
	// Load the tiles & font
	bgInitTileSet(0, (u8 *) &logog, (u8 *) &logop, 2, ((u8 *) &logog_end - (u8 *) &logog), 16*2*2, BG_16COLORS, GFXMAP0ADR);
	bgInitTileSet(1, (u8 *) &starsg, (u8 *) &starsp, 1, ((u8 *) &starsg_end - (u8 *) &starsg), 16*2*1, BG_16COLORS, GFXMAP1ADR);
	setBrightness(0x0); 
	dmaCopyVram(&fontg, GFXMAP0ADR+FONTADR/2, (&fontg_end-&fontg));
	dmaCopyCGram(&fontp, 0 * 16, 16*2);

	// Copy Map to VRAM
	bgInitMapSet(0, &logom, 32*32*2,SC_32x32, MAP0ADR);
	bgInitMapSet(1, &starsm, 64*32*2,SC_64x32, MAP1ADR);

	// Init sprites
	oamInitGfxSet(&spriteg, (&spriteg_end-&spriteg), &spritep, 16*2*2, 0, GFXADRSPR, OBJ_SIZE32_L64);
	for(i = 0; i < MAX_SPRITES; i++) {
		oamSetAttr(i<<2,  0, 0, 0, 2<<4); 
		oamSetVisible(i<<2, OBJ_SHOW);
	}
	
	// Now Put in 16 color mode and disable other BGs except 1st one
	setMode(BG_MODE1,0);  bgSetEnable(1); bgSetDisable(2);
	
	//	Create the scrolling offset table 
	s = 1;
	for(i = 0; i < TABLE_LEN; i++) {
		scroll_bg2[i*3] = 3;
		do
		{
			ns = ((rand() % 3) + 1);
		} while (ns == s);
		scroll_speed[i] = ns;
		s = ns;
	}
	scroll_bg2[TABLE_LEN]=0x00;// init end of hdma table
	
	for (i=0;i<32;i++)
		txtLine[i]=0x0000;
	
	// Init vars
	figure_counter = 0;
	figure_mode=0;
	demo_phase = 0;
	phase_counter = 0;
	writer_switch = 0;
	writer_state = WRT_CENTER_CUR_LINE;		
	current_string_idx = 0;
	current_char_x = 0;
	current_char_idx = 0;

	// play music now
	spcLoad(0); spcPlay(0);
	
	// Infinite loop to keep the program running
	// TEST	figure_mode=13;
	s = 0;
	while(1) {
		switch(demo_phase) {
			case 0:
				setFadeEffect(FADE_IN);
				phase_counter = 0;
				demo_phase++;
				break;

			case 1:
				phase_counter++;
				if (phase_counter > 32 + 16) {
					phase_counter = 0;
					demo_phase++;
				}
				break;
			case 2:
				phase_counter++;
				if (phase_counter > 32 + 16) {
					phase_counter = 0;
					demo_phase++;
				}
				break;
		}

		// do starfiled and sprites only for some cases
		if (figure_mode<13) {
			// update text if possible
			if (demo_phase > 2) {
				if ( (writer_switch!=0) || (writer_state == WRT_CLEAR_LINE) )
					updateLineWriter();
				writer_switch = 1-writer_switch;					
			}

			// 	Scroll the starfield 
			hdmaScroll();
			ptscr=(u8 *) &(scroll_bg2+1);
			ptspd=(u8 *) &scroll_speed;
			for(i = 0; i < TABLE_LEN; i++) {
				*ptscr=(*ptscr+*ptspd) & 0xFF;
				ptspd++;
				ptscr=ptscr+3;
			}

			//	Animate the sprites
			for(i = 0; i < MAX_SPRITES; i++) {
				switch(figure_mode) {
					case 0:
					case 9:
						oamSetAttr(i<<2, (cosFix16(s + (i << 5)) << 1) + 128 - 16, sinFix16(s + (i << 5)) + 112 - 16, sprIdx[(( i) & 7)], 2<<4);
						break;
					case 1:
					case 10:
						oamSetAttr(i<<2, (cosFix16(s + (i << 6)) << 1) + 128 - 16, (sinFix16(s + (i << 5))) + 112 - 16, sprIdx[((( i) & 7))+8], (1<<1) | (2<<4));
						break;
					case 2:
					case 11:
						oamSetAttr(i<<2, ((sinFix16((s << 1) + (i << 6))) << 1) + 128 - 16, (cosFix16(s + (i << 5)) << 1) + 112 - 16, sprIdx[(( i) & 7)], 2<<4);
						break;
					case 3:
					case 12:
						oamSetAttr(i<<2, (sinFix16(s + (i << 7))) + 128 - 16, (cosFix16((s >> 1) + (i << 4)) << 1) + 112 - 16, sprIdx[((( i) & 7))+8], (1<<1) | (2<<4));
						break;
					case 4:
						oamSetAttr(i<<2, (cosFix16((s << 1) + (i << 5)) << 1) + 128 - 16, (sinFix16((s >> 1) + (i << 5)) << 1) + 112 - 16, sprIdx[(( i) & 7)], 2<<4);
						break;
					case 5:
						oamSetAttr(i<<2, (cosFix16((s << 1) + (i << 5)) << 1) + 128 - 16, (sinFix16((s >> 1) + (i << 5)) << 1) + 112 - 16, sprIdx[((( i) & 7))+8], (1<<1) | (2<<4));
						break;
					case 6:
						oamSetAttr(i<<2, (cosFix16((s << 1) + (i << 5)) << 1) + 128 - 16, (sinFix16((s >> 1) + (i << 5)) << 1) + 112 - 16, sprIdx[(( i) & 7)], 2<<4);
						break;
					case 7:
						oamSetAttr(i<<2, ((sinFix16((s << 1) + (i << 6))) << 1) + 128 - 16, (cosFix16(s + (i << 5)) << 1) + 112 - 16, sprIdx[((( i) & 7))+8], (1<<1) | (2<<4));
						break;
					case 8:
						oamSetAttr(i<<2, (cosFix16(s + (i << 6)) << 1) + 128 - 16, (sinFix16(s + (i << 5))) + 112 - 16, sprIdx[(( i) & 7)], 2<<4);
						break;
				}
			}
		}
		if (figure_mode==13) {
			setFadeEffect(FADE_OUT);
			spcProcess();	setBrightness(0); // Force VBlank
			bgSetDisable(1);
			for(i = 0; i < MAX_SPRITES; i++) {
				oamSetXY(i<<2,  256, 240); 
			}
			dmaCopyVram(&firstonesg, GFXMAP0ADR, (&firstonesg_end-&firstonesg));
			dmaCopyCGram(&firstonesp, 2 * 16, 16*2*5);
			dmaCopyVram(&firstonesm, MAP0ADR, 32*32*2);
			figure_counter=640; // to go quickly to next step
		}
		else if (figure_mode==14) {
			// display 1st event with a fade effect
			setFadeEffect(FADE_IN);
			figure_counter=640; // to go quickly to next step
			rgc_counter=0;	// to begin correct rgc presentation
		}
		// 16-17->2006 19-20->2007 22-23->2008 25-26->2010 28-29->2011 31-32->2012 34-35->2016 37-38-> 2018
		else if ((figure_mode>=16) &&  (figure_mode<=38)) {
			if ((figure_mode!=18) && (figure_mode!=21) && (figure_mode!=24) && (figure_mode!=27) && (figure_mode!=30) && (figure_mode!=33) && (figure_mode!=36) && (figure_mode!=39)) // bad !
				showCurrentRGC();
		}
		else if (figure_mode==FIRSTDISPAGAIN-3) {
			// display last event with a fade effect
			setFadeEffect(FADE_OUT);
			spcProcess();	setBrightness(0); // Force VBlank
			bgSetDisable(1);
			dmaCopyVram(&lastonesg, GFXMAP0ADR, (&lastonesg_end-&lastonesg));
			dmaCopyCGram(&lastonesp, 2 * 16, 16*2*5);
			dmaCopyVram(&lastonesm, MAP0ADR, 32*32*2);
			figure_counter=640; // to go quickly to next step
		}
		else if (figure_mode==FIRSTDISPAGAIN-2) {
			// display last event with a mosaic effect
			setFadeEffect(FADE_IN);
			figure_counter=640; // to go quickly to next step
		}
		else if (figure_mode==FIRSTDISPAGAIN) {
			// again 1st screen
			setFadeEffect(FADE_OUT);
			spcProcess();	setBrightness(0); // Force VBlank
			bgSetEnable(1);
			dmaCopyVram(&logog, GFXMAP0ADR, (&logog_end-&logog));
			dmaCopyCGram(&logop, 2 * 16, 16*2*2);
			dmaCopyVram(&logom, MAP0ADR, 32*32*2);
			dmaCopyVram(&fontg, GFXMAP0ADR+FONTADR/2, (&fontg_end-&fontg));
			dmaCopyVram(&starsg, GFXMAP1ADR, (&starsg_end-&starsg));
			figure_counter=640; // to go quickly to next step
		}
		
		// update counters for sprites
		s += 4;
		figure_counter++;
		if (figure_counter > 640) {
			figure_mode++;
			if (figure_mode > FIRSTDISPAGAIN) { figure_mode = 0; setFadeEffect(FADE_IN); }
			figure_counter = 0;
		}	
		
		// Wait refresh
		spcProcess();WaitForVBlank();
	}
	return 0;
}
