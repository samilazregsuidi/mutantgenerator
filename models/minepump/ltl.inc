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

 /* The ptstate and actual pump state are in sync: if the pump is on, the state
 * is set to "running".
 *  [] (!pumpOn || stateRunning)
 *  -> satisfied by all.*/
 
ltl pump_synch_on
{
[] (!pumpOn || stateRunning)
}

ltl read_msg_consistency
{
[] (readCommand || readAlarm || readLevel)
}

ltl pump_state_consistency
{
[] (stateReady || stateRunning || stateStopped || stateMethanestop || stateLowstop)
}

/********* ADDED **********/

ltl pump_weak_synch_off
{
[] (pumpOn || <> !stateRunning)
}

ltl pump_strong_synch_off
{
[] (!stateRunning -> !pumpOn)
}

/**** METHANE ****/

/*
 * When the pump is running, and there is methane, then it is eventually 
 * switched off.
 *  [] ((pumpOn && methane) -> <> !pumpOn)
 *  -> violated by: Start & High; these two features are required for the pump
 *     to be switched on in the first place.  Once it is one, the system can 
 *     simply ignore any methane alarms it receives.
 * The same with the proper assumption:
 *  (([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> [] ((pumpOn && methane) -> <> !pumpOn)
 *  -> violated by: Start & !MethaneAlarm & High
 */
ltl pump_methane_switch_off
{
(([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> [] ((pumpOn && methane) -> <> !pumpOn)
}

/*
 * We never arrive at a situation in which the pump runs indefinitely even
 * though there is methane. 
 *  !<>[] (pumpOn && methane)
 *  -> violated by: Start & High; same problem as before: the system can 
 *     all the messages it receives.
 * With the proper assumption:
 *  (([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> !<>[] (pumpOn && methane)
 *  -> violated by: Start & High & !MethaneAlarm; basically, the MethaneAlarm
 *     is required for this property to hold (as expected).
 */
ltl pump_methane_safetyness
{
(([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> (!<>[] (pumpOn && methane))
}

/*
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
 *     is a (commented) piece of code that exhibits this.*/

ltl pump_safe_methane_starting
{
[] ((!pumpOn && methane && <>!methane) -> ((!pumpOn) U !methane))
}

/************** ADDED *************/

ltl methane_sensor_liveness
{
(([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> ([] (methane -> (<>!stateRunning)))
}

ltl methane_sensor_liveness_light
{
([]<> readAlarm) -> ([] (methane -> (<>!stateRunning)))
}

ltl pump_methane_safetyness_light
{
([]<> readAlarm) -> (!<>[] (pumpOn && methane))
}

/***** LOW WATER *****/

/*
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
 */

ltl pump_stopping
{
(([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> ([] (lowWater -> (<>!pumpOn)))
}

/*
 * Similar property: we never arrive at a situation in which the pump runs 
 * indefinitely even though the water is low.
 *  !<>[] (pumpOn && lowWater)
 *  -> violated by: Start & High; same reason as before.
 * The same with the proper assumption:
 *  (([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> (!<>[] (pumpOn && lowWater))
 *  -> violated by: Start & !MethaneAlarm & !Low & High; As expected, the 
 *     Low and MethaneAlarm features will prevent this.*/

ltl pump_stopped
{
(([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> (!<>[] (pumpOn && lowWater))
}

/***** HIGH WATER *****/
/*
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
 *  -> satisfied by all.*/

ltl pump_effectiveness
{
(([]<> readCommand) && ([]<> readAlarm) && ([]<> readLevel)) -> (!<>[] (!pumpOn && !methane && highWater))
}

/*
* When the pump is off and the water is low, it will only start once the 
 * water is high again.
 *  [] ((!pumpOn && lowWater && <>highWater) -> ((!pumpOn) U highWater))
 *  -> satisfied by all; this is easy since it does not require any feature.*/

ltl pump_activation
{
[] ((!pumpOn && lowWater && <>highWater) -> ((!pumpOn) U highWater))
}

/****** WATER CHANGE ********/

ltl water_level_consistency
{
[] (lowWater || mediumWater || highWater)
}

/****** ADDED *********/

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

