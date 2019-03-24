#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

class Bignum
{
    public:
    Bignum(const string str="0");
    //Bignum(const long long&);
    Bignum(const Bignum& x);
    void construct(string str);
    
    void display();

    friend istream& operator>>(istream&, Bignum&);
    friend ostream& operator<<(ostream&, Bignum&);

    friend Bignum operator+(const Bignum& a,const Bignum& b);
    friend Bignum operator-(const Bignum& a,const Bignum& b);
    friend bool operator>(const Bignum& a,const Bignum&b);
    friend bool operator<(const Bignum& a,const Bignum&b);
    private:
    vector <int>a;
    int symbol;
    
    
};

void Bignum::construct(string str)
{
    int n,i;
    symbol=1;
    n=str.length();
    while(!a.empty())
      a.pop_back();
    if(str[0]=='-')
    {    
        symbol=0;
        for(i=1;i<n;i++)
        a.push_back(str[i]-'0');
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

Bignum operator+(const Bignum& a,const Bignum& b)
{
    Bignum c;
    while(!c.a.empty())
      c.a.pop_back();
    int m,n,sum,k=0,j=0,h,i,t;
    m=a.a.size();
    n=b.a.size();
    if(a.symbol&&b.symbol)
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
    }
    else if(a.symbol==0&&b.symbol==0)
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
    if(a>b)
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
    else
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

bool operator>(const Bignum& a,const Bignum& b)
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
    Bignum c(a+b);Bignum d(a-b);
    cout<<a<<b;
    cout<<c<<endl;
    x=a>b;
    cout<<x<<endl;
    x=a<b;
    cout<<x<<endl;
    cout<<d<<endl;
    return 0;
}