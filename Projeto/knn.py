import math
import random
import input_loader

def euclideanDist(A, B):
    sum = 0.0
    for i in range(len(A)):
        sum += ((A[i]-B[i])**2)

    return math.sqrt(sum)

# Calc dist between two itens "'year,period,family'"
def calcDist(x1, x2):
    x1Splited = x1.split(",")
    x1Vals = [int(x1Splited[0]), int(x1Splited[1]), x1Splited[2]]
    x2Splited = x2.split(",")
    x2Vals = [int(x2Splited[0]), int(x2Splited[1]), x2Splited[2]]

    if x1Vals[2] != x2Vals[2]:
        return float("inf")
    else:
        return euclideanDist( \
            [int(x1Vals[0]),int(x1Vals[1])], \
            [int(x2Vals[0]),int(x2Vals[1])] )

def knn(k, dataset, new, error):
    datasetKeys = sales_map.keys()
    distances = []

    for key in dataset:
        distances.append((key, calcDist(key, new)))

    print(distances)

inputs = input_loader.getInput()
testingElementKey = random.choice(inputs.keys())
#testingVal = input.pop(testingElementKey)

print(testingElementKey)

#knn(10, inputs, testingElementKey, 0.5)
