from process import *
from scheduler import *

if __name__ == "__main__":
	#input
	processes = list()
	N = int(input())
	for i in range(N):
		processes.append(Process(input()))
		
	p = processes
	schFCFS = FCFS(p)
	for entry in schFCFS.log:
		print(entry)
	print('')
	schFCFS.printInfo()
