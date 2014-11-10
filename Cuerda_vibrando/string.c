#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define T 40 //N
#define L 100 //M
#define N 100

float *copy(float *u);

int main(int argc, char **argv)
{
  float rho, npoints,c,r;
  FILE *file;
  float *u_initial;
  float *u_future;
  float *u_present;
  float *u_past;
  float delta_x, delta_t;
  int i, j,t;

  npoints = 100.0;
  rho = atof(argv[1]);
  delta_x = (L/npoints);
  delta_t = 0.0005;
  c = sqrt(T/rho);
  r = c*(delta_t/delta_x);

  u_initial = malloc(sizeof(float)*N);
  u_future = malloc(sizeof(float)*N);
  u_present = malloc(sizeof(float)*N);
  u_past = malloc(sizeof(float)*N);
  
  //Creando el nombre del archivo
  char filename[100];
  snprintf(filename, sizeof(char)*100,"string_%.2f.dat",(float) rho);

  file = fopen(filename,"w");
  if(!file)
    {
      printf("problems opening the file %s\n", filename);
      exit(1);
    }
  //Condiciones iniciales
  for(i=0;i<N;i++){
    if((i*delta_x) <= (0.8*L)){
      u_initial[i] = (1.25*i*delta_x)/L;
    }
    else{
      u_initial[i] = (5-((5*i*delta_x)/L));
    }
  }
 
  //Condiciones de contorno: puntos fijos
  u_initial[0] = 0.0; 
  u_initial[N-1] = 0.0;
  u_future[0] = 0.0;
  u_future[N-1] = 0.0;

  for(i=0;i<N;i++){
    fprintf(file,"%f ",u_initial[i]);
  }
  fprintf(file,"\n");

  //Primer paso
  for(i=0;i<N;i++){
    if(i==0){
      fprintf(file,"%f ",u_future[0]);
    }
    else if(i==N-1){
      fprintf(file,"%f ",u_future[0]);
    }
    else{
      u_future[i] = u_initial[i] + (pow(r,2)/2.0) * (u_initial[i+1] - 2.0*u_initial[i] + u_initial[i-1]);
      fprintf(file,"%f ",u_future[i]);
    } 
  }
  fprintf(file,"\n");

  u_past = copy(u_initial);
  u_present = copy(u_future);
  
  //Iteraciones siguientes
  t = 120;
  for(j=1;j<t;j++){
    for(i=0;i<N;i++){
      if(i==0){
	u_future[0] = 0.0;
	fprintf(file,"%f ",u_future[0]);
      }
      else if(i==N-1){
	u_future[N-1] = 0.0;
	fprintf(file,"%f ",u_future[N-1]);
      }
      else{     
	u_future[i] = ((2.0*(1.0-pow(r,2)))*u_present[i]) - u_past[i] + ((pow(r,2))*(u_present[i+1] + u_present[i-1]));
	fprintf(file,"%f ",u_future[i]);
      }
    }
    u_past = copy(u_present);
    u_present = copy(u_future);
    fprintf(file,"\n");
  }
  return 0;
}

float *copy(float *u){
  float *u_new;
  int i;
  u_new = malloc(sizeof(float)*N);

  for(i=0;i<N;i++){
    u_new[i] = u[i];
  }
  return u_new;
}
