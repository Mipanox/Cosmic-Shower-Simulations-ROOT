/*** Calculate muon range ***/
// how far muon can travel inside a rock of density 2.65 g/cm3
// NOTE: 'range': given energy, how far a particle can travel

const double M_mu = 0.105658; // GeV
const double M_e  = 511.e-6;

TRandom *r;
TF1 *Func_muon_dxde;

////// sub-functions //////
double dedx_mu(double *x, double *par);
double dxde_mu(double *x, double *par);
double Get_M_R(float E, int mat_code);

/*------ main func ------*/
void muon_depth()
{
  r = new TRandom();

  Func_muon_dxde = new TF1("fr",dxde_mu,0.2,100,1);
  Func_muon_dxde -> SetNpx(1000); // how many points to draw func

  TH1F *muon_d = new TH1F("muon_d","muon_d",100,0,500);
  
  for (int i=0; i<10000; i++)
  {
    float E_mu = 30; // incoming muon energy
    int mat_code = 1; // rock
    float R_muon = Get_M_R(E_mu,mat_code);

    float X = r -> Exp(R_muon); // Manually generate exponential distribution !
                                // in g/cm2
    float den_rock = 2.65; // g/cm3
    float pen_dis  = X/den_rock/100; // penetrating distance; in meter
    
    muon_d -> Fill(pen_dis);
  }
  muon_d -> SetXTitle("Muon Penetrating Depth in rock (m)");
  muon_d -> Fit("expo");
  muon_d -> Draw();
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

double dxde_mu(double *x, double *par)
{
  double dedx = dedx_mu(x,par);
  double dxde = 1/dedx;
  return dxde;
}

double Get_M_R(float E, int mat_code)
{
  Func_muon_dxde -> SetParameter(0,mat_code);

  if (E <= 0.2) return 0; // avoid Anderson-Zeigler regime
  return Func_muon_dxde -> Integral(0.2,E);
  /*       _
          | 0.2    dE     
      R = |      ------ = dE * -dx/dE  <--the 'inverse function'
         _| E    -dE/dx  
   */    
}
