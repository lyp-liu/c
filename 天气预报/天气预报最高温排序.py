
# coding: utf-8

# In[8]:


import requests
from bs4 import BeautifulSoup



'''
#网页的解析函数，分析网页看能否解析出需要的信息结构
def parse_page(url):
    headers = {
        'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) '
                     'AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.102 Safari/537.36'
    }
    response = requests.get(url,headers=headers)
    text = response.content.decode('utf-8')
    soup = BeautifulSoup(text,'html.parser')
    conMidtab = soup.find('div',class_ = 'conMidtab')
    print(conMidtab)#打印输出看输出是否符合条件
 
def main():
    url = 'http://www.weather.com.cn/textFC/db.shtml'
    parse_page(url)
if __name__ == '__main__':
    main()


# In[14]:


#网页的解析函数，分析网页看能否解析出需要的信息结构,huoquchengshixinxi 
def parse_page(url):
    headers = {
        'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) '
                     'AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.102 Safari/537.36'
    }
    response = requests.get(url,headers=headers)
    text = response.content.decode('utf-8')
    soup = BeautifulSoup(text,'lxml')
    conMidtab = soup.find('div',class_ = 'conMidtab')
    tables = conMidtab.find_all('table')
    #查看是否拿到了每个城市的天气
    for table in tables:
        print(table)
        print('=' * 30)


# In[13]:


#查看是否拿到了每个城市的天气
for table in tables:
        trs = table.find_all('tr')[2:]
        for tr in trs:
            print(tr)
            print('='*30)
        break


# In[15]:


import requests
from bs4 import BeautifulSoup
import matplotlib.pyplot as plt
 
ALL_DATA = []
 
#网页的解析函数
def parse_page(url):
    headers = {
        'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) '
                     'AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.102 Safari/537.36'
    }
    response = requests.get(url,headers=headers)
    text = response.content.decode('utf-8')
    soup = BeautifulSoup(text,'html5lib')#由于html5lib容错性较好因此用它不用lxml
    conMidtab = soup.find('div',class_ = 'conMidtab')
    tables = conMidtab.find_all('table')
    #查看是否拿到了每个城市的天气
    for table in tables:
        trs = table.find_all('tr')[2:]
        for index,tr in enumerate(trs):
            tds = tr.find_all('td')
            city_td = tds[0]
            if index == 0:
                city_td = tds[1]
            city = list(city_td.stripped_strings)[0]#获取标签里面的字符串属性返回一个生成器,因此要转化为一个列表
            temp_td = tds[-5]
            min_temp = list(temp_td.stripped_strings)[0]
            ALL_DATA.append({'城市':city,'最高气温':int(min_temp)})#将数据添加到列表当作
 
def main():
    urls = [
        'http://www.weather.com.cn/textFC/hb.shtml',
        'http://www.weather.com.cn/textFC/db.shtml',
        'http://www.weather.com.cn/textFC/hz.shtml',
        'http://www.weather.com.cn/textFC/hn.shtml',
        'http://www.weather.com.cn/textFC/hd.shtml',
        'http://www.weather.com.cn/textFC/xb.shtml',
        'http://www.weather.com.cn/textFC/xn.shtml',
        'http://www.weather.com.cn/textFC/gat.shtml'
    ]
for url in urls:
        parse_page(url)
if __name__ == '__main__':
    main()
    # 分析数据，根据最低气温进行排序
    
    


# In[2]:


import requests
from bs4 import BeautifulSoup
import html5lib
from pyecharts.charts import Bar
 
#网页的解析函数
def parse_page(url):
    headers = {
        'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) '
                     'AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.102 Safari/537.36'
    }
    response = requests.get(url,headers=headers)
    text = response.content.decode('utf-8')
    soup = BeautifulSoup(text,'html5lib')#由于html5lib容错性较好因此用它不用lxml
    conMidtab = soup.find('div',class_ = 'conMidtab')
    tables = conMidtab.find_all('table')
    #查看是否拿到了每个城市的天气
    for table in tables:
        trs = table.find_all('tr')[2:]
        for index,tr in enumerate(trs):
            tds = tr.find_all('td')
            city_td = tds[0]
            if index == 0:
                city_td = tds[1]
            city = list(city_td.stripped_strings)[0]#获取标签里面的字符串属性返回一个生成器,因此要转化为一个列表
            temp_td = tds[-5]
            min_temp = list(temp_td.stripped_strings)[0]
            print({'城市':city,'最高气温':min_temp})
 
def main():
    urls = [
        'http://www.weather.com.cn/textFC/hb.shtml',
        'http://www.weather.com.cn/textFC/db.shtml',
        'http://www.weather.com.cn/textFC/hz.shtml',
        'http://www.weather.com.cn/textFC/hn.shtml',
        'http://www.weather.com.cn/textFC/hd.shtml',
        'http://www.weather.com.cn/textFC/xb.shtml',
        'http://www.weather.com.cn/textFC/xn.shtml',
        'http://www.weather.com.cn/textFC/gat.shtml'
    ]
    for url in urls:
        parse_page(url)
if __name__ == '__main__':
    main()
'''

