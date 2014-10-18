/****************************************************
 *  DriveToEdge.c                                         
 *  Created on: 18-Apr-2014 11:37:48 AM                      
 *  Implementation of the Class DriveToEdge       
 *  Original author: Working                     
 ****************************************************/

#include "DriveToEdge.h"

void Backup()
{
	
}

Drive()
{
}

void Turn()
{
	
} 


/* Begin - EA generated code for StateMachine */


/* Begin - EA generated code for StateMachine */
DriveToEdge* DriveToEdge_New(ContextManager* pManager, String1024 sInstanceName)
{
	DriveToEdge* context = (DriveToEdge*)malloc(sizeof(DriveToEdge));
	StateMachineContext_Initialize(&context->base, (void*)context, pManager, sInstanceName, "DriveToEdge");
	/*Initialize Region Variables*/
	context->m_drivetoedgesm = NOSTATE;
	return context;
}

bool DriveToEdge_defer(DriveToEdge* this, Event* event, StateData* toState, bool bCheckOnly)
{
	return false;	/* no statemachines in this context have deferred event pattern */
}


void DriveToEdge_TransitionProc(DriveToEdge* this, TransitionEnum transition, Signal* signal, StateData* submachineState)
{
	switch (transition) {
		case DriveToEdge_ENUM_TURN__TO__FORWARD_4:
			DriveToEdge_Turn__TO__Forward_4(this, signal, submachineState); 
			break;

		case DriveToEdge_ENUM_FORWARD__TO__BACKUP_2:
			DriveToEdge_Forward__TO__Backup_2(this, signal, submachineState); 
			break;

		case DriveToEdge_ENUM_INITIAL_4__TO__FORWARD_1:
			DriveToEdge_Initial_4__TO__Forward_1(this, signal, submachineState); 
			break;

		case DriveToEdge_ENUM_BACKUP__TO__TURN_3:
			DriveToEdge_Backup__TO__Turn_3(this, signal, submachineState); 
			break;
	}
}

void DriveToEdge_Turn__TO__Forward_4_effect(DriveToEdge* this, Signal* signal)
{
	String1024 buffer;
	sprintf(buffer, "%s[%s].Turn__TO__Forward_4 Effect\12", this->base.m_sInstanceName, this->base.m_sType);
	trace(buffer);
	
}

void DriveToEdge_Turn__TO__Forward_4(DriveToEdge* this, Signal* signal, StateData* submachineState) 
{
	if(!StateData_IsActiveState(StateMachineContext_GetStateObject(&this->base, submachineState, DriveToEdge_ENUM_DRIVETOEDGESM_TURN)))
	{
		return;
	}
	DriveToEdge_StateProc(this, DriveToEdge_ENUM_DRIVETOEDGESM_TURN, submachineState, EXIT, 0, DefaultEntry, NULL, 0);
	DriveToEdge_Turn__TO__Forward_4_effect(this, signal);
	DriveToEdge_StateProc(this, DriveToEdge_ENUM_DRIVETOEDGESM_FORWARD, submachineState, ENTRY, signal, DefaultEntry, NULL, 0);
}

void DriveToEdge_Forward__TO__Backup_2_effect(DriveToEdge* this, Signal* signal)
{
	String1024 buffer;
	sprintf(buffer, "%s[%s].Forward__TO__Backup_2 Effect\12", this->base.m_sInstanceName, this->base.m_sType);
	trace(buffer);
	
}

void DriveToEdge_Forward__TO__Backup_2(DriveToEdge* this, Signal* signal, StateData* submachineState) 
{
	if(!StateData_IsActiveState(StateMachineContext_GetStateObject(&this->base, submachineState, DriveToEdge_ENUM_DRIVETOEDGESM_FORWARD)))
	{
		return;
	}
	DriveToEdge_StateProc(this, DriveToEdge_ENUM_DRIVETOEDGESM_FORWARD, submachineState, EXIT, 0, DefaultEntry, NULL, 0);
	DriveToEdge_Forward__TO__Backup_2_effect(this, signal);
	DriveToEdge_StateProc(this, DriveToEdge_ENUM_DRIVETOEDGESM_BACKUP, submachineState, ENTRY, signal, DefaultEntry, NULL, 0);
}

