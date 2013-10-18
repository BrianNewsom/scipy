

extern "C" {
  void qag_(float(*)(float *), float *, float *, float *, float *, int *,
      float *, float *, int *, int *, int *, int *, int *, int(*)[50], float(*)[200]);
}

class function {
  private:
    //void func(float*);
    float (*func)(float *); //How do I make this have an optional number of inputs? :/

    float a, b, epsabs, epsrel, result, abserr;
    int key, neval, ier, last;
    int limit;
    int lenw;
    int iwork[50];
    float work[200];
  public:
    void integrate();
    function(float(*)(float *));
    void eval();
};

void function::integrate(){
    qag_(this->func,&this->a,&this->b,&this->epsabs,&this->epsrel,&this->key,
    &this->result,&this->abserr,&this->neval,&this->ier,&this->limit,&this->lenw,&this->last,&this->iwork,&this->work);
    printf("%f\n",this->result);
}


function::function(float(*integrand)(float *)){
  limit = 50; //These should all be moved into the constructor
  lenw = 200;
  a = -1.;
  b = 1.;
  epsabs = 1e-3;
  epsrel = 1e-3;
  key = 1;
  this->func = integrand;

}
//}


void function::eval(){
  float q = 12.0;
  float* x = &q;
  float z = this->func(x);
  printf("F evaluated at 12: ");
  printf("%f\n", z);
}



