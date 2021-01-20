/*
*********************************************************************************************************
* Filename      : sf_interface.c 
* Author        : 郝wh                                      
* Version       : V0.0.1_Alpha
* Data			: 2021.1.19
* Note(s)       :与stateflow接口函数
*********************************************************************************************************
*/

#include "sf_interface.h"
#include "Key.h"

float Car_Speed;

msg_in_t FSM_in_Fun(void)
{
   msg_in_t p_msg_in = {event_null,acc_state_null,0};
	static uint8_t Key0_D2U_Flag = 0;
	static uint8_t Key2_D2U_Flag = 0;

   p_msg_in.speed = Car_Speed;
	/*加减挡判断*/
	if(KEY0==0){				                //档位+
		if(Key0_D2U_Flag == 0){                 //松手检测标志位：while(KEY0==1)升级版写法
			p_msg_in.CarEvent = shift_up;
			Key0_D2U_Flag = 1;
		}else{
			p_msg_in.CarEvent = event_null;
		}
	}
	else if(KEY2==0){			                //档位-
		if(Key2_D2U_Flag == 0){                 //松手检测标志位：while(KEY0==1)升级版写法
			p_msg_in.CarEvent = shift_down;
			Key2_D2U_Flag = 1;
		}else{
			p_msg_in.CarEvent = event_null;
		}
	}else{
		p_msg_in.CarEvent = event_null;
		Key0_D2U_Flag = 0;
		Key2_D2U_Flag = 0;
	}
	/*加减速判断*/
	if(WK_UP==1){			                    //速度+ 
		p_msg_in.AccState = acc_up;
	}
	else if(KEY1==0){			                //速度-
		p_msg_in.AccState = acc_down;
	}
	else{
		p_msg_in.AccState = acc_state_null;
	}
	return p_msg_in;
}

void FSM_out_Fun(msg_out_t p_msg_out)
{
	const uint8_t speed_update_cycle = 20;	//20ms执行一次
	float p_acc;
	/*加载刹车时加速度值(因为无事件触发时加速度恒为0,刹车时需要一直有加速度直到停车)*/
	switch(p_msg_out.BrakeState){
		case BreakReverse:  p_acc= 10; break;	//倒车时刹车制动加速度值
		case BrakeLow:      p_acc=-10; break;	//低速时刹车制动加速度值
		case BrakeMid:      p_acc=-20; break;    //中速时刹车制动加速度值
		case BrakeHigh:     p_acc=-30; break;    //高速时刹车制动加速度值
		default: p_acc = p_msg_out.acc;break;
	}

	Car_Speed = Car_Speed + p_acc * speed_update_cycle/1000;	//v = v + at;
	switch(p_msg_out.CurState){
		case state_R: 	
			if(Car_Speed <= MaxMinusSpeed){					//限制倒车最大速度
				Car_Speed = MaxMinusSpeed;
			}else if(Car_Speed >=0){			
				Car_Speed = 0;			
			}			
			break;			
		case state_P:	
			if(p_msg_out.BrakeState == BreakReverse){
				if(Car_Speed >=0){
					Car_Speed =0;
				}
			}else{
				if(Car_Speed <=0){
					Car_Speed =0;
				}
			}
			break;
		case state_D_low:
		case state_D_mid:
		case state_D_high:
			if(Car_Speed <=0){
				Car_Speed = 0;
			}else if(Car_Speed >= MaxPlusSpeed){
				Car_Speed = MaxPlusSpeed;
			}
			break;
		default:	break;
	}
}



