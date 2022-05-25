#include "livetimesB.cpp"

void runBoiling(){

  clock_t t=clock();
  for(Int_t i=3204;i<3227;i++){
    if(i!=3208 && i!=3209 && i!=3216&i!=3222)
      {
	livetimesB(i);
      }
  }
 t = clock()-t;
 printf("The Anaylsis took %.1f seconds \n",((float) t)/CLOCKS_PER_SEC);
  return;
}
