from os import stat
import pandas
from sklearn.metrics import r2_score
from sqlalchemy import not_
from sympy import total_degree
import statistics
import matplotlib.pyplot as plt
import numpy as np
from sklearn.linear_model import Lasso, LogisticRegression
import seaborn as sns

''' 
The following is the starting code for path1 for data reading to make your first step easier.
'dataset_1' is the clean data for path1.
'''
dataset_1 = pandas.read_csv('NYC_Bicycle_Counts_2016_Corrected.csv')
dataset_1['Brooklyn Bridge']      = pandas.to_numeric(dataset_1['Brooklyn Bridge'].replace(',','', regex=True))
dataset_1['Manhattan Bridge']     = pandas.to_numeric(dataset_1['Manhattan Bridge'].replace(',','', regex=True))
dataset_1['Queensboro Bridge']    = pandas.to_numeric(dataset_1['Queensboro Bridge'].replace(',','', regex=True))
dataset_1['Williamsburg Bridge']  = pandas.to_numeric(dataset_1['Williamsburg Bridge'].replace(',','', regex=True))
dataset_1['Williamsburg Bridge']  = pandas.to_numeric(dataset_1['Williamsburg Bridge'].replace(',','', regex=True))
#print(dataset_1.to_string()) #This line will print out your data


"""The use of the code provided is optional, feel free to add your own code to read the dataset. The use (or lack of use) of this code is optional and will not affect your grade."""

#get all data catagories into separate lists
high_temps = dataset_1.loc[:,'High Temp'].tolist()
low_temps = dataset_1.loc[:,'Low Temp'].tolist()
precipitation = dataset_1.loc[:,'Precipitation'].tolist()
brooklyn_bridge = dataset_1.loc[:,'Brooklyn Bridge'].tolist()
manhattan_bridge = dataset_1.loc[:,'Manhattan Bridge'].tolist()
queensboro_bridge = dataset_1.loc[:,'Queensboro Bridge'].tolist()
williamsburg_bridge = dataset_1.loc[:,'Williamsburg Bridge'].tolist()

#manually compute bridge total data catagory since the original is strings instead of floats
total_bridge = []
for x in range(0, len(brooklyn_bridge)):
    total_bridge.append(brooklyn_bridge[x] + manhattan_bridge[x] + queensboro_bridge[x] + williamsburg_bridge[x])

#find and print statistics for each catagory
print("\nStatistics")

#High Temps
print("\nHigh Temp")
n_high_temps = len(high_temps)
mean_high_temps = sum(high_temps) / len(high_temps)
median_high_temps = statistics.median(high_temps)
max_high_temp = max(high_temps)
min_high_temp = min(high_temps)
std_high_temp = statistics.stdev(high_temps)
print("Number of observations: ", n_high_temps)
print("Mean: ", mean_high_temps)
print("Median: ", median_high_temps)
print("Maximum: ", max_high_temp)
print("Minimum: ", min_high_temp)
print("Standard Deviation: ", std_high_temp)

#Low Temps
print("\nLow Temp")
n_low_temps = len(low_temps)
mean_low_temps = sum(low_temps) / len(low_temps)
median_low_temps = statistics.median(low_temps)
max_low_temp = max(low_temps)
min_low_temp = min(low_temps)
std_low_temp = statistics.stdev(low_temps)
print("Number of observations: ", n_low_temps)
print("Mean: ", mean_low_temps)
print("Median: ", median_low_temps)
print("Maximum: ", max_low_temp)
print("Minimum: ", min_low_temp)
print("Standard Deviation: ", std_low_temp)

#Precipitation
print("\nPrecipitation")
n_precipitation = len(precipitation)
mean_precipitation = sum(precipitation) / len(precipitation)
median_precipitation = statistics.median(precipitation)
max_precipitation = max(precipitation)
min_precipitation = min(precipitation)
std_precipitation = statistics.stdev(precipitation)
print("Number of observations: ", n_precipitation)
print("Mean: ", mean_precipitation)
print("Median: ", median_precipitation)
print("Maximum: ", max_precipitation)
print("Minimum: ", min_precipitation)
print("Standard Deviation: ", std_precipitation)

#Brooklyn Bridge
print("\nBrooklyn Bridge")
n_brooklyn = len(brooklyn_bridge)
mean_brooklyn = sum(brooklyn_bridge) / len(brooklyn_bridge)
median_brooklyn = statistics.median(brooklyn_bridge)
max_brooklyn = max(brooklyn_bridge)
min_brooklyn = min(brooklyn_bridge)
std_brooklyn = statistics.stdev(brooklyn_bridge)
print("Number of observations: ", n_brooklyn)
print("Mean: ", mean_brooklyn)
print("Median: ", median_brooklyn)
print("Maximum: ", max_brooklyn)
print("Minimum: ", min_brooklyn)
print("Standard Deviation: ", std_brooklyn)

