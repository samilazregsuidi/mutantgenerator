import glob
import subprocess

separator = '=====================================================\n'
separator_ = '-----------------------------------------------------\n'

diag = ''
properties_killings = ''
      
killing_report = dict()

time_limit = 60


properties = {'fsm_ready', 'fsm_starting', 'fsm_running', 'fsm_paused', 'fsm_stopping', 'fsm_stopped', 'fsm_aborting', 'fsm_aborted', 'abort_is_undoable', 'supervisor_is_the_first_thread', 'supervisor_constructs_workers', 'supervisor_stops_after_all_workers_stop', 'supervisor_stops_after_some_workers_abort', 'supervisor_never_aborts', 'supervisor_halts_last', 'liveness', 'fairness'}

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
	print("------------- "+str(percent * 100 / len(mutants))+"% ---------------")
	
	res = subprocess.run(['spin','-a', mutant], capture_output=True)
	to_print = res.stdout.decode('utf-8')
	
	if to_print.find('error') != -1 or to_print.find('Error') != -1 or to_print.find('ERROR') != -1:
		print('syntax or semantic error ' + mutant+'\n')
		continue
	
	print('parsed \t\t' + mutant)
		
	res = subprocess.run(['gcc', '-o', 'pan', 'pan.c'], capture_output=True)
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

for survivor in survivors:
        subprocess.run(['cp', survivor, 'survivors'])

subprocess.run(['rm', '-f', '*.tmp'])
subprocess.run(['rm', '-f', '*trail'])
subprocess.run(['rm', '-f', './pan.*'])


