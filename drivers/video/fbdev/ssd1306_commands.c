#include "ssd1306_commands.h"

void SSD1306_write(bool is_cmd, uint8_t hex, struct i2c_client *i2c_client){

    uint8_t buf[LEN_COMMANDS] = {0};
    
    buf[0] = is_cmd == true ? SSD1306_CMD : SSD1306_DATA;

    pr_info("CMD: %s:0x%x", is_cmd ? "True" : "False",is_cmd ? SSD1306_CMD : SSD1306_DATA);
    
    buf[1] = hex;
    
    i2c_master_send(i2c_client, buf, LEN_COMMANDS);
}

void SSD1306_command_send(uint8_t value, struct i2c_client *i2c_client){
    SSD1306_write(true, value, i2c_client);
}


/*
 =====================================
 =   1. Fundamental Command Table    =
 =====================================
*/

void SSD1306_command_contrast(uint8_t value, struct i2c_client *i2c_client){
    SSD1306_command_send(SSD1306_CONSTRAST_ADDR, i2c_client);
    SSD1306_command_send(value, i2c_client);
}

void SSD1306_command_entire_on(uint8_t value, struct i2c_client *i2c_client){
    SSD1306_command_send(value, i2c_client);
}

void SSD1306_command_inverse_disp(uint8_t value, struct i2c_client *i2c_client){
    SSD1306_command_send(value, i2c_client);
}

void SSD1306_command_turnon(uint8_t value, struct i2c_client *i2c_client){
    SSD1306_command_send(value, i2c_client);
}


/*
 ====================================
 =   2. Scrolling Command Table     =
 ====================================
*/

void SSD1306_command_horizontal_scroll(uint8_t direction, uint8_t start_page_addr, 
                                        uint8_t time_interval, uint8_t end_page_addr,
                                        struct i2c_client *i2c_client){   
    SSD1306_command_send(direction, i2c_client);
    SSD1306_command_send(SSD1306_DUMMY_ZEROS, i2c_client);
    SSD1306_command_send(start_page_addr, i2c_client);
    SSD1306_command_send(time_interval, i2c_client);
    SSD1306_command_send(end_page_addr, i2c_client);
    SSD1306_command_send(SSD1306_DUMMY_ZEROS, i2c_client);
    SSD1306_command_send(SSD1306_DUMMY_ONES, i2c_client);
}

void SSD1306_command_diagonal_scroll(uint8_t direction, uint8_t start_page_addr, 
                                        uint8_t time_interval, uint8_t end_page_addr,
                                        uint8_t vertical_offset,
                                        struct i2c_client *i2c_client){
    SSD1306_command_send(direction, i2c_client);
    SSD1306_command_send(SSD1306_DUMMY_ZEROS, i2c_client);
    SSD1306_command_send(start_page_addr, i2c_client);
    SSD1306_command_send(time_interval, i2c_client);
    SSD1306_command_send(end_page_addr, i2c_client);
    SSD1306_command_send(vertical_offset, i2c_client);
}

void SSD1306_command_deactivate_scroll(struct i2c_client *i2c_client){
    SSD1306_command_send(SSD1306_SCROLL_DEACTIVE, i2c_client);
}

void SSD1306_command_activate_scroll(struct i2c_client *i2c_client){
    SSD1306_command_send(SSD1306_SCROLL_ACTIVE, i2c_client);
}

void SSD1306_command_vertical_scroll(uint8_t row_top, uint8_t row_scroll,
                                        struct i2c_client *i2c_client){
    SSD1306_command_send(SSD1306_SCROLL_VERTICAL, i2c_client);
    SSD1306_command_send(row_top, i2c_client);
    SSD1306_command_send(row_scroll, i2c_client);
}

/*
 ============================================
 =   3. Addressing Setting Command Table    =
 ============================================
*/

