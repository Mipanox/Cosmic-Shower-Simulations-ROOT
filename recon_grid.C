/// Chi-Square visualization ///
// - reconstruction of cosmic ray shower origin
//   from array timing data: "muon.root"

TRandom *r;

const Int_t MAX_N = 1000;
Int_t evt;
Int_t n_mu;
Float_t theta;
Float_t phi;
Float_t e;
Float_t x[MAX_N];
Float_t y[MAX_N];
Float_t z[MAX_N];
Float_t t[MAX_N];
int i_mu_ref;

void fcn(Int_t &npar, Double_t *gin, Double_t &f,
	 Double_t *par, Int_t iflag);
double Dt_Point_Plane(double x, double y, double z, double theta,
		      double phi, double d);

void recon_grid()
{
  r = new TRandom();

  TFile *file      = new TFile("muon.root");
  TTree *Tree_Muon = (TTree*) file -> Get("muon_tree");

  Tree_Muon -> SetBranchAddress("evt", &evt);
  Tree_Muon -> SetBranchAddress("n_mu",&n_mu);
  Tree_Muon -> SetBranchAddress("theta",&theta);
  Tree_Muon -> SetBranchAddress("phi", &phi);
  Tree_Muon -> SetBranchAddress("e", &e);
  Tree_Muon -> SetBranchAddress("x", &x);
  Tree_Muon -> SetBranchAddress("y", &y);
  Tree_Muon -> SetBranchAddress("z", &z);
  Tree_Muon -> SetBranchAddress("t", &t);

  Int_t nentries = (Int_t)Tree_Muon -> GetEntries();
  TH2F *test = new TH2F ("test","Chisq",360,0,360,90,0,90);

  for (int i=0; i<1; i++)
  {
    Tree_Muon -> GetEntry(i);
    i_mu_ref = TMath::LocMin(n_mu,t);

    double dummy[100];
    int iflag = 0;
    int npar  = 3;
    double par[3];

    for (int itheta=0; itheta<180; itheta++)
    {
      for (int iphi=0; iphi<360; iphi++)
      {
        double chi2;
	par[0] = float(itheta)*TMath::DegToRad();
	par[1] = float(iphi)  *TMath::DegToRad();
	par[2] = 0;

	fcn(npar, dummy, chi2, par, iflag);

	test -> Fill(iphi, itheta, chi2);
      }
    }
  }

  test -> SetAxisRange(20,70,"X");
  test -> SetAxisRange(20,70,"Y");
  test -> SetXTitle("iphi");
  test -> SetYTitle("itheta");
  test -> SetMaximum(30);
  test -> Draw("surf3");

 }				


/*------------
  Sub Function
  -----------*/

void fcn(Int_t &npar, Double_t *gin, Double_t &f,
	 Double_t *par, Int_t iflag)
{
  float theta = TMath::Pi() - par[0];
  float phi   = TMath::Pi() + par[1];
  float d     = par[2];
  float t_ref = t[i_mu_ref];
  float x_ref = x[i_mu_ref];
  float y_ref = y[i_mu_ref];
  float z_ref = z[i_mu_ref];
  float t_exp_ref = Dt_Point_Plane(x_ref,y_ref,z_ref,theta,phi,d);

  Double_t chisq = 0;
  for (int i=0; i<n_mu; i++)
  {
    float dt_err = 20 * sqrt(2);
    float dt_obs = t[i] - t_ref;
    float dt_exp = Dt_Point_Plane(x[i],y[i],z[i],theta,phi,d)-t_exp_ref;
    float delta  = dt_obs - dt_exp;
    float chi    = delta / dt_err;
    chisq += chi*chi;
  }
  f = chisq;
}

double Dt_Point_Plane(double x, double y, double z, double theta,
		      double phi, double d)
{
  double a = cos(phi)*sin(theta);
  double b = sin(phi)*sin(theta);
  double c = cos(theta);

  if (a==0 && b==0 && c==0)
  {
    a = 1.0e-8;
    b = 1.0e-8;
    c = 1.0e-8;
  }
  return (a*x+b*y+c*z+d)/0.0003; // 0.0003 = c in km/ns
}
