double M_pi = 0.13997;
double M_mu = 0.10157;
double M_nu = 0;
TRandom *r;

/* no physics, isotropically distributed angle */
void draw_par()
{
  r = new TRandom();

  TCanvas *sky = new TCanvas("sky","sky",300,10,1000,1600);
  TView *view  = TView::CreateView(1,0,0);

  view -> ShowAxis();
  view -> SetRange(-5,-5,0,5,5,10);

  for (int i=0; i<100; i++)
  {
    double theta = acos(r -> Rndm()); // 0 - 90 deg downgoing
    double phi   = r -> Rndm()*TMath::Pi()*2.; // 2pi

    double Mu_p  = 1;
    double Mu_px = -Mu_p*sin(theta)*sin(phi); // '-' just for convention
    double Mu_py = -Mu_p*sin(theta)*cos(phi); // since particle physicists
    double Mu_pz = -Mu_p*cos(theta);          // like to interpret angle 
    double Mu_E  = sqrt(Mu_p*Mu_p+M_mu*M_mu); // from zenith !

    TLorentzVector Muon(Mu_px,Mu_py,Mu_pz,Mu_E);
    TParticle * Particle_Muon = new TParticle();
    Particle_Muon -> SetMomentum(Muon); // simply read in the distribution

    double vx=0;
    double vy=0;
    double vz=10; // vertex in km

    Particle_Muon -> SetProductionVertex(vx,vy,vz,0);
    Particle_Muon -> SetLineColor(2);
    Particle_Muon -> Draw();
  }
}
