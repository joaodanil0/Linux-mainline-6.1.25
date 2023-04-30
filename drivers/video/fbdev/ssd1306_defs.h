

/*
 ==================
 =    Utils       =
 ==================
*/
#define SSD1306_CMD  0x00
#define SSD1306_DATA 0x40

#define SSD1306_DUMMY_ZEROS 0x00
#define SSD1306_DUMMY_ONES  0xFF

/*
 ==================
 =    Addresses   =
 ==================
*/
#define SSD1306_MEM_ADDR_MODE_ADDR  0x20
#define SSD1306_COL_ADDR            0x21
#define SSD1306_PAGE_ADDR           0x22
#define SSD1306_CONSTRAST_ADDR      0x81
#define SSD1306_CHARGE_PUMP_ADDR    0x8D
#define SSD1306_MUX_RATIO_ADDR      0xA8
#define SSD1306_DISP_OFFSET_ADDR    0xD3
#define SSD1306_COM_PINS_ADDR       0xDA
#define SSD1306_DISP_CLK_ADDR       0xD5
#define SSD1306_PRE_CHARGE_ADDR     0xD9
#define SSD1306_V_COMH_ADDR         0xDB

/*
 ==================
 =    Commands    =
 ==================
*/
#define SSD1306_SCROLL_HOR_RIGTH        0x26
#define SSD1306_SCROLL_HOR_LEFT         0x27
#define SSD1306_SCROLL_DIAG_RIGTH       0x29
#define SSD1306_SCROLL_DIAG_LEFT        0x2A
#define SSD1306_SCROLL_DEACTIVE         0x2E
#define SSD1306_SCROLL_ACTIVE           0x2F
#define SSD1306_SCROLL_VERTICAL         0xA3

#define SSD1306_HW_CONF_REMAP_NORMAL    0xA0
#define SSD1306_HW_CONF_REMAP_FLIPED    0xA1
#define SSD1306_HW_CONF_COM_NORMAL      0xC0
#define SSD1306_HW_CONF_COM_FLIPED      0xC8
