#importamos la libreria de hilos para hacer el multithread
import threading
import time
 
m = int(input("Enter the number N to generate NxN matrix : "))

X = [[1]*m]*m
Y = [[1]*m]*m
 
def mult(X, Y):
   result = [[0]*m]
   for z in range(len(Y[0])):
       for k in range(len(Y)):
           result[0][z] += X[0] * Y[k][z]
   # print(f" {result}")
 
threads = list()
start = time.perf_counter()
for i in range(len(X[0])):
   x = threading.Thread(target = mult, args=(X[i], Y))
   threads.append(x)
   x.start()
 
for index, thread in enumerate(threads):
   thread.join()
end = time.perf_counter()
 
print(f"Time taken to complete mult() {m}x{m}: {round(end - start, 5)} seconds(s)")