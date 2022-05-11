/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Features
 * 
 *  x empty: if empty, all calls inside the lift are ignored
 *  x exec: executive floor: calls to/at this floor have priority
 *  x open-if-idle: when the lift is idle it will open its doors
 *  x overload: when the lift is overloaded, it will not close its doors 
 *  x park: when the lift is idle, it will park at floor 0
 *  x quick-close: the lift door cannot be reopened by pushing the platform 
 *    button if there are other calls
 *  x shuttle: the lift will not change its direction in the middle.
 *  x tt-full: when the lift is two-thirds full, ill will ignore any floor 
 *    calls
 * 
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Properties
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Assumptions
 * 
 * The controller goes infinitely often through the main loop.
 *  ![]<> progress
 * Violated in every product; i.e. reasonable assumption for every product.
 * 
 * All floors are visited infinitely often:
 *  ![]<>f0 || ![]<>f1 || ![]<>f2 || ![]<>f3
 * Violated in every product; i.e. reasonable assumption for every product.
 * 
 * Each person can infinitely often visit each floor
 *  ![]<>p0at0 || ![]<>p0at1 || ![]<>p0at2 || ![]<>p0at3
 * Violated in every product; i.e. reasonable assumption for every product.
 *
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Service properties
 * 
 * When a button is pushed, the elevator will eventually arrive at the floor.
 *  [] (fb2 -> (<> f2)
 *  -> violated by all: missing the assumption that the elevator actually
 *     does something. In this case, the proctype of the controller does not
 *     advance.
>>> To be revised: <<<
 * The same with an assumption:
 *  []<> progress -> ([] (fb2 -> (<> f2)))
 *  -> violated by !Shuttle & Exec: when people keep calling the executive 
 *     floor (3) is called at indefinetely, then the lift will indefinitely
 *     remain there.  That is, unless it operates in shuttle mode, in which
 *     case the exec feature is overridden.
>>> To be revised: <<<
 * However, in that case, it probably won't open its doors at floor 2..:
 *  []<> progress -> ([] (fb2 -> (<> (f2 && dopen))))
 *  -> violated by Exec: as expected; it just passes by.
 *
 * If a person wants to floor X he will eventually get to it.
 *  []<> progress -> ([] (p0to2 -> (<> p0at2)))
 *  -> violated by all: this is related to the timeout, which (it appears)
 *     can occur even after the floor has changed (which of course; should
 *     not be possible since the floor can't change unless the door closes)
 *     This is maybe due to the door == closed transition, not being executed
 *     necessarily!  To be checked.
 *
>>> To be revised: <<<
 * The lift won't idle forever at floor 2.
 *  []<> progress -> (!<>[] f2)
 *  -> violated by: !Shuttle, which is due to the fact that the shuttle 
 *     feature will never keep the lift at the same floor indefinitely.
 *     This property does not take into account the parking or idle 
 *     features because they set the variable "waiting".
>>> To be revised: <<<
 * With the changed assumption:
 *  []<> (progress || waiting) -> (!<>[] f2)
 *  -> violated by: (!Shuttle) | (Shuttle & !QuickClose) | (Shuttle & QuickClose & OpenIfIdle)
 *     that is: !Shuttle | !QuickClose | OpenIfIdle, whis is not very
 *     intuitive since QuickClose and OpenIfIdle  should not have an effect.
 *     This is in fact due to both of these features allowing the peson 
 *     proctypes to execute indefinitely.
>>> To be revised: <<<
 * When we do this for the parking floor, we get:
 *  []<> (progress || waiting) -> (!<>[] f0)
 *  -> violated by: (!Shuttle) | (Shuttle & !Park & !QuickClose) | (Shuttle & !Park & QuickClose & OpenIfIdle) | (Shuttle & Park)
 *     that is: !Shuttle | !QuickClose | OpenIfIdle | Park, the same as 
 *     before plus the Park feature, as expected.
 *
 * It is impossible that cabin buttons are pressed and nobody is inside.
 *  !<> ((cb0 || cb1 || cb2 || cb3) && !(p0in || p1in) && dclosed)
 *  -> violated by !Empty: as expected, only the empty feature prevents 
 *     this situation.
 * 
 * The door should never remain closed indefinitely.
 *  []<> progress -> (!<>[] dclosed)
 *  -> violated by all: simply if nobody wants to take the elevator.
 * The door should never remain closed indefinitely while somebody wants to
 * travel.
 *  []<> progress -> (!<>[] (p0to3 && dclosed))
 *  -> satisfied by all
 * 
 * The door should never remain open indefinitely.
 *  []<> progress -> (!<>[] dopen)
 *  -> satisfied by all: this is correct, even with the parking of openIfIdle
 *     features and without the quickClose feature, the progress variable 
 *     prevents the case in which the lift waits for customers.
 * The same but accounting for the waiting time:
 *  []<> (progress || waiting) -> (!<>[] dopen)
 *  -> violated by: (!Park & !QuickClose) | (!Park & QuickClose & OpenIfIdle) | (Park)
 *     This boils down to Park || OpenIfIdle || !QuickClose: if these features
 *     are present, then the lift might keep its doors indefintely open since
 *     customers might keep pushing buttons indefitely or stop altogether.
 * Now we add the assumption that platform buttons are pushed infinitely often
 *  (([]<> (progress || waiting)) && ([]<> (fb0 || fb1 || fb2 || fb3))) -> (!<>[] dopen)
 *  -> violated by the same as before.
 *     When users keep pushing buttons, then normally the OpenIfIdle and Park
 *     features will not keep the lift doors open indefinitely ofen as they
 *     rely on buttons not being pused. Only !QuickClose should then violate
 *     the property and allow this.  This is not the case, because Park and
 *     OpenIfIdle set the waiting variable, after which control will not have
 *     to be passed back to the controller, and so they violate the property
 *     because of this.  This property has yet to be refined.
 * 
 * There cannot be two persons in the elevator at the same time.
 *  !<> (p0in && p1in && dclosed)
 *  -> violated by !Overload: as expected, the overload feature will prevent
 *     two persons from being transported at the same time.
 * 
 * A person cannot be trapped forever in the elevator.
 *  !<>[] (p0in && dclosed)
 *  -> violated by all: missing the assumption that the elevator actually
 *     does something. In this case, the proctype of the controller does not
 *     advance.
>>> To be revised: <<<
 * The same with an assumption:
 *  []<> progress -> (!<>[] (p0in && dclosed))
 *  -> satisfied by all.
 *     
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Macros used in the above properties:
 */
#define f0 (floor == 0)
#define f1 (floor == 1)
#define f2 (floor == 2)
#define f3 (floor == 3)
#define f4 (floor == 4)
#define f5 (floor == 5)

#define dopen (door == open)
#define dclosed (door == closed)

#define goingup (direction == up)
#define goingdown (direction == down)
#define staying (direction == stay)

#define fb0 (floor_button[0].pushed)
#define fb1 (floor_button[1].pushed)
#define fb2 (floor_button[2].pushed)
#define fb3 (floor_button[3].pushed)
#define fb4 (floor_button[4].pushed)
#define fb5 (floor_button[5].pushed)

#define cb0 (cabin_button[0].pushed)
#define cb1 (cabin_button[1].pushed)
#define cb2 (cabin_button[2].pushed)
#define cb3 (cabin_button[3].pushed)
#define cb4 (cabin_button[4].pushed)
#define cb5 (cabin_button[5].pushed)

#define p0in (person[0].in_elevator)
#define p1in (person[1].in_elevator)
#define p2in (person[2].in_elevator)

#define p0at0 (person[0].at_floor == 0)
#define p0at1 (person[0].at_floor == 1)
#define p0at2 (person[0].at_floor == 2)
#define p0at3 (person[0].at_floor == 3)
#define p0at4 (person[0].at_floor == 4)
#define p0at5 (person[0].at_floor == 5)
#define p1at0 (person[1].at_floor == 0)
#define p1at1 (person[1].at_floor == 1)
#define p1at2 (person[1].at_floor == 2)
#define p1at3 (person[1].at_floor == 3)
#define p1at4 (person[1].at_floor == 4)
#define p1at5 (person[1].at_floor == 5)
#define p2at0 (person[2].at_floor == 0)
#define p2at1 (person[2].at_floor == 1)
#define p2at2 (person[2].at_floor == 2)
#define p2at3 (person[2].at_floor == 3)
#define p2at4 (person[2].at_floor == 4)
#define p2at5 (person[2].at_floor == 5)

#define p0to0 (person[0].to_floor == 0)
#define p0to1 (person[0].to_floor == 1)
#define p0to2 (person[0].to_floor == 2)
#define p0to3 (person[0].to_floor == 3)
#define p0to4 (person[0].to_floor == 4)
#define p0to5 (person[0].to_floor == 5)
#define p1to0 (person[1].to_floor == 0)
#define p1to1 (person[1].to_floor == 1)
#define p1to2 (person[1].to_floor == 2)
#define p1to3 (person[1].to_floor == 3)
#define p1to4 (person[1].to_floor == 4)
#define p1to5 (person[1].to_floor == 5)
#define p2to0 (person[2].to_floor == 0)
#define p2to1 (person[2].to_floor == 1)
#define p2to2 (person[2].to_floor == 2)
#define p2to3 (person[2].to_floor == 3)
#define p2to4 (person[2].to_floor == 4)
#define p2to5 (person[2].to_floor == 5)

/* 
 * Modifying these macros is sufficient for varying the number of floors and persons.
 * The indices range from 0 to NB*-1!
 */
#define NBPERS 2
#define SIZE_OVERLOAD 2
#define SIZE_TT 2
#define allPersons(field, value) (person[0].field == value && person[1].field == value)
#define nbPersonsInElevator() ((person[0].in_elevator ; 1 : 0) + (person[1].in_elevator ; 1 : 0))
#define NBFLOORS 4
#define EXEC_FLOOR 3
#define PARK_FLOOR 0
#define cancelCabinButtons()   cabin_button[0].pushed = false; \
	                           cabin_button[1].pushed = false; \
	                           cabin_button[2].pushed = false; \
	                           cabin_button[3].pushed = false
#define choosefloor(var) if :: [0.4] var = 0; :: [0.2] var = 1; :: [0.2] var = 2;  :: [0.2] var = 3; fi;
#define choosefloorExcept(var, not) if :: not != 0; var = 0; :: not != 1; var = 1; :: not != 2; var = 2;  :: not != 3; var = 3; fi;
#define buttonPushed()			(		               floor_button[0].pushed || cabin_button[0].pushed   \
									||	               floor_button[1].pushed || cabin_button[1].pushed   \
									||	               floor_button[2].pushed || cabin_button[2].pushed   \
									||	               floor_button[3].pushed || cabin_button[3].pushed   \
									)
#define buttonAbovePushed(floor) (		(floor < 0 && (floor_button[0].pushed || cabin_button[0].pushed)) \
									||	(floor < 1 && (floor_button[1].pushed || cabin_button[1].pushed)) \
									||	(floor < 2 && (floor_button[2].pushed || cabin_button[2].pushed)) \
									||	(floor < 3 && (floor_button[3].pushed || cabin_button[3].pushed)) \
									)
