#include "ssd1306_commands.h"

void SSD1306_command_write(bool is_cmd, unsigned char data, struct i2c_client *i2c_client) {

    unsigned char buf[LEN_COMMANDS] = {0};
    
    buf[0] = is_cmd == true ? 0x00 : 0x40;
    
    buf[1] = data;
    
    i2c_master_send(i2c_client, buf, LEN_COMMANDS);
}


/*
 =====================================
 =   1. Fundamental Command Table    =
 =====================================
*/

/*
Set Contrast Control

Double byte command to select 1 out of 256
contrast steps. Contrast increases as the value
increases. (RESET = 7Fh )

+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
*/
void SSD1306_command_contrast(unsigned char contrast, struct i2c_client  *i2c_client){
    SSD1306_command_write(true, 0x81, i2c_client);
    SSD1306_command_write(true, contrast, i2c_client);
}

/*
Entire Display ON

A4h, X0=0b: Resume to RAM content display (RESET) Output follows RAM content
A5h, X0=1b: Entire display ON Output ignores RAM content

+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
|  1 |  0 |  1 |  0 | 0  | 1  | 0  | X0 |
+----+----+----+----+----+----+----+----+
*/
void SSD1306_command_entire_on(bool is_all_on, struct i2c_client  *i2c_client){
    if(is_all_on)
        SSD1306_command_write(true, 0xA5, i2c_client);
    else
        SSD1306_command_write(true, 0xA4, i2c_client);
}

/*
Set Normal/Inverse Display 

A6h, X[0]=0b: Normal display (RESET)
 0 in RAM: OFF in display panel
 1 in RAM: ON in display panel
A7h, X[0]=1b: Inverse display
 0 in RAM: ON in display panel
 1 in RAM: OFF in display panel 

+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
|  1 |  0 |  1 |  0 | 0  | 1  | 1  | X0 |
+----+----+----+----+----+----+----+----+
*/
void SSD1306_command_inverse_disp(bool is_inverse, struct i2c_client  *i2c_client){
    if(is_inverse)
        SSD1306_command_write(true, 0xA7, i2c_client);
    else
        SSD1306_command_write(true, 0xA6, i2c_client);
}

/*
Set Display ON/OFF

AEh, X[0]=0b:Display OFF (sleep mode) (RESET)
AFh, X[0]=1b:Display ON in normal mode 

+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
|  1 |  0 |  1 |  0 | 1  | 1  | 1  | X0 |
+----+----+----+----+----+----+----+----+
*/
void SSD1306_command_turnon(bool is_on, struct i2c_client  *i2c_client) {
    if(is_on)
        SSD1306_command_write(true, 0xAF, i2c_client);
    else
        SSD1306_command_write(true, 0xAE, i2c_client);
}


/*
 ====================================
 =   2. Scrolling Command Table     =
 ====================================
*/

