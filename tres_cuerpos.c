#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define e 1

void RK4_step(double delta_t, double t, double *q1, double *p1);                              //Runge Kutta para el cuerpo 1
void leapfrog_step(double delta_t, double t, double *q1, double *p1);                         //Leapfrog para el cuerpo 1
void RK43_step(double delta_t, double t, double *q3, double *p3, double *q1, double *p1);     //Runge Kutta para el cuerpo 3
void leapfrog3_step(double delta_t, double t, double *q3, double *p3, double *q1, double *p1); //Leapfrog para el cuerpo 3

//Funciones que permiten resolver las ecuaciones de Hamilton para el problema de tres cuerpos.
double deriv_q1(double t, double q1, double p1);
double deriv_p1(double t, double q1, double p1);
double deriv_q3(double t, double q3, double p3, double q1, double p1);
double deriv_p3(double t, double q3, double p3, double q1, double p1);

//Funcion para calcular la energia
double Energia(double q3, double p3, double q1, double p1);

FILE *salida_1;
FILE *salida_2;
FILE *salida_3;
FILE *salida_4;

int main(int argc, char **argv){
   
  char ArchSalida1[] = "salida_1.dat";
  salida_1 = fopen(ArchSalida1, "w");
  char ArchSalida2[] = "salida_2.dat";
  salida_2 = fopen(ArchSalida2, "w");
  char ArchSalida3[] = "salida_3.dat";
  salida_3 = fopen(ArchSalida3, "w");
  char ArchSalida4[] = "salida_4.dat";
  salida_4 = fopen(ArchSalida4, "w");
  

  argc=4;
  double q1_RK4, q1_LF;
  double p1_RK4, p1_LF;
  double q3_RK43, q3_LF3;
  double p3_RK43, p3_LF3;
  double energia_RK4;
  double energia_LF4;
  double t;
  int j;
  int k; 
  for (j=1;j<=4;j++)
  {
  
  
  for (k=0;k<=100; k++)
    {
  double T=3E3;
  double delta_t=6E-3;
  int n_step = (int)(T/delta_t);
  int i;

  t=0.0;
  q1_RK4 = atof(argv[j]);
  //q1_RK4= 0.35355339059327376220; 
  //q1_RK4= 0.4325;
  p1_RK4=0.0;
  q1_LF = q1_RK4; 
  //q1_LF = 0.4325;
  p1_LF=0.0;
  q3_RK43=-0.1+0.03*k;
  p3_RK43=0.0;
  q3_LF3=-0.1+ 0.03*k;
  p3_LF3=0.0;


  for(i=0;i<n_step;i++){
   
   if(p1_RK4 <=0.001 && p1_RK4 >=-0.0001 )// seccion de poincare para p entre -0.001 y 0.001
   {
   
    if(j==1){fprintf(salida_1,"%f %.15e %.15e %.15e %.15e %.15e %.15e %.15e %.15e %.15e %.15e\n", t, q1_RK4, p1_RK4, q1_LF, p1_LF, q3_RK43, p3_RK43, q3_LF3, p3_LF3, energia_RK4, energia_LF4);}
    if(j==2){fprintf(salida_2,"%f %.15e %.15e %.15e %.15e %.15e %.15e %.15e %.15e \n", t, q1_RK4, p1_RK4, q1_LF, p1_LF, q3_RK43, p3_RK43, q3_LF3, p3_LF3);}
    if(j==3){fprintf(salida_3,"%f %.15e %.15e %.15e %.15e %.15e %.15e %.15e %.15e \n", t, q1_RK4, p1_RK4, q1_LF, p1_LF, q3_RK43, p3_RK43, q3_LF3, p3_LF3);}
    if(j==4){fprintf(salida_4,"%f %.15e %.15e %.15e %.15e %.15e %.15e %.15e %.15e \n", t, q1_RK4, p1_RK4, q1_LF, p1_LF, q3_RK43, p3_RK43, q3_LF3, p3_LF3);}
  }
    RK4_step(delta_t, t, &q1_RK4, &p1_RK4);
    RK43_step(delta_t, t, &q3_RK43, &p3_RK43, &q1_RK4, &p1_RK4);
    leapfrog_step(delta_t, t, &q1_LF, &p1_LF);
    leapfrog3_step(delta_t, t, &q3_LF3, &p3_LF3, &q1_LF, &p1_LF);
    energia_RK4 = Energia(q3_RK43, p3_RK43, q1_RK4, p1_RK4);
    energia_LF4 = Energia(q3_LF3, p3_LF3, q1_LF, p1_LF);
    t += delta_t;     
    
  	}
  }
  }

  return 0;
}

