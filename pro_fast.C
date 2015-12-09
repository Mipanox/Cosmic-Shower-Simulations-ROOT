TRandom *r;


float lbd_p = 87;
float d_h   = 1;
float h_max = 300;
float rho0  = 1.021/1000;
float A     = 8;

float ang   = 20.; // incident zenith angle
float rad   = TMath::Pi()/180.*ang;


float Get_H_from_X(float X, float ang)
{
  float h = -log(X/(rho0*A*100000))*A; // integral of rho func
                                       // see week6, p.4
  h = h/cos(rad);
  return h;

}
float Get_P_Int_Height_fast()
{
  float X = r -> Exp(lbd_p);
  float h = Get_H_from_X(X,ang);
  return h;
}



void pro_fast()
{
  r = new TRandom();
  
  TH1F *h1 = new TH1F("h1","h1",100,0,200);
  TRandom *r = new TRandom();

  for (int ievt=0; ievt<1000000; ievt++)
  {
    float p_int_f = Get_P_Int_Height_fast();
    h1 -> Fill(p_int_f);

  }
  h1 -> Draw();

  h1 -> SetTitle("Proton Interaction Fast");
}


