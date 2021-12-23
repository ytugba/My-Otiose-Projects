#### - modificate to run different cases

import random, numpy,math
from random import randint
from collections import Counter
import matplotlib.pyplot as plt
n = 10 #small world nodes ####
new_nodes = 1000 - n #incoming nodes ####
e = 0 #initial edge

def degree_distribution(adj):   
    degrees = []
    for i in range(len(adj)):
        degree = 0
        for j in range(len(adj)):
            if(adj[i][j] == 1):
                degree += 1
        #print(str(i) + ": " + str(degree))
        degrees.append(degree) 
    degreeFrequency= Counter(degrees)
    frequencyCalculations = []
    degL = []
    j = 0
    for i in range(0, len(degrees)):
        x = degreeFrequency[i] / len(degrees)
        if(x != 0.0):
            frequencyCalculations.insert(j, (degreeFrequency[i] / len(degrees)))
            degL.insert(j,i)
            #print('%d - %.2f' % (degL[j], frequencyCalculations[j]))
            j += 1
    print("------------------------------------------------------------")
            
    plt.figure(num='Degree Distribution')
    plt.xlabel('Degrees')
    plt.ylabel('Distribution')
    plt.yticks(numpy.arange(min(frequencyCalculations), max(frequencyCalculations)+1, 0.01))
    plt.xticks(numpy.arange(min(degL), max(degL)+1, 1.0))
    plt.scatter(degL,frequencyCalculations,marker="o", color='#fcba03')
    plt.show()


def adjacent(adj,j):
    include = []
    for i in range(len(adj[j])):
        if(adj[j][i] == 1):
            include.append(i)
    return len(include)

def adjMatrix():
    global e
    adj = [[0 for i in range(n)] for j in range(n)]
    for i in range(n):
        adj[i][i] = 0 
    for i in range(n):
        for j in range(i+1, n):
            adj[i][j] = 1
            adj[j][i] = adj[i][j]
            e += 1
    return adj

def create_initial(adj):
    initial = []
    for k in range(n+1):
        initial.append(0)
    adj = [x + [0] for x in adj]
    adj.append(initial)
    return initial,adj


def gamma_calculation(g,x):
    dist_list = [random.paretovariate(g-1) for i in range(x)]
    return dist_list

def preferential():
    global n,e,new_nodes
    adj = adjMatrix()
    dist_list = gamma_calculation(2.2, n+new_nodes) ####
    print(sum(dist_list) / len(dist_list) )
    for node in range(new_nodes):
        initial,adj=create_initial(adj)
        edgeToConnect = randint(0, n)
        
        for j in range(n+1):
            chance = random.random()
            #FOR GAMMA 2.2
            #b = dist_list[j] / e ####
            #FOR 1000 and 10000 ####
            b = adjacent(adj,j) / e
            if b > chance and j != (len(initial)-1):
                    adj[j][(len(initial)-1)] = 1
                    adj[len(initial)-1][j] = adj[j][(len(initial)-1)]
                    e += 1
            else:
                adj[j][(len(initial)-1)] = 0
                adj[len(initial)-1][j] = adj[j][(len(initial)-1)]
        n += 1
    degree_distribution(adj)
    return adj
#ADDITIONAL
import networkx as nx
def display_network(adj):
    adjacencyMatrix = numpy.matrix(adj)
    G = nx.Graph()
    G = nx.from_numpy_matrix(adjacencyMatrix)
    plt.figure(num='Network with ' + str(len(G)) + " nodes")
    plt.axis('off')
    nx.draw_circular(G, node_color = '#fcba03', font_size = '8')
    plt.show()

#CALL
adj= preferential()
#ADDITIONAL
#display_network(adj)
