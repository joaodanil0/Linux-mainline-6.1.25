#include <linux/i2c.h>
#include "ssd1306_defs.h"

#define LEN_COMMANDS 2

void SSD1306_write(bool is_cmd, uint8_t hex, struct i2c_client *i2c_client);
void SSD1306_command_send(uint8_t value, struct i2c_client *i2c_client);

/*
 =====================================
 =   1. Fundamental Command Table    =
 =====================================
*/

/*
-> Command:
    Set Contrast Control
-> Description:
    Command to select 1 out of 256 contrast steps. 
    Contrast increases as the value increases.
-> Reset Value:
    0x7F
-> Address: 
    0x81
-> Values:
    0x01 ~ 0xFF
*/
void SSD1306_command_contrast(uint8_t value, struct i2c_client *i2c_client);

/*
-> Command:
    Entire Display ON
-> Description:
    0xA4: Resume to RAM content display Output follows RAM content
    0xA5: Entire display ON Output ignores RAM content
-> Reset Value:
    0xA4
-> Address: 
    -
-> Values:
    0xA4 or 0xA5
*/
void SSD1306_command_entire_on(uint8_t value, struct i2c_client *i2c_client);

/*
-> Command:
    Set Normal/Inverse Display 
-> Description:
    0xA6: Normal display
    0XA7: Inverse display
-> Reset Value:
    0xA6
-> Address: 
    -
-> Values:
    0xA6 or 0xA7
*/
void SSD1306_command_inverse_disp(uint8_t value, struct i2c_client *i2c_client);

/*
-> Command:
    Set Display ON/OFF
-> Description:
    0xAE: Display OFF (sleep mode)
    0xAF: Display ON in normal mode 
-> Reset Value:
    0xAE
-> Address: 
    -
-> Values:
    0xAE or 0xAF
*/
void SSD1306_command_turnon(uint8_t value, struct i2c_client *i2c_client);

/*
 ====================================
 =   2. Scrolling Command Table     =
 ====================================
*/

/*
-> Command:
    Continuous Horizontal Scroll Setup
-> Description:
    ------- 1st Sequence ----------
    0x26: Right Horizontal Scroll or
    0x27: Left Horizontal Scroll
    ------- 2nd Sequence ----------
    0x00: Dummy byte
    ------- 3rd Sequence ----------
    0x00 ~ 0x07: Define start page address
        0x00 – PAGE0    0x03 – PAGE3    0x06 – PAGE6
        0x01 – PAGE1    0x04 – PAGE4    0x07 – PAGE7
        0x02 – PAGE2    0x05 – PAGE5
    ------- 4th Sequence ----------
    0x00 ~ 0x07: Set time interval between each scroll 
                    step in terms of frame frequency
        0x00 –   5 frames   0x03 – 256 frames   0x06 – 25 frames     
        0x01 –  64 frames   0x04 –   3 frames   0x07 –  2 frames   
        0x02 – 128 frames   0x05 –   4 frames               
    ------- 5th Sequence ----------
    0x00 ~ 0x07: Define end page address (this value must be bigger
                    than 3rd sequence)
        0x00 – PAGE0    0x03 – PAGE3    0x06 – PAGE6
        0x01 – PAGE1    0x04 – PAGE4    0x07 – PAGE7
        0x02 – PAGE2    0x05 – PAGE5
    ------- 6th Sequence ----------
    0x00 : Dummy byte
    ------- 7th Sequence ----------
    0xFF : Dummy byte
-> Reset Value:
    -
-> Address: 
    -
-> Values:
    ------- 1st Sequence ----------
    0x26 or 0x27
   ------- 2nd Sequence ----------
    0x00
    ------- 3rd Sequence ----------
    0x00 ~ 0x07
    ------- 4th Sequence ----------
    0x00 ~ 0x07        
    ------- 5th Sequence ----------
    0x00 ~ 0x07
    ------- 6th Sequence ----------
    0x00
    ------- 7th Sequence ----------
    0xFF
*/
void SSD1306_command_horizontal_scroll(uint8_t direction, uint8_t start_page_addr, 
                                        uint8_t time_interval, uint8_t end_page_addr,
                                        struct i2c_client *i2c_client);

