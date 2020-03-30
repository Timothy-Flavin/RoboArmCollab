/* 
Hey Ferdinand this is the file I was making back in Tulsa to do stuff with images. 
some of the methods are not filled in because I had written the pseudo code but then 
school made me put it on pause lol incomplete project and all

----------------------------READ COMMENTS IN MAIN BEFORE COMMENTS IN INDIVIDUAL FUNCTIONS------------------------
*/

#include<opencv2/opencv.hpp> // you will need to install opencv before this will work 
#include<iostream>
#include <string>
//#include <windows.h> idk why this was included ever but I don't use it lol
#include <random>
#include <ctime>
using namespace std; //for cout convinience as this was not going to be used by anyone else until you
using namespace cv; //also for convinience, if you comment this out and then do cv.-----  wherever the code throws errors you should be good
                    //if you have any questions about namespaces just ask

//this method scrus accross the image and moves each pixel's value closer to the average pixel value in this picture 
//it has the effect of making squares that are blurred and it is shown by the first call in main
Mat scrubImageXThenY(Mat image, int radius) {
	Mat img = image.clone(); //cloned to not mess with the original image in case the user wants it to stay the same
	int scrubBrushSize = (2*radius + 1)*(2*radius + 1);//size of the brush. run it and you will get what I mean
	int moveAmount = (radius)*2; //how much the brush moves between each smudge 
	int changeNum = 2; //higher change num = less blurring. you will see later
	
	
	
	for (int y = radius; y < img.rows - radius; y+=moveAmount)
	{
		imshow("image", img); //I show it once per row, that seemed reasonable 
		waitKey(10);
		for (int x = radius; x < img.cols - radius; x+=moveAmount)
		{
			int red = 0, green = 0, blue = 0;
			// these 2 loops get the total r, g, and b, values within the brush currently in order to find the average 
			// r g and b per pixel of all the pixels in the brush. we will later move each pixel's rgb values closer
			// to the averages in order to lower the contrast of this brush location. if we made them all equal to
			// the average this would make the whole image look like pixel art but the average contrast of the entire 
			// image is also significantly lowered so if I were to make a second method to turn this blurred thing into
			// pixel art or something I would have a part 2 that raises the contrast
			for (int smally = y - radius; smally <= y + radius; smally++) {
				for (int smallx = x - radius; smallx <= x + radius; smallx++) {
					//Vect3v is an open cv datatype that is a vector of 3 bytes, in this case rgb.
					//rather than use ints, this saves space and stuff. the & means to get a pointer to 
					//the vec3b that is in our material using the Mat.at(x,y) to get the pixel at that 
					//location and that pixel in this case is the Vec3b. the reason for the & is so that
					//if we edit the variable 'color' it will edit the value in the img itself too so we
					// don't have to use any kind of set(x,y,color) kinda thing
					Vec3b & color = img.at<Vec3b>(smally, smallx);
					red += color[0];
					green += color[1];
					blue += color[2];
				}
			}

			red /= scrubBrushSize; // devided by number of pixels so that we get the average
			green /= scrubBrushSize;
			blue /= scrubBrushSize;


			//this loop pulls all the pixels colors towards the averages by the difference between this pixel and
			//the average devided by change num. so if you had a change num of 5 it would cut the contrast down for 
			//each brush location by 1/5 and if your changenum was 1 then the entire block would be set to the same
			//color
			for (int smally = y - radius; smally <= y + radius; smally++) {
				for (int smallx = x - radius; smallx <= x + radius; smallx++) {
					Vec3b & color = img.at<Vec3b>(smally, smallx);
					//color[0] = rand() % 256;
					//color[0] = rand() % 256;
					//color[1] = rand() % 256;
					//color[2] = rand() % 256;
					if (color[0] - ((color[0] - red) / changeNum) < 0)
						color[0] = 0;
					else if (color[0] - ((color[0] - red) / changeNum) > 255)
						color[0] = 255;
					else
						color[0] -= (color[0] - red)/2;
					if (color[1] - ((color[1] - green) / changeNum) < 0)
						color[1] = 0;
					else if (color[1] - ((color[1] - green) / changeNum) > 255)
						color[1] = 255;
					else
						color[1] -= (color[1] - green) / changeNum;
					if (color[2] - ((color[2] - blue) / changeNum) < 0)
						color[2] = 0;
					else if (color[2] - ((color[2] - blue) / changeNum) > 255)
						color[2] = 255;
					else
						color[2] -= (color[2] - blue) / changeNum;
					//img.at<Vec3b>(smally, smallx) = color;
				}
			}
			//Vec3b & color = img.at<Vec3b>(y, x);

			// ... do something to the color ....
			//color[0] = rand() % 256;
			//color[1] = rand() % 256;
			//color[2] = rand() % 256;

			// set pixel
			//image.at<Vec3b>(Point(x,y)) = color;
			//if you copy value
		}
	}
	return img;
}

