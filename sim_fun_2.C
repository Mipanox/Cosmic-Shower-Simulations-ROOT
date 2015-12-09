double myf(double *x, double *p) // root defined grammar: must be double, two vars
{
  double y = 0;

  if (x[0] > 5) y = p[0];

  return y;
}

void sim_fun_2()
{
  TF1 *test1 = new TF1("test1",myf,0,10,1); // # of par = 1
  TF1 *test2 = new TF1("test2",myf,0,10,1);

  test1 -> SetParameters(1,0); // root can't identify only "one" par
  test1 -> SetLineStyle(2);
  test1 -> SetLineColor(4);
  test1 -> SetNpx(10000);

  test2 -> SetParameters(2,0);
  test2 -> SetLineColor(2);

  test2 -> Draw();
  test1 -> Draw("same");

}
