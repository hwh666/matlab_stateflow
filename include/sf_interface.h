#ifndef __SF_INTERFACE_H
#define __SF_INTERFACE_H

#include "sf_fsm.h"

extern float Car_Speed;
msg_in_t FSM_in_Fun(void);
void FSM_out_Fun(msg_out_t p_msg_out);

#endif

