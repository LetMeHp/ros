#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/Image.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char **argv) {
	// ��ʼ��ROS�ڵ�
	ros::init(argc, argv, "camera_info_display");
	ros::NodeHandle nh;

	// ����ROSbag���󲢴��ļ�
	rosbag::Bag bag;
	bag.open("/home/robot/all.bag", rosbag::bagmode::Read);

	// ������Ҫ��ȡ�Ļ���

	std::vector<std::string> topics = {"/camera/color/camera_info", "/camera/color/image_raw"};

	// ����ROSbag��ͼ���󣬲����û��������
	rosbag::View view(bag, rosbag::TopicQuery(topics));

	// ����OpenCV����
	cv::namedWindow("Camera Image");

	// ����ROSbag�е���Ϣ
	for (const rosbag::MessageInstance &msg : view) {
		// �����Ϣ�����Ƿ�ΪCameraInfo
		if (msg.getDataType() == "sensor_msgs/CameraInfo") {
			sensor_msgs::CameraInfo::ConstPtr camera_info = msg.instantiate<sensor_msgs::CameraInfo>();

			// ������������ʾCameraInfo��Ϣ
			ROS_INFO_STREAM("CameraInfo: " << *camera_info);
		}
		// �����Ϣ�����Ƿ�Ϊͼ������
		else if (msg.getDataType() == "sensor_msgs/Image") {
			sensor_msgs::Image::ConstPtr image = msg.instantiate<sensor_msgs::Image>();

			// ��ͼ������ת��ΪOpenCV��ʽ
			cv_bridge::CvImagePtr cv_image;
			try {
				cv_image = cv_bridge::toCvCopy(image, image->encoding);
			} catch (cv_bridge::Exception &e) {
				ROS_ERROR("cv_bridge exception: %s", e.what());
				continue;
			}

			// ��ʾͼ��
			cv::imshow("Camera Image", cv_image->image);

			// �ȴ��û�����ESC���˳�
			if (cv::waitKey(1) == 27)
				break;
		}
	}

	// �ر�ROSbag�ļ�
	bag.close();

	return 0;
}