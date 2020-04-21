#ifndef SIMORG_CPP
#define SIMORG_CPP
#include "Simorg.h"

/* Constructor */
Simorg::Simorg( const int _dim ){
  env = (bool*)malloc(_dim*_dim*sizeof(bool));
  envStack = (bool*)malloc(_dim*_dim*sizeof(bool));
  gen = (int*)calloc(_dim*_dim, sizeof(int)); 
  dim = _dim;
}

/* Destructor */
Simorg::~Simorg(){
  free(env);
  free(envStack);
  free(gen);
}

/* Update the whole board */
void Simorg::nextEvo( ){ 
  for( int r = 0; r < dim; r++ ){ 
    for( int c = 0; c < dim; c++ ){ 
      if( this -> willDie(r,c) ) setState(false, 2, r, c); 
      else setState(true, 2, r, c); 
    }
  }
  for( int r = 0; r < dim; r++ ){ 
    // printf("\n GEN COUNT BOARD "); 
    for( int c = 0; c < dim; c++ ){ 
      if( this -> getState(1,r,c) && this -> getState(2,r,c) ) this -> nextGen(r,c); 
      this -> setState(this->getState(2,r,c),1,r,c); 
      if( !this -> getState(2,r,c) ) resetGen(r,c); 
      // printf("  %d  ", getGen(r,c)); 
    }
  }
  // printf("\n"); 
}

/* Set as inactve for next generation if rules determine fit */
bool Simorg::willDie( const int r, const int c ){ 
  int neighbors =  this -> neighbors(r,c); 

  /* Rule 5 */
  if( getGen( r, c ) >= 9 ) return true; 

  /* Rule 1 */
  if( neighbors < 2 ) return true; 

  /* Rule 2 */
  if( neighbors == 2 ) return !( getState(1, r,c)); 

  /* Rule 3 */
  if( neighbors == 3) return false; 

  /* Rule 4 */
  if( neighbors >= 4 ) return true; 

  return false; 
}

/* Set the state of the location r, c */
void Simorg::setState( bool newState, const int board,const int r, const int c ){ 
  if( board == 1 )
    *(env + r*dim+c) = newState; 
  else 
    *(envStack + r*dim+c) = newState; 
}

bool Simorg::getState( const int board, const int r, const int c ){ 
  if( board == 1 )
    return *(env + (r*dim+c)); 
  else 
    return *(envStack + (r*dim+c)); 
}

/* Get generation count */
int Simorg::getGen( const int r, const int c ){ 
  return *(gen+(r*dim+c)); 
}

/* Get T/F on whether or not the Simorg is active */
bool Simorg::isActive( const int r, const int c ){ 
  if( r < 0 || c < 0 ) return false; 
  if( r >= dim || c >= dim ) return false; 
  return *(env + (r*dim+c)); 
}

/* Print the environment state */
void Simorg::printEnv( ){ 
  bool cell; 
  for( int r = 0; r < dim; r++ ){
    printf("\n"); 
    for( int c = 0; c < dim; c++ ){ 
      cell = *(env + (r*dim+c)); 
      if( cell ) printf(" X ");
      else printf(" 0 "); 
    }
  }
  printf("\n\n"); 
}

/* Increase the generation of a cell */
void Simorg::nextGen( const int r, const int c ){ 
  *(gen + (r*dim+c)) += 1; 
}

/* Reset the generation of a cell */
void Simorg::resetGen( const int r, const int c ){ 
  *(gen + (r*dim+c)) = 0; 
}

/* Return the count of the neighboring cells */
int Simorg::neighbors( const int r, const int c ){ 
  int neighbors = 0; 
  if( this -> isActive( r-1, c-1 )) neighbors++; 
  if( this -> isActive( r-1, c+0 )) neighbors++; 
  if( this -> isActive( r-1, c+1 )) neighbors++; 
  if( this -> isActive( r+0, c-1 )) neighbors++; 
  if( this -> isActive( r+0, c+1 )) neighbors++; 
  if( this -> isActive( r+1, c-1 )) neighbors++; 
  if( this -> isActive( r+1, c+0 )) neighbors++; 
  if( this -> isActive( r+1, c+1 )) neighbors++; 
  return neighbors; 
} 

void Simorg::printNeighbors( ){ 
  for( int r = 0; r < dim; r++ ){ 
    printf("\n"); 
    for( int c = 0; c < dim; c++ ){ 
      printf(" %d ", this -> neighbors(r,c) ); 
    }
  }
}
  
void Simorg::printNextMove( ){ 
  for( int r = 0; r < dim; r++ ){ 
    printf("\n"); 
    for( int c = 0; c < dim; c++ ){ 
      printf(" %d ", !this -> willDie(r,c) ); 
    }
  }
}

#endif 