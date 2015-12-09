void his_2d()
{
  TCanvas *c1 = new TCanvas("c1","c1",0,0,500,500);
  TH2F *gau2  = new TH2F("gau2","gau2",100,-6,6,100,-6,6);
  TRandom *r  = new TRandom();

  c1 -> Divide(2,2);

  r -> SetSeed(1240); // seed 
                      // must declare outside the loop !

  for (int i=0; i<10000; i++)
  {
    float x,y;
    r -> Rannor(x,y); // Return 2 numbers distributed
                      // following a gaussian with mean=0 and sigma=1
                      //-alternative: 2 indep. Gaussians
    
    gau2 -> Fill(x,y);
  }

  c1 -> cd(1);
  gau2 -> Draw("colz");

  c1 -> cd(2);
  gau2 -> Draw("surf1");

  c1 -> cd(3);
  gau2 -> Draw("box");

  c1 -> cd(4);
  gau2 -> Draw("cont2");

  c1 -> cd();

}
