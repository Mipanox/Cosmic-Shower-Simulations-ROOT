// Simulation for Hillas Splitting proton and pion production
// only interaction with air, NO pion decay !!!

/*-------
  Header
  -------*/

// PDG code identification for particles
int pro_p = 2212;
int pio_0 = 111;
int pio_p = 211;
int pio_n =-211;

void HS(int id, float E, float theta, float phi,
	float x, float y, float z);
// initialize Hillas Spilt branches = 4
TRandom *r;
const int n_br = 4;

// mass in GeV
float M_pro = 0.938;
float M_pi  = 0.13977;
float M_pi0 = 0.13498;

// Xsec in g cm-3
float rho0 = 1.021/1000;
float A    = 8;

float pi   = TMath::Pi();
// class
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
};

// how many particles
const int bank_size = 200000;
par Ptcl_Bank[bank_size];
int n_particle; // produced number

void Ptcl_Reg(int id, int flag, float px, float py, float pz,
	      float vx, float vy, float vz);
void split_N(float E_in, float E_br[]);
void E_split_two(float E_in, float &E_A, float &E_B);
float Get_H_from_X(float X, float h0, float theta);
void Get_P_Int_Position(float theta, float phi,
			float x, float y, float z,
			float &vx, float &vy, float &vz);
void Get_Pi_Int_Position(float theta, float phi,
			 float x, float y, float z,
			 float &vx, float &vy, float &vz);
void HS(int id, float E, float theta, float phi,
	float x, float y, float z);


/*****************************************/



/*---------
  Main Part
  ---------*/

void rec_pion()
{
  TCanvas *c1  = new TCanvas("c1","c1",0,0,1200,600);
  c1 -> Divide(2,1);
  
  TNtuple *ntu = new TNtuple("ntu","ntu","id:flag:E:px:py:pz:x:y:z");
  r = new TRandom();

  // a thousand incoming protons !
  for (int ievt=0; ievt<5000; ievt++)
  {
    n_particle = 0; // nothing generated yet

    float E = 1000; // initial energy of proton, in GeV
    float theta = acos(r->Rndm());
    float phi   = r -> Rndm() * pi * 2;

    float x=0; float y=0; float z=1.e10; // incident position, z=inf
    float vx ; float vy ; float vz;      // in km

    // where interaction happens
    Get_P_Int_Position(theta, phi, x, y ,z, vx, vy, vz);

    HS(pro_p, E, theta, phi, vx, vy, vz);

    float E_th = 10; // threshold for particle energy
    int i_particle = 0; // number of particles produced

    // loop through all particles (now just for protons)
    // dynamically: n_partcile is INCREASING during the process !
    while (i_particle < n_particle)
    {
      float id   = Ptcl_Bank[i_particle].id;
      float flag = Ptcl_Bank[i_particle].flag; // if alive, assign 1
                                               // if dead, then 0
      float E    = Ptcl_Bank[i_particle].E;

      x = Ptcl_Bank[i_particle].vx; // where the first interaction happens
      y = Ptcl_Bank[i_particle].vy; // from the incoming proton (outside the loop)
      z = Ptcl_Bank[i_particle].vz;

      if (abs(id)==pro_p && flag==1 && E>E_th)
      {
        Get_P_Int_Position(theta,phi,x,y,z,vx,vy,vz);

	if (vz > 0) // interaction must take place above ground
	{
          HS(pro_p,Ptcl_Bank[i_particle].E,theta,phi,vx,vy,vz);
	  Ptcl_Bank[i_particle].flag = 0; // now it's dead
	}
      }

      if (abs(id)==pio_p && flag==1 && E>E_th)
      {
        Get_Pi_Int_Position(theta,phi,x,y,z,vx,vy,vz);

	if (vz > 0) // interaction must take place above ground
	{
          HS(pio_p,Ptcl_Bank[i_particle].E,theta,phi,vx,vy,vz);
	  Ptcl_Bank[i_particle].flag = 0; // now it's dead
	}
      }

      i_particle++; // one proton produced !
    }

    for (int i_p=0; i_p<n_particle; i_p++)
    {
      float id   = Ptcl_Bank[i_p].id;
      float flag = Ptcl_Bank[i_p].flag;
      float E    = Ptcl_Bank[i_p].E;
      float px   = Ptcl_Bank[i_p].px;
      float py   = Ptcl_Bank[i_p].py;
      float pz   = Ptcl_Bank[i_p].pz;
      float vx   = Ptcl_Bank[i_p].vx;
      float vy   = Ptcl_Bank[i_p].vy;
      float vz   = Ptcl_Bank[i_p].vz;

      ntu -> Fill(id,flag,E,px,py,pz,vx,vy,vz);
    }    
  }
  c1 -> cd(1);
  ntu -> Draw("z", "id==2212");
  ntu -> SetTitle("Secondary Proton Height");
  // adding title and color for Ntuple FAILED

  c1 -> cd(2);
  ntu -> Draw("z", "id==211");
  ntu -> SetLineColor(2);
  ntu -> SetTitle("Secondary Pion Height");
  
}


