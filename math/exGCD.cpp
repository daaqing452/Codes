inline void exGCD(int a, int b, int c)
{
	if (b == 0)
	{
		x = c / a; y = 0;
		return;
	}
	exGCD(b, a % b, c);
	int	s = y, t = x - a / b * y;
	x = s; y = t;
}
