#include "fonts.h"

#include <avr/pgmspace.h>

#if defined(__AVR__)
	#include <avr/pgmspace.h>
	#define fontdatatype const uint8_t
#elif defined(__PIC32MX__)
	#define PROGMEM
	#define fontdatatype const unsigned char
#elif defined(__arm__)
	#define PROGMEM
	#define fontdatatype const unsigned char
#endif

fontdatatype font_cp1251_0508[] PROGMEM = {
	0x00, 0x05, 0x08, // count, width, height 
//const uint8_t font_cp1251_08[] PROGMEM = {
	0x00, 0x00, 0x00, VOID, VOID,		/* 0x20 =>   * fixed: 4-> 3 pixels/ 
	0x5F, VOID, VOID, VOID, VOID,		/* 0x21 => ! */
	0x07, 0x00, 0x07, VOID, VOID,		/* 0x22 => " */
	0x14, 0x7F, 0x14, 0x7F, 0x14,		/* 0x23 => # */
	0x24, 0x2A, 0x7F, 0x2A, 0x12,		/* 0x24 => $ */
	0x23, 0x13, 0x08, 0x64, 0x62,		/* 0x25 => % */
	0x36, 0x49, 0x55, 0x22, 0x50,		/* 0x26 => & */
	0x05, 0x03, VOID, VOID, VOID,		/* 0x27 => ' */
	0x1C, 0x22, 0x41, VOID, VOID,		/* 0x28 => ( */
	0x41, 0x22, 0x1C, VOID, VOID,		/* 0x29 => ) */
	0x14, 0x08, 0x3E, 0x08, 0x14,		/* 0x2A => * */
	0x08, 0x08, 0x3E, 0x08, 0x08,		/* 0x2B => + */
	0x80, 0x40, VOID, VOID, VOID,		/* 0x2C => , */
	0x08, 0x08, 0x08, 0x08, VOID,		/* 0x2D => - */
	0x40, VOID, VOID, VOID, VOID,		/* 0x2E => . */
	0x20, 0x10, 0x08, 0x04, 0x02,		/* 0x2F => / */

	0x3E, 0x41, 0x41, 0x3E, VOID,		/* 0x30 => 0 */
	0x00, 0x42, 0x7F, 0x40, VOID,		/* 0x31 => 1 */
	0x42, 0x61, 0x51, 0x4E, VOID,		/* 0x32 => 2 */
	0x22, 0x41, 0x49, 0x36, VOID,		/* 0x33 => 3 */
	0x18, 0x14, 0x12, 0x7F, VOID,		/* 0x34 => 4 */
	0x27, 0x45, 0x45, 0x39, VOID,		/* 0x35 => 5 */
	0x3E, 0x49, 0x49, 0x32, VOID,		/* 0x36 => 6 */
	0x01, 0x71, 0x09, 0x07, VOID,		/* 0x37 => 7 */
	0x36, 0x49, 0x49, 0x36, VOID,		/* 0x38 => 8 */
	0x26, 0x49, 0x49, 0x3E, VOID,		/* 0x39 => 9 */
	0x24, VOID, VOID, VOID, VOID,		/* 0x3A => : */
	0x40, 0x24, VOID, VOID, VOID,		/* 0x3B => ; */
	0x08, 0x14, 0x22, 0x41, VOID,		/* 0x3C => < */
	0x14, 0x14, 0x14, 0x14, 0x14,		/* 0x3D => = */
	0x41, 0x22, 0x14, 0x08, VOID,		/* 0x3E => > */
	0x02, 0x01, 0x51, 0x09, 0x06,		/* 0x3F => ? */

	0x3E, 0x41, 0x5D, 0x55, 0x1E,		/* 0x40 => @ */
	0x7E, 0x11, 0x11, 0x11, 0x7E,		/* 0x41 => A */
	0x7F, 0x49, 0x49, 0x49, 0x36,		/* 0x42 => B */
	0x3E, 0x41, 0x41, 0x41, 0x22,		/* 0x43 => C */
	0x7F, 0x41, 0x41, 0x22, 0x1C,		/* 0x44 => D */
	0x7F, 0x49, 0x49, 0x49, 0x41,		/* 0x45 => E */
	0x7F, 0x09, 0x09, 0x09, 0x01,		/* 0x46 => F */
	0x3E, 0x41, 0x49, 0x49, 0x7A,		/* 0x47 => G */
	0x7F, 0x08, 0x08, 0x08, 0x7F,		/* 0x48 => H */
	0x41, 0x7F, 0x41, VOID, VOID,		/* 0x49 => I */
	0x20, 0x40, 0x41, 0x3F, 0x01,		/* 0x4A => J */
	0x7F, 0x08, 0x14, 0x22, 0x41,		/* 0x4B => K */
	0x7F, 0x40, 0x40, 0x40, VOID,		/* 0x4C => L */
	0x7F, 0x02, 0x0C, 0x02, 0x7F,		/* 0x4D => M */
	0x7F, 0x04, 0x08, 0x10, 0x7F,		/* 0x4E => N */
	0x3E, 0x41, 0x41, 0x41, 0x3E,		/* 0x4F => O */

	0x7F, 0x09, 0x09, 0x09, 0x06,		/* 0x50 => P */
	0x3E, 0x41, 0x51, 0x21, 0x5E,		/* 0x51 => Q */
	0x7F, 0x09, 0x19, 0x29, 0x46,		/* 0x52 => R */
	0x26, 0x49, 0x49, 0x49, 0x32,		/* 0x53 => S */
	0x01, 0x01, 0x7F, 0x01, 0x01,		/* 0x54 => T */
	0x3F, 0x40, 0x40, 0x40, 0x3F,		/* 0x55 => U */
	0x07, 0x18, 0x60, 0x18, 0x07,		/* 0x56 => V */
	0x3F, 0x40, 0x38, 0x40, 0x3F,		/* 0x57 => W */
	0x63, 0x14, 0x08, 0x14, 0x63,		/* 0x58 => X */
	0x07, 0x08, 0x70, 0x08, 0x07,		/* 0x59 => Y */
	0x61, 0x51, 0x49, 0x45, 0x43,		/* 0x00 => Z */
	0x7F, 0x41, 0x41, VOID, VOID,		/* 0x5B => [ */
	0x18, 0x24, 0x7E, 0x24, 0x10,		/* 0x5C => ¢ */
	0x41, 0x41, 0x7F, VOID, VOID,		/* 0x5D => ] */
	0x04, 0x02, 0x01, 0x02, 0x04,		/* 0x5E => ^ */
	0x40, 0x40, 0x40, 0x40, 0x40,		/* 0x5F => - */

	0x01, 0x02, VOID, VOID, VOID,		/* 0x60 => ` */
	0x20, 0x54, 0x54, 0x54, 0x78,		/* 0x61 => a */
	0x7F, 0x48, 0x44, 0x44, 0x38,		/* 0x62 => b */
	0x38, 0x44, 0x44, 0x44, 0x20,		/* 0x63 => c */
	0x38, 0x44, 0x44, 0x48, 0x7F,		/* 0x64 => d */
	0x38, 0x54, 0x54, 0x54, 0x18,		/* 0x65 => e */
	0x08, 0x7E, 0x09, 0x01, 0x02,		/* 0x66 => f */
	0x18, 0xA4, 0xA4, 0xA4, 0x7C,		/* 0x67 => g */
	0x7F, 0x08, 0x04, 0x04, 0x78,		/* 0x68 => h */
	0x44, 0x7D, 0x40, VOID, VOID,		/* 0x69 => i */
	0x40, 0x80, 0x84, 0x7D, VOID,		/* 0x6A => j */
	0x7F, 0x10, 0x28, 0x44, VOID,		/* 0x6B => k */
	0x41, 0x7F, 0x40, VOID, VOID,		/* 0x6C => l */
	0x7C, 0x04, 0x18, 0x04, 0x78,		/* 0x6D => m */
	0x7C, 0x08, 0x04, 0x78, VOID,		/* 0x6E => n */
	0x38, 0x44, 0x44, 0x44, 0x38,		/* 0x6F => o */

	0xFC, 0x24, 0x44, 0x44, 0x38,		/* 0x70 => p */
	0x38, 0x44, 0x44, 0x24, 0xFC,		/* 0x71 => q */
	0x7C, 0x08, 0x04, 0x08, VOID,		/* 0x72 => r */
	0x08, 0x54, 0x54, 0x54, 0x20,		/* 0x73 => s */
	0x04, 0x3F, 0x44, 0x40, 0x20,		/* 0x74 => t */
	0x3C, 0x40, 0x40, 0x20, 0x7C,		/* 0x75 => u */
	0x0C, 0x30, 0x40, 0x30, 0x0C,		/* 0x76 => v */
	0x3C, 0x40, 0x30, 0x40, 0x3C,		/* 0x77 => w */
	0x44, 0x28, 0x10, 0x28, 0x44,		/* 0x78 => x */
	0x0C, 0x50, 0x50, 0x50, 0x3C,		/* 0x79 => y */
	0x44, 0x64, 0x54, 0x4C, 0x44,		/* 0x7A => z */
	0x08, 0x36, 0x41, VOID, VOID,		/* 0x7B => { */
	0x7F, VOID, VOID, VOID, VOID,		/* 0x7C => | */
	0x41, 0x36, 0x08, VOID, VOID,		/* 0x7D => } */
	0x08, 0x04, 0x08, 0x04, VOID,		/* 0x7E => ~ */
	0x00, VOID, VOID, VOID, VOID,		/* 0x7F =>   */

//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x80 =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x81 =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x82 =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x83 =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x84 =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x85 =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x86 =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x87 =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x88 =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x89 =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x8A =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x8B =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x8C =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x8D =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x8E =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x8F =>  */

//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x90 =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x91 =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x92 =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x93 =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x94 =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x95 =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x96 =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x97 =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x98 =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* IDLE =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x9A =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x9B =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x9C =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x9D =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x9E =>  */
//	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0x9F =>  */

	0x20, 0x3C, 0x7E, 0x3C, 0x20,		/* 0xA0 => BELL  = font[0x60] */
	0x06, 0x49, 0x4A, 0x49, 0x36,		/* 0xA1 => Ў */
	0x0C, 0x51, 0x52, 0x51, 0x3C,		/* 0xA2 => ў */
	0x20, 0x40, 0x41, 0x3F, 0x01,		/* 0xA3 => Ј */
	0x2A, 0x1C, 0x77, 0x1C, 0x2A,		/* 0xA4 => ¤ */
	0x7E, 0x02, 0x02, 0x02, 0x03,		/* 0xA5 => Ґ */
	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0xA6 =>  */
	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0xA7 =>  */
	0x7E, 0x4B, 0x4A, 0x4B, 0x42,		/* 0xA8 => Ё */
	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0xA9 =>  */
	0x3E, 0x49, 0x49, 0x41, 0x22,		/* 0xAA => Є */
	0x08, 0x14, 0x2A, 0x14, 0x22,		/* 0xAB => « */
	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0xAC =>  */
	0x3C, 0x4A, 0x72, 0x42, 0x3C,		/* 0xAD => CLOCK */
	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0xAE =>  */
	0x41, 0x7E, 0x41, VOID, VOID,		/* 0xAF => Ї */

	0x00, 0x06, 0x09, 0x09, 0x06,		/* 0xB0 => °  = font [0x70] */   
	0x48, 0x48, 0x5F, 0x48, 0x48,		/* 0xB1 => ± */
	0x41, 0x7F, 0x41, VOID, VOID,		/* 0xB2 => І */
	0x44, 0x7D, 0x40, VOID, VOID,		/* 0xB3 => і */
	0x7C, 0x04, 0x04, 0x0D, VOID,		/* 0xB4 => ґ */
	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0xB5 =>  */
	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0xB6 =>  */
	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0xB7 =>  */
	0x38, 0x55, 0x54, 0x55, 0x18,		/* 0xB8 => ё */
	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0xB9 =>  */
	0x38, 0x54, 0x54, 0x44, 0x28,		/* 0xBA => є */
	0x22, 0x14, 0x2A, 0x14, 0x08,		/* 0xBB => » */
	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0xBC =>  */
	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0xBD =>  */
	0x7F, 0x7F, 0x7F, 0x7F, 0x7F,		/* 0xBE =>  */
	0x45, 0x7C, 0x45, VOID, VOID,		/* 0xBF => ї */

	0x7E, 0x11, 0x11, 0x11, 0x7E,		/* 0xC0 => А  = font [0x80]*/
	0x7F, 0x49, 0x49, 0x49, 0x31,		/* 0xC1 => Б */
	0x7F, 0x49, 0x49, 0x49, 0x36,		/* 0xC2 => В */
	0x7F, 0x01, 0x01, 0x01, 0x03,		/* 0xC3 => Г */
	0xC0, 0x7E, 0x41, 0x7F, 0xC0,		/* 0xC4 => Д */
	0x7F, 0x49, 0x49, 0x49, 0x41,		/* 0xC5 => Е */
	0x77, 0x08, 0x7F, 0x08, 0x77,		/* 0xC6 => Ж */
	0x41, 0x49, 0x49, 0x49, 0x36,		/* 0xC7 => З */
	0x7F, 0x10, 0x08, 0x04, 0x7F,		/* 0xC8 => И */
	0x7E, 0x20, 0x13, 0x08, 0x7E,		/* 0xC9 => Й */
	0x7F, 0x08, 0x14, 0x22, 0x41,		/* 0xCA => К */
	0x40, 0x3C, 0x02, 0x01, 0x7F,		/* 0xCB => Л */
	0x7F, 0x02, 0x0C, 0x02, 0x7F,		/* 0xCC => М */
	0x7F, 0x08, 0x08, 0x08, 0x7F,		/* 0xCD => Н */
	0x3E, 0x41, 0x41, 0x41, 0x3E,		/* 0xCE => О */
	0x7F, 0x01, 0x01, 0x01, 0x7F,		/* 0xCF => П */

	0x7F, 0x09, 0x09, 0x09, 0x06,		/* 0xD0 => Р */
	0x3E, 0x41, 0x41, 0x41, 0x22,		/* 0xD1 => С */
	0x01, 0x01, 0x7F, 0x01, 0x01,		/* 0xD2 => Т */
	0x07, 0x48, 0x48, 0x48, 0x3F,		/* 0xD3 => У */
	0x3C, 0x42, 0xFF, 0x42, 0x3C,		/* 0xD4 => Ф */
	0x63, 0x14, 0x08, 0x14, 0x63,		/* 0xD5 => Х */
	0x7F, 0x40, 0x40, 0x7F, 0xC0,		/* 0xD6 => Ц */
	0x07, 0x08, 0x08, 0x08, 0x7F,		/* 0xD7 => Ч */
	0x7F, 0x40, 0x7F, 0x40, 0x7F,		/* 0xD8 => Ш */
	0x7F, 0x40, 0x7F, 0x40, 0xFF,		/* 0xD9 => Щ */
	0x01, 0x7F, 0x48, 0x48, 0x30,		/* 0xDA => Ъ */
	0x7F, 0x48, 0x30, 0x00, 0x7F,		/* 0xDB => Ы */
	0x7F, 0x48, 0x44, 0x44, 0x38,		/* 0xDC => Ь */
	0x22, 0x41, 0x49, 0x49, 0x3E,		/* 0xDD => Э */
	0x7F, 0x08, 0x3E, 0x41, 0x3E,		/* 0xDE => Ю */
	0x46, 0x29, 0x19, 0x09, 0x7F,		/* 0xDF => Я */

	0x20, 0x54, 0x54, 0x54, 0x78,		/* 0xE0 => а */
	0x3C, 0x4A, 0x4A, 0x49, 0x30,		/* 0xE1 => б */
	0x7C, 0x54, 0x54, 0x28, VOID,		/* 0xE2 => в */
	0x7C, 0x04, 0x04, 0x0C, VOID,		/* 0xE3 => г */
	0xC0, 0x78, 0x44, 0x7C, 0xC0,		/* 0xE4 => д */
	0x38, 0x54, 0x54, 0x54, 0x18,		/* 0xE5 => е */
	0x6C, 0x10, 0x7C, 0x10, 0x6C,		/* 0xE6 => ж */
	0x44, 0x54, 0x54, 0x28, VOID,		/* 0xE7 => з */
	0x7C, 0x20, 0x10, 0x08, 0x7C,		/* 0xE8 => и */
	0x7C, 0x21, 0x12, 0x09, 0x7C,		/* 0xE9 => й */
	0x7C, 0x10, 0x28, 0x44, VOID,		/* 0xEA => к */
	0x70, 0x08, 0x04, 0x7C, VOID,		/* 0xEB => л */
	0x7C, 0x08, 0x10, 0x08, 0x7C,		/* 0xEC => м */
	0x7C, 0x10, 0x10, 0x7C, VOID,		/* 0xED => н */
	0x38, 0x44, 0x44, 0x44, 0x38,		/* 0xEE => о */
	0x7C, 0x04, 0x04, 0x7C, VOID,		/* 0xEF => п */

	0xFC, 0x24, 0x44, 0x44, 0x38,		/* 0xF0 => р */
	0x38, 0x44, 0x44, 0x44, 0x20,		/* 0xF1 => с */
	0x04, 0x04, 0x7C, 0x04, 0x04,		/* 0xF2 => т */
	0x0C, 0x50, 0x50, 0x50, 0x3C,		/* 0xF3 => у */
	0x30, 0x48, 0xFC, 0x48, 0x30,		/* 0xF4 => ф */
	0x44, 0x28, 0x10, 0x28, 0x44,		/* 0xF5 => х */
	0x7C, 0x40, 0x40, 0x7C, 0xC0,		/* 0xF6 => ц */
	0x0C, 0x10, 0x10, 0x7C, VOID,		/* 0xF7 => ч */
	0x7C, 0x40, 0x7C, 0x40, 0x7C,		/* 0xF8 => ш */
	0x7C, 0x40, 0x7C, 0x40, 0xFC,		/* 0xF9 => щ */
	0x04, 0x7C, 0x50, 0x50, 0x20,		/* 0xFA => ъ */
	0x7C, 0x50, 0x20, 0x00, 0x7C,		/* 0xFB => ы */
	0x7C, 0x50, 0x50, 0x20, VOID,		/* 0xFC => ь */
	0x28, 0x44, 0x54, 0x54, 0x38,		/* 0xFD => э */
	0x7C, 0x10, 0x38, 0x44, 0x38,		/* 0xFE => ю */
	0x08, 0x54, 0x34, 0x14, 0x7C,		/* 0xFF => я */
};
