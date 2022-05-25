Double_t myFunc(Double_t *x, Double_t *par)
{
  Double_t xx=x[0];
  Double_t answer=0;
  for(Int_t i=0;i<par[0];i++)
    {

answer+=1/TMath::Factorial(i)*pow((par[1]*xx),i)*TMath::Exp(-par[1]*xx);
    }
  return answer;
}

void modelttest(){
  TF1 *f1=new TF1("f1",myFunc,0,50000,2);
  f1->SetParameter(0,1);
  f1->SetParameter(1,.0002);
  f1->Draw();
}
