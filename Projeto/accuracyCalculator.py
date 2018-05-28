from math import ceil

def compare(correctVal, predictedVal, errorMarginPercentage=20.0):
    minAccepted = correctVal - (correctVal * errorMarginPercentage / 100.0)
    maxAccepted = correctVal + (correctVal * errorMarginPercentage / 100.0)
    if predictedVal >= minAccepted and predictedVal <= maxAccepted:
        return True
    else:
        return False

def calcAccuracy(correctValMap, predictedValMap, errorMargin=20.0):
    if len(correctValMap) < len(predictedValMap):
        print("[ERROR]: accuracyCalculator.calcAccuracy() - Maps with diferent sizes.")
        return None

    correctCount = 0
    for k, v in predictedValMap.iteritems():
        if(compare(correctVal=correctValMap[k], predictedVal=v, errorMarginPercentage=errorMargin)):
            correctCount += 1

    return correctCount/float(len(predictedValMap))

def createBlocksGenerator(list, blockSize):
    blockSize = int(blockSize)
    for i in range(0, len(list), blockSize):
        yield list[i:i + blockSize]

def kFoldSplit(map, blocksCount):
    mapItens = map.items()
    resultMapsList = []
    blocksSize = ceil(len(mapItens)/float(blocksCount))

    print("Spliting " + str(len(mapItens)) + " inputs, into " + str(blocksCount) + " blocks of " + str(blocksSize))

    blocksGenerator = createBlocksGenerator(list=mapItens, blockSize=blocksSize)
    for block in blocksGenerator:
        tempDict = {}
        for item in block:
            tempDict[item[0]] = item[1]
        resultMapsList.append(tempDict)
    return resultMapsList
