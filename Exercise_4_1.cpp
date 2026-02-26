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

#include<iostream>
#include<opencv2/opencv.hpp>

const unsigned char __ = 0x00; // Background is black
const unsigned char FF = 0xFF; // Digit colour is white

//Handling arrow keys
enum class Directions
{
    Left, Up, Right, Down
};

//Functions 
void drawDigit(cv::Mat& image, int value, unsigned* startX, unsigned* startY);
void boundryCheck(unsigned* coord, Directions dir);

int main(int argc, char* argv[]) {

	//Create an array for a 8 bit 500 width and 500 height image filled with 0s
	cv::Mat img = cv::Mat::zeros(500, 500, CV_8UC1);
    
    //img.clone() for cursor handling
    cv::Mat disp;

	cv::namedWindow("Press ESC to exit", cv::WINDOW_AUTOSIZE);
	cv::imshow("Press ESC to exit", img);

    //Define cursor
    unsigned char cursor[20][10] = {
    {FF,FF,FF,FF,FF,FF,FF,FF,FF,FF},
    {FF,__,__,__,__,__,__,__,__,FF},
    {FF,__,__,__,__,__,__,__,__,FF},
    {FF,__,__,__,__,__,__,__,__,FF},
    {FF,__,__,__,__,__,__,__,__,FF},
    {FF,__,__,__,__,__,__,__,__,FF},
    {FF,__,__,__,__,__,__,__,__,FF},
    {FF,__,__,__,__,__,__,__,__,FF},
    {FF,__,__,__,__,__,__,__,__,FF},
    {FF,__,__,__,__,__,__,__,__,FF},
    {FF,__,__,__,__,__,__,__,__,FF},
    {FF,__,__,__,__,__,__,__,__,FF},
    {FF,__,__,__,__,__,__,__,__,FF},
    {FF,__,__,__,__,__,__,__,__,FF},
    {FF,__,__,__,__,__,__,__,__,FF},
    {FF,__,__,__,__,__,__,__,__,FF},
    {FF,__,__,__,__,__,__,__,__,FF},
    {FF,__,__,__,__,__,__,__,__,FF},
    {FF,__,__,__,__,__,__,__,__,FF},
    {FF,FF,FF,FF,FF,FF,FF,FF,FF,FF}
    };
    
    //Wrapping a row C++ array into cv::Mat
    cv::Mat mask(20, 10, CV_8UC1, cursor);
    

    int inputDigit{};  //Input key
    unsigned startX{}, startY{};  //Location handling
    
    do {
        inputDigit = cv::waitKeyEx(0);

        if (inputDigit == 27) {
            break;
        } // ESC for exit
        
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
    } while (true)
      	

    ;

	cv::destroyAllWindows;
	
}

