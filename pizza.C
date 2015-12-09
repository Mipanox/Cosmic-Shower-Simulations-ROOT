TRandom *r;

void pizza()
{
  r = new TRandom();
  TCanvas *c1 = new TCanvas("c1","c1",100,100,400,700);
  c1 -> Divide(1,3);
  
  TH1F *h_m = new TH1F("h_m","h_m",100,0,1);
  TH1F *h_n = new TH1F("h_n","h_n",100,0,10);
  TH1F *h_s = new TH1F("h_s","h_s",100,0,1);

  double tax = 0.05;
  
  for (int i=0; i<100000; i++)
  {
    double m_p = 1;
    int n = 0;
    double sum_A = 0;

    while (m_p > 0)
    {
      float f = r -> Rndm();
      float A = f * m_p;

      m_p = (1-f) * m_p - tax;
      n++;
      sum_A += A;

      h_m -> Fill(A);
    }
    h_n -> Fill(n);
    h_s -> Fill(sum_A);

  }
  c1 -> cd(2);
  h_m -> Draw();
  h_m -> SetLineColor(2);
  h_m -> SetTitle("How much A takes one time");
  
  c1 -> cd(1);
  h_n -> Draw();
  h_n -> SetTitle("How many pieces A takes");
  h_n -> GetXaxis() -> SetTitle("number of pieces");

  c1 -> cd(3);
  h_s -> Draw();
  h_s -> SetLineColor(6);
  h_s -> SetTitle("Total portion that A gets");
}


