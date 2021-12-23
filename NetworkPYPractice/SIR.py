"""
Download ndlib: https://ndlib.readthedocs.io/en/latest/installing.html
Download igraph https://igraph.org/python/ (required for ndlib)
Other libraries can be installed via command prompt: pip install x
Change constants in the code to change network structure
"""

import networkx as nx
import ndlib.models.epidemics as ep
import ndlib.models.ModelConfig as mc
import matplotlib.pyplot as plt
import numpy as np

import warnings
warnings.filterwarnings("ignore")

#ADDED FOR VIDEO
input = input()

#CONSTANTS CHANGE HERE FOR UPDATES -----------------------------------------
node = 50 #initial S
inf = 0.05 #infected people
rec = 0.02 #recovery probability
number_of_iterations = 20
delay = 0.1 #plot graph frames

#init
i = 0
iterations = []
infected = []
recovered = []
susceptible = []
infectedseq = []
recoveredseq = []
susceptibleseq = []
graphseq = []
S = []
I = []
R = []
fig = plt.figure(num='Scale Free Network SIR Model', figsize=(8,5))
plt.get_current_fig_manager().window.wm_geometry("+0+0")
#FUNCTIONS ------------------------------------------------------------------

def print_graph_stats(title, g):
    print("Simple stats for: " + title)
    print("# of nodes: " + str(len(g.nodes())))
    print("# of edges: " + str(len(g.edges())))
    print("Is graph connected? " + str(nx.is_connected(g)))

def initialize_parameters(model, infection = 0.05, recovery = 0.001, fraction = 0.05):
    #configuration
    cfg = mc.Configuration()
    #infection
    cfg.add_model_parameter('beta', infection)
    #recovery
    cfg.add_model_parameter('gamma', recovery)
    #probability
    cfg.add_model_parameter("fraction_infected", fraction)
    
    model.set_initial_status(cfg)
    return model

#Init graph
def create_graph(node = 100):
    g = nx.Graph()
    g = nx.scale_free_graph(node)
    g = g.to_undirected()
    print_graph_stats("Scale-Free Network", g)
    return g

def drawSIRGraph(susceptible, infected, recovered, iternum):

    plt.rcParams['axes.facecolor'] = 'beige'
    plt.title("SIR Model of Scale Free Network")

    size = len(susceptible[iternum])+ len(infected[iternum])+ len(recovered[iternum])

    S.append(len(susceptible[iternum])/size)
    I.append(len(infected[iternum])/size)
    R.append(len(recovered[iternum])/size)
    
    plt.plot(S, label = 'S', color = 'chartreuse')
    plt.plot(I, label = 'I', color = 'tomato')
    plt.plot(R, label = 'R', color = 'yellow')
    
    plt.xlabel('iterations')
    plt.xticks(np.arange(1, iternum+1, 1))
    
    plt.ylabel('# of nodes normalized')
    plt.yticks(np.arange(0, size/size, 0.05))
    
    plt.legend(loc="upper right")

#To update network colors
def create_color_map(infected, recovered):
    for node in G:
        if node in infected:
            color_map.append('tomato')
        elif node in recovered: 
            color_map.append('yellow')
        else:
            color_map.append('chartreuse')
    return color_map

#MAIN CODE -------------------------------------------------------------
G = create_graph(node)

model = ep.SIRModel(G)
model = initialize_parameters(model, float(inf), float(rec))

#Initial healty nodes
susceptible = list(G.nodes)

while(i <= int(number_of_iterations)):

    iteration = model.iteration()
    color_map = []

    print(iteration)
    
    #ex. ref. {'iteration': 1, 'status': {99: 1}, 'node_count': {0: 94, 1: 6, 2: 0}, 'status_delta': {0: -1, 1: 1, 2: 0}}
    #print(iteration["iteration"]) iteration counter 
    #print(iteration["status"]) dict new infected
    #print(iteration["node_count"]) dict current S I R 
    #print(iteration["status_delta"]) dict change
    
    print(str(iteration["iteration"]) + ": ")
    if(len(iteration["status"]) <= 0):
        print("No infection or recovery in this phase.")
        
    else:
        for x in iteration["status"]:
            if(iteration["status"][x] == 1):
                print("Node: " + str(x) + " is infected.")
                infected.append(x)
                susceptible.remove(x)
            elif(iteration["status"][x] == 2):
                print("Node: " + str(x) + " is recovered.")
                infected.remove(x)
                recovered.append(x)
                
        #iterate graph phase
        #print(infected)
                
    graphseq.append(color_map)
    infectedseq.append(infected)
    recoveredseq.append(recovered)
    susceptibleseq.append(susceptible)
    iterations.append(iteration)
    
    color_map = create_color_map(infected, recovered)

    plt.subplot2grid((3,3), (0,0), colspan=1, rowspan=2)
    drawSIRGraph(susceptibleseq, infectedseq, recoveredseq, i)
    
    plt.subplot2grid((3,3), (0,1), colspan=2, rowspan=3)
    nx.draw_circular(G, node_color=color_map, with_labels=True)
    
    plt.tight_layout()

    plt.pause(delay)
    print('*' * 30) 
    i += 1
    #EOF While

print("Total infected nodes:")
infected.sort()
print(infected)

print("Total recovered nodes:")
recovered.sort()
print(recovered)

plt.show()