void DriveToEdge_Initial_4__TO__Forward_1_effect(DriveToEdge* this, Signal* signal)
{
	String1024 buffer;
	sprintf(buffer, "%s[%s].Initial_4__TO__Forward_1 Effect\12", this->base.m_sInstanceName, this->base.m_sType);
	trace(buffer);
	
}

void DriveToEdge_Initial_4__TO__Forward_1(DriveToEdge* this, Signal* signal, StateData* submachineState) 
{
	if(submachineState)
		StateData_IncrementActiveCount(submachineState);
	DriveToEdge_Initial_4__TO__Forward_1_effect(this, signal);
	DriveToEdge_StateProc(this, DriveToEdge_ENUM_DRIVETOEDGESM_FORWARD, submachineState, ENTRY, signal, DefaultEntry, NULL, 0);
}

void DriveToEdge_Backup__TO__Turn_3_effect(DriveToEdge* this, Signal* signal)
{
	String1024 buffer;
	sprintf(buffer, "%s[%s].Backup__TO__Turn_3 Effect\12", this->base.m_sInstanceName, this->base.m_sType);
	trace(buffer);
	
}

void DriveToEdge_Backup__TO__Turn_3(DriveToEdge* this, Signal* signal, StateData* submachineState) 
{
	if(!StateData_IsActiveState(StateMachineContext_GetStateObject(&this->base, submachineState, DriveToEdge_ENUM_DRIVETOEDGESM_BACKUP)))
	{
		return;
	}
	DriveToEdge_StateProc(this, DriveToEdge_ENUM_DRIVETOEDGESM_BACKUP, submachineState, EXIT, 0, DefaultEntry, NULL, 0);
	DriveToEdge_Backup__TO__Turn_3_effect(this, signal);
	DriveToEdge_StateProc(this, DriveToEdge_ENUM_DRIVETOEDGESM_TURN, submachineState, ENTRY, signal, DefaultEntry, NULL, 0);
}

bool DriveToEdge_StateProc(DriveToEdge* this, StateEnum state, StateData* submachineState, StateBehaviorEnum behavior, Signal* signal, EntryTypeEnum enumEntryType, EntryEnum entryArray[], int nArrayCount)
{
	switch (state) {
		case DriveToEdge_ENUM_DRIVETOEDGESM_FORWARD:
			return DriveToEdge_DriveToEdgeSM_Forward(this, behavior, submachineState, signal, enumEntryType, entryArray, nArrayCount);

		case DriveToEdge_ENUM_DRIVETOEDGESM_BACKUP:
			return DriveToEdge_DriveToEdgeSM_Backup(this, behavior, submachineState, signal, enumEntryType, entryArray, nArrayCount);

		case DriveToEdge_ENUM_DRIVETOEDGESM_TURN:
			return DriveToEdge_DriveToEdgeSM_Turn(this, behavior, submachineState, signal, enumEntryType, entryArray, nArrayCount);
	}
	return false;
}

bool DriveToEdge_DriveToEdgeSM_Forward(DriveToEdge* this, StateBehaviorEnum behavior, StateData* submachineState, Signal* signal, EntryTypeEnum enumEntryType, EntryEnum entryArray[], int nArrayCount)
{
	StateData*  state = StateMachineContext_GetStateObject(&this->base, submachineState, DriveToEdge_ENUM_DRIVETOEDGESM_FORWARD);
	switch (behavior) {
		case ENTRY:
			if(state->active_count > 0)
				return false;
			this->m_drivetoedgesm = DriveToEdge_ENUM_DRIVETOEDGESM_FORWARD;
			StateData_IncrementActiveCount(state);
			DriveToEdge_DriveToEdgeSM_Forward_behavior(this, ENTRY);
			
			if(enumEntryType == HistoryEntry)
			{
				return true;
			}
			
			DriveToEdge_DriveToEdgeSM_Forward_behavior(this, DO);
			
			if((enumEntryType == EntryPointEntry || enumEntryType == DefaultEntry) && StateData_IsActiveState(state))
				StateMachineContext_DeferInternalEvent(&this->base, COMPLETION, 0, state);
			break;
		case EXIT:
			if(state->active_count == 0)
				return false;
			this->m_drivetoedgesm = NOSTATE;
			StateData_DecrementActiveCount(state);
			DriveToEdge_DriveToEdgeSM_Forward_behavior(this, EXIT);
			StateMachineContext_RemoveInternalEvent(&this->base, state);
			break;
	}
	
	return true;
}

