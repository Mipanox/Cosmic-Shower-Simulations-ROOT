void prob_1() 
{
  TCanvas *c1  = new TCanvas("c1","c1",0,0,400,1200);
  TNtuple *ntu = new TNtuple("ntuple","ntuple","x:y:z");
  TH1F    *h1  = new TH1F("h1","h1",100,-6,6);
  TRandom *r   = new TRandom();

  c1 -> Divide(1,2);
  r -> SetSeed(1240); // the random seed
  
  float mn  = 0;
  float sig = 1;
  
  for (int i=0; i<30000; i++)
  {
    float x = r -> Gaus(mn,sig);
    float y = r -> Gaus(mn,sig);

    ntu -> Fill(x,y);
  }

  c1  -> cd(1);
  ntu -> Draw("y:x");

  c1  -> cd(2);
  ntu -> Draw("x+y >> h1");
  h1  -> SetMarkerColor(2);
  h1  -> Fit("gaus"); 
  
  c1 -> cd();

  /* the fitting result for 'h1':
     Sigma        1.41511e+00
 
     this is ~sqrt(2)
  */
}
