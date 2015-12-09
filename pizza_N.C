TRandom *r;
const int N = 4;

// In C++, array IS address
void split_by_N(double In, double branch[])
{
  double frac[N];
  double sum = 0;

  for (int i=0; i<N; i++)
  {
    frac[i] = r -> Rndm();
    sum    += frac[i];
  }
  for (int i=0; i<N; i++)
  {
    branch[i] = frac[i]/sum*In;
  }
}

void split_N(double In, double branch[]);

void pizza_N()
{
  TCanvas *c1 = new TCanvas("c1","c1",0,0,400,1200);
  c1 -> Divide(1,3);
  
  float P_mass = 1; // total pizza mass
  
  r = new TRandom();
  TH1F *h1 = new TH1F("h1","h1",100,0,1);
  TH1F *h2 = new TH1F("h2","h2",100,0,1);

  for (int i=0; i<100000; i++)
  {
    double piece[N];
    split_by_N(P_mass, piece);

    h1 -> Fill(piece[1]); // say, what's the result for the 3rd guy?

    double piecc[N];
    split_N(P_mass, piecc);

    h2 -> Fill(piecc[1]);

  }

  TH1F *rdm = new TH1F("rdm","rdm",100,0,1);
  TF1 *func = new TF1("func","3*(1-x)*(1-x)",0,1);

  c1 -> cd(1);
  func -> Draw();
  func -> SetTitle("Analytical Distribution");

  c1 -> cd(2);
  h2 -> Draw();
  h2 -> SetMinimum(0);
  h2 -> SetMaximum();
  h2 -> SetTitle("True Random Split");

  c1 -> cd(3);
  h1 -> Draw();
  h1 -> SetMaximum();
  h1 -> SetMinimum(0);
  h1 -> SetTitle("Split by sum up");
}


/* Correct spliting RNG */

void split_N(double In, double branch[])
{
  double temp[N-1];
  
  for (int i=0; i<N-1; i++)
  {
    temp[i] = r -> Rndm();
  }

  int ind[N-1];
  TMath::Sort(N-1,temp,ind);
  
  int pd = ind[0];
  branch[0] = 1-temp[pd]; // the first portion
  
  for (int i=1; i<N-1; i++)
  {
    int id = ind[i];
    int dd = ind[i-1];
    branch[i] = temp[dd] - temp[id];
  }

  int ld = ind[N-2];
  branch[N-1] = temp[ld]-0;
}