#define buttonBelowPushed(floor) (		(floor > 0 && (floor_button[0].pushed || cabin_button[0].pushed)) \
									||	(floor > 1 && (floor_button[1].pushed || cabin_button[1].pushed)) \
									||	(floor > 2 && (floor_button[2].pushed || cabin_button[2].pushed)) \
									||	(floor > 3 && (floor_button[3].pushed || cabin_button[3].pushed)) \
									)
/*
#define debug_printf(s) printf(s);
#define debug_printf_a(s, a) printf(s, a);
#define debug_printf_aa(s, a, b) printf(s, a, b);
#define debug_printm(s) printm(s);
*/
#define debug_printf(s) 
#define debug_printf_a(s, a) 
#define debug_printf_aa(s, a, b) 
#define debug_printm(s)

typedef features {
    bool Elevator=1;
	bool Empty=1;
	bool Exec=0;
	bool OpenIfIdle=0;
	bool Overload=1;
	bool Park=0;
	bool QuickClose=1;
	bool Shuttle=1;
	bool TTFull=1
}

features f;

typedef tPerson {
	byte at_floor = 0;  	
	byte to_floor = 0;		/* both fields have value 0 when they are not used in order to keep the number of states low */
	bool in_elevator = 0
}

typedef tButton {
	bool pushed = false
}

