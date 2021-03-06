void pro_air()
{
  TNtuple *ntu = new TNtuple("ntuple","ntuple","x");

  TH1F *h1   = new TH1F("h1","h1",100,0,200);
  
  TRandom *r   = new TRandom();

  r -> SetSeed(1240); // seed

  const double lba_pr  = 87; // g/cm^2
  const double step    = 1; // km
  const double h_max   = 200; //km

  for (int i=0; i<10000; i++)
  {
    int s  = 0; // initial height = h_max
    double h  = h_max;
    double p  = 0.;
    
    while (r -> Rndm() > p)
    {
      s++;
      h = h_max - step * s; // height above sea level
      double rh = 1.02*exp(-h/8)*pow(10.,-3.);
      double dx = rh*step*100000.;
      p  = 1/lba_pr*dx;
    }
    ntu -> Fill(h);
  }

  ntu -> Draw("x>>h1");

  h1 -> SetTitle("Proton Interaction Height");
  h1 -> SetXTitle("Travel length (km)");
  h1 -> SetYTitle("Entries");  
}