/*
-> Command:
    Continuous Vertical and Horizontal Scroll Setup 
-> Description:
    ------- 1st Sequence ----------
    0x29: Vertical and Right Horizontal Scroll or
    0x2A: Vertical and Left Horizontal Scroll
    ------- 2nd Sequence ----------
    0x00: Dummy byte
    ------- 3rd Sequence ----------
    0x00 ~ 0x07: Define start page address
        0x00 – PAGE0    0x03 – PAGE3    0x06 – PAGE6
        0x01 – PAGE1    0x04 – PAGE4    0x07 – PAGE7
        0x02 – PAGE2    0x05 – PAGE5
    ------- 4th Sequence ----------
    0x00 ~ 0x07: Set time interval between each scroll 
                    step in terms of frame frequency
        0x00 –   5 frames   0x03 – 256 frames   0x06 – 25 frames     
        0x01 –  64 frames   0x04 –   3 frames   0x07 –  2 frames   
        0x02 – 128 frames   0x05 –   4 frames  
    ------- 5th Sequence ----------
    0x00 ~ 0x07: Define end page address (this value must be bigger
                    than 3rd sequence)
        0x00 – PAGE0    0x03 – PAGE3    0x06 – PAGE6
        0x01 – PAGE1    0x04 – PAGE4    0x07 – PAGE7
        0x02 – PAGE2    0x05 – PAGE5
    ------- 6th Sequence ----------
    0x01 ~ 0x3F: Vertical scrolling offset
-> Reset Value:
    -
-> Address: 
    -
-> Values:
   ------- 1st Sequence ----------
    0x29 or 0x2A
   ------- 2nd Sequence ----------
    0x00
    ------- 3rd Sequence ----------
    0x00 ~ 0x07
    ------- 4th Sequence ----------
    0x00 ~ 0x07        
    ------- 5th Sequence ----------
    0x00 ~ 0x07
    ------- 6th Sequence ----------
    0x01 ~ 0x3F
*/
void SSD1306_command_diagonal_scroll(uint8_t direction, uint8_t start_page_addr, 
                                        uint8_t time_interval, uint8_t end_page_addr,
                                        uint8_t vertical_offset,
                                        struct i2c_client *i2c_client);

/*
-> Command:
    Deactivate scroll
-> Description:
    Stop scrolling that is configured by command 0x26/0x27/0x29/0x2A. 
-> Reset Value:
    -
-> Address: 
    -
-> Values:
    -
*/
void SSD1306_command_deactivate_scroll(struct i2c_client *i2c_client);

/*
-> Command:
    Activate scroll
-> Description:
    Start scrolling that is configured by the scrolling setup
        commands :0x26/0x27/0x29/0x2A:

-> Reset Value:
    -
-> Address: 
    -
-> Values:
    -
*/
void SSD1306_command_activate_scroll(struct i2c_client *i2c_client);

/*
-> Command:
    Set Vertical Scroll Area
-> Description:
    ------- 1st Sequence ----------
    0xA3: Vertical Scroll    
    ------- 2nd Sequence ----------
    0x00 ~ 0x3F: Set number of rows in top fixed area
    ------- 3rd Sequence ----------
    0x00 ~ 0x7F: Set No. of rows in scroll area
-> Reset Value:
    -
-> Address: 
    -
-> Values:
    ------- 1st Sequence ----------
    0xA3  
    ------- 2nd Sequence ----------
    0x00 ~ 0x3F
    ------- 3rd Sequence ----------
    0x00 ~ 0x7F
*/
void SSD1306_command_vertical_scroll(uint8_t row_top, uint8_t row_scroll,
                                        struct i2c_client *i2c_client);

/*
 ============================================
 =   3. Addressing Setting Command Table    =
 ============================================
*/

