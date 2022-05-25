#include "hmsLivetimesB.cpp"

void runHmsBoiling(){

  clock_t t=clock();
  for(Int_t i=2073;i<2097;i++){
    if(i!=2077 && i!=2079 && i!=2086 &i!=2092)
      {
	hmsLivetimesB(i);
      }
  }
 t = clock()-t;
 printf("The Anaylsis took %.1f seconds \n",((float) t)/CLOCKS_PER_SEC);
  return;
}
