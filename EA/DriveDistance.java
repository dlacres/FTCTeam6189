//package Classes;	//Comment out for EA Statemachine simulation purpose	

import java.util.*;

#define STOP_DIST 400
#define MOTOR_A ltMotor
#define MOTOR_C rtMotor

/**
 * @author Working
 * @version 1.0
 * @created 18-Apr-2014 9:06:26 PM
 */
public class DriveDistance implements StateMachineContext {

	/* Begin - EA generated code for StateMachine */


	enum StateMachineEnum 
	{
		NOSTATEMACHINE,
		DriveDistance_ENUM_DRIVEDISTANCESM
	};

	enum StateEnum 
	{
		NOSTATE,
		DriveDistance_VIRTUAL_SUBMACHINESTATE,
		DriveDistance_ENUM_DRIVEDISTANCESM_FORWARDSTATE,
		DriveDistance_ENUM_DRIVEDISTANCESM_STOPSTATE
	};

	enum TransitionEnum 
	{
		NOTRANSITION,
		DriveDistance_ENUM_INITIAL_10__TO__FORWARDSTATE_5,
		DriveDistance_ENUM_FORWARDSTATE__TO__STOPSTATE_6
	};

	enum EntryEnum
	{
		NOENTRY,
		DriveDistance_ENUM_DRIVEDISTANCESM_INITIAL_10
	};

	public StateMachineImpl m_StateMachineImpl;
	
	public DriveDistance()
	{
		m_StateMachineImpl = null;
	}
	
	protected void finalize( ) throws Throwable
	{
	}
	
	public DriveDistance(ContextManager pManager, String sInstanceName)
	{
		//Initialize Region Variables
		m_drivedistancesm = StateEnum.NOSTATE;	
		m_sInstanceName = sInstanceName;
		m_sType = "DriveDistance";
		m_StateMachineImpl = new StateMachineImpl(this, pManager);
	}
	
    public String m_sInstanceName;
    public String m_sType;
	
	public String GetInstanceName()
	{
		return m_sInstanceName;
	}
	
	public String GetTypeName()
	{
		return m_sType;
	}
	
	public boolean defer(Event event, StateData toState, boolean bCheckOnly)
	{
		if (m_StateMachineImpl == null)
			return false;
		
		boolean bDefer = false;
		if(event.eventEnum == EventProxy.EventEnum.COMPLETION)
			return bDefer;
		
		
		if(!bDefer)
		{
			if(toState.parent_state != null)
			{
				bDefer = defer(event, toState.parent_state, true);
				if(bDefer && !bCheckOnly)
				{
					defer(event, toState.parent_state, false);
				}
			}
		}
		else if(!bCheckOnly)
		{
			boolean bExist = false;
			for (int index = 0; index < m_StateMachineImpl.deferredEvents.size(); index++)
			{
				Event evt = m_StateMachineImpl.deferredEvents.get(index);
				if (evt == event)
				{
					bExist = true;
					break;
				}
			}
			if(!bExist)
			{
				m_StateMachineImpl.deferredEvents.add(event);
			}
		}
		return bDefer;
	}

	public void TransitionProc(TransitionEnum transition, Signal signal, StateData submachineState)
	{
		if (m_StateMachineImpl == null)
			return;
		
	
		switch (transition) 
		{
			case DriveDistance_ENUM_INITIAL_10__TO__FORWARDSTATE_5:
				m_StateMachineImpl.currentTransition.SetTransition(transition.ordinal(), submachineState, "DriveDistance_Initial_10__TO__ForwardState_5", "{349C5E01-7C43-4303-AB4B-888A0D4917F2},");
				Initial_10__TO__ForwardState_5(signal, submachineState); 
				break;
			case DriveDistance_ENUM_FORWARDSTATE__TO__STOPSTATE_6:
				m_StateMachineImpl.currentTransition.SetTransition(transition.ordinal(), submachineState, "DriveDistance_ForwardState__TO__StopState_6", "{8083DC99-F5F9-4020-8F9A-8B14BF7FC814},");
				ForwardState__TO__StopState_6(signal, submachineState); 
				break;
		}
	
		m_StateMachineImpl.currentTransition.SetTransition(TransitionEnum.NOTRANSITION.ordinal(), null, "", "");	
	}
	
