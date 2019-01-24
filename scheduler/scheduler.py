from process import *
class Scheduler:
	def __init__(self, processes):
		self.timer = 0
		self.processes = processes
		self.CPU_queue = list()
		self.IN_queue = list()
		self.OP_queue = list()
		self.completed = list()
		#self.state = "new"
		self.log = list()
		self.processes = sorted(processes, key=lambda process: process.arrivalTime)
		self.schedule()
	def printInfo(self):
		print("Process Id\tBurst Time\t Response Time\t Waiting Time\t TurnAroundTime")
		for p in self.completed:
			print(p.pid,p.burstTime,p.responseTime,p.waitingTime,p.turnAroundTime,sep='\t\t')
	def addToCPU(self,process):
		self.log.append("Moved process %d to CPU_queue at time %d" %(process.pid, self.timer))
		self.CPU_queue.append(process)
	def addToIN(self,process):
		self.log.append("Moved process %d to IN_queue at time %d" %(process.pid, self.timer))
		self.IN_queue.append(process)
	def addToOP(self,process):
		self.log.append("Moved process %d to OP_queue at time %d" %(process.pid, self.timer))
		self.OP_queue.append(process)
	def removeFromCPU(self,process):
		self.CPU_queue.remove(process)
		self.log.append("Process %d removed from CPU_queue at %d" %(process.pid, self.timer))
	def removeFromIN(self,process):
		self.IN_queue.remove(process)
		self.log.append("Process %d removed from IN_queue at %d" %(process.pid, self.timer))
	def removeFromOP(self,process):
		self.OP_queue.remove(process)
		self.log.append("Process %d removed from OP_queue at %d" %(process.pid, self.timer))
	def completeProcess(self,process):
		self.log.append("Process %d completed at %d" %(process.pid, self.timer))
		process.endTime = self.timer
		process.turnAroundTime = self.timer - process.arrivalTime
		process.waitingTime = process.turnAroundTime - process.burstTime
		self.completed.append(process)
	def startProcess(self):
		while len(self.processes)>0 and self.timer == self.processes[0].arrivalTime:
			top = self.processes.pop(0)
			# top.state = "ready"
			self.addToCPU(top)
	def tick(self):
		self.timer+=1
			
class FCFS(Scheduler):
	def schedule(self):
		# sort acc to arrival time
		while True:
			if len(self.processes) == 0 and len(self.CPU_queue)==0 and len(self.IN_queue)==0 and len(self.OP_queue)==0:
				break
			#print(self.timer)
			self.startProcess()
			self.pushNext()
			self.tickCPU()
			self.tickIN()
			self.tickOP()
			self.tick()
	def pushNext(self):
		# remove blank instruction
		if len(self.CPU_queue)>0:
			top = self.CPU_queue[0]
			if len(top.instructions)==0:
				self.removeFromCPU(top)
				self.completeProcess(top)
		if len(self.IN_queue)>0:
			top = self.IN_queue[0]
			if len(top.instructions)==0:
				self.removeFromIN(top)
				self.completeProcess(top)
		if len(self.OP_queue)>0:
			top = self.OP_queue[0]
			if len(top.instructions)==0:
				self.removeFromOP(top)
				self.completeProcess(top)
		# change queue
		if len(self.CPU_queue)>0:
			top = self.CPU_queue[0]
			ins = top.instructions[0]
			if(ins[0]=='I'):
				self.removeFromCPU(top)
				self.addToIN(top)
			if(ins[0]=='O'):
				self.removeFromCPU(top)
				self.addToOP(top)
		if len(self.IN_queue)>0:
			top = self.IN_queue[0]
			ins = top.instructions[0]
			if(ins[0]=='C'):
				self.removeFromIN(top)
				self.addToCPU(top)
			if(ins[0]=='O'):
				self.removeFromIN(top)
				self.addToOP(top)
		if len(self.OP_queue)>0:
			top = self.OP_queue[0]
			ins = top.instructions[0]
			if(ins[0]=='C'):
				self.removeFromOP(top)
				self.addToCPU(top)
			if(ins[0]=='I'):
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
				if(ins[1]==0):
					top.instructions.pop(0)
				else:
					top.instructions[0]=ins
			
	def tickIN(self):
		if len(self.IN_queue)>0:
			top = self.IN_queue[0]
			ins = top.instructions[0]
			if(ins[0]=='C'):
				self.removeFromIN(top)
				self.addToCPU(top)
			elif(ins[0]=='I'):
				ins[1]-=1
				if(ins[1]==0):
					top.instructions.pop(0)
				else:
					top.instructions[0]=ins
	def tickOP(self):
		if len(self.OP_queue)>0:
			top = self.OP_queue[0]
			ins = top.instructions[0]
			if(ins[0]=='O'):
				ins[1]-=1
				if(ins[1]==0):
					top.instructions.pop(0)
				else:
					top.instructions[0]=ins
