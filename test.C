{
  FitManager RF;

  RF.SetUp().LoadFormula("r=sqrt(@a1Re[0.0,-1.0,1.0]*@a1Re[]+@a1Im[0.0,-1.0,1.0]*@a1Im[]+@a2Re[0.0,-1.0,1.0]*@a2Re[]+@a2Im[0.0,-1.0,1.0]*@a2Im[]+@a3Re[0.0,-1.0,1.0]*@a3Re[]+@a3Im[0.0,-1.0,1.0]*@a3Im[]+@a4Re[0.0,-1.0,1.0]*@a4Re[]+@a4Im[0.0,-1.0,1.0]*@a4Im[])");
  RF.SetUp().LoadFormula("B=((@a1Re[]*@a1Re[]+@a1Im[]*@a1Im[])+(@a2Re[]*@a2Re[]+@a2Im[]*@a2Im[])-(@a3Re[]*@a3Re[]+@a3Im[]*@a3Im[])-(@a4Re[]*@a4Re[]+@a4Im[]*@a4Im[]))/@r[]");
}
