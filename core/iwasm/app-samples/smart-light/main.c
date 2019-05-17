/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>

//User LED
#define LED_PORT "GPIOA"
#define LED 5

//User KEY
#define KEY_PORT "GPIOC"
#define KEY 13

/** GPIO pin to be input. */
#define GPIO_DIR_IN (0 << 0)

/** GPIO pin to be output. */
#define GPIO_DIR_OUT (1 << 0)

void *device_get_binding(const char *);
int gpio_pin_configure(void *, unsigned int, int);
int gpio_pin_read(void *, unsigned int, unsigned int *);
int gpio_pin_write(void *, unsigned int, unsigned int);

int main(int argc, char **argv)
{
    unsigned int gpio_value;
    unsigned char flag = 0;
    struct device *dev, *key_dev;

    dev = device_get_binding(LED_PORT);
    /* Set LED pin as output */
    gpio_pin_configure(dev, LED, GPIO_DIR_OUT);

    key_dev = device_get_binding(KEY_PORT);
    /* Set KEY pin as input */
    gpio_pin_configure(key_dev, KEY, GPIO_DIR_IN);

    while (1) {
        gpio_pin_read(key_dev, KEY, &gpio_value);
        if (!gpio_value) {
            gpio_pin_write(dev, LED, 1);
            if (!flag) {
                printf("object detected\n");
                flag = 1;
            }
        } else {
            gpio_pin_write(dev, LED, 0);
            flag = 0;
        }
    }
    return 0;
}
