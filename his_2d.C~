void trdm()
{
  TH1F *rdm = new TH1F("rdm","rdm",100,0,1);
  TRandom *r = new TRandom();

  r -> SetSeed(1240); // seed 
                      // must declare outside the loop !

  for (int i=0; i<1000000; i++)
  {
    float x = r -> Rndm(); // machine independent generator !
    rdm -> Fill(x);        // e.g. for collaborative debugging !
  }

  rdm -> Draw();
  rdm -> SetMinimum(0);

}
