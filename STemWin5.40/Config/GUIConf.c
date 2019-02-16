#include "GUI.h"
#include "stm32f4xx.h"
#include <rtthread.h>
#include <stdlib.h>
#define GUI_NUMBYTES  1024 * 4096	// 分配4M字节的SDRAM给emWin

//	emWin使用的SDRAM起始地址，这个地址前面的SDRAM空间已划分给LTDC做显存
//	这里预留了emWin 使用32位色、三缓冲以及开双层所需的空间
//	计算方法，以32位颜色格式为例，每个像素点占4字节，则使用emWin三缓冲每层所需空间为：480*272*4*3
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
