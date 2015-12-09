double M_pi = 0.13977; //GeV
double Tau_pi = 2.6e-7; // 0.26 mu s
double c = 3.e8; // m / s

TRandom *r;

double Get_D_L(double E, double M, double T);
void pi_decay()
{
  r = new TRandom();

  TCanvas *c1 = new TCanvas("c1","c1",10,10,1200,600);
  c1 -> Divide(2,1);

  TH1F *h_t = new TH1F("h_t","Pion Decay Time",100,0,3e-6);
  TH1F *h_l = new TH1F("h_l","Pion Decay Length",100,0,100);

  for (int i=0; i<100000; i++)
  {
    double E = 10; // GeV
    double d_t = r -> Exp(Tau_pi); // decay time
    double d_l = Get_D_L(E, M_pi, d_t);

    h_t -> Fill(d_t);
    h_l -> Fill(d_l);
  }

  c1 -> cd(1);
  h_t -> Draw();
  h_t -> Fit("expo");
  h_t -> SetXTitle("Time (s)");

  c1 -> cd(2);
  h_l -> Draw();
  h_l -> SetLineColor(4);
  h_l -> SetXTitle("Length (km)");
  h_l -> SetMinimum(0);
}

double Get_D_L(double E, double M, double T)
{
  // Energy & Mass in GeV; Time in s
  double gamma = E / M; // Lorentz dilation
  double d_l = c*T*gamma/1000; // from m to km
  return d_l;
}
