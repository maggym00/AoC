#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Dec 23 20:10:46 2018

@author: magnushall
"""

import matplotlib.pyplot as plt
import numpy as np
import csv

data = open("/Users/magnushall/Desktop/coding/AoC/day9/output.csv","r")

graphdata=[]
splituplist=[]
for line in data:
    splituplist.append(line)
x=0
for line in splituplist:
    x = line.split(',')
    for point in x:
        graphdata.append(int(point))
#plt.plot(graphdata)
patternspot=[]
for x in range(len(graphdata)-1):
    patternspot.append(graphdata[x+1]-graphdata[x])
plt.plot(patternspot)