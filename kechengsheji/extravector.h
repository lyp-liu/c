#ifndef EXTRAVECTOR_H
#define EXTRAVECTOR_H
#include<iostream>
using namespace std;
template<typename T>
class extravector{
    T* m_data;
    int m_size;                                   //计数目前数组元素的个数
    int new_size;                                 //计数数组开辟的总长度
public:
    extravector() :m_size(0),new_size(740) {
        m_data=new T[740];
    }
    ~extravector() { delete[] m_data; }
    extravector(int n, const T &val);                //构造
    extravector(const extravector &rhs);                //复制构造
    const int _size(){ return m_size; }           //获取容器数组元素个数
    void resize(int n);                           //改变数组元素个数
    bool empty() { return m_size; }               //容器是否为空
    void clear();                                 //清除数组元素
    void push_back(const T&x);                    //在最后添加数组
    void pop_back();                              //删除最后一个数组
    extravector<T>& operator=(const extravector<T>& t); //重载赋值运算符
    const T& at(int i)const;                      //搜索并返回编号
    T& front() { return m_data[0]; }              //返回第一个要素
    T& back() { return m_data[m_size - 1]; }      //返回最后一个
    void show();
    void sort();                                  //快速排序
    bool insert(const T& x, int i);
    bool erase(int i);
    T& operator[](int i) { return m_data[i]; }
    T& operator[](int i)const { return m_data[i]; }
    int binarySearch(const T& value);             //二分查找
private:
    void quickSort(int, int);
    bool Is_Sort();                               //是否有序
    void change(T&, T&);
};

template <typename T>//构造函数
extravector<T>::extravector(int n,const T &val)
    :m_size(n),
      new_size(m_size)
{
    m_data = new T[m_size+1];
    for (int i = 0; i < m_size; i++)
        m_data[i] = val;
}


template<typename T>
extravector<T>::extravector(const extravector& rhs) {//复制构造
    m_size = rhs.m_size;
    new_size=m_size;
    m_data = new T[740];
    for (int i = 0; i < m_size; i++)
        m_data[i] = rhs[i];
}

template<typename T>
void extravector<T>::resize(int n) {
  /*  if (n < m_size) {
        for (int i = n; i < m_size; i++)
            m_data.erase(i);
    }
    else if (n > m_size) {
        myVector<T> loc_1(*this);
        delete[] m_data;
        m_data = new T[n + 1];
        *this = loc_1;
    }*/
    m_size = n;
}

template<typename T>
bool extravector<T>::insert(const T& x, int i) {//插入数据
    if (i<0 || i >= m_size)return false;
   extravector loc_1(*this);
    delete[] m_data;
    m_size++;
    m_data = new  T[m_size + 1];
    for (int j = 0; j < i; j++)
        m_data[j] = loc_1.m_data[j];
    m_data[i] = x;
    for (int j = i + 1; j < m_size; j++)
        m_data[j] = loc_1.m_data[j - 1];
    return true;
}

template<typename T>
bool extravector<T>::erase(int i) {
    if (i<0 || i >= m_size)return false;
    for (int j = i; j <= m_size; j++)
        m_data[j] = m_data[j + 1];
    m_size--;
    return true;
}

template<typename T>
void extravector<T>::clear() {
    delete[] m_data;
    m_data = nullptr;
    m_size = 0;
    new_size=0;
}

template<typename T>
void extravector<T>::push_back(const T&x) {
    if (m_size<new_size)
        m_data[m_size++] = x;
    else {
        new_size = m_size != 0 ? 2 * m_size : 1;
        extravector V(*this);
        delete[] m_data;
        m_data = new T[new_size];
        *this = V;

        m_data[m_size++] = x;
    }
}


template<typename T>
void extravector<T>::pop_back() {
    erase(m_size - 1);
}


template<typename T>
const T& extravector<T>::at(int i)const {
    static T t = T();
    if (i >= m_size || i < 0) {
        cout << "out of range!" << endl;
        return t;
    }
    else return (*this)[i];
}

template<typename T>
extravector<T>& extravector<T>::operator=(const extravector<T>& t) {
    if (this == &t)return *this;
    delete[] m_data;
    m_size = t.m_size;
    m_data = new T[m_size + 1];
    for (int i = 0; i < m_size; i++) {
        m_data[i] = t.m_data[i];
    }
    return *this;
}

template<typename T>//outputscore界面中的显示函数
void extravector<T>::show() {
    for (int i = 0; i < m_size; i++)
        cout << m_data[i] << endl;
}

template<typename T>
void extravector<T>::sort() {
    if (this->Is_Sort())return;//有序返回，无序排序
    else {
        for (int i = 0; i < m_size; i++)
            for (int j = i + 1; j < m_size; j++)
                if (m_data[j] < m_data[i])
                    change(m_data[i], m_data[j]);
    }
}

template<typename T>
void extravector<T>::change(T&A, T&B) {//换位函数
    T C(A);
    A = B;
    B = C;
}
template<typename T>
bool extravector<T>::Is_Sort() {//判断是否有序
    for (int i = 0; i < m_size - 1; i++)
        if (m_data[i+1] < m_data[i])
            return false;
    return true;
}
template<typename T>
int extravector<T>::binarySearch(const T& value) {//二分查找
    int start = 0;
    int end = m_size - 1;
    int mid = -1;
    while (start <= end) {
        mid = (start + end) / 2;
        if (value < m_data[mid])end = mid - 1;
        else if (m_data[mid] < value)start = mid + 1;
        else return mid;
    }
    if (mid != -1 && m_data[mid - 1] != value)mid = -1;
    return mid;
}


template<typename T>
void extravector<T>::quickSort(int begin, int end) {
    if (m_data + begin == m_data + end)
        return;
    int standard = *(m_data + begin);
    int _l = begin, _r = end;          //记录变量l和r的下标
    int *l = m_data + _l;
    int *r = m_data + _r;
    while (l < r) {
        while (l<r&&*r>standard) {
            r--;
            _r--;
        }
        if (l < r) {
            *(l++) = *r;
            _l++;
        }
        while (l < r&&*l < standard) {
            l++;
            _l++;
        }
        if (l < r) {
            *(r--) = *l;
            _r--;
        }
    }
    *l = standard;
    quickSort(begin, _l);
    quickSort(_l + 1, end);
}

#endif // EXTRAVECTOR_H
