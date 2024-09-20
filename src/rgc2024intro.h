#ifndef _GFXS_H_
#define _GFXS_H_

#include <string.h>

#define	TABLE_LEN 74
#define MAX_SPRITES 16

#define MAP0ADR			0x7000 // 0x7000
#define MAP1ADR			0x7400 // 0x7400

#define GFXMAP0ADR	0x3000
#define GFXMAP1ADR	0x6000
#define GFXADRSPR		0x0000

#define	FONTADR			0x4000	// 0x1000 indexed from MAP0 

#define WRT_CENTER_CUR_LINE 0
#define WRT_WRITE_CUR_LINE 1
#define WRT_WAIT 2
#define WRT_CLEAR_LINE 3

#define FONT_OFFSET 			0x200
#define FONT_PUNCT_OFFSET 0x224
#define FONT_LINE_OFFSET ((504 >> 3) - 1)

#define PLAN_B_TILE_H 20
#define PLAN_A_TILE_H 10

#endif