/*
Continuous Horizontal Scroll Setup

26h, X[0]=0, Right Horizontal Scroll
27h, X[0]=1, Left Horizontal Scroll (Horizontal scroll by 1 column)
A[7:0] : Dummy byte (Set as 00h)
B[2:0] : Define start page address
    000b – PAGE0    011b – PAGE3    110b – PAGE6
    001b – PAGE1    100b – PAGE4    111b – PAGE7
    010b – PAGE2    101b – PAGE5
C[2:0] : Set time interval between each scroll step in terms of frame frequency
    000b – 5 frames     100b – 3 frames
    001b – 64 frames    101b – 4 frames
    010b – 128 frames   110b – 25 frame
    011b – 256 frames   111b – 2 frame
D[2:0] : Define end page address
    000b – PAGE0    011b – PAGE3    110b – PAGE6
    001b – PAGE1    100b – PAGE4    111b – PAGE7
    010b – PAGE2    101b – PAGE5
    The value of D[2:0] must be larger or equal to B[2:0]
E[7:0] : Dummy byte (Set as 00h)
F[7:0] : Dummy byte (Set as FFh) 

+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
|  0 |  0 |  1 |  0 |  0 |  1 |  1 | X0 |
+----+----+----+----+----+----+----+----+
| 0  | 0  | 0  | 0  | 0  | 0  | 0  | 0  |
+----+----+----+----+----+----+----+----+
| *  | *  | *  | *  | *  | B2 | B1 | B0 |
+----+----+----+----+----+----+----+----+
| *  | *  | *  | *  | *  | C2 | C1 | C0 |
+----+----+----+----+----+----+----+----+
| *  | *  | *  | *  | *  | D2 | D1 | D0 |
+----+----+----+----+----+----+----+----+
| 0  | 0  | 0  | 0  | 0  | 0  | 0  | 0  |
+----+----+----+----+----+----+----+----+
| 1  | 1  | 1  | 1  | 1  | 1  | 1  | 1  |
+----+----+----+----+----+----+----+----+
*/
void SSD1306_command_horizontal_scroll(bool is_left, unsigned char start_page_address, 
                                        unsigned char time_interval,
                                        unsigned char end_page_address,
                                        struct i2c_client  *i2c_client){

    if(is_left)
        SSD1306_command_write(true, 0x27, i2c_client);
    else
        SSD1306_command_write(true, 0x26, i2c_client);

    SSD1306_command_write(true, 0x00, i2c_client);
    SSD1306_command_write(true, start_page_address, i2c_client);
    SSD1306_command_write(true, time_interval, i2c_client);
    SSD1306_command_write(true, end_page_address, i2c_client);
    SSD1306_command_write(true, 0x00, i2c_client);
    SSD1306_command_write(true, 0xFF, i2c_client);
}

/*
Continuous Vertical and Horizontal Scroll Setup 

29h, X1X0=01b : Vertical and Right Horizontal Scroll
2Ah, X1X0=10b : Vertical and Left Horizontal Scroll  (Horizontal scroll by 1 column)
A[7:0] : Dummy byte
B[2:0] : Define start page address
    000b – PAGE0    011b – PAGE3    110b – PAGE6
    001b – PAGE1    100b – PAGE4    111b – PAGE7
    010b – PAGE2    101b – PAGE5
C[2:0] : Set time interval between each scroll step in terms of frame frequency
    000b – 5 frames     100b – 3 frames
    001b – 64 frames    101b – 4 frames
    010b – 128 frames   110b – 25 frame
    011b – 256 frames   111b – 2 frame
D[2:0] : Define end page address
    000b – PAGE0 011b – PAGE3 110b – PAGE6
    001b – PAGE1 100b – PAGE4 111b – PAGE7
    010b – PAGE2 101b – PAGE5
    The value of D[2:0] must be larger or equal to B[2:0]
E[5:0] : Vertical scrolling offset
 e.g. E[5:0]= 01h refer to offset =1 row
 E[5:0] =3Fh refer to offset =63 rows

+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
|  0 |  0 |  1 |  0 |  1 |  0 | X1 | X0 |
+----+----+----+----+----+----+----+----+
| 0  | 0  | 0  | 0  | 0  | 0  | 0  | 0  |
+----+----+----+----+----+----+----+----+
| *  | *  | *  | *  | *  | B2 | B1 | B0 |
+----+----+----+----+----+----+----+----+
| *  | *  | *  | *  | *  | C2 | C1 | C0 |
+----+----+----+----+----+----+----+----+
| *  | *  | *  | *  | *  | D2 | D1 | D0 |
+----+----+----+----+----+----+----+----+
| 0  | 0  | E5 | E4 | E3 | E2 | E1 | E0 |
+----+----+----+----+----+----+----+----+
*/
void SSD1306_command_vertical_horizontal_scroll(bool is_left, unsigned char start_page_address, 
                                                    unsigned char time_interval,
                                                    unsigned char end_page_address,
                                                    unsigned char vertical_offset,
                                                    struct i2c_client  *i2c_client){

    if(is_left)
        SSD1306_command_write(true, 0x2A, i2c_client);
    else
        SSD1306_command_write(true, 0x29, i2c_client);

    SSD1306_command_write(true, 0x00, i2c_client);
    SSD1306_command_write(true, start_page_address, i2c_client);
    SSD1306_command_write(true, time_interval, i2c_client);
    SSD1306_command_write(true, end_page_address, i2c_client);
    SSD1306_command_write(true, vertical_offset, i2c_client);
}

