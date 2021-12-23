#Function calls are in the below of the script
#--------------------------------------------------------------------------

#Imports
import networkx as nx
import matplotlib.pyplot as plt
from collections import Counter
from networkx.algorithms import community
from networkx.algorithms.community.quality import performance
from networkx.algorithms.community.quality import coverage
import numpy as np
import random
import math
#---------------------------------------------------------------------------
#1. Generate Scale-Free Network (SFN) = (G)
def create_graph(node):
    G = nx.Graph()
    G = nx.scale_free_graph(node,alpha=0.25, beta=0.7, gamma=0.05)
    G = G.to_undirected()
    return G

def print_stats(G):
    print("Simple stats for: Final Exam - SF Network")
    print("# of nodes: " + str(len(G.nodes())))
    print("# of edges: " + str(len(G.edges())))
    print("Is graph connected? " + str(nx.is_connected(G)))
    print("-" * 30)
#---------------------------------------------------------------------------


#---------------------------------------------------------------------------
# degree_distribution is a function for 2nd and 7th parts

def degree_distribution(degrees, name = "Sub", c = 1,  w = 3):
    if name != "SFN":
        print("For " + "Community_" + str(c) + ", degree distribution: ")

    degreeFrequency= Counter(degrees)
    frequencyCalculations = []
    degL = []
    j = 0
    for i in range(0, len(degrees)):
        x = degreeFrequency[i] / len(degrees)
        if(x != 0.0):
            frequencyCalculations.insert(j, (degreeFrequency[i] / len(degrees)))
            frequencyCalculations[j] = round(frequencyCalculations[j],2)
            degL.insert(j,i)
            print('Degree: %d\'s distribution rate: %.2f' % (degL[j], frequencyCalculations[j]))
            j += 1
    if(len(degL) > 0):
        if name == "SFN":
            plt.title("Degree Distribution of " + name)
            plt.subplot2grid((3,3), (0,0), colspan=1, rowspan=2)
            plt.scatter(degL,frequencyCalculations,marker="o", color='#fcba03')
            plt.xlabel("Degrees")
            plt.xticks(np.arange(min(degL), max(degL)+1, 2.0))
            plt.ylabel("Distribution")
            plt.yticks(np.arange(min(frequencyCalculations),1, 0.1))
        else:
            plt.subplot(w, w, c+1)
            plt.title(name)
            plt.scatter(degL,frequencyCalculations,marker="o", color='#fcba03')
            plt.xlabel("Degrees")
            plt.xticks(np.arange(min(degL), max(degL)+1, 1.0))
            plt.ylabel("Distribution")
            plt.yticks(np.arange(min(frequencyCalculations),1, 0.1))
    else:
        print("Node is the only member of community.")
    print("-" * 30)
#---------------------------------------------------------------------------
    
#---------------------------------------------------------------------------
#2. Degree Distribution of SFN on Graph (MATPLOT)
        
def calculate_draw_degree_distribution(G):
    degreeList = G.degree()
    nodes,degrees = zip(*degreeList)
    degree_distribution(degrees, "SFN",1,3)
#---------------------------------------------------------------------------   

#---------------------------------------------------------------------------
#3. Find Communities In the Network & 4. Number of Communities Printed
    
def find_community(G):
    communities = list(community.greedy_modularity_communities(G))
    #communities = list(community.asyn_lpa_communities(G))
    com = []
    com_names = []
    for i in range(0, len(communities)):
        com.append(communities[i])
        com_names.append("Community_" + str(i))

    com_dict = dict(zip(com_names, com))
    print("The number of communities is " + str(len(com)))
    print("-" * 30)
#---------------------------------------------------------------------------
    
#---------------------------------------------------------------------------
    #5. Details of ALL the communities 

    print("COMMUNITY NAME\tCOMMUNITY SIZE\tCOMMUNITY MEMBERS")
    for i in range(0, len(com_dict)):
        comm_name = "Community_" + str(i)
        print(comm_name + "\t" + str(len(com_dict[comm_name])) + "\t\t" + str(com_dict[comm_name]))
    print("-" * 30)
    return communities, com, com_dict
#---------------------------------------------------------------------------

#---------------------------------------------------------------------------
#6. Color Codes of Each Community on Printed Network (MATPLOT)


def color_code(G, com):
    color_map = []
    for i in range(0, len(G.nodes())):
        color_map.append("#"+"%06x" % 0xFFFFFF)
        
    for i in range (0, len(com)):
        com_lis = list(com[i])
        color = "%06x" % random.randint(0, 0xFFFFFF)
        for j in range(0, len(com_lis)):
            color_map[com_lis[j]] = str("#"+color)
    return color_map

