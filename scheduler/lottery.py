from process import *
from scheduler import *
import random
class Lottery(Scheduler):
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
		i=0
		while i<len(self.CPU_queue):
			if len(self.CPU_queue[i].instructions)==0:
				p = self.CPU_queue[i]
				self.removeFromCPU(p)
				self.completeProcess(p)
			else:
				i+=1
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
		i=0
		while i<len(self.CPU_queue):
			p = self.CPU_queue[i]
			ins = p.instructions[0]
			if(ins[0]=='I'):
				self.removeFromCPU(p)
				self.addToIN(p)
			elif(ins[0]=='O'):
				self.removeFromCPU(p)
				self.addToOP(p)
			else:
				i+=1
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
		if len(self.CPU_queue)==0:
			return
		tickets = 0
		for i in range(len(self.CPU_queue)):
			tickets += self.CPU_queue[i].share
		ticket = random.randint(1,tickets)
		self.log.append("Ticket gennerated: %d" %ticket)
		i=0
		while True:
			if ticket > self.CPU_queue[i].share:
				ticket -= self.CPU_queue[i].share
				i += 1
			else:
				self.log.append("Ticket allocated to process with pid %d" %self.CPU_queue[i].pid)
				p = self.CPU_queue[i]
				ins = p.instructions[0]
				if(ins[0]=='C'):
					if p.responseTime==-1:
						p.responseTime = self.timer - p.arrivalTime
					ins[1]-=1
					if(ins[1]==0):
						p.instructions.pop(0)
					else:
						p.instructions[0]=ins
				break
			
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
