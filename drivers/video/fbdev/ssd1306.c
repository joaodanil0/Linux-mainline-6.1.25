#include "ssd1306.h"

static int ssd1306_probe(struct i2c_client *client, const struct i2c_device_id *id) {

    pr_info("SSD1306 driver Probing!!!\n");
    SSD1306_DisplayInit(i2c_client); 

    // SSD1306_Fill(0x00, i2c_client);
    
    // SSD1306_command_diagonal_scroll(SSD1306_SCROLL_DIAG_RIGTH, 0x00, 0x03, 0x07, 0x07, i2c_client);
    // SSD1306_command_vertical_scroll(0x00, 0x01, i2c_client);
    // SSD1306_command_activate_scroll(i2c_client);
    SSD1306_String("Teste\n", i2c_client);

    //BBBBBBBBBBBBBBBBB\nCCCCCCCCCCCCCCCCCCCC\nDDDDDDDDDDDDDDDDDDDD\nEEEEEEEEEEEEEEEEEEEE\nFFFFFFFFFFFFFFFFFFFF\nGGGGGGGGGGGGGGGGGGGG\n////////////////////
    // SSD1306_Fill(0xFF, i2c_client);

 
    pr_info("OLED Probed!!!\n");
  
    return 0;
}

static void ssd1306_remove(struct i2c_client *client) {

    SSD1306_SetCursor(0,0, i2c_client);  
    //clear the display
    SSD1306_Fill(0x00, i2c_client);
    
    SSD1306_command_turnon(0xAE, i2c_client);
    
    pr_info("OLED Removed!!!\n");

}

static int __init ssd1306_init(void) {

    struct i2c_adapter *i2c_adapter = NULL;

    i2c_adapter = i2c_get_adapter(I2C_BUS);

    if(i2c_adapter == NULL){
        pr_err("I2C Adapter not found!\n");
        return -1;
    }

    i2c_client = i2c_new_client_device(i2c_adapter, &i2c_info);

    if(i2c_client == NULL){
        pr_err("I2C client not found!\n");
        return -1;
    }

    i2c_add_driver(&ssd1306_driver);
    i2c_put_adapter(i2c_adapter);

    pr_info("SSD1306 driver Added\n");
    
    return 0;
}

static void __exit ssd1306_exit(void){
  i2c_unregister_device(i2c_client);
  i2c_del_driver(&ssd1306_driver);
  pr_info("SSD1306 driver Removed!!!\n");
}

module_init(ssd1306_init);
module_exit(ssd1306_exit);

MODULE_DESCRIPTION("FB driver for the Solomon SSD1306 OLED controller");
MODULE_AUTHOR("João Danilo <joaodanilo1992@gmail.com>");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");