# In[5]:


import requests
from bs4 import BeautifulSoup
#import html5lib
#from pyecharts.charts import Bar
import matplotlib.pyplot as plt
ALL_DATA = []
#网页的解析函数
def parse_page(url):
    headers = {
        'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) '
                     'AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.102 Safari/537.36'
    }
    response = requests.get(url,headers=headers)
    text = response.content.decode('utf-8')
    soup = BeautifulSoup(text,'html5lib')#由于html5lib容错性较好因此用它不用lxml
    conMidtab = soup.find('div',class_ = 'conMidtab')
    tables = conMidtab.find_all('table')
    #查看是否拿到了每个城市的天气
    for table in tables:
        trs = table.find_all('tr')[2:]
        for index,tr in enumerate(trs):
            tds = tr.find_all('td')
            city_td = tds[0]
            if index == 0:
                city_td = tds[1]
            city = list(city_td.stripped_strings)[0]#获取标签里面的字符串属性返回一个生成器,因此要转化为一个列表
            temp_td = tds[-5]
            #print(temp_td)
            max_temp = list(temp_td.stripped_strings)[0]

            #print({'城市':city,'最高气温':min_temp})
            ALL_DATA.append({'城市': city, '最高气温': int(max_temp)})  # 将数据添加到列表当作
            print({'城市': city, '最高气温': max_temp})
           # print(ALL_DATA);
 
def main():
    urls = [
        'http://www.weather.com.cn/textFC/hb.shtml',
        'http://www.weather.com.cn/textFC/db.shtml',
        'http://www.weather.com.cn/textFC/hz.shtml',
        'http://www.weather.com.cn/textFC/hn.shtml',
        'http://www.weather.com.cn/textFC/hd.shtml',
        'http://www.weather.com.cn/textFC/xb.shtml',
        'http://www.weather.com.cn/textFC/xn.shtml',
        'http://www.weather.com.cn/textFC/gat.shtml'
    ]
 
    for url in urls:
        parse_page(url)
    # 分析数据，根据最低气温进行排序
    #print(type(ALL_DATA))
    ALL_DATA.sort(key=lambda data:data['最高气温'],reverse=True)
    data = ALL_DATA[0:10]#取出前10的最高气温及其城市

    #data.reverse();
    #print(data);
    return data
 
if __name__ == '__main__':
    datas = main()
    city = []
    temp = []
    plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
    plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号
    for data in datas:
        city.append(data['城市'])
        temp.append(data['最高气温'])
    #city.reverse();
    #temp.reverse();
   # print(temp);
    #range(len(city))
    #plt.ylim(-2,20);
    #plt.ylim(-5,20)
    plt.bar(range(len(city)),temp,tick_label=city)
   # y_major_locator=MultipleLocator(2);

    plt.show()

