import pandas
df = pandas.read_excel("./finance.xlsx", sheet_name=0)
df["交易额"] = df["交易额"].fillna(0)
res = df.groupby("日期")["交易额"].sum()
res = res.sort_values().head(3)
for date, finance in res.items():
    print(date, int(finance), pandas.to_datetime(date).day_name())