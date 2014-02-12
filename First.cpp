#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <bitset>

using namespace std;

int main(int argc, char *argv[])
{
  int x0=4;
  int a=21;
  int c=6;
  int m=143;
  int x=x0;
  int period=0;
  int count_for_ones = 0;
  int count_for_zeros = 0;
  int even_figures_count = 0;

  do{
    x=(a*x+c)%m;
    period++;
    bitset<8>Bits(x);

    if (Bits[0]==0) even_figures_count++;

    for (int i = 0; i<8; i++)
    {
      if (Bits[i]==1) count_for_ones++;
        else count_for_zeros++;
    }

    cout << x <<" ";
  }while(x!=x0);

  cout << "\nPeriod: " << period << "\n";;
  cout << "Ones: " << count_for_ones << "\n";
  cout << "Zeros: " << count_for_zeros << "\n";
  cout << "Amount even figures: " << even_figures_count << "\n";
  return 0;
}