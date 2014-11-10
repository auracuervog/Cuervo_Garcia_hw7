#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define e 2.75
#define PI 3.14159265358979323846

void Initialize_Function(float *u1,float *u2, float *u3, int n_x);
void Euler(float *f, float *u1_initial, float *u1_past,float *u2_initial, float *u2_past,float *u3_initial, float *u3_past, int n_x, int n_t, double dt, double dx);

double flux_fn(double u1, double u2, double u3,int i);

int main(int argc, char **argv){

  double dt, dx;
  int n_x, n_t;

  float *f;

  float *u1_initial,*u2_initial, *u3_initial, *u1_past, *u2_past, *u3_past;

  FILE *file;


  char filename[64];
  sprintf (filename, "estado_%f.dat", atof(argv[1]));
 
  file=fopen(filename, "w");
  
  

  n_x=2001;


  dt=0.0001;
  dx=0.01;

  n_t=atof(argv[1])/dt;


  u1_initial = malloc(n_x * sizeof(float));
  u2_initial = malloc(n_x * sizeof(float));
  u3_initial = malloc(n_x * sizeof(float));

  u1_past = malloc(n_x * sizeof(float));
  u2_past = malloc(n_x * sizeof(float));
  u3_past = malloc(n_x * sizeof(float));


  f = malloc(3 * sizeof(float));

  Initialize_Function(u1_initial,u2_initial,u3_initial, n_x);


 
  Euler(f, u1_initial, u1_past,u2_initial, u2_past,u3_initial, u3_past, n_x, n_t, dt, dx);

  double P;
  int i;
  
  for(i=0;i<n_x;i++){

    P=0.4*(u3_initial[i]-0.5*(pow(u2_initial[i],2)/u1_initial[i]));
    
      
    fprintf(file, "%f \t %f \t %f \t %f\n", i*dx-10,(u2_initial[i]/u1_initial[i]),  P,u1_initial[i] );
      
  }

 
  fclose(file);

  return 0;
}



void Initialize_Function(float *u1, float *u2, float *u3, int s){
  
  int i;
  
  for(i=0;i<s/2;i++){
      u1[i]=1.0;
      u2[i]=0.0;
      u3[i]=250.0;
  }
  

  for(i=s/2;i<s;i++){
     u1[i]=0.125;
     u2[i]=0.0;
     u3[i]=25.0;
  }
  
}



void Euler(float *f, float *u1_initial, float *u1_past,float *u2_initial, float *u2_past,float *u3_initial, float *u3_past, int n_x, int n_t, double dt, double dx){

  int i;
  int j;
  float *u1_int, *u2_int, *u3_int;
  
  u1_int = malloc(n_x * sizeof(float));
  u2_int = malloc(n_x * sizeof(float));
  u3_int = malloc(n_x * sizeof(float));

  for(j=0;j<n_t;j++){

    for(i=0;i<n_x;i++){
    
      u1_past[i]=u1_initial[i];
      u2_past[i]=u2_initial[i];
      u3_past[i]=u3_initial[i];

    }
    
    
    for(i=0;i<n_x-1;i++){

   

      u1_int[i]=0.5*(u1_past[i+1]+u1_past[i])-(dt/(2*dx))*(flux_fn(u1_past[i+1],u2_past[i+1],u3_past[i+1],0)-flux_fn(u1_past[i],u2_past[i],u3_past[i],0));

     
      u2_int[i]=0.5*(u2_past[i+1]+u2_past[i])-(dt/(2*dx))*(flux_fn(u1_past[i+1],u2_past[i+1],u3_past[i+1],1)-flux_fn(u1_past[i],u2_past[i],u3_past[i],1));
      

      u3_int[i]=0.5*(u3_past[i+1]+u3_past[i])-(dt/(2*dx))*(flux_fn(u1_past[i+1],u2_past[i+1],u3_past[i+1],2)-flux_fn(u1_past[i],u2_past[i],u3_past[i],2));

       //if(u2_int[i]!=u2_int[i]){
       //printf("paila :( \t %d\n", i);
       //}
       
   		
    }

    for(i=1;i<n_x-1;i++){

 
      if(i==n_x-1){
	 printf("paila :( \t %f\n", u1_initial[i-1]);
      }
      u1_initial[i] = u1_past[i]-(dt/dx)*(flux_fn(u1_int[i],u2_int[i],u3_int[i],0)-flux_fn(u1_int[i-1],u2_int[i-1],u3_int[i-1],0));

      
      u2_initial[i] = u2_past[i]-(dt/dx)*(flux_fn(u1_int[i],u2_int[i],u3_int[i],1)-flux_fn(u1_int[i-1],u2_int[i-1],u3_int[i-1],1));

      u3_initial[i] = u3_past[i]-(dt/dx)*(flux_fn(u1_int[i],u2_int[i],u3_int[i],2)-flux_fn(u1_int[i-1],u2_int[i-1],u3_int[i-1],2));

      
							   
    }
      
  }

}

double flux_fn(double u1, double u2, double u3,int i){

  double g[3];

  g[0]=u2;
  g[1]=pow(u2,2)/u1+0.4*(u3-0.5*(pow(u2,2)/u1));
  g[2]=(u3+0.4*(u3-0.5*(pow(u2,2)/u1)))*(u2/u1);


  return g[i];

}
