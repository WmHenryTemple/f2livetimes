// remember to remove first row with column labels
double getLivetime(Double_t run=2550,TString what="tlt"){

  FILE *fp = fopen("livetimes_April2021.txt","r");  
  Double_t s1x,rn, clt, clterr, elt, elterr, tlt, tlterr;
  Int_t ncols; 
  double_t result=-99;

  while (1) { 
    ncols = fscanf(fp,"%lf %lf %lf %lf %lf %lf %lf %lf",&rn, &s1x, &clt, &clterr,&elt, &elterr,&tlt, &tlterr);
    //    cout << run <<endl;
    if (ncols < 0) break;
    if(rn==run && what=="s1xrate"){result=s1x;break;}
    if(rn==run && what=="clt"){result=clt;break;}
    if(rn==run && what=="clte"){result=clterr;break;}
    if(rn==run && what=="elt"){result=elt;break;}
    if(rn==run && what=="elte"){result=elterr;break;}
    if(rn==run && what=="tlt"){result=tlt;break;}
    if(rn==run && what=="tlte"){result=tlterr;break;}
  }
  fclose (fp);
  return result;
}

