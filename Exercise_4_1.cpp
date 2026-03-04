/****************************************************************************************
* Create a 500 × 500 single channel uchar image with every pixel equal to zero.
* a.)Create an ASCII numeric typewriter where you can type numbers into your
*    computer and have the number show up in a 20 - pixel - high by 10 - pixel - wide
*    block.As you type, the numbers will display from left to right until you hit the
*    end of the image.Then just stop.
* b.)Allow for carriage return and backspace.
* c.)Allow for arrow keys to edit each number.
* d.)Create a key that will convert the resulting image into a color image, each
*    number taking on a different color.
*****************************************************************************************/

#include<array>
#include<iostream>
#include<iterator>
#include<vector>
#include<opencv2/opencv.hpp>

const unsigned char OO = 0x00; // Background is black
const unsigned char FF = 0xFF; // Digit colour is white

const unsigned char digit0[20][10] = {
    {OO,OO,OO,OO,OO,OO,OO,OO,OO,OO},
    {OO,OO,OO,FF,FF,FF,FF,OO,OO,OO},
    {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,OO,FF,FF,FF,FF,OO,OO,OO},
    {OO,OO,OO,OO,OO,OO,OO,OO,OO,OO}
};
const unsigned char digit1[20][10] = {
    {OO,OO,OO,OO,OO,OO,OO,OO,OO,OO},
    {OO,OO,OO,OO,FF,OO,OO,OO,OO,OO},
    {OO,OO,OO,FF,FF,OO,OO,OO,OO,OO},
    {OO,OO,FF,OO,FF,OO,OO,OO,OO,OO},
    {OO,OO,OO,OO,FF,OO,OO,OO,OO,OO},
    {OO,OO,OO,OO,FF,OO,OO,OO,OO,OO},
    {OO,OO,OO,OO,FF,OO,OO,OO,OO,OO},
    {OO,OO,OO,OO,FF,OO,OO,OO,OO,OO},
    {OO,OO,OO,OO,FF,OO,OO,OO,OO,OO},
    {OO,OO,OO,OO,FF,OO,OO,OO,OO,OO},
    {OO,OO,OO,OO,FF,OO,OO,OO,OO,OO},
    {OO,OO,OO,OO,FF,OO,OO,OO,OO,OO},
    {OO,OO,OO,OO,FF,OO,OO,OO,OO,OO},
    {OO,OO,OO,OO,FF,OO,OO,OO,OO,OO},
    {OO,OO,OO,OO,FF,OO,OO,OO,OO,OO},
    {OO,OO,OO,OO,FF,OO,OO,OO,OO,OO},
    {OO,OO,OO,OO,FF,OO,OO,OO,OO,OO},
    {OO,OO,OO,OO,FF,OO,OO,OO,OO,OO},
    {OO,OO,FF,FF,FF,FF,FF,OO,OO,OO},
    {OO,OO,OO,OO,OO,OO,OO,OO,OO,OO}
};

const unsigned char digit2[20][10] = {
    {OO,OO,OO,OO,OO,OO,OO,OO,OO,OO},
    {OO,OO,FF,FF,FF,FF,FF,OO,OO,OO},
    {OO,FF,OO,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,OO,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,OO,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,OO,OO,OO,OO,FF,OO,OO,OO},
    {OO,OO,OO,OO,OO,FF,OO,OO,OO,OO},
    {OO,OO,OO,OO,FF,OO,OO,OO,OO,OO},
    {OO,OO,OO,FF,OO,OO,OO,OO,OO,OO},
    {OO,OO,FF,OO,OO,OO,OO,OO,OO,OO},
    {OO,FF,OO,OO,OO,OO,OO,OO,OO,OO},
    {OO,FF,OO,OO,OO,OO,OO,OO,OO,OO},
    {OO,FF,OO,OO,OO,OO,OO,OO,OO,OO},
    {OO,FF,OO,OO,OO,OO,OO,OO,OO,OO},
    {OO,FF,OO,OO,OO,OO,OO,OO,OO,OO},
    {OO,FF,OO,OO,OO,OO,OO,OO,OO,OO},
    {OO,FF,OO,OO,OO,OO,OO,OO,OO,OO},
    {OO,FF,OO,OO,OO,OO,OO,OO,OO,OO},
    {OO,FF,FF,FF,FF,FF,FF,FF,OO,OO},
    {OO,OO,OO,OO,OO,OO,OO,OO,OO,OO}
};

