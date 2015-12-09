TRandom *r;
const double lba_pr  = 87; // g/cm^2
const double step    = 1; // km
const double h_max   = 200; //km

double rho_air(double h)
{
  return 1.02*exp(-h/8)*pow(10.,-3.);
}

double pro_air_h()
{
  int s  = 0;
  double h  = h_max;
  double p  = 0.;
    
  while (r -> Rndm() > p)
  {
    s++;
    h  = h_max - step * s; // height above sea level
    double rh = rho_air(h);
    double dx = rh*step*100000.;
    p  = 1/lba_pr*dx;
  }
  return h;
}


void pro_zen()
{
  TNtuple *ntu = new TNtuple("ntuple","ntuple","x");
  TH1F *h1   = new TH1F("h1","h1",100,0,200);
  r   = new TRandom(); 

  r -> SetSeed(1240); // seed

  for (int i=0; i<10000; i++)
  {
    double h = pro_air_h();
    ntu -> Fill(h);
  }

  ntu -> Draw("x>>h1");

  h1 -> SetTitle("Proton Interaction Height");
  h1 -> SetXTitle("Travel length (km)");
  h1 -> SetYTitle("Entries");  
}

