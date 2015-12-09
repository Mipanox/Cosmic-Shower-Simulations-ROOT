void sum_range()
{
  sum_xy(100,200);
}

void sum_xy(int x, int y)
{
  int sum = 0;

  for (int i=0; i<y; i++)
  {
    sum += i;
  }
  
  printf("summation from %d to %d is %d\n", x, y, sum);
}