const unsigned char digit3[20][10] = {
    {OO,OO,OO,OO,OO,OO,OO,OO,OO,OO}, {OO,OO,FF,FF,FF,FF,FF,OO,OO,OO}, {OO,FF,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,OO,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,OO,OO,FF,FF,FF,OO,OO,OO}, {OO,OO,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,OO,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,OO,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,FF,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,FF,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,FF,FF,FF,FF,FF,OO,OO,OO}, {OO,OO,OO,OO,OO,OO,OO,OO,OO,OO}
};

const unsigned char digit4[20][10] = {
    {OO,OO,OO,OO,OO,OO,OO,OO,OO,OO}, {OO,OO,OO,OO,OO,FF,OO,OO,OO,OO}, {OO,OO,OO,OO,FF,FF,OO,OO,OO,OO}, {OO,OO,OO,FF,OO,FF,OO,OO,OO,OO}, {OO,OO,FF,OO,OO,FF,OO,OO,OO,OO},
    {OO,FF,OO,OO,OO,FF,OO,OO,OO,OO}, {OO,FF,OO,OO,OO,FF,OO,OO,OO,OO}, {OO,FF,OO,OO,OO,FF,OO,OO,OO,OO}, {OO,FF,OO,OO,OO,FF,OO,OO,OO,OO}, {OO,FF,OO,OO,OO,FF,OO,OO,OO,OO},
    {OO,FF,FF,FF,FF,FF,FF,FF,OO,OO}, {OO,OO,OO,OO,OO,FF,OO,OO,OO,OO}, {OO,OO,OO,OO,OO,FF,OO,OO,OO,OO}, {OO,OO,OO,OO,OO,FF,OO,OO,OO,OO}, {OO,OO,OO,OO,OO,FF,OO,OO,OO,OO},
    {OO,OO,OO,OO,OO,FF,OO,OO,OO,OO}, {OO,OO,OO,OO,OO,FF,OO,OO,OO,OO}, {OO,OO,OO,OO,OO,FF,OO,OO,OO,OO}, {OO,OO,OO,OO,OO,FF,OO,OO,OO,OO}, {OO,OO,OO,OO,OO,OO,OO,OO,OO,OO}
};

const unsigned char digit5[20][10] = {
    {OO,OO,OO,OO,OO,OO,OO,OO,OO,OO},
    {OO,FF,FF,FF,FF,FF,FF,FF,FF,OO},
    {OO,FF,OO,OO,OO,OO,OO,OO,OO,OO},
    {OO,FF,OO,OO,OO,OO,OO,OO,OO,OO},
    {OO,FF,OO,OO,OO,OO,OO,OO,OO,OO},
    {OO,FF,OO,OO,OO,OO,OO,OO,OO,OO},
    {OO,FF,FF,FF,FF,FF,FF,OO,OO,OO},
    {OO,OO,OO,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,OO,OO,OO,OO,OO,OO,FF,OO},
    {OO,OO,OO,OO,OO,OO,OO,OO,FF,OO},
    {OO,OO,OO,OO,OO,OO,OO,OO,FF,OO},
    {OO,OO,OO,OO,OO,OO,OO,OO,FF,OO},
    {OO,OO,OO,OO,OO,OO,OO,OO,FF,OO},
    {OO,OO,OO,OO,OO,OO,OO,OO,FF,OO},
    {OO,OO,OO,OO,OO,OO,OO,OO,FF,OO},
    {OO,OO,OO,OO,OO,OO,OO,OO,FF,OO},
    {OO,FF,OO,OO,OO,OO,OO,OO,FF,OO},
    {OO,FF,OO,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,FF,FF,FF,FF,FF,OO,OO,OO},
    {OO,OO,OO,OO,OO,OO,OO,OO,OO,OO}
};