//rather than moving by a defined amount making squares this one moves left and down by a random amount which makes it less like pixelating and
//more just blurry. not practical just fun
Mat scrubImageXThenYRandIncrement(Mat image, int radius) {
	Mat img = image.clone();
	int scrubBrushSize = (2 * radius + 1)*(2 * radius + 1);
	int moveAmount = (radius + 1)*2;
	int changeNum = 3;
	for (int y = radius; y < img.rows - radius; y += rand() % moveAmount)
	{
		imshow("image", img);
		waitKey(10);
		for (int x = radius; x < img.cols - radius; x += rand() % moveAmount)
		{
			int red = 0, green = 0, blue = 0;
			// get pixel
			for (int smally = y - radius; smally <= y + radius; smally++) {
				for (int smallx = x - radius; smallx <= x + radius; smallx++) {
					Vec3b & color = img.at<Vec3b>(smally, smallx);
					red += color[0];
					green += color[1];
					blue += color[2];
				}
			}

			red /= scrubBrushSize;
			green /= scrubBrushSize;
			blue /= scrubBrushSize;

			for (int smally = y - radius; smally <= y + radius; smally++) {
				for (int smallx = x - radius; smallx <= x + radius; smallx++) {
					Vec3b & color = img.at<Vec3b>(smally, smallx);
					//color[0] = rand() % 256;
					//color[0] = rand() % 256;
					//color[1] = rand() % 256;
					//color[2] = rand() % 256;
					if (color[0] - ((color[0] - red) / changeNum) < 0)
						color[0] = 0;
					else if (color[0] - ((color[0] - red) / changeNum) > 255)
						color[0] = 255;
					else
						color[0] -= (color[0] - red) / 2;
					if (color[1] - ((color[1] - green) / changeNum) < 0)
						color[1] = 0;
					else if (color[1] - ((color[1] - green) / changeNum) > 255)
						color[1] = 255;
					else
						color[1] -= (color[1] - green) / changeNum;
					if (color[2] - ((color[2] - blue) / changeNum) < 0)
						color[2] = 0;
					else if (color[2] - ((color[2] - blue) / changeNum) > 255)
						color[2] = 255;
					else
						color[2] -= (color[2] - blue) / changeNum;
					//img.at<Vec3b>(smally, smallx) = color;
				}
			}
			//Vec3b & color = img.at<Vec3b>(y, x);

			// ... do something to the color ....
			//color[0] = rand() % 256;
			//color[1] = rand() % 256;
			//color[2] = rand() % 256;

			// set pixel
			//image.at<Vec3b>(Point(x,y)) = color;
			//if you copy value
		}
	}
	return img;
}


