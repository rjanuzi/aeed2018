import math
import random
from operator import itemgetter
import input_loader
from xlsWriter import KnnResult
from xlsWriter import saveEntriesDict
from xlsWriter import saveKnnResultList

PREDICTED_OUTPUT_FILE_PATH = "C:\\Users\\Rafael\\Desktop\\aeed2018\\Projeto\\predicted.xlsx"
RNDM_ACC_OUTPUT_FILE_PATH = "C:\\Users\\Rafael\\Desktop\\aeed2018\\Projeto\\calcRandomAccuracyResult.xlsx"

K_DEFAULT_PARAM = 5
DEFAULT_ACCEPTED_ERROR = 1000

def buildKey(year, period, family):
    return str(year) + "," + \
        str(period)  + "," + \
        str(family)

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

def knn(dataset, new, k=K_DEFAULT_PARAM, familyKeys=None, filterMaxMin=False, useMedian=False):
    # Filter the keys in dataset with family of interest

    if familyKeys:
        datasetKeysWithFamily = familyKeys
    else:
        familyOfInterest = new.split(",")[2]
        datasetKeysWithFamily = filter(lambda f: familyOfInterest in f, dataset.keys())

    # Each element in distances list is a list like (key, distToReference)
    distances = []
    for key in datasetKeysWithFamily:
        distances.append((key, calcDist(key, new)))

    distances = sorted(distances, key=itemgetter(1))

    if K_DEFAULT_PARAM < len(distances):
        kElements = distances[0:K_DEFAULT_PARAM]
    else:
        kElements = distances

    if len(kElements) > 2 and filterMaxMin:
        kElements.pop() #Remove last (Max)
        kElements.pop(0) #Remove first (Min)

    if not useMedian:
        sum = .0
        for element in kElements:
            sum += dataset[element[0]]

        return sum/float(len(kElements)) # Return the average
    else:
        return dataset[ kElements[int(float(len(kElements))/2.0)][0] ] # Return the median (element in midle of the sorted list)

# ======================= TESTS ======================== #

def testRun():
    inputs, families = input_loader.getInput()

    for count in range(10):
        # Pick (remove) a random value from the dataset
        testingElementKey = random.choice(inputs.keys())
        testingVal = inputs.pop(testingElementKey)
        print("Picked: " + str(testingElementKey))
        print("Val: " + str(testingVal) + " ~= " + str(knn(inputs, testingElementKey)))

        #Add picked element back
        inputs[testingElementKey] = testingVal

def predictYear(yearToPredict):
    PERIOD_COUNT = 11*12
    PERIOD_MIN = 1
    PERIOD_MAX = PERIOD_COUNT+1

    # Load inputs
    inputs, families = input_loader.getInput()
    predictedEntries = dict()

    for i in range(len(families)):
        print("Predicting: " + str((float(i)/float(len(families)))*100.0) + "%)")
        keysOfInterest = filter(lambda f: families[i] in f, inputs.keys())
        for period in range(PERIOD_MIN, PERIOD_MAX):
            tempKey = buildKey(yearToPredict, period, families[i])
            predictedEntries[tempKey] = knn(inputs, tempKey, familyKeys=keysOfInterest)
        i += 1

    inputs.update(predictedEntries)

    print("Saving predicted file")
    saveEntriesDict(PREDICTED_OUTPUT_FILE_PATH, inputs)
    print("Done")

def calcRandomAccuracy(countPerConfig, kParams):

    booleanOpts = [True, False]

    # Load inputs
    inputs, families = input_loader.getInput()

    results = []
    for kParam in kParams:
        for filterMaxMinParam in booleanOpts:
            for useMedianParam in booleanOpts:
                errors = []
                for i in range(countPerConfig):
                    # Pick (remove) a random value from the dataset
                    testingElementKey = random.choice(inputs.keys())
                    testingVal = inputs.pop(testingElementKey)

                    # Predict the removed value
                    predictedVal = knn(inputs, testingElementKey, \
                        k=kParam, filterMaxMin=filterMaxMinParam, useMedian=useMedianParam)

                    # Register the error (absolute distance between the predicted and the real value)
                    errors.append(abs(testingVal-predictedVal))

                    # Return the removed elemento to the datase
                    inputs[testingElementKey] = testingVal

                # Append the result object
                errors = sorted(errors)
                resultTemp = KnnResult()
                resultTemp.paramK = kParam
                resultTemp.filterMaxMin = filterMaxMinParam
                resultTemp.useMedian = useMedianParam
                resultTemp.averageError = sum(errors)/float(len(errors))
                resultTemp.medianError = errors[ int((len(errors)/2)) ]
                resultTemp.minError, resultTemp.maxError = errors[0], errors[-1]
                results.append(resultTemp)

    saveKnnResultList(results, RNDM_ACC_OUTPUT_FILE_PATH)


#testRun()
#predictYear(2016)
#calcRandomAccuracy(200, range(30))

## TODO: Implementar o teste de acurária avaliando apenas os elementos com as 7 familias mais importantes