void SSD1306_command_lower_col_start(uint8_t value, struct i2c_client *i2c_client){
    SSD1306_command_send(value, i2c_client);
}

void SSD1306_command_higher_col_start(uint8_t value, struct i2c_client *i2c_client){
    SSD1306_command_send(value, i2c_client);
}

void SSD1306_command_mem_addr_mode(uint8_t value, struct i2c_client *i2c_client){
    SSD1306_command_send(SSD1306_MEM_ADDR_MODE_ADDR, i2c_client);
    SSD1306_command_send(value, i2c_client);
}

void SSD1306_command_col_addr(uint8_t col_addr_start, uint8_t col_addr_end, 
                                struct i2c_client *i2c_client){
    SSD1306_command_send(SSD1306_COL_ADDR, i2c_client); 
    SSD1306_command_send(col_addr_start, i2c_client); 
    SSD1306_command_send(col_addr_end, i2c_client); 
}

void SSD1306_command_page_addr(uint8_t page_addr_start, uint8_t page_addr_end, 
                                struct i2c_client *i2c_client){
    SSD1306_command_send(SSD1306_PAGE_ADDR, i2c_client); 
    SSD1306_command_send(page_addr_start, i2c_client); 
    SSD1306_command_send(page_addr_end, i2c_client); 

}

void SSD1306_command_page_start(uint8_t addr, struct i2c_client *i2c_client){
    SSD1306_command_send(addr, i2c_client); 
}


/*
 ====================================================================================
 =    4. Hardware Configuration (Panel resolution & layout related) Command Table   =
 ====================================================================================
*/

void SSD1306_command_start_line(uint8_t value, struct i2c_client *i2c_client) {
    SSD1306_command_send(value, i2c_client);
}

void SSD1306_command_horizontal_flip(uint8_t value, struct i2c_client *i2c_client){
    SSD1306_command_send(value, i2c_client);
}

void SSD1306_command_mux_ratio(uint8_t value, struct i2c_client *i2c_client) {
    SSD1306_command_send(value, i2c_client);
}

void SSD1306_command_vertical_flip(uint8_t value, struct i2c_client *i2c_client) {
    SSD1306_command_send(value, i2c_client);
}

void SSD1306_command_display_offset(uint8_t offset, struct i2c_client *i2c_client) {
    SSD1306_command_send(SSD1306_DISP_OFFSET_ADDR, i2c_client);
    SSD1306_command_send(offset, i2c_client); 
}

void SSD1306_command_com_pins(uint8_t config, struct i2c_client *i2c_client){
    SSD1306_command_send(SSD1306_COM_PINS_ADDR, i2c_client); 
    SSD1306_command_send(config, i2c_client); 
}

/*
 ==========================================================
 =   5. Timing & Driving Scheme Setting Command Table     =
 ==========================================================
*/

void SSD1306_command_set_clock(uint8_t clock, struct i2c_client *i2c_client){
    SSD1306_command_send(SSD1306_DISP_CLK_ADDR, i2c_client); 
    SSD1306_command_send(clock, i2c_client);
}

void SSD1306_command_pre_charge(uint8_t phase, struct i2c_client *i2c_client){
    SSD1306_command_send(SSD1306_PRE_CHARGE_ADDR, i2c_client); 
    SSD1306_command_send(phase, i2c_client); 
}

void SSD1306_command_VCOMH(uint8_t vcomh, struct i2c_client  *i2c_client){
    SSD1306_command_send(SSD1306_V_COMH_ADDR, i2c_client); 
    SSD1306_command_send(vcomh, i2c_client); 
}

/*
 ==========================================================
 =   6. Charge Pump Command Table                         =
 ==========================================================
*/

void SSD1306_command_charge_pump(uint8_t pump, struct i2c_client  *i2c_client){
    SSD1306_command_send(SSD1306_CHARGE_PUMP_ADDR, i2c_client); 
    SSD1306_command_send(pump, i2c_client); 
}
