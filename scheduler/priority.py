from scheduler import *
import functools
class Priority(Scheduler):
	def pushNext(self):
		# remove blank instruction
		if len(self.CPU_queue)>0:
			top = self.CPU_queue[0]
			if len(top.instructions)==0:
				top.inProcess = False
				self.removeFromCPU(top)
				self.completeProcess(top)
		if len(self.IN_queue)>0:
			top = self.IN_queue[0]
			if len(top.instructions)==0:
				top.inProcess = False
				self.removeFromIN(top)
				self.completeProcess(top)
		if len(self.OP_queue)>0:
			top = self.OP_queue[0]
			if len(top.instructions)==0:
				top.inProcess = False
				self.removeFromOP(top)
				self.completeProcess(top)
		# change queue
		if len(self.CPU_queue)>0:
			top = self.CPU_queue[0]
			ins = top.instructions[0]
			if(ins[0]=='I'):
				top.inProcess = False
				self.removeFromCPU(top)
				self.addToIN(top)
			if(ins[0]=='O'):
				top.inProcess = False
				self.removeFromCPU(top)
				self.addToOP(top)
		if len(self.IN_queue)>0:
			top = self.IN_queue[0]
			ins = top.instructions[0]
			if(ins[0]=='C'):
				top.inProcess = False
				self.removeFromIN(top)
				self.addToCPU(top)
			if(ins[0]=='O'):
				top.inProcess = False
				self.removeFromIN(top)
				self.addToOP(top)
		if len(self.OP_queue)>0:
			top = self.OP_queue[0]
			ins = top.instructions[0]
			if(ins[0]=='C'):
				top.inProcess = False
				self.removeFromOP(top)
				self.addToCPU(top)
			if(ins[0]=='I'):
				top.inProcess = False
				self.removeFromOP(top)
				self.addToIN(top)
	def tickCPU(self):
		if len(self.CPU_queue)>0:
			top = self.CPU_queue[0]
			ins = top.instructions[0]
			if(ins[0]=='C'):
				if top.responseTime==-1:
					top.responseTime = self.timer - top.arrivalTime
				ins[1]-=1
				top.inProcess = True
				if(ins[1]==0):
					top.instructions.pop(0)
				else:
					top.instructions[0]=ins
					top.remainingTime -= 1
			
	def tickIN(self):
		if len(self.IN_queue)>0:
			top = self.IN_queue[0]
			ins = top.instructions[0]
			if(ins[0]=='I'):
				ins[1]-=1
				top.inProcess = True
				if(ins[1]==0):
					top.instructions.pop(0)
				else:
					top.instructions[0]=ins
					top.remainingTime -= 1
	def tickOP(self):
		if len(self.OP_queue)>0:
			top = self.OP_queue[0]
			ins = top.instructions[0]
			if(ins[0]=='O'):
				ins[1]-=1
				top.inProcess = True
				if(ins[1]==0):
					top.instructions.pop(0)
				else:
					top.instructions[0]=ins
					top.remainingTime -= 1

def customSortNP(arr):
	n = len(arr)
	for i in range(n):
		for j in range(0, n-i-1):
			if arr[j].inProcess != True:
				if arr[j].priority > arr[j+1].priority:
					arr[j], arr[j+1] = arr[j+1], arr[j]
	return arr
def customSortP(arr):
	n = len(arr)
	for i in range(n):
		for j in range(0, n-i-1):
			if arr[j].priority > arr[j+1].priority:
				arr[j], arr[j+1] = arr[j+1], arr[j]
	return arr

class PriorityNP(Priority):
	def schedule(self):
		# sort acc to arrival time
		while True:
			if len(self.processes) == 0 and len(self.CPU_queue)==0 and len(self.IN_queue)==0 and len(self.OP_queue)==0:
				break
			#print(self.timer)
			self.startProcess()
			self.pushNext()
			self.CPU_queue = customSortNP(self.CPU_queue)
			self.tickCPU()
			self.tickIN()
			self.tickOP()
			self.tick()
class PriorityP(Priority):
	def schedule(self):
		# sort acc to arrival time
		while True:
			if len(self.processes) == 0 and len(self.CPU_queue)==0 and len(self.IN_queue)==0 and len(self.OP_queue)==0:
				break
			#print(self.timer)
			self.startProcess()
			self.pushNext()
			self.CPU_queue = customSortP(self.CPU_queue)
			self.tickCPU()
			self.tickIN()
			self.tickOP()
			self.tick()

