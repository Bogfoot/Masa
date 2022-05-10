import pandas as pd
import numpy as np
import plotly.graph_objects as go
import plotly.io as pio
import os

np.set_printoptions(precision=3, suppress=False)

if not os.path.exists("Slike"):
    os.mkdir("Slike")


df = pd.read_csv('rolling_median.csv',delimiter=',')
y = df["23.08"]
x = np.linspace(1,len(df),len(df))

name_m = "Rolling median za Adriana"
fig = go.Figure()
fig.add_trace(go.Scatter( x = x, y = y, name = name_m, mode = 'lines'))

pio.write_image(fig, "Slike/" + name_m + ".png", width=2000, height=2000)
