void ntu_rdm() // spread sheet
{
  TCanvas *c1  = new TCanvas("c1","c1",0,0,400,1200);
  TFile *f     = new TFile("ntu_rdm.root","RECREATE"); // export the ntuple !
                                                       // to save time for later
                                                       // uses, e.g. change clr
  //                                       overwrite
  
  TNtuple *ntu = new TNtuple("ntuple","ntuple","x:y:z");
  //                                            no length limit !
  TRandom *r   = new TRandom();

  c1 -> Divide(1,3);

  r -> SetSeed(1240); // seed 
                      // must declare outside the loop !

  float mn  = 0;
  float sig = 1;
  
  for (int i=0; i<30000; i++)
  {
    float x = r -> Gaus(mn,sig);
    float y = r -> Gaus(mn,sig);
    float z = r -> Gaus(mn,sig);

    ntu -> Fill(x,y,z);
  }

  c1  -> cd(1);
  ntu -> Draw("x");

  c1  -> cd(2);
  ntu -> Draw("x:y");
  ntu -> SetMarkerColor(2);

  c1  -> cd(3);
  ntu -> Draw("x:y:z");
  ntu -> SetMarkerColor(4);
  ntu -> Draw("x:y:z", "sqrt(x^2+y^2-z^2)>1", "same");
  //                   constraints: selecting data to draw
  ntu -> SetMarkerColor(5);
  
  c1 -> cd();

  f  -> Write(); // write the file declared at top

}