bool DriveToEdge_DriveToEdgeSM_Forward_behavior(DriveToEdge* this, StateBehaviorEnum behavior) 
{
	switch (behavior) {
		case ENTRY:
		{
			String1024 buffer;
			sprintf(buffer, "%s[%s].DriveToEdgeSM_Forward ENTRY\12", this->base.m_sInstanceName, this->base.m_sType);
			trace(buffer);
		}
			break;
		case DO:
		{
			String1024 buffer;
			sprintf(buffer, "%s[%s].DriveToEdgeSM_Forward DO\12", this->base.m_sInstanceName, this->base.m_sType);
			trace(buffer);
			/*
			Forward()
			*/
		}
			break;
		case EXIT:
		{
			String1024 buffer;
			sprintf(buffer, "%s[%s].DriveToEdgeSM_Forward EXIT\12", this->base.m_sInstanceName, this->base.m_sType);
			trace(buffer);
		}
			break;
	}
	
	return true;
}

bool DriveToEdge_DriveToEdgeSM_Backup(DriveToEdge* this, StateBehaviorEnum behavior, StateData* submachineState, Signal* signal, EntryTypeEnum enumEntryType, EntryEnum entryArray[], int nArrayCount)
{
	StateData*  state = StateMachineContext_GetStateObject(&this->base, submachineState, DriveToEdge_ENUM_DRIVETOEDGESM_BACKUP);
	switch (behavior) {
		case ENTRY:
			if(state->active_count > 0)
				return false;
			this->m_drivetoedgesm = DriveToEdge_ENUM_DRIVETOEDGESM_BACKUP;
			StateData_IncrementActiveCount(state);
			DriveToEdge_DriveToEdgeSM_Backup_behavior(this, ENTRY);
			
			if(enumEntryType == HistoryEntry)
			{
				return true;
			}
			
			DriveToEdge_DriveToEdgeSM_Backup_behavior(this, DO);
			
			if((enumEntryType == EntryPointEntry || enumEntryType == DefaultEntry) && StateData_IsActiveState(state))
				StateMachineContext_DeferInternalEvent(&this->base, COMPLETION, 0, state);
			break;
		case EXIT:
			if(state->active_count == 0)
				return false;
			this->m_drivetoedgesm = NOSTATE;
			StateData_DecrementActiveCount(state);
			DriveToEdge_DriveToEdgeSM_Backup_behavior(this, EXIT);
			StateMachineContext_RemoveInternalEvent(&this->base, state);
			break;
	}
	
	return true;
}

bool DriveToEdge_DriveToEdgeSM_Backup_behavior(DriveToEdge* this, StateBehaviorEnum behavior) 
{
	switch (behavior) {
		case ENTRY:
		{
			String1024 buffer;
			sprintf(buffer, "%s[%s].DriveToEdgeSM_Backup ENTRY\12", this->base.m_sInstanceName, this->base.m_sType);
			trace(buffer);
		}
			break;
		case DO:
		{
			String1024 buffer;
			sprintf(buffer, "%s[%s].DriveToEdgeSM_Backup DO\12", this->base.m_sInstanceName, this->base.m_sType);
			trace(buffer);
			/*
			Backup()
			*/
		}
			break;
		case EXIT:
		{
			String1024 buffer;
			sprintf(buffer, "%s[%s].DriveToEdgeSM_Backup EXIT\12", this->base.m_sInstanceName, this->base.m_sType);
			trace(buffer);
		}
			break;
	}
	
	return true;
}

