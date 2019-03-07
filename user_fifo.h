/* **************************************************************************************
 * All Rights Reserved
 * Pico
 * **************************************************************************************
 * Name : user_fifo.h
 *
 * Description : 
 *
 * Author :Solen Liu <solen.liu@picovr.com>
 *
 * Date : 2019/03/06
 *
 * ************************************************************************************** */
 #ifndef USER_FIFO_H
 #define USER_FIFO_H
 #include <stdint.h>
 #include "nrf_log.h"
 #include "nrf_log_ctrl.h"
 #include "nrf_log_default_backends.h"
 #define  USER_FIFO_LOG_ENABLE
 #ifdef USER_FIFO_LOG_ENABLE
 #define user_fifo_log(format,...)    NRF_LOG_INFO("FILE: %s, FUNCTION: %s, LINE: %d: "format"", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
 #else
 #define user_spis_log(format,...) 
 #endif
 #define FIFO_MAX_LENGTH 320 /*< DataLength X DataNumber  < FIFO_MAX_LENGTH*/
 typedef struct
 {
	 uint16_t WriteIndex;
	 uint16_t ReadIndex;
	 uint8_t DataBuff[FIFO_MAX_LENGTH];
	 uint16_t DataLength;
	 uint16_t DataNumber;
 }T_FIFO;
extern void FIFO_Init(T_FIFO *t_Fifo,uint16_t length,uint16_t number);
extern int FIFO_Put(T_FIFO *t_Fifo,uint8_t *databuff);
extern int FIFO_Get(T_FIFO *t_Fifo,uint8_t *databuff);
extern int FIFO_Put_Size(T_FIFO *t_Fifo); 
extern int FIFO_Get_Size(T_FIFO *t_Fifo);
 #endif
