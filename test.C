/****************
everytime I call Rndm() inside a function,
root gives error: 

 *** Break *** segmentation violation

 ***************/


float tt(float x)
{
  return x*2;
}
TRandom *r;

double pro_air_h()
{
  int s  = 0;
  double h  = 5.;
  double p  = 0.;

  //r -> Rndm();
  // if (r -> Rndm() > 2.5)
  // {
  //   s++;
  // }
  return h;
}
void test(){
  float t = tt(2.5);
  // cout << t << endl;

  TRandom *r = new TRandom();
  r -> SetSeed(111);
  // double x = 0;
  // while (r -> Rndm() > 0.5){
  //   x = 1;
  // }
  double x;
  x = pro_air_h();
  cout << x << endl;
}
