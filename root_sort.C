void root_sort()
{
   float a[4]={2, 1, 5, 4};
   long long size = 4;
   long long ind[4];
   TMath::Sort(size,a,ind);
   for (int i = 0; i < size; ++i) 
      std::cout << "INDEX   "<< ind[i] << std::endl;
}

