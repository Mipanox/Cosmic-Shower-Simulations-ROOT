void split_N()
{
  const int N=4;
  double branch[N];
  double temp[N-1];

  TRandom *r = new TRandom();
  
  for (int i=0; i<N-1; i++)
  {
    temp[i] = r -> Rndm();
  }

  for (int i=0; i<N-1; i++)
  {
    cout << temp[i] << endl;
  }
  cout << "" << endl;
  
  int ind[N-1];
  TMath::Sort(N-1,temp,ind);

  for (int i=0; i<N-1; i++)
  {
    cout << ind[i] << endl;
  }  

  cout << "" << endl;
  
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

  for (int i=0; i<N; i++)
  {
    cout << branch[i] << endl;
  }

}
