PERIOD_COUNT = 11*12

PERIOD_MIN = 1
PERIOD_MAX = PERIOD_COUNT+1
YEAR_MIN = 2010
YEAR_MAX = 2016 #2015 + 1

def getBefore(year, period):
    if(period > PERIOD_MIN):
        return year, period-1
    else:
        if(year > YEAR_MIN):
            return year-1, PERIOD_MAX-1
        else:
            return -1, -1

x, y = getBefore(2010, 1)
print(x, y)
