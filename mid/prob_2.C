/* prob 2
   neutrino propagation in Earth with decaying energy in CN interactions
*/

double pi    = TMath::Pi();
double N_Av  = 6.02E23; // g^-1
double rho_E = 5.52;    // g cm^-3
double R_E   = 6.4E8;   // cm

// cross-section of neutrino
double Xsec_n(double E)
{
  double Xsec = 2.51E-36*pow(E,0.363); //cm^2
  return Xsec;
}

// length of path of neutrins -> x=Cord_len * rho
double Cord_len(double R, double theta)
{
  double k = 2*theta-pi;
  return  2*R*sin(k/2.);
}


void prob_2()
{
  TRandom3 *r  = new TRandom3();
  TNtuple *ntu = new TNtuple("ntuple","ntuple","e:theta:weight");

  double E   = 1.E09; // GeV ; energy of incoming neutrinos

  TH1F *hist = new TH1F("hist","hist",100,0,180);
  
  for (int i=0; i<100000; i++)
  {
    double E_  = E; // initial energy
    double Sig = Xsec_n(E);
    double lba = 1./(N_Av*Sig);
    
    double theta = acos(r -> Rndm() - 1);
    double theta_deg = theta * 180./pi;
    double Cord_len_cm = Cord_len(R_E, theta);
    double Cord_len_X  = Cord_len_cm * rho_E;

    double Prop_len_X  = r -> Exp(lba);
    
    // if the neutrino survive, it decays and goes on
    double prop_ln = Prop_len_X; // initialize propagation length

    while (E_ > 1.E08) // if hasn't reached, continue propagating
    {
      E_  = E_/2.; // lose half of energy
      Sig = Xsec_n(E);
      lba = 1./(N_Av*Sig);

      prop_ln += r -> Exp(lba);
      if (prop_ln > Cord_len_X)
      {
	ntu -> Fill(E_, theta_deg);
      
      }
    }
    
    ntu -> Draw("theta >> hist");
  }
  gPad -> SetLogy();
  hist -> SetTitle("Arrival distribution of Neutrinos > 10^17 eV");
  hist -> Draw("h");
}
  
  
