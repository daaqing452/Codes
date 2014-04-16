next[1] = 0;
for (int i = 2; i <= N; ++ i)
{
	for (j = next[i - 1]; j > 0 && str[j + 1] != str[i]; j = next[j]);
	if (str[j + 1] == str[i]) next[i] = j + 1; else next[i] = 0;
}
