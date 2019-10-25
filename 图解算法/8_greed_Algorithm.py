# 需要覆盖的电台
states_needed = set(["mt", "wa", "or", "id", "nv", "ut","ca", "az"]) # set集合，类似于列表，但是同样的元素只能出现一次

# 广播台清单，散列表实现
stations = {}
stations["kone"] = set(["id", "nv", "ut"])
stations["ktwo"] = set(["wa", "id", "mt"])
stations["kthree"] = set(["or", "nv", "ca"])
stations["kfour"] = set(["nv", "ut"])
stations["kfive"] = set(["ca", "az"])

# 用一个集合存储最终选择的广播台
final_stations = set()


while states_needed:
    # 当前循环选取的局部最优的电台
    best_station = None
    # 包含该广播台覆盖的所有未覆盖的州
    states_covered = set()

    for station, states_for_station in stations.items(): # 遍历散列表中的所有内容，散列表的键为电台，值为列表
        covered = states_needed & states_for_station # 选出与需求中的州列表交集最多的电台
        if len(covered) > len(states_covered):
            best_station = station
            states_covered = covered
    
    states_needed -= states_covered
    final_stations.add(best_station)


print(final_stations)
