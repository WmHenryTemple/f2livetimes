double getRate(Double_t run=2550,TString what="s1x"){

  FILE *fp = fopen("src/rates.txt","r");  
  Double_t rn,trig1,trig2,trig3,s1xs1y,s2xs2y,s1x,s1y,s2x,s2y,p1x7,p1y7,p2x7,p2y9,current;
  Double_t ncer,elLoLo, elLo, elHi, prLo, prHi,stof;
  Int_t ncols; 
  double_t result=0.;
  while (1) { 

    ncols = fscanf(fp,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf ",&rn,&s1x,&s1y,&s2x,&s2y,&p1x7,&p1y7,&p2x7,&p2y9,&s1xs1y,&s2xs2y,&trig1,&trig2,&trig3,&ncer,&elLoLo,&elLo,&elHi,&prHi,&prLo,&stof);
    //    cout << run <<endl;
    if (ncols < 0) break;
    if(rn==run && what=="s1x"){result=s1x;break;}
    if(rn==run && what=="s1y"){result=s1y;break;}
    if(rn==run && what=="s2x"){result=s2x;break;}
    if(rn==run && what=="s2y"){result=s2y;break;}
    if(rn==run && what=="trig1"){result=trig1;break;}
    if(rn==run && what=="trig2"){result=trig2;break;}
    if(rn==run && what=="trig3"){result=trig3;break;}
    if(rn==run && what=="s1xs1y"){result=s1xs1y;break;}
    if(rn==run && what=="elHi"){result=elHi;break;}
    if(rn==run && what=="elLo"){result=elLo;break;}
  }
  return result;
}

