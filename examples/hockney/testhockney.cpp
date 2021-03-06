

#include "hockney.fftx.codegen.hpp"

using namespace fftx;

int main(int argc, char* argv[])
{
  printf("%s: Entered test program\n call hockney::init()\n", argv[0]);
	
  hockney::init();
 
  const int n  =130;
  const int ns =33;
  const int nd =96;

  box_t<3> sbox({{0,0,0}}, {{ns-1, ns-1, ns-1}});
  box_t<3> dbox({{n-nd,n-nd,n-nd}}, {{n-1,n-1,n-1}});
  box_t<3> freq({{0,0,0}}, {{(n-1)/2+1, n-1, n-1}});
  
  array_t<3,double> input(sbox);
  array_t<3,double> output(dbox);
  array_t<3,double> symbol(freq);

  forall([](double(&v), const fftx::point_t<3>& p)
         {
           if(p==point_t<3>({{2,2,2}}))  v=1.0;
           else  v=0.0;
         },input);

  forall([](double(&v), const fftx::point_t<3>& p)
           {
           if(p==point_t<3>::Zero())
             v=0;
           else
             v=-1.0/(p[0]*p[0]+p[1]*p[1]+p[2]*p[2]);         
           },symbol);

  
  printf("call hockney::transform()\n");
  hockney::transform(input, output, symbol);
  printf("hockney for size n=%d ns=%d nd=%d took  %.7e milliseconds\n", n, ns, nd, hockney::CPU_milliseconds);
  hockney::destroy();


  
  printf("%s: All done, exiting\n", argv[0]);
  return 0;
}
