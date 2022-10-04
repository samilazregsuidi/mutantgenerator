typedef features {
	bool Start = 1;
	bool Stop = 1;
 	bool MethaneAlarm = 1;
 	bool MethaneQuery = 1;
	bool Low = 0;
	bool Normal = 0;
	bool High = 1
}

features f;

mtype = {stop, start, alarm, low, medium, high, ready, running, stopped, methanestop, lowstop, commandMsg, alarmMsg, levelMsg}

chan cCmd = [0] of {mtype}; 	/* stop, start			*/
chan cAlarm = [0] of {mtype}; 	/* alarm                */
chan cMethane = [0] of {mtype}; /* methanestop, ready   */
chan cLevel = [0] of {mtype}; 	/* low, medium, high    */

mtype pstate = stopped; 		/* ready, running, stopped, methanestop, lowstop */
mtype readMsg = commandMsg; 		/* commandMsg, alarmMsg, levelMsg */

bool pumpOn = false;
bool methane = false;
mtype waterLevel = medium;

mtype uwants = stop; 			/* what the user wants */

active proctype controller() {
	mtype pcommand = start;
	mtype level = medium;
	
	do	::	atomic {
				cCmd?pcommand;
				readMsg = commandMsg; 
			};
			if	::	pcommand == stop;
					if	::	f.Stop;
							if	::	atomic {
										pstate == running;
										pumpOn = false;
									}
								::	else -> skip;
								fi;
							pstate = stopped;
						::	else -> skip;
						fi;
				::	pcommand == start;
					if	::	f.Start;
							if	::	atomic {
										pstate != running;
										pstate = ready;
									};
								::	else -> skip;
								fi;
						::	else -> skip;
						fi;
				::	else -> assert(false);
				fi;
			cCmd!pstate;
			
		::	atomic { 
				cAlarm?_;
				readMsg = alarmMsg;
			};
			if	::	f.MethaneAlarm;
					if	::	atomic {
								pstate == running;
								pumpOn = false;
							};
						::	else -> skip;
						fi;
					pstate = methanestop;	
				::	else -> skip;
				fi;
			
		::	atomic { 
				cLevel?level;
				readMsg = levelMsg;
			};
			if	::	level == high;
					if	::	f.High;
							/* The same block with and without race condition.
							   First, without race condition: */
							if	::	pstate == ready  ||  pstate == lowstop;
									if	::	f.MethaneQuery;
											skip;
											atomic {
												cMethane!pstate;
												cMethane?pstate;
												if	::	pstate == ready;
														pstate = running;
														pumpOn = true;
													::	else -> skip;
												fi;
											};
										::	else;
											skip;
											atomic {
												pstate = running;
												pumpOn = true;
											};
										fi;
								::	else -> skip;
								fi;
							/* Here, with race condition: (only for testing)
							if	::	pstate == ready  ||  pstate == lowstop;
									if	::	f.MethaneQuery;
											cMethane!pstate;
											cMethane?pstate;
										::	else;
											pstate = ready;
										fi;
									if	::	atomic {
												pstate == ready;
												pstate = running;
												pumpOn = true;
											};
										::	else -> skip;
									fi;
								::	else -> skip;
								fi;
								*/
						::	else -> skip;
						fi;
				::	level == low;
					if	::	f.Low;
							if	::	atomic {
										pstate == running;
										pumpOn = false;
										pstate = lowstop;
									};
								::	else -> skip;
								fi;
						::	else -> skip;
						fi;
				::	level == medium;
					skip;
				fi;
		od;
}

active proctype user() {
	do	::	if	::	uwants = start;
				::	uwants = stop;
				fi;
			cCmd!uwants;
			cCmd?_;			/* Sends back the state; ignore it */
		od;
}

active proctype methanealarm() {
	do	:: 	methane = true;
			cAlarm!alarm;
		::	methane = false;
		od;
}

active proctype methanesensor() {
	do	:: 	atomic {
				cMethane?_;
				if	::	methane;
						cMethane!methanestop;
					::	!methane;
						cMethane!ready;
					fi;
			};
		od;
}