tPerson person[NBPERS];
tButton cabin_button[NBFLOORS];
tButton floor_button[NBFLOORS];

byte floor = 0;

mtype = {open, closed, up, down, stay}
mtype door = closed;
mtype direction = stay;

/*
 * This person is determined;
 *  - Does not err in the choice of the floor.
 *  - Gets out at the chosen floor as soon as the lift arrives there.
 *  - Two small distractions: might decide not to take the elevator after having 
 *    called it; might decide to leave the elevator after having chosen, but before
 *    the doors close.
 */
#define me person[_pid]
active [NBPERS] proctype ptPersonDetermined() {
	/* Initial floor non-deterministic */
	choosefloor(me.at_floor);
	debug_printf_aa("P%d: Start at floor %d..\n", _pid, me.at_floor)
	
	do	::	atomic {
				floor_button[me.at_floor].pushed = true;
				debug_printf_aa("   P%d: Pushed button at floor %d..\n", _pid, me.at_floor)
			};
			
			/* Wait for the cabin to arrive and its doors to open (blocks until then); or don't do anything */
			if	::	skip;
				::	atomic {
						floor == me.at_floor && door == open;
						debug_printf_aa("   P%d: -> Elevator arrived at %d, entering..\n", _pid, me.at_floor)
						me.at_floor = 0;
						me.in_elevator = true;
						
						choosefloorExcept(me.to_floor, floor);
						cabin_button[me.to_floor].pushed = true;
						debug_printf_aa("   P%d: In elevator, pushed button of floor %d..\n", _pid, me.to_floor)
					
						if	::	door == closed;
								floor == me.to_floor && door == open;
								me.at_floor = floor;
								me.to_floor = 0;
								me.in_elevator = false;
								debug_printf_aa("   P%d:       -> Getting out at %d.\n", _pid, me.at_floor)
								
							::	timeout;
								me.at_floor = floor;
								me.to_floor = 0;
								me.in_elevator = false;
								debug_printf_aa("   P%d:       -> Left before doors closed and stayed at %d.\n", _pid, me.at_floor)
							fi;
					};
				fi;
		od;
}

