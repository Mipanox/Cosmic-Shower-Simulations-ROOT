void yellow()
{

  TH1F *step = new TH1F("step","step",100,0,10);
  TRandom *r = new TRandom();

  r -> SetSeed(1240); // seed 

  for (int i=0; i<10000; i++)
  {
    int sp = 0; // initialize step

    while (r -> Rndm() > 0.5) sp++;
    // printf("%d\n", sp);
    step -> Fill(sp);
  }

  step -> Draw();
}
