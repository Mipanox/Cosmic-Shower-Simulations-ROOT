void draw_tf_random()
{
  // fraw canvas first
  TCanvas *c1 = new TCanvas("c1","c1",10,10,400,700);
  c1 -> Divide(1,2);
  //          nx,ny

  TH1F *random = new TH1F("random","random",100,-50,50);
  // TF1 *fun     = new TF1("fun","sin(x)/x",-50,50);
  // // test NEGATIVE probability ?!
  TF1 *fun = new TF1("fun","(sin(x))^2/(x)+0.4",-50,50);

  c1  -> cd(1);
  //     move to the 1st subplot
  fun -> SetLineColor(2);
  fun -> Draw();

  for (int i=0;i<50000;i++)
  {
    double x = fun -> GetRandom();
    random -> Fill(x);
  }

  c1 -> cd(2);
  random -> SetLineColor(4);
  random -> Draw();
  c1 -> cd();
  //    go to "home", otherwise there'll be YELLOW mark
  
}
