# -*- coding: utf-8 -*-
from click import style
import pandas as pd
import matplotlib.pyplot as plt
import casefoam
import seaborn as sns

sns.set_style("ticks")

caseStructure = [['isoAlpha', 'plicRDF','MULES'],
                ['CFL005', 'CFL01', 'CFL02', 'CFL05'],
                ['x010', 'x020', 'x040', 'x080', 'x160', 'x320', 'x640']]

baseCase = 'Cases'
solutionDir = 'volumeFractionError/0'
file = 'volumeFractionError.dat'

error = casefoam.time_series(solutionDir,file,caseStructure,baseCase)
error = error.reset_index("t")

error = error[error["t"] == 0.5]
error = error.rename(columns={"var_0": "Model", "var_1": "CFL", "var_2": "Res"})
error = error.rename(columns={1: "E1", 2: "Emass", 3: "Ebound", 8 : "delta"}) # delta = avg cell dist

error["nCells"] = 1/error["delta"] # domain size is 1
error['Res'] = error['Res'].str.replace('x', '')
error['Res'] = error['Res'].apply(pd.to_numeric)
# error = error.set_index(["var_0","var_1","var_2"])
print("error",error)
error.to_csv("error.csv",index=False)
sns.lineplot(x="Res", y="E1",markers=True,hue="Model",style="CFL",data=error)
plt.xscale('log')
plt.yscale('log')
plt.savefig("error.png")
# plt.show()

