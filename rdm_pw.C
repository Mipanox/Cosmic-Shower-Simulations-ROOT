void rdm_pw() // integral -> inverse
{              // e.g. y = x^2 -> 1/3x^3     (integral)
               //             <-> (3x)^(1/3) (inverse)

  TH1F *rdm = new TH1F("rdm","rdm",100,0,1);
  TRandom *r = new TRandom();

  r -> SetSeed(1240); // seed 

  for (int i=0; i<1000000; i++)
  {
    float x  = r -> Rndm()/3.;
    float iv = pow(3*x, 1./3.); // the inverse function
    // cout << iv << endl;
    rdm -> Fill(iv);
  }
  rdm -> Draw();

  // expected x^2 distribution
  TF1 *pw = new TF1("pw","x^2*30000",0,1);
  pw -> Draw("same");
  pw -> SetLineStyle(2);
  pw -> SetLineColor(4);
}
