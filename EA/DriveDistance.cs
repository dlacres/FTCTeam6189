///////////////////////////////////////////////////////////
//  DriveDistance.cs
//  Implementation of the Class DriveDistance
//  Generated by Enterprise Architect
//  Created on:      18-Apr-2014 9:08:09 PM
//  Original author: Working
///////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Text;
using System.IO;



#define STOP_DIST 400
#define MOTOR_A ltMotor
#define MOTOR_C rtMotor
namespace Classes {
	public class DriveDistance : StateMachineContext {

		/* Begin - EA generated code for StateMachine */




		public enum StateMachineEnum 
		{
			NOSTATEMACHINE,
			DriveDistance_ENUM_DRIVEDISTANCESM,
		};
	
		public enum StateEnum 
		{
			NOSTATE,
			DriveDistance_VIRTUAL_SUBMACHINESTATE,
			DriveDistance_ENUM_DRIVEDISTANCESM_FORWARDSTATE,
			DriveDistance_ENUM_DRIVEDISTANCESM_STOPSTATE,
		};
	
		public enum TransitionEnum 
		{
			NOTRANSITION,
			DriveDistance_ENUM_INITIAL_10__TO__FORWARDSTATE_5,
			DriveDistance_ENUM_FORWARDSTATE__TO__STOPSTATE_6,
		};
	
		public enum EntryEnum
		{
			NOENTRY,
			DriveDistance_ENUM_DRIVEDISTANCESM_INITIAL_10,
		};
	
	    public StateMachineImpl m_StateMachineImpl;
	
		public DriveDistance()
	    {
	        m_StateMachineImpl = null;
	    }
	
		~DriveDistance()
	    {
	    }
	
		public DriveDistance(ContextManager pManager, string sInstanceName)
	    {
			//Initialize Region Variables
			m_drivedistancesm = StateEnum.NOSTATE;
			m_sInstanceName = sInstanceName;
			m_sType = "DriveDistance";
			m_StateMachineImpl = new StateMachineImpl(this, pManager);
		
	
	    }
	
	    public string m_sInstanceName;
	    public string m_sType;
	
		public string GetInstanceName()
		{
			return m_sInstanceName;
		}
	
		public string GetTypeName()
		{
			return m_sType;
		}
	
