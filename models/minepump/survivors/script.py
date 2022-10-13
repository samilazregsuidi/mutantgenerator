import glob
import subprocess

separator = '=====================================================\n'
separator_ = '-----------------------------------------------------\n'

diag = ''
properties_killings = ''
      
killing_report = dict()

time_limit = 60


#properties = {
#'pump_state_consistency',
#'pump_synch_on', 
#'read_msg_consistency',
#
#'pump_methane_switch_off'
#'pump_methane_safetyness', 
#'pump_safe_methane_starting', 
#
#'pump_stopping', 
#'pump_stopped',
#'pump_effectiveness', 
#'pump_activation',
#
#'water_level_consistency',
#
#'user_cmd_consistency'
#}

properties = {
#'pump_state_consistency',
#'pump_synch_on', 
#'read_msg_consistency',
'pump_weak_synch_off',
#'pump_strong_synch_off',

#'pump_methane_switch_off'
#'pump_methane_safetyness', 
#'pump_safe_methane_starting', 
#'methane_sensor_liveness',
#'methane_sensor_liveness_light',
#'pump_methane_safetyness_light',

#'pump_stopping', 
#'pump_stopped',
#'pump_effectiveness', 
#'pump_activation',

'water_level_consistency',
'low_water_evolution_consistency',
'medium_water_evolution_consistency',
'high_water_evolution_consistency'

#'user_cmd_consistency'
}

mutants = glob.glob('*.pml')
#mutants = {'original.pml', 'mutant_1.pml', 'mutant_10.pml', 'mutant_20.pml', 'mutant_30.pml', 'mutant_40.pml', 'mutant_50.pml', 'mutant_60.pml', 'mutant_70.pml', 'mutant_80.pml', 'mutant_90.pml'} 
#survivors = {'original.pml', 'mutant_1.pml', 'mutant_10.pml', 'mutant_20.pml', 'mutant_30.pml', 'mutant_40.pml', 'mutant_50.pml', 'mutant_60.pml', 'mutant_70.pml', 'mutant_80.pml', 'mutant_90.pml'} 
survivors = glob.glob('*.pml')
assert(len(mutants) > 0)
assert(len(properties) > 0)

for prop in properties:
	killing_report[prop] = list()

percent = 0

for mutant in mutants:

	print(separator)
	print("------------- "+str(percent * 100 / len(mutant))+"% ---------------")
	
	res = subprocess.run(['spin','-a', mutant], capture_output=True)
	to_print = res.stdout.decode('utf-8')
	
	if to_print.find('error') != -1 or to_print.find('Error') != -1 or to_print.find('ERROR') != -1:
		print('syntax or semantic error ' + mutant+'#'+properties+'\n')
		continue
	
	print('parsed \t\t' + mutant)
		
	res = subprocess.run(['gcc', '-DNOREDUCE', '-o', 'pan', 'pan.c'], capture_output=True)
	to_print = res.stdout.decode('utf-8')
	if to_print.find('error') != -1:
		diag += 'compilation error ' + mutant+'\n'
		continue
		
	print('compiled \t' + mutant)
	
	for prop in properties:
		
		print('checking \t'+mutant+'#'+prop)
		try:
			res = subprocess.run(['./pan', '-a', '-f', '-n', '-m100000', '-w30', '-N', prop], capture_output=True, timeout=time_limit)
			
		except subprocess.TimeoutExpired:
			print('timeout \t'+mutant + '#'+ prop+'\n')
			diag += (prop+'\t\t'+ mutant +'\t\t timeout\n')
			killing_report[prop].append(mutant)
			if mutant in survivors:
				survivors.remove(mutant)
			continue
		
		to_print = res.stdout.decode('utf-8')
		
		if to_print.find('acceptance cycle') != -1 or to_print.find('assertion violated') != -1:
			print('violated \t'+mutant+'#'+prop+'\n')
			killing_report[prop].append(mutant)
			if mutant in survivors:
				survivors.remove(mutant)
			diag += (prop+'\t\t'+ mutant +'\t\t violated\n')
		else:
			print('satisfied \t'+mutant+'#'+prop+'\n')
			diag += (prop+'\t\t'+ mutant +'\t\t satisfied\n')
			
		print(separator_)
		diag += to_print+'\n'+separator+'\n'
		
	percent = percent + 1
	
for prop in properties:
	if (len(killing_report[prop]) * 100 / len(mutants)) > 0:
		properties_killings += "*****************************************************\n\n"
		properties_killings += prop + ' killed '+ str(len(killing_report[prop]) * 100 / len(mutants)) + '% of mutants\n\n'


print(properties_killings)
diag += properties_killings

nb_killed = len(mutants) - len(survivors)
mutation_result = '********** MUTATION SCORE : '+ str(nb_killed * 100 / len(mutants)) + '% **********\n\n'
mutation_result += 'SURVIVORS : \n{\n'
for survivor in survivors:
	mutation_result += '\t' + str(survivor) + '\n'
mutation_result += '}\n'

print(mutation_result)
diag += mutation_result

#print(diag)
log = open("log.txt", 'w')
log.write(diag)

subprocess.run(['rm', '-f', '*.tmp'])
subprocess.run(['rm', '-f', '*trail'])
subprocess.run(['rm', '-f', './pan.*'])


