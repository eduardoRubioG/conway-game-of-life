#ifndef SIMORG_H
#define SIMORG_H
#include "inc.h"
class Simorg {
private:
  /* data */
  int dim;
  bool* env; 
  bool* envStack; 
  int* gen; 

  bool getState( const int, const int, const int ); 
  int getGen( const int, const int ); 
  int neighbors( const int, const int ); 
  void nextGen( const int, const int ); 
  void resetGen( const int, const int ); 

public:
  Simorg( const int );
  bool isActive( const int, const int ); 
  bool willDie( const int, const int ); 
  void setState( bool, const int, const int, const int ); 
  void printEnv(); 
  void nextEvo( ); 
  void printNeighbors( ); 
  void printNextMove( ); 

  ~Simorg();
};

#include "Simorg.cpp"
#endif 