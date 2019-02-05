from scheduler import *
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
