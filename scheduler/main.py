from process import *
from scheduler import *
from FCFS import *
from SJF import *
from priority import *
from roundRobin import *
if __name__ == "__main__":
	#input
	p1 = list()
	p2 = list()
	p3 = list()
	p4 = list()
	p5 = list()
	N = int(input())
	for i in range(N):
		x = input()
		p1.append(Process(x))
		p2.append(Process(x))
		p3.append(Process(x))
		p4.append(Process(x))
		p5.append(Process(x))
	print("First Come First Serve")
	schFCFS = FCFS(p1)
	"""
	for entry in schFCFS.log:
		print(entry)
	print('')
	"""
	schFCFS.printInfo()
	print("")
	
	print("Shortest Job First")
	schSJF = SJF(p2)
	"""
	for entry in schSJF.log:
		print(entry)
	print('')
	"""
	schSJF.printInfo()
	print("")
	
	print("Priority Scheduling: Preemptive")
	schPP = PriorityP(p3)
	"""
	for entry in schPP.log:
		print(entry)
	print('')
	"""
	schPP.printInfo()
	print("")
	
	print("Priority Scheduling: Non Preemptive")
	schPNP = PriorityNP(p4)
	"""
	for entry in schPNP.log:
		print(entry)
	print('')
	"""
	schPNP.printInfo()
	print("")
	
	print("Round Robin")
	schRR = RoundRobin(p5)
	"""
	for entry in schRR.log:
		print(entry)
	print('')
	"""
	schRR.printInfo()
	print("")
	
