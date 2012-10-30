#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <plat/sys_config.h>

static u32 pio_hdle = 0;
static const char *gpio_para = "gpio_para";
static int nr_gpio_cnt = 68;

void gpio_set_all(int v)
{
	int count = 0;
	char buf[32];

	memset(buf, 0, sizeof(buf));

	for (count=1; count<68; count++) {
		sprintf(buf, "gpio_pin_%d", count);
		gpio_write_one_pin_value(pio_hdle, v, buf);
	}
}


static int __init gpio_test_init(void)
{
  
	pr_info("gpio test init\n");
	pio_hdle = gpio_request_ex(gpio_para, NULL);
	pr_info("pio_hdle: %u\n", pio_hdle);

    if(SCRIPT_PARSER_OK != script_parser_fetch("gpio_para", "gpio_num", 
				&nr_gpio_cnt, sizeof(nr_gpio_cnt)/sizeof(__u32))) {
		printk("fetch gpio_num error\n");
		nr_gpio_cnt = 67;
	}

	printk("gpio count: %d\n", nr_gpio_cnt);

	gpio_set_all(0);
	gpio_set_all(1);

	return 0;
}
module_init(gpio_test_init);

static void __exit gpio_test_exit(void)
{
	pr_info("gpio_test exit\n");

	gpio_set_all(0);

	gpio_release(pio_hdle, 1);
}
module_exit(gpio_test_exit);

MODULE_LICENSE("GPL");