/*
Deactivate scroll

Stop scrolling that is configured by command 26h/27h/29h/2Ah. 
*/
void SSD1306_command_deactivate_scroll(struct i2c_client  *i2c_client){
    SSD1306_command_write(true, 0x2E, i2c_client);
}

/*
Activate scroll

Start scrolling that is configured by the scrolling setup
commands :26h/27h/29h/2Ah with the following valid
sequences:
Valid command sequence 1: 26h ;2Fh.
Valid command sequence 2: 27h ;2Fh.
Valid command sequence 3: 29h ;2Fh.
Valid command sequence 4: 2Ah ;2Fh.
*/
void SSD1306_command_activate_scroll(struct i2c_client  *i2c_client){
    SSD1306_command_write(true, 0x2F, i2c_client);
}

/*
Set Vertical Scroll Area

A[5:0] : Set No. of rows in top fixed area. The No. of
rows in top fixed area is referenced to the
top of the GDDRAM (i.e. row 0).[RESET =0]
B[6:0] : Set No. of rows in scroll area. This is the
number of rows to be used for vertical
scrolling. The scroll area starts in the first
row below the top fixed area. [RESET = 64]

+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
|  * |  * | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
| *  | B6 | B5 | B4 | B3 | B2 | B1 | B0 |
+----+----+----+----+----+----+----+----+
*/
void SSD1306_command_vertical_scroll(unsigned char row_top, 
                                        unsigned char row_scroll,
                                        struct i2c_client  *i2c_client){

    SSD1306_command_write(true, 0xA3, i2c_client);
    SSD1306_command_write(true, row_top, i2c_client);
    SSD1306_command_write(true, row_scroll, i2c_client);
}

/*
 ============================================
 =   3. Addressing Setting Command Table    =
 ============================================
*/

/*
Set Lower Column Start Address for Page Addressing Mode

Set the lower nibble of the column start address
register for Page Addressing Mode using X[3:0]
as data bits. The initial display line register is
reset to 0000b after RESET. 

(This command is only for page addressing mode)

range: OxO ~ 0xF

+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
|  0 |  0 |  0 |  0 | X3 | X2 | X1 | X0 |
+----+----+----+----+----+----+----+----+
*/
void SSD1306_command_lower_col_start(unsigned char lower_col_start, struct i2c_client  *i2c_client){
    SSD1306_command_write(true, lower_col_start, i2c_client);
}

/*
Set Higher Column Start Address for Page Addressing Mode 

Set the higher nibble of the column start address
register for Page Addressing Mode using X[3:0]
as data bits. The initial display line register is
reset to 0000b after RESET. 

(This command is only for page addressing mode)

range: Ox1O ~ 0x1F

+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
|  0 |  0 |  0 |  1 | X3 | X2 | X1 | X0 |
+----+----+----+----+----+----+----+----+
*/
void SSD1306_command_higher_col_start(unsigned char higher_col_start, struct i2c_client  *i2c_client){
    SSD1306_command_write(true, higher_col_start, i2c_client);
}


/*
Set Memory Addressing Mode

A[1:0] = 00b, Horizontal Addressing Mode
A[1:0] = 01b, Vertical Addressing Mode
A[1:0] = 10b, Page Addressing Mode (RESET)
A[1:0] = 11b, Invalid

+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
|  * |  * |  * |  * |  * |  * | A1 | A0 |
+----+----+----+----+----+----+----+----+
*/
void SSD1306_command_mem_addr_mod(unsigned char mode, struct i2c_client  *i2c_client){
    SSD1306_command_write(true, 0x20, i2c_client); 
    SSD1306_command_write(true, mode, i2c_client); 
}

