double M_pi = 0.13997;
double M_mu = 0.10157;
double M_nu = 0;
double Tau_pi = 2.6e-8;
double c = 3e8;
TRandom *r;

double Get_D_L(double E, double M, double T);
void draw_pion_decay()
{
  r = new TRandom();
  r -> SetSeed(1240);

  TCanvas *sky = new TCanvas("sky","sky",300,10,1000,1600);
  TView *view  = TView::CreateView(1,0,0);

  view -> ShowAxis();
  view -> SetRange(-5,-5,0,5,5,10);

  for (int i=0; i<100; i++)
  {
    // Pion's energy and momentum
    double px = 0;
    double py = 0;
    double pz = -1; // initial conditions, in GeV
    double E  = sqrt(px*px+py*py+pz*pz+M_pi*M_pi);

    // Pion's decay time and decay point
    double pion_d_t = r -> Exp(Tau_pi);
    double pion_d_l = Get_D_L(E, M_pi, pion_d_t);

    double vx=0;
    double vy=0;
    double vz=10 - pion_d_l; // vertex in km

    // Pion's decay products (Mu+Neu)
    TLorentzVector Pion(px,py,pz,E);
    Double_t decay_p_m[2] = {M_mu, M_nu};

    TGenPhaseSpace event;
    event.SetDecay(Pion, 2, decay_p_m); // decay into TWO particles: mu and nu
    event.Generate(); // execute

    TLorentzVector Muon = *(event.GetDecay(0)); // Product mu's 4-momentum
    TLorentzVector Neu  = *(event.GetDecay(1));

    // Drawing
    TParticle *Particle_Muon = new TParticle();
    Particle_Muon -> SetMomentum(Muon);

    TParticle *Particle_Neu = new TParticle();
    Particle_Neu -> SetMomentum(Neu);

    Particle_Muon -> SetProductionVertex(vx,vy,vz,0);
    Particle_Muon -> SetLineColor(2);
    Particle_Muon -> Draw();

    Particle_Neu -> SetProductionVertex(vx,vy,vz,0);
    Particle_Neu -> SetLineColor(4);
    Particle_Neu -> Draw();
    
  }
}


double Get_D_L(double E, double M, double T)
{
  // Energy & Mass in GeV; Time in s
  double gamma = E / M; // Lorentz dilation
  double d_l = c*T*gamma/1000; // from m to km
  return d_l;
}
