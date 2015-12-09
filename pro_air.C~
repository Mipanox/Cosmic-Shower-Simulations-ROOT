void pion_air()
{
  TFile *f     = new TFile("ntu_rdm.root","RECREATE");
  TCanvas *c1  = new TCanvas("c1","c1",0,0,600,400);
  TNtuple *ntu = new TNtuple("ntuple","ntuple","x");

  TH1F *h1   = new TH1F("h1","h1",100,0,5000);
  TH1F *h2   = new TH1F("h2","h2",100,0,5000);
  
  c1 -> Divide(1,2);
  
  TRandom *r   = new TRandom();

  r -> SetSeed(1240); // seed

  const double rho_air = 1.2754e-03;
  const double lba_pi  = 130;
  const double step    = 50; // cm
  double prob = 1./lba_pi*rho_air*step;

  for (int i=0; i<10000; i++)
  {
    double ln = 0;

    while (r -> Rndm() > prob) ln++;
    ntu -> Fill(ln);
  }

  ntu -> Draw("x>>h1");
  ntu -> Draw("x>>h2");

  h1 -> SetXTitle("Travel length (m)");
  h1 -> SetYTitle("Entries");

  c1 -> cd(2);
  h2 -> Draw();

  c1 -> cd(1);
  h1 -> Fit("expo");

  c1 -> cd();

  f -> Write();
  
}
