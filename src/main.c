#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/sensor/ccs811.h>

int main(void)
{
const struct device *ccs811= DEVICE_DT_GET_ANY(ams_ccs811); 
struct sensor_value co2, tvoc; 
int rc = 0;

printk("TRY INIT");

if (!device_is_ready(ccs811))
{

printk("NOT GOOD TO START");

return 1;

}

printk("GOOD TO START");

while (true)

{

rc  = sensor_sample_fetch(ccs811);

sensor_channel_get(ccs811, SENSOR_CHAN_CO2, &co2);
sensor_channel_get(ccs811, SENSOR_CHAN_VOC, &tvoc);
printk("\nCCS811: %u ppm eCO2; %u ppb eTVOC\n", co2.val1, tvoc.val1);

k_sleep(K_SECONDS(2));
}
return 0;
}