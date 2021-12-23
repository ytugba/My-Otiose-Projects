from __future__ import division
import matplotlib.pyplot as plt
import networkx as nx
import random, warnings, math, numpy
from collections import Counter

#Generates Adjacency Matrix For Network
def GenerateMatrix():
    #CHANGE HERE IF YOU WANT A SPECIFIC NUMBER OF NODES AND EDGES
    #n = 100
    n = random.randint(1, 100)
    randMatrix = [[random.randint(0, 1) for i in range(n)] for j in range(n)]    
    for i in range(n):
        randMatrix[i][i] = 0       
    for i in range(n):
        for j in range(n):
            randMatrix[j][i] = randMatrix[i][j]          
    adjacencyMatrix = numpy.matrix(randMatrix)
    
    return adjacencyMatrix

#Generates Graph From Numpy Adjacency Array Matrix
def CreateGraph():
    adjacencyMatrix = GenerateMatrix()
    
    G = nx.Graph()
    G = nx.from_numpy_matrix(adjacencyMatrix)
    print("------------------------------------------------------------")
    print("Number of nodes: " + str(len(G)))
    print("Number of edges: " + str(G.number_of_edges()))
    print("------------------------------------------------------------")    
    return G

#Draws Graph Is Created
def DrawGraph(G):
    plt.figure(num='Network with ' + str(len(G)) + " nodes")
    plt.axis('off')
    nx.draw_networkx(G, node_color = '#fcba03', font_size = '8')
    
#Calculates and Draws the Degree Distribution of the Network Created
def DegreeDistribution(G):

    print("------------------------------------------------------------")
    degreeList = G.degree()
    print("[node , #degree]:")
    print(str(degreeList))
    nodes,degrees = zip(*degreeList)
    print("------------------------------------------------------------")

    print("------------------------------------------------------------")
    print("Degree Distributions:")
    degreeFrequency= Counter(degrees)
    frequencyCalculations = []
    degL = []
    j = 0
    for i in range(0, len(degrees)):
        x = degreeFrequency[i] / len(degrees)
        if(x != 0.0):
            frequencyCalculations.insert(j, (degreeFrequency[i] / len(degrees)))
            degL.insert(j,i)
            print('%d - %.2f' % (degL[j], frequencyCalculations[j]))
            j += 1
    print("------------------------------------------------------------")

    plt.figure(num='Degree Distribution')
    plt.xlabel('Degrees')
    plt.ylabel('Distribution')
    plt.yticks(numpy.arange(min(frequencyCalculations), max(frequencyCalculations)+1, 0.01))
    plt.xticks(numpy.arange(min(degL), max(degL)+1, 1.0))
    plt.scatter(degL,frequencyCalculations,marker="o", color='#fcba03')

#Runs Plotted Windows
def DisplayWindows():
    plt.show()

#Function Calls
if __name__ == '__main__':
    warnings.filterwarnings("ignore")
    GenerateMatrix()
    G = CreateGraph()
    DrawGraph(G)
    DegreeDistribution(G)
    DisplayWindows()
