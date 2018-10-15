// Image_tests.cpp
// Unit tests for Image class, CS 223 Lab 3
// B. Wahl and T. Wilson
// Updated 2-8-2018
//
// ******************************************************************
// NOTE: Students need to add three test implementations to this file
// (scroll to bottom, just above main, to see the declarations):
//
//   - TEST(TestAssignmentOperator, assignSmallerImageToBiggerImage)
//
//   - TEST(TestAssignmentOperator, assignBiggerImageToSmallerImage)
//
//   - TEST(TestCopyConstructor, basicOperation)
// ******************************************************************

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include "Pixel.h"        // provides the Pixel class
#include "Image.h"        // provides the Image class
#include "gtest/gtest.h"  // declares the testing framework

using namespace std;
using namespace imagelab;

namespace {

static const int MAX_COLOR = imagelab::Image::MAX_COLOR;

// basic constructor, accessors
TEST(TestBasicConstructorAndGetters, DefaultConstructor)
{
    int height = 100;
    int width = 100;
    Image im1;
    Pixel black;
    EXPECT_EQ(im1.getWidth(), width);
    EXPECT_EQ(im1.getHeight(), height);
    EXPECT_EQ(im1.getFormat(), "P3");
    EXPECT_EQ(im1.getMaxColor(), MAX_COLOR);
    EXPECT_EQ(im1.getPixel(0,   0), black);
    EXPECT_EQ(im1.getPixel(height - 1, width - 1), black);
    EXPECT_EQ(im1.getPixel(0,  width - 1), black);
    EXPECT_EQ(im1.getPixel(height - 1,  0), black);
    EXPECT_EQ(im1.getPixel(13, 79), black);
}

TEST(TestBasicConstructorAndGetters, red5_green6_blue7_width8_height9)
{
    int height = 9;
    int width = 8;
    Image im1(width, height, 5, 6, 7);
    Pixel pix(5, 6, 7);
    ASSERT_EQ(im1.getWidth(), width);
    ASSERT_EQ(im1.getHeight(), height);
    EXPECT_EQ(im1.getFormat(), "P3");
    EXPECT_EQ(im1.getMaxColor(), MAX_COLOR);
    EXPECT_EQ(im1.getPixel(0, 0), pix);
    EXPECT_EQ(im1.getPixel(0, width - 1), pix);
    EXPECT_EQ(im1.getPixel(height - 1, 0), pix);
    EXPECT_EQ(im1.getPixel(height - 1, width - 1), pix);
    EXPECT_EQ(im1.getPixel(2, 6), pix);
}

TEST(TestBasicConstructorAndGetters, redMax_greenMax_blueMax_width1_height1)
{
    int height = 1;
    int width = 1;
    Image im1(width, height, 5, 6, 7);
    Pixel pix(5, 6, 7);
    EXPECT_EQ(im1.getWidth(), 1);
    EXPECT_EQ(im1.getHeight(), 1);
    EXPECT_EQ(im1.getFormat(), "P3");
    EXPECT_EQ(im1.getMaxColor(), MAX_COLOR);
    EXPECT_EQ(im1.getPixel(0, 0), pix);  // (0, 0) is the only pixel
}

// ************************************************************
// UNCOMMENT a section of tests below to enable those tests
// as you are developing the corresponding implementation code.

// setPixel, 3 arguments -- setPixel(int x, int y, Pixel pix)
TEST(TestSetPixelThreeArgs, checkForAliasingProblems)
{
    int height = 9;
    int width = 8;
    Image im1(width, height, 5, 6, 7);
    Pixel pix1(0, 20, MAX_COLOR);
    Pixel pix2 = pix1;  // clone of pix1
    im1.setPixel(3, 5, pix1);
    // changing pix1 should NOT change im1
    pix1.set(9, 9, 9);
    EXPECT_EQ(im1.getPixel(3, 5), pix2);
}

TEST(TestSetPixelThreeArgs, checkCornersOfImageAreSet)
{
    int height = 9;
    int width = 8;
    Image im1(width, height, 5, 6, 7);
    Pixel pix(0, 20, MAX_COLOR);
    im1.setPixel(0, 0, pix);
    im1.setPixel(height-1, width-1, pix);
    im1.setPixel(0, width-1, pix);
    im1.setPixel(height-1, 0, pix);
    EXPECT_EQ(im1.getPixel(0, 0), pix);
    EXPECT_EQ(im1.getPixel(height-1, width-1), pix);
    EXPECT_EQ(im1.getPixel(0, width-1), pix);
    EXPECT_EQ(im1.getPixel(height-1, 0), pix);
}

// // // setPixel, 5 arguments
TEST(TestSetPixelFiveArgs, checkMiddleAndCornersOfImageAreSet)
{
    int height = 9;
    int width = 8;
    Image im1(width, height, 5, 6, 7);
    Pixel pix(0, 20, MAX_COLOR);
    // set five pixels to color (0, 20, MAX_COLOR)
    im1.setPixel(0, 0, 0, 20, MAX_COLOR);
    im1.setPixel(height-1, width-1, 0, 20, MAX_COLOR);
    im1.setPixel(0, width-1, 0, 20, MAX_COLOR);
    im1.setPixel(height-1, 0, 0, 20, MAX_COLOR);
    im1.setPixel(3, 2, 0, 20, MAX_COLOR);
    EXPECT_EQ(im1.getPixel(0, 0), pix);
    EXPECT_EQ(im1.getPixel(height-1, width-1), pix);
    EXPECT_EQ(im1.getPixel(0, width-1), pix);
    EXPECT_EQ(im1.getPixel(height-1, 0), pix);
    EXPECT_EQ(im1.getPixel(3, 2), pix);
}

// // stream input constructor
TEST(TestStreamInputConstructor, use_image_n44f_001)
{
//     // Read in an image file to create an Image.
//     // Check that image format, width, height, and maxcolor
//     // are correctly set.  Also check that the first three
//     // and the last three pixels of the the image are correct.

//     // Contents of n44f_001.ppm:
//     // P3
//     // 600 339
//     // 255
//     // 0 0 0
//     // 0 10 16
//     // 86 8 14
//     // etc...

    string imagefilestr =
       "/usr/local/share/images/images_noisy/n44f/n44f_001.ppm";
    cout << "            -reading image " << imagefilestr << endl;
    ifstream imagefile(imagefilestr.c_str());
    Image image(imagefile);
    imagefile.close();

//     // cout << "    -checking image format and dimensions" << endl;
    EXPECT_EQ(image.getFormat(), "P3");
    EXPECT_EQ(image.getWidth(), 600);
    EXPECT_EQ(image.getHeight(), 339);
    EXPECT_EQ(image.getMaxColor(), 255);

//     // cout << "    -checking first three pixels of image" << endl;
    EXPECT_EQ(image.getPixel(0, 0), Pixel(0, 0, 0));
    EXPECT_EQ(image.getPixel(0, 1), Pixel(0, 10, 16));
    EXPECT_EQ(image.getPixel(0, 2), Pixel(86, 8, 14));

//     // cout << "    -checking last three pixels of image" << endl;
    int w = 600;
    int h = 339;
    EXPECT_EQ(image.getPixel(h-1, w-3), Pixel(255, 100, 0));
    EXPECT_EQ(image.getPixel(h-1, w-2), Pixel(17, 118, 0));
    EXPECT_EQ(image.getPixel(h-1, w-1), Pixel(255, 0, 0));
}

TEST(TestStreamInputConstructor, use_image_orion_010)
{
//     // Read in an image file to create an Image.
//     // Check that image format, width, height, and maxcolor
//     // are correctly set.  Also check that the first three
//     // and the last three pixels of the the image are correct.

//     // P3
//     // 600 600
//     // 255
//     // 0 0 16
//     // 0 0 0
//     // 14 0 16
//     // etc...

    string imagefilestr =
       "/usr/local/share/images/images_noisy/orion/orion_010.ppm";
    cout << "            -reading image " << imagefilestr << endl;
    ifstream imagefile(imagefilestr.c_str());
    Image image(imagefile);
    imagefile.close();

//     // cout << "    -checking image format and dimensions" << endl;
    EXPECT_EQ(image.getFormat(), "P3");
    EXPECT_EQ(image.getWidth(), 600);
    EXPECT_EQ(image.getHeight(), 600);
    EXPECT_EQ(image.getMaxColor(), 255);

//     // cout << "    -checking first three pixels of image" << endl;
    EXPECT_EQ(image.getPixel(0, 0), Pixel(0, 0, 16));
    EXPECT_EQ(image.getPixel(0, 1), Pixel(0, 0, 0));
    EXPECT_EQ(image.getPixel(0, 2), Pixel(14, 0, 16));

//     // cout << "    -checking last three pixels of image" << endl;
    int h = 600;
    int w = 600;
    EXPECT_EQ(image.getPixel(h-1, w-3), Pixel(0, 0, 18));
    EXPECT_EQ(image.getPixel(h-1, w-2), Pixel(0, 4, 16));
    EXPECT_EQ(image.getPixel(h-1, w-1), Pixel(0, 4, 0));
}

// // stream output operator<<
TEST(TestStreamOutputOperator, basicOperation)
{
    // Read in an image file to create an Image, then write that
    // image out to a new file. USE THE LINUX COMMAND LINE to check
    // for differences in the two files.

    string imagefilestr =
       "/usr/local/share/images/images_noisy/n44f/n44f_001.ppm";
    cout << "            -reading image " << imagefilestr << endl;
    ifstream imagefile(imagefilestr.c_str());
    Image image(imagefile);
    imagefile.close();

    string outfilestr = "testimage.ppm";
    cout << "            -writing image to " << outfilestr << endl;
    ofstream outfile(outfilestr.c_str());
    outfile << image;
    outfile.close();

    cout << "\nIMPORTANT!"<< endl;
    cout << "\nTo check for differences between the original image file \n";
    cout << "and the newly created image file, please run the following \n";
    cout << "command:\n" << endl;
    cout << "    diff " << imagefilestr << " " << outfilestr << endl << endl;
    cout << "If there are no differences, your stream output operator\n";
    cout << "is correct! If there are differences, there's an error in \n";
    cout << "the implementation of your stream output. Use the 'head'\n";
    cout << "and 'tail' commands to inspect the two files and help you \n";
    cout << "figure out what is wrong.\n";
    cout << "\nAs a final test, you should use an image viewer to try to\n";
    cout << "view " << outfilestr << "." << endl;
    cout << "-----------------------------------------" << endl << endl;
}

TEST(TestStreamOutputOperator, chaining)
{
    stringstream out;   // simulated output stream
    string correct;     // correct output

//     // 1. Set up Image and store correct output
    int height = 2;
    int width = 1;
    Image im1(width, height, 20, 40, 60);
    Pixel pix(20, 40, 60);

//     // store correct result for `outstream << im1 << im1`
//     // print WIDTH before HEIGHT

    correct = "P3\n1 2\n255\n20 40 60\n20 40 60\n";
    correct = correct + correct;

//     // 2. Execute (put sequence into output stream)
    out << im1 << im1;

//     // 3. Assert (check that contents of output stream are correct)
    EXPECT_EQ(out.str(), correct);
}

// // assignment operator=
TEST(TestAssignmentOperator, selfAssignmentIsOK)
{
    int height = 9;
    int width = 8;
    Image im1(width, height, 5, 6, 7);
    Pixel pix(5, 6, 7);
    im1 = im1;  // self assignment
    EXPECT_EQ(im1.getWidth(), width);
    EXPECT_EQ(im1.getHeight(), height);
    EXPECT_EQ(im1.getFormat(), "P3");
    EXPECT_EQ(im1.getMaxColor(), MAX_COLOR);
    EXPECT_EQ(im1.getPixel(0, 0), pix);
    EXPECT_EQ(im1.getPixel(height-1, width-1), pix);
    EXPECT_EQ(im1.getPixel(0, width-1), pix);
    EXPECT_EQ(im1.getPixel(height-1, 0), pix);
    EXPECT_EQ(im1.getPixel(3, 2), pix);
}

TEST(TestAssignmentOperator, chaining)
{
    int height = 9;
    int width = 8;
    // make a 72-pixel image with RGB = (5,6,7)
    Image im1(width, height, 5, 6, 7);
    Pixel pix(5, 6, 7);
    // set a few distinctive pixels
    im1.setPixel(0, 0, 255, 0, 0); // (0,0) is red
    im1.setPixel(4, 6, 0, 255, 0); // (4,6) is green
    im1.setPixel(5, 2, 0, 0, 255); // (5,2) is blue

    // make a 24-pixel all-black image
    Image im2(8, 3);

    // make a 15-pixel all-white image
    Image im3(3, 5, 255, 255, 255);

    // execute the chained assignment
    im3 = im2 = im1;

    // ASSERT correct dimensions before continuing on...
    ASSERT_EQ(im2.getHeight(), height);
    ASSERT_EQ(im3.getHeight(), height);
    ASSERT_EQ(im2.getWidth(), width);
    ASSERT_EQ(im3.getWidth(), width);

    // check some pixels in im2
    EXPECT_EQ(im2.getPixel(0, 0), Pixel(255, 0, 0));
    EXPECT_EQ(im2.getPixel(height-1, width-1), pix);
    EXPECT_EQ(im2.getPixel(0, width-1), pix);
    EXPECT_EQ(im2.getPixel(height-1, 0), pix);
    EXPECT_EQ(im2.getPixel(3, 2), pix);
    EXPECT_EQ(im2.getPixel(4, 6), Pixel(0, 255, 0));
    EXPECT_EQ(im2.getPixel(5, 2), Pixel(0, 0, 255));
    // check some pixels in im3
    EXPECT_EQ(im3.getPixel(0, 0), Pixel(255, 0, 0));
    EXPECT_EQ(im3.getPixel(height-1, width-1), pix);
    EXPECT_EQ(im3.getPixel(0, width-1), pix);
    EXPECT_EQ(im3.getPixel(height-1, 0), pix);
    EXPECT_EQ(im3.getPixel(3, 2), pix);
    EXPECT_EQ(im3.getPixel(4, 6), Pixel(0, 255, 0));
    EXPECT_EQ(im3.getPixel(5, 2), Pixel(0, 0, 255));
}

TEST(TestAssignmentOperator, assignSmallerImageToBiggerImage)
{
    int height = 9;
    int width = 8;
    // make a 72-pixel image with RGB = (5,6,7)
    Image im1(width, height, 5, 6, 7);
    Pixel pix(5, 6, 7);
    im1.setPixel(0, 0, 255, 0, 0); // (0,0) is red
    im1.setPixel(4, 6, 0, 255, 0); // (4,6) is green
    im1.setPixel(5, 2, 0, 0, 255); // (5,2) is blue
    // make a 24-pixel all-black image
    Image im2(8, 3);
    im2 = im1;
    // ASSERT correct dimensions before continuing on..
    ASSERT_EQ(im2.getHeight(), height);
    ASSERT_EQ(im2.getWidth(), width);
    // check some pixels in im2
    EXPECT_EQ(im2.getPixel(0, 0), Pixel(255, 0, 0));
    EXPECT_EQ(im2.getPixel(height-1, width-1), pix);
    EXPECT_EQ(im2.getPixel(0, width-1), pix);
    EXPECT_EQ(im2.getPixel(height-1, 0), pix);
    EXPECT_EQ(im2.getPixel(3, 2), pix);
    EXPECT_EQ(im2.getPixel(4, 6), Pixel(0, 255, 0));
    EXPECT_EQ(im2.getPixel(5, 2), Pixel(0, 0, 255));
}

TEST(TestAssignmentOperator, assignBiggerImageToSmallerImage)
{
    int height = 9;
    int width = 8;
    // make a 72-pixel image with RGB = (5,6,7)
    Image im1(width, height, 5, 6, 7);
    Pixel pix(5, 6, 7);
    im1.setPixel(0, 0, 255, 0, 0); // (0,0) is red
    im1.setPixel(4, 6, 0, 255, 0); // (4,6) is green
    im1.setPixel(5, 2, 0, 0, 255); // (5,2) is blue
    // make a 88-pixel all-black image
    Image im2(8, 11);
    im2 = im1;
    // ASSERT correct dimensions before continuing on..
    ASSERT_EQ(im2.getHeight(), height);
    ASSERT_EQ(im2.getWidth(), width);
    // check some pixels in im2
    EXPECT_EQ(im2.getPixel(0, 0), Pixel(255, 0, 0));
    EXPECT_EQ(im2.getPixel(height-1, width-1), pix);
    EXPECT_EQ(im2.getPixel(0, width-1), pix);
    EXPECT_EQ(im2.getPixel(height-1, 0), pix);
    EXPECT_EQ(im2.getPixel(3, 2), pix);
    EXPECT_EQ(im2.getPixel(4, 6), Pixel(0, 255, 0));
    EXPECT_EQ(im2.getPixel(5, 2), Pixel(0, 0, 255));
}

// // copy constructor

TEST(TestCopyConstructor, basicOperation)
{
    int height = 9;
    int width = 8;
    // make a 72-pixel image with RGB = (5,6,7)
    Image im1(width, height, 5, 6, 7);
    Pixel pix(5, 6, 7);
    im1.setPixel(0, 0, 255, 0, 0); // (0,0) is red
    im1.setPixel(4, 6, 0, 255, 0); // (4,6) is green
    im1.setPixel(5, 2, 0, 0, 255); // (5,2) is blue
    Image im2 = im1;
    // ASSERT correct dimensions before continuing on..
    ASSERT_EQ(im2.getHeight(), height);
    ASSERT_EQ(im2.getWidth(), width);
    // check some pixels in im2
    EXPECT_EQ(im2.getPixel(0, 0), Pixel(255, 0, 0));
    EXPECT_EQ(im2.getPixel(height-1, width-1), pix);
    EXPECT_EQ(im2.getPixel(0, width-1), pix);
    EXPECT_EQ(im2.getPixel(height-1, 0), pix);
    EXPECT_EQ(im2.getPixel(3, 2), pix);
    EXPECT_EQ(im2.getPixel(4, 6), Pixel(0, 255, 0));
    EXPECT_EQ(im2.getPixel(5, 2), Pixel(0, 0, 255));
}

}  // namespace

// main() for testing -- boilerplate
int main(int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
