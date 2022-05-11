import glob
import subprocess

separator = '=====================================================\n'
diag = ''
properties_killings = ''
      
killing_report = dict()


mutants = glob.glob('*.pml')
survivors = glob.glob('*.pml')
assert(len(mutants) > 0)
assert(len(glob.glob('../properties/*')) > 0)

for properties in glob.glob('../properties/*'):

	killing_report[properties] = list()
	for mutant in mutants:
		print(separator)
		
		res = subprocess.run(['spin','-a', '-F', properties, mutant], capture_output=True)
		to_print = res.stdout.decode('utf-8')
		if to_print.find('error') != -1 or to_print.find('Error') != -1 or to_print.find('ERROR') != -1:
			print('syntax or semantic error ' + mutant+'#'+properties+'\n')
			continue
		print('parsed \t\t' + mutant+'#'+properties)
			
		res = subprocess.run(['gcc', '-o', 'pan', 'pan.c'], capture_output=True)
		to_print = res.stdout.decode('utf-8')
		if to_print.find('error') != -1:
			diag += 'compilation error ' + mutant+"#"+properties +'\n'
			continue
		print('compiled \t' + mutant + '#'+ properties)
		
		
		print('checking \t'+mutant+'#'+properties+'\n')
		try:
			res = subprocess.run(['./pan', '-a', '-m40000'], capture_output=True, timeout=10)
		except subprocess.TimeoutExpired:
			print('timeout \t'+mutant + '#'+ properties+'\n')
			diag += (properties+'\t\t'+ mutant +'\t\t timeout\n')
			killing_report[properties].append(mutant)
			if mutant in survivors:
				survivors.remove(mutant)
			continue
		
		to_print = res.stdout.decode('utf-8')
		
		if to_print.find('acceptance cycle') != -1 or to_print.find('assertion violated') != -1:
			print('violated \t'+mutant+'#'+properties+'\n')
			killing_report[properties].append(mutant)
			if mutant in survivors:
				survivors.remove(mutant)
			diag += (properties+'\t\t'+ mutant +'\t\t violated\n')
		else:
			print('satisfied \t'+mutant+'#'+properties+'\n')
			diag += (properties+'\t\t'+ mutant +'\t\t satisfied\n')
			
		diag += to_print+'\n'+separator+'\n'
	
	properties_killings += "*****************************************************\n\n"
	properties_killings += '////////// '+ properties + ' killed '+ str(len(killing_report[properties]) * 100 / len(mutants)) + '% of mutants //////////\n\n'


print(properties_killings)
diag += properties_killings
	
mutation_result = '********** MUTATION SCORE : '+ str(len(survivors) * 100 / len(mutants)) + '% **********\n\n'
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


