void rdm_2()
{
  float x = 7;
  float pi = 3.14159265358979323846;
  
  TH1F* hist_test = new TH1F("test","test",100,0,1);

  for (int i=0; i<10000; i++)
  {
    x = (pi*x)-int(pi*x);
    // printf("x%d = %f\n", i, x);
    hist_test -> Fill(x);
  }

  hist_test -> Draw();
}
