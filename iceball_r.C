/*
 neutrino coming from below of a uniform-density spherical Earth
*/

// assumption: every survival neutrino pass through the center of detector

double pi    = TMath::Pi();
double N_Av  = 6.02E23; // g^-1
double rho_E = 5.52;    // g cm^-3
double R_E   = 6.4E8;   // cm
double R_D   = 1.0E5;   // cm; detector size
double rho_D = 0.9;     // g cm^-3; density of ice

// cross-section of neutrino
double Xsec_n(double E, int Cur)
{
  // Energy in GeV
  /* Current = 0: NC
     Current = 1: CC
     Current = 2: NC+CC
  */

  double Xsec_CC = 5.53E-36*pow(E,0.363); // see draw_nu_xsec.C
  double Xsec_NC = 2.31E-36*pow(E,0.363);

  if (Cur == 0) return Xsec_NC;
  else if (Cur == 1) return Xsec_CC;
  else if (Cur == 2) return Xsec_NC + Xsec_CC;
}

// length of path of neutrins -> x=Cord_len * rho
double Cord_len(double R, double theta)
{
  double k = 2*theta-pi;
  return  2*R*sin(k/2.);
}

// Integral of probability from x = 0 to l
double Prob_Int(double X_prop, double Int_len)
{ 
  return (1-exp(-X_prop/Int_len));
}

void iceball_r()
{
  TRandom3 *r  = new TRandom3();
  TNtuple *ntu = new TNtuple("ntuple","ntuple","e:theta:weight");

  double E   = 1.E07; // GeV ; energy of incoming neutrinos
  double Sig = Xsec_n(E,2);
  double lba = 1./(N_Av*Sig);

  TH1F *hist[10];

  for (double E=1.E05;  E<=1.E05; E=E*10.)
  {
    j = 1; // Color
    
    for (int i=0; i<10000; i++)
    {
      double theta = acos(r -> Rndm() - 1);
      // due to effective detecting area (solid angle),
      // to generate isotropic angle distribution,
      // we must use acos -> -pi ~ pi -> -1 gives angles upwards
      double theta_deg = theta * 180./pi;
    
      double Cord_len_cm = Cord_len(R_E, theta);
      double Cord_len_X  = Cord_len_cm * rho_E;
      // slant depth of the pass through the Earth
      double len_X_D     = 2*R_D*rho_D;
      // slant depth for the detector

      double prob_pas_E = 1 - Prob_Int(Cord_len_X, lba);
      double prob_int_D =     Prob_Int(len_X_D, lba);

      double prob_tot   = prob_pas_E * prob_int_D;
      
      ntu -> Fill(E, theta_deg, prob_tot);
    }
    char *hs_n = new char[10];
    sprintf(hs_n, "hist%d", j);

    hist[j] = new TH1F(hs_n,"",100,0,180);

    char *hs = new char[20];
    sprintf(hs, "theta >> hist[%d]", j);
    
    ntu  -> Draw(hs,"weight"); // trying to insert hist[j] but failed
    hs -> Draw("h");
    // hist[j] -> Draw("h");
    // hist[j] -> Draw("same");
    // hist[j] -> SetLineColor(j);
    
    j++;
  }
  gPad -> SetLogy();
}
  
  
