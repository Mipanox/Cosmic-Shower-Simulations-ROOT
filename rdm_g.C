void rdm_g()
{
  // pros: easy
  // cons: waste of CPU and time (2 random numbers -> double consumption!)
  TH1F *gau = new TH1F("gau","gau",10000,-10,10);
  TRandom *r = new TRandom();
  //-- the TRandom CLASS, many built distribution in the library --//

  r -> SetSeed(1240); // seed 
                      // must declare outside the loop !

  for (int i=0; i<1000000; i++)
  {
    float x = r -> Rndm()*20.-10; // machine independent generator !
    float g = exp(-x*x/2.);

    float y = r -> Rndm(); // note this is followed after x   
 
    if (y < g) gau -> Fill(x);
  }

  gau -> Draw();

}
