/*----------------------------------------------------------------------------
 * Copyright (c) <2018>, <Huawei Technologies Co., Ltd>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Notice of Export Control Law
 * ===============================================
 * Huawei LiteOS may be subject to applicable export control laws and regulations, which might
 * include those applicable to Huawei LiteOS of U.S. and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 *---------------------------------------------------------------------------*/
/**
 *  DATE                AUTHOR      INSTRUCTION
 *  2019-05-14 17:21  zhangqianfu  The first version
 *
 */
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include <osal.h>
#include <oc_lwm2m_al.h>
#include <link_endian.h>

#include "E53_IA1.h"
#include "lcd.h"

#include <gpio.h>
#include <stm32l4xx_it.h>

#define cn_endpoint_id "changteng"
#define cn_app_server "119.3.250.80"
#define cn_app_port "5683"

#define cn_app_Agriculture 0x0
#define cn_app_Agriculture_Control_Light 0x1
#define cn_app_response_Agriculture_Control_Light 0x2
#define cn_app_Agriculture_Control_Motor 0x3
#define cn_app_response_Agriculture_Control_Motor 0x4

#pragma pack(1)
typedef struct
{
    int8_t messageId;
    int8_t Temperature;
    int8_t Humidity;
    uint16_t Luminance;
} tag_app_Agriculture;

typedef struct
{
    int8_t messageId;
    uint16_t mid;
    int8_t errcode;
    int8_t Light_State;
} tag_app_Response_Agriculture_Control_Light;

typedef struct
{
    int8_t messageId;
    uint16_t mid;
    int8_t errcode;
    int8_t Motor_State;
} tag_app_Response_Agriculture_Control_Motor;

typedef struct
{
    int8_t messageId;
    uint16_t mid;
    char Light[3];
} tag_app_Agriculture_Control_Light;

typedef struct
{
    uint8_t messageId;
    uint16_t mid;
    char Motor[3];
} tag_app_Agriculture_Control_Motor;
#pragma pack()

E53_IA1_Data_TypeDef E53_IA1_Data;

//if your command is very fast,please use a queue here--TODO
#define cn_app_rcv_buf_len 128
static int s_rcv_buffer[cn_app_rcv_buf_len];
static int s_rcv_datalen;
static osal_semp_t s_rcv_sync;

//use this function to push all the message to the buffer
static int app_msg_deal(void *usr_data, en_oc_lwm2m_msg_t type, void *data, int len)
{
    unsigned char *msg;
    msg = data;
    int ret = -1;

    if (len <= cn_app_rcv_buf_len)
    {
        if (msg[0] == 0xaa && msg[1] == 0xaa)
        {
            printf("OC respond message received! \n\r");
            return ret;
        }
        memcpy(s_rcv_buffer, msg, len);
        s_rcv_datalen = len;

        (void)osal_semp_post(s_rcv_sync);

        ret = 0;
    }
    return ret;
}

