class Process:
	# name, priority, arrival time, list of burst time & I/O time
	def __init__(self,name,priority,AT,instructions):
		self.name = name
		self.priority = priority 
		self.state = "ready"
		self.arrivalTime = AT
		self.instructions = instructions
		self.waitingTime = 0
		self.turnAroundTime = 0
		self.responseTime = 0
	def invertPriority(self, other):
		self.priority, other.priority = other.priority, self.priority
	def increasePriority(self):
		self.priority -= 1
	def decreasePriority(self):
		self.priority -= 1
