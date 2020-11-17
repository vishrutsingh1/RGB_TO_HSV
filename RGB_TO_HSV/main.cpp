#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>


using namespace std;
using namespace cv;




/*Mat convertBGRtoGray(Mat image){
    cout << "hello"<<endl;
    Mat channels[3];
    Mat outputImage =Mat::zeros(Size(image.size()),CV_8UC1);
    split(image,channels);
    outputImage = channels[0] * 0.114 +channels[1] * 0.587 + channels[2] * 0.299;


    return outputImage;
}*/






Mat BGR_HSV(Mat convt_image)
{
int width = convt_image.size().width;
int height = convt_image.size().height;
float scaling_factor = 1/255.0;
float shift = 0;
convt_image.convertTo(convt_image,CV_32F,scaling_factor);

Mat hue = Mat::zeros(convt_image.size(),CV_32F);
Mat sat = Mat::zeros(convt_image.size(),CV_32F);
Mat val = Mat::zeros(convt_image.size(),CV_32F);

Vec3f pixels;
Mat new_image;
float cmax,cmin , delta,r,g,b;
for(int i = 0; i < height ; i++)
{
for(int j = 0; j < width; j++)
{
pixels =  convt_image.at<Vec3f>(i,j);
cmax = std::max(pixels[0],std::max(pixels[1],pixels[2]));
cmin = std::min(pixels[0],std::min(pixels[1],pixels[2]));
delta = cmax - cmin;

r = pixels[2];
g = pixels[1];
b = pixels[0];


val.at<float>(i,j) = cmax;



if (cmax == 0)
{
sat.at<float>(i,j) = 0;
}
else
sat.at<float>(i,j) = delta / cmax;


if (cmax == r)
{
hue.at<float>(i,j) = 60*(g-b)/(delta);


}
else if (delta == 0)
{

hue.at<float>(i,j) == 0.0;

}

else if (cmax == g)
{
hue.at<float>(i,j) = 120+ 60*(b-r)/(delta);

}


else if (cmax == b)
{
hue.at<float>(i,j) = 240 +60*(r-g)/(delta);

}



if (hue.at<float>(i,j) < 0)
{
 hue.at<float>(i,j)  = (int)(360 + hue.at<float>(i,j));



}



}



}
hue  = hue /2;
sat = sat *255.0;
val = val * 255.0;

Mat channels[] = {hue,sat,val};
merge(channels,3,new_image);
new_image.convertTo(new_image,CV_8UC3);


return new_image;


}





int main()
{

Mat image = imread("images/girl.jpg");
Mat hsv;
cvtColor(image,hsv,COLOR_BGR2HSV);

Mat x = BGR_HSV(image);
Mat hsvdiff;
absdiff(hsv,x,hsvdiff);








namedWindow("new_hsv_image",WINDOW_AUTOSIZE);
namedWindow("hsv_image",WINDOW_AUTOSIZE);
namedWindow("image_diff",WINDOW_AUTOSIZE);

imshow("new_hsv_image",x);
imshow("image_diff",hsvdiff);
imshow("hsv_image",hsv);



waitKey(0);

destroyAllWindows();




}