#Manhattan Bridge
print("\nManhattan Bridge")
n_manhattan = len(manhattan_bridge)
mean_manhattan = sum(manhattan_bridge) / len(manhattan_bridge)
median_manhattan = statistics.median(manhattan_bridge)
max_manhattan = max(manhattan_bridge)
min_manhattan = min(manhattan_bridge)
std_manhattan = statistics.stdev(manhattan_bridge)
print("Number of observations: ", n_manhattan)
print("Mean: ", mean_manhattan)
print("Median: ", median_manhattan)
print("Maximum: ", max_manhattan)
print("Minimum: ", min_manhattan)
print("Standard Deviation: ", std_manhattan)

#Queensboro Bridge
print("\nQueensboro Bridge")
n_queensboro = len(queensboro_bridge)
mean_queensboro = sum(queensboro_bridge) / len(queensboro_bridge)
median_queensboro = statistics.median(queensboro_bridge)
max_queensboro = max(queensboro_bridge)
min_queensboro = min(queensboro_bridge)
std_queensboro = statistics.stdev(queensboro_bridge)
print("Number of observations: ", n_queensboro)
print("Mean: ", mean_queensboro)
print("Median: ", median_queensboro)
print("Maximum: ", max_queensboro)
print("Minimum: ", min_queensboro)
print("Standard Deviation: ", std_queensboro)

#Williamburg Bridge
print("\nWilliamsburg Bridge")
n_williamsburg = len(williamsburg_bridge)
mean_williamsburg = sum(williamsburg_bridge) / len(williamsburg_bridge)
median_williamsburg = statistics.median(williamsburg_bridge)
max_williamsburg = max(williamsburg_bridge)
min_williamsburg = min(williamsburg_bridge)
std_williamsburg = statistics.stdev(williamsburg_bridge)
print("Number of observations: ", n_williamsburg)
print("Mean: ", mean_williamsburg)
print("Median: ", median_williamsburg)
print("Maximum: ", max_williamsburg)
print("Minimum: ", min_williamsburg)
print("Standard Deviation: ", std_williamsburg)

#Total for all bridges
print("\nTotal for all bridges")
n_total = len(total_bridge)
mean_total = sum(total_bridge) / len(total_bridge)
median_total = statistics.median(total_bridge)
max_total = max(total_bridge)
min_total = min(total_bridge)
std_total = statistics.stdev(total_bridge)
print("Number of observations: ", n_total)
print("Mean: ", mean_total)
print("Median: ", median_total)
print("Maximum: ", max_total)
print("Minimum: ", min_total)
print("Standard Deviation: ", std_total)

#make histogram for total from all bridges
plt.hist(total_bridge, density=True, bins=20)
plt.xlabel("Total traffic on all bridges")
plt.ylabel("Number of observations")
plt.title("Histogram for Total Traffic on all Bridges")
plt.show()

#problem 1

#normalize all the bridge datasets
norm_brooklyn = []
norm_manhattan = []
norm_queensboro = []
norm_williamsburg = []
norm_total = []

for x in range(0, len(total_bridge)):
    norm_brooklyn.append((brooklyn_bridge[x] - mean_brooklyn) / std_brooklyn)
    norm_manhattan.append((manhattan_bridge[x] - mean_manhattan) / std_manhattan)
    norm_queensboro.append((queensboro_bridge[x] - mean_queensboro) / std_queensboro)
    norm_williamsburg.append((williamsburg_bridge[x] - mean_williamsburg) / std_williamsburg)
    norm_total.append((total_bridge[x] - mean_total) / std_total)

plt.scatter(range(0, 214), norm_brooklyn, color="red", label="Brooklyn")
plt.scatter(range(0, 214), norm_manhattan, color="blue", label="Manhattan")
plt.scatter(range(0, 214), norm_queensboro, color="orange", label="Queensboro")
plt.scatter(range(0, 214), norm_williamsburg, color="green", label="Williamsburg")
plt.scatter(range(0, 214), norm_total, color="black", label="Total")
plt.legend()
plt.title("Normalized Bridge Traffic Data")
plt.ylabel("Normalized bike traffic")
plt.xlabel("Day")
plt.show()

#polyfit predictor
second = np.poly1d(np.polyfit(range(0, 214), norm_total, 2))

x = np.linspace(0, 214, 1000)

plt.scatter(range(0, 214), norm_total, color="Black")
plt.plot(x, second(x), color="blue")
plt.title("Total")
plt.ylabel("Normalized bike traffic")
plt.xlabel("Day")
plt.show()

plt.scatter(range(0, 214), norm_brooklyn, color="Black")
plt.plot(x, second(x), color="blue")
plt.title("Brooklyn")
plt.ylabel("Normalized bike traffic")
plt.xlabel("Day")
plt.show()

