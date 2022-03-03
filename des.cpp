#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

map<ll,vector<ll>>invSBox;
map<ll,map<ll,ll>>invXorMap;

/* E BIT_SELECTION TABLE */
int E[] = {
  32, 1, 2, 3, 4, 5,
  4, 5,6, 7, 8, 9,
  8, 9, 10, 11, 12, 13,
  12, 13, 14, 15, 16, 17, 
  16, 17, 18, 19, 20, 21, 
  20, 21, 22, 23, 24, 25, 
  24, 25, 26, 27, 28, 29,
  28, 29, 30, 31, 32, 1
};

/* Inverse of E */
int INV_E[] = {
  2, 3, 4, 5, 
  6, 9, 10, 11, 
  12, 15, 16, 17, 
  18, 21, 22, 23, 
  24, 27, 28, 29, 
  30, 33, 34, 35, 
  36, 39, 40, 41, 
  42, 45, 46, 1 
};

/* PERMUTATION FUNCTION P */
int P[] = {
  16, 7, 20, 21, 
  29, 12, 28, 17,
  1, 15, 23, 26,
  5, 18, 31,10,
  2, 8, 24, 14,
  32, 27, 3, 9,
  19, 13, 30, 6,
  22, 11, 4, 25,
};

/* Inverse of P */
int INV_P[] = {
	9, 17, 23, 31,
	13, 28, 2, 18,
	24, 16, 30, 6,
	26, 20, 10, 1,
	8, 14, 25, 3,
	4, 29, 11, 19,
	32, 12, 22, 7,
	5, 27, 15, 21,
};

ll e(ll r)
{
        ll res=0;
        for(int i=0;i<48;i++)
                res|=((r>>(E[i]-1))&1)<<i;;
        return res;
}

ll invE(ll alpha)
{
        ll r=0;
        for(int i=0;i<32;i++)
                r|=((alpha>>(INV_E[i]-1))&1)<<i;
        return r;
}
ll s(ll b)
{
        vector<int>bBits;
        while(bBits.size()<6)
        {
                bBits.push_back(b%2);
                b/=2;
        }
        reverse(bBits.begin(),bBits.end());
        int res;        
        res=bBits[0]^(bBits[1]&bBits[2]&bBits[3]);
        res<<=1;
        res+=bBits[5]^(bBits[2]&bBits[3]&bBits[4]);
        res<<=1;
        res+=bBits[0]^(bBits[1]&bBits[3]&bBits[4]);
        res<<=1;
        res+=bBits[5]^(bBits[1]&bBits[2]&bBits[4]);
        return res;
}
ll getS(ll b)
{
        vector<int>group(8);
        for(int i=0;i<8;i++)
        {
                for(int j=0;j<6;j++)
                        group[i]=group[i]*2+((b>>(48-i-8*j-1))&1);
        }
        ld probability=1;
        for(int i=0;i<8;i++)
        {
                int mxCnt=0;
                int val=0;
                for(auto i:invXorMap[group[i]])
                {
                }
        }
        return 1;
}
ll p(ll y)
{
        ll x=0;
        for(int i=0;i<32;i++)
                x|=((y>>(P[i]-1))&1)<<i;
        return x;
}

ll invP(ll x)
{
        ll y=0;
        for(int i=0;i<32;i++)
                y|=((x>>(INV_P[i]-1))&1)<<i;
        return y;
}
void getInvMap()
{
        for(int i=0;i<(1<<6);i++)
        {
                for(int j=0;j<(1<<4);j++)
                {
                        if(s(i)==j)
                                invSBox[j].push_back(i);
                }
        }
}
void printInvSBox()
{
        cout<<"Inverse mapping"<<endl;
        for(auto i:invSBox)
        {
                cout<<bitset<4>(i.first).to_string()<<" -> ";
                for(auto j:i.second)
                        cout<<bitset<6>(j).to_string()<<" ";
                cout<<endl;
        }
        cout<<endl;
}
void getXorMap()
{
        for(int i=0;i<(1<<6);i++)
        {
                for(int j=0;j<(1<<6);j++)
                        invXorMap[i^j][s(i)^s(j)]++;
        }
}
void printXorMap()
{
        cout<<"XOR Map"<<endl;
        cout<<"b^b' -> {s(b)^s(b'), count}"<<endl;
        for(auto i:invXorMap)
        {
                cout<<"{"<<bitset<6>(i.first)<<"} -> ";
                for(auto j:i.second)
                        cout<<"["<<bitset<4>(j.first)<<","<<j.second<<"] ";
                cout<<endl;
        }
        cout<<endl;
}
int main()
{
        getInvMap();
        printInvSBox();
        getXorMap();
        printXorMap();
        ld expectedSize=0;
        for(auto i:invXorMap)
        {
                for(auto j:i.second)
                        expectedSize+=((ld)j.second/i.second.size())/64;;
        }
        cout<<expectedSize<<endl;
        ll x=(1<<2);
        ll l_0=invE(x);
        ll r_0=0;
        cout<<e(l_0)<<endl;
        ll l_1=r_0;
        ll r_1=l_0;
        cout<<l_1<<" "<<r_1<<endl;
        cout<<bitset<48>(e(r_1))<<endl;
        return 0;
}