active proctype watersensor() {
	do	:: 	atomic {
				if	::	waterLevel == low ->
						if	:: waterLevel = low;
							:: waterLevel = medium;
							fi;
					::	waterLevel == medium ->
						if	:: waterLevel = low;
							:: waterLevel = medium;
							:: waterLevel = high;
							fi;
					::	waterLevel == high ->
						if	:: waterLevel = medium;
							:: waterLevel = high;
							fi;
					fi;
				cLevel!waterLevel;
			};
		od;
};

/*
 * Alternative watersensor: takes pump into account (reduces state space).
 *
active proctype watersensor() {
	do	:: 	atomic {
				if	::	waterLevel == low  && !pumpOn ->
						if	::	waterLevel = low;
							::	waterLevel = medium;
							fi;
					::	waterLevel == medium && pumpOn ->
						if	::	waterLevel = low;
							  	waterLevel = medium;
							fi;
					::	waterLevel == medium && !pumpOn ->
						if	::	waterLevel = medium;
							  	waterLevel = high;
							fi;
					::	waterLevel == high && pumpOn ->
						if	::	waterLevel = medium;
							::	waterLevel = high;
							fi;
					::	else ->
						skip;
					fi;
				cLevel!waterLevel;
			};
		od;
};
*/


/*
 * This model is based on the code from the article 
 *
 *   Kramer, J.; Magee, J.; Sloman, M. & Lister, A. CONIC: an integrated 
 *   approach to distributed computer control systems Computers and Digital 
 *   Techniques, IEE Proceedings E, 1983, 130, 1-10
 *
 * A similar model, formulated directly as an FTS was used in the ICSE 2010
 * paper about FTS (Classen et al., "Model Checking Lots of Systems").  See
 * also "Modelling with FTS: a Collection of Illustrative Examples".
 *
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Properties
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Basic model correctness
 * 
 * Test whether the pstate does actually change.  The "violated by" products
 * are those in which the pstate does indeed change infinitely often.
 *  !([]<> (stateReady && highWater && userStart))-> violated by: Start
 *  !([]<> stateReady)               -> violated by: Start
 *  !([]<> stateRunning)             -> violated by: Start & High
 *  !([]<> stateStopped)             -> violated by: all
 *  !([]<> stateMethanestop)         -> violated by: (!Start & MethaneAlarm) | (Start & !MethaneQuery & MethaneAlarm) | (Start & MethaneQuery & !MethaneAlarm & High) | (Start & MethaneQuery & MethaneAlarm)
 *  !([]<> stateLowstop)             -> violated by: Start & Low & High
 * 
 * The controller can fairly receive each of the three message types.  This
 * is an important assumption for many properties.
 *  !([]<> readCommand)               -> violated by: all
 *  !([]<> readAlarm)                 -> violated by: all
 *  !([]<> readLevel)                 -> violated by: all
 *  !(([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> violated by: all
 * 
 * The pump can be switched on and off infinitely often
 *  !([]<>  pumpOn)                   -> violated by: Start & High
 *  !([]<> !pumpOn)                   -> violated by: all
 *  !(([]<> pumpOn) && ([]<> !pumpOn))-> violated by: (Start & !Stop & !MethaneAlarm & Low & High) | (Start & !Stop & MethaneAlarm & High) | (Start & Stop & High)
 * 
 * The same for the methane.
 *  !([]<>  methane)                  -> violated by: all
 *  !([]<> !methane)                  -> violated by: all
 *  !(([]<> methane) && ([]<> !methane))-> violated by: all
 *
 * The ptstate and actual pump state are in sync: if the pump is on, the state
 * is set to "running".
 *  [] (!pumpOn || stateRunning)
 *  -> satisfied by all.
 *
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Variations of "Pump is off when there is methane":
 *
 * When there is methane, the pump will eventually stop because of it.
 *  [] (methane ->  (<> stateMethanestop))
 *  -> violated by all; there are other reasons for which the pump can stop.
 *
 * When there is methane, the pump will never stop because of it.
 *  [] (methane -> !(<> stateMethanestop)) 
 *  -> violated by same as !([]<> stateMethanestop): shows that MethaneQuery 
 *     and MethaneAlarm are necessary for a methaneStop to occur.
 *
 * The pump is never on when there is methane.
 *  [] (pumpOn || !methane)
 *  -> violated by: all; it takes time for the methane alarm to reach the
 *     controller.
 *
 * When the pump is running, and there is methane, then it is eventually 
 * switched off.
 *  [] ((pumpOn && methane) -> <> !pumpOn)
 *  -> violated by: Start & High; these two features are required for the pump
 *     to be switched on in the first place.  Once it is one, the system can 
 *     simply ignore any methane alarms it receives.
 * The same with the proper assumption:
 *  (([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> [] ((pumpOn && methane) -> <> !pumpOn)
 *  -> violated by: Start & !MethaneAlarm & High
 * 
 * We never arrive at a situation in which the pump runs indefinitely even
 * though there is methane. 
 *  !<>[] (pumpOn && methane)
 *  -> violated by: Start & High; same problem as before: the system can 
 *     all the messages it receives.
 * With the proper assumption:
 *  (([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> !<>[] (pumpOn && methane)
 *  -> violated by: Start & High & !MethaneAlarm; basically, the MethaneAlarm
 *     is required for this property to hold (as expected).
 * 
 * The MethaneQuery alone is not sufficient to guarantee these properties.
 * All it does is check whether there is methane before the pump is switched
 * on.  If methane appears after it was switched on, only the MethaneAlarm 
 * will switch it off.
 * 
 * When the pump is off an there is methane, it remains switched off until
 * the methane is gone.
 *  [] ((!pumpOn && methane && <>!methane) -> ((!pumpOn) U !methane))
 *  -> violated by: Start & High & !MethaneQuery; as expected, the 
 *     MethaneQuery feature prevents this from happening.  But only if the 
 *     methane cannot switch to true immediately after a query was made. 
 *     If this were the case, there would be a race condition, and the pump 
 *     might be switched on even though there *is* methane.  Below, there 
 *     is a (commented) piece of code that exhibits this.
 * 
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Variations of "Pump is on when there is water and no methane":
 *
 * When the water is high and there is no methane, then the pump is on.
 *  [] ((highWater && !methane) -> <>pumpOn)
 *  -> violated by all; due to the fact that the controller can 
 *     ignore the high water level notifications, or methane might appear
 *     just after the highWater message was received.
 * Hypothesis:
 *  !(<> (highWater && !methane))
 *  -> violated by all.
 * Adding a fairness assumption:
 *  (([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> ([] ((highWater && !methane) -> <>pumpOn))
 *  -> violated by all; this does not solve the problems mentioned earlier.
 *
 * What would it take for the pump not to be switched on at all eventually:
 *  [] ((highWater && !methane) -> !<>pumpOn)
 *  -> violated by: Start & High; shows that Start and High are necessary 
 *     for the pump to be switched on eventually.  However, this does not
 *     mean that their presence will indeed cause the pump to be switched
 *     on at all when the water is high.
 * 
 * The pump is never indefinitely off when the water is high.
 *  !<>[] (!pumpOn && highWater)
 *  -> violated by all; if there is methane the pump remains off.
 * The same with the assumption
 *  (([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> (!<>[] (!pumpOn && highWater))
 *  -> violated by all; the assumption does not change the fact that the
 *     methane has "priority" over the high water.
 * So we account for this in the property.
 *  !<>[] (!pumpOn && !methane && highWater)
 *  -> violated by all, since the controller can ignore highWater messages.
 * So we add the assumption:
 *  (([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> (!<>[] (!pumpOn && !methane && highWater))
 *  -> satisfied by all.
 * 
 * When the pump on and the water is high, it will keep on running until
 * the water is low again.
 *  [] ((pumpOn && highWater && <>lowWater) -> (pumpOn U lowWater))
 *  -> violated by: (Start & !Stop & MethaneAlarm & High) | (Start & Stop & High)
 *     This means that, as expected, the "Stop" feature or the "MethaneAlarm"
 *     can cause a running pump to stop when there is high water.
 * Hypothesis:
 *  !<> (pumpOn && highWater && <>lowWater)
 *  -> violated by: Start & High.
 * 
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Variations of "Pump is off when the water is low":
 *
 * When the water is low, then pump will be off
 *  [] (lowWater -> (<>!pumpOn))
 *  -> violated by: Start & High; due to the fact that the controller can 
 *     ignore the water level notification.
 * With the proper assumption:
 *  (([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> ([] (lowWater -> (<>!pumpOn)))
 *  -> violated by: Start & !MethaneAlarm & !Low & High; As expected, the 
 *     Low and MethaneAlarm features will prevent this.
 * 
 * Similar property: we never arrive at a situation in which the pump runs 
 * indefinitely even though the water is low.
 *  !<>[] (pumpOn && lowWater)
 *  -> violated by: Start & High; same reason as before.
 * The same with the proper assumption:
 *  (([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> (!<>[] (pumpOn && lowWater))
 *  -> violated by: Start & !MethaneAlarm & !Low & High; As expected, the 
 *     Low and MethaneAlarm features will prevent this.
 * 
 * When the pump is off and the water is low, it will only start once the 
 * water is high again.
 *  [] ((!pumpOn && lowWater && <>highWater) -> ((!pumpOn) U highWater))
 *  -> satisfied by all; this is easy since it does not require any feature.
 * Hypothesis:
 *  !<> (!pumpOn && lowWater && <>highWater)
 *  -> violated by all.
 * 
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Macros used in the above properties:
 */
