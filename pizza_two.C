TRandom *r;

// use pointers to save returned values (more than one)
void split_by_two(double In, double &A, double &B)
{
  float frac = r -> Rndm();
  A = frac * In;
  B = (1-frac) * In;
}

void pizza_two()
{
  float P_mass = 1; // total pizza mass
  
  r = new TRandom();
  TH1F *h1 = new TH1F("h1","h1",100,0,1);

  for (int i=0; i<100000; i++)
  {
    double piece_A,piece_B;
    split_by_two(P_mass, piece_A, piece_B);

    h1 -> Fill(piece_B);

  }
  h1 -> Draw();
  h1 -> SetMaximum();
  h1 -> SetMinimum(0);
  h1 -> SetTitle("How many fraction will B get?");
}


