/*
*********************************************************************************************************
* Filename      : sf_fsm.c 	     利用stateflow实现有限元状态机FSM(Finite State Machine)
* Author        : 郝wh                                      
* Version       : V0.0.1_Alpha
* Data			: 2021.1.18-23:15
*********************************************************************************************************
* Note(s) 
* 1.FSM(Finite State Machine) 有限元状态机："有限"二字表示：系统有有限个状态，不存在未知状态
*    在多状态处理时，一般采用 if-else 或者用 switch来实现功能，
*	 但当 ①状态较多   ②状态迁移条件复杂或较多 ③各状态之间存在嵌套情况 时采用状态机编程思想
* 2.利用matlab下simulink工具箱下的stateflow能够能加高效的进行状态机的开发(鼓励使用matlab进行代码开发)
*    使用stateflow进行开发一般流程如下：
*	    		    		┌───────┐
*       		         	│       │ 
*				   g_msg_in │ 		│ g_msg_out
*   输入预处理函数 ─────────→│  FSM  │──────────→  输出处理函数  
*				            │		│
*							│ 		│
*							└───────┘	
*	使用stateflow进行状态机开发时常见的思路是:输入当前系统各个状态，经过状态机处理后，输出一些标志位或者进行赋值
*   状态机不会直接进行功能处理，只对变量进行赋值，这样做使代码分层清晰、各子系统低耦合、且可维护性高
*********************************************************************************************************
*/

#include "sf_fsm.h"

float Car_Speed;
msg_in_t  g_msg_in;
msg_out_t g_msg_out;

float acc_update(CarState_e CarEvent)
{
	float p_acc;
	switch(CarEvent){
		case state_R: 	
			if(g_msg_in.AccState == acc_up){					 
				p_acc = -ACC_ONCE;
			}else if(g_msg_in.AccState == acc_down){			
				p_acc =  ACC_ONCE;			
			}
			else{
				p_acc =  0;
			}			
			break;			
		case state_P:	
			p_acc =  0;
			break;
		case state_D_low:
		case state_D_mid:
		case state_D_high:
			if(g_msg_in.AccState == acc_up){					 
				p_acc =  ACC_ONCE;
			}else if(g_msg_in.AccState == acc_down){			
				p_acc = -ACC_ONCE;			
			}
			else{
				p_acc =  0;
			}
			break;
		default:	break;
	}
	return p_acc;
}


