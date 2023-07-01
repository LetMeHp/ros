#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <nav_msgs/Odometry.h>

int main(int argc, char **argv) {
	// ��ʼ�� ROS �ڵ�
	ros::init(argc, argv, "bag_odometry_reader");
	ros::NodeHandle nh;

	// �� ROSBAG �ļ�
	rosbag::Bag bag;
	bag.open("your_bag_file.bag", rosbag::bagmode::Read);

	// ����һ�� View�����ڻ�ȡָ���������Ϣ
	rosbag::View view(bag, rosbag::TopicQuery("/odom_topic"));

	// ���� ROSBAG �е���Ϣ

	for (const rosbag::MessageInstance &msg : view) {
		// �����Ϣ�����Ƿ�Ϊ Odometry ��Ϣ
		if (msg.isType<nav_msgs::Odometry>()) {
			// ����Ϣת��Ϊ Odometry ��Ϣ����
			nav_msgs::Odometry::ConstPtr odom_msg = msg.instantiate<nav_msgs::Odometry>();

			// ���������д�ӡ Odometry ����
			std::cout << "Timestamp: " << odom_msg->header.stamp << std::endl;
			std::cout << "Position (x, y, z): " << odom_msg->pose.pose.position.x << ", "
			          << odom_msg->pose.pose.position.y << ", " << odom_msg->pose.pose.position.z << std::endl;
			std::cout << "Orientation (x, y, z, w): " << odom_msg->pose.pose.orientation.x << ", "
			          << odom_msg->pose.pose.orientation.y << ", " << odom_msg->pose.pose.orientation.z << ", "
			          << odom_msg->pose.pose.orientation.w << std::endl;
			std::cout << "Linear Velocity (x, y, z): " << odom_msg->twist.twist.linear.x << ", "
			          << odom_msg->twist.twist.linear.y << ", " << odom_msg->twist.twist.linear.z << std::endl;
			std::cout << "Angular Velocity (x, y, z): " << odom_msg->twist.twist.angular.x << ", "
			          << odom_msg->twist.twist.angular.y << ", " << odom_msg->twist.twist.angular.z << std::endl;
			std::cout << "----------------------------------" << std::endl;
		}
	}

	// �ر� ROSBAG �ļ�
	bag.close();

	return 0;
}