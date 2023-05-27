// 一段简单的测试代码
#include <opencv2/opencv.hpp>
int main() {
  cv::Mat img = cv::imread("D:\\PlateDetect\\比赛测试\\车牌\\新能源车牌\\1.jpg"); //改成你自己的图片路径
  cv::imshow("plate", img);
  cv::waitKey(0);
}