/*
 * The differences wrt. the determined person are:
 *  - Might select another floor while the elevator is moving.
 *  - Might miss his stop (and push the button of the desired stop again).
 *  - Can get out at any floor except the one he got in at.
 * The result is a much larger system.
 * 
active [NBPERS] proctype ptPersonDistracted() {
	/* Initial floor non-deterministic *
	choosefloor(me.at_floor);
	debug_printf_aa("P%d: Start at floor %d..\n", _pid, me.at_floor)
	
	/* Non deterministically decide whether to go to another floor *
	do	::	debug_printf_a("   P%d: Doing nothing..\n", _pid)
			skip;
		::	atomic {
				floor_button[me.at_floor].pushed = true;
				debug_printf_aa("   P%d: Pushed button at floor %d..\n", _pid, me.at_floor)
			};
			
			/* Wait for the cabin to arrive and its doors to open (blocks until then); or don't do anything *
			if	::	skip;
				::	atomic {
						floor == me.at_floor && door == open;
						me.in_elevator = true;
						debug_printf_aa("   P%d: -> Elevator arrived at %d, entering..\n", _pid, me.at_floor)
						choosefloorExcept(me.to_floor, floor);
						cabin_button[me.to_floor].pushed = true;
						debug_printf_aa("   P%d: In elevator, pushed button of floor %d..\n", _pid, me.to_floor)
					};
					
					if	::	door == closed;
						::	atomic { 
								timeout;
								assert(door == open);
								me.at_floor = floor;
								me.to_floor = 0;
								me.in_elevator = false;
								debug_printf_aa("   P%d:       -> Left before doors closed and stayed at %d.\n", _pid, me.at_floor)
							};
						fi;	
					
					if	::	skip;
						::	atomic {
								choosefloorExcept(me.to_floor, me.at_floor);
								cabin_button[me.to_floor].pushed = true;
								debug_printf_aa("   P%d: In elevator, changed mind, pushed button of floor %d..\n", _pid, me.to_floor)
							};
						fi;
					
					do	::	skip;
						::	cabin_button[me.to_floor].pushed = true;
						::	atomic {
								floor != me.at_floor && door == open;	/* to make it even more realistic, the "floor != me.at_floor" can be removed (might double states) *
								me.at_floor = floor;
								me.to_floor = 0;
								me.in_elevator = false;
								debug_printf_aa("   P%d:       -> Got out at %d.\n", _pid, me.at_floor)
							};	
							break;
						od;
				fi;
		od;
}*/

