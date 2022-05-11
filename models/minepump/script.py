import glob
import subprocess

separator = '================================================================================'

diag = ''
      
for filename in glob.glob('properties/*'):
	print(filename)
	subprocess.run(['spin','-a', '-F', filename,'original.pml'])
	subprocess.run(['gcc', '-DCOLLAPSE', '-o', 'pan', 'pan.c'])
	res = subprocess.run(['./pan', '-a'], capture_output=True)
	print(str(res.stdout)+'\n')
	if str(res.stdout).find('acceptance cycle'):
		diag += (filename+' \t\t violated\n')
	else:
		diag += (filename+' \t\t satisfied\n')

print(diag)

subprocess.run(['rm', '-f', '*.tmp'])
subprocess.run(['rm', '-f', '*trail'])
subprocess.run(['rm', '-f', './pan.*'])
