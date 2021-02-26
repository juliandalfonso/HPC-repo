#importamos la libreria tiempo para calcular el tiempo de cpu de solo la matriz
import time

#ingresamos el tamano N a generar de la matriz NxN
m = int(input("Enter the number N to generate NxN matrix : "))

X = [[1]*m]*m
Y = [[1]*m]*m
 
def mult(X, Y):
   result = [[0]*m]
   for z in range(len(Y[0])):
       for k in range(len(Y)):
           result[0][z] += X[0] * Y[k][z]
   # print(result)
start = time.perf_counter()
for i in range(len(X[0])):
   mult(X[i], Y)
end = time.perf_counter()
 
print(f"Time taken to complete mult(){m}x{m} without threading: {round(end - start, 5)} seconds(s)")