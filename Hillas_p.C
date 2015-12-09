TRandom *r;
const int N = 4; // how many pions produced in the first split.
double M_pi = 0.13977; // rest mass of pion plus.

void sp_by_two(double E_in, double &E_A, double &E_B)
{
  float frac = r -> Rndm();
  E_A = frac * E_in;
  E_B = (1-frac) * E_in;
}

void sp_by_N(double E_in, double E_branch[])
{
  double frac[N];
  double sum = 0;

  for (int i=0; i<N; i++)
  {
    frac[i] = r -> Rndm();
    sum    += frac[i];
  }
  for (int i=0; i<N; i++)
  {
    E_branch[i] = frac[i]/sum*E_in;
  }
}

void Hillas_p()
{
  TCanvas *c1 = new TCanvas("c1","c1",100,100,700,400);
  c1 -> Divide(2,1);
  
  TH1F *h_n = new TH1F("h_m","h_m",100,0,50);
  TH1F *h_e = new TH1F("h_n","h_n",100,0,150);

  r = new TRandom();
  
  double E = 1000; // initial energy of proton, in GeV
  
  for (int i=0; i<100000; i++)
  {
    // daughter proton and groups of pions
    double E_A,E_B;
    sp_by_two(E, E_A, E_B);
    double E_branch[N];
    sp_by_N(E_B, E_branch);

    int n_pi = 0;
    for (int j=0; j<N; j++)
    {
      double E_in = E_branch[j];
      double E_a, E_b;

      while (E_in > M_pi)
      {
        sp_by_two(E_in, E_a, E_b);
	double E_pi_k = E_a;
	double E_pi   = E_pi_k + M_pi; // kinetic + rest

	h_e -> Fill(E_pi);

	E_in = E_b - M_pi;
	n_pi++;

      }
    }

    h_n -> Fill(n_pi);

  }

  c1 -> cd(1);
  h_n -> Draw();
  h_n -> SetLineColor(2);
  h_n -> Fit("gaus"); // central limit theorem? or Poisson?
  h_n -> SetTitle("How many pions produced");
  h_n -> SetXTitle("N of pions");
  
  c1 -> cd(2);
  h_e -> Draw();
  gPad -> SetLogy();
  h_e -> SetTitle("Distribution of produced pions");
  h_e -> SetXTitle("pion energy (GeV)");

}