/*
-> Command:
    Set Lower Column Start Address for Page Addressing Mode
-> Description:
    Set the lower nibble of the column start address
    register for Page Addressing Mode
    (This command is only for page addressing mode)
-> Reset Value:
    0x00
-> Address: 
    -
-> Values:
    OxO0 ~ 0x0F
*/
void SSD1306_command_lower_col_start(uint8_t value, struct i2c_client *i2c_client);

/*
-> Command:
    Set Higher Column Start Address for Page Addressing Mode 
-> Description:
    Set the higher nibble of the column start address
    register for Page Addressing Mode 
    (This command is only for page addressing mode)
-> Reset Value:
    0x00
-> Address: 
    -
-> Values:
    Ox10 ~ 0x1F
*/
void SSD1306_command_higher_col_start(uint8_t value, struct i2c_client *i2c_client);

/*
-> Command:
    Set Memory Addressing Mode
-> Description:
    0x00: Horizontal Addressing Mode
    0x01: Vertical Addressing Mode
    0x02: Page Addressing Mode
    0x03: Invalid
-> Reset Value:
    0x00
-> Address: 
    0x20
-> Values:
    Ox00 ~ 0x02
*/
void SSD1306_command_mem_addr_mode(uint8_t value, struct i2c_client *i2c_client);

/*
-> Command:
    Set Column Address
-> Description:
    Setup column start and end address 
    0x00 ~ 0x7F : Column start address
    0x00 ~ 0x7F: Column end address
    (This command is only for horizontal or vertical addressing mode.)
-> Reset Value:
    Column start address: 0x00
    Column end address:   0x7F
-> Address: 
    0x21
-> Values:
    0x00 ~ 0x7F
*/
void SSD1306_command_col_addr(uint8_t col_addr_start, uint8_t col_addr_end, struct i2c_client *i2c_client);

/*
-> Command:
    Set Page Address
-> Description:
    Setup page start and end address
    0x00 ~ 0x07: Page start Address
    0x00 ~ 0x07: Page end Address
    (This command is only for horizontal or vertical addressing mode. )
-> Reset Value:
    Column start address: 0x00
    Column end address:   0x07
-> Address: 
    0x22
-> Values:
    0x00 ~ 0x07
*/
void SSD1306_command_page_addr(uint8_t page_addr_start, uint8_t page_addr_end, struct i2c_client *i2c_client);

/*
-> Command:
    Set Page Start Address for Page Addressing Mode
-> Description:
    Set GDDRAM Page Start Address (PAGE0~PAGE7) for Page Addressing Mode
    (This command is only for page addressing mode)
-> Reset Value:
    -
-> Address: 
    -
-> Values:
    0xB0 ~ 0xB7
*/
void SSD1306_command_page_start(uint8_t addr, struct i2c_client *i2c_client);

/*
 ====================================================================================
 =    4. Hardware Configuration (Panel resolution & layout related) Command Table   =
 ====================================================================================
*/

/*
-> Command:
    Set Display Start Line
-> Description:
    Set display RAM display start line register 
    from 0x40 ~ 0x7F (equivalent to 0 ~ 63)
-> Reset Value:
    0x00
-> Address: 
    -
-> Values:
    0x40 ~ 0x7F
*/
void SSD1306_command_start_line(uint8_t value, struct i2c_client *i2c_client);

/*
-> Command:
    Set Segment Re-map
-> Description:
    0xA0: column address   0 is mapped to SEG0
    0xA1: column address 127 is mapped to SEG0 
-> Reset Value:
    0xA0
-> Address: 
    -
-> Values:
    0xA0 or 0xA1
*/
void SSD1306_command_horizontal_flip(uint8_t value, struct i2c_client *i2c_client);