double deriv_q1(double t, double q1, double p1){
return p1;

}
double deriv_q3(double t, double q3, double p3, double q1, double p1){
  return p3;
}


double deriv_p1(double t, double q1, double p1){
  return -2*q1/(pow((4*q1*q1+1),1.5));
}
double deriv_p3(double t, double q3, double p3, double q1, double p1){
 return   ((q1-q3)/(pow(((q1-q3)*(q1-q3)+0.25),1.5)) - (q1+q3)/(pow(((q1+q3)*(q1+q3)+0.25),1.5)));
}

//Definición del metodo integrador simplectico a cuarto orden para las cordenadas del espacio de fase la masa 1.

void leapfrog_step(double delta_t, double t, double *q1, double *p1){

  double q1_in;
  double p1_in;

  q1_in = *q1;
  p1_in = *p1;

 /*drift*/
  q1_in += 0.675603596 * p1_in * delta_t;

 /*kick*/
  p1_in += 1.351207192 * deriv_p1(t,q1_in,p1_in) * delta_t;

 /*drift*/
  q1_in += -0.175603596 * p1_in * delta_t;

 /*kick*/
  p1_in += -1.702414384 * deriv_p1(t,q1_in,p1_in) * delta_t;

 /*drift*/
  q1_in += -0.175603596 * p1_in * delta_t;

 /*kick*/
  p1_in += 1.351207192 * deriv_p1(t,q1_in,p1_in) * delta_t;

 /*drift*/
  q1_in +=  0.675603596 * p1_in * delta_t;

  *q1 = q1_in;
  *p1 = p1_in;
}

//Definición del metodo integrador simplectico a cuarto orden para las cordenadas del espacio de fase de la masa 3.

void leapfrog3_step(double delta_t, double t, double *q3, double *p3, double *q1, double *p1){

  double q3_in;
  double p3_in;
  double p1_in;
  double q1_in;

  q1_in = *q1;
  p1_in = *p1; 
  q3_in = *q3;
  p3_in = *p3;

  /*drift*/
  q3_in += 0.675603596 * p3_in * delta_t;
 
  /*kick*/
  p3_in +=  1.351207192 * deriv_p3(t, q3_in , p3_in, q1_in, p1_in) * delta_t;
  
  /*drift*/
  q3_in += -0.175603596 * p3_in * delta_t;
 
  /*kick*/
  p3_in +=  -1.702414384 * deriv_p3(t, q3_in, p3_in, q1_in, p1_in) * delta_t;

  /*drift*/
  q3_in += -0.175603596 * p3_in * delta_t;

  /*kick*/
  p3_in +=  1.351207192 * deriv_p3(t, q3_in , p3_in, q1_in, p1_in) * delta_t;
  
  /*drift*/
  q3_in += 0.675603596 * p3_in * delta_t;

  *q3 = q3_in;
  *p3= p3_in;
  *q1 = q1_in;
  *p1 = p1_in;
}

//Definición del método de Runge Kutta de cuarto orden para las cordenadas del espacio de fase de la masa 1.