static int app_cmd_task_entry()
{
    int ret = -1;
    tag_app_Response_Agriculture_Control_Light Response_Agriculture_Control_Light;
    tag_app_Response_Agriculture_Control_Motor Response_Agriculture_Control_Motor;
    tag_app_Agriculture_Control_Light *Agriculture_Control_Light;
    tag_app_Agriculture_Control_Motor *Agriculture_Control_Motor;
    int8_t msgid;

    while (1)
    {
        if (osal_semp_pend(s_rcv_sync, cn_osal_timeout_forever))
        {
            msgid = s_rcv_buffer[0] & 0x000000FF;
             //**********************云平台控制：命令下发****************************************//
            switch (msgid)
            {
            case cn_app_Agriculture_Control_Light:
                Agriculture_Control_Light = (tag_app_Agriculture_Control_Light *)s_rcv_buffer;
                printf("Agriculture_Control_Light:msgid:%d mid:%d", Agriculture_Control_Light->messageId, ntohs(Agriculture_Control_Light->mid));
                /********** code area for cmd from IoT cloud  **********/
                if (Agriculture_Control_Light->Light[0] == 'O' && Agriculture_Control_Light->Light[1] == 'N')
                {
                    HAL_GPIO_WritePin(IA1_Light_GPIO_Port, IA1_Light_Pin, GPIO_PIN_SET);
                    Response_Agriculture_Control_Light.messageId = cn_app_response_Agriculture_Control_Light;
                    Response_Agriculture_Control_Light.mid = Agriculture_Control_Light->mid;
                    Response_Agriculture_Control_Light.errcode = 0;
                    Response_Agriculture_Control_Light.Light_State = 1;
                    oc_lwm2m_report((char *)&Response_Agriculture_Control_Light, sizeof(Response_Agriculture_Control_Light), 1000); ///< report cmd reply message
                }
                if (Agriculture_Control_Light->Light[0] == 'O' && Agriculture_Control_Light->Light[1] == 'F' && Agriculture_Control_Light->Light[2] == 'F')
                {
                    HAL_GPIO_WritePin(IA1_Light_GPIO_Port, IA1_Light_Pin, GPIO_PIN_RESET);
                    Response_Agriculture_Control_Light.messageId = cn_app_response_Agriculture_Control_Light;
                    Response_Agriculture_Control_Light.mid = Agriculture_Control_Light->mid;
                    Response_Agriculture_Control_Light.errcode = 0;
                    Response_Agriculture_Control_Light.Light_State = 0;
                    oc_lwm2m_report((char *)&Response_Agriculture_Control_Light, sizeof(Response_Agriculture_Control_Light), 1000); ///< report cmd reply message
                }
                /********** code area end  **********/
                break;
            case cn_app_Agriculture_Control_Motor:
                Agriculture_Control_Motor = (tag_app_Agriculture_Control_Motor *)s_rcv_buffer;
                printf("Agriculture_Control_Motor:msgid:%d mid:%d", Agriculture_Control_Motor->messageId, ntohs(Agriculture_Control_Motor->mid));
                /********** code area for cmd from IoT cloud  **********/
                if (Agriculture_Control_Motor->Motor[0] == 'O' && Agriculture_Control_Motor->Motor[1] == 'N')
                {
                    HAL_GPIO_WritePin(IA1_Motor_GPIO_Port, IA1_Motor_Pin, GPIO_PIN_SET);
                    Response_Agriculture_Control_Motor.messageId = cn_app_response_Agriculture_Control_Motor;
                    Response_Agriculture_Control_Motor.mid = Agriculture_Control_Motor->mid;
                    Response_Agriculture_Control_Motor.errcode = 0;
                    Response_Agriculture_Control_Motor.Motor_State = 1;
                    oc_lwm2m_report((char *)&Response_Agriculture_Control_Motor, sizeof(Response_Agriculture_Control_Motor), 1000); ///< report cmd reply message
                }
                if (Agriculture_Control_Motor->Motor[0] == 'O' && Agriculture_Control_Motor->Motor[1] == 'F' && Agriculture_Control_Motor->Motor[2] == 'F')
                {
                    HAL_GPIO_WritePin(IA1_Motor_GPIO_Port, IA1_Motor_Pin, GPIO_PIN_RESET);
                    Response_Agriculture_Control_Motor.messageId = cn_app_response_Agriculture_Control_Motor;
                    Response_Agriculture_Control_Motor.mid = Agriculture_Control_Motor->mid;
                    Response_Agriculture_Control_Motor.errcode = 0;
                    Response_Agriculture_Control_Motor.Motor_State = 0;
                    oc_lwm2m_report((char *)&Response_Agriculture_Control_Motor, sizeof(Response_Agriculture_Control_Motor), 1000); ///< report cmd reply message
                }
                /********** code area end  **********/
                break;
            default:
                break;
            }
        }
    }

    return ret;
}

