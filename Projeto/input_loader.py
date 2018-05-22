from openpyxl import load_workbook
from openpyxl import Workbook

# In use cols
YEAR_COL = 0
PERIOD_COL = 1
CLIENT_COL = 2
FAMILY_COL = 3
QTD_COL = 4

inputFilePath = "C:\\Users\\Rafael\\Desktop\\aeed2018\\Projeto\\treated_input.xlsx"

def buildKey(year, period, client, family):
    return str(year) + "," + \
        str(period)  + "," + \
        str(client) + "," + \
        str(family)

def getInput():
    print("Loading input")
    # Load Workbook. data_only = True force the formulas calculations
    wb = load_workbook(filename = inputFilePath, data_only = True) # Full input
    # Get the desired Sheet
    ws = wb['Sheet']

    # Create new dictionary
    inputs = dict()
    # Start at row 2 to skip the table title
    for row in ws.iter_rows(min_row = 1, max_col = 6):
        try:
            # Generate the map key
            temp_key = buildKey(row[YEAR_COL].value, row[PERIOD_COL].value, \
                    row[CLIENT_COL].value, row[FAMILY_COL].value)
            # Adjust quantity to the map
            if temp_key in inputs:
                print("[ERROR]: input_loader.py - Loading - duplicated key: " + temp_key)
            else:
                inputs[temp_key] = int(row[QTD_COL].value)
        except ValueError:
            print "Oops! Error interpreting the file"

    wb.close()
    print("Input Loaded: " + str(len(inputs)) + " entries")
    return inputs