/*
-> Command:
    Set Multiplex Ratio
-> Description:
    Set MUX ratio to N+1 MUX
    From 0 to 14(0x0E) are invalid entry. 
    From 0x0F to 0x3F, equivalent to 16 MUX to 64 MUX
-> Reset Value:
    0x3F
-> Address: 
    0xA8
-> Values:
    0x0F ~ 0x3F
*/
void SSD1306_command_mux_ratio(uint8_t value, struct i2c_client *i2c_client);

/*
-> Command:
    Set COM Output Scan Direction 
-> Description:
    0xC0: normal mode Scan from COM0 to COM[N –1]
    0xC8: remapped mode Scan from COM[N-1] to COM0
    Where N is the Multiplex ratio. 
-> Reset Value:
    0xC0
-> Address: 
    -
-> Values:
    0xC0 or 0xC8
*/
void SSD1306_command_vertical_flip(uint8_t value, struct i2c_client *i2c_client);

/*
-> Command:
    Set Display Offset
-> Description:
    Set vertical shift by COM from 0x00 ~ 0x3F
-> Reset Value:
    0x00
-> Address: 
    0xD3
-> Values:
    0x00 ~ 0x3F
*/
void SSD1306_command_display_offset(uint8_t value, struct i2c_client *i2c_client);

/*
-> Command:
Set COM Pins Hardware Configuration 
-> Description:
    0x02: Disable COM Left/Right remap and
          Sequential COM pin configuration
    0x12: Disable COM Left/Right remap and
          Alternative COM pinconfiguration
    0x22: Enable COM Left/Right remap and
          Sequential COM pin configuration 
    0x32: Enable COM Left/Right remap and
          Alternative COM pinconfiguration
-> Reset Value:
    0x12
-> Address: 
    0xDA
-> Values:
    0x02, 0x12, 0x22 or 0x32
*/
void SSD1306_command_com_pins(uint8_t value, struct i2c_client *i2c_client); 


/*
 ==========================================================
 =   5. Timing & Driving Scheme Setting Command Table     =
 ==========================================================
*/

/*
-> Command:
    Set Display Clock Divide Ratio/Oscillator Frequency
-> Description:
    0x0 ~ 0xF (1st nibble): Define the divide ratio (D) of the display 
                            clocks (DCLK): Divide ratio= A[3:0] + 1
    0x0 ~ 0xF (2nd nibble): Set the Oscillator Frequency, FOSC.
                            Oscillator Frequency increases with the 
                            value  and vice versa 
-> Reset Value:
    0x10
-> Address: 
    0xD5
-> Values:
    0x00 ~ 0xFF
*/
void SSD1306_command_set_clock(uint8_t clock, struct i2c_client *i2c_client);

/*
-> Command:
    Set Pre-charge Period
-> Description:
    0x1 ~ 0xF (1st nibble): Phase 1 period of up to 15 DCLK clocks 0 is invalid entry 
    0x1 ~ 0xF (2nd nibble): Phase 2 period of up to 15 DCLK clocks 0 is invalid entry
-> Reset Value:
    0x22
-> Address: 
    0xD9
-> Values:
    0x11 ~ 0xFF
*/
void SSD1306_command_pre_charge(uint8_t phase, struct i2c_client *i2c_client);

/*
-> Command:
    Set VCOMH Deselect Level 
-> Description:
    0x00: ~ 0.65 x VCC 
    0x20: ~ 0.77 x VCC
    0x30: ~ 0.83 x VCC 
-> Reset Value:
    0x20
-> Address: 
    0xDB
-> Values:
    0x00, 0x20 or 0x30
*/
void SSD1306_command_VCOMH(uint8_t vcomh, struct i2c_client *i2c_client);

/*
 ==========================================================
 =   6. Charge Pump Command Table                         =
 ==========================================================
*/

/*
-> Command:
    Charge Pump Setting 
-> Description:
    0x10: Disable charge pump
    0x14: Enable charge pump during display on 
-> Reset Value:
    0x10
-> Address: 
    0x8D
-> Values:
    0x10 or 0x14
*/
void SSD1306_command_charge_pump(uint8_t pump, struct i2c_client *i2c_client);



