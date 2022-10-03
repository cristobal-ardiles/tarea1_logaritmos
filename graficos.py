from matplotlib import patches
import matplotlib.pyplot as plt
import numpy
import pandas as pd

tiempos_a1 = pd.read_csv("test1.txt")
tiempos_a1["algoritmo"] = 1
tiempos_a2 = pd.read_csv("test2.txt")
tiempos_a2["algoritmo"] = 2

tiempos = pd.concat([tiempos_a1,tiempos_a2])

ax = plt.gca()
ax.set_xscale("log")
ax.set_yscale("log")
plt.scatter(x=tiempos["tamaño"],y=tiempos["tiempo "],c=tiempos["algoritmo"])
plt.title("Tamaño v/s tiempo de ejecución")
plt.xlabel("Tamaño en bytes")
plt.ylabel("Tiempo de ejecución")
plt.savefig("fig1.png")
plt.show()
