import input_loader
import random
from xlsWriter import saveEntriesDict
from accuracyCalculator import calcAccuracy
from accuracyCalculator import kFoldSplit
from sklearn.neural_network import MLPRegressor

K_FOLD_OUTPUT_FILE_PATH = "C:\\Users\\Rafael\\Desktop\\aeed2018\\Projeto\\mlp_kfold_predictions.xlsx"
HIDDEN_LAYER_SIZES_DEFAULT = (100,)
ACTIVATION_DEFAULT = "relu"
SOLVER_DEFAULT = "adam"
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

def createTrainedRegressor(inputs, expectedOutputs):
    regressor = MLPRegressor(hidden_layer_sizes=HIDDEN_LAYER_SIZES_DEFAULT,
        activation=ACTIVATION_DEFAULT, solver=SOLVER_DEFAULT)
    regressor.fit(inputs, expectedOutputs)
    return regressor

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
        trainInputs = [] # [ [year1, period1, family_int_sum1], [year2, period2, family_int_sum2], ...]
        trainExpectedOutputs = [] # [[result1], [result2], ...]

        for j in range(len(inputsBlocks)):
            if j != i:
                dataSet.update(inputsBlocks[j])

        # Prepare data to train
        print("Preparing data to train...")
        for k, v in dataSet.iteritems():
            splitedKey = k.split(",")
            trainInputs.append([int(splitedKey[0]), int(splitedKey[1]), sum(bytearray(splitedKey[2]))])
            trainExpectedOutputs.append(v)

        # Training
        print("Training regressor...")
        regressor = createTrainedRegressor(trainInputs, trainExpectedOutputs)

        # Predicting...
        for testingKey in testSet.keys():
            splitedKey = k.split(",")
            predictionsMap[testingKey] = regressor.predict([[int(splitedKey[0]), int(splitedKey[1]), sum(bytearray(splitedKey[2]))]])[0]

        # Calculating Accuracy
        print("Calculating Accuracy...")
        tempAccuracy = calcAccuracy(correctValMap=testSet, predictedValMap=predictionsMap, errorMargin=ERROR_MARGIN_DEFAULT)
        print("Accuracy for fold " + str(i) + ": " + str(tempAccuracy))
        accuracies.append(tempAccuracy)
        predictedEntries.update(predictionsMap)

    print("Accuracies: " + str(accuracies))
    tempSum = .0
    for acc in accuracies:
        tempSum += acc
    print("Average Accuracy: " + str(tempSum/float(len(accuracies))))
    print("Saving predicted file")
    saveEntriesDict(K_FOLD_OUTPUT_FILE_PATH, predictedEntries)

calcKFoldAccuracy()
