memset(T,0,sizeof(T)); T[0].l=1;
for (int i=1;i<=Number_Of Name;++i)
for (int j=0,k=Length_Of_Name[i],p;k;) {
	//找公共部分
	for (p=T[j].r;p>=T[j].l;--p,--k)
	if (Name[T[j].a][p]!=Name[i][k]) break;
	//分解该点
	if (p>=T[j].l) {
		T[++N]=T[j]; T[j].l=p+1; T[N].r=p;
		memset(T[j].s,0,sizeof(T[j].s));
		T[j].s[Name[T[j].a][p]-96]=N;
	}
	//找子节点
	if (!k) break; else
	if (T[j].s[Name[i][k]-96]) j=T[j].s[Name[i][k]-96]; else {
		T[j].s[Name[i][k]-96]=++N;
		T[N].a=i; T[N].l=1; T[N].r=k;
		j=N;
	}
}
