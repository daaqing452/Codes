//--------------------math--------------------

template<class T>inline T gcd(T a,T b){return!b?a:gcd(b,a%b);}
template<class T>inline T egcd(T a,T b,T c,T &x,T &y){if(!b){x=c/a;y=0;return;}egcd(b,a%c,c,x,y);T s=y;T t=x-a/b*y;x=s;y=t;}
template<class T>inline T egcd2(T n,T a,T b,T c){if(!n||!c)return 0;T s=a/c*n+b/c*n*(n-1)/2;a%=c;b%=c;return s+egcd2((a+b*n)/c,(a+b*n)%c,c,b);}
//inline void getInv(int N,int mod){inv[1]=1;for(int i=2;i<=N;++i)inv[i]=((-(int64)mod/i*inv[mod%i])%mod+mod)%mod;}
//void getPrime(int N){for(int i=2;i<=N;++i){if(!pp[i])p[++P]=pp[i]=i;for(int j=1;j<=P&&i*p[j]<=N;++j){pp[i*p[j]]=p[j];if(i%p[j]==0)break;}}}

//--------------------math--------------------
