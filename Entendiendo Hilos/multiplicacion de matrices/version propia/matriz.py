import numpy as np

n=int(input("ingrese filas y columnas: ")) 
#m=int(input("ingrese columnas"))
#creo la matriz A con numeros entero entre 0 y 100 con tamaño nxn
matrizA = np.random.randint(0,100,(n,n)) #numerominimo,numeromaximo,tamañomatriz
#imprimo la matriz A
print("matriz A")
for i in range(n):
    print (matrizA[i])

#creo la matriz B con numeros entero entre 0 y 100 con tamaño nxn
matrizB = np.random.randint(0,100,(n,n))
#imprimo la matriz B
print("matriz B")
for i in range(n):
    print (matrizB[i])

#inicializo matriz resultado llena de 0
matrizResultado = np.zeros((n,n))

#multiplico A con B
for i in range(n): #fila matrizA
    for j in range(n): #columna matrizB
        for k in range(n): #noc
            matrizResultado[i][j] += matrizA[i][k] * matrizB[k][j]

#ver matrizResultado
print("resultado")
for i in range(n):
    R=[]
    for j in range(n):
        R.append(matrizResultado[i][j])
    print(R)