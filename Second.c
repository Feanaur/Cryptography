#include <stdio.h>
#include <ctype.h>
#include <math.h>

int even = 0, odd = 0, zerosCounter = 0, onesCounter = 0,period=0, i = 0;
int previosCondition= 0;
int gammaBitsLength = 0;
int shiftRegister = 0;
//F(x) = 1+x+x^3+x^6+x^8
int coefficientArray[4] = { 1, 2, 5, 7 };
int resultSequenceFigure = 0;

void ZeroOneCounter(int x)
{
  while (x>0)
  {
    if ( x & 1 == 1 )
    {
      onesCounter++;
    }
    else
    {
      zerosCounter++;
    }
    x>>=1;
  }
}

void EvenOrOdd(int x)
{
  if (x % 2 == 0)
  {
    even++;
  }
  else
  {
    odd++;
  }
}

void LFSRstep()
{
  resultSequenceFigure<<=1;
  resultSequenceFigure |= ((shiftRegister & 128)>>7);
  
  previosCondition=shiftRegister;
  shiftRegister<<=1;

  shiftRegister|=((previosCondition & (int) pow(2,coefficientArray[3]))/(int)pow(2,coefficientArray[3]))
                  ^((previosCondition & (int) pow(2,coefficientArray[2]))/(int)pow(2,coefficientArray[2]))
                  ^((previosCondition & (int) pow(2,coefficientArray[1]))/(int)pow(2,coefficientArray[1]))
                  ^((previosCondition & (int) pow(2,coefficientArray[0]))/(int)pow(2,coefficientArray[0]));
  
  gammaBitsLength++;
}

int LFSR(int seed)
{
  shiftRegister = seed;
  
  LFSRstep();

  while((shiftRegister&255)!=seed) //don`t ask, just trust me...
  {
    LFSRstep();
    if(gammaBitsLength==8)
    {
      printf("%i ", resultSequenceFigure);
      ZeroOneCounter(resultSequenceFigure);
      EvenOrOdd(resultSequenceFigure);
      period++;
      resultSequenceFigure = 0;
      gammaBitsLength = 0;
    }

  }

}
int main(int argc,char *argv[])
{
  printf("Sequence: ");
  int seedValue = 243;
  LFSR(seedValue);
  printf("\nAmount of even elements: %i\nAmount of odd elements: %i\n",even,odd);
  printf("Amount of ones in sequence: %i\nAmount of zeros in sequence: %i\n",onesCounter,zerosCounter);
  printf("Period: %i\n", period);
  return 0;
}