const unsigned char digit6[20][10] = {
    {OO,OO,OO,OO,OO,OO,OO,OO,OO,OO}, {OO,OO,OO,FF,FF,FF,FF,OO,OO,OO}, {OO,OO,FF,OO,OO,OO,OO,OO,OO,OO}, {OO,FF,OO,OO,OO,OO,OO,OO,OO,OO}, {OO,FF,OO,OO,OO,OO,OO,OO,OO,OO},
    {OO,FF,FF,FF,FF,FF,OO,OO,OO,OO}, {OO,FF,OO,OO,OO,OO,FF,OO,OO,OO}, {OO,FF,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,FF,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,FF,OO,OO,OO,OO,OO,FF,OO,OO},
    {OO,FF,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,FF,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,FF,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,FF,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,FF,OO,OO,OO,OO,OO,FF,OO,OO},
    {OO,FF,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,FF,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,OO,FF,FF,FF,FF,OO,OO,OO}, {OO,OO,OO,OO,OO,OO,OO,OO,OO,OO}
};

const unsigned char digit7[20][10] = {
    {OO,OO,OO,OO,OO,OO,OO,OO,OO,OO}, {OO,FF,FF,FF,FF,FF,FF,FF,OO,OO}, {OO,OO,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,OO,OO,OO,OO,FF,OO,OO,OO},
    {OO,OO,OO,OO,OO,OO,FF,OO,OO,OO}, {OO,OO,OO,OO,OO,FF,OO,OO,OO,OO}, {OO,OO,OO,OO,OO,FF,OO,OO,OO,OO}, {OO,OO,OO,OO,FF,OO,OO,OO,OO,OO}, {OO,OO,OO,OO,FF,OO,OO,OO,OO,OO},
    {OO,OO,OO,FF,OO,OO,OO,OO,OO,OO}, {OO,OO,OO,FF,OO,OO,OO,OO,OO,OO}, {OO,OO,FF,OO,OO,OO,OO,OO,OO,OO}, {OO,OO,FF,OO,OO,OO,OO,OO,OO,OO}, {OO,OO,FF,OO,OO,OO,OO,OO,OO,OO},
    {OO,OO,FF,OO,OO,OO,OO,OO,OO,OO}, {OO,OO,FF,OO,OO,OO,OO,OO,OO,OO}, {OO,OO,FF,OO,OO,OO,OO,OO,OO,OO}, {OO,OO,FF,OO,OO,OO,OO,OO,OO,OO}, {OO,OO,OO,OO,OO,OO,OO,OO,OO,OO}
};

const unsigned char digit8[20][10] = {
    {OO,OO,OO,OO,OO,OO,OO,OO,OO,OO}, {OO,OO,OO,FF,FF,FF,FF,OO,OO,OO}, {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,OO,FF,FF,FF,FF,OO,OO,OO}, {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,OO,FF,FF,FF,FF,OO,OO,OO}, {OO,OO,OO,OO,OO,OO,OO,OO,OO,OO}
};

const unsigned char digit9[20][10] = {
    {OO,OO,OO,OO,OO,OO,OO,OO,OO,OO}, {OO,OO,OO,FF,FF,FF,FF,OO,OO,OO}, {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO}, {OO,FF,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,FF,OO,OO,OO,OO,OO,FF,OO,OO},
    {OO,FF,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,FF,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,FF,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,FF,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,FF,OO,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,FF,FF,FF,FF,FF,FF,OO,OO}, {OO,OO,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,OO,OO,OO,OO,OO,FF,OO,OO},
    {OO,OO,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,OO,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,FF,OO,OO,OO,OO,FF,OO,OO}, {OO,OO,OO,FF,FF,FF,FF,OO,OO,OO}, {OO,OO,OO,OO,OO,OO,OO,OO,OO,OO}
};


using digPtr = const unsigned char (*)[20][10];
//const digPtr digits[10] = {&digit0, &digit1,  &digit2,  &digit3,  &digit4,
//                           &digit5, &digit6,  &digit7,  &digit8,  &digit9 };


