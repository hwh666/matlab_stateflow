#ifndef __SF_FSM_H
#define __SF_FSM_H

#define ACC_ONCE		(5)
#define MaxPlusSpeed	(60)
#define MaxMinusSpeed	(-20)

typedef enum{
	state_R,					//(Reverse)倒车档
	state_P,					//(Parking)停车档
	state_D_low,				//(Drive)前进(低速)档
	state_D_mid,				//(Drive)前进(中速)档
	state_D_high,				//(Drive)前进(高速)档
}CarState_e;					//汽车档位状态

typedef enum{
    event_null,					//无事件触发
	shift_up,					//摇杆加档
	shift_down,					//摇杆减档
}CarEvent_e;                    //汽车触发事件

typedef enum{
    acc_state_null,				//无加减速
	acc_up,						//加速
	acc_down, 					//减速
}AccState_e;                    //油门状态

typedef enum{
	Lock,
	UnLock,
	BreakReverse,
	BrakeLow,
	BrakeMid,
	BrakeHigh,
}BrakeState_e;                //运行状态

typedef struct msg_in_s		//note: linux内核中 _s后缀表示struct（一个结构体）_t后缀表示一个type(一个类型)
{
	CarEvent_e CarEvent;		//触发事件
	AccState_e AccState;		//油门状态
    float      speed;           //速度
}msg_in_t;               


typedef struct msg_out_s
{
	float      acc;             //加速度
	CarState_e CurState;		//FSM当前状态
    BrakeState_e BrakeState;    //刹车状态
}msg_out_t;

extern msg_in_t  g_msg_in;
extern msg_out_t g_msg_out;
float acc_update(CarState_e CarEvent);
#endif
