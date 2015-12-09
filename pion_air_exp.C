void pion_air_exp()
{
  TH1F *h1     = new TH1F("h1","h1",100,0,5000);
  TF1 *fun     = new TF1("fun","exp(-x)",0,10);
  TRandom *r   = new TRandom();

  r -> SetSeed(1240); // seed

  const double rho_air = 1.2754e-03;
  const double lba_pi  = 130;


  for (int i=0; i<10000; i++)
  {
        
    float x = fun -> GetRandom();
    float l = x/rho_air*lba_pi/100.; // to meter

    h1 -> Fill(l);
    
  }
  h1 -> Draw();
  h1 -> Fit("expo");

  h1 -> SetXTitle("Travel length (m)");
  h1 -> SetYTitle("Entries");
}
