from openpyxl import load_workbook
from openpyxl import Workbook

# In use cols
DATE_COL = 0
FAMILY_COL = 2
SALES_COL = 6

PERIOD_COUNT = 6*12
PERIOD_COUNT_V2 = 11*12

inputFilePath = "C:\\Users\\Rafael\\Desktop\\aeed2018\\Projeto\\Dataset\\Ztco0018 2010_2015.xlsx"
outputFilePath = "C:\\Users\\Rafael\\Desktop\\aeed2018\\Projeto\\treated_input.xlsx"

#Ex: angularCoefficient([-5.0,4.0], [3.0,2.0])
def angularCoefficient(A, B):
    return (B[1]-A[1]) / (B[0]-A[0])

def calcPeriod(day, month):
        "This function calculate the period of year"
        month_part = calcMonthPart(day)

        if month_part <= 0:
                return -1
        return month_part + 6*month - 6

def calcPeriod_v2(day, month):
        "This function calculate the period of year"
        month_part = calcMonthPart_v2(day)

        if month_part <= 0:
                return -1
        return month_part + 11*month - 11

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

def calcMonthPart_v2(day):
        "This function calculate the month part of the year's period"
        if(day <= 0):
                return -1
        # [1, 3)
        if day >= 1 and day < 3:
                return 1
        # [3, 6)
        if day >= 3 and day < 6:
                return 2
        # [6, 9)
        if day >= 6 and day < 9:
                return 3
        # [9, 12)
        if day >= 9 and day < 12:
                return 4
        # [12, 15)
        if day >= 12 and day < 15:
                return 5
        # [15, 18)
        if day >= 15 and day < 18:
                return 6
        # [18, 21)
        if day >= 18 and day < 21:
                return 7
        # [21, 24)
        if day >= 21 and day < 24:
                return 8
        # [24, 27)
        if day >= 24 and day < 27:
                return 9
        # [27, 30)
        if day >= 27 and day < 30:
                return 10
        return 11

def buildKey(year, period, family):
    return str(year) + "," + \
        str(period)  + "," + \
        str(family)

print("Loading input")

# Load Workbook. data_only = True force the formulas calculations
wb = load_workbook(filename = inputFilePath, data_only = True) # Full input

# Get the desired Sheet
ws = wb['Plan1']

# Create new dictionary
sales_map = dict()
families = []

print("Processing input")

# Start at row 2 to skip the table title
for row in ws.iter_rows(min_row = 2, max_col = 13):
    tempFamilyName = row[FAMILY_COL].value.encode('utf-8') # Encode to solve a dataset problem
    try:
        # Generate the map key
        temp_key = buildKey(row[DATE_COL].value.year, \
                    str( calcPeriod_v2(row[DATE_COL].value.day, row[DATE_COL].value.month) ), \
                    tempFamilyName )

        # Adjust quantity to the map
        if temp_key in sales_map:
                sales_map[temp_key] = sales_map[temp_key] + row[SALES_COL].value
        else:
                sales_map[temp_key] = row[SALES_COL].value

        # Fill the families list for future use
        if tempFamilyName not in families:
            families.append(tempFamilyName)

    except ValueError:
        print "Oops! Error interpreting the file"

wb.close()

#Generate 0s for missing dots
print("Adding 0s for missing entries")

period_min = 1
period_max = PERIOD_COUNT_V2+1
for family in families:
    keysList = list(sales_map.keys())
    keysWithFamily = filter(lambda k: family in k, keysList)
    for year in range(2010, 2016):
        for period in range(period_min, period_max):
            tempKey = buildKey(year, period, family)
            if tempKey not in sales_map:
                sales_map[tempKey] = 0

print("Saving treated_input")

res = Workbook()
res_sheet = res.active

for key, value in sales_map.items():
            splited_key = key.split(",")
            splited_key.append(value)
            res_sheet.append(splited_key)

res.save(outputFilePath)
res.close()

print("Done")