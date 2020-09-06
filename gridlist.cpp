// File:        gridlist.cpp
// Date:        2020-01-18 00:11
// Description: Contains partial implementation of GridList class
//              CPSC 221 2019W2 PA1
//              Function bodies to be completed by yourselves
//
// ADD YOUR FUNCTION IMPLEMENTATIONS IN THIS FILE
//

#include "gridlist.h"
#include "gridlist_given.cpp"

// Creates a PNG of appropriate pixel dimensions according to the GridList's structure
//   and colours each pixel according the each GridNode's Block data.
// The fully coloured PNG is returned.
PNG GridList::Render() const
{
  PNG image;
  if (northwest != NULL){
    int dim = (northwest->data).Dimension();
    image.resize(dimx*dim,dimy*dim);
    int i = 0;
    GridNode* temp = northwest;
    (temp->data).Render(image,0,0);
    while(temp->next != NULL){               //has next
      temp = temp->next;
      i++;
      int y = (i / dimx) * dim;
      int x = (i % dimx) * dim;
      (temp->data).Render(image,y,x);
    }
  }
  return image;

  // PNG image;
  // if(northwest == NULL){
  //   return image;
  //
  // } else{
  //   int size = Length();
  //   Block b;
  //   GridNode* temp = northwest;
  //   int dim = (northwest->data).Dimension();
  //   image.resize(dimx*dim,dimy*dim);
  //   if(dimx * dimy <= size){
  //     for(int y = 0; y < dimy; y++){
  //       for(int x = 0; x < dimx; x++){
  //         b = temp->data;
  //         b.Render(image,y*dim,x*dim);
  //         temp = temp->next;
  //       }
  //     }
  //   } else {
  //     int col = dimx;
  //     int row = (size - size%dimx)/dimx;
  //     // int row = size/(size - size%dimx);
  //     for(int y = 0; y < row; y++){
  //       for(int x = 0; x < dimx; x++){
  //         b = temp->data;
  //         b.Render(image,y*dim,x*dim);
  //         temp = temp->next;
  //       }
  //     }
  //     if(size%dimx != 0){
  //       for(int x = 0; x < size%dimx; x++){
  //         b = temp->data;
  //         b.Render(image,(row+1)*dim,x*dim);
  //         temp = temp->next;
  //       }
  //     }
  //   }
  //   // enter your code here
  //   return image;
  }

// Allocates a new GridNode containing bdata and
//   attaches it to end of this list.
// Be careful of the special case of inserting into an empty list.
void GridList::InsertBack(const Block& bdata)
{
  if (northwest == NULL){             //empty list
    northwest= new GridNode(bdata);
    southeast = northwest;
    // northwest = end;
  } else {
    GridNode* end = new GridNode(bdata);
    end -> prev = southeast;
    southeast -> next = end;
    southeast = end;
  }

  //
  // GridNode* end = new GridNode(bdata);
  // if(Length()!=0){
  //   // end->prev = southeast->prev;
  //   // southeast->prev->next = end;
  //   // southeast->prev = end;
  //   // end->next = southeast;
  //   // southeast = end;
  //   end->next = NULL;
  //   GridNode* temp = southeast;
  //   end->prev = temp;
  //   temp->next = end;
  //   southeast = end;
  //
  //   // end -> prev = southeqast;
  //   // southeast -> next = end;
  //   // southeast = end;
  // } else{
  //   end->next = NULL;
  //   end->prev = NULL;
  //   northwest = end;
  //   southeast = end;
  // }

  // enter your code here
}

// if this list has an odd number of column blocks, then the right side will have more blocks
// PRE:  this list and inner are not the same physical list
//       this list must have at least two column blocks
//       inner list must have at least one column block
//       inner list must have the same vertical resolution, vertical block dimension, and block size
// POST: this list has nodes of the entire inner list in between the left and right halves of this list
//         and inner list becomes empty
//       innerNodewise both lists are not modified
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::Sandwich_H(GridList& inner)
{
  if((dimy != inner.dimy) || (dimx<2) || (inner.dimx<1)){
    return;
  }
  if(northwest == NULL || inner.northwest == NULL || (northwest->data.Dimension()) != (inner.northwest->data.Dimension())){
    return;
  }
  int middle = dimx/2 - 1;              //mid point
  // int innerWidth = inner.dimx;
  int i = 0;
  int num;
  int originalDimx = dimx;
  GridNode* curr = northwest;
  GridNode* innerNode = inner.northwest;
  dimx += inner.dimx;
  while (curr->next != NULL) {           //has next
    if(i % originalDimx == middle){     //at mid point
      num = 0;
      while (num < inner.dimx) {
        GridNode* temp = innerNode;
        innerNode = innerNode->next;
        temp->prev = curr;
        temp->next = curr->next;
        curr->next->prev = temp;
        curr->next = temp;
        curr = curr->next;
        ++ num;
      }
    }
    curr = curr->next;
    i ++;
  }
  inner.dimx = 0;
  inner.dimy = 0;
  inner.southeast = NULL;
  inner.northwest = NULL;
  // enter your code here
}

