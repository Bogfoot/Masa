import pandas as pd
import numpy as np
import plotly.graph_objects as go
import plotly.io as pio
import os

if not os.path.exists("Slike"):
    os.mkdir("Slike")

def line_fit(x, k, l):
    return k*x + l

height = 1.76

df = pd.read_csv('masa.csv')

x, y = df["Dan"], df["Masa"]
masa = [mass for mass in df["Masa"]]
BMI = [mass/(height**2) for mass in df["Masa"]]
df["BMI"] = BMI


k, l = np.polyfit(x, y, 1)
print(f"k = {k}\nl = {l}")


#1. slika
name_m = "Promjena mase u vremenu za A.U."
fig = go.Figure()
fig.add_trace(go.Scatter( x = x, y = y, name = name_m, mode = 'lines'))
fig.add_trace(go.Scatter( x = x, y = line_fit(x, k, l),name = name_m + " linear fit" ,mode = 'lines+markers'))
#legenda
# fig.update_layout(legend=dict(
#     yanchor="top",
#     y=0.99,
#     xanchor="right",
#     x=0.01
# ))

#2. slika
name_BMI = "Promjena BMI u vremenu za A.U." 
fig2 = go.Figure()
fig2.add_trace(go.Scatter( x=x, y=BMI, name=name_BMI))
# fig2.update_layout(legend=dict(
#     yanchor="top",
#     y=0.99,
#     xanchor="right",
#     x=0.01
# ))


print(f"Prvi dan ti je BMI bio {BMI[0]} kg/m^2.\n")
print(f"Zadnji dan ti je BMI jednak {BMI[-1]} kg/m^2.\n")
razlika_BMI = BMI[0] - BMI[-1]
br_dana = len(BMI)
print(f"Razlika u {br_dana} dana je {razlika_BMI} kg/m^2.\n")
razlika_BMI_jucer = BMI[-2] - BMI[-1]
razlika_mase = masa[0] - masa[-1]
razlika_mase_jucer = masa[-2] - masa[-1]
print(f"Početna masa je {masa[0]}.\n")
print(f"Današnja masa je {masa[-1]}.\n")
print(f"Ukupna razlika mase je {razlika_mase}.\n")
if(razlika_BMI_jucer > 0):
    print(f"Bravo, razlika od jučer je {razlika_BMI_jucer} kg/m^2.\n")
    print(f"Razlika mase od jučer je {razlika_mase_jucer} kg.\n")
else:
    print(f"Smrade, skidaj kile ili umri. Udeblja si se od jučer za {razlika_mase_jucer} kg.\n")
    print(f"Razlika BMI od jučer je loša stari: {razlika_BMI_jucer} kg/m^2, smanji hranu pederu. Vježbaj, pička ti materina.")


# fig.show()
# fig2.show()

pio.write_image(fig, "Slike/" + name_m + "_new.png", width=1900, height=1200)
pio.write_image(fig2, "Slike/" + name_BMI + "_new.png", width=1900, height=1200)