	private void Initial_10__TO__ForwardState_5_effect(Signal signal)
	{
		StringBuilder ss = new StringBuilder();
		ss.append(m_sInstanceName + "[" + m_sType + "].Initial_10__TO__ForwardState_5 Effect\n");
		GlobalFuncs.trace(ss.toString());
	
	}

	private void Initial_10__TO__ForwardState_5(Signal signal, StateData submachineState) 
	{
		if (m_StateMachineImpl == null)
			return;
	
		if(submachineState != null)
			submachineState.IncrementActiveCount();
		Initial_10__TO__ForwardState_5_effect(signal);
		m_StateMachineImpl.currentTransition.SetActive(m_StateMachineImpl);
		StateProc(StateEnum.DriveDistance_ENUM_DRIVEDISTANCESM_FORWARDSTATE, submachineState, StateBehaviorEnum.ENTRY, signal, EntryTypeEnum.DefaultEntry);
	}
	private void ForwardState__TO__StopState_6_effect(Signal signal)
	{
		StringBuilder ss = new StringBuilder();
		ss.append(m_sInstanceName + "[" + m_sType + "].ForwardState__TO__StopState_6 Effect\n");
		GlobalFuncs.trace(ss.toString());
	
	}

	private void ForwardState__TO__StopState_6(Signal signal, StateData submachineState) 
	{
		if (m_StateMachineImpl == null)
			return;
	
		if(!m_StateMachineImpl.GetStateObject(submachineState, StateEnum.DriveDistance_ENUM_DRIVEDISTANCESM_FORWARDSTATE.ordinal()).IsActiveState())
		{
			return;
		}
		StateProc(StateEnum.DriveDistance_ENUM_DRIVEDISTANCESM_FORWARDSTATE, submachineState, StateBehaviorEnum.EXIT, null);
		ForwardState__TO__StopState_6_effect(signal);
		m_StateMachineImpl.currentTransition.SetActive(m_StateMachineImpl);
		StateProc(StateEnum.DriveDistance_ENUM_DRIVEDISTANCESM_STOPSTATE, submachineState, StateBehaviorEnum.ENTRY, signal, EntryTypeEnum.DefaultEntry);
	}
	public boolean StateProc(StateEnum state, StateData submachineState, StateBehaviorEnum behavior, Signal signal)
	{
		return StateProc(state, submachineState, behavior, signal, EntryTypeEnum.DefaultEntry, null, 0);
	}
	
	public boolean StateProc(StateEnum state, StateData submachineState, StateBehaviorEnum behavior, Signal signal, EntryTypeEnum enumEntryType)
	{
		return StateProc(state, submachineState, behavior, signal, enumEntryType, null, 0);
	}
	
	public boolean StateProc(int state, StateData submachineState, StateBehaviorEnum behavior, Signal signal, EntryTypeEnum enumEntryType, int[] entryArray, int nArrayCount)
    {
		ArrayList<EntryEnum> entryEnumList = new ArrayList<>();
		if (entryArray != null)
		{
			for(int nEntryIndex : entryArray)
			{
				entryEnumList.add(EntryEnum.values()[nEntryIndex]);
			}
		}
        return StateProc(StateEnum.values()[state], submachineState, behavior, signal, enumEntryType, entryEnumList.toArray(new EntryEnum[entryEnumList.size()]), nArrayCount);
    }
	
