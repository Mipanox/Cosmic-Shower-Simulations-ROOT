double M_pi = 0.13977;
double M_mu = 0.10566;
double M_nu = 0.1e-9;

TRandom *r;

void pion_decay()
{
  r = new TRandom();
  TCanvas *c1 = new TCanvas("c1","c1",10,10,1200,600);

  c1 -> Divide(2,1);

  TH1F *h_theta = new TH1F("h_theta","Muon Theta" ,100,175,180);
  TH1F *h_E     = new TH1F("h_E"    ,"Muon Energy",100,0,1);

  for (int i=0; i<10000; i++)
  {
    double px = 0;
    double py = 0;
    double pz = -1; // initial conditions, in GeV
    double E  = sqrt(px*px+py*py+pz*pz+M_pi*M_pi);

    // Exploit built classes in ROOT !!!
    TLorentzVector Pion(px,py,pz,E); // 4-momentum

    Double_t decay_p_m[2] = {M_mu, M_nu}; // daughter particles' masses
    TGenPhaseSpace event;
    event.SetDecay(Pion, 2, decay_p_m); // decay into TWO particles: mu and nu
    event.Generate(); // execute

    TLorentzVector Muon = *(event.GetDecay(0)); // Product mu's 4-momentum
    TLorentzVector Neu  = *(event.GetDecay(1));

    float theta_mu = Muon.Theta()*TMath::RadToDeg();
    float E_mu     = Muon.E(); // extract results !

    h_theta -> Fill(theta_mu);
    h_E     -> Fill(E_mu);
  }

  c1 -> cd(1);
  h_theta -> Draw();
  h_theta -> SetXTitle("Theta Muon (deg)");

  c1 -> cd(2);
  h_E -> Draw();
  h_E -> SetLineColor(2);
  h_E -> SetXTitle("Energy (GeV)");
}  
