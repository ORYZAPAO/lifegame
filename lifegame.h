#ifndef __LIFEGAME_H__
#define __LIFEGAME_H__

#include <ctime>
#include <string>
#include <boost/random.hpp>
#include <boost/multi_array.hpp>

namespace lifegame{

template<int XX=50, int YY=50>
class Cell{
private:
  //const int SizeX=50+2;
  //const int SizeY=50+2;
  const int SizeX=XX+2;
  const int SizeY=YY+2;

  typedef boost::multi_array<int, 2> CellMatrix;
  CellMatrix::index  CellIndex;
  CellMatrix  _cell;
  CellMatrix  _cell_next;
public:

  //------------------------------------
  Cell(): _cell(boost::extents[SizeX][SizeY]), 
          _cell_next(boost::extents[SizeX][SizeY]){
    Initialize();
  }
  
  //------------------------------------
  void Initialize(){
    for(CellMatrix::index y=0; y<SizeY; y++){
      for(CellMatrix::index x=0; x<SizeY; x++)  _cell[x][y]=0;
    }
  }
  
  //------------------------------------
  void Preset(){
    boost::mt19937              gen( static_cast<unsigned long>(time(0)) );
    boost::uniform_smallint<>   dst( 0,9 );
    boost::variate_generator< 
      boost::mt19937&, boost::uniform_smallint<>
      > rand( gen, dst );
    
    for(CellMatrix::index y=1; y<(SizeY-1); y++){      
      for(CellMatrix::index x=1; x<(SizeX-1); x++){
        if( rand() == 5 ) _cell[x][y]=1;
        else              _cell[x][y]=0;
      }
    }
  }

  //------------------------------------
  bool isLive(CellMatrix::index x, CellMatrix::index y){
    int  ct; // Cell Counter
    bool result = (_cell[x][y] == 1 ) ? true : false;
    
    ct = _cell[x-1][y-1] + _cell[x][y-1] + _cell[x+1][y-1] +
         _cell[x-1][y]                   + _cell[x+1][y  ] +
         _cell[x-1][y+1] + _cell[x][y+1] + _cell[x+1][y+1];
    
    if( _cell[x][y] == 1 ){ 
      /// Live Cell 
      if( (ct <= 1) || (ct >= 4) ) result = false; /// Death ///
    }else{
      /// Death Cell
      if( ct == 3 ) result = true; /// Birth ///
    } 

    return result ;
  }

  //------------------------------------
  void NextStep(){
    CellMatrix::index x, y;
    
    for(y=1; y<(SizeY-1); y++){
      for(x=1; x<(SizeX-1); x++) _cell_next[x][y] = isLive(x,y);
    }
    
    for(y=1; y<(SizeY-1); y++){
      for(x=1; x<(SizeX-1); x++) _cell[x][y] = _cell_next[x][y];
    }
  }
  
  //------------------------------------
  void Print(){
    CellMatrix::index x, y;
    std::string line;

    for(y=1; y<(SizeY-1); y++){
      line="";
      for(x=1; x<(SizeX-1); x++){
        if( _cell[x][y]==1 ) line += "*";
        else                 line += " ";      
      }
      std::cout << line << std::endl;
    }
    
    std::cout << std::endl;
  }

};/// class Cell{

};/// namespace lifegame{

#endif ///__LIFEGAME_H__
