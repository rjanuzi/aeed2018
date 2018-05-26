from accuracyCalculator import kFoldSplit

map = {"A":1, "B":2, "C":3, "D":4, "E":5, "F":6, "G":7, "H":8, "J":9, "K":10 }
mapItens = map.items()

mapsList = kFoldSplit(map, 5)
for subMap in mapsList:
    print(subMap)
