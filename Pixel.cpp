// Pixel.cpp
// Last modified 2-7-2018
//
// Implementation file for CS 223 Lab 3: Pixel Class
//   - operator overloads are defined in this file
//   - all other function definitions are "inlined" in the .h file

// Class Invariant:  the rval, gval, and bval values are always
// in the range 0 to 255.

#include <iostream>
#include <sstream>
#include "Pixel.h"

using namespace std;

namespace imagelab
{
/* operator==
 * Equivalence operator for pixels.
 */
bool operator== (const Pixel& pix1, const Pixel& pix2)
{
   return (pix1.getRed() == pix2.getRed()) &&
          (pix1.getGreen() == pix2.getGreen()) &&
          (pix1.getBlue() == pix2.getBlue());
}

/* operator!=
 * Inequivalence operator for pixels.
 */
bool operator!= (const Pixel& pix1, const Pixel& pix2)
{
   return !(pix1 == pix2);
}

/* operator<<
 * Stream output operator (<<) for outputting the contents of a pixel.
 * Example: A pixel with red value 100, green value 150, and blue value 200
 *    will produce the following output:100 150 200
 * Note: Returns the `out` parameter to allow chaining of stream output.
 */
std::ostream& operator<< (std::ostream& out, const Pixel& pix)
{
   out << pix.getRed() << " " << pix.getGreen() << " " << pix.getBlue();

   return out;
}

/* operator>>
 * Stream input operator (>> for reading a pixel from an input stream.
 * Precondition: `in` holds a string of three integers separated by spaces;
 *    each integer must be in the range 0 to 255, inclusive.
 * Postconditions:
 *    -The red value of pix is set to the first integer.
 *    -The blue value of pix is set to the third integer.
 * Note: Returns the `in` parameter to allow chaining of stream input.
 */
std::istream& operator>> (std::istream& in, Pixel& pix)
{
   int r, g, b;
   in >> r >> g >> b;
   pix.setRed(r);
   pix.setGreen(g);
   pix.setBlue(b);

   return in;
}

} // end namespace