void RK4_step(double delta_t, double t, double *q1, double *p1){
  double k1, k2, k3, k4;
  double l1, l2, l3, l4;
  double q1_in;
  double p1_in;
  q1_in = *q1;
  p1_in = *p1;


  k1 = deriv_q1(t,q1_in,p1_in);  
  l1 = deriv_p1(t,q1_in,p1_in);  

  k2 = deriv_q1(t + delta_t*0.5, q1_in + k1*delta_t*0.5, p1_in + l1*delta_t*0.5);
  l2 = deriv_p1(t + delta_t*0.5, q1_in + k1*delta_t*0.5, p1_in + l1*delta_t*0.5) ;

  k3 = deriv_q1(t + delta_t*0.5, q1_in + k2*delta_t*0.5, p1_in + l2*delta_t*0.5);
  l3 = deriv_p1(t + delta_t*0.5, q1_in + k2*delta_t*0.5, p1_in + l2*delta_t*0.5);

  k4 = deriv_q1(t + delta_t, q1_in + k3*delta_t, p1_in + l3*delta_t);
  l4 = deriv_p1(t + delta_t, q1_in + k3*delta_t, p1_in + l3*delta_t);

  q1_in += (k1/6.0 + k2/3.0 + k3/3.0 + k4/6.0)*delta_t;
  p1_in += (l1/6.0 + l2/3.0 + l3/3.0 + l4/6.0)*delta_t;

  *q1 = q1_in;
  *p1 = p1_in;

}

//Definición del método de Runge Kutta de cuarto orden para las cordenadas del espacio de fase de la masa 3.

void RK43_step(double delta_t, double t, double *q3, double *p3, double *q1, double *p1){
  double k13, k23, k33, k43;
  double l13, l23, l33, l43;
  double k1, k2, k3, k4;
  double l1, l2, l3, l4;
  double q3_in;
  double p3_in;
  double p1_in;
  double q1_in;

  q3_in = *q3;
  p3_in = *p3;
  q1_in = *q1;
  p1_in = *p1;

  k13 = deriv_q3(t,q3_in,p3_in,q1_in,p1_in);  
  l13 = deriv_p3(t,q3_in,p3_in,q1_in,p1_in);  

  k23 = deriv_q3(t + delta_t*0.5, q3_in + k13*delta_t*0.5, p3_in + l13*delta_t*0.5,q1_in + k1*delta_t*0.5,p1_in + l1*delta_t*0.5);
  l23 = deriv_p3(t + delta_t*0.5, q3_in + k13*delta_t*0.5, p3_in + l13*delta_t*0.5,q1_in + k1*delta_t*0.5,p1_in + l1*delta_t*0.5) ;

  k33 = deriv_q3(t + delta_t*0.5, q3_in + k23*delta_t*0.5, p3_in + l23*delta_t*0.5,q1_in + k2*delta_t*0.5,p1_in + l2*delta_t*0.5);
  l33 = deriv_p3(t + delta_t*0.5, q3_in + k23*delta_t*0.5, p3_in + l23*delta_t*0.5,q1_in + k2*delta_t*0.5,p1_in + l2*delta_t*0.5);

  k43 = deriv_q3(t + delta_t, q3_in + k33*delta_t, p3_in + l33*delta_t,q1_in +  k3*delta_t,p1_in + l3*delta_t);
  l43 = deriv_p3(t + delta_t, q3_in + k33*delta_t, p3_in + l33*delta_t,q1_in +  k3*delta_t,p1_in + l3*delta_t);

  q3_in += (k13/6.0 + k23/3.0 + k33/3.0 + k43/6.0)*delta_t;
  p3_in += (l13/6.0 + l23/3.0 + l33/3.0 + l43/6.0)*delta_t;

  *q3 = q3_in;
  *p3 = p3_in;
  *q1 = q1_in;
  *p1 = p1_in;
}

double Energia(double q3, double p3, double q1, double p1)
{
double T;
double V;
double H;
double q3_in;
double p3_in;
double p1_in;
double q1_in;  

  q3_in = q3;
  p3_in = p3;
  q1_in = q1;
  p1_in = p1;

  T = p1_in*p1_in*0.5;
  V = -(1)/(pow(4*q1_in*q1_in+1,0.5));
  H = T+V;
  return H;
}

