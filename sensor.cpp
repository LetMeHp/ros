#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>

int main(int argc, char **argv) {
	// ��ʼ��ROS�ڵ�
	ros::init(argc, argv, "laser_scan_display");
	ros::NodeHandle nh;

	// ����ROSbag���󲢴��ļ�
	rosbag::Bag bag;
	bag.open("/home/robot/all.bag", rosbag::bagmode::Read);

	// ������Ҫ��ȡ�Ļ���

	std::vector<std::string> topics = {"/scan"};

	// ����ROSbag��ͼ���󣬲����û��������
	rosbag::View view(bag, rosbag::TopicQuery(topics));

	// ����PCL���ӻ�����
	pcl::visualization::PCLVisualizer viewer("Laser Scan");

	// ����ROSbag�е���Ϣ
	for (const rosbag::MessageInstance &msg : view) {
		// �����Ϣ�����Ƿ�ΪPointCloud2
		if (msg.getDataType() == "sensor_msgs/PointCloud2") {
			sensor_msgs::PointCloud2::ConstPtr cloud_msg = msg.instantiate<sensor_msgs::PointCloud2>();

			// ����PCL���ƶ��󲢴�ROS��Ϣ���������
			pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
			pcl::fromROSMsg(*cloud_msg, *cloud);

			// ��PCL���ӻ���������ӵ�������
			viewer.addPointCloud(cloud, "cloud");

			// ����PCL���ӻ�����
			viewer.spinOnce();
		}
	}

	// �ر�ROSbag�ļ�
	bag.close();

	// ��ʾ���Ʋ����ִ��ڴ�
	viewer.spin();

	return 0;
}