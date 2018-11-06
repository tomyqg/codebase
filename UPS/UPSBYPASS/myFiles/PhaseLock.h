//-------------------------------------------------------------
// 文件名： "Scr.h"
//-------------------------------------------------------------
//功能：	1.包含Scr.c所用头文件
//		2.进行相关宏定义
//      3.声明全局变量
//-------------------------------------------------------------
// 作者： 刘亚彬
// 创建日期：2016年12月27日
// 修改日期：
// 版本：v0.1
//-------------------------------------------------------------

#ifndef PHASELOCK_H
#define PHASELOCK_H

//-------------------------------------------------------------
// INCLUDE
//-------------------------------------------------------------
#include "GlobalDefine.h"
#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "Scr.h"
#include "SampleAndControl.h"

//-------------------------------------------------------------

//-------------------------------------------------------------
// 宏定义
//-------------------------------------------------------------


//-------------------------------------------------------------
// 结构体声明
//-------------------------------------------------------------

//标志位位段
typedef struct PLFlag
{								//	bit	description
	Uint16 CurFreOF:1;			//	0:	当前捕获频率溢出
	Uint16 HisFreOF:1;			//	1:	历史上有无捕获溢出
	Uint16 lastCalOF:1;			//	2：	上一次计算溢出
	Uint16 HisCalOF:1;			//	3:	历史上有一次计算溢出
} PLFlag;

//锁相模块	最大测量周期为28s
typedef struct PhaseLock
{
	//属性
	State State;			//频率检测使能
	State StatePL;			//锁相同步使能位
	float PhaseComp;		//相位补偿值,由于变压器接法不同会导致测量的
							//相位变换，因此需要进行补偿(取值范围:0-1,单位:周期)
	PhaseShiftDir PSD;		//相位移动方向
	PLFlag Flag;			//标志位
	Uint32 ZeroTimeAct;		//执行机构过零点时刻

	//方法
	Uint16 (*Init)(void);	//初始化
	Uint16 (*ChangeState)(State state);			//改变状态（频率检测）
	Uint16 (*PhaseLockCmd)(State state);		//锁相使能
	Uint16 (*Scan)(void);						//锁相扫描
	void (*CapOverFlowCallback)(void);			//捕获溢出回调函数
	void (*CalOverFlowCallback)(void);			//计算溢出回调函数
}PhaseLock;

//-------------------------------------------------------------
// 全局变量声明
//-------------------------------------------------------------
extern PhaseLock myPhaseLock;

//-------------------------------------------------------------
// 函数声明
//-------------------------------------------------------------
void UsePhaseLock(void);
interrupt void ECap2_ISR(void);
interrupt void ECap5_ISR(void);
#endif
