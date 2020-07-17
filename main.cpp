/*
 * textdetection.cpp
 *
 * A demo program of End-to-end Scene Text Detection and Recognition:
 * Shows the use of the Tesseract OCR API with the Extremal Region Filter algorithm described in:
 * Neumann L., Matas J.: Real-Time Scene Text Localization and Recognition, CVPR 2012
 *
 * Created on: Jul 31, 2014
 *     Author: Lluis Gomez i Bigorda <lgomez AT cvc.uab.es>
 */

#include "opencv2/text.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <tesseract/baseapi.h>

#include <iostream>

using namespace std;
using namespace cv;
using namespace cv::text;

//Calculate edit distance between two words
size_t edit_distance(const string& A, const string& B);
size_t min(size_t x, size_t y, size_t z);
bool   isRepetitive(const string& s);
bool   sort_by_length(const string &a, const string &b);
//Draw ER's in an image via floodFill
void   er_draw(vector<Mat> &channels, vector<vector<ERStat> > &regions, vector<Vec2i> group, Mat& segmentation);

char* read_text(Mat input_image)
{
    tesseract::TessBaseAPI text_recognizer;
    text_recognizer.Init("", "eng", tesseract::OEM_DEFAULT);
    text_recognizer.SetImage((uchar*)input_image.data, input_image.cols, input_image.rows, input_image.channels(), input_image.step1());
    text_recognizer.Recognize(0);
    return text_recognizer.GetUTF8Text();
}
//Perform text detection and recognition and evaluate results using edit distance
int main(int argc, char* argv[])
{
    cout << endl << argv[0] << endl << endl;
    cout << "A demo program of End-to-end Scene Text Detection and Recognition: " << endl;
    cout << "Shows the use of the Tesseract OCR API with the Extremal Region Filter algorithm described in:" << endl;
    cout << "Neumann L., Matas J.: Real-Time Scene Text Localization and Recognition, CVPR 2012" << endl << endl;

    Mat image;
    
    if(argc>1)
        image  = imread(argv[1]);
    else
    {
        cout << "    Usage: " << argv[0] << " <input_image> [<gt_word1> ... <gt_wordN>]" << endl;
        return(0);
    }

    cout << "IMG_W=" << image.cols << endl;
    cout << "IMG_H=" << image.rows << endl;

    /*Text Detection*/

    // Extract channels to be processed individually
    vector<Mat> channels;

    Mat cropedImage = image(Rect(670, 220, 600, 630));

    Mat grey;
    cvtColor(cropedImage, grey, cv::COLOR_BGR2GRAY);

    // Notice here we are only using grey channel, see textdetection.cpp for example with more channels

    Mat bw;
    Size size(6000, 6000);//the dst image size,e.g.100x100  4000, 4000 funciona bien
    resize(grey,grey,size);//resize image

    adaptiveThreshold(~grey, grey, 50, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 79, 31);
    erode(grey, grey, Mat(), Point(-1, -1), 8, 1, 1);
    dilate(grey, grey, Mat(), Point(-1, -1), 1, 1, 1);

    Mat mask;
    inRange(grey, Scalar(50), Scalar(255), grey);

    Rect horizontalRect = Rect(0,0,6000,900);
    Rect horizontalRect2 = Rect(0,1470,6000,100);
    Rect verticalRect = Rect(4650, 0, 320, 6000);
    rectangle(grey,horizontalRect, Scalar(255, 255, 255), -1, 4, 0);
    rectangle(grey,horizontalRect2, Scalar(255, 255, 255), -1, 4, 0);
    rectangle(grey, verticalRect, Scalar(255, 255, 255), -1, 4, 0);


    imshow("test", grey);
    printf("OCR output:\n%s", read_text(grey));
    waitKey(0);

    return 0;
}