static int app_report_task_entry()
{
    int ret = -1;

    oc_config_param_t oc_param;
    tag_app_Agriculture Agriculture;

    (void)memset(&oc_param, 0, sizeof(oc_param));

    oc_param.app_server.address = cn_app_server;
    oc_param.app_server.port = cn_app_port;
    oc_param.app_server.ep_id = cn_endpoint_id;
    oc_param.boot_mode = en_oc_boot_strap_mode_factory;
    oc_param.rcv_func = app_msg_deal;

    ret = oc_lwm2m_config(&oc_param);
    if (0 != ret)
    {
        return ret;
    }
    //**********************云平台控制：上报****************************************//
    //install a dealer for the led message received
    while (1) //--TODO ,you could add your own code here
    {
        Agriculture.messageId = cn_app_Agriculture;
        Agriculture.Temperature = (int8_t)E53_IA1_Data.Temperature;
        Agriculture.Humidity = (int8_t)E53_IA1_Data.Humidity;
        Agriculture.Luminance = htons((uint16_t)E53_IA1_Data.Lux);
        oc_lwm2m_report((char *)&Agriculture, sizeof(Agriculture), 1000);
        osal_task_sleep(2 * 1000);
    }
    return ret;
}
extern UART_HandleTypeDef uart_comm;
uint8_t comm_data[16] = {0};

        

static int app_collect_task_entry()
{
    Init_E53_IA1();
    while (1)
    {
        E53_IA1_Read_Data();
        printf("\r\n******************************Lux Value is  %d\r\n", (int)E53_IA1_Data.Lux);
        printf("\r\n******************************Humidity is  %d\r\n", (int)E53_IA1_Data.Humidity);
        printf("\r\n******************************Temperature is  %d\r\n", (int)E53_IA1_Data.Temperature);

        //**********************智能控制****************************************//
        //光照信息：
        if (E53_IA1_Data.Lux <= 10)
        {
            HAL_GPIO_WritePin(IA1_Light_GPIO_Port, IA1_Light_Pin, GPIO_PIN_SET);
        }
        else if( E53_IA1_Data.Lux >= 1000)
        {
            HAL_GPIO_WritePin(IA1_Light_GPIO_Port, IA1_Light_Pin, GPIO_PIN_RESET);
        }

        //温度信息
        if (E53_IA1_Data.Temperature >= 37)
        {
            HAL_GPIO_WritePin(IA1_Motor_GPIO_Port, IA1_Motor_Pin, GPIO_PIN_SET);
        }
        else if(E53_IA1_Data.Temperature <= 25)
        {
            HAL_GPIO_WritePin(IA1_Motor_GPIO_Port, IA1_Motor_Pin, GPIO_PIN_RESET);
        }

        //湿度信息
        if (E53_IA1_Data.Humidity >= 50)
        {
            HAL_GPIO_WritePin(IA1_Motor_GPIO_Port, IA1_Motor_Pin, GPIO_PIN_RESET);
        }
        else if(E53_IA1_Data.Humidity <= 20)
        {
            HAL_GPIO_WritePin(IA1_Motor_GPIO_Port, IA1_Motor_Pin, GPIO_PIN_SET);
        }

        //**********************信息获取和显示****************************************//
        //判断马达状态
        if (HAL_GPIO_ReadPin(IA1_Motor_GPIO_Port, IA1_Motor_Pin) == GPIO_PIN_SET)
        {
            LCD_ShowString(134, 158, 200, 16, 24, "  ON");
        }
        else if (HAL_GPIO_ReadPin(IA1_Motor_GPIO_Port, IA1_Motor_Pin) == GPIO_PIN_RESET)
        {
            LCD_ShowString(134, 158, 200, 16, 24, " OFF");
        }
        //判断灯状态
        if (HAL_GPIO_ReadPin(IA1_Light_GPIO_Port, IA1_Light_Pin) == GPIO_PIN_SET)
        {
             LCD_ShowString(134, 192, 200, 16, 24, "  ON");
        }
        else if (HAL_GPIO_ReadPin(IA1_Light_GPIO_Port, IA1_Light_Pin) == GPIO_PIN_RESET)
        {
             LCD_ShowString(134, 192, 200, 16, 24, " OFF");
        }


        //LCD_ShowString(10, 140, 200, 16, 16, "Temperature:");
        LCD_ShowNum(134, 63, (int)E53_IA1_Data.Temperature, 4, 24);
        //LCD_ShowString(10, 170, 200, 16, 16, "Humidity:");
        LCD_ShowNum(134, 90, (int)E53_IA1_Data.Humidity, 4, 24);
        //LCD_ShowString(10, 200, 200, 16, 16, "Luminance:");
        LCD_ShowNum(134, 120, (int)E53_IA1_Data.Lux, 4, 24);
        comm_data[0] = 'C';
        comm_data[1] = 'O';
        comm_data[2] = 'M';
        comm_data[3] = 'M';

         comm_data[4] = (int)E53_IA1_Data.Temperature / 1000 % 10 + '0';//千+‘0’为了转变成ASCII码
        comm_data[5] = (int)E53_IA1_Data.Temperature / 100 % 10 + '0';//百
        comm_data[6] = (int)E53_IA1_Data.Temperature / 10 % 10 + '0';//十
        comm_data[7] = (int)E53_IA1_Data.Temperature % 10 + '0';//个

        comm_data[8] = (int)E53_IA1_Data.Humidity / 1000 % 10 + '0';
        comm_data[9] = (int)E53_IA1_Data.Humidity / 100 % 10 + '0';
        comm_data[10] = (int)E53_IA1_Data.Humidity / 10 % 10 + '0';
        comm_data[11] = (int)E53_IA1_Data.Humidity % 10 + '0';

        comm_data[12] = (int)E53_IA1_Data.Lux / 1000 % 10 + '0';
        comm_data[13] = (int)E53_IA1_Data.Lux / 100 % 10 + '0';
        comm_data[14] = (int)E53_IA1_Data.Lux / 10 % 10 + '0';
        comm_data[15] = (int)E53_IA1_Data.Lux % 10 + '0';

        HAL_UART_Transmit(&uart_comm, &comm_data, 16, 0xff);
        osal_task_sleep(2 * 1000);
    }

    return 0;
}

