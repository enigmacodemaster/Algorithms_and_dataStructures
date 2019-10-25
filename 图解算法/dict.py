# 建立整个无环有向图
graph = {}

graph["start"] = {}
graph["start"]["a"] = 5
graph["start"]["b"] = 2

graph["a"] = {}
graph["a"]["c"] = 4
graph["a"]["d"] = 2

graph["b"] = {}
graph["b"]["a"] = 8
graph["b"]["d"] = 7

graph["c"] = {}
graph["c"]["fin"] = 3
graph["c"]["d"] = 6

graph["d"] = {}
graph["d"]["fin"] = 1

graph["fin"] = {}


# 维护开销的散列表，一开始到终点的开销为无穷大
infinity = float("inf")

costs = {}
costs["a"] = 5
costs["b"] = 2
costs["c"] = infinity
costs["d"] = infinity
costs["fin"] = infinity


# 构建父节点的散列表
parents = {}
parents["a"] = "start"
parents["b"] = "start"
parents["c"] = None
parents["d"] = None
parents["fin"] = None

# 构建一个数组，用于存放已经处理过的节点
processed = []

def find_lowest_cost_node(costs):
    lowest_cost = float("inf") # 将 cost 定义为最大数，发现更小的cost就更新lowest_cost
    lowest_cost_node = None
    for node in costs:
        cost = costs[node]
        if cost < lowest_cost and node not in processed:
            lowest_cost = cost
            lowest_cost_node = node
    return lowest_cost_node


node = find_lowest_cost_node(costs) # 找到未处理的节点中开销最少的
while node is not None:
    cost = costs[node] # 返回开销表中的从起点到node节点的开销
    neighbors = graph[node] # neighbors也是一个散列表，找到node节点的邻居
    for nbs in neighbors.keys(): # neighbors.keys()函数返回散列表的键，也即邻居，这个for循环跑完了，将node的邻居的开销都更新了一遍，包括父节点，这个node节点也就处理完了
        new_cost = cost + neighbors[nbs] # 更新其邻居的开销
        if costs[nbs] > new_cost: # 如果到其邻居的开销小于开销散列表中存储的，更新
            costs[nbs] = new_cost
            parents[nbs] = node
    processed.append(node)
    node = find_lowest_cost_node(costs) # 继续找到未处理的节点中开销最少的


print(costs["fin"])
        


