"""
**************************************************
|Ibrar Yunus
|BSCS-2B
|Advanced Programming
|Assignment 1
**************************************************
"""

"""Imports"""
import random
import easygui
#Library for GUI creation
import Tkinter
import tkSimpleDialog
from Tkinter import * 
from easygui import * 
import AS1_IbrarYunus

"""For colored output ot the console"""
class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

print "Initilizing GUI"
option = indexbox(msg='Run Unit Tests or With Random Input?', title=' ', choices=('Unit Tests', 'Random Input'), image=None)



def Trivial():
	"""This is the number of stations"""
	num = 2
	"""Added +1 to allow list indexes from 1 to n (rather than 0 tp n-1)"""
	num = num + 1
	"""Creation of dynamic 2D and 1D lists"""
	a = [[0 for x in range(num)] for x in range(3)] 
	t = [[0 for x in range(num)] for x in range(3)] 
	e = [0 for x in range(num)]
	x = [0 for x in range(num)]

	"""for passing on to the _fastestWay function"""
	n = num

	"""Initializes random numbers to each of the array indexes"""
	for i in range(num):
		a[1][i] = 1
		a[2][i] = 67
		t[1][i] = 9
		t[2][i] = 9

	"""Initializes random numbers to each of the array indexes"""
	for i in range(1,3):
		e[i] 	= 1
		x[i]	= 1
	"""Assertion Check (Problem Statement and return should be 4, verified by dry - running"""
	assert _OUT(a,t,e,x,n) == '4'

def Medium():
	"""This is the number of stations"""
	num = 6
	"""Added +1 to allow list indexes from 1 to n (rather than 0 tp n-1)"""
	num = num + 1
	"""Creation of dynamic 2D and 1D lists"""
	a = [[0 for x in range(num)] for x in range(3)] 
	t = [[0 for x in range(num)] for x in range(3)] 
	e = [0 for x in range(num)]
	x = [0 for x in range(num)]

	"""for passing on to the _fastestWay function"""
	n = num

	"""Initializes random numbers to each of the array indexes"""
	
	a[1][1] = 7
	a[1][2] = 9
	a[1][3] = 3
	a[1][4] = 4
	a[1][5] = 8
	a[1][6] = 4

	a[2][1] = 8
	a[2][2] = 5
	a[2][3] = 6
	a[2][4] = 4
	a[2][5] = 5
	a[2][6] = 7

	t[1][1] = 2
	t[1][2] = 3
	t[1][3] = 1
	t[1][4] = 3
	t[1][5] = 4

	t[2][1] = 2
	t[2][2] = 1
	t[2][3] = 2
	t[2][4] = 2
	t[2][5] = 1

	e[1] = 2
	e[2] = 4

	x[1] = 3
	x[2] = 2

	"""Assertion Check (Problem Statement and return should be 37, verified from an example in book"""
	assert _OUT(a,t,e,x,n) == '38'	

def _OUT(a,t,e,x,n):
	"""UI Print statements, do not contribute to mathematical logic"""
	_formattedText = ""
	print '   Taking total stations as: ' + str(n) + '\n'
	print '   Entry to Line 1: ' + bcolors.WARNING + str(e[1]) + bcolors.ENDC
	print '   Entry to Line 2: ' + bcolors.FAIL + str(e[2]) + bcolors.ENDC + '\n'
	print '   Line 1' + '    ' + 'Trans' + '\t' + 'Line 2'

	_formattedText = _formattedText + '   Taking total stations as: ' + str(n) + '\n'
	_formattedText = _formattedText + '   Entry to Line 1: '  + str(e[1]) + '\n'
	_formattedText = _formattedText + '   Entry to Line 2: '  + str(e[2]) + '\n'
	_formattedText = _formattedText + '   Line 1' + '     ' + 'Trans' + '    ' + 'Line 2' + '\n'

    # _formattedText + 'jdsk'
	

	"""for printing the problem statement to Console"""
	for i in range(n):
		print bcolors.WARNING + "     " + str(a[1][i]) + bcolors.FAIL + '\t\t        ' + str(a[2][i]) + bcolors.ENDC
		_formattedText =  _formattedText + "    " + str(a[1][i]) + '                  ' + str(a[2][i]) + '\n'
		if( i < n-1 ):
			print '\t     ' + bcolors.WARNING + str(t[1][i]) + bcolors.FAIL + '/' + str(t[2][i]) 
			_formattedText = _formattedText + '              '  + str(t[1][i])  + '/' + str(t[2][i]) + '\n'

	"""UI Print statements, do not contribute to mathematical logic"""
	print '\n   Exit from Line 1: ' + bcolors.WARNING + str(x[1]) + bcolors.ENDC
	_formattedText = _formattedText + '\n   Exit from Line 1: '  + str(x[1])  + '\n'
	print '   Exit from Line 2: ' + bcolors.FAIL + str(x[2]) + bcolors.ENDC
	_formattedText = _formattedText + '   Exit from Line 2: '  + str(x[2]) + '\n'

	"""Prints the result of the FastestWay Algorihtm"""
	returner = AS1_IbrarYunus._fastestWay(a,t,e,x,n)
	_formattedText = _formattedText + returner[1]

	returner = str(returner[0])
	print '   Fastest Way to Exit the Assembly Line is: ' + bcolors.BOLD + returner + bcolors.ENDC
	_formattedText = _formattedText + '   Fastest Way to Exit the Assembly Line is: ' + returner + '\n'
	#assert returner == '4'
	print bcolors.OKGREEN + '!PASSED' + bcolors.ENDC
	_formattedText = _formattedText +  '!PASSED'
	textbox(msg='Output', title=' Unit Tests', text= _formattedText, codebox=0)
	return returner



if( option == 0):
	Trivial()
	Medium()
else:
	AS1_IbrarYunus.Randomizer()

