#include "readReport.cpp"
#include "src/getRate.cpp"


Double_t calcBinomRatioErr(Double_t numerCnts, Double_t denomCnts) {
  //  return (0.5*(Double_t) numerCnts / (Double_t) denomCnts) * TMath::Sqrt((1./((Double_t) numerCnts)) + (1./((Double_t) denomCnts)));
  return ((Double_t) numerCnts / (Double_t) denomCnts) * TMath::Sqrt( TMath::Power(1./(Double_t)numerCnts + 1./TMath::Sqrt(numerCnts),2) + (1./((Double_t) denomCnts)));

}

Double_t calcRatioErr(Double_t numer, Double_t numerErr, Double_t denom, Double_t denomErr) {
  return (numer/denom) * TMath::Sqrt(TMath::Power(numerErr/numer, 2.) + TMath::Power(denomErr/denom, 2.));
}

TGraphErrors* makeGr(Int_t fact=1,Int_t option=1, Int_t eRate=1){

  FILE *fp = fopen("livetimes.txt","r");  
  Float_t ps, rt, eto, etf,eso, esf, tto, ttf, tso, tsf, trig1rt;
  Float_t denom,num,clt,tlt,elt,tlte,clte,elte, cut;
  Int_t ncols,rn; 
  vector <float> rate, run, dt, err;
  while (1) { 
         ncols = fscanf(fp,"%d %f %f %f %f %f %f %f %f %f %f %f %f",&rn,&ps,&rt,&trig1rt,&cut,&eto,&etf,&eso,&esf,&tto,&ttf,&tso,&tsf);
    //      ncols = fscanf(fp,"%d %f %f %f %f %f %f %f %f %f %f %f",&rn,&ps,&rt,&trig1rt,&eto,&etf,&eso,&esf,&tto,&ttf,&tso,&tsf); 
   //    ncols = fscanf(fp,"%f %f %f %f %f %f %f %f %f %f %f %f",&rn,&ps,&rt,&s1x,&eto,&etf,&eso,&esf,&tto,&ttf,&tso,&tsf);
 
    //    ncols = fscanf(fp,"%d %f %f %f %f %f %f %f %f %f %f",&rn,&ps,&rt,&eto,&etf,&eso,&esf,&tto,&ttf,&tso,&tsf);
    //    cout << run <<endl;
    if (ncols < 0) break;
    if((ps==fact||fact==99)&&rn>0&&ps<=17&&rn<3902){
      if(option==1){num=eto;denom=eso;}       // edtm TLT  
      if(option==2){num=tto+eto;denom=tso;}  // CLT     
      //      if(option==2){num=tto;denom=tso-eso;}       
      //      if(option==1){num=eto+etf;denom=eso+esf;}       
      //      if(option==2){num=tto+ttf;denom=tso+tsf;}       
      if(option==1 || option==2)
	{
	  //	  rate.push_back(rt/ps);
	  rate.push_back(rt);
	  run.push_back(rn);
	  dt.push_back(num/denom*ps);
	  //err.push_back(calcBinomRatioErr(num,denom)*ps);
	
	Double_t did=num;
	Double_t should=denom;
	Double_t fid=did/should;
	//	Double_t error=TMath::Sqrt(did*fid*(abs(1-fid)))/should;
	//	Double_t error=TMath::Sqrt(1/did)*ps*fid;
	//	Double_t error=TMath::Sqrt(did)*ps/should;
	Double_t error=TMath::Sqrt(num*(1-num/denom))*ps/denom;
	err.push_back(error);
	  //	  	  err.push_back(ps/denom);
	if(num/denom*ps>1.0)cout << rn <<"\t"<<ps<< "\t" << num << "\t" << denom <<"\t"<<num/denom*ps << "\t" << error << endl;
	}
      if(option==3)
	{

	  //Total LT
	  num=eto;  //edtm triggers beam on
	  denom=eso;//edtm scaler counts beam on       
	  tlt=num/denom*ps;
	  tlte=TMath::Sqrt(num*(1-num/denom))*ps/denom;
	  //CLT
	  num=tto+eto; //edtm+trig2 all triggers
	  denom=tso;   //trig2 scaler counts
	  //	  num=tto; //edtm+trig2 all triggers
	  //	  denom=tso-eso;   //trig2 scaler counts
	  clt=num/denom*ps;
	  clte=TMath::Sqrt(num*(1-num/denom))*ps/denom;
	  elte=calcRatioErr(tlt,tlte,clt,clte);
	  elt=tlt/clt;
	  dt.push_back(elt);
	  err.push_back(elte);
	  run.push_back(rn);
	  //	  rate.push_back(trig1rt);
//	  rate.push_back(readReport(rn,"ngcer rate")*1000.);
//	  	  rate.push_back(readReport(rn,"p1x rate")*1000.);

	  if(eRate==0)rate.push_back(trig1rt);//really s1x
	  if(eRate==1)rate.push_back(getRate(rn,"s1x"));
	  if(eRate==2)rate.push_back(getRate(rn,"s1y"));
	  if(eRate==3)rate.push_back(getRate(rn,"s2x"));
	  if(eRate==4)rate.push_back(getRate(rn,"s2y"));
	  if(eRate==5)rate.push_back(getRate(rn,"trig1"));
	  if(eRate==6)rate.push_back(getRate(rn,"s1xs1y"));
	  if(eRate==7)rate.push_back(getRate(rn,"elHi"));
	  if(eRate==8)rate.push_back(getRate(rn,"elLo"));
	  if(eRate==10)rate.push_back(getRate(rn,"stof"));

	  //	  double test=getRate(rn,"s1x");	 
	  //	  if(test>400000)cout << "High Rate Run:"<<rn<<"  Rate: "<<test<<endl;
	  //	  if(fact==1) cout << ps <<endl;
		 //	  if(readReport(rn,"p1x rate")>1000)cout<<rn<<"\t"<<ps<<endl;
	}
    }
  }
  Int_t pts=run.size();
  TGraphErrors *g=new TGraphErrors(pts,&rate[0],&dt[0],0,&err[0]);
  //  g->SetMarkerStyle(20);
  //  g->Draw();
  return g;
}

