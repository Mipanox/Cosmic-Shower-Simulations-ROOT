void hist1()
{
  TH1F* hist_test = new TH1F("test","test",100,0,5000);
  //                       obj name, title
  //                     --see ntu_rdm.C        for saving the object
  //                     --    read_root_file.C for loading and browsing it.
  int sum=0;

  for (int i=1; i<=100; i++)
  {
    sum += i;
    hist_test -> SetBinContent(i,sum);
    hist_test -> SetBinContent(sum,i);
  }

  hist_test -> Draw();
}