		public bool defer(Event _event, StateData toState, bool bCheckOnly)
		{
			bool bDefer = false;
			if(_event.eventEnum == EventEnum.COMPLETION)
				return bDefer;
		
		
			if(!bDefer)
			{
				if (toState.parent_state != null)
				{
					bDefer = defer(_event, toState.parent_state, true);
					if(bDefer && !bCheckOnly)
					{
						defer(_event, toState.parent_state, false);
					}
				}
			}
			else if(!bCheckOnly)
			{
				bool bExist = false;
				foreach (Event evt in m_StateMachineImpl.deferredEvents)
				{
					if (evt == _event)
					{
						bExist = true;
						break;
					}
				}
				if(!bExist)
				{
					m_StateMachineImpl.deferredEvents.Add(_event);
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
				case TransitionEnum.DriveDistance_ENUM_INITIAL_10__TO__FORWARDSTATE_5:
					m_StateMachineImpl.currentTransition.SetTransition((int)transition, submachineState, "DriveDistance_Initial_10__TO__ForwardState_5", "{349C5E01-7C43-4303-AB4B-888A0D4917F2},");
					Initial_10__TO__ForwardState_5(signal, submachineState); 
					break;
				case TransitionEnum.DriveDistance_ENUM_FORWARDSTATE__TO__STOPSTATE_6:
					m_StateMachineImpl.currentTransition.SetTransition((int)transition, submachineState, "DriveDistance_ForwardState__TO__StopState_6", "{8083DC99-F5F9-4020-8F9A-8B14BF7FC814},");
					ForwardState__TO__StopState_6(signal, submachineState); 
					break;
			}
	
			m_StateMachineImpl.currentTransition.SetTransition((int)TransitionEnum.NOTRANSITION, null, "", "");
		}
	
		private void Initial_10__TO__ForwardState_5_effect(Signal signal)
		{
			StringBuilder ss = new StringBuilder();
			ss.AppendFormat("{0}[{1}].Initial_10__TO__ForwardState_5 Effect", m_sInstanceName, m_sType);
			ss.AppendLine();
			GlobalFuncs.trace(ss.ToString());
	
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
			ss.AppendFormat("{0}[{1}].ForwardState__TO__StopState_6 Effect", m_sInstanceName, m_sType);
			ss.AppendLine();
			GlobalFuncs.trace(ss.ToString());
	
		}

		private void ForwardState__TO__StopState_6(Signal signal, StateData submachineState) 
		{
			if (m_StateMachineImpl == null)
				return;
	
			if(!m_StateMachineImpl.GetStateObject(submachineState, (int)StateEnum.DriveDistance_ENUM_DRIVEDISTANCESM_FORWARDSTATE).IsActiveState())
			{
				return;
			}
			StateProc(StateEnum.DriveDistance_ENUM_DRIVEDISTANCESM_FORWARDSTATE, submachineState, StateBehaviorEnum.EXIT, null);
			ForwardState__TO__StopState_6_effect(signal);
			m_StateMachineImpl.currentTransition.SetActive(m_StateMachineImpl);
			StateProc(StateEnum.DriveDistance_ENUM_DRIVEDISTANCESM_STOPSTATE, submachineState, StateBehaviorEnum.ENTRY, signal, EntryTypeEnum.DefaultEntry);
		}
	
		public virtual bool StateProc(StateEnum state, StateData submachineState, StateBehaviorEnum behavior, Signal signal)
		{
			return StateProc(state, submachineState, behavior, signal, EntryTypeEnum.DefaultEntry, null, 0);
		}
	
		public virtual bool StateProc(StateEnum state, StateData submachineState, StateBehaviorEnum behavior, Signal signal, EntryTypeEnum enumEntryType)
		{
			return StateProc(state, submachineState, behavior, signal, enumEntryType, null, 0);
		}
	
		public bool StateProc(int state, StateData submachineState, StateBehaviorEnum behavior, Signal signal, EntryTypeEnum enumEntryType, int[] entryArray, int nArrayCount)
		{
			EntryEnum[] entryEnumArray = new EntryEnum[nArrayCount];
			for (int i = 0; i < nArrayCount; i++)
			{
				if (entryArray != null && i < entryArray.Length)
					entryEnumArray[i] = (EntryEnum)entryArray[i];
			}      
			return StateProc((StateEnum)state, submachineState, behavior, signal, enumEntryType, entryEnumArray, nArrayCount);
		}
	
		public bool StateProc(StateEnum state, StateData submachineState, StateBehaviorEnum behavior, Signal signal, EntryTypeEnum enumEntryType, EntryEnum[] entryArray, int nArrayCount)
		{
			switch (state) 
			{
				case StateEnum.DriveDistance_ENUM_DRIVEDISTANCESM_FORWARDSTATE:
					DriveDistanceSM_ForwardState(behavior, submachineState, signal, enumEntryType, entryArray, nArrayCount);
					break;

				case StateEnum.DriveDistance_ENUM_DRIVEDISTANCESM_STOPSTATE:
					DriveDistanceSM_StopState(behavior, submachineState, signal, enumEntryType, entryArray, nArrayCount);
					break;
			}
			return false;
		}
	
		public bool DriveDistanceSM_ForwardState(StateBehaviorEnum behavior, StateData submachineState, Signal signal, EntryTypeEnum enumEntryType, EntryEnum[] entryArray, int nArrayCount) 
		{
			if (m_StateMachineImpl == null)
				return false;
	
			StateData state = m_StateMachineImpl.GetStateObject(submachineState, (int)StateEnum.DriveDistance_ENUM_DRIVEDISTANCESM_FORWARDSTATE);
			switch (behavior) 
			{
				case StateBehaviorEnum.ENTRY:
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
						m_StateMachineImpl.deferInternalEvent(EventEnum.COMPLETION, null, state);
					break;
				case StateBehaviorEnum.EXIT:
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

		public bool DriveDistanceSM_ForwardState_behavior(StateBehaviorEnum behavior)
		{
			switch (behavior) 
			{
				case StateBehaviorEnum.ENTRY:
				{
					StringBuilder ss = new StringBuilder();
					ss.AppendFormat("{0}[{1}].DriveDistanceSM_ForwardState ENTRY", m_sInstanceName, m_sType);
					ss.AppendLine();
					GlobalFuncs.trace(ss.ToString());
				}
				break;
				case StateBehaviorEnum.DO:
				{
					StringBuilder ss = new StringBuilder();
					ss.AppendFormat("{0}[{1}].DriveDistanceSM_ForwardState DO", m_sInstanceName, m_sType);
					ss.AppendLine();
					GlobalFuncs.trace(ss.ToString());
					motor[MOTOR_A] = FWD_SPEED;
					motor[MOTOR_C] = FWD_SPEED;
				}
				break;
				case StateBehaviorEnum.EXIT:
				{
					StringBuilder ss = new StringBuilder();
					ss.AppendFormat("{0}[{1}].DriveDistanceSM_ForwardState EXIT", m_sInstanceName, m_sType);
					ss.AppendLine();
					GlobalFuncs.trace(ss.ToString());
				}
				break;
			}
	
			return true;
		}
		public bool DriveDistanceSM_StopState(StateBehaviorEnum behavior, StateData submachineState, Signal signal, EntryTypeEnum enumEntryType, EntryEnum[] entryArray, int nArrayCount) 
		{
			if (m_StateMachineImpl == null)
				return false;
	
			StateData state = m_StateMachineImpl.GetStateObject(submachineState, (int)StateEnum.DriveDistance_ENUM_DRIVEDISTANCESM_STOPSTATE);
			switch (behavior) 
			{
				case StateBehaviorEnum.ENTRY:
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
						m_StateMachineImpl.deferInternalEvent(EventEnum.COMPLETION, null, state);
					break;
				case StateBehaviorEnum.EXIT:
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

		public bool DriveDistanceSM_StopState_behavior(StateBehaviorEnum behavior)
		{
			switch (behavior) 
			{
				case StateBehaviorEnum.ENTRY:
				{
					StringBuilder ss = new StringBuilder();
					ss.AppendFormat("{0}[{1}].DriveDistanceSM_StopState ENTRY", m_sInstanceName, m_sType);
					ss.AppendLine();
					GlobalFuncs.trace(ss.ToString());
				}
				break;
				case StateBehaviorEnum.DO:
				{
					StringBuilder ss = new StringBuilder();
					ss.AppendFormat("{0}[{1}].DriveDistanceSM_StopState DO", m_sInstanceName, m_sType);
					ss.AppendLine();
					GlobalFuncs.trace(ss.ToString());
					motor[MOTOR_A] = 0;
					motor[MOTOR_C] = 0;
				}
				break;
				case StateBehaviorEnum.EXIT:
				{
					StringBuilder ss = new StringBuilder();
					ss.AppendFormat("{0}[{1}].DriveDistanceSM_StopState EXIT", m_sInstanceName, m_sType);
					ss.AppendLine();
					GlobalFuncs.trace(ss.ToString());
				}
				break;
			}
	
			return true;
		}
		public bool dispatch(Event _event, StateData toState, bool bCheckOnly)
		{
			if (m_StateMachineImpl == null)
				return false;
		
	
	    
			bool bDispatched = false;
			if(toState == null || !toState.IsActiveState() && !bCheckOnly)
				return bDispatched;
		
			switch ((StateEnum)toState.state_enum) 
			{
				case StateEnum.DriveDistance_VIRTUAL_SUBMACHINESTATE:
					if(_event.eventEnum == EventEnum.COMPLETION)
					{
						if(!bCheckOnly)
						{
							m_StateMachineImpl.ReleaseSubmachineState(toState);
							List<StateData> lstStateData = m_StateMachineImpl.GetStateData();
							foreach (StateData state in lstStateData)
							{
								if (state == toState)
								{
									lstStateData.Remove(state);
									break;
								}					
							}
							//delete toState;
							toState = null;
						}			
						bDispatched = true;
					}
					break;
				case StateEnum.DriveDistance_ENUM_DRIVEDISTANCESM_FORWARDSTATE:
					switch (_event.eventEnum) 
					{
						case EventEnum.COMPLETION:
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
		
			if (!bDispatched && toState != null && toState.parent_state != null && _event.eventEnum != EventEnum.COMPLETION)
			{
				bDispatched = dispatch(_event, toState.parent_state, true);
				if (bDispatched && !bCheckOnly)
				{
					/*1. Exit the current state; 2. Decrement the active count of the parent state; 3. dispatch the event to parent state*/
					StateProc((StateEnum)toState.state_enum, toState.submachine_state, StateBehaviorEnum.EXIT, null);
					toState.parent_state.DecrementActiveCount();
					dispatch(_event, toState.parent_state, false);
					_event = null;
				}
			}
		
			return bDispatched;
		}
	
		StateEnum m_drivedistancesm;
	
	    public void runStateMachine(string statemachine)
	    {
			if (statemachine.CompareTo("DriveDistance_DriveDistanceSM") == 0)
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
				StateInitialData initialData = new StateInitialData((int)StateEnum.DriveDistance_VIRTUAL_SUBMACHINESTATE, (int)StateEnum.NOSTATE, 1, false, "DriveDistance_VIRTUAL_SUBMACHINESTATE", ""); 
				submachineState = new StateData(m_StateMachineImpl, initialData);
				submachineState.IncrementActiveCount();
				m_StateMachineImpl.GetStateData().Add(submachineState);
			}
			switch (statemachine) 
			{
				case StateMachineEnum.DriveDistance_ENUM_DRIVEDISTANCESM:
					{
						const int nArrayCount = 2;
						StateInitialData[] initialDataArray = new StateInitialData[nArrayCount]
							{
								new StateInitialData((int)StateEnum.DriveDistance_ENUM_DRIVEDISTANCESM_FORWARDSTATE, (int)StateEnum.NOSTATE, 0, false, "DriveDistance_DriveDistanceSM_ForwardState", "{7C4E3CFB-F8EA-4d72-83D7-1257A76F1FFF}"),
								new StateInitialData((int)StateEnum.DriveDistance_ENUM_DRIVEDISTANCESM_STOPSTATE, (int)StateEnum.NOSTATE, 0, false, "DriveDistance_DriveDistanceSM_StopState", "{EB0BB228-E76D-4701-B2F9-04C5EC06EC50}")
							};
		
						m_StateMachineImpl.CreateStateObjects(initialDataArray, nArrayCount, submachineState);
					}
					for(int i = 0; i < nEntryCount; i++)
					{
						switch(entryArray[i])
						{
						case EntryEnum.DriveDistance_ENUM_DRIVEDISTANCESM_INITIAL_10:
							TransitionProc(TransitionEnum.DriveDistance_ENUM_INITIAL_10__TO__FORWARDSTATE_5, signal, submachineState);
							break;
						}
					}
					if(submachineState.IsActiveState())
						m_StateMachineImpl.deferInternalEvent(EventEnum.COMPLETION, null, submachineState);
					break;
			}
	
		}
	
		public void runStateMachine(StateMachineEnum statemachine)
		{
			if (m_StateMachineImpl == null)
				return;
		
			List<StateData> activeStateArray = new List<StateData>();
			if(m_StateMachineImpl.GetCurrentStates(activeStateArray) > 0)
				return;
			switch (statemachine) 
			{
				case StateMachineEnum.DriveDistance_ENUM_DRIVEDISTANCESM:
					{
						const int nArrayCount = 1;
						EntryEnum[] entryArray = new EntryEnum[] {EntryEnum.DriveDistance_ENUM_DRIVEDISTANCESM_INITIAL_10};
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

}//end namespace Classes