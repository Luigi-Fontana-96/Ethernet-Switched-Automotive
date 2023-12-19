#!/usr/bin/env python3
from tkinter import FALSE
import pandas as pd

df = pd.read_csv('report2.csv')

statistics = df[["NomeFlusso"," numRxFrames"," numeroSimulazione"]].groupby(["NomeFlusso"," numeroSimulazione"]).max()

statistics.to_csv("statistic.csv")
