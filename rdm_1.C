void rdm_1()
{
  int x = 8225;
  int m = 54325;
  int b = 713459;

  for (int i=0; i<100; i++)
  {
    x = x*m%b%99;
    printf("x%d = %d\n", i, x);
  }

}
