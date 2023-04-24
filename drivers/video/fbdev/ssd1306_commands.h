#include <linux/i2c.h>

#define LEN_COMMANDS 2

void SSD1306_command_write(bool is_cmd, unsigned char data, struct i2c_client *i2c_client);


// 1. Fundamental Command Table 
void SSD1306_command_contrast(unsigned char contrast, struct i2c_client  *i2c_client);
void SSD1306_command_entire_on(bool is_all_on, struct i2c_client  *i2c_client);
void SSD1306_command_inverse_disp(bool is_inverse, struct i2c_client  *i2c_client);
void SSD1306_command_turnon(bool is_on, struct i2c_client  *i2c_client);

// 2. Scrolling Command Table 
void SSD1306_command_horizontal_scroll(bool is_left, unsigned char start_page_address, 
                                        unsigned char time_interval,
                                        unsigned char end_page_address,
                                        struct i2c_client  *i2c_client);
void SSD1306_command_vertical_horizontal_scroll(bool is_left, unsigned char start_page_address, 
                                                    unsigned char time_interval,
                                                    unsigned char end_page_address,
                                                    unsigned char vertical_offset,
                                                    struct i2c_client  *i2c_client);
void SSD1306_command_deactivate_scroll(struct i2c_client  *i2c_client);
void SSD1306_command_activate_scroll(struct i2c_client  *i2c_client);
void SSD1306_command_vertical_scroll(unsigned char row_top, 
                                        unsigned char row_scroll,
                                        struct i2c_client  *i2c_client);

// 3. Addressing Setting Command Table
void SSD1306_command_lower_col_start(unsigned char lower_col_start, struct i2c_client  *i2c_client);
void SSD1306_command_higher_col_start(unsigned char higher_col_start, struct i2c_client  *i2c_client);
void SSD1306_command_mem_addr_mod(unsigned char mode, struct i2c_client  *i2c_client);
void SSD1306_command_col_addr(unsigned char col_addr_start, unsigned char col_addr_end, struct i2c_client  *i2c_client);
void SSD1306_command_page_addr(unsigned char page_addr_start, unsigned char page_addr_end, struct i2c_client  *i2c_client);
void SSD1306_command_page_start(unsigned char addr, struct i2c_client  *i2c_client);

// 4. Hardware Configuration (Panel resolution & layout related) Command Table 
void SSD1306_command_start_line(unsigned char line, struct i2c_client  *i2c_client);
void SSD1306_command_horizontal_flip(bool is_flip, struct i2c_client  *i2c_client);
void SSD1306_command_mux_ratio(unsigned char ratio, struct i2c_client  *i2c_client);
void SSD1306_command_vertical_flip(bool is_flip, struct i2c_client  *i2c_client);
void SSD1306_command_display_offset(unsigned char offset, struct i2c_client  *i2c_client);
void SSD1306_command_com_pins(unsigned char config, struct i2c_client  *i2c_client); 


// 5. Timing & Driving Scheme Setting Command Table
void SSD1306_command_set_clock(unsigned char clock, struct i2c_client  *i2c_client);
void SSD1306_command_pre_charge(unsigned char phase, struct i2c_client  *i2c_client);
void SSD1306_command_VCOMH(unsigned char vcomh, struct i2c_client  *i2c_client);

// 6. Charge Pump Command Table
void SSD1306_command_charge_pump(unsigned char pump, struct i2c_client  *i2c_client);