// inner list must have the same horizontal resolution, horizontal block dimension, and block size
// if this list has an odd number of row blocks, then the bottom side will have more blocks
// PRE:  this list and inner are not the same physical list
//       this list must have at least two row blocks
//       inner list must have at least one row block
//       inner list must have same horizontal resolution, horizontal block dimension, and block size
// POST: this list has nodes of the entire inner list in between the upper and lower halves of this list
//         and inner list becomes empty
//       innerNodewise both lists are not modified
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::Sandwich_V(GridList& inner)
{
  if((dimx != inner.dimx) || (dimy<2) || (inner.dimy<1)){
    return;
  }
  if(northwest == NULL || inner.northwest == NULL || (northwest->data.Dimension()) != (inner.northwest->data.Dimension())){
    return;
  }
  int middle = dimy / 2 * dimx -1;              //mid point
  int i = 0;
  GridNode* curr = northwest;
  dimy += inner.dimy;
  while (curr->next != NULL){
    if(i == middle){
      inner.southeast->next = curr->next;
      inner.northwest ->prev = curr;
      curr->next->prev = inner.southeast;
      curr->next = inner.northwest;
    }
    curr = curr->next;
    i++;
  }
  inner.dimx = 0;
  inner.dimy = 0;
  inner.southeast = NULL;
  inner.northwest = NULL;
}


// PRE:  this list and innerNodelist have the same pixel dimensions, block dimensions, and block size
// POST: this list and innerNodelist are checkered with each innerNode's nodes
//       each list's dimensions remain the same
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::CheckerSwap(GridList& innerNodelist)
{
  //fish
  if((dimy != innerNodelist.dimy) || (dimx != innerNodelist.dimx)){
    return;
  }
  if((northwest == NULL) || innerNodelist.northwest == NULL || (northwest->data).Dimension() != (innerNodelist.northwest->data).Dimension()){
    return;
  }
  int i = 0;
  int dim = (northwest->data).Dimension();
  GridNode* curr = northwest;
  GridNode* innerNode = innerNodelist.northwest;
  while(curr->next != NULL){
    curr = curr->next;
    innerNode = innerNode->next;
    i++;
    int upper = (i / dimx) * dim;
    int left = (i % dimx) * dim;
    if((upper+left)%2 ==1){
      if(curr->next != NULL){
        curr->next->prev = innerNode;
        innerNode->next->prev = curr;
      }
      curr->prev->next = innerNode;
      innerNode->prev->next = curr;
      GridNode* temp = curr->prev;
      curr->prev = innerNode->prev;
      innerNode->prev = temp;
      temp = curr->next;
      curr->next = innerNode->next;
      innerNode->next = temp;
    }
  }


  // enter your code here
  //
  // GridNode* temp1 = northwest;
  // GridNode* temp2 = innerNodelist.northwest;
  // for(int y = 0;y < dimy ;y++){
  //   for(int x = 0;x <dimx; x++){
  //     if((x+y)%2 ==1){
  //       temp1 =temp2;
  //     }
  //     temp1 = temp1->next;
  //     temp2 = temp2->next;
  //   }
  // }
}

// POST: this list has the negative effect applied selectively to GridNodes to form
//         a checkerboard pattern.
//       The northwest block is normal (does not have the negative effect applied).
// Ensure that the checkering looks correct for both odd and even horizontal block dimensions
void GridList::CheckerN()
{
  if(northwest != NULL){
    int i = 0;
    GridNode* temp = northwest;
    while(temp->next != NULL){
      temp = temp->next;
      i++;
      int upper = i / dimx;
      int left = i % dimx;
      if((upper+left)%2 ==1){
        temp->data.Negative();
      }
    }
  }



  // GridNode* temp = northwest;
  // for(int y = 0;y < dimy ;y++){
  //   for(int x = 0;x <dimx; x++){
  //     if((x+y)%2 ==1){
  //       temp->data.Negative();
  //     }
  //     temp = temp->next;
  //   }
  // }


  // enter your code here
}

// Deallocates any dynamic memory associated with this list
//   and re-initializes this list to an empty state
void GridList::Clear()
{
  if (Length() != 0) {
    GridNode* curr = northwest;
      while(curr->next != NULL){
        GridNode* temp = curr;
        curr = curr->next;
        delete temp;
      }
      delete southeast;
      dimx = 0;
      dimy = 0;
      southeast = NULL;
      northwest = NULL;
    }
}

// Allocates new nodes into this list as copies of all nodes from innerNodelist
void GridList::Copy(const GridList& innerNodelist)
{

  dimx = innerNodelist.dimx;
  dimy = innerNodelist.dimy;
  northwest = new GridNode(*(innerNodelist.northwest));
  GridNode* curr = northwest;
  GridNode* innerNode = (innerNodelist.northwest)->next;
  curr->next = new GridNode(*(innerNode));
  GridNode* prev = northwest;
  curr = curr->next;
  innerNode = innerNode->next;

  while (innerNode->next != NULL) {
      curr->next = new GridNode(*(innerNode));
      curr->prev = prev;
      innerNode = innerNode->next;
      prev = curr;
      curr = curr->next;
  }
  southeast = new GridNode(*(innerNodelist.southeast));
  curr->next = southeast;
  curr->prev = prev;
  southeast->prev = curr;
  // enter your code here
}

// IMPLEMENT ANY PRIVATE FUNCTIONS YOU HAVE ADDED BELOW
//
//