#include <stimer.h>

int standard_app_demo_main()
{
    LCD_Clear(BLACK);
    POINT_COLOR = GREEN;
    extern const unsigned char gImage_nonyye[115208] ;
    LCD_Show_Image(0, 0, 240, 240, gImage_nonyye);
    //LCD_ShowString(10, 10, 200, 16, 24, "Welcome to BearPi");
    //LCD_ShowString(15, 40, 200, 16, 24, "Agriculture Demo");
    //LCD_ShowString(10, 80, 200, 16, 16, "NCDP_IP:");
    //LCD_ShowString(80, 80, 200, 16, 16, cn_app_server);
    //LCD_ShowString(10, 110, 200, 16, 16, "NCDP_PORT:");
    //LCD_ShowString(100, 110, 200, 16, 16, cn_app_port);

    osal_semp_create(&s_rcv_sync, 1, 0);

    osal_task_create("app_collect", app_collect_task_entry, NULL, 0x400, NULL, 3);
    osal_task_create("app_report", app_report_task_entry, NULL, 0x1000, NULL, 2);
    osal_task_create("app_command", app_cmd_task_entry, NULL, 0x1000, NULL, 3);

    //**********************设备端控制****************************************//
    osal_int_connect(KEY1_EXTI_IRQn, 2, 0, Key1_IRQHandler, NULL);
    osal_int_connect(KEY2_EXTI_IRQn, 3, 0, Key2_IRQHandler, NULL);
    return 0;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    switch (GPIO_Pin)
    {
    case KEY1_Pin:
        HAL_GPIO_TogglePin(IA1_Motor_GPIO_Port, IA1_Motor_Pin);
        break;
    case KEY2_Pin:
        HAL_GPIO_TogglePin(IA1_Light_GPIO_Port, IA1_Light_Pin);
        break;
    default:
        break;
    }
}
void UART2_Control(unsigned char buf)
{
//	HAL_UART_Transmit(&huart1,&data,1,0);
	//收到“1”，电灯，收到“2”，灭灯
	if(buf == 'M')
	{
		HAL_GPIO_TogglePin(IA1_Motor_GPIO_Port,IA1_Motor_Pin);
	}
	else if(buf == 'L')
	{
		HAL_GPIO_TogglePin(IA1_Light_GPIO_Port,IA1_Light_Pin);
	}
}