struct par
{
  int id;
  int flag;
  float E;
  float px;
  float py;
  float pz;
  float vx;
  float vy;
  float vz;
  float fx; // final position
  float fy;
  float fz;
}; // SEMICOLON !!

void fill_info(par *p_list)
{
  for (int i=0; i<10; i++)
  {
    p_list[i].id   = i+1;
    p_list[i].flag = i+1;
    p_list[i].E    = i+1;
    p_list[i].px   = i+1;
  }
}

void par_struc()
{
  par p_list[10];

  fill_info(p_list);
  
  cout << "initialized information" << endl;
  for (int i=0; i<10; i++)
  {
    cout << "id " << p_list[i].id << endl;
  }
}
