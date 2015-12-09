double pi = TMath::Pi();

void draw_nu_xsec()
{
  // arXiv: 1305.7513 [hep-ex]
  // theoretical expectation
  
  TF1 *F_sigma_CC = new TF1("CC","5.53E-36*pow(x,0.363)",1.0E01,1.0E11); //cm2
  TF1 *F_sigma_NC = new TF1("NC","2.31E-36*pow(x,0.363)",1.0E01,1.0E11);

  F_sigma_CC -> Draw();
  F_sigma_CC -> GetXaxis()->SetTitle("Energy (GeV)");
  
  F_sigma_NC -> SetLineColor(4);
  F_sigma_NC -> Draw("same");
  

}