bool DriveToEdge_DriveToEdgeSM_Turn(DriveToEdge* this, StateBehaviorEnum behavior, StateData* submachineState, Signal* signal, EntryTypeEnum enumEntryType, EntryEnum entryArray[], int nArrayCount)
{
	StateData*  state = StateMachineContext_GetStateObject(&this->base, submachineState, DriveToEdge_ENUM_DRIVETOEDGESM_TURN);
	switch (behavior) {
		case ENTRY:
			if(state->active_count > 0)
				return false;
			this->m_drivetoedgesm = DriveToEdge_ENUM_DRIVETOEDGESM_TURN;
			StateData_IncrementActiveCount(state);
			DriveToEdge_DriveToEdgeSM_Turn_behavior(this, ENTRY);
			
			if(enumEntryType == HistoryEntry)
			{
				return true;
			}
			
			DriveToEdge_DriveToEdgeSM_Turn_behavior(this, DO);
			
			if((enumEntryType == EntryPointEntry || enumEntryType == DefaultEntry) && StateData_IsActiveState(state))
				StateMachineContext_DeferInternalEvent(&this->base, COMPLETION, 0, state);
			break;
		case EXIT:
			if(state->active_count == 0)
				return false;
			this->m_drivetoedgesm = NOSTATE;
			StateData_DecrementActiveCount(state);
			DriveToEdge_DriveToEdgeSM_Turn_behavior(this, EXIT);
			StateMachineContext_RemoveInternalEvent(&this->base, state);
			break;
	}
	
	return true;
}

bool DriveToEdge_DriveToEdgeSM_Turn_behavior(DriveToEdge* this, StateBehaviorEnum behavior) 
{
	switch (behavior) {
		case ENTRY:
		{
			String1024 buffer;
			sprintf(buffer, "%s[%s].DriveToEdgeSM_Turn ENTRY\12", this->base.m_sInstanceName, this->base.m_sType);
			trace(buffer);
		}
			break;
		case DO:
		{
			String1024 buffer;
			sprintf(buffer, "%s[%s].DriveToEdgeSM_Turn DO\12", this->base.m_sInstanceName, this->base.m_sType);
			trace(buffer);
			/*
			Turn()
			*/
		}
			break;
		case EXIT:
		{
			String1024 buffer;
			sprintf(buffer, "%s[%s].DriveToEdgeSM_Turn EXIT\12", this->base.m_sInstanceName, this->base.m_sType);
			trace(buffer);
		}
			break;
	}
	
	return true;
}

bool DriveToEdge_dispatch(DriveToEdge* this, Event* event, StateData* toState, bool bCheckOnly) 
{
	bool bDispatched = false;
	
	
	if(!toState || !StateData_IsActiveState(toState) && !bCheckOnly)
		return bDispatched;
	switch (toState->state_enum) {
		case DriveToEdge_VIRTUAL_SUBMACHINESTATE:
			if(event->eventEnum == COMPLETION)
			{
				if(!bCheckOnly)
				{
					StateDataNode* current;
					StateMachineContext_ReleaseSubmachineState(&this->base, toState);
					current = this->base.lstStateDataHead;
					while( current != NULL )
					{
						StateData* state = current->state;
						if (state == toState)
						{
							current = (StateDataNode*)deleteElem((void**)&this->base.lstStateDataHead, current);
							break;
						}
						else
							current = current->next;
					}
					free(toState);
					toState = NULL;
				}
				bDispatched = true;
			}
			break;
		case DriveToEdge_ENUM_DRIVETOEDGESM_FORWARD:
	
			switch (event->eventEnum) {
		
				case COMPLETION:
					if(!bCheckOnly)
						DriveToEdge_TransitionProc(this, DriveToEdge_ENUM_FORWARD__TO__BACKUP_2, 0, toState->submachine_state);
					bDispatched = true;
					break;
		
			}
	
			break;
		case DriveToEdge_ENUM_DRIVETOEDGESM_BACKUP:
	
			switch (event->eventEnum) {
		
				case COMPLETION:
					if(!bCheckOnly)
						DriveToEdge_TransitionProc(this, DriveToEdge_ENUM_BACKUP__TO__TURN_3, 0, toState->submachine_state);
					bDispatched = true;
					break;
		
			}
	
			break;
		case DriveToEdge_ENUM_DRIVETOEDGESM_TURN:
	
			switch (event->eventEnum) {
		
				case COMPLETION:
					if(!bCheckOnly)
						DriveToEdge_TransitionProc(this, DriveToEdge_ENUM_TURN__TO__FORWARD_4, 0, toState->submachine_state);
					bDispatched = true;
					break;
		
			}
	
			break;
	}
	if(!bDispatched && toState && toState->parent_state && event->eventEnum != COMPLETION)
	{
		bDispatched = DriveToEdge_dispatch(this, event, toState->parent_state, true);
		if(bDispatched && !bCheckOnly)
		{
			/*1. Exit the current state; 2. Decrement the active count of the parent state; 3. dispatch the event to parent state*/
			DriveToEdge_StateProc(this, toState->state_enum, toState->submachine_state, EXIT, 0, DefaultEntry, NULL, 0);
			StateData_DecrementActiveCount(toState->parent_state);
			DriveToEdge_dispatch(this, event, toState->parent_state, false);
			event = 0;
		}
	}
	return bDispatched;
}