/*------------
  Fill in Bank
  ------------*/

void Ptcl_Reg(int id, int flag, float px, float py, float pz,
	      float vx, float vy, float vz)
{
  float mass;
  if      (id == pio_0) mass = M_pi0;
  else if (id == pio_p) mass = M_pi;
  else if (id == pro_p) mass = M_pro;

  Ptcl_Bank[n_particle].id   = id;
  Ptcl_Bank[n_particle].flag = flag;
  Ptcl_Bank[n_particle].E    = sqrt(px*px+py*py+pz*pz+mass*mass);
  Ptcl_Bank[n_particle].px   = px;
  Ptcl_Bank[n_particle].py   = py;
  Ptcl_Bank[n_particle].pz   = pz;
  Ptcl_Bank[n_particle].vx   = vx;
  Ptcl_Bank[n_particle].vy   = vy;
  Ptcl_Bank[n_particle].vz   = vz;

  n_particle++; // move to the next slot !
}


/*------------------
  Other sub-funcions
  ------------------*/

void split_N(float E_in, float E_br[])
{
  float temp[n_br-1];
  
  for (int i=0; i<n_br-1; i++)
  {
    temp[i] = r -> Rndm();
  }

  int ind[n_br-1];
  TMath::Sort(n_br-1,temp,ind);
  
  int pd = ind[0];
  E_br[0] = (1-temp[pd]) * E_in; // the first portion
  
  for (int i=1; i<n_br-1; i++)
  {
    int id = ind[i];
    int dd = ind[i-1];
    E_br[i] = (temp[dd] - temp[id]) * E_in;
  }

  int ld = ind[n_br-2];
  E_br[n_br-1] = (temp[ld]-0) * E_in;
}

void E_split_two(float E_in, float &E_A, float &E_B)
{
  float frac = r -> Rndm();
  E_A = frac       * E_in;
  E_B = (1 - frac) * E_in;
}


float Get_H_from_X(float X, float h0, float theta)
{
  float costheta = fabs(cos(theta));
  float h;

  if (costheta != 0)  h = -log(X*costheta/(rho0*A*100000) + exp(-h0/A)) * A;
  else                h = h0;
  return h;
}

void Get_P_Int_Position(float theta, float phi,
			float x, float y, float z,
			float &vx, float &vy, float &vz)
{
  float lbd_pro = 87; // g cm-2
  float X  = r -> Exp(lbd_pro);
  float h0 = z;

  // vertex positions
  vz = Get_H_from_X(X, h0, theta);
  float R = vz*tan(theta);
  vx = R * cos(phi);
  vy = R * sin(phi);
}
void Get_Pi_Int_Position(float theta, float phi,
		 	 float x, float y, float z,
			 float &vx, float &vy, float &vz)
{ // for pions
  float lbd_pio = 116; // g cm-2
  float X  = r -> Exp(lbd_pio);
  float h0 = z;

  // vertex positions
  vz = Get_H_from_X(X, h0, theta);
  float R = vz*tan(theta);
  vx = R * cos(phi);
  vy = R * sin(phi);
}

/*------------
  Hillas Split
  ------------*/

void HS(int id, float E, float theta, float phi,
	float x, float y, float z)
{
  float E_A = 0;
  float E_B = 0;

  float mass = M_pro; 

  while (E_A < mass)
  {
    E_split_two(E, E_A, E_B);
    // if E_A < mass, physically impossible, so do it again
  }

  float p  = sqrt(E_A*E_A-mass*mass); // relativity
  float px = -p*sin(theta)*cos(phi);
  float py = -p*sin(theta)*sin(phi);
  float pz = -p*cos(theta);

  Ptcl_Reg(id, 1, px, py, pz, x, y, z); // flag = 1: survival

  float E_br[n_br];
  // split into n_br after generating the first proton,
  // which has been registered !

  split_N(E_B, E_br);

  for (int j=0; j<n_br; j++)
  {
    // loop through all sub-branches of pion
    float E_in = E_br[j];
    float E_a, E_b;

    while (E_in > 0)
    {
      E_split_two(E_in, E_a, E_b);
      float E_k_pi = E_a;
      float E_t_pi = E_a+M_pi; // total energy

      E_in = E_b-M_pi; // taxed

      // marked as "E" in output pdf
      float p_pi  = sqrt(E_t_pi*E_t_pi-M_pi*M_pi);
      float px_pi = -p*sin(theta)*cos(phi);
      float py_pi = -p*sin(theta)*sin(phi);
      float pz_pi = -p*cos(theta);          // direction of p does not change
      
      Ptcl_Reg(pio_p, 1, px_pi, py_pi, pz_pi, x, y, z);
    }
  }
}
