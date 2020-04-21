#include "inc.h"
#include "Simorg.h"
#define DIM 20 
#define MAXGEN 100
using std::cout; 
using std::endl; 

/* Prototypes */
void buildEnv( const int dim, const double yield, Simorg& env ); 
void buildEnv( std::string filename, Simorg& env ); 

int main( int argc, char* argv[] ){ 

  Simorg env( DIM ); 
  double YIELD; 
  bool random; 


  /* Generate Board  */
  if( argc < 2 ){ 
    /* Generate random board */
    random = true; 
    cout << "Random environment will be generated. What initial population percentage would you like? " << endl; 
    std::cin >> YIELD; 
    if( YIELD < 0 || YIELD > 1 ){ 
      cout << "Invalid percentage entered (must be 0 < YIELD < 1). Using default value of 0.80\n" << endl; 
      YIELD = 0.80; 
    }
    buildEnv( DIM, YIELD, env ); 
  } else if( argc < 4 ){ 
    /* Build board from file */
    std::string flag(argv[1]); 
    if( flag.compare("-f") != 0 ){
      cout << "Error: Command line argument error" << endl; 
    }
    std::string file(argv[2]); 
    buildEnv( file, env ); 
  } else { 
    /* Error */
    cout << "Error: Command line argument error" << endl; 
  }
  
  for( int i = 0; i < MAXGEN; i++ ){ 
    system("clear"); 
    cout << "E N V I R O N M E N T   A T   G E N   " << i+1 << endl; 
    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl; 
    if( random ) 
      cout << "Started with " << YIELD * DIM * DIM << " active Simorgs\n" << endl; 
    else 
      cout << "Started with file " << argv[2] << endl; 
    env.printEnv(); 
    env.nextEvo(); 
    std::this_thread::sleep_for(std::chrono::milliseconds(2000)); 
  }

  return 0; 
}

/* Build random environment */
void buildEnv( const int dim, const double yield, Simorg& env ){ 
  srand(time(NULL)); 
  int activecount = yield * dim * dim; 
  int rrow, rcol;  
  printf("Generating a random board | %d / %d Simorgs will start active\n", activecount, dim); 
  for( int i = 0; i < activecount; i++ ){ 
    rrow = (rand() % dim);
    rcol = (rand() % dim);
    env.setState(true, 1, rrow, rcol); 
  }
}

/* Build environment from file */
void buildEnv( const std::string filename, Simorg& env ){ 
  std::ifstream file( filename.c_str(), std::ios::in ); 
  if( !file.good() ) { 
    printf("Error: Issue with opening file \"%s\"\n", filename.c_str()); 
    exit(1); 
  }
  char cellStateBuffer; 
  bool cellState; 
  for( int r = 0; r < DIM; r++ ){
    for( int c = 0; c < DIM; c++ ){ 
      if( file >> cellStateBuffer ){ 
       if( cellStateBuffer == 'X' ) cellState = true; 
       else cellState = false; 
        env.setState(cellState, 1, r, c); 
      } else { 
        printf("Error: I/O issue reading the file \"%s\"\n",filename.c_str()); 
        exit(1); 
      }
    }
  }
}