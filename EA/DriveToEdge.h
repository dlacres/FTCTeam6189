/****************************************************
 *  DriveToEdge.h                                         
 *  Created on: 18-Apr-2014 11:37:47 AM                      
 *  Implementation of the Class DriveToEdge       
 *  Original author: Working                     
 ****************************************************/

#if !defined(EA_DF14AE85_E2C6_4b22_974D_9A259866F6D0__INCLUDED_)
#define EA_DF14AE85_E2C6_4b22_974D_9A259866F6D0__INCLUDED_


#ifdef __cplusplus
extern "C" {
#endif

#include ""
void Backup();
Drive();
void Turn();	/* Begin - EA generated code for StateMachine */


#include ""


typedef struct DriveToEdge
{
	StateMachineContext base;
	StateEnum m_drivetoedgesm;
} DriveToEdge;

DriveToEdge* DriveToEdge_New(ContextManager* pManager, String1024 sInstanceName);
/* transition proc */
void DriveToEdge_TransitionProc(DriveToEdge* this, TransitionEnum transition, Signal* signal, StateData* submachineState);
void DriveToEdge_Turn__TO__Forward_4_effect(DriveToEdge* this, Signal* signal);
void DriveToEdge_Turn__TO__Forward_4(DriveToEdge* this, Signal* signal, StateData* submachineState);
void DriveToEdge_Forward__TO__Backup_2_effect(DriveToEdge* this, Signal* signal);
void DriveToEdge_Forward__TO__Backup_2(DriveToEdge* this, Signal* signal, StateData* submachineState);
void DriveToEdge_Initial_4__TO__Forward_1_effect(DriveToEdge* this, Signal* signal);
void DriveToEdge_Initial_4__TO__Forward_1(DriveToEdge* this, Signal* signal, StateData* submachineState);
void DriveToEdge_Backup__TO__Turn_3_effect(DriveToEdge* this, Signal* signal);
void DriveToEdge_Backup__TO__Turn_3(DriveToEdge* this, Signal* signal, StateData* submachineState);
/* state proc */
bool DriveToEdge_StateProc(DriveToEdge* this, StateEnum state, StateData* submachineState, StateBehaviorEnum behavior, Signal* signal, EntryTypeEnum enumEntryType, EntryEnum entryArray[], int nArrayCount);
bool DriveToEdge_DriveToEdgeSM_Forward(DriveToEdge* this, StateBehaviorEnum behavior, StateData* submachineState, Signal* signal, EntryTypeEnum enumEntryType, EntryEnum entryArray[], int nArrayCount);
bool DriveToEdge_DriveToEdgeSM_Forward_behavior(DriveToEdge* this, StateBehaviorEnum behavior);
bool DriveToEdge_DriveToEdgeSM_Backup(DriveToEdge* this, StateBehaviorEnum behavior, StateData* submachineState, Signal* signal, EntryTypeEnum enumEntryType, EntryEnum entryArray[], int nArrayCount);
bool DriveToEdge_DriveToEdgeSM_Backup_behavior(DriveToEdge* this, StateBehaviorEnum behavior);
bool DriveToEdge_DriveToEdgeSM_Turn(DriveToEdge* this, StateBehaviorEnum behavior, StateData* submachineState, Signal* signal, EntryTypeEnum enumEntryType, EntryEnum entryArray[], int nArrayCount);
bool DriveToEdge_DriveToEdgeSM_Turn_behavior(DriveToEdge* this, StateBehaviorEnum behavior);
/* statemachine operations */
void DriveToEdge_runStateMachine(DriveToEdge* this, StateMachineEnum statemachine, StateData* submachineState, Signal* signal, EntryEnum entryArray[], int nEntryCount);
void DriveToEdge_runStateMachine_by_Enum(DriveToEdge* this, StateMachineEnum statemachine);
void DriveToEdge_runStateMachines(DriveToEdge* context);
bool DriveToEdge_dispatch(DriveToEdge* this, Event* event, StateData* toState, bool bCheckOnly);
bool DriveToEdge_defer(DriveToEdge* this, Event* event, StateData* toState, bool bCheckOnly);
long DirectionClk();
long DistanceClk();
short SeeEdge();
	/* End - EA generated code for StateMachine */


#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_DF14AE85_E2C6_4b22_974D_9A259866F6D0__INCLUDED_)*/
 