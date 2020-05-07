﻿#include "EdgeDetector.h"
#include <string>
#include <string.h>

int main(int argc, char* argv[])
{
#pragma region ONLY_FOR_DEBUG
	/*argc = 5;
	char* temp[5];
	temp[0] = _strdup("1712842_1712698_BT02.exe");
	temp[1] = _strdup("Lena.png");
	temp[2] = _strdup("--sobel");
	temp[3] = _strdup("80");
	temp[4] = _strdup("60");
	argv = temp;*/
#pragma endregion

	char* command, * inputPath, * cmdArguments;

	try
	{
		inputPath = argv[1];
		command = argv[2];
		

		// khởi tạo mặc định 
		int isSuccess = 0;
		Mat srcImg = imread(inputPath, IMREAD_COLOR);
		Mat dstImg;

		
		/*-----------------------------------------------*/

		EdgeDetector EdgeD;
		
		if (strcmp(command, "--sobel") == 0)
		{
			//kWidth = 3, kHeight = 3
			isSuccess = EdgeD.DetectBySobel(srcImg, dstImg, 3, 3);
			
		}
		else if (strcmp(command, "--prewitt") == 0)
		{
			isSuccess = EdgeD.DetectByPrewitt(srcImg, dstImg, 3, 3);
		}
		else if (strcmp(command, "--laplace") == 0)
		{
			isSuccess = EdgeD.DetectByLaplace(srcImg, dstImg, 3, 3);
		}
		else if (strcmp(command, "--canny") == 0)
		{
			int low, hight;
			low = atoi(argv[3]);
			hight = atoi(argv[4]);
			EdgeD.setThreshold(low, hight);
			isSuccess = EdgeD.DetectByCanny(srcImg, dstImg);

			GaussianBlur(srcImg, srcImg, Size(5, 5), 0);
			Mat _Canny;
			Canny(srcImg, _Canny, low, hight, 3);
			imshow("Canny OpenCV", _Canny);

		}

		//in kết quả
		if (isSuccess)
		{
			imshow("Source Image", srcImg);
			imshow("Destination Image", dstImg);
			
			waitKey(0);

		}
		else
		{
			throw "Error:..........";
		}
		//----------------------------------
	}
	catch (const char* msg)
	{
		cout << msg << endl;
		system("pause");
	}


#pragma region ONLY_FOR_DEBUG
	/*free(temp[0]);
	free(temp[1]);
	free(temp[2]);
	free(temp[3]);
	free(temp[4]);*/
#pragma endregion

	//system("pause");
	return 0;
}