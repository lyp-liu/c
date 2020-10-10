
# coding: utf-8

# In[8]:


# 中国天气网   
# 练习使用 BeautifulSoup 解析
# 数据可视化

import requests
from bs4 import BeautifulSoup
import html5lib
from pyecharts.charts import Bar
ALL_DATA = []

def parse_page(url):
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36"
    }
    response = requests.get(url=url,headers=headers)
    text =response.content.decode("utf-8")
     # 实例化soup对象  主要使用find,find_all定位  获取标签下所有文字stripped_strings
    # 坑 1
    # html5lib 主要是因为 港澳台url里面的数据格式跟其他url里的不一样,table没有闭合标签
    # html5lib 可以自动补全table 的闭合标签
    soup = BeautifulSoup(text,'html5lib')              
    conMidtab = soup.find("div",class_="conMidtab")
    tables = conMidtab.find_all('table')
    for table in tables:
        print("========")
        trs = table.find_all('tr')[2:]
        for index,tr in enumerate(trs):
            tds = tr.find_all('td')
            # 坑 2
            city_td = tds[0] # 拿到的是省份名
            if index == 0:
                city_td = tds[1]
            # 拿到tds[0]这个标签下所有的文字    需要记住获取的方法
            city = list(city_td.stripped_strings)[0] #拿到所有哦的城市名
            
            # 取最低气温标签   取出每个table中的的tr里的最低气温
            temp_td = tds[-2]
            min_temp = list(temp_td.stripped_strings)[0]
            ALL_DATA.append({"city":city,"min_temp":int(min_temp)})
            print({"city":city,"min_temp":int(min_temp)})

def main():
    urls = [
         'http://www.weather.com.cn/textFC/hb.shtml',
         'http://www.weather.com.cn/textFC/db.shtml',
         'http://www.weather.com.cn/textFC/hd.shtml',
         'http://www.weather.com.cn/textFC/hz.shtml',
         'http://www.weather.com.cn/textFC/hn.shtml',
         'http://www.weather.com.cn/textFC/xb.shtml',
         'http://www.weather.com.cn/textFC/xn.shtml',
         'http://www.weather.com.cn/textFC/gat.shtml'
    ]
    for url in urls:
        parse_page(url)

    # 数据分析 根据最低气温排序
    ALL_DATA.sort(key=lambda data:data["min_temp"]) # 通过key指定根据什么排序
    # data 是ALL_DATA列表中每一行的字典数据, 根据data["min_temp"]返回值排序

    data = ALL_DATA[0:10] # 最低气温排前十的城市/区
    cities = list(map(lambda x:x['city'], data))
    temps = list(map(lambda x:x['min_temp'], data))
    chart = Bar()
    # 给这个图取名
    #chart.add(cities,temps,is_more_utils=True)
    chart.add_xaxis(cities)
    chart.add_yaxis("最低气温表",temps)
    chart.render('temperature.html')

if __name__ == '__main__':
    main()

