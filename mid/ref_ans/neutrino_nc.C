double pi=TMath::Pi();
double N_Av=6.02E23; //g^-1
double rho_Earth=5.52; //g/cm3
double R_Earth=6.4E8; //cm
double R_Det=1.0E5;//cm
double rho_Det=0.9; //g/cm3, Anrarctic Ice under 200 depth.

void neutrino_nc(){

  TRandom3 *r = new TRandom();;
  TH1F *hist1 = new TH1F("hist1","Arrival Direction",100,0,180);


  for (int ievt=0 ; ievt<100000; ievt++){

    double theta=acos(r->Rndm()-1); 
    //isotropic in zenith angle, up-coming only 90 deg - 180 deg
    double theta_deg=theta*180./pi;
    

    double Cord_length_cm= Cord_length(R_Earth, theta);
    double Cord_length_X= Cord_length_cm*rho_Earth;
    
    double Energy=1.E09; // GeV;
    double Energy_threshold=1.E08;
    
    double total_propa_length_X=0;
    while(total_propa_length_X < Cord_length_X){
      double Sigma=Xsec_neutrino(Energy,0); // it's very important to calculate X-section while losing energy.
      double Lambda=1./(N_Av*Sigma);
      double dX=r->Exp(Lambda);    
      total_propa_length_X=total_propa_length_X+dX;
      Energy=Energy*0.5;
    }
   
    if (Energy>Energy_threshold){
      hist1->Fill(theta_deg);
    }
  }

  hist1->SetXTitle("Theta (deg)");
  hist1->SetYTitle("Entries");

  hist1->Draw();

}

double Xsec_neutrino(double Energy, int Current){

  //Energy in GeV
  //Current=0;NC, Current=1; CC, Current=2; NC+CC;
  //arXiv:1305.7513 [hep-ex]

  double alpha=0.363;
  double Xsec_CC=5.53E-36*pow(Energy,alpha);
  double Xsec_NC=2.31E-36*pow(Energy,alpha);
  
  if (Current==0) return Xsec_NC;
  if (Current==1) return Xsec_CC;
  if (Current==2) return Xsec_CC+Xsec_NC;
} 

double Cord_length(double R, double theta){
  double kapa=2*theta-pi;
  double c=2*R*sin(kapa/2.);
  return c;
}
