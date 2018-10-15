// image_stacker.cpp
// CS 223, Winter 2018, Lab 3
//Name: Od Ganzorig

/*
  Specifications for the image stacker program:
     - Ask the user for the directory containing the images to stack
     - Ask the user for what to call the final good image file
     - Average all all noisy images in the given directory to create
       a final good image
     - write the final good image in PPM format to the filename given
       by the user
*/

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <dirent.h>
#include "Pixel.h"
#include "Image.h"

using namespace std;
using namespace imagelab;

static const int NOISY_IMAGES = 10;

// getAverage, takes an array parameter(the noisy picture)
// Postcondition: accumulates values of red, green, blue 
//      AT THE SAME LOCATION in the noisy images, and calculates 
//      the average red, average green, and averag blue color 
//      values over all the pixels.


Image getAverage(Image image_array[])
{
  Image final_image(image_array[0]);
  for ( int row = 0; row < image_array -> getHeight(); row++)
  {
    for ( int col = 0; col < image_array -> getWidth(); col++)
    {
      int acc_R = 0, acc_G = 0, acc_B = 0;
      for ( int i = 0; i < NOISY_IMAGES; i++)

      {
        acc_R = acc_R + image_array[i].getPixel(row, col).getRed();
        acc_G = acc_G + image_array[i].getPixel(row, col).getGreen();
        acc_B = acc_B + image_array[i].getPixel(row, col).getBlue();

      }
      int avg_R, avg_G, avg_B;
        avg_R = acc_R/NOISY_IMAGES;
        avg_G = acc_G/NOISY_IMAGES;
        avg_B = acc_B/NOISY_IMAGES;
      final_image.setPixel(row, col, avg_R, avg_G, avg_B);


    }
  }
  return final_image;

  
}
// readDir -- PROVIDED CODE
// puts filenames from a directory into an output stream
// Explanation of the parameters:
//   out - output stream (may be a stringstream)
//   dir - string containing the path to the directory to read
//   n - number of filenames to return
// Preconditions:
//   dir is a valid directory
//   0 <= n <= the number of files in dir
// Postcondition:
//   returns output stream `out` with the filenames inserted
//     (space-separated)
ostream& readDir(ostream& out, string dir, int n)
{
    string fname, filepath;
    DIR *dp;
    struct dirent *dirp;

    cout << "dir to get files of: " << dir << endl;
    dp = opendir( dir.c_str() );
    if (dp == NULL)
    {
    cout << "ERROR_OPENING:" << dir << endl;
    return out;
    }

    int i = 0;
    while ((dirp = readdir( dp )) && i < n)
    {
       fname = dirp->d_name;

       if ((fname.length() >= 3) &&
          (fname.substr(fname.length()-3, 3) == "ppm"))
       {
           filepath = dir + "/" + fname;
           out << filepath << " ";
           i++;
       }
    }
    closedir( dp );
    return out;
}


int main()
{
  //Prompt the user to enter the name of the directory that contains the images to be stacked
  string image_directory;
  cout << "Please enter the name of the directory: ";
  cin >> image_directory; 

  //Prompt the user to enter the name of the file that will hold the good final image
  string file_name;
  cout << "Please enter the name of the output file (this should not be an existing file): ";
  cin >> file_name;
  ofstream output_file(file_name.c_str());
   
  // initialize a stringstream containing a space-separated string
  // of the first n PPM image filenames in the given directory
  stringstream files;
  files << readDir(files, image_directory, NOISY_IMAGES);

  // extract the filenames as strings from the stringstream variable 
  string s = files.str();

  //initializing file and image arrays to 
  string file_array[NOISY_IMAGES];
  Image image_array[NOISY_IMAGES];

  // open the file and create a new image using the Image 
  // constructor that takes stream input as an argument
  for (int i = 0; i < NOISY_IMAGES; i++)
  {
    files >> file_array[i];
  }
  for ( int j = 0; j < NOISY_IMAGES; j++)
  {
    ifstream input_file(file_array[j].c_str()); 
    Image im1(input_file);
    image_array[j] = im1;
  }

  //Write the final good image in PPM format to the output filename provided by the user
  output_file << getAverage(image_array)<< endl;

}
