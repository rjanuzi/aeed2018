from openpyxl import load_workbook
from openpyxl import Workbook

# In use cols
DATE_COL = 0
CLIENT_COL = 1
FAMILY_COL = 2
SALES_COL = 6

inputFilePath = "C:\\Users\\Rafael\\Desktop\\aeed2018\\Projeto\\Dataset\\Ztco0018 2010_2015.xlsx"
outputFilePath = "C:\\Users\\Rafael\\Desktop\\aeed2018\\Projeto\\treated_input.xlsx"

ENTRIES_TOTAL_COUNT = 432 # 6 Periods by month (12) by year (6)
ENTRIES_MIN_COUNT = 350 #Dataset contains 432 points

def calcPeriod(day, month):
        "This function calculate the period of year"
        month_part = calcMonthPart(day)

        if month_part <= 0:
                return -1
        return month_part + 6*month - 6

def calcMonthPart(day):
        "This function calculate the month part of the year's period"
        if(day <= 0):
                return -1
        # [1, 5)
        if day >= 1 and day < 5:
                return 1
        # [5, 10)
        if day >= 5 and day < 10:
                return 2
        # [10, 15)
        if day >= 10 and day < 15:
                return 3
        # [15, 20)
        if day >= 15 and day < 20:
                return 4
        # [20, 25)
        if day >= 20 and day < 25:
                return 5
        return 6

def buildKey(year, period, client, family):
    return str(year) + "," + \
        str(period)  + "," + \
        str(tempClientName) + "," + \
        str(tempFamilyName)

print("Loading input")

# Load Workbook. data_only = True force the formulas calculations
wb = load_workbook(filename = inputFilePath, data_only = True) # Full input

# Get the desired Sheet
ws = wb['Plan1']

# Create new dictionary
sales_map = dict()
clients = []
families = []
finalClients = []
finalFamilies = []

print("Processing input")

# Start at row 2 to skip the table title
for row in ws.iter_rows(min_row = 2, max_col = 13):
    tempClientName = row[CLIENT_COL].value.encode("utf-8") # Encode to solve a dataset problem
    tempFamilyName = row[FAMILY_COL].value.encode('utf-8') # Encode to solve a dataset problem
    try:
        # Generate the map key
        temp_key = buildKey(row[DATE_COL].value.year, \
                    str( calcPeriod(row[DATE_COL].value.day, row[DATE_COL].value.month) ), \
                    tempClientName, \
                    str(tempFamilyName) )

#        temp_key = str(row[DATE_COL].value.year) + "," + \
#                str( calcPeriod(row[DATE_COL].value.day, row[DATE_COL].value.month) )  + "," + \
#                str(tempClientName) + "," + \
#                str(tempFamilyName)

        # Adjust quantity to the map
        if temp_key in sales_map:
                sales_map[temp_key] = sales_map[temp_key] + row[SALES_COL].value
        else:
                sales_map[temp_key] = row[SALES_COL].value

        # Fill the clients and families list for future use
        if tempClientName not in clients:
            clients.append(tempClientName)
        if tempFamilyName not in families:
            families.append(tempFamilyName)

    except ValueError:
        print "Oops! Error interpreting the file"

wb.close()

# Start filter clients and families with low data
print("Filtering treted data")

print("Removing clients and families with low data")

keysList = list(sales_map.keys())
for client in clients:
    keysWithClient = filter(lambda k: client in k, keysList)
    if(len(keysWithClient) < ENTRIES_MIN_COUNT):
        for keyToRemove in keysWithClient:
            if keyToRemove in sales_map:
                del sales_map[keyToRemove]
    else:
        finalClients.append(client)

keysList = list(sales_map.keys())
for family in families:
    keysWithFamily = filter(lambda k: family in k, keysList)
    if(len(keysWithFamily) < ENTRIES_MIN_COUNT):
        for keyToRemove in keysWithFamily:
            if keyToRemove in sales_map:
                del sales_map[keyToRemove]
    else:
        finalFamilies.append(family)

#Generate 0s for missing dots
print("Adding 0s for missing entries")

for year in range(2010, 2016):
    for period in range(1, 73):
        for client in finalClients:
            for family in finalFamilies:
                tempKey = buildKey(year, period, client, family)
                if tempKey not in sales_map:
                    sales_map[tempKey] = 0

print( str(len(finalClients)) + " - clients: " + str(finalClients))
print( str(len(finalFamilies)) + " - families: " + str(finalFamilies))

print("Saving treated_input")

res = Workbook()
res_sheet = res.active

for key, value in sales_map.items():
            splited_key = key.split(",")
            splited_key.append(value)
            res_sheet.append(splited_key)

res.save(outputFilePath)

print("Done")
