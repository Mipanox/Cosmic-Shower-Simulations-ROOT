/* Problem 3
   up-coming protons penetrate through the air.
*/
TRandom *r;

float lbd_p = 87;
float rho0  = 1.021/1000; // g/cm^3
float A     = 8;

float ang   = 45; // shooting angle
float rad   = TMath::Pi()/180.*ang;


float Get_H_from_X(float X, float rad)
{
  float h = -A*log(1-X/(100000*rho0*A));
  // integration of X and convert to h
  /*         _               _
            | h             | h         -h/A  
     X(h) = |   rho(h) dh = |   rho0 * e      dh
           _| 0            _| 0
                      _         _
                     |      -h/A |
          = rho0 * A | 1 - e     |
                     |_         _|
                      _              _
                     |          X     |
    ==> h = - A * ln | 1 -   ------   |
                     |_      rho0*A  _|
                   
   */
  h = h/cos(rad); // effective height
  return h;

}
float Get_P_Int_Height_fast()
{
  float X = r -> Exp(lbd_p);
  float h = Get_H_from_X(X,rad);
  return h;
}



void prob_3()
{
  r = new TRandom();
  
  TH1F *h1 = new TH1F("h1","h1",1000,0,10);
  TRandom *r = new TRandom();

  for (int ievt=0; ievt<1000000; ievt++)
  {
    float p_int_f = Get_P_Int_Height_fast();
    h1 -> Fill(p_int_f);

  }
  h1 -> Draw();
  h1 -> SetXTitle("altitude (km)");
  h1 -> SetTitle("Proton Interaction Height");
}