std::vector<digPtr> digits = {&digit0, &digit1,  &digit2,  &digit3,  &digit4,
                           &digit5, &digit6,  &digit7,  &digit8,  &digit9 };



//Handling arrow keys
enum class Directions
{
    Left, Up, Right, Down
};

//Functions 
void drawDigit(cv::Mat& image, int value, unsigned* startX, unsigned* startY);
void boundryCheck(unsigned* coord, Directions dir);
void colouringDigits(const cv::Mat& image);

//int main(int argc, char* argv[]) {
int main(void) {


    //Create an array for a 8 bit 500 width and 500 height image filled with 0s
    cv::Mat img = cv::Mat::zeros(500, 500, CV_8UC1);
    
    //img.clone() for cursor handling
    cv::Mat disp;

    cv::namedWindow("Press ESC to exit", cv::WINDOW_AUTOSIZE);
    //cv::imshow("Press ESC to exit", img);

    //Define cursor
    unsigned char cursor[20][10] = {
    {FF,FF,FF,FF,FF,FF,FF,FF,FF,FF},
    {FF,OO,OO,OO,OO,OO,OO,OO,OO,FF},
    {FF,OO,OO,OO,OO,OO,OO,OO,OO,FF},
    {FF,OO,OO,OO,OO,OO,OO,OO,OO,FF},
    {FF,OO,OO,OO,OO,OO,OO,OO,OO,FF},
    {FF,OO,OO,OO,OO,OO,OO,OO,OO,FF},
    {FF,OO,OO,OO,OO,OO,OO,OO,OO,FF},
    {FF,OO,OO,OO,OO,OO,OO,OO,OO,FF},
    {FF,OO,OO,OO,OO,OO,OO,OO,OO,FF},
    {FF,OO,OO,OO,OO,OO,OO,OO,OO,FF},
    {FF,OO,OO,OO,OO,OO,OO,OO,OO,FF},
    {FF,OO,OO,OO,OO,OO,OO,OO,OO,FF},
    {FF,OO,OO,OO,OO,OO,OO,OO,OO,FF},
    {FF,OO,OO,OO,OO,OO,OO,OO,OO,FF},
    {FF,OO,OO,OO,OO,OO,OO,OO,OO,FF},
    {FF,OO,OO,OO,OO,OO,OO,OO,OO,FF},
    {FF,OO,OO,OO,OO,OO,OO,OO,OO,FF},
    {FF,OO,OO,OO,OO,OO,OO,OO,OO,FF},
    {FF,OO,OO,OO,OO,OO,OO,OO,OO,FF},
    {FF,FF,FF,FF,FF,FF,FF,FF,FF,FF}
    };
    
    //Wrapping a row C++ array into cv::Mat
    cv::Mat mask(20, 10, CV_8UC1, cursor);
    

    int inputDigit{};  //Input key
    unsigned startX = 0, startY = 0;  //Location handling
    
    do {
        inputDigit = cv::waitKeyEx(0);

        if (inputDigit == 27) {
            break;
        } // ESC for exit

        if (inputDigit == 'c') {
            colouringDigits(img);
        }
        
        switch (inputDigit)
            {

            case 0x250000: boundryCheck(&startX, Directions::Left) ;    break;     //Left
            case 0x260000: boundryCheck(&startY, Directions::Up);       break;     //Up
            case 0x270000: boundryCheck(&startX, Directions::Right);    break;     //Right
            case 0x280000: boundryCheck(&startY, Directions::Down);     break;     //Down

            default:
                break;
            } //Check if input is arrow key

        if (inputDigit >= '0' && inputDigit <= '9') {
            inputDigit -= '0';
            drawDigit(img, inputDigit, &startX, &startY);

        } //Check if input is between 0...9 and convert to int 0...9

        cv::Rect imMask(startX, startY, 10, 20); //Create mask for region to write to
        disp = img.clone();

        //cv::add(disp(imMask), mask, disp(imMask), mask);

        mask.copyTo(disp(imMask), mask);

         cv::imshow("Press ESC to exit", disp);
    } while (true);


    cv::destroyAllWindows();
    
}

