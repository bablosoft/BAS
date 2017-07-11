#include "imagefinder.h"
#include "base64.h"
#include "lodepng.h"
#include "log.h"


ImageFinder::ImageFinder()
{
    Width = 0;
    Height = 0;
}

void ImageFinder::ClearImage()
{
    ImageToFind.release();
    Data.clear();
    Width = 0;
    Height = 0;
}

void ImageFinder::SetImage(const std::string& base64)
{
    ClearImage();

    {
        std::string raw_png = base64_decode(base64);
        lodepng::decode(Data, Width, Height, (const unsigned char *)raw_png.c_str(), raw_png.size());
    }

    ImageToFind = Mat(Height, Width, CV_8UC4, Data.data());
    cvtColor(ImageToFind,ImageToFind, COLOR_BGRA2RGBA);

}

std::string ImageFinder::FindImage(char *data, int width, int height, int scrollx, int scrolly)
{
    Mat Screen = Mat(height, width, CV_8UC4, data);

    int result_cols =  Screen.cols - ImageToFind.cols + 1;
    int result_rows = Screen.rows - ImageToFind.rows + 1;

    if(result_cols<=0 || result_rows<=0)
        return std::string("-1|0|0|") + std::to_string(Width) + std::string("|") + std::to_string(Height);

    if(Result.cols != result_cols || Result.rows != result_rows)
    {
        Result.release();
        Result.create( result_rows, result_cols, CV_32FC1 );
    }

    matchTemplate( Screen, ImageToFind, Result, CV_TM_CCOEFF_NORMED );

    double minVal; double maxVal; Point minLoc; Point maxLoc;
    Point matchLoc;

    minMaxLoc( Result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

    matchLoc = maxLoc;

    Screen.release();
    //Result.release();

    return std::to_string((int)(maxVal * 100.0)) + std::string("|") + std::to_string(matchLoc.x + scrollx) + std::string("|") + std::to_string(matchLoc.y + scrolly) + std::string("|") + std::to_string(Width) + std::string("|") + std::to_string(Height);
}
