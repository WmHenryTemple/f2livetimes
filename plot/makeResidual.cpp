#include "readReport.cpp"
#include "src/getRate.cpp"



TGraphErrors* makeResidual(Int_t fact=99,Double_t tau=2.04e-7){

  FILE *fp = fopen("livetimes.txt","r");  
  Float_t ps, rt, eto, etf,eso, esf, tto, ttf, tso, tsf, trig1rt;
  Float_t denom,num,clt,tlt,elt,tlte,clte,elte,model;
  Int_t ncols,rn; 
  vector <float> rate, run, dt, err;
  TF1 *flt=new TF1("flt","1/(1+[0]*x)",0,5);
  flt->SetLineStyle(7);
  flt->SetParName(0,"Busy Time");
  flt->SetParameter(0,tau);
  while (1) { 
    ncols = fscanf(fp,"%d %f %f %f %f %f %f %f %f %f %f %f",&rn,&ps,&rt,&trig1rt,&eto,&etf,&eso,&esf,&tto,&ttf,&tso,&tsf);
    if (ncols < 0) break;
    if(ps==fact||fact==99){
      //Total LT
      num=eto;  //edtm triggers beam on
      denom=eso;//edtm scaler counts beam on       
      tlt=num/denom*ps;
      tlte=TMath::Sqrt(num*(1-num/denom))*ps/denom;
      //CLT
      num=tto+eto; //edtm+trig2 all triggers
      denom=tso;   //trig2 scaler counts
      clt=num/denom*ps;
      clte=TMath::Sqrt(num*(1-num/denom))*ps/denom;
      elte=calcRatioErr(tlt,tlte,clt,clte);
      elt=tlt/clt;
      Double_t planeRate=getRate(rn,"s1x");
      rate.push_back(planeRate);
      model=flt->Eval(planeRate);
	  dt.push_back(elt/model);
	  err.push_back(elte/model);
	  run.push_back(rn);
	  //	  rate.push_back(trig1rt);
//	  rate.push_back(readReport(rn,"ngcer rate")*1000.);
//	  	  rate.push_back(readReport(rn,"p1x rate")*1000.);



	 
	  //	  if(fact==1) cout << ps <<endl;
	  if(readReport(rn,"p1x rate")>1000)cout<<rn<<"\t"<<ps<<endl;

    }
  }
  Int_t pts=run.size();
  TGraphErrors *g=new TGraphErrors(pts,&rate[0],&dt[0],0,&err[0]);
  //  g->SetMarkerStyle(20);
  //  g->Draw();
  return g;
}