void drawDigit(cv::Mat& image, int value, unsigned* startX, unsigned* startY) {
    const unsigned char (*ptr)[10] = nullptr;

    //Select based on name

    switch (value) {
    case 0: ptr = digit0; break; 
    case 1: ptr = digit1; break;
    case 2: ptr = digit2; break; 
    case 3: ptr = digit3; break;
    case 4: ptr = digit4; break; 
    case 5: ptr = digit5; break;
    case 6: ptr = digit6; break; 
    case 7: ptr = digit7; break;
    case 8: ptr = digit8; break; 
    case 9: ptr = digit9; break;
    }
    
    

    if (ptr) {
        
        cv::Mat digit(20, 10, CV_8UC1, const_cast<unsigned char*>(&ptr[0][0]));

        cv::Rect location(*startX, *startY, 10, 20);

        //image(location).copyTo(digit)
        digit.copyTo(image(location));

        *startX += 10;
        if (*startX == 500 && *startY != 480 ) {
            *startX = 0;
            *startY += 20;
        }
        if (*startX == 500 && *startY == 480) {
            *startX = 0;
            *startY = 0;
        }

       
    }
}


void boundryCheck(unsigned* coord, Directions dir ) {

    switch (dir)
    {
    case Directions::Left:
        *coord < 10 ? *coord = 0 : *coord -= 10;
        break;
    case Directions::Up:
        *coord < 10 ? *coord = 0 : *coord -= 20;
        break;
    case Directions::Right:
        *coord > 489 ? *coord = 490 : *coord += 10;
        break;
    case Directions::Down:
        *coord > 479 ? *coord = 480 : *coord += 20;
        break;
    default:
        break;
    }

   
}

void colouringDigits(const cv::Mat& image) {

    const unsigned char (*ptrToDigit)[20][10] = nullptr;

    size_t coordX{}, coordY{};
    size_t windowWidth{ 10 };
    size_t windowHeight{ 20 };
    
    cv::Mat colorImg(500, 500, CV_8UC3);

    static const std::array<cv::Vec3b, 10> PALETTE = {
        cv::Vec3b(68,  1,  84),
        cv::Vec3b(59, 82, 139),
        cv::Vec3b(33,145,140),
        cv::Vec3b(94,201, 98),
        cv::Vec3b(171,221, 84),
        cv::Vec3b(253,231, 37),
        cv::Vec3b(253,174, 97),
        cv::Vec3b(244,109, 67),
        cv::Vec3b(214, 45, 49),
        cv::Vec3b(12, 12, 12)
    };

    //std::vector<digPtr>::iterator end = std::end(digits);
    //std::vector<digPtr>::iterator it = std::begin(digits);
    // auto start = std::begin(digits);
    auto end = std::end(digits);

    for (size_t y{}; y < (image.rows / windowHeight); y++) {
        for (size_t x{}; x < (image.cols / windowWidth); x++) {
            //for (size_t z{}; z < (sizeof(digits) / sizeof(digits[0])); z++) {
            int z{};
            for (auto it = std::begin(digits) ; it != end; it++) {

                //ptrToDigit = digits[z];
                ptrToDigit = *it;
                cv::Rect window(coordX, coordY, windowWidth, windowHeight);

                cv::Mat test(20, 10, CV_8UC1, const_cast<unsigned char*>(ptrToDigit[0][0]));
                if (!(cv::countNonZero(image(window)) == 0)) {
                    if (!cv::countNonZero(image(window) - test)) {
                        colorImg(window) = image(window);
                        colorImg(window).setTo(PALETTE[z], test);

                        break;
                    }
                }
                z++;
            }
            if (coordX < 490) {
                coordX += 10;
            }
            else {
                coordX = 0;
            }
        }
        if (coordY < 480) {
            coordY += 20;
        }
        else {
            coordY = 0;


        }

        cv::namedWindow("Color Window", cv::WINDOW_AUTOSIZE);
        cv::imshow("Color Window", colorImg);
    }
}