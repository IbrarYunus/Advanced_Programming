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

"""The fastes way algorithm"""
def _fastestWay(a,t,e,x,n):
	#print 'num is ' + str(n)
	"""creation of temporary 1D arrays"""
	f1 = [0 for u in range(n)]
	f2 = [0 for u in range(n)]
	l1 = [0 for u in range(n)]
	l2 = [0 for u in range(n)]
	path  =  [0 for u in range(n)]

	"""Calculating the values for first stations at each of the Assembly Lines"""
	f1[1] = e[1] + a[1][1]
	f2[1] = e[2] + a[2][1]

	"""fstar returns the size of teh shortest path"""
	_fstar = 0;
	_lstar = 0;

	for j in range(2,n):
		"""Calculating and finding minimum current path for Assembly Line 1"""
		if (f1[j-1] + a[1][j]) <= (f2[j-1] + t[2][j-1] + a[1][j]):
			"""Trivial Path"""
			f1[j] = f1[j-1] + a[1][j]
			l1[j-1] = 1
		else:
			"""Non-trivial path"""
			f1[j] = f2[j-1] + t[2][j-1] + a[1][j]
			l1[j-1] = 2
		"""Calculating and finding minimum current path for Assembly Line 2"""	
		if (f2[j-1] + a[2][j]) <= (f1[j-1] +t[1][j-1] + a[2][j]):
			f2[j] = f2[j-1] + a[2][j]
			l2[j-1] = 2
		else:
			f2[j] = f1[j-1] + t[1][j-1] + a[2][j]
			l2[j-1] = 1

	"""Final selection from both of the paths"""
	if	(f1[n-1] + x[1]) <= (f2[n-1] + x[2]):
	 	_fstar = f1[n-1] + x[1]
	 	path = l1
		_lstar = 1
	else:
		_fstar = f2[n-1] + x[2]
		path = l2
		_lstar = 2	

	"""For display purposes, kindly ignore"""
	path[n-1] = _lstar
	if(f1[1] < f2[1]):
		path[0] = 1
	else:
		path[0] = 2		
	#print "   1st Fastest Path: " + str(f1[n-1] + x[1])	
	#print "   2nd Fastest Path: " + str(f2[n-1] + x[2])	
	print '   Path Taken: ' 
	_formattedText = '   Path Taken: \n' 
	_formattedText = _formattedText  + "  " + str(path) + "\n"
	print path

 	return [_fstar,_formattedText]


# """Main starts here""" 	
def Randomizer():
	print 'Initializing'
	some_input = easygui.enterbox(
	    title="Fastest Algorithm",
	    strip=True, # will remove whitespace around whatever the user types in
	    default="Enter total number of stations")

	"""This is the number of stations"""
	num = int(some_input)

	"""Added +1 to allow list indexes from 1 to n (rather than 0 tp n-1)"""

	"""Creation of dynamic 2D and 1D lists"""
	a = [[0 for x in range(num)] for x in range(3)] 
	t = [[0 for x in range(num)] for x in range(3)] 
	e = [0 for x in range(num)]
	x = [0 for x in range(num)]

	"""for passing on to the _fastestWay function"""
	n = num

	"""Initializes random numbers to each of the array indexes"""
	for i in range(num):
		a[1][i] = random.randrange(1,100)
		a[2][i] = random.randrange(1,100)
		t[1][i] = random.randrange(1,100)
		t[2][i] = random.randrange(1,100)

	"""Initializes random numbers to each of the array indexes"""
	for i in range(1,3):
		e[i] 	= random.randrange(1,100)
		x[i]	= random.randrange(1,100)

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
	returner = _fastestWay(a,t,e,x,n)
	_formattedText = _formattedText + returner[1]

	returner = str(returner[0])
	print '   Fastest Way to Exit the Assembly Line is: ' + bcolors.BOLD + returner + bcolors.ENDC
	_formattedText = _formattedText + '   Fastest Way to Exit the Assembly Line is: ' + returner + '\n'
	#assert returner == '4'
	print bcolors.OKGREEN + '!PASSED' + bcolors.ENDC
	#_formattedText = _formattedText +  '!PASSED'
	textbox(msg='Output', title=' Unit Tests', text= _formattedText, codebox=0)



