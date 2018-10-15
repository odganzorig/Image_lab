// Image.cpp
// Implementation file for Lab 3: Image Class

// Name: Od Ganzorig
// Date: 02/13/2018

// INVARIANT for the Image class:
//   Images store a 2-D array of pixels indexed by their (row,col)-coordinates
//   such that row is the ROW index and col is the COLUMN index.  Specifically,
//   pixels are indexed FIRST by their row-coordinate and THEN by their
//   column-coordinate.
//   For example,
//      - the upper-right corner is row = 0, col = width-1:  arr[0][width-1]
//      - the lower-left corner is row = height-1, col = 0:  arr[height-1][0]

// MEMBER CONSTANTS
//    static const int MAX_COLOR = 255;

// INSTANCE VARIABLES
//    string format;       // image format specifier
//    int width;           // width of the image, in pixels
//    int height;          // height of the image, in pixels
//    int maxcolor;        // maximum int value for red, blue, or green color
//    Pixel ** arr;        // pointer to a 2-dimensional dynamic array of Pixel
                           // objects
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>
#include "Pixel.h"
#include "Image.h"

using namespace std;

namespace imagelab
{
   // Basic constructor
   // Preconditions: w > 0; h > 0; 0 <= r <= 255; 0 <= g <= 255; 0 <= b <= 255
   // Postconditions:
   //   - format is set to "P3"
   //   - width is set to the value of w
   //   - height is set to the value of h
   //   - maxcolor is set to MAX_COLOR
   //   - arr is a 2-D array of pixels with width w and height h
   //   - each pixel in `arr` is set to the same RGB color, (r, g, b)
   // NOTE: Remember to pay attention to the class invariant!
   Image::Image(int w, int h, int r, int g, int b)
   {
      format = "P3";
      width = w;
      height = h;
      maxcolor = MAX_COLOR;
      arr = new Pixel* [height];
      for (int row = 0; row < height; row++)
      {
         arr[row] = new Pixel[width];
      }
      for (int row = 0; row < height; row++)
      {
         for (int col = 0; col < width; col++)
         {
            arr[row][col].set(r,g,b);
         }
         
      }
   }

   

   // Copy constructor
   // Initializes a new Image object to be a clone of the `other` image.
   // NOTE: Remember to pay attention to the class invariant!
   Image::Image(const Image &other)
   {
      format = other.format;
      width = other.width;
      height = other.height;
      maxcolor = other.maxcolor;
      arr = new Pixel* [height];
      for (int row = 0; row < height; row++)
      {
         arr[row] = new Pixel[width];
      }
      for (int row = 0; row < height; row++)
      {
         for (int col = 0; col < width; col++)
         {
            arr[row][col] = other.getPixel(row, col);
         }
         
      }

      
   }

   // Stream input constructor
   // Initializes a new Image object by reading a PPM image from the input
   // stream, `in`.
   // Postconditions:
   //   - format, width, height, and maxcolor for the new Image object
   //     are set based on the input stream
   //   - `arr` points to a 2-D array of pixels which is populated
   //      by the pixel values read from the input stream
   // NOTE: Remember to pay attention to the class invariant!
   Image::Image(std::istream &in)
   {
      in >> format >> width >> height >> maxcolor;
      arr = new Pixel* [height];
      for (int row = 0; row < height; row++)
      {
         arr[row] = new Pixel[width];
      }
      for (int row = 0; row < height; row++)
      {
         for (int col = 0; col < width; col++)
         {
            in >> arr[row][col];
            
         }
         
      }
      
   }

   // MODIFIERS

   // setPixel, 3 argument version; takes row, col, pix
   // Preconditions: 0 <= row <= height; 0 <= col <= width
   // Postconditions: pixel at arr[row][col] is set to pix
   void Image::setPixel(int row, int col, Pixel pix)
   {
      assert(0 <= row <= height && 0 <= col <= width);
      arr[row][col] = pix;

   }

   // setPixel, 5 argument version; takes row, col, r, g, b
   // Preconditions: 0 <= row <= height; 0 <= col <= width;
   //                0 <= r, b, b <= 255
   // Postconditions: pixel at arr[row][col] has RGB values (r, g, b)
   void Image::setPixel(int row, int col, int r, int g, int b)
   {
      if(0 <= row <= height && 0 <= col <= width && (0 <= r, b, b <= 255))
      {
        arr[row][col].set(r,g,b); 
      }
      
   }

   // DESTRUCTOR, ~Image
   // Deallocates memory used by an Image object, to prevent memory leaks.
   // Postcondition: all dynamic memory allocated to the object is deleted
   // Postcondition: `arr` is set to NULL
   // DESTRUCTOR
   Image::~Image()
   {
      for (int row = 0; row < height; row++)
      {
         delete [] arr[row];
      }
      delete [] arr;
      arr = NULL;
   }

   // Assignment operator overload (member function)
   // Postcondition: this image has the same format, width, height,
   //    and maxcolor as `source`
   // Postcondition: this image has a pixel array `arr` which is a *deep copy*
   //    of the pixel array for `source`.
   // Postcondition: the two pixel arrays are independent (unless `source` and
   //    `this` are literally the same object), but they store the exact same
   //    pattern of pixels
   Image& Image::operator= (const Image& source)
   {
      if (this == &source)
      {
         return *this;
      }
      for (int row = 0; row < height; row++)
      {
         delete [] arr[row];
      }
      delete [] arr;
      arr = NULL;
      this -> format = source.format;
      this -> width = source.width;
      this -> height = source.height;
      this -> maxcolor = source.maxcolor;
      arr = new Pixel* [height];
      for (int row = 0; row < height; row++)
      {
         arr[row] = new Pixel[width];
      }
      for (int row = 0; row < height; row++)
      {
         for (int col = 0; col < width; col++)
         {
            arr[row][col] = source.getPixel(row, col);
         }
         
      }
      

      // return the "this" object reference so we can chain the operator
      return *this;
   }

   // OUTPUT STREAM OPERATOR -- FRIEND -- PROVIDED CODE
   // Puts the image into an output stream, in PPM format.
   //   1st item: 2-character format string
   //   2nd item: image width in pixels
   //   3rd item: image height in pixels
   //   4th item: maximum pixel color
   //   Subsequent items:  the RGB values for each pixel, row-by-row
   //
   // For example, a very small image with 16 pixels and max color
   // value of 15 might look like the following:
   //   P3
   //   4 4
   //   15
   //   0  0  0
   //   0  0  0
   //   0  0  0
   //   15  0 15
   //   0  0  0
   //   0 15  7
   //   0  0  0
   //   0  0  0
   //   0  0  0
   //   0  0  0
   //   0 15  7
   //   0  0  0
   //   15  0 15
   //   0  0  0
   //   0  0  0
   //   0  0  0
   //
   std::ostream& operator<< (std::ostream &out, const Image &image)
   {
      int h = image.getHeight();
      int w = image.getWidth();
      int maxColor = image.getMaxColor();

      out << image.getFormat() << '\n' << w << " " << h
          << '\n' << maxColor << '\n';
      for (int row = 0; row < h; row++)
      {
         for (int col = 0; col < w; col++)
         {
            out << image.getPixel(row, col) << '\n';
         }
      }
      return out;    // return out for chaining
   }
}  // namespace imagelab
