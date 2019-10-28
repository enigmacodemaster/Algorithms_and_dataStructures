from collections import deque

graph = {}
graph["A"] = ["B", "C", "D"]



def person_is_seller(name):
    return name[-1] == 'm' # 最后一个字母为m


def search(name):
    search_queue = deque()  # 创建队列
    search_queue += graph[name] # 在队列中添加元素
    searched = []
    while search_queue:
        person = search_queue.popleft()
        if not person in searched:
            if person_is_seller(person):
                print(person + "is not a mango seller!")
                return True
            else:
                search_queue += graph["person"]
                searched.append(person)
    return False


search("you")