/*
Set Column Address

Setup column start and end address 
A[6:0] : Column start address, range : 0-127d, (RESET=0d)
B[6:0] : Column end address,   range : 0-127d, (RESET =127d) 

(This command is only for horizontal or vertical addressing mode. )
+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
|  * | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
| *  | B6 | B5 | B4 | B3 | B2 | B1 | B0 |
+----+----+----+----+----+----+----+----+
*/
void SSD1306_command_col_addr(unsigned char col_addr_start, unsigned char col_addr_end, struct i2c_client  *i2c_client){
    SSD1306_command_write(true, 0x21, i2c_client); 
    SSD1306_command_write(true, col_addr_start, i2c_client); 
    SSD1306_command_write(true, col_addr_end, i2c_client); 
}


/*
Set Page Address

Setup page start and end address
A[2:0] : Page start Address, range : 0-7d, (RESET = 0d)
B[2:0] : Page end Address, range : 0-7d,   (RESET = 7d) 

(This command is only for horizontal or vertical addressing mode. )

+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
|  * |  * |  * |  * |  * | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
| *  | *  | *  | *  | *  | B2 | B1 | B0 |
+----+----+----+----+----+----+----+----+
*/
void SSD1306_command_page_addr(unsigned char page_addr_start, unsigned char page_addr_end, struct i2c_client  *i2c_client){
    SSD1306_command_write(true, 0x22, i2c_client); 
    SSD1306_command_write(true, page_addr_start, i2c_client); 
    SSD1306_command_write(true, page_addr_end, i2c_client); 
}

/*
Set Page Start Address for Page Addressing Mode

Set GDDRAM Page Start Address (PAGE0~PAGE7) for Page Addressing Mode
using X[2:0]. 

(This command is only for page addressing mode)

+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
|  1 |  0 |  1 |  1 |  0 | X2 | X1 | X0 |
+----+----+----+----+----+----+----+----+
*/
void SSD1306_command_page_start(unsigned char addr, struct i2c_client  *i2c_client){
    SSD1306_command_write(true, addr, i2c_client); 
}


/*
 ====================================================================================
 =    4. Hardware Configuration (Panel resolution & layout related) Command Table   =
 ====================================================================================
*/

/*
Set Display Start Line

Set display RAM display start line register from 0-63 (40h-7Fh) using X5-X3-X2-X1-X0.
Display start line register is reset to 000000b during RESET. 

+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
|  0 |  1 | X5 | X4 | X3 | X2 | X1 | X0 |
+----+----+----+----+----+----+----+----+
*/
void SSD1306_command_start_line(unsigned char line, struct i2c_client  *i2c_client) {

    unsigned char offset = 0x40;
    SSD1306_command_write(true, offset + line, i2c_client);
}

/*
Set Segment Re-map

A0h, X[0]=0b: column address   0 is mapped to SEG0 (RESET)
A1h, X[0]=1b: column address 127 is mapped to SEG0 

+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
|  1 |  0 |  1 |  0 | 0  | 0  | 0  | X0 |
+----+----+----+----+----+----+----+----+
*/
void SSD1306_command_horizontal_flip(bool is_flip, struct i2c_client  *i2c_client){
    if(is_flip)
        SSD1306_command_write(true, 0xA0, i2c_client);
    else
        SSD1306_command_write(true, 0xA1, i2c_client);
}

/*
Set Multiplex Ratio

Set MUX ratio to N+1 MUX
A[5:0]     from 0 to 14(0xE) are invalid entry. 
N=A[5:0] : from 16 MUX to 64 MUX, RESET=111111b (i.e. 63d, 64MUX)
N=A[5:0] : from Fh to 3Fh


+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
|  * |  * | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
*/
void SSD1306_command_mux_ratio(unsigned char ratio, struct i2c_client  *i2c_client) {
    SSD1306_command_write(true, 0xA8, i2c_client);
    SSD1306_command_write(true, ratio, i2c_client);
}

/*
Set COM Output Scan Direction 

C0h, X[3]=0b: normal mode (RESET) Scan from COM0 to COM[N –1]
C8h, X[3]=1b: remapped mode. Scan from COM[N-1] to COM0
Where N is the Multiplex ratio. 
+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
|  1 |  1 |  0 |  0 | X3 | 0  | 0  | 0  |
+----+----+----+----+----+----+----+----+
*/
void SSD1306_command_vertical_flip(bool is_flip, struct i2c_client  *i2c_client) {
    if(is_flip)
        SSD1306_command_write(true, 0xC0, i2c_client);
    else
        SSD1306_command_write(true, 0xC8, i2c_client);
}