def draw_network(G, color_map):
    plt.subplot2grid((3,3), (0,1), colspan=2, rowspan=3)
    nx.draw_circular(G, node_color=color_map, with_labels=True)

def draw_sub_graph(Gs, c, w, color_map):
    
    plt.subplot(w, w, c+1)
    plt.title("Community_" + str(c))

    col_map = []
    node_list = list(Gs.nodes())
    
    for i in range(0, len(Gs.nodes())):
        col_map.append(color_map[node_list[i]])
    nx.draw(Gs, node_color = col_map[0], with_labels=True)
#---------------------------------------------------------------------------

#---------------------------------------------------------------------------
#7. Degree Distribution of Communities on Graphs (MATPLOT)

def calculate_degree_subnetwork(comm, G, comm_name, size):
    subnetwork_degrees = []
    degreeList = G.degree()
    nodes,degrees = zip(*degreeList)
    for i in range(0, len(comm)):
        if comm[i] in nodes:
            subnetwork_degrees.append(degrees[comm[i]])

def subnetwork_graph(com_dict, G, color_map):
    size = len(com_dict)
    w = math.sqrt(size)
    w = math.ceil(w)
    plt.figure(num = "Communities Degree Distribution")
    for i in range(0, size):
        comm_name = "Community_" + str(i)
        #comm_name size: len(com_dict[comm_name]) nodes: com_dict[comm_name])
        comm = list(com_dict[comm_name])
        
        subnetwork_degrees = []
        degreeList = G.degree()
        nodes,degrees = zip(*degreeList)
        for j in range(0, len(comm)):
            if comm[j] in nodes:
                subnetwork_degrees.append(degrees[comm[j]])
        title = "Community_" + str(i)
        degree_distribution(subnetwork_degrees, title, i, w)

    sub_networks = []
    plt.figure(num = "Communities")    
    for i in range(0, size):
        comm_name = "Community_" + str(i)
        #comm_name size: len(com_dict[comm_name]) nodes: com_dict[comm_name])
        comm = list(com_dict[comm_name])
        #-- ASSIGN TO NEW SUBNETWORK
        Gs = G.subgraph(comm)
        sub_networks.append(Gs)
        draw_sub_graph(Gs, i, w, color_map)
    return sub_networks
#---------------------------------------------------------------------------

#8. Interpretion & comments

from networkx.algorithms.assortativity.correlation import degree_assortativity_coefficient

def interpret(sub_networks, community_nodes, G):
    G2 = nx.Graph(G)
    perf = performance(G2, community_nodes)
    cov = coverage(G2, community_nodes)
    r=nx.degree_pearson_correlation_coefficient(G2)

    print("Correlation: %3.1f"%r)
    print("Coverage: " + str(cov))
    print("Performance: " + str(perf))
    print("-" * 30)

def comments():
        
    print("This part is an example of the 100 nodes Scale Free Network algorithm." +
    " This section is commented during the delivery of the code, and this part will be included in example Log.txt." +
    " I ran a 100 nodes SFN and the result of correlation as above." +
    " During this tests results are Correlation:~-0.5" +
    " According to these results & degree distributions" +
    " Since the correlation is negative," +
    " this situation has resulted in the connection of high degree individuals to low degree nodes rather than connecting with each other." +
    " If I say in a more social language, the first nodes joining the network want to gather small connections and create communities." +
    " In this way, they tend to create a hub both on the general network and on their own networks." +
    " It is also possible to see this in the graphics I created." +
    " The number of nodes that have too many connections in the network I have created can be counted by fingers within communities." +
    " It is also seen that there is a hierarchy among the communities. While some communities are very crowded, some communities are quite small." +
    " I liken this very much to the grouping of friends mentioned in the lesson. Some networks have adopted a more social behavior than others." 
    " In short, communities are developed by a bottom-up approach as I can review on graphs and values in the Log.txt")
#---------------------------------------------------------------------------
#### FUNCTION CALLS ####

#Number of Nodes
node = 100

print("Number of Nodes is: " + str(node))

#Scale free Network
G = create_graph(node)
print_stats(G)
# SFN Degree dist.
calculate_draw_degree_distribution(G)
# Community Detection
communities, community_nodes, com_dict = find_community(G)
#Color code by community
color_map = color_code(G, communities)
#Draw  network
draw_network(G, color_map)
#Draw subnetworks and degree dist.
sub_networks = subnetwork_graph(com_dict, G, color_map)

#interpretion
interpret(sub_networks, community_nodes, G)

#interpretion comments on an experiment with 100 nodes
#comments()

plt.subplots_adjust(left=0, bottom=0, right=0.9, top=0.9, wspace=0.2, hspace=0.5)
plt.show()
print('DONE')
#---------------------------------------------------------------------------
