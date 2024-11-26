import numpy as np
import matplotlib.pyplot as plt
from decimal import Decimal
import os
import csv
import matplotlib.ticker as ticker
import sys

def DoRatio(tag1, tag2):

	postfit1 = 'postfit_errors_' + tag1 +'.txt'
	postfit2 = 'postfit_errors_' + tag2 +'.txt'
	
	with open(postfit1,'r') as file:
		errors1 = [float(line.strip()) for line in file]

	with open(postfit2,'r') as file:
		errors2 = [float(line.strip()) for line in file]

	ratio=[x / y for x,y in zip(ratio1, ratio2)]

	plt.hist(ratio, bins=10, alpha=0.7, color='blue', edgecolor='black')
	plt.xlabel('Ratio')
	plt.ylabel('Frequency')
	plt.title('Histogram of Error Ratios '+tag1+'/'+tag2)
	plt.grid(True)
	plt.show()

if len(sys.argv) != 3:
    print("Usage: python3 script_name.py tag1 tag2")
    sys.exit(1)

tag1 = sys.argv[1]
tag2 = sys.argv[2]
DoRatio(tag1,tag2)
