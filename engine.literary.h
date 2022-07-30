
#define B	{0, 0, 0}
#define W	{255, 255, 255}
#define R	{0, 0, 255}
#define DR	{0, 0, 125}
#define LR	{75, 75, 255}
#define G	{0, 255, 0}
#define LG	{125, 255, 125}
#define DG	{25, 145, 25}
#define BLG {80, 170, 45}
#define BL	{255, 0, 0}
#define DBL	{175, 0, 0}
#define LBL {200, 75, 75}
#define Y	{125, 225, 225}
#define GR	{125, 125, 125}
#define DGR	{50, 50, 50}
#define LGR {200, 200, 200}
#define BRN	{25, 135, 215}
#define LBR {95, 195, 250}
#define DBR	{10, 50, 190}
#define PNK	{200, 190, 255}
#define DPNK {190, 80, 220}
#define LPNK {200, 200, 255}
#define X	{235, 235, 235, 0}
#define Z	{0, 0, 0, 0, 1}

#define CLRS {R, G, BL, Y, GR, BRN, PNK, B, W, X};


#define ENGINE_SPRITE_ZERO	{R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R}

#define ENGINE_MAP_TEST				{0.000001, -1, -1, '*', '*',	{{R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R}, 5}}
#define ENGINE_MAP_ZERO				{0.00001, 48, 0, '0', '0',		{{B, B, B, B, B, B, X, X, X, B, B, B, B, B, B, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_ONE				{0.00002, 49, 1, '1', '1',		{{X, B, X, X, X, B, B, B, B, B, X, B, X, X, B, R, G, B, R, G, B, R, G, B, R}, 2}}
#define ENGINE_MAP_TWO				{0.00003, 50, 2, '2', '2',		{{B, X, B, B, B, B, X, B, X, B, B, B, B, X, B, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_THREE			{0.00004, 51, 3, '3', '3',		{{B, X, B, X, B, B, X, B, X, B, B, B, B, B, B, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_FOUR				{0.00005, 52, 4, '4', '4',		{{B, B, B, X, X, X, X, B, X, X, B, B, B, B, B, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_FIVE				{0.00006, 53, 5, '5', '5',		{{B, B, B, X, B, B, X, B, X, B, B, X, B, B, B, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_SIX				{0.00007, 54, 6, '6', '6',		{{X, B, B, B, B, B, X, B, X, B, X, X, B, B, B, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_SEVEN			{0.00008, 55, 7, '7', '7',		{{B, X, X, X, X, B, X, X, B, B, B, B, B, X, X, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_EIGHT			{0.00009, 56, 8, '8', '8',		{{B, B, B, B, B, B, X, B, X, B, B, B, B, B, B, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_NINE				{0.0001, 57, 9, '9', '9',		{{B, B, B, X, X, B, X, B, X, B, B, B, B, B, B, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_A				{0.00011, 97, -1, 'a', 'A',		{{B, B, B, B, B, B, X, B, X, X, B, B, B, B, B, B, B, B, B, B, B, B, B, B, BL}, 3}}
#define ENGINE_MAP_B				{0.00012, 98, -1, 'b', 'B',		{{B, B, B, B, B, B, X, B, X, B, X, B, X, B, X, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_C				{0.00013, 99, -1, 'c', 'C',		{{X, B, B, B, X, B, X, X, X, B, B, X, X, X, B, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_D				{0.00014, 100, -1, 'd', 'D',	{{B, B, B, B, B, B, X, X, X, B, X, B, B, B, X, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_E				{0.00015, 101, -1, 'e', 'E',	{{B, B, B, B, B, B, X, B, X, B, B, X, X, X, B, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_F				{0.00016, 102, -1, 'f', 'F',	{{B, B, B, B, B, B, X, B, X, X, B, X, X, X, X, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_G				{0.00017, 103, -1, 'g', 'G',	{{X, B, B, B, X, B, X, X, X, B, B, X, B, X, B, X, X, B, B, X, B, R, G, B, R}, 4}}
#define ENGINE_MAP_H				{0.00018, 104, -1, 'h', 'H',	{{B, B, B, B, B, X, X, B, X, X, B, B, B, B, B, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_I				{0.00019, 105, -1, 'i', 'I',	{{B, X, B, B, B, X, X, B, X, X, B, X, X, B, X, R, G, B, R, G, B, R, G, B, R}, 1}}
#define ENGINE_MAP_J				{0.0002, 106, -1, 'j', 'J',		{{X, X, X, B, X, X, X, X, X, B, B, B, B, B, X, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_K				{0.00021, 107, -1, 'k', 'K',	{{B, B, B, B, B, X, X, B, X, X, X, B, X, B, X, B, X, X, X, B, B, R, G, B, R}, 4}}
#define ENGINE_MAP_L				{0.00022, 108, -1, 'l', 'L',	{{B, B, B, B, B, X, X, X, X, B, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R}, 2}}
#define ENGINE_MAP_M				{0.00023, 109, -1, 'm', 'M',	{{B, B, B, B, B, X, B, X, X, X, X, X, B, X, X, X, B, X, X, X, B, B, B, B, B}, 5}}
#define ENGINE_MAP_N				{0.00024, 110, -1, 'n', 'N',	{{B, B, B, B, B, X, B, B, X, X, X, X, B, B, X, B, B, B, B, B, B, R, G, B, R}, 4}}
#define ENGINE_MAP_O				{0.00025, 111, -1, 'o', 'O',	{{B, B, B, B, B, B, X, X, X, B, B, B, B, B, B, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_P				{0.00026, 112, -1, 'p', 'P',	{{B, B, B, B, B, B, X, B, X, X, B, B, B, X, X, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_Q				{0.00027, -1, -1, '\0', '\0',	{{R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_R				{0.00028, 114, -1, 'r', 'R',	{{B, B, B, B, B, B, X, B, B, X, B, B, B, X, B, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_S				{0.00029, 115, -1, 's', 'S',	{{B, B, B, X, B, B, X, B, X, B, B, X, B, B, B, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_T				{0.0003, 116, -1, 't', 'T',		{{B, X, X, X, X, B, B, B, B, B, B, X, X, X, X, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_U				{0.00031, 117, -1, 'u', 'U',	{{B, B, B, B, B, X, X, X, X, B, B, B, B, B, B, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_V				{0.00032, 118, -1, 'v', 'V',	{{B, B, X, X, X, X, X, B, B, X, X, X, X, X, B, X, X, B, B, X, B, B, X, X, X}, 5}}
#define ENGINE_MAP_W				{0.00033, 119, -1, 'w', 'W',	{{B, B, B, X, X, X, X, X, B, B, X, X, B, X, X, X, X, X, B, B, B, B, B, X, X}, 5}}
#define ENGINE_MAP_X				{0.00034, 120, -1, 'x', 'X',	{{B, B, X, B, B, X, X, B, X, X, B, B, X, B, B, X, B, X, B, X, B, X, X, X, B}, 3}}
#define ENGINE_MAP_Y				{0.00035, 121, -1, 'y', 'Y',	{{B, B, X, X, X, X, X, B, B, B, B, B, X, X, X, B, X, X, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_Z				{0.00036, -1, -1, '\0', '\0',	{{R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_SPACE			{0.00037, 32, -1, ' ', ' ',		{{X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, R, G, B, R, G, B, R, G, B, R}, 1}}
#define ENGINE_MAP_QUESTION			{0.00038, 63, -1, '?', '?',		{{B, X, X, X, X, B, X, B, X, B, B, B, B, X, X, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_MINUS			{0.00039, 45, -1, '-', '-',		{{X, X, B, X, X, X, X, B, X, X, X, X, X, X, X, R, G, B, R, G, B, R, G, B, R}, 2}}
#define ENGINE_MAP_PLUS				{0.0004, 43, -1, '+', '+',		{{X, X, B, X, X, X, B, B, B, X, X, X, B, X, X, R, G, B, R, G, B, R, G, B, R}, 3}}
#define ENGINE_MAP_AND				{0.00041, 38, -1, '&', '&',		{{X, B, X, B, X, B, X, B, X, B, B, X, X, B, X, X, X, B, X, B, B, R, G, B, R}, 4}}
#define ENGINE_MAP_EXCLAMATION		{0.00042, 33, -1, '!', '!',		{{B, B, B, X, B, B, X, B, X, B, B, X, X, B, X, X, X, B, X, B, B, R, G, B, R}, 1}}
#define ENGINE_MAP_DOT				{0.00043, 46, -1, '.', '.',		{{X, X, X, X, B, B, X, B, X, B, B, X, X, B, X, X, X, B, X, B, B, R, G, B, R}, 1}}
#define ENGINE_MAP_BRACKET_LEFT		{0.00044, -1, -1, '(', '(',		{{X, B, B, B, X, B, X, X, X, B}, 2}}
#define ENGINE_MAP_BRACKET_RIGHT	{0.00045, -1, -1, ')', ')',		{{B, X, X, X, B, X, B, B, B, X}, 2}}
#define ENGINE_MAP_SLASH_FORWARD	{0.00046, -1, -1, '/', '/',		{{X, X, X, X ,B, X, B, B, B, X, B, X, X, X, X}, 3}}

