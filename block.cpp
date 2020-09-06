#include "block.h"
#include <vector>

using namespace std;
// set values in data attribute, based on a dimension x dimension square region
//   with upper-left corner at (left, upper) in the input PNG image
// The orientation of the pixels in the data vector must match the orientation
//   of the pixels in the PNG.
// PRE: upper and left (and upper + dimension, left + dimension) are valid
//        vector indices
void Block::Build(PNG& im, int upper, int left, int dimension){
  // vector<vector<HSLAPixel>> data;
   // = new std::vector<vector<HSLAPixel>> v
   // data.resize(dimension);
  for(int i = 0;i < dimension;i++){
    vector<HSLAPixel> temp;
    // data[i].resize(dimension);
    for(int j = 0; j < dimension; j++){

      // HSLAPixel* p = im.getPixel(i,j);
      temp.push_back(*(im.getPixel(i + left,j + upper)));
      // data.push_back(*p);
      // data[i-upper-1][j-left-1] = *p;
    }
    data.push_back(temp);
  }
}




// write the pixel colour data fom data attribute into im,
//   with upper-left corner at (left, upper)
// PRE: upper and left (and upper + dimension, left + dimension) are valid
//        vector indices
void Block::Render(PNG& im, int upper, int left) const{
  for(int i = 0;i < Dimension();i++){
    for(int j = 0; j < Dimension(); j++){
      HSLAPixel* temp = im.getPixel(i + left,j + upper);
      *temp = data[i][j];
    }
  }

}

// "Reverse" the Hue and Luminance channels for each pixel in the data attribute
//   to simulate a photo-negative effect.
// Refer to the HSLAPixel documentation to determine an appropriate transformation
//   for "reversing" hue and luminance.
void Block::Negative(){
  for (int i = 0; i < Dimension(); i++){
    for (int j = 0; j < Dimension(); j++){
      // HSLAPixel* p = new HSLAPixel();
      // *p = data[i][j];
      // p->l = 1 - p->l;
      // if(p->h < 180){
      //   p->h = p->h + 180;
      // } else {
      //   p->h = p->h - 180;
      // }
      data[i][j].l = 1 - data[i][j].l;
      if(data[i][j].h < 180){
        data[i][j].h += 180;
      } else {
        data[i][j].h -= 180;
      }
    }
  }
}

// Return the horizontal (or vertical) size of the data block's image region
int Block::Dimension() const{
   // for(int i = 0; i < static_cast<int>(data.size());i ++){
   //   if(data[i].size() != 0){
   //     return data[i].size();
   //   }
   // }
   return data.size();
}
