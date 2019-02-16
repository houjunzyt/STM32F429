#include "GUI.h"
#include "stm32f4xx.h"
#include <rtthread.h>
#include <stdlib.h>
#define GUI_NUMBYTES  1024 * 4096	// ����4M�ֽڵ�SDRAM��emWin

//	emWinʹ�õ�SDRAM��ʼ��ַ�������ַǰ���SDRAM�ռ��ѻ��ָ�LTDC���Դ�
//	����Ԥ����emWin ʹ��32λɫ���������Լ���˫������Ŀռ�
//	���㷽������32λ��ɫ��ʽΪ����ÿ�����ص�ռ4�ֽڣ���ʹ��emWin������ÿ������ռ�Ϊ��480*272*4*3
//
#define GUI_EXTBUFADD  0xD02FD000
//U32 aMemory[GUI_NUMBYTES / 4] __EXRAM;
#define GUI_BLOCKSIZE (500)
void GUI_X_Config(void) 
{
	static U32 aMemory[GUI_NUMBYTES / 4] __attribute__((at(GUI_EXTBUFADD)));
  GUI_ALLOC_AssignMemory(aMemory, GUI_NUMBYTES);
}

/*************************** End of file ****************************/