	public boolean StateProc(StateEnum state, StateData submachineState, StateBehaviorEnum behavior, Signal signal, EntryTypeEnum enumEntryType, EntryEnum[] entryArray, int nArrayCount)
	{
		switch (state) 
		{
			case DriveDistance_ENUM_DRIVEDISTANCESM_FORWARDSTATE:
				DriveDistanceSM_ForwardState(behavior, submachineState, signal, enumEntryType, entryArray, nArrayCount);
				break;

			case DriveDistance_ENUM_DRIVEDISTANCESM_STOPSTATE:
				DriveDistanceSM_StopState(behavior, submachineState, signal, enumEntryType, entryArray, nArrayCount);
				break;
		}
		return false;
	}
	
	public boolean DriveDistanceSM_ForwardState(StateBehaviorEnum behavior, StateData submachineState, Signal signal, EntryTypeEnum enumEntryType, EntryEnum[] entryArray, int nArrayCount) 
	{
		if (m_StateMachineImpl == null)
			return false;
	
		StateData state = m_StateMachineImpl.GetStateObject(submachineState, StateEnum.DriveDistance_ENUM_DRIVEDISTANCESM_FORWARDSTATE.ordinal());
		switch (behavior) 
		{
			case ENTRY:
				if(state.active_count > 0)
					return false;
				m_drivedistancesm = StateEnum.DriveDistance_ENUM_DRIVEDISTANCESM_FORWARDSTATE;
				state.IncrementActiveCount();
				DriveDistanceSM_ForwardState_behavior(StateBehaviorEnum.ENTRY);
			
				if(enumEntryType == EntryTypeEnum.HistoryEntry)
				{
					return true;
				}
						
				DriveDistanceSM_ForwardState_behavior(StateBehaviorEnum.DO);
			
				if((enumEntryType == EntryTypeEnum.EntryPointEntry || enumEntryType == EntryTypeEnum.DefaultEntry) && state.IsActiveState())
					m_StateMachineImpl.deferInternalEvent(EventProxy.EventEnum.COMPLETION, null, state);
				break;
			case EXIT:
				if(state.active_count == 0)
					return false;
				m_drivedistancesm = StateEnum.NOSTATE;
				state.DecrementActiveCount();
				DriveDistanceSM_ForwardState_behavior(StateBehaviorEnum.EXIT);
				m_StateMachineImpl.removeInternalEvent(state);
				break;
		}
	
		return true;
	}

	public boolean DriveDistanceSM_ForwardState_behavior(StateBehaviorEnum behavior)
	{
		switch (behavior) 
		{
			case ENTRY:
			{
				StringBuilder ss = new StringBuilder();
				ss.append(m_sInstanceName + "[" + m_sType + "].DriveDistanceSM_ForwardState ENTRY\n");
				GlobalFuncs.trace(ss.toString());
			}
			break;
			case DO:
			{
				StringBuilder ss = new StringBuilder();
				ss.append(m_sInstanceName + "[" + m_sType + "].DriveDistanceSM_ForwardState DO\n");
				GlobalFuncs.trace(ss.toString());
				motor[MOTOR_A] = FWD_SPEED;
				motor[MOTOR_C] = FWD_SPEED;
			}
			break;
			case EXIT:
			{
				StringBuilder ss = new StringBuilder();
				ss.append(m_sInstanceName + "[" + m_sType + "].DriveDistanceSM_ForwardState EXIT\n");
				GlobalFuncs.trace(ss.toString());
			}
			break;
		}
	
		return true;
	}
	public boolean DriveDistanceSM_StopState(StateBehaviorEnum behavior, StateData submachineState, Signal signal, EntryTypeEnum enumEntryType, EntryEnum[] entryArray, int nArrayCount) 
	{
		if (m_StateMachineImpl == null)
			return false;
	
		StateData state = m_StateMachineImpl.GetStateObject(submachineState, StateEnum.DriveDistance_ENUM_DRIVEDISTANCESM_STOPSTATE.ordinal());
		switch (behavior) 
		{
			case ENTRY:
				if(state.active_count > 0)
					return false;
				m_drivedistancesm = StateEnum.DriveDistance_ENUM_DRIVEDISTANCESM_STOPSTATE;
				state.IncrementActiveCount();
				DriveDistanceSM_StopState_behavior(StateBehaviorEnum.ENTRY);
			
				if(enumEntryType == EntryTypeEnum.HistoryEntry)
				{
					return true;
				}
						
				DriveDistanceSM_StopState_behavior(StateBehaviorEnum.DO);
			
				if((enumEntryType == EntryTypeEnum.EntryPointEntry || enumEntryType == EntryTypeEnum.DefaultEntry) && state.IsActiveState())
					m_StateMachineImpl.deferInternalEvent(EventProxy.EventEnum.COMPLETION, null, state);
				break;
			case EXIT:
				if(state.active_count == 0)
					return false;
				m_drivedistancesm = StateEnum.NOSTATE;
				state.DecrementActiveCount();
				DriveDistanceSM_StopState_behavior(StateBehaviorEnum.EXIT);
				m_StateMachineImpl.removeInternalEvent(state);
				break;
		}
	
		return true;
	}

