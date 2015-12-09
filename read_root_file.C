void read_root_file()
{
  TFile *_file0 = TFile::Open("ntu_rdm.root");

  ntuple -> Draw("x:y^3");
  // object name !

  //-- Alternative way:
  //  (in the command line)
  //$ root filename.root
  //$ (C-p: root automatically 'insert' a command for us !)
  //$ TBrowser 'browser name' # can be a letter
  //  # interactive browser
}
