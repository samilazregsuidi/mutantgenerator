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
 *  !([]<> (stateReady && highWater))-> violated by: Start
 *  !([]<> stateReady)               -> violated by: Start
 *  !([]<> stateRunning)             -> violated by: Start & High
 *  !([]<> stateMethanestop)         -> violated by: (!Start & MethaneAlarm) | (Start & !MethaneQuery & MethaneAlarm) | (Start & MethaneQuery & !MethaneAlarm & High) | (Start & MethaneQuery & MethaneAlarm)
 *  !([]<> stateLowstop)             -> violated by: Start & Low & High
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
 * 
 * We never arrive at a situation in which the pump runs indefinitely even
 * though there is methane. 
 *  !<>[] (pumpOn && methane)
 *  -> violated by: Start & High; same problem as before: the system can 
 *     all the messages it receives.
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
 * So we account for this in the property.
 *  !<>[] (!pumpOn && !methane && highWater)
 *  -> violated by all, since the controller can ignore highWater messages.
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
 * 
 * Similar property: we never arrive at a situation in which the pump runs 
 * indefinitely even though the water is low.
 *  !<>[] (pumpOn && lowWater)
 *  -> violated by: Start & High; same reason as before.
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

#define highWater (waterLevel == high)
#define mediumWater (waterLevel == medium)
#define lowWater (waterLevel == low)

#define stateReady (pstate == ready)
#define stateRunning (pstate == running)
#define stateMethanestop (pstate == methanestop)
#define stateLowstop (pstate == lowstop)

typedef features {
	bool MinePump=1;
 	bool MethaneQuery=1;
	bool Low=1;
	bool High=1
}

features f;

mtype = {low, medium, high, ready, running, lowstop, methanestop}

chan cMethane = [0] of {mtype}; /* methanestop, ready   */
chan cLevel = [0] of {mtype}; 	/* low, medium, high    */

mtype pstate = ready; 		/* ready, running, methanestop, lowstop */

bool pumpOn = false;
bool methane = false;
mtype waterLevel = medium;

active proctype controller() {

	mtype level = medium;
	
	do  ::	cLevel?level;
			if	::	level == high;
					if	::	f.High;
							if	::	pstate == ready  ||  pstate == lowstop;
									if	::	f.MethaneQuery;
											skip;
											atomic {
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

/*init = (233,242,256)
executables(init) = (235, 237, 244, 248) = current->E
executablesNever(init) = (258, 259) = current->E_never
*/

active proctype methanesensor() {
	do	
       ::   methane = true;
		    cMethane!methanestop;
       ::	methane = false;
			cMethane!ready;
		od;
}

active proctype watersensor() {
	 do	
	    :: 	waterLevel = high;
			cLevel!waterLevel;
        ::  waterLevel = medium;
	        cLevel!waterLevel;
	    ::  waterLevel = low;
	        cLevel!waterLevel;
		od;
};
/*
never {
 T0_init:
* if
 :: (fail) -> goto accept_Strue
 :: (true) -> goto T0_init
 fi;
accept_Strue:
 if
 :: (fail) -> goto accept_Strue
 :: (true) -> goto T0_init
 fi;
}*/