#define ENGINE_MAP_DUMMY			{0.00050, -1, -1, '\0', '\0',	{{R, W, W, W, W, W, W, W, W, W, W, W, W, W, BL}, 3}}

/*


#define ENGINE_MAP_TEST				{0.000001, -1, -1, '*', '*',	{3, 5, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_ZERO				{0.00001, 48, 0, '0', '0',		{3, 5, B, B, B, B, B, B, X, X, X, B, B, B, B, B, B, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_ONE				{0.00002, 49, 1, '1', '1',		{2, 5, X, B, X, X, X, B, B, B, B, B, X, B, X, X, B, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_TWO				{0.00003, 50, 2, '2', '2',		{3, 5, B, X, B, B, B, B, X, B, X, B, B, B, B, X, B, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_THREE			{0.00004, 51, 3, '3', '3',		{3, 5, B, X, B, X, B, B, X, B, X, B, B, B, B, B, B, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_FOUR				{0.00005, 52, 4, '4', '4',		{3, 5, B, B, B, X, X, X, X, B, X, X, B, B, B, B, B, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_FIVE				{0.00006, 53, 5, '5', '5',		{3, 5, B, B, B, X, B, B, X, B, X, B, B, X, B, B, B, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_SIX				{0.00007, 54, 6, '6', '6',		{3, 5, X, B, B, B, B, B, X, B, X, B, X, X, B, B, B, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_SEVEN			{0.00008, 55, 7, '7', '7',		{3, 5, B, X, X, X, X, B, X, X, B, B, B, B, B, X, X, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_EIGHT			{0.00009, 56, 8, '8', '8',		{3, 5, B, B, B, B, B, B, X, B, X, B, B, B, B, B, B, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_NINE				{0.0001, 57, 9, '9', '9',		{3, 5, B, B, B, X, X, B, X, B, X, B, B, B, B, B, B, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_A				{0.00011, 97, -1, 'a', 'A',		{3, 5, B, B, B, B, B, B, X, B, X, X, B, B, B, B, B, B, B, B, B, B, B, B, B, B, BL}}
#define ENGINE_MAP_B				{0.00012, 98, -1, 'b', 'B',		{3, 5, B, B, B, B, B, B, X, B, X, B, X, B, X, B, X, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_C				{0.00013, 99, -1, 'c', 'C',		{3, 5, X, B, B, B, X, B, X, X, X, B, B, X, X, X, B, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_D				{0.00014, 100, -1, 'd', 'D',	{3, 5, B, B, B, B, B, B, X, X, X, B, X, B, B, B, X, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_E				{0.00015, 101, -1, 'e', 'E',	{3, 5, B, B, B, B, B, B, X, B, X, B, B, X, X, X, B, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_F				{0.00016, 102, -1, 'f', 'F',	{3, 5, B, B, B, B, B, B, X, B, X, X, B, X, X, X, X, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_G				{0.00017, 103, -1, 'g', 'G',	{4, 5, X, B, B, B, X, B, X, X, X, B, B, X, B, X, B, X, X, B, B, X, B, R, G, B, R}}
#define ENGINE_MAP_H				{0.00018, 104, -1, 'h', 'H',	{3, 5, B, B, B, B, B, X, X, B, X, X, B, B, B, B, B, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_I				{0.00019, 105, -1, 'i', 'I',	{1, 5, B, X, B, B, B, X, X, B, X, X, B, X, X, B, X, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_J				{0.0002, 106, -1, 'j', 'J',		{3, 5, X, X, X, B, X, X, X, X, X, B, B, B, B, B, X, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_K				{0.00021, 107, -1, 'k', 'K',	{4, 5, B, B, B, B, B, X, X, B, X, X, X, B, X, B, X, B, X, X, X, B, B, R, G, B, R}}
#define ENGINE_MAP_L				{0.00022, 108, -1, 'l', 'L',	{2, 5, B, B, B, B, B, X, X, X, X, B, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_M				{0.00023, 109, -1, 'm', 'M',	{5, 5, B, B, B, B, B, X, B, X, X, X, X, X, B, X, X, X, B, X, X, X, B, B, B, B, B}}
#define ENGINE_MAP_N				{0.00024, 110, -1, 'n', 'N',	{4, 5, B, B, B, B, B, X, B, B, X, X, X, X, B, B, X, B, B, B, B, B, B, R, G, B, R}}
#define ENGINE_MAP_O				{0.00025, 111, -1, 'o', 'O',	{3, 5, B, B, B, B, B, B, X, X, X, B, B, B, B, B, B, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_P				{0.00026, 112, -1, 'p', 'P',	{3, 5, B, B, B, B, B, B, X, B, X, X, B, B, B, X, X, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_Q				{0.00027, -1, -1, '*', '*',		{3, 5, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_R				{0.00028, 114, -1, 'r', 'R',	{3, 5, B, B, B, B, B, B, X, B, B, X, B, B, B, X, B, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_S				{0.00029, 115, -1, 's', 'S',	{3, 5, B, B, B, X, B, B, X, B, X, B, B, X, B, B, B, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_T				{0.0003, 116, -1, 't', 'T',		{3, 5, B, X, X, X, X, B, B, B, B, B, B, X, X, X, X, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_U				{0.00031, 117, -1, 'u', 'U',	{3, 5, B, B, B, B, B, X, X, X, X, B, B, B, B, B, B, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_V				{0.00032, 118, -1, 'v', 'V',	{5, 5, B, B, X, X, X, X, X, B, B, X, X, X, X, X, B, X, X, B, B, X, B, B, X, X, X}}
#define ENGINE_MAP_W				{0.00033, 119, -1, 'w', 'W',	{5, 5, B, B, B, X, X, X, X, X, B, B, X, X, B, X, X, X, X, X, B, B, B, B, B, X, X}}
#define ENGINE_MAP_X				{0.00034, 120, -1, 'x', 'X',	{3, 5, B, B, X, B, B, X, X, B, X, X, B, B, X, B, B, X, B, X, B, X, B, X, X, X, B}}
#define ENGINE_MAP_Y				{0.00035, 121, -1, 'y', 'Y',	{3, 5, B, B, X, X, X, X, X, B, B, B, B, B, X, X, X, B, X, X, R, G, B, R, G, B, R}}
#define ENGINE_MAP_Z				{0.00036, -1, -1, '*', '*',		{3, 5, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_SPACE			{0.00037, 32, -1, ' ', ' ',		{1, 5, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_QUESTION			{0.00038, 63, -1, '?', '?',		{3, 5, B, X, X, X, X, B, X, B, X, B, B, B, B, X, X, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_MINUS			{0.00039, 45, -1, '-', '-',		{2, 5, X, X, B, X, X, X, X, B, X, X, X, X, X, X, X, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_PLUS				{0.0004, 43, -1, '+', '+',		{3, 5, X, X, B, X, X, X, B, B, B, X, X, X, B, X, X, R, G, B, R, G, B, R, G, B, R}}
#define ENGINE_MAP_AND				{0.00041, 38, -1, '&', '&',		{4, 5, X, B, X, B, X, B, X, B, X, B, B, X, X, B, X, X, X, B, X, B, B, R, G, B, R}}	
#define ENGINE_MAP_EXCLAMATION		{0.00042, 33, -1, '!', '!',		{1, 5, B, B, B, X, B, B, X, B, X, B, B, X, X, B, X, X, X, B, X, B, B, R, G, B, R}}	
#define ENGINE_MAP_DOT				{0.00043, 46, -1, '.', '.',		{1, 5, X, X, X, X, B, B, X, B, X, B, B, X, X, B, X, X, X, B, X, B, B, R, G, B, R}}	

*/

