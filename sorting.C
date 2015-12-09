struct score
{
  string name;
  float math;
  float phys;
}; // SEMICOLON !!

void sorting() // swap sorting
{
  string name[5]={"A","B","C","D","E"};
  float math[5]={80,60,70,60,100};
  float phys[5]={100,76,80,75,88};

  score mid[5];
  for (int i=0; i<5; i++)
  {
    mid[i].name=name[i];
    mid[i].math=math[i];
    mid[i].phys=phys[i];
  }


  for (int i=0; i<4; i++)
  {
    for (int j=i+1; j<5; j++)
    {
      if (mid[i].phys > mid[j].phys)
      {
	score mid_t=mid[i];
        mid[i] = mid[j];
	mid[j] = mid_t;

      }
      
      /* Naive approach
      if (phys[i] < phys[j])
      {
	// sort by phys score
	
        float phys_t = phys[i];
	phys[i] = phys[j];
	phys[j] = phys_t;

	string name_t = name[i];
	name[i] = name[j];
	name[j] = name_t;

	float math_t = math[i];
	math[i] = math[j];
	math[j] = math_t;
      }
      */
    }
  }

  cout << "Sorted information" << endl;
  cout << "Name Phys Math" << endl;

  for (int i=0; i<5; i++)
  {
    cout << mid[i].name << " " << mid[i].phys << " " << mid[i].math << endl;
    // cout << name[i] << " " << phys[i] << " " << math[i] << endl;
  }
}
