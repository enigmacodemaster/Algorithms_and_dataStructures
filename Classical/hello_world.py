def sumup(arr):
    lenth = len(arr)
    if lenth==1:
        return arr[0]
    else:
        tmp = arr[0]
        del arr[0]
        return tmp + sumup(arr)

print(sumup([1,2,3,4,5]))