/*
Set Display Offset

Set vertical shift by COM from 0d ~ 63d (0h ~ 3Fh)
The value is reset to 00h after RESET

+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
|  * |  * | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
*/
void SSD1306_command_display_offset(unsigned char offset, struct i2c_client  *i2c_client) {
    SSD1306_command_write(true, 0xD3, i2c_client); 
    SSD1306_command_write(true, offset, i2c_client); 
}

/*
Set COM Pins Hardware Configuration 

A[4]=0b, Sequential COM pin configuration
A[4]=1b, Alternative COM pinconfiguration (RESET)
A[5]=0b, Disable COM Left/Rightremap (RESET)
A[5]=1b, Enable COM Left/Right remap 

+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
|  0 |  0 | A5 | A4 | 0  | 0  | 1  | 0  |
+----+----+----+----+----+----+----+----+
*/
void SSD1306_command_com_pins(unsigned char config, struct i2c_client  *i2c_client){
    SSD1306_command_write(true, 0xDA, i2c_client);
    SSD1306_command_write(true, config, i2c_client);
}

/*
 ==========================================================
 =   5. Timing & Driving Scheme Setting Command Table     =
 ==========================================================
*/

/*
Set Display Clock Divide Ratio/Oscillator Frequency

A[3:0] : Define the divide ratio (D) of the display clocks (DCLK):
    Divide ratio= A[3:0] + 1, RESET is 0000b (divide ratio = 1)
A[7:4] : Set the Oscillator Frequency, FOSC.

Oscillator Frequency increases with the value of A[7:4] and vice versa.
    RESET is 1000b
    Range:0000b ~ 1111b
Frequency increases as setting value increases.

+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
*/
void SSD1306_command_set_clock(unsigned char clock, struct i2c_client  *i2c_client){
    SSD1306_command_write(true, 0xD5, i2c_client);
    SSD1306_command_write(true, clock, i2c_client);
}

/*
Set Pre-charge Period

A[3:0] : Phase 1 period of up to 15 DCLK clocks 0 is invalid entry (RESET=2h)
A[7:4] : Phase 2 period of up to 15 DCLK clocks 0 is invalid entry (RESET=2h) 

+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
*/
void SSD1306_command_pre_charge(unsigned char phase, struct i2c_client  *i2c_client){
    SSD1306_command_write(true, 0xD9, i2c_client); 
    SSD1306_command_write(true, phase, i2c_client); 
}

/*
Set VCOMH Deselect Level 

+--------+------+-----------------------+
| A[6:4] |  Hex | V COMH deselect level |
|        | code |                       |
+--------+------+-----------------------+
| 000b   | 00h  | ~ 0.65 x VCC          |
+--------+------+-----------------------+
| 010b   | 20h  | ~ 0.77 x VCC (RESET)  |
+--------+------+-----------------------+
| 011b   | 30h  | ~ 0.83 x VCC          |
+--------+------+-----------------------+

+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
|  0 | A6 | A5 | A4 |  0 |  0 |  0 |  0 |
+----+----+----+----+----+----+----+----+
*/
void SSD1306_command_VCOMH(unsigned char vcomh, struct i2c_client  *i2c_client){
    SSD1306_command_write(true, 0xDB, i2c_client); 
    SSD1306_command_write(true, vcomh, i2c_client); 
}

/*

    6. Charge Pump Command Table 

*/

/*
Charge Pump Setting 

A[2] = 0b, Disable charge pump(RESET)
A[2] = 1b, Enable charge pump during display on 

+----+----+----+----+----+----+----+----+
| A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
+----+----+----+----+----+----+----+----+
|  * |  * |  0 |  1 | 0  | A2 | 0  | 0  |
+----+----+----+----+----+----+----+----+
*/
void SSD1306_command_charge_pump(unsigned char pump, struct i2c_client  *i2c_client){
    SSD1306_command_write(true, 0x8D, i2c_client);
    SSD1306_command_write(true, pump, i2c_client);
}
