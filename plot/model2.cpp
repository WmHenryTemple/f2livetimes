Double_t myFunc(Double_t n, Double_t tau, Double_t x)
{
  return 1/TMath::Factorial(n)*pow((tau*x),n)*TMath::Exp(-tau*x);
}

void model2()
{
  Double_t tau=0.000160;

  TF1 *f1=new TF1("f1","myFunc(0,.00016,x)+myFunc(1,.00016,x)",0,100000);
  TF1 *f2=new TF1("f2","myFunc(0,.00016,x)+myFunc(1,.00016,x)+myFunc(2,.00016,x)",0,100000);
  TF1 *f3=new TF1("f3","myFunc(0,.00016,x)+myFunc(1,.00016,x)+myFunc(2,.00016,x)+myFunc(3,.00016,x)",0,100000);
  TF1 *f5=new TF1("f5","myFunc(0,.00016,x)+myFunc(1,.00016,x)+myFunc(2,.00016,x)+myFunc(3,.00016,x)+myFunc(4,.00016,x)+myFunc(5,.00016,x)",0,100000);
  TF1 *f9=new TF1("f9","myFunc(0,.00016,x)+myFunc(1,.00016,x)+myFunc(2,.00016,x)+myFunc(3,.00016,x)+myFunc(4,.00016,x)+myFunc(5,.00016,x)+myFunc(6,.00016,x)+myFunc(7,.00016,x)+myFunc(8,.00016,x)+myFunc(9,.00016,x)",0,100000);
  TF1 *f17=new TF1("f9","myFunc(0,.00016,x)+myFunc(1,.00016,x)+myFunc(2,.00016,x)+myFunc(3,.00016,x)+myFunc(4,.00016,x)+myFunc(5,.00016,x)+myFunc(6,.00016,x)+myFunc(7,.00016,x)+myFunc(8,.00016,x)+myFunc(9,.00016,x)+myFunc(10,.00016,x)+myFunc(11,.00016,x)+myFunc(12,.00016,x)+myFunc(13,.00016,x)+myFunc(14,.00016,x)+myFunc(15,.00016,x)+myFunc(16,.00016,x)+myFunc(17,.00016,x)",0,100000);      



  f1->Draw();
  f2->Draw("same");
  f3->Draw("same");
  f5->Draw("same");
  f9->Draw("same");
  f17->Draw("same");      

  return;
}
