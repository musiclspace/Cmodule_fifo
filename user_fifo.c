/* **************************************************************************************
 * All Rights Reserved
 * Pico
 * **************************************************************************************
 * Name : user_fifo.c
 *
 * Description : 
 *
 * Author :Solen Liu <solen.liu@picovr.com>
 *
 * Date : 2019/03/06
 *
 * ***************************************************************************************/
 #include "user_fifo.h"
/***************************************************************************************
 * @Function    : FIFO_Init
 * @Description : FIFO structure initialisation
 * @Input       : T_Fifo * t_Fifo = Handler of FIFO structure
 *              : uint8_t *databuff = first address of array
 *              : uint8_t length = data length 
 *              : uint8_t number = number of data 
 * @Ouptut      : none ; global variable (* t_Fifo) is updated
 ****************************************************************************************/
void FIFO_Init(T_FIFO *t_Fifo,uint16_t length,uint16_t number)
{
	t_Fifo->WriteIndex = 0;
	t_Fifo->ReadIndex = 0;
	t_Fifo->DataLength = length;
	t_Fifo->DataNumber = number;
	memset(t_Fifo->DataBuff,0,length*number);
	if(length*number > FIFO_MAX_LENGTH)
		user_fifo_log("fatal error: Beyond the fifo SPACE!");
}
/***************************************************************************************
 * @Function    : FIFO_Put
 * @Description : Put packet data into FIFO
 * @Input       : T_Fifo * t_Fifo = Handler of FIFO structure
 *              : uint8_t *databuff = first address of array TO input
 * @Ouptut      : return writeindex, if the fifo is full,return -1
 ****************************************************************************************/
int FIFO_Put(T_FIFO *t_Fifo,uint8_t *databuff)
{
	uint16_t WriteIndexNext = t_Fifo->WriteIndex + t_Fifo->DataLength;
	
	if(WriteIndexNext >= (t_Fifo->DataNumber*t_Fifo->DataLength))
	{
		WriteIndexNext = 0;
	}
	if(WriteIndexNext!=t_Fifo->ReadIndex)
	{
		for(uint16_t i = 0;i<t_Fifo->DataLength;i++)
		(t_Fifo->DataBuff)[t_Fifo->WriteIndex+i] = databuff[i];
		
		 t_Fifo->WriteIndex = WriteIndexNext;
		 return t_Fifo->WriteIndex;
	}
	else
		return -1;
}
/***************************************************************************************
 * @Function    : FIFO_Get
 * @Description : Put packet data into FIFO
 * @Input       : T_Fifo * t_Fifo = Handler of FIFO structure
 *              : uint8_t *databuff = first address of array TO read
 * @Ouptut      : return readindex, if the fifo is empry, return -1
 ****************************************************************************************/
int FIFO_Get(T_FIFO *t_Fifo,uint8_t *databuff)
{
	uint16_t ReadIndexNext;
	if(t_Fifo->ReadIndex != t_Fifo->WriteIndex)
	{
		ReadIndexNext = t_Fifo->ReadIndex + t_Fifo->DataLength;
		if(ReadIndexNext>=(t_Fifo->DataNumber*t_Fifo->DataLength))
		{
			ReadIndexNext = 0;
		}
		for(uint16_t i = 0;i<t_Fifo->DataLength;i++)
		databuff[i] = (t_Fifo->DataBuff)[t_Fifo->ReadIndex+i];
		
		t_Fifo->ReadIndex = ReadIndexNext;
		return t_Fifo->ReadIndex;
	}
	else
		return -1;
}
/***************************************************************************************
 * @Function    : FIFO_Put_Size
 * @Description : return the available size to input
 * @Input       : T_Fifo * t_Fifo = Handler of FIFO structure
 * @Ouptut      : return size
 ****************************************************************************************/
int FIFO_Put_Size(T_FIFO *t_Fifo)
{
	int put_size;
	if(t_Fifo->WriteIndex < t_Fifo->ReadIndex)
	  put_size = t_Fifo->ReadIndex - t_Fifo->WriteIndex;
	else
		put_size = t_Fifo->DataNumber - t_Fifo->WriteIndex + t_Fifo->ReadIndex;	
	user_fifo_log("put size = %d",put_size);
	return put_size;
}
/***************************************************************************************
 * @Function    : FIFO_Get_Size
 * @Description : return the available size to read
 * @Input       : T_Fifo * t_Fifo = Handler of FIFO structure
 * @Ouptut      : return size
 ****************************************************************************************/
int FIFO_Get_Size(T_FIFO *t_Fifo)
{
	int get_size;
	if(t_Fifo->ReadIndex <= t_Fifo->WriteIndex)
		get_size = t_Fifo->WriteIndex - t_Fifo->ReadIndex;
	else
		get_size = t_Fifo->DataNumber - t_Fifo->ReadIndex + t_Fifo->WriteIndex;
	user_fifo_log("get size = %d",get_size);
	return get_size;
}