#define readCommand (readMsg == commandMsg)
#define readAlarm (readMsg == alarmMsg)
#define readLevel (readMsg == levelMsg)
#define userStart (uwants == start)
#define userStop (uwants == stop)
#define highWater (waterLevel == high)
#define mediumWater (waterLevel == medium)
#define lowWater (waterLevel == low)
#define stateReady (pstate == ready)
#define stateRunning (pstate == running)
#define stateStopped (pstate == stopped)
#define stateMethanestop (pstate == methanestop)
#define stateLowstop (pstate == lowstop)

/**** PUMP CONTROLLER ****/

ltl pump_state_consistency
{
[] (stateReady || stateRunning || stateStopped || stateMethanestop || stateLowstop)
}

ltl pump_synch_on
{
[] (!pumpOn || stateRunning)
}

ltl pump_weak_synch_off
{
[] (pumpOn || <> !stateRunning)
}

ltl pump_strong_synch_off
{
[] (!stateRunning -> !pumpOn)
}

ltl read_msg_consistency
{
[] (readCommand || readAlarm || readLevel)
}

/**** METHANE ****/

ltl methane_sensor_liveness
{
(([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> ([] (methane -> (<>!stateRunning)))
}

ltl pump_methane_safetyness
{
(([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> (!<>[] (pumpOn && methane))
}

ltl pump_safe_methane_starting
{
[] ((!pumpOn && methane && <>!methane) -> ((!pumpOn) U !methane))
}

ltl methane_sensor_liveness_light
{
([]<> readAlarm) -> ([] (methane -> (<>!stateRunning)))
}

ltl pump_mathane_safetyness_light
{
([]<> readAlarm) -> (!<>[] (pumpOn && methane))
}

/***** LOW WATER *****/

ltl pump_stopping
{
(([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> ([] (lowWater -> (<>!pumpOn)))
}

ltl pump_stopped
{
(([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> (!<>[] (pumpOn && lowWater))
}

/***** HIGH WATER *****/

ltl pump_effectiveness
{
(([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> (!<>[] (!pumpOn && !methane && highWater))
}

ltl pump_activation
{
[] ((!pumpOn && lowWater && <>highWater) -> ((!pumpOn) U highWater))
}

/****** WATER CHANGE ********/

ltl water_level_consistency
{
[] (lowWater || mediumWater || highWater)
}
/*
ltl low_water_evolution_consistency
{
[] (lowWater U (mediumWater || highWater))
}
*/
ltl medium_water_evolution_consistency
{
[] (mediumWater U (lowWater || mediumWater || highWater))
}

ltl high_water_evolution_consistency
{
[] (highWater U (mediumWater || highWater))
}

/****** USER COMMANDS *******/

ltl user_cmd_consistency
{
[] (userStart || userStop)
}
/*
ltl user_start_pump
{
(([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> ([] (userStart -> (!<>[] !pumpOn)))
}

ltl user_stop_pump
{
(([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> ([] (userStop -> (!<>[] pumpOn)))
}*/


