/*
	-----Name-----
		���θ߾��ȳ˷� Karatsuba Algorithm
	
	-----Work-----
		����˼��
		���߾�����a��bƽ�����2��
			a = x * P + w
			b = z * P + y
			P = 10^p
		��r = a * b = (x * P + w) * (z * P + y)
		              = x * z * P^2 + (x * y + w * z) * P + w * y
			      = (x * z) * P^2 + ((x + w) * (z + y) - (x * z) - (w * y)) * P + (w * y)
		����ֻ����μ���
			x * z
			w * y
			(x + w) * (z + y)
		�Ĵ𰸣����ɵõ�r
	
	-----Time-----
		ÿ�ν�����ΪN���������������ΪN/2����
		������Ҫ��log2(N)��
		ÿ����Ҫ���õݹ�3��
		��˸��Ӷ���
			  log2(N)     log2(3)     1.58496
			3         = N         �� N
*/
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;


typedef	long long	int64;
typedef	vector<int64>	vectori;


//ѹ��10^16һλ
const	int64	MOD = 10000000000000000ll;
const	int64	MOE = 100000000;


//���vector����Ļ
void	print(vectori& z)
{
	for (int i = z.size() - 1; i >= 0; -- i) cerr << z[i];
	cerr << endl;
}

vectori	work(vectori& a, vectori& b)
{
	//ȥǰ��0
	for (; a.size() && !a[a.size() - 1]; ) a.pop_back();
	for (; b.size() && !b[b.size() - 1]; ) b.pop_back();
	
	//�����ȣ�������ż����1���У�����ȫ����
	int	L = max(a.size(), b.size());
	if (!L) L = 1;
	if (L > 1 && (L & 1)) L ++;
	for (; a.size() < L; ) a.push_back(0);
	for (; b.size() < L; ) b.push_back(0);
	
	int	L2 = L >> 1;
	
	//���г���Ϊ1
	if (L == 1)
	{
		//a = x * MOE + w��b = z * MOE + y
		int64	w = a[0] % MOE, x = a[0] / MOE;
		int64	y = b[0] % MOE, z = b[0] / MOE;
		
		//a * b = (x * MOE + w) * (z * MOE + y) = f * MOD + (d + e) * MOE + c
		int64	c = w * y, d = w * z, e = x * y, f = x * z;
		
		//��a * b��Ϊ��λ����
		vectori	r(2, 0);
		r[0] = c + (d % MOE + e % MOE) * MOE;
		r[1] = d / MOE + e / MOE + f;
		
		if (r[0] >= MOD) r[0] -= MOD, r[1] ++;
		if (r[0] >= MOD) r[0] -= MOD, r[1] ++;
		
		if (!r[1]) r.pop_back();
		return r;
	}
	
	//a = a1 * MOD^L2 + a0��b = b1 * MOD^L2 + b0
	vectori	a0(L2, 0), a1(L2, 0);
	vectori	b0(L2, 0), b1(L2, 0);
	
	//c = a0 + a1��d = b0 + b1
	vectori	c(L2 + 1, 0), d(L2 + 1, 0);
	
	//����a0,a1,b0,b1,c,d
	for (int i = 0; i < L2; ++ i)
	{
		a0[i] = a[i];
		a1[i] = a[i + L2];
		
		b0[i] = b[i];
		b1[i] = b[i + L2];
		
		c[i] += a0[i] + a1[i];
		if (c[i] >= MOD) c[i] -= MOD, c[i + 1] ++;
		
		d[i] += b0[i] + b1[i];
		if (d[i] >= MOD) d[i] -= MOD, d[i + 1] ++;
	}
	
	//e = a0 * b0, f = (a0 + a1) * (b0 + b1), g = a1 + b1
	vectori	e = work(a0, b0);
	vectori	f = work(c, d);
	vectori	g = work(a1, b1);
	
	//r = a * b = (a1 * MOD^L2 + a0) * (b1 * MOD^L2 + b0)
	//          = a1 * b1 * MOD^L + (a0 * b1 + a1 * b0) * MOD^L2 + a0 *  b0
	//	    = g * MOD^L + (f - e - g) * MOD^L2 + e
	vectori	r(L * 2, 0);
	
	//����f - e - g
	for (int i = 0; i < f.size(); ++ i)
	{
		if (e.size() > i) f[i] -= e[i];
		if (g.size() > i) f[i] -= g[i];
		if (f[i] < 0) f[i] += MOD, f[i + 1] --;
		if (f[i] < 0) f[i] += MOD, f[i + 1] --;
	}
	
	//����r
	for (int i = 0; i < r.size(); ++ i)
	{
		if (e.size() > i) r[i] += e[i];
		if (i >= L2 && f.size() > i - L / 2) r[i] += f[i - L2];
		if (i >= L && g.size() > i - L) r[i] += g[i - L];
		if (r[i] >= MOD) r[i] -= MOD, r[i + 1] ++;
		if (r[i] >= MOD) r[i] -= MOD, r[i + 1] ++;
	}
	
	//ȥǰ��0
	for (; r.size() && !r[r.size() - 1]; ) r.pop_back();
	return r;
}

int	main()
{
	freopen("mult.in", "r", stdin);
	freopen("mult.out", "w", stdout);
	
	//�����һ����
	vectori	num1(0);
	string	str1;
	cin >> str1;
	//�����MOD������
	for (int64 i = (int)str1.size() - 1, tot = 0, p10 = 1; i >= 0; -- i)
	{
		tot += (str1[i] - '0') * p10;
		p10 *= 10;
		if (p10 == MOD || i == 0)
		{
			num1.push_back(tot);
			tot = 0;
			p10 = 1;
		}
	}
	
	//����ڶ�����
	vectori	num2(0);
	string	str2;
	cin >> str2;
	//�����MOD������
	for (int64 i = (int)str2.size() - 1, tot = 0, p10 = 1; i >= 0; -- i)
	{
		tot += (str2[i] - '0') * p10;
		p10 *= 10;
		if (p10 == MOD || i == 0)
		{
			num2.push_back(tot);
			tot = 0;
			p10 = 1;
		}
	}
	
	//�����
	vectori	ans = work(num1, num2);
	if (!ans.size()) ans.push_back(0);
	cout << ans[ans.size() - 1];
	for (int i = ans.size() - 2; i >= 0; -- i)
	{
		int64	p10 = MOD / 10;
		for (; p10 > 1 && ans[i] < p10; p10 /= 10) cout << 0;
		cout << ans[i];
	}
	cout << endl;
	
	return 0;
}
