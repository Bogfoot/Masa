import pandas as pd
import numpy as np
import plotly.graph_objects as go
import plotly.io as pio
import os
import math

np.set_printoptions(precision=3, suppress=False)

if not os.path.exists("Slike"):
    os.mkdir("Slike")


def line_fit(x, k, l):
    return k * x + l


def rolling_median(mase, br_dana):
    br_mj = int(len(mase) / br_dana) + 1
    average_br_dana = []
    for i in range(br_mj):
        if len(mase[i * br_dana :]) <= br_dana:
            average_br_dana.append(np.mean(mase[i * br_dana :]))
        else:
            average_br_dana.append(np.mean(mase[i * br_mj : i * br_mj + br_dana]))
    return np.array(average_br_dana)


def newDate(df):
    return pd.to_datetime(df["Dan"], format="%d.%m.%Y", dayfirst=True)


height = 1.76
df = pd.read_csv("masa.csv")
df["Dan"] = newDate(df)
df["Dan"] = df["Dan"].dt.date
x, y = df["Dan"], df["Masa"]
masa = np.array([mass for mass in df["Masa"]])
BMI = np.array([mass / (height**2) for mass in masa])
df["BMI"] = BMI

k, l = np.polyfit(np.linspace(0, len(y), len(y)), df["Masa"], 1)
print(f"k = {k}\n\nl = {l}")

# 1. slika
name_m = "Promjena mase u vremenu za A.U."
fig = go.Figure()
fig.add_trace(go.Scatter(x=df["Dan"], y=df["Masa"], name=name_m))
fig.add_trace(
    go.Scatter(
        x=df["Dan"],
        y=line_fit(df["Masa"], k, l),
        name=name_m + " linear fit",
        mode="markers",
    )
)
# 2. slika
name_BMI = "Promjena BMI u vremenu za A.U."
fig2 = go.Figure()
fig2.add_trace(go.Scatter(x=x, y=BMI, name=name_BMI))

pio.write_image(fig, "Slike/" + name_m + ".png", width=2000, height=2000)
pio.write_image(fig2, "Slike/" + name_BMI + ".png", width=2000, height=2000)

# Output
print(f"Prvi dan ti je BMI bio {round(BMI[0],2)} kg/m^2.\n")
print(f"Danas ti je BMI jednak {round(BMI[-1],2)} kg/m^2.\n")
razlika_BMI = BMI[0] - BMI[-1]
br_dana = len(BMI)
print(f"Razlika u {br_dana} dana je {round(razlika_BMI,2)} kg/m^2.\n")
razlika_BMI_jucer = BMI[-2] - BMI[-1]
razlika_mase = masa[0] - masa[-1]
razlika_mase_jucer = masa[-2] - masa[-1]
print(f"Početna masa je {round(masa[0],2)}.\n")
print(f"Današnja masa je {round(masa[-1],2)}.\n")
print(f"Ukupna razlika mase je {round(razlika_mase,2)}.\n")
print(f"Najniža masa je {min(masa)} kg.\n")
print(f"Najniži BMI je {round(min(BMI),2)} kg/m^2.\n")


# if mass is higher, lower, or equal to the day before -> Do something
if razlika_BMI_jucer > 0:
    print(f"Bravo, razlika od jučer je {round(razlika_BMI_jucer,2)} kg/m^2.\n")
    print(f"Razlika mase od jučer je {round(razlika_mase_jucer,2)} kg.\n")
elif razlika_BMI_jucer == 0:
    print(
        f"Smrade, skidaj kile ili umri. Nisi se udeblja danas al u pičku materinu, vježbaj konju glupi.\n"
    )
    print(f"Razlika BMI od jučer je {round(razlika_BMI_jucer,2)} kg/m^2\n")
else:
    print(
        f"Smrade, skidaj kile ili umri. Udeblja si se od jučer za {-round(razlika_mase_jucer,2)} kg.\n"
    )
    print(
        f"Razlika BMI od jučer je loša stari: {round(razlika_BMI_jucer,2)} kg/m^2, smanji hranu pederu. Vježbaj, pička ti materina.\n"
    )


# y = k*x + l Line fit from before
# x = (y-l)/k
X = 85
br_d_do_X = (X - l) / k - br_dana
print(
    f"Broj dana do {X} kg je cca.: {round(br_d_do_X,2)} tj. ({round(br_d_do_X/7,2)} tjedana.)\n"
)

average_br_dana = rolling_median(masa, 5)
average_br_dana = [x for x in average_br_dana if math.isnan(x) == False]
print(f"Srednja masa prvi misec je {round(average_br_dana[0],2)}kg.\n")
if len(masa) >= 60:
    print(f"Srednja masa prošli misec je {round(average_br_dana[-2],2)}kg.\n")
elif len(masa) >= 30:
    print(f"Srednja masa ovaj misec je {round(average_br_dana[-1],2)}kg.\n")
