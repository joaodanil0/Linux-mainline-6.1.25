
#include <linux/module.h>
#include <linux/i2c.h>


#include "ssd1306_util.h"
#include "ssd1306_commands.h"

#define I2C_BUS               (0)
#define I2C_DEVICE_NAME       ("SSD1306FB")
#define SSD1306_ADDR          (0x3C)

// -------------- Functions
static int __init ssd1306_init(void);
static void __exit ssd1306_exit(void);
static int ssd1306_probe(struct i2c_client *client, const struct i2c_device_id *id);
static void ssd1306_remove(struct i2c_client *client);



// -------------- Variables
static struct i2c_client  *i2c_client = NULL;

static const struct i2c_device_id ssd1306_id[] = {
    { I2C_DEVICE_NAME, 0 },
    { }
};
MODULE_DEVICE_TABLE(i2c, ssd1306_id);

static struct i2c_driver ssd1306_driver = {
  .driver = {
    .name   = I2C_DEVICE_NAME,
    .owner  = THIS_MODULE
  },
  .probe          = ssd1306_probe,
  .remove         = ssd1306_remove,
  .id_table       = ssd1306_id,
};

static struct i2c_board_info i2c_info = {
    I2C_BOARD_INFO(I2C_DEVICE_NAME, SSD1306_ADDR)
};