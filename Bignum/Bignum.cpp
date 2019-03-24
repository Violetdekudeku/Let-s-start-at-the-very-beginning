#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

class Bignum
{
    public:
    Bignum(const string str="0");//构造函数
    Bignum(const Bignum& x);//复制构造函数
    void construct(string str);//成员函数，转化成大数类对象
    
    void display();//成员函数，输出对象

    friend istream& operator>>(istream&, Bignum&);
    friend ostream& operator<<(ostream&, Bignum&);

    friend Bignum operator+(const Bignum& a,const Bignum& b);
    friend Bignum operator*(const Bignum& a,const Bignum& b);
    friend Bignum operator-(const Bignum& a,const Bignum& b);
    friend bool operator>(const Bignum& a,const Bignum&b);
    friend bool operator<(const Bignum& a,const Bignum&b);
    private:
    vector <int>a;
    int symbol;//代表了大数对象的符号 
};

void Bignum::construct(string str)
{
    int n,i;
    symbol=1;
    n=str.length();
    while(!a.empty())//清空向量中初始化的0
      a.pop_back();
    if(str[0]=='-')
    {    
        symbol=0;
        for(i=1;i<n;i++)
        a.push_back(str[i]-'0');//字符转化为整数int
    }
    else 
    {
        for(i=0;i<n;i++)
        a.push_back(str[i]-'0');
    }
}

void Bignum::display()
{
    int n,i=0;
    n=a.size();
    if(symbol==0)
    cout<<'-';
    while(i<n)
    {
        cout<<a.at(i);
        i++;
    }
    cout<<endl;
}

Bignum::Bignum(const Bignum& x)
{
    symbol=x.symbol;
    a=x.a;
}

Bignum::Bignum(const string str)
{
    int n,i;
    
    n=str.length(); 
    symbol=1;  
    if(str[0]=='-')
    {    symbol=0;
    for(i=1;i<n;i++)
        a.push_back(str[i]-'0');
    }
    else
    {
        for(i=0;i<n;i++)
        a.push_back(str[i]-'0');
    }
    
}

istream& operator>>(istream& in,Bignum& x)
{
    string str;
    in>>str;
    x.construct(str);
    
    return in;
}

ostream& operator<<(ostream& out, Bignum& x)
{
    x.display();
    
    return out;
}

//两个整数之间（正负）做加减运算，一共有2*2*2=8八种，输入注意格式，共可以转化成三种分别为：两个正数相加，两个负数相加，两个正数相减
Bignum operator+(const Bignum& a,const Bignum& b)
{
    Bignum c;
    while(!c.a.empty())
      c.a.pop_back();
    int m,n,sum,k=0,j=0,h,i,t;
    m=a.a.size();
    n=b.a.size();
    if(a.symbol&&b.symbol)//当两个大数对象都为正时
    {
        while(m--&&n--)//从最后一位开始相加，值得注意的是：如果&&前面的条件已经为否的话，&&后面的条件就不会执行了
    {
        sum=j+a.a.at(m)+b.a.at(n);//j记录进位数，k记录保留数
        k=sum%10;
        j=sum/10;
        c.a.push_back(k);
    }
    if(m==-1&&n==0)//分类共三种：1.两个对象位数相同
    {
        if(j)
            c.a.push_back(1);
        j=0;
    }
    else if(m==-1&&n>0)//2.第二个对象位数长
    {
        while(n--)//把剩下的位数填充进去
        {
            sum=j+b.a.at(n);
            k=sum%10;
            j=sum/10;
            c.a.push_back(k);
        }
        if(j)
            c.a.push_back(1);
    }
    else//3.第一个对象位数长
    {
        while(m>-1)
        {
            sum=j+a.a.at(m);
            k=sum%10;
            j=sum/10;
            c.a.push_back(k);
            m--;
        }
        if(j)
            c.a.push_back(1);
            
    }
    h=c.a.size();
    for(i=0;i<h/2;i++)//h记录位数，倒序变为正序
    {
        t=c.a.at(i);c.a.at(i)=c.a.at(h-1-i);c.a.at(h-1-i)=t;
    }
    }
    else if(a.symbol==0&&b.symbol==0)//两个大数对象都为负时
    {
        while(m--&&n--)
    {
        sum=j+a.a.at(m)+b.a.at(n);
        k=sum%10;
        j=sum/10;
        c.a.push_back(k);
    }
    if(m==-1&&n==0)
    {
        if(j)
            c.a.push_back(1);
        j=0;
    }
    else if(m==-1&&n>0)
    {
        while(n--)
        {
            sum=j+b.a.at(n);
            k=sum%10;
            j=sum/10;
            c.a.push_back(k);
        }
        if(j)
            c.a.push_back(1);
    }
    else
    {
        while(m>-1)
        {
            sum=j+a.a.at(m);
            k=sum%10;
            j=sum/10;
            c.a.push_back(k);
            m--;
        }
        if(j)
            c.a.push_back(1);
            
    }
    
    h=c.a.size();
    for(i=0;i<h/2;i++)
    {
        t=c.a.at(i);c.a.at(i)=c.a.at(h-1-i);c.a.at(h-1-i)=t;
    }
    c.symbol=0;
    }
    return c;
}

