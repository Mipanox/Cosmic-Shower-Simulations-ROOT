/*** Plot the Bethe-Block formula for muons ***/

const double M_mu = 0.105658; // GeV
const double M_e  = 511.e-6;

double dedx_mu(double *x, double *par);

void dedx_muon()
{
  TF1 *f1 = new TF1("air" ,dedx_mu,M_mu,1000,1);
  TF1 *f2 = new TF1("rock",dedx_mu,M_mu,1000,1);

  f1 -> SetParameter(0,0); // mat_code = 0: air
  f1 -> SetLineColor(4);
  f1 -> Draw();

  f2 -> SetParameter(0,1); // mat_code = 1: rock
  f2 -> SetLineColor(2);
  f2 -> Draw("same");

  f2 -> GetHistogram()->GetXaxis()->SetTitle("Momentum (GeV/c)");
  f2 -> GetHistogram()->GetYaxis()->SetTitle("dE/dX (Gev/(g/cm2))");
  // NOTE: add axis FAILED
    
  gPad -> SetLogx();
  gPad -> SetLogy();
}

double dedx_mu(double *x, double *par)
{
  double E = x[0]; // 1-d
  int mat_code = par[0]; // what type of material: air? rock?
  // cout << mat_code << endl;

  // constants
  double K     = 0.307e-3; // GeV/(g/cm2)
  double delta = 0;
  double z     = 1;
  double p     = sqrt(E*E-M_mu*M_mu);
  double gamma = sqrt(1.+pow(p/M_mu,2));
  double betaa = sqrt(1.-1./(gamma*gamma));
  double g_b   = p/M_mu;
  double tmax  = 2*M_e*p*p/(M_mu*M_mu+M_e*M_e+2*M_e*E);
    
  // mat_code == 0: air
  double I  = 85.7e-9 ; // GeV
  double ZA = 0.49919;  // target Z/A: charge number/mass number

  if (mat_code==1)
    { // rock
    I  = 136.4e-9;
    ZA = 0.50;
  }

  // Bethe-Block formula
  double dedx = K*z*z*ZA/(betaa*betaa)*
    (1/2.*log(2*M_e*g_b*g_b*tmax/(I*I))-betaa*betaa-delta/2.); // GeV/cm2

  return dedx;
}
