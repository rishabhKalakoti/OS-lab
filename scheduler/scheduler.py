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
		self.processes = sorted(self.processes, key=lambda process: process.arrivalTime)
		self.schedule()
	def printInfo(self):
		print("Process Id\tBurst Time\tResponse Time\tWaiting Time\tTurnAroundTime")
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
			

