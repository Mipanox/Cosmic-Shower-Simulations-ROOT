TRandom *r;
float lambda_proton=87 ; //g/cm2 for <0.1TeV
float d_h=1; // 1km
float h_max=300;;
float rho0=1.021/1000; // g/cm3
float A=8; // km

void proton_up(){

  r = new TRandom();

  TH1F * h1 = new TH1F("h1","Interaction Height",100,0,10000);
  TRandom *r = new TRandom();

  for (int ievt=0 ; ievt<1000000 ; ievt++){
    float theta = 45*TMath::DegToRad();
    float p_interaction_y=Get_P_Int_Height_up(theta);
    h1->Fill(p_interaction_y);
  }
  h1->SetXTitle("Interaction Height (meter)");
  h1->SetYTitle("Entries");
  h1->Draw();    

}

float Get_P_Int_Height_up(float theta){
  float X=r->Exp(lambda_proton);
  float h=Get_H_from_X_up(X, theta);
  return h;
}


float Get_H_from_X_up(float X, float theta){
  X=X*cos(theta);
  if ((1-X/(rho0*A*100000))<0)  return 1E10;
  float h=-log(1-X/(rho0*A*100000))*A*1000;
  return h;    
}

