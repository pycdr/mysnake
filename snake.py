import termpixels as term
from random import randint,choice
import sys
# from getch import getch

class main(term.App):
	def __init__(self):
		super().__init__()
	def on_frame(self):
		self.snake()
		self.screen.update()
	def snake(self):
		out=""
		for x in range(self.screen.h):
			for y in range(self.screen.w):
				if (x,y) in self._snake_pos:
					out+="█"
				#elif (x,y) == self._foodpos:
				#	out+="@"
				else:
					out+="░"
			out+="\n"
		self.screen.print(out,0,0)#print(out)
		self.moveSnake()
		self.screen.update()#self.backend.clear_screen()
	def moveSnake(self,rm=True):
		"""
		1: Up
		2: Down
		3: Left
		4: Right		
		"""
		if rm:
			del self._snake_pos[-1]
		lm = self.checkPos()
		head=self._snake_pos[0]
		if len(lm)==0:
			exit()
		rand = choice(list(lm))
		if rand==1:
			self._snake_pos = [(head[0],head[1]+1)]+self._snake_pos
		elif rand==2:
			self._snake_pos = [(head[0],head[1]-1)]+self._snake_pos
		elif rand==3:
			self._snake_pos = [(head[0]-1,head[1])]+self._snake_pos
		else:
			self._snake_pos = [(head[0]+1,head[1])]+self._snake_pos
		#if head == self._foodpos:
		#	self.moveSnake(rm=False)
		#	self._foodpos=[randint(1,self.screen.h),randint(1,self.screen.w)]
	def checkPos(self):
		l = {1,2,3,4}
		head = self._snake_pos[0]
		nl = [	(head[0],head[1]+1),
			(head[0],head[1]-1),
			(head[0]-1,head[1]),
			(head[0]+1,head[1])]
		for x in range(len(nl)):
			n=x+1
			x=nl[x]
			if not(x[0] < self.screen.h and x[1] < self.screen.w and (not x in self._snake_pos)):
				l.remove(n)
		return l
	def addBlock(self):
		pass
	def on_start(self):
		self._framerate=5
		#self._foodpos=[randint(1,self.screen.h),randint(1,self.screen.w)]
		self._snake_pos=[
			(self.screen.h//2,self.screen.w//2),
			(self.screen.h//2+1,self.screen.w//2),
			(self.screen.h//2+2,self.screen.w//2),
			(self.screen.h//2+2,self.screen.w//2+1),
			(self.screen.h//2+2,self.screen.w//2+2),
			(self.screen.h//2+1,self.screen.w//2+2),
			(self.screen.h//2+1,self.screen.w//2+3)
		]
if __name__ == "__main__":
	app=main()
	app.start()