void drawDigit(cv::Mat& image, int value, unsigned* startX, unsigned* startY) {
    const unsigned char (*ptr)[10] = nullptr;

    const unsigned char digit0[20][10] = {
        {__,__,__,__,__,__,__,__,__,__},
        {__,__,__,FF,FF,FF,FF,__,__,__},
        {__,__,FF,__,__,__,__,FF,__,__},
        {__,__,FF,__,__,__,__,FF,__,__},
        {__,__,FF,__,__,__,__,FF,__,__},
        {__,__,FF,__,__,__,__,FF,__,__},
        {__,__,FF,__,__,__,__,FF,__,__},
        {__,__,FF,__,__,__,__,FF,__,__},
        {__,__,FF,__,__,__,__,FF,__,__},
        {__,__,FF,__,__,__,__,FF,__,__},
        {__,__,FF,__,__,__,__,FF,__,__},
        {__,__,FF,__,__,__,__,FF,__,__},
        {__,__,FF,__,__,__,__,FF,__,__},
        {__,__,FF,__,__,__,__,FF,__,__},
        {__,__,FF,__,__,__,__,FF,__,__},
        {__,__,FF,__,__,__,__,FF,__,__},
        {__,__,FF,__,__,__,__,FF,__,__},
        {__,__,FF,__,__,__,__,FF,__,__},
        {__,__,__,FF,FF,FF,FF,__,__,__},
        {__,__,__,__,__,__,__,__,__,__}
    };

    const unsigned char digit1[20][10] = {
        {__,__,__,__,__,__,__,__,__,__}, 
        {__,__,__,__,FF,__,__,__,__,__}, 
        {__,__,__,FF,FF,__,__,__,__,__}, 
        {__,__,FF,__,FF,__,__,__,__,__}, 
        {__,__,__,__,FF,__,__,__,__,__},
        {__,__,__,__,FF,__,__,__,__,__}, 
        {__,__,__,__,FF,__,__,__,__,__}, 
        {__,__,__,__,FF,__,__,__,__,__}, 
        {__,__,__,__,FF,__,__,__,__,__}, 
        {__,__,__,__,FF,__,__,__,__,__},
        {__,__,__,__,FF,__,__,__,__,__}, 
        {__,__,__,__,FF,__,__,__,__,__}, 
        {__,__,__,__,FF,__,__,__,__,__}, 
        {__,__,__,__,FF,__,__,__,__,__}, 
        {__,__,__,__,FF,__,__,__,__,__},
        {__,__,__,__,FF,__,__,__,__,__}, 
        {__,__,__,__,FF,__,__,__,__,__}, 
        {__,__,__,__,FF,__,__,__,__,__}, 
        {__,__,FF,FF,FF,FF,FF,__,__,__}, 
        {__,__,__,__,__,__,__,__,__,__}
    };

    const unsigned char digit2[20][10] = {
        {__,__,__,__,__,__,__,__,__,__}, 
        {__,__,FF,FF,FF,FF,FF,__,__,__}, 
        {__,FF,__,__,__,__,__,FF,__,__}, 
        {__,__,__,__,__,__,__,FF,__,__}, 
        {__,__,__,__,__,__,__,FF,__,__},
        {__,__,__,__,__,__,FF,__,__,__}, 
        {__,__,__,__,__,FF,__,__,__,__}, 
        {__,__,__,__,FF,__,__,__,__,__}, 
        {__,__,__,FF,__,__,__,__,__,__}, 
        {__,__,FF,__,__,__,__,__,__,__},
        {__,FF,__,__,__,__,__,__,__,__}, 
        {__,FF,__,__,__,__,__,__,__,__}, 
        {__,FF,__,__,__,__,__,__,__,__}, 
        {__,FF,__,__,__,__,__,__,__,__}, 
        {__,FF,__,__,__,__,__,__,__,__},
        {__,FF,__,__,__,__,__,__,__,__}, 
        {__,FF,__,__,__,__,__,__,__,__}, 
        {__,FF,__,__,__,__,__,__,__,__}, 
        {__,FF,FF,FF,FF,FF,FF,FF,__,__}, 
        {__,__,__,__,__,__,__,__,__,__}
    };

    const unsigned char digit3[20][10] = {
        {__,__,__,__,__,__,__,__,__,__}, {__,__,FF,FF,FF,FF,FF,__,__,__}, {__,FF,__,__,__,__,__,FF,__,__}, {__,__,__,__,__,__,__,FF,__,__}, {__,__,__,__,__,__,__,FF,__,__},
        {__,__,__,__,FF,FF,FF,__,__,__}, {__,__,__,__,__,__,__,FF,__,__}, {__,__,__,__,__,__,__,FF,__,__}, {__,__,__,__,__,__,__,FF,__,__}, {__,__,__,__,__,__,__,FF,__,__},
        {__,__,__,__,__,__,__,FF,__,__}, {__,__,__,__,__,__,__,FF,__,__}, {__,__,__,__,__,__,__,FF,__,__}, {__,__,__,__,__,__,__,FF,__,__}, {__,__,__,__,__,__,__,FF,__,__},
        {__,__,__,__,__,__,__,FF,__,__}, {__,FF,__,__,__,__,__,FF,__,__}, {__,FF,__,__,__,__,__,FF,__,__}, {__,__,FF,FF,FF,FF,FF,__,__,__}, {__,__,__,__,__,__,__,__,__,__}
    };

    const unsigned char digit4[20][10] = {
        {__,__,__,__,__,__,__,__,__,__}, {__,__,__,__,__,FF,__,__,__,__}, {__,__,__,__,FF,FF,__,__,__,__}, {__,__,__,FF,__,FF,__,__,__,__}, {__,__,FF,__,__,FF,__,__,__,__},
        {__,FF,__,__,__,FF,__,__,__,__}, {__,FF,__,__,__,FF,__,__,__,__}, {__,FF,__,__,__,FF,__,__,__,__}, {__,FF,__,__,__,FF,__,__,__,__}, {__,FF,__,__,__,FF,__,__,__,__},
        {__,FF,FF,FF,FF,FF,FF,FF,__,__}, {__,__,__,__,__,FF,__,__,__,__}, {__,__,__,__,__,FF,__,__,__,__}, {__,__,__,__,__,FF,__,__,__,__}, {__,__,__,__,__,FF,__,__,__,__},
        {__,__,__,__,__,FF,__,__,__,__}, {__,__,__,__,__,FF,__,__,__,__}, {__,__,__,__,__,FF,__,__,__,__}, {__,__,__,__,__,FF,__,__,__,__}, {__,__,__,__,__,__,__,__,__,__}
    };

    const unsigned char digit5[20][10] = {
        {__,__,__,__,__,__,__,__,__,__}, 
        {__,FF,FF,FF,FF,FF,FF,FF,FF,__}, 
        {__,FF,__,__,__,__,__,__,__,__}, 
        {__,FF,__,__,__,__,__,__,__,__}, 
        {__,FF,__,__,__,__,__,__,__,__},
        {__,FF,__,__,__,__,__,__,__,__},
        {__,FF,FF,FF,FF,FF,FF,__,__,__},
        {__,__,__,__,__,__,__,FF,__,__}, 
        {__,__,__,__,__,__,__,__,FF,__}, 
        {__,__,__,__,__,__,__,__,FF,__},
        {__,__,__,__,__,__,__,__,FF,__}, 
        {__,__,__,__,__,__,__,__,FF,__}, 
        {__,__,__,__,__,__,__,__,FF,__}, 
        {__,__,__,__,__,__,__,__,FF,__}, 
        {__,__,__,__,__,__,__,__,FF,__},
        {__,__,__,__,__,__,__,__,FF,__}, 
        {__,FF,__,__,__,__,__,__,FF,__}, 
        {__,FF,__,__,__,__,__,FF,__,__}, 
        {__,__,FF,FF,FF,FF,FF,__,__,__}, 
        {__,__,__,__,__,__,__,__,__,__}
    };

    const unsigned char digit6[20][10] = {
        {__,__,__,__,__,__,__,__,__,__}, {__,__,__,FF,FF,FF,FF,__,__,__}, {__,__,FF,__,__,__,__,__,__,__}, {__,FF,__,__,__,__,__,__,__,__}, {__,FF,__,__,__,__,__,__,__,__},
        {__,FF,FF,FF,FF,FF,__,__,__,__}, {__,FF,__,__,__,__,FF,__,__,__}, {__,FF,__,__,__,__,__,FF,__,__}, {__,FF,__,__,__,__,__,FF,__,__}, {__,FF,__,__,__,__,__,FF,__,__},
        {__,FF,__,__,__,__,__,FF,__,__}, {__,FF,__,__,__,__,__,FF,__,__}, {__,FF,__,__,__,__,__,FF,__,__}, {__,FF,__,__,__,__,__,FF,__,__}, {__,FF,__,__,__,__,__,FF,__,__},
        {__,FF,__,__,__,__,__,FF,__,__}, {__,FF,__,__,__,__,__,FF,__,__}, {__,__,FF,__,__,__,__,FF,__,__}, {__,__,__,FF,FF,FF,FF,__,__,__}, {__,__,__,__,__,__,__,__,__,__}
    };

    const unsigned char digit7[20][10] = {
        {__,__,__,__,__,__,__,__,__,__}, {__,FF,FF,FF,FF,FF,FF,FF,__,__}, {__,__,__,__,__,__,__,FF,__,__}, {__,__,__,__,__,__,__,FF,__,__}, {__,__,__,__,__,__,FF,__,__,__},
        {__,__,__,__,__,__,FF,__,__,__}, {__,__,__,__,__,FF,__,__,__,__}, {__,__,__,__,__,FF,__,__,__,__}, {__,__,__,__,FF,__,__,__,__,__}, {__,__,__,__,FF,__,__,__,__,__},
        {__,__,__,FF,__,__,__,__,__,__}, {__,__,__,FF,__,__,__,__,__,__}, {__,__,FF,__,__,__,__,__,__,__}, {__,__,FF,__,__,__,__,__,__,__}, {__,__,FF,__,__,__,__,__,__,__},
        {__,__,FF,__,__,__,__,__,__,__}, {__,__,FF,__,__,__,__,__,__,__}, {__,__,FF,__,__,__,__,__,__,__}, {__,__,FF,__,__,__,__,__,__,__}, {__,__,__,__,__,__,__,__,__,__}
    };

    const unsigned char digit8[20][10] = {
        {__,__,__,__,__,__,__,__,__,__}, {__,__,__,FF,FF,FF,FF,__,__,__}, {__,__,FF,__,__,__,__,FF,__,__}, {__,__,FF,__,__,__,__,FF,__,__}, {__,__,FF,__,__,__,__,FF,__,__},
        {__,__,__,FF,FF,FF,FF,__,__,__}, {__,__,FF,__,__,__,__,FF,__,__}, {__,__,FF,__,__,__,__,FF,__,__}, {__,__,FF,__,__,__,__,FF,__,__}, {__,__,FF,__,__,__,__,FF,__,__},
        {__,__,FF,__,__,__,__,FF,__,__}, {__,__,FF,__,__,__,__,FF,__,__}, {__,__,FF,__,__,__,__,FF,__,__}, {__,__,FF,__,__,__,__,FF,__,__}, {__,__,FF,__,__,__,__,FF,__,__},
        {__,__,FF,__,__,__,__,FF,__,__}, {__,__,FF,__,__,__,__,FF,__,__}, {__,__,FF,__,__,__,__,FF,__,__}, {__,__,__,FF,FF,FF,FF,__,__,__}, {__,__,__,__,__,__,__,__,__,__}
    };

    const unsigned char digit9[20][10] = {
        {__,__,__,__,__,__,__,__,__,__}, {__,__,__,FF,FF,FF,FF,__,__,__}, {__,__,FF,__,__,__,__,FF,__,__}, {__,FF,__,__,__,__,__,FF,__,__}, {__,FF,__,__,__,__,__,FF,__,__},
        {__,FF,__,__,__,__,__,FF,__,__}, {__,FF,__,__,__,__,__,FF,__,__}, {__,FF,__,__,__,__,__,FF,__,__}, {__,FF,__,__,__,__,__,FF,__,__}, {__,FF,__,__,__,__,__,FF,__,__},
        {__,__,FF,FF,FF,FF,FF,FF,__,__}, {__,__,__,__,__,__,__,FF,__,__}, {__,__,__,__,__,__,__,FF,__,__}, {__,__,__,__,__,__,__,FF,__,__}, {__,__,__,__,__,__,__,FF,__,__},
        {__,__,__,__,__,__,__,FF,__,__}, {__,__,__,__,__,__,__,FF,__,__}, {__,__,FF,__,__,__,__,FF,__,__}, {__,__,__,FF,FF,FF,FF,__,__,__}, {__,__,__,__,__,__,__,__,__,__}
    };
    
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

        //image(location).copyTo(digit);
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