	public boolean DriveDistanceSM_StopState_behavior(StateBehaviorEnum behavior)
	{
		switch (behavior) 
		{
			case ENTRY:
			{
				StringBuilder ss = new StringBuilder();
				ss.append(m_sInstanceName + "[" + m_sType + "].DriveDistanceSM_StopState ENTRY\n");
				GlobalFuncs.trace(ss.toString());
			}
			break;
			case DO:
			{
				StringBuilder ss = new StringBuilder();
				ss.append(m_sInstanceName + "[" + m_sType + "].DriveDistanceSM_StopState DO\n");
				GlobalFuncs.trace(ss.toString());
				motor[MOTOR_A] = 0;
				motor[MOTOR_C] = 0;
			}
			break;
			case EXIT:
			{
				StringBuilder ss = new StringBuilder();
				ss.append(m_sInstanceName + "[" + m_sType + "].DriveDistanceSM_StopState EXIT\n");
				GlobalFuncs.trace(ss.toString());
			}
			break;
		}
	
		return true;
	}
	public boolean dispatch(Event event, StateData toState, boolean bCheckOnly)
	{
		if (m_StateMachineImpl == null)
			return false;
		
	
		
		boolean bDispatched = false;
		if(toState == null || !toState.IsActiveState() && !bCheckOnly)
			return bDispatched;
		
		switch (StateEnum.values()[toState.state_enum]) 
		{
			case DriveDistance_VIRTUAL_SUBMACHINESTATE:
				if(event.eventEnum == EventProxy.EventEnum.COMPLETION)
				{
					if(!bCheckOnly)
					{
						m_StateMachineImpl.ReleaseSubmachineState(toState);
						for (int index = m_StateMachineImpl.lstStateData.size() - 1; index >= 0; index--)
						{
							StateData state = m_StateMachineImpl.lstStateData.get(index);
							if (state == toState)
							{
								m_StateMachineImpl.lstStateData.remove(state);
								break;
							}						
						}
						//delete toState;
						toState = null;
					}				
					bDispatched = true;
				}
				break;
			case DriveDistance_ENUM_DRIVEDISTANCESM_FORWARDSTATE:
				switch (event.eventEnum) 
				{
					case COMPLETION:
						if(abs(nMotorEncoder[MOTOR_A]) > STOP_DIST) {
							if(!bCheckOnly)
								TransitionProc(TransitionEnum.DriveDistance_ENUM_FORWARDSTATE__TO__STOPSTATE_6, null, toState.submachine_state);
							bDispatched = true;
							break;
						}
						break;
				}
				break;
		}
		
		if (!bDispatched && toState != null && toState.parent_state != null && event.eventEnum != EventProxy.EventEnum.COMPLETION)
		{
			bDispatched = dispatch(event, toState.parent_state, true);
			if (bDispatched && !bCheckOnly)
			{
				/*1. Exit the current state; 2. Decrement the active count of the parent state; 3. dispatch the event to parent state*/
				StateProc(StateEnum.values()[toState.state_enum], toState.submachine_state, StateBehaviorEnum.EXIT, null);
				toState.parent_state.DecrementActiveCount();
				dispatch(event, toState.parent_state, false);
				event = null;
			}
		}
		
		return bDispatched;
	}
	
