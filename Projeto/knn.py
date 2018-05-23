import math
import random
from operator import itemgetter
import input_loader

DEFAULT_ACCEPTED_ERROR = 1000

def euclideanDist(A, B):
    sum = 0.0
    for i in range(len(A)):
        sum += ((A[i]-B[i])**2)

    return math.sqrt(sum)

# Calc dist between two itens "'year,period,family'"
def calcDist(x1, x2):
    x1Splited = x1.split(",")
    x2Splited = x2.split(",")
    x1Vals = [int(x1Splited[0]), int(x1Splited[1])]
    x2Vals = [int(x2Splited[0]), int(x2Splited[1])]

    return euclideanDist([x1Vals[0],x1Vals[1]], [x2Vals[0],x2Vals[1]])

def knn(k, dataset, new):
    # Filter the keys in dataset with family of interest
    familyOfInterest = new.split(",")[2]
    datasetKeysWithFamily = filter(lambda f: familyOfInterest in f, dataset.keys())

    # Each element in distances list is a list like (key, distToReference)
    distances = []
    for key in datasetKeysWithFamily:
        distances.append((key, calcDist(key, new)))

    distances = sorted(distances, key=itemgetter(1))

    if k < len(distances):
        kElements = distances[0:k]
    else:
        kElements = distances

    print("K-Distances: " + str(kElements))

    sum = .0
    for element in kElements:
        sum += dataset[element[0]]

    print("Sum: " + str(sum))
    print("Average: " + str(sum/float(len(kElements))))
    return sum/float(len(kElements))

# Load inputs
inputs = input_loader.getInput()

for count in range(5):
    # Pick (remove) a random value from the dataset
    testingElementKey = random.choice(inputs.keys())
    testingVal = inputs.pop(testingElementKey)
    print("Picked: " + str(testingElementKey))
    print("Val: " + str(testingVal))
    print("Predicted: " + str(knn(5, inputs, testingElementKey)))
    print("\n")
