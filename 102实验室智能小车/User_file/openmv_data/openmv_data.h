#ifndef __OPENMV_E
#define __OPENMV_E
#include "sys.h"
#include "string.h"
typedef struct
{
   unsigned char  data[3]; 
	unsigned int datas[1];
}openmv;

extern openmv openmv_data;
void OPNMV_DataHandle(unsigned char ucData);

#endif









