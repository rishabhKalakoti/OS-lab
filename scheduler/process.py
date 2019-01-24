class Process:
	# name, priority, arrival time, list of burst time & I/O time
	def __init__(self, data):
		# pre-processing
		data=data.split(" ")
		while '' in data:
			data.remove('')
		# pid,AT,priority,share,instructions
		self.pid = int(data[0])
		self.arrivalTime = int(data[1])
		self.priority = int(data[2])
		self.share=int(data[3])
		self.state = "start"
		self.waitingTime = 0
		self.turnAroundTime = 0
		self.responseTime = -1
		self.endTime = 0
		self.instructions = list()
		i=4
		while data[i]!='-1':
			self.instructions.append([data[i],int(data[i+1])])
			i+=2
		# print(self.instructions)
	def invertPriority(self, other):
		self.priority, other.priority = other.priority, self.priority
	def increasePriority(self):
		self.priority -= 1
	def decreasePriority(self):
		self.priority += 1
