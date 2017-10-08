#!/usr/bin/python3

import threading

class multiThread(threading.Thread):
   def __init__(self, threadID, name, counter, func_name):
      threading.Thread.__init__(self)
      self.threadID = threadID
      self.name = name
      self.counter = counter
      self.func_name = func_name
   def run(self):
      print ("Starting " + self.name)
      if(self.func_name=="Fibonacci"):
        for i in range(0, self.counter):
            print(fibo(i))
      if(self.func_name=="Pattern"):
          pattern(self.counter)   
      print ("Exiting " + self.name)

def fibo(counter):
    if counter<=1:
        return counter
    else:
        return (fibo(counter-1)+ fibo(counter-2))

def pattern(n):
    for i in range(0,n):
        print("******")

# Create 
thread1 = multiThread(1, "FiboThread", 17, "Fibonacci")
thread2 = multiThread(2, "PatThread", 5, "Pattern")

# Execute
thread1.start()
thread2.start()
thread1.join()
thread2.join()
print ("Exiting Main Thread")