#define ENGINE_TYPO	{ENGINE_MAP_ZERO}
#define ENGINE_TYPOGRAPH			{ENGINE_MAP_ZERO, ENGINE_MAP_ONE, ENGINE_MAP_TWO, ENGINE_MAP_THREE, ENGINE_MAP_FOUR, ENGINE_MAP_FIVE, ENGINE_MAP_SIX, ENGINE_MAP_SEVEN, ENGINE_MAP_EIGHT, ENGINE_MAP_NINE, ENGINE_MAP_A, ENGINE_MAP_B, ENGINE_MAP_C, ENGINE_MAP_D, ENGINE_MAP_E, ENGINE_MAP_F, ENGINE_MAP_G, ENGINE_MAP_H, ENGINE_MAP_I, ENGINE_MAP_J, ENGINE_MAP_K, ENGINE_MAP_L, ENGINE_MAP_M, ENGINE_MAP_N, ENGINE_MAP_O, ENGINE_MAP_P, ENGINE_MAP_Q, ENGINE_MAP_R, ENGINE_MAP_S, ENGINE_MAP_T, ENGINE_MAP_U, ENGINE_MAP_V, ENGINE_MAP_W, ENGINE_MAP_X, ENGINE_MAP_Y, ENGINE_MAP_Z, ENGINE_MAP_SPACE, ENGINE_MAP_QUESTION, ENGINE_MAP_MINUS, ENGINE_MAP_PLUS, ENGINE_MAP_AND, ENGINE_MAP_EXCLAMATION, ENGINE_MAP_DOT, ENGINE_MAP_BRACKET_LEFT, ENGINE_MAP_BRACKET_RIGHT, ENGINE_MAP_SLASH_FORWARD}



#define ENGINE_ZERO		{0.00001, -1, 0, '0', '0', {ENGINE_SPRITE_ZERO, 3}}
#define ENGINE_ONE		{1, '1'}
#define ENGINE_TWO		{2, '2'}
#define ENGINE_THREE	{3, '3'}
#define ENGINE_FOUR		{4, '4'}
#define ENGINE_FIVE		{5, '5'}
#define ENGINE_SIX		{6, '6'}
#define ENGINE_SEVEN	{7, '7'}
#define ENGINE_EIGHT	{8, '8'}
#define ENGINE_NINE		{9, '9'}

#define ENGINE_DUMMY	{-1, '?'}

#define ENGINE_WRIT	{ENGINE_MAP_ZERO}

#define ENGINE_WRITER	{ENGINE_ZERO, ENGINE_ONE, ENGINE_TWO, ENGINE_THREE, ENGINE_FOUR, ENGINE_FIVE, ENGINE_SIX, ENGINE_SEVEN, ENGINE_EIGHT, ENGINE_NINE}