//incomplete, if you want to know what this method was going to do before numerical methdos stopped me from having dun just ask
Mat PicAndSpread(Mat image, int initialX, int initialY, double tolerance) {
	Mat img = image.clone();
	int* states = new int[img.rows*img.cols];
	for (int i = 0; i < img.rows*img.cols; i++) {
		states[i] = 0;
	}
	int* frontier = new int[img.rows*img.cols*2 / 3];
	int frontierLength = 1;
	frontier[0] = initialY * image.cols + initialX;
	int* used = new int[img.rows*img.cols * 2 / 3];
	int usedLength = 0;

	do {

		int iq = 0;
	} while (false);
	//Vec3b & color = img.at<Vec3b>(initialX, initialY);
					//red += color[0];
					//green += color[1];
					//blue += color[2];
			
	return img;
}

Mat scanForLikeColors(Mat img) {
	//take a starting point and add all the points similar in color to one array simArray and add all the ones not similar to another array difArray
	//all the points in SimArray now equal Avg Sim Array
	//totalArray now equals dif array and loop again until diff array is empty 
	//possibly increase difference or look at Hue in hsv
	return img;
}

int main(int argc, char* argv[])
{
	srand(time(NULL)); // this is for random numbers, srand sets the first psuedo random number from a given seed
	                   // and time(NULL) give the number of seconds that have passed since like 1970 or something
	                   // so effectively every time you run the program it won't repeat and stuch
	
	//this was my attempt to get the path of this file because for me it is nested in 
	// a bunch of visual studio workspace shit so I didn't know where the thing was
	// actually running so I could not make relative paths. you can ignore it
	std::string argv_str(argv[0]); 
	std::string base = argv_str.substr(0, argv_str.find_last_of("/"));
	cout << "THIS IS MY PATH BITCHES \n"; //C:\Users\tcfla\source\repos\ImageShader\x64\Debug\ImageShader.exe
	cout << base<<endl;
	cin.get();
	
	
	
	//in opencv Mat is an object type that basically just means an array of values which make up an image
	//pretty sure mine is rgb 0-256 values so it will be a 3d array that is width by height by color 
	// and color has 3 dimensions, r g b. sometimes opencv likes to make the rgb values floats from 
	// [0,1] instead of ints to 256. doesnt really matter lol and there is a function to convert anyway
	Mat image;
	//-------------------------CHANGE THIS PATH TO AN ACTUAL IMAGE \/
	image = imread("C:\\Users\\tcfla\\Desktop\\programs\\TestImage.jpg");// .convertTo(img, CV_32FC3, (1. / 255.)); 

	//img.clone is a deep copy because I wanted a clean copy at all times and if we did Mat img = image; then
	//we would have just made a reference to image so if we fucked with image then it would also have changed
	//img and I did not want that in this case.
	Mat img = image.clone();
	cout << "img empty: " << img.empty();
	
	//this was just to get the user to choose the number of colors, it is currently pointless in the algorithms
	//that are here rn. yet to be implemented lol
	int numColors=3;
	cout << "number of colors: ";
	cin >> numColors;
	
	//scrubImageXThenY(img, 2);
	//img is the image being scrubbed and 30 is the number of pixels to move over after each scrubbing. it will make
	//more sense be reading the method description. 
	img = scrubImageXThenY(img, 30);

	//namedWindow is an opencv method that creates a window with a name in this case 'image' and WINDOW_AUTOSIZE makes
	//the window the same size as the image it is loading by default I think. there is also WINDOW_FULLSCREEN and some others
	namedWindow("image", WINDOW_AUTOSIZE);

	//imshow refreshes the fram with a new Mat object, in this case img. if you want to animate stuff with opencv you do
	//for(int i = 0; i < whatever; i++) imshow("someName",someMatObj); or something along those lines
	imshow("image", img);

	img = scrubImageXThenYRandIncrement(img, 30);
	imshow("image", img);

	//wait Key makes the frame wait a certain number of ms before showing the next imshow command. This is important because 
	//if you have some operation going on that will call imshow before the previous imshow happened then the frame can 
	//get stuck at a grey screen trying to show your images over and over again and it looks like it is broken
	waitKey(1);
	return 0;
}