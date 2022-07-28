import os
import glob

states = glob.glob('*.dot')

for state in states:
	print(state)
	os.system('dot -Tpdf ' + state +' > pdfs/'+state+'.pdf')

os.system('rm *.dot')

os.system('pdfunite $(ls -v pdfs/*.pdf) trace.pdf')

os.system('rm pdfs/*.pdf')
