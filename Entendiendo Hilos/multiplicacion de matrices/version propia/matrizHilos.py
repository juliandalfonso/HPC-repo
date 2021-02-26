#librerias
from threading import Thread
import numpy as np
import math
import threading
import time

matrizA = []
matrizB = []
matrizResultado = []

#funciones
def entradas():    
    global n
    global numeroHilos
    n=int(input("ingrese filas y columnas: ")) 
    numeroHilos = int(input("ingrese el numero de hilos: "))

def inicializarMatrices():
    global matrizA
    global matrizB
    global matrizResultado

    #creo la matriz A con numeros entero entre 0 y 100 con tamaño nxn
    matrizA = np.random.randint(0,100,(n,n)) #numerominimo,numeromaximo,tamañomatriz
    matrizA = matrizA.astype(int)
    #imprimo la matriz A
    print("matriz A")
    for i in range(n):
        print (matrizA[i])

    #creo la matriz B con numeros entero entre 0 y 100 con tamaño nxn
    matrizB = np.random.randint(0,100,(n,n))
    matrizB = matrizB.astype(int)
    #imprimo la matriz B
    print("matriz B")
    for i in range(n):
        print (matrizB[i])

    #inicializo matriz resultado llena de 0
    matrizResultado = np.zeros((n,n))
    matrizResultado = matrizResultado.astype(int)

def multiplicacionMatriz(start,end):
    #multiplico A con B
    for i in range(start,end): #fila matrizA
        for j in range(n): #columna matrizB
            for k in range(n): #noc
                matrizResultado[i][j] += matrizA[i][k] * matrizB[k][j]

def hilos():
    global numeroHilos
    threadHandle = []

    for j in range (numeroHilos):
        tiempo = Thread(target=multiplicacionMatriz, args=(int((n/numeroHilos) * j),int((n/numeroHilos) * (j+1))))
        threadHandle.append(tiempo)
        tiempo.start()
    for j in range (numeroHilos):
        threadHandle[j].join()

def resultado():
    #ver matrizResultado
    print("resultado")
    for i in range(n):
        R=[]
        for j in range(n):
            R.append(matrizResultado[i][j])
        print(R)

if __name__ == "__main__":
    entradas()
    inicializarMatrices()

    start_time = time.time()
    hilos()
    end_time = time.time()
    print("Time taken to multiply two matrices in parallel comes out to be : " + str(end_time - start_time))
    resultado()