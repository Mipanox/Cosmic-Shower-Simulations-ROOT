void sim_fun()
{
  TF1 *test1 = new TF1("test1","x",-10,10);
  TF1 *test2 = new TF1("test1","sin(x)*cos(x-6)",0,10);
  TF1 *test3 = new TF1("test3","sin(x)/x",0,10);

  test1 -> SetLineColor(4);
  // test1 -> Draw();

  test2 -> SetLineColor(4);
  test2 -> Draw();

  test3 -> SetLineColor(2);
  test3 -> Draw("same");
}
