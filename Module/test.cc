
int expo(int, int);
int expo(int x, int n)
{
	int rekursiv = 0;
	if (n==0)
	{
		rekursiv = 1;
	} else 
	{
		rekursiv = x*expo(x,n-1);
	}
	return rekursiv;
}

void main() 
{
	int r;
	r = expo(2, 10);
	int_out(r);
}