	StateEnum m_drivedistancesm;
	
	@Override
    public void runStateMachine(String statemachine)
    {
		if(statemachine.equals("DriveDistance_DriveDistanceSM"))
		{
			runStateMachine(StateMachineEnum.DriveDistance_ENUM_DRIVEDISTANCESM);
			return;
		}
    }
	
	private void runStateMachine(StateMachineEnum statemachine, StateData submachineState, Signal signal)
	{
		runStateMachine(statemachine, submachineState, signal, null, 0);
	}
	
	private void runStateMachine(StateMachineEnum statemachine, StateData submachineState, Signal signal, EntryEnum[] entryArray, int nEntryCount)
	{
		if (m_StateMachineImpl == null)
			return;
		
		if(submachineState == null)
		{
			StateInitialData initialData = new StateInitialData(StateEnum.DriveDistance_VIRTUAL_SUBMACHINESTATE.ordinal(), StateEnum.NOSTATE.ordinal(), 1, false, "DriveDistance_VIRTUAL_SUBMACHINESTATE", ""); 
			submachineState = new StateData(m_StateMachineImpl, initialData);
			submachineState.IncrementActiveCount();
			m_StateMachineImpl.lstStateData.add(submachineState);
		}
		switch (statemachine) 
		{
			case DriveDistance_ENUM_DRIVEDISTANCESM:
				{
					final int nArrayCount = 2;
					StateInitialData[] initialDataArray = 
						{
							new StateInitialData(StateEnum.DriveDistance_ENUM_DRIVEDISTANCESM_FORWARDSTATE.ordinal(), StateEnum.NOSTATE.ordinal(), 0, false, "DriveDistance_DriveDistanceSM_ForwardState", "{7C4E3CFB-F8EA-4d72-83D7-1257A76F1FFF}"),
							new StateInitialData(StateEnum.DriveDistance_ENUM_DRIVEDISTANCESM_STOPSTATE.ordinal(), StateEnum.NOSTATE.ordinal(), 0, false, "DriveDistance_DriveDistanceSM_StopState", "{EB0BB228-E76D-4701-B2F9-04C5EC06EC50}")
						};
		
					m_StateMachineImpl.CreateStateObjects(initialDataArray, nArrayCount, submachineState);
				}
				for(int i = 0; i < nEntryCount; i++)
				{
					switch(entryArray[i])
					{
					case DriveDistance_ENUM_DRIVEDISTANCESM_INITIAL_10:
						TransitionProc(TransitionEnum.DriveDistance_ENUM_INITIAL_10__TO__FORWARDSTATE_5, signal, submachineState);
						break;
					}
				}
				if(submachineState.IsActiveState())
					m_StateMachineImpl.deferInternalEvent(EventProxy.EventEnum.COMPLETION, null, submachineState);
				break;
		}
	
	}
	
	public void runStateMachine(StateMachineEnum statemachine)
	{
		if (m_StateMachineImpl == null)
			return;
		
		List<StateData> activeStateArray = new ArrayList<StateData>();
		if(m_StateMachineImpl.GetCurrentStates(activeStateArray) > 0)
			return;
		switch (statemachine) 
		{
			case DriveDistance_ENUM_DRIVEDISTANCESM:
				{
					final int nArrayCount = 1;
					EntryEnum[] entryArray = {EntryEnum.DriveDistance_ENUM_DRIVEDISTANCESM_INITIAL_10};
					runStateMachine(statemachine, null, null, entryArray, nArrayCount);	//submachineState is NULL if run standalone statemachine 
				}
				break;
		}
	}
	
	public void runStateMachines()
	{
		runStateMachine(StateMachineEnum.DriveDistance_ENUM_DRIVEDISTANCESM);	
	}


	/* End - EA generated code for StateMachine */
}//end DriveDistance