plt.scatter(range(0, 214), norm_manhattan, color="Black")
plt.plot(x, second(x), color="blue")
plt.title("Manhattan")
plt.ylabel("Normalized bike traffic")
plt.xlabel("Day")
plt.show()

plt.scatter(range(0, 214), norm_queensboro, color="Black")
plt.plot(x, second(x), color="blue")
plt.title("Queensboro")
plt.ylabel("Normalized bike traffic")
plt.xlabel("Day")
plt.show()

plt.scatter(range(0, 214), norm_williamsburg, color="Black")
plt.plot(x, second(x), color="blue")
plt.title("Williamsburg")
plt.ylabel("Normalized bike traffic")
plt.xlabel("Day")
plt.show()

#problem 2

weather = np.column_stack((high_temps, low_temps, precipitation))
y2 = np.array(total_bridge)

model = Lasso()

model.fit(weather, y2)

print("\nTotal traffic predictions based on weather:")
print("high temp, low temp, precipitation: prediction")

print("\n90, 80, 0.0: ", model.predict(np.array([90, 80, 0.0]).reshape(1, -1)))
print("90, 80, 0.5: ", model.predict(np.array([90, 80, 0.5]).reshape(1, -1)))
print("90, 80, 1.0: ", model.predict(np.array([90, 80, 1.0]).reshape(1, -1)))
print("90, 80, 1.5: ", model.predict(np.array([90, 80, 1.5]).reshape(1, -1)))

print("\n50, 40, 0.0: ", model.predict(np.array([50, 40, 0.0]).reshape(1, -1)))
print("50, 40, 0.5: ", model.predict(np.array([50, 40, 0.5]).reshape(1, -1)))
print("50, 40, 1.0: ", model.predict(np.array([50, 40, 1.0]).reshape(1, -1)))
print("50, 40, 1.5: ", model.predict(np.array([50, 40, 1.5]).reshape(1, -1)))

print("\n70, 60, 0.0: ", model.predict(np.array([70, 60, 0.0]).reshape(1, -1)))
print("70, 60, 0.5: ", model.predict(np.array([70, 60, 0.5]).reshape(1, -1)))
print("70, 60, 1.0: ", model.predict(np.array([70, 60, 1.0]).reshape(1, -1)))
print("70, 60, 1.5: ", model.predict(np.array([70, 60, 1.5]).reshape(1, -1)))

print("\ncoeffs = ", model.coef_)

print("r-squared = ", r2_score(total_bridge, model.predict(weather)))

#problem 3

rain_or_not = []
rain = []
no_rain = []
for x in precipitation:
    if x > 0:
        rain_or_not.append(1)
    else:
        rain_or_not.append(0)

not_raining = []
raining = []
for y in range(0, len(precipitation)):
    if rain_or_not[y] == 0:
        not_raining.append(total_bridge[y])
    else:
        raining.append(total_bridge[y])

print("\nMean traffic on days with rain: ", np.mean(raining))
print("Median traffic on days with rain: ", np.median(raining))
print("Standard deviation of traffic on days with rain: ", np.std(raining))
print("Maximum of traffic on days with rain: ", max(raining))
print("Minimum of traffic on days with rain: ", min(raining))

print("\nMean traffic on days with no rain: ", np.mean(not_raining))
print("Median traffic on days with no rain: ", np.median(not_raining))
print("Standard deviation of traffic on days with no rain: ", np.std(not_raining))
print("Maximum of traffic on days with no rain: ", max(not_raining))
print("Minimum of traffic on days with no rain: ", min(not_raining))

traffic = np.array(total_bridge).reshape(-1, 1)
rain_or_not = np.array(rain_or_not)

rain_model = LogisticRegression(class_weight = 'balanced')

rain_model.fit(traffic, rain_or_not)

test_data = [30000, 28000, 26000, 24000, 22000, 20000, 18000, 16000, 14000, 12000, 10000, 8000, 6000, 4000, 2000, 0]
test_results = rain_model.predict(np.array(test_data).reshape(-1, 1))

plt.scatter(traffic, rain_or_not)
plt.title("Rain vs. Total Traffic")
plt.xlabel("Total Traffic")
plt.ylabel("Rain (1) or No rain (0)")
plt.show()

print("\nPredictions for total traffic numbers 30000, 28000, 26000, 24000, 22000, 20000, 18000, 16000, 14000, 12000, 10000, 8000, 6000, 4000, 2000, 0")
print("(0 = no rain, 1 = rain)")
print(test_results)

test_data2 = [18000, 17800, 17600, 17400, 17200, 17000, 16800, 16600, 16400, 16200, 16000]
test_results2 = rain_model.predict(np.array(test_data2).reshape(-1, 1))

print("\nPredictions for total traffic numbers 18000, 17800, 17600, 17400, 17200, 17000, 16800, 16600, 16400, 16200, 16000")
print("(0 = no rain, 1 = rain)")
print(test_results2)