void DriveToEdge_runStateMachine_by_Enum(DriveToEdge* this, StateMachineEnum statemachine)
{
	if(StateMachineContext_GetCurrentStatesCount(&this->base) > 0)
		return;
	switch (statemachine) {
		case DriveToEdge_ENUM_DRIVETOEDGESM:
			{
				EntryEnum entryArray[1] = {DriveToEdge_ENUM_DRIVETOEDGESM_INITIAL_4};
				DriveToEdge_runStateMachine(this, statemachine, NULL, 0, entryArray, 1);	/* submachineState is NULL if run standalone statemachine */
			}
			break;
	}
}

void DriveToEdge_runStateMachines(DriveToEdge* this)
{
	StateMachineContext_runStateMachine_by_Enum(&this->base, DriveToEdge_ENUM_DRIVETOEDGESM);
}
void DriveToEdge_runStateMachine(DriveToEdge* this, StateMachineEnum statemachine, StateData* submachineState, Signal* signal, EntryEnum entryArray[], int nEntryCount)
{
	if(!submachineState)
	{
		StateDataNode* newNode;
		StateInitialData initialData = {DriveToEdge_VIRTUAL_SUBMACHINESTATE, NOSTATE, 1, false}; 
		submachineState = StateData_New(&this->base, &initialData);
		StateData_IncrementActiveCount(submachineState);
		
		/* create new node; */
		newNode = (StateDataNode*)malloc(sizeof(StateDataNode));
		newNode->next = NULL;
		newNode->state = submachineState;
		this->base.lstStateDataHead = (StateDataNode*)AddTail(this->base.lstStateDataHead, newNode);
	}
	switch (statemachine) {
		case DriveToEdge_ENUM_DRIVETOEDGESM:
			{
				int i;
				StateInitialData initialDataArray[3] = 
					{
						{DriveToEdge_ENUM_DRIVETOEDGESM_FORWARD, NOSTATE, 0, false},
						{DriveToEdge_ENUM_DRIVETOEDGESM_BACKUP, NOSTATE, 0, false},
						{DriveToEdge_ENUM_DRIVETOEDGESM_TURN, NOSTATE, 0, false}
					};
		
				StateMachineContext_CreateStateObjects(&this->base, initialDataArray, 3, submachineState);
	
				for(i = 0; i < nEntryCount; i++)
				{
					switch(entryArray[i])
					{
					case DriveToEdge_ENUM_DRIVETOEDGESM_INITIAL_4:
						DriveToEdge_TransitionProc(this, DriveToEdge_ENUM_INITIAL_4__TO__FORWARD_1, signal, submachineState);
						break;
					}
				}
				if(StateData_IsActiveState(submachineState))
					StateMachineContext_DeferInternalEvent(&this->base, COMPLETION, 0, submachineState);
			}
			break;
	}
}

/* End - EA generated code for StateMachine */


/* End - EA generated code for StateMachine */

long DirectionClk()
{
	return 0;
}

long DistanceClk()
{
	return 0;
}

short SeeEdge()
{
	return 0;
}