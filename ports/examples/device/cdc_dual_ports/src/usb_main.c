/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-07     chenyingchun portting for rt-thread
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "tusb.h"

#include <rtthread.h>

#define THREAD_PRIORITY      20
#define THREAD_STACK_SIZE    (1024 * 2)
#define THREAD_TIMESLICE     5

// echo to either Serial0 or Serial1
// with Serial0 as all lower case, Serial1 as all upper case
static void echo_serial_port(uint8_t itf, uint8_t buf[], uint32_t count)
{
  for(uint32_t i=0; i<count; i++)
  {
    if (itf == 0)
    {
      // echo back 1st port as lower case
      if (isupper(buf[i])) buf[i] += 'a' - 'A';
    }
    else
    {
      // echo back 2nd port as upper case
      if (islower(buf[i])) buf[i] -= 'a' - 'A';
    }

    tud_cdc_n_write_char(itf, buf[i]);
  }
  tud_cdc_n_write_flush(itf);
}

//--------------------------------------------------------------------+
// USB CDC
//--------------------------------------------------------------------+
static void cdc_task(void)
{
  uint8_t itf;

  for (itf = 0; itf < CFG_TUD_CDC; itf++)
  {
    // connected() check for DTR bit
    // Most but not all terminal client set this when making connection
    // if ( tud_cdc_n_connected(itf) )
    {
      if ( tud_cdc_n_available(itf) )
      {
        uint8_t buf[64];

        uint32_t count = tud_cdc_n_read(itf, buf, sizeof(buf));

        // echo back to both serial ports
        echo_serial_port(0, buf, count);
        echo_serial_port(1, buf, count);
      }
    }
  }
}

static void thread_entry(void *parameter)
{
    board_init();
    tusb_init();

    while (1)
    {
        tud_task(); // tinyusb device task
        cdc_task();
    }
}


int usb_main(void)
{
    /* 指向线程控制块的指针 */
    rt_thread_t tid = RT_NULL;

    /* 创建线程 */
    tid = rt_thread_create("thread1",
                           thread_entry, RT_NULL,
                           THREAD_STACK_SIZE,
                           THREAD_PRIORITY, THREAD_TIMESLICE);
    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}





/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(usb_main, usb_main sample);