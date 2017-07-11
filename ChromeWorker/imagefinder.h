#ifndef IMAGEFINDER_H
#define IMAGEFINDER_H

#include <string>
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;

class ImageFinder
{
    std::vector<unsigned char> Data;
    Mat ImageToFind;
    Mat Result;
    unsigned int Width;
    unsigned int Height;
public:
    ImageFinder();

    void ClearImage();
    void SetImage(const std::string& base64);
    std::string FindImage(char *data, int width, int height, int scrollx, int scrolly);
};

#endif // IMAGEFINDER_H
