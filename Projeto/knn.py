import math
import random
from operator import itemgetter
import input_loader
from xlsWriter import KnnResult
from xlsWriter import saveEntriesDict
from xlsWriter import saveKnnResultList
from accuracyCalculator import compare
from accuracyCalculator import calcAccuracy
from accuracyCalculator import kFoldSplit

PREDICTED_OUTPUT_FILE_PATH = "C:\\Users\\Rafael\\Desktop\\aeed2018\\Projeto\\predicted.xlsx"
RNDM_ACC_OUTPUT_FILE_PATH = "C:\\Users\\Rafael\\Desktop\\aeed2018\\Projeto\\calcRandomAccuracyResult.xlsx"
YEARS_ACC_OUTPUT_FILE_PATH = "C:\\Users\\Rafael\\Desktop\\aeed2018\\Projeto\\calcAccuracyForYearsResult.xlsx"
K_FOLD_OUTPUT_FILE_PATH = "C:\\Users\\Rafael\\Desktop\\aeed2018\\Projeto\\knn_kfold_predictions.xlsx"

K_DEFAULT_PARAM = 9
FILTER_MAX_MIN_DEFAULT_PARAM = True
USE_MEADIAN_DEFAULT_PARAM = True
ERROR_MARGIN_DEFAULT = 10.0

#PERIOD_COUNT = 11*12
PERIOD_COUNT = 6*12
PERIOD_MIN = 1
PERIOD_MAX = PERIOD_COUNT+1
YEAR_MIN = 2010
YEAR_MAX = 2016 #2015 + 1

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

def knn(dataset, new, k=K_DEFAULT_PARAM, familyKeys=None, \
    filterMaxMin=FILTER_MAX_MIN_DEFAULT_PARAM, useMedian=USE_MEADIAN_DEFAULT_PARAM):
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
def predict2016():

    # Load inputs
    inputs, families = input_loader.getInput()
    predictedEntries = dict()
    yearToPredict = 2016

    for i in range(len(families)):
        print("Predicting: " + str((float(i)/float(len(families)))*100.0) + " % ")
        keysOfInterest = filter(lambda f: families[i] in f, inputs.keys())
        for period in range(PERIOD_MIN, PERIOD_MAX):
            tempKey = buildKey(yearToPredict, period, families[i])
            predictedEntries[tempKey] = knn(inputs, tempKey, familyKeys=keysOfInterest)
        i += 1

    inputs.update(predictedEntries)

    print("Saving predicted file")
    saveEntriesDict(PREDICTED_OUTPUT_FILE_PATH, inputs)
    print("Done")

def calcRandomAccuracy(countPerConfig, kParams, familesToPredict=None):

    booleanOpts = [True, False]

    # Load inputs
    inputs, families = input_loader.getInput()

    print("Total keys: " + str(len(inputs.keys())))
    if familesToPredict: # Not all families
        validKeys = []
        for validFamily in familesToPredict:
            validKeys += filter(lambda k: validFamily in k, inputs.keys())
    else:
        validKeys = inputs.keys() # All families

    print("Eligible keys to test: " + str(len(validKeys)))

    results = []
    for i in range(len(kParams)):
        print("Testing: " + str((float(i)/float(len(kParams)))*100.0) + " %")
        for filterMaxMinParam in booleanOpts:
            for useMedianParam in booleanOpts:
                errors = []
                correctPredictionCount = 0
                for j in range(countPerConfig):
                    # Pick (remove) a random value from the dataset
                    testingElementKey = random.choice(validKeys)
                    testingVal = inputs.pop(testingElementKey)

                    # Predict the removed value
                    predictedVal = knn(inputs, testingElementKey, \
                        k=kParams[i], filterMaxMin=filterMaxMinParam, useMedian=useMedianParam)

                    # Register the error (absolute distance between the predicted and the real value)
                    erroTemp = abs(testingVal-predictedVal)
                    errors.append(erroTemp)
                    if(compare(testingVal, predictedVal, errorMarginPercentage=ERROR_MARGIN_DEFAULT)):
                        correctPredictionCount += 1

                    # Return the removed elemento to the datase
                    inputs[testingElementKey] = testingVal

                # Append the result object
                errors = sorted(errors)
                resultTemp = KnnResult()
                resultTemp.paramK = kParams[i]
                resultTemp.filterMaxMin = filterMaxMinParam
                resultTemp.useMedian = useMedianParam
                resultTemp.averageError = sum(errors)/float(len(errors))
                resultTemp.minError, resultTemp.maxError = errors[0], errors[-1]
                resultTemp.accuracy = correctPredictionCount/float(len(errors))
                results.append(resultTemp)
        i += 1

    saveKnnResultList(results, RNDM_ACC_OUTPUT_FILE_PATH)

def calcKFoldAccuracy():
    inputs, families = input_loader.getInput()
    inputsBlocks = kFoldSplit(map=inputs, blocksCount=10)
    accuracies = []
    predictedEntries = {}

    for i in range(len(inputsBlocks)):
        print("Testing fold " + str(i) + " of " + str(len(inputsBlocks)-1))
        predictionsMap = {}
        testSet = inputsBlocks[i]
        dataSet = {}

        for j in range(len(inputsBlocks)):
            if j != i:
                dataSet.update(inputsBlocks[j])

        for testingKey in testSet.keys():
            predictionsMap[testingKey] = knn(dataSet, testingKey)

        tempAccuracy = calcAccuracy(correctValMap=testSet, predictedValMap=predictionsMap, errorMargin=ERROR_MARGIN_DEFAULT)
        print("Accuracy for fold " + str(i) + ": " + str(tempAccuracy))
        accuracies.append(tempAccuracy)
        predictedEntries.update(predictionsMap)

    print("Accuracies: " + str(accuracies))
    sum = .0
    for acc in accuracies:
        sum += acc
    print("Average Accuracy: " + str(sum/float(len(accuracies))))
    print("Saving predicted file")
    saveEntriesDict(K_FOLD_OUTPUT_FILE_PATH, predictedEntries)

#predict2016()
#calcRandomAccuracy(200, range(1, 25)) # All families
#calcRandomAccuracy(200, range(1, 25), familesToPredict=["CAABSK5C40", "CAABCB5C40", "CACICK5C40", "CAABSK5B20", "CAABCA5C40", "CAABSK9C50", "CAABCZ5C40"]) # 7 more selled
calcKFoldAccuracy()