Bignum operator-(const Bignum& a,const Bignum& b)
{
    Bignum c;int m,n;int i,j;int h,t;
    while(!c.a.empty())
        c.a.pop_back();
    m=a.a.size();n=b.a.size();
    if(a>b)//调用重载运算符>函数，如果a>b，c为正
    {
        c.symbol=1;
        Bignum d(a);
        for(i=m-1,j=n-1;i>-1&&j>-1;i--,j--)
        {
            if(d.a.at(i)>=b.a.at(j))
                c.a.push_back(d.a.at(i)-b.a.at(j));
            else
            {
                c.a.push_back(d.a.at(i)+10-b.a.at(j));
                h=i-1;
                while(d.a.at(h)==0)
                {
                    d.a.at(h)=9;
                    h--;
                }
                d.a.at(h)--;
            }
        }
        while(i>-1)
        {
            c.a.push_back(d.a.at(i));
            i--;
        }
    }
    else//如果a<b,c为负
    {
        c.symbol=0;
        Bignum d(b);
        for(i=m-1,j=n-1;i>-1&&j>-1;i--,j--)
        {
            if(d.a.at(j)>=a.a.at(i))
                c.a.push_back(d.a.at(j)-a.a.at(i));
            else
            {
                c.a.push_back(d.a.at(j)+10-a.a.at(i));
                h=j-1;
                while(d.a.at(h)==0)
                {
                    d.a.at(h)=9;
                    h--;
                }
                d.a.at(h)--;
            }
            
        }
        while(j>-1)
        {
            c.a.push_back(d.a.at(j));
            j--;
        }
    }
    h=c.a.size();
    for(i=0;i<h/2;i++)
    {
        t=c.a.at(i);c.a.at(i)=c.a.at(h-1-i);c.a.at(h-1-i)=t;
    }
    return c;
}

Bignum operator*(const Bignum& a,const Bignum& b)
{
    Bignum c;int m,n,k;int i,j;int t;
    if(a.symbol*b.symbol)//有a和b确定c的符号
        c.symbol=1;
    else
        c.symbol=0;
    
    while(!c.a.empty())
        c.a.pop_back();
    Bignum d(a);Bignum e(b);d.symbol=a.symbol;e.symbol=b.symbol;    
    m=a.a.size();n=b.a.size();
    for(i=0;i<m/2;i++)
    {    
        t=d.a.at(i);d.a.at(i)=d.a.at(m-1-i);d.a.at(m-1-i)=t;//做乘法运算时，从数的最后一位开始运算，所以将大数倒序
    }
    for(j=0;j<n/2;j++)
    {
        t=e.a.at(j);e.a.at(j)=e.a.at(n-1-j);e.a.at(n-1-j)=t;
    }
    //先把c初始化一下
    c.a.resize(m+n-1);//重新分配向量的存储空间，否则越界
    for(i=0;i<m+n-1;i++)
        c.a.at(i)=0;
    //现在把大数a当作乘数
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            c.a.at(i+j)+=d.a.at(i)*e.a.at(j);

    j=0;
    for(i=0;i<m+n-1;i++)//n记录暂时的大数c的位数
    {
        k=(j+c.a.at(i))%10;//k记录保留的数字
        j=(j+c.a.at(i))/10;//j记录进位数
        c.a.at(i)=k;
    }
    while(j!=0)//把剩下的进位填充
    {
        c.a.at(i)=j%10;
        j=j/10;
        i++;
    }
    
    for(j=0;j<i/2;j++)
    {    
        t=c.a.at(j);c.a.at(j)=c.a.at(i-1-j);c.a.at(i-1-j)=t;
    }
    
    return c;
}

bool operator>(const Bignum& a,const Bignum& b)//先比较符号，再比较位数，再比较每位的大小
{
    if(a.symbol>b.symbol)
    return true;
    else if(a.symbol<b.symbol)
    return false;
    else if(a.symbol==1&&b.symbol==1)
    {
        int m,n;
        m=a.a.size();n=b.a.size();
        if(m>n)
            return true;
        else if(m<n)
            return false;
        else
        {
            for(int i=0;i<n;i++)
            {
                if(a.a.at(i)!=b.a.at(i))
                    if(a.a.at(i)>b.a.at(i))
                        return true;
                    else
                        return false;
                        
                    
            }
        }
        
    }
    else if(a.symbol==0&&b.symbol==0)
    {
        int m,n;
        m=a.a.size();n=b.a.size();
        if(m>n)
            return false;
        else if(m<n)
            return true;
        else
        {
            for(int i=0;i<n;i++)
            {
                if(a.a.at(i)!=b.a.at(i))
                    if(a.a.at(i)>b.a.at(i))
                        return false;
                    else
                        return true;
                        
                    
            }
        }
    }
}

bool operator<(const Bignum& a,const Bignum& b)
{
    bool x;
    x=a>b;
    if(x==false)
        return true;
    else 
        return false;
}

int main()
{
    bool x;
    Bignum a;
    Bignum b;
    cin>>a>>b;
    Bignum c(a+b);Bignum d(a-b);Bignum e(a*b);//加法和减法不能一起用，除非是两个正数，我继续改
    cout<<a<<b;
    cout<<c<<endl;
    x=a>b;
    cout<<x<<endl;
    x=a<b;
    cout<<x<<endl;
    cout<<d<<endl;
    cout<<e<<endl;
    return 0;
}