bool progress = false;
bool waiting = false;

active proctype controller() {
	bool stop = false;

	do	::	[0.6] progress = false;
		::  [0.4] progress = true;
			debug_printf_a("E: Loop start (floor %d)\n", floor)
			
			/* 
			 * Check whether to stop; if yes: stop, open, close
			 *
			 * With the exec feature, a floor will be skipped when the executive floor was called
			 * and this isn't it.  With TTFull feature, a floor will be skipped when only the
			 * floor button was pushed and the lift is already full.
			 *
			 * These features interact.  The interaction is resolved by addressing each case
			 * individually.  The resolution is to exempt the executive floor from the overload
			 * rule.
			 */
			
			if	::	f.TTFull  && f.Exec;
					stop = (nbPersonsInElevator() < SIZE_TT ; 
								(cabin_button[floor].pushed || floor_button[floor].pushed) && (floor == EXEC_FLOOR || !(cabin_button[EXEC_FLOOR].pushed || floor_button[EXEC_FLOOR].pushed))
							:	(cabin_button[EXEC_FLOOR].pushed || floor_button[EXEC_FLOOR].pushed ;
										floor == EXEC_FLOOR
									: 	cabin_button[floor].pushed || (floor_button[floor].pushed && nbPersonsInElevator() < SIZE_TT)));
				::	f.TTFull  && !f.Exec;
					stop = cabin_button[floor].pushed || (floor_button[floor].pushed && nbPersonsInElevator() < SIZE_TT);
				::	!f.TTFull &&  f.Exec;
					stop = (cabin_button[floor].pushed || floor_button[floor].pushed) && (floor == EXEC_FLOOR || !(cabin_button[EXEC_FLOOR].pushed || floor_button[EXEC_FLOOR].pushed));
				::	else;
					stop = (cabin_button[floor].pushed || floor_button[floor].pushed);
				fi;
				
			if 	::	atomic {
						stop;
						stop = false;
						door = open;
						cabin_button[floor].pushed = false;
						floor_button[floor].pushed = false;
						debug_printf("E: - Stopping, opening doors..\n")
					
						/* We assume that everybody who wants out of the elevator does get out when it stops */
						(person[0].to_floor != floor || !person[0].in_elevator)	&& (person[1].to_floor != floor || !person[1].in_elevator);
					};

					/* Here, unless the QuickClose feature is there, the doors can be kept open by holding the floor button pushed */
					if	::	!f.QuickClose;
							do	::	atomic {
										floor_button[floor].pushed || cabin_button[floor].pushed;
										floor_button[floor].pushed = false;
										cabin_button[floor].pushed = false;
										waiting = true;
									};
									waiting = false;
								::	else;
									break;
								od;
						::	else;
						fi;
						
					/* When no calls, stay here and wait (except if f.Park is selected, then we only stay if we're at the parking floor) */
					if	::	f.OpenIfIdle || f.Park;
							if	::	atomic {
										floor == PARK_FLOOR;
										waiting = true;
									};
									atomic {										
										buttonPushed();
										waiting = false;
									};
								::	else;
									if	::	f.OpenIfIdle;
											waiting = true;
											atomic {
												buttonPushed();
												waiting = false;
											};
										::	else;
										fi;
								fi;
						::	else;
						fi;
					
					
					/* People can go in, before we close the doors */
					
					atomic {
						/* With overload, we wait until the lift is not overloaded. */
						if	::	f.Overload;
								nbPersonsInElevator() < SIZE_OVERLOAD;
							::	else;
							fi;

						cabin_button[floor].pushed = false;
						floor_button[floor].pushed = false;

						/* With the empty feature: all calls inside the cabin are canceled if no one is in there */
						if	::	f.Empty;
								if	::	allPersons(in_elevator, false);
										cancelCabinButtons();
									::	else;
									fi;
							::	else;
							fi;
							
						door = closed;	
					};
				::	else -> skip;
				fi;
			
			/*
			 * Determine direction as follows: 
			 *  - If no button was pressed or if the buttons of the current floor are pressed, the lift remains where it is.
			 *  - If we're on the top floor, direction is down, if we're on the bottom floor, direction is up.
			 *  - If a button was pushed in the direction we travel, we continue in this direction; otherwise, we revert.
			 */
			atomic {
				debug_printf_aa("f0 - floor: %d, cabin: %d\n", floor_button[0].pushed, cabin_button[0].pushed)
				debug_printf_aa("f1 - floor: %d, cabin: %d\n", floor_button[1].pushed, cabin_button[1].pushed)
				debug_printf_aa("f2 - floor: %d, cabin: %d\n", floor_button[2].pushed, cabin_button[2].pushed)
				debug_printf_aa("f3 - floor: %d, cabin: %d\n", floor_button[3].pushed, cabin_button[3].pushed)
				debug_printf("E: - Determining direction, current: '")
				debug_printm(direction)
				debug_printf_aa("', below: %d, above: %d, ", buttonBelowPushed(floor), buttonAbovePushed(floor))

				/* 
				 * Do not officially change the direction to "stay" if someone has pushed at the current floor.
				 * Otherwise, the previous direction is lost and the lift will not continue in it (it would thus
				 * be possible to trick the lift into going down first).
				 */

				bool set = false;

				/* With the shuttle feature, there are no direction changes in between */
				if	::	f.Shuttle;
						direction = (floor == 0 -> up : (floor == NBFLOORS-1 -> down : direction));
						set = true;
					::	else;
					fi;

				/* With the executive floor feature, the direction is fixed if a call was made for it. */
				if	::	f.Exec;
						if	::	!set && (cabin_button[EXEC_FLOOR].pushed || floor_button[EXEC_FLOOR].pushed);
								direction = (EXEC_FLOOR < floor -> down : (EXEC_FLOOR > floor -> up : stay));
								set = true;
							::	else;
							fi;
					::	else;
					fi;
				
				/* When the park feature is active, then go to the parking floor. */
				if	::	f.Park;
						if	::	!set && !buttonPushed();
								direction = (PARK_FLOOR < floor -> down : (PARK_FLOOR > floor -> up : stay));
								set = true;
							::	else;
							fi;
					::	else;
					fi;
				
				if	::	set;
				 		set = false;
					::	else;
						direction = (floor == 0 -> up : (floor == NBFLOORS-1 -> down : direction));
						direction = (buttonBelowPushed(floor) && direction == down -> 		down
										: (buttonAbovePushed(floor) && direction == up -> 	up
											: (buttonBelowPushed(floor) -> 					down
												: (buttonAbovePushed(floor) -> 				up
													:										stay
														))));
					fi;

				/* Advance */
				floor = (direction == up -> floor + 1 : (direction == down -> floor - 1 : floor));
				/* assert(floor >= 0 && floor < NBFLOORS); */
					
				debug_printf("new: '")
				debug_printm(direction)
				debug_printf_a("', new floor: %d.\n", floor)
			};
		od;
}

