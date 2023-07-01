#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <sensor_msgs/Imu.h>

int main(int argc, char **argv) {
	// ��ʼ�� ROS �ڵ�
	ros::init(argc, argv, "bag_imu_reader");
	ros::NodeHandle nh;

	// �� ROSBAG �ļ�
	rosbag::Bag bag;
	bag.open("your_bag_file.bag", rosbag::bagmode::Read);  //�޸�bag��ַ

	// ����һ�� View�����ڻ�ȡָ���������Ϣ
	rosbag::View view(bag, rosbag::TopicQuery("/imu_topic"));  //���ĵĻ�������

	// ���� ROSBAG �е���Ϣ

	for (const rosbag::MessageInstance &msg : view) {
		// �����Ϣ�����Ƿ�Ϊ IMU ��Ϣ
		if (msg.isType<sensor_msgs::Imu>()) {
			// ����Ϣת��Ϊ IMU ��Ϣ����
			sensor_msgs::Imu::ConstPtr imu_msg = msg.instantiate<sensor_msgs::Imu>();

			// ���������д�ӡ IMU ����
			std::cout << "Timestamp: " << imu_msg->header.stamp << std::endl;
			std::cout << "Angular Velocity (x, y, z): " << imu_msg->angular_velocity.x << ", "
			          << imu_msg->angular_velocity.y << ", " << imu_msg->angular_velocity.z << std::endl;
			std::cout << "Linear Acceleration (x, y, z): " << imu_msg->linear_acceleration.x << ", "
			          << imu_msg->linear_acceleration.y << ", " << imu_msg->linear_acceleration.z << std::endl;
			std::cout << "Orientation (x, y, z, w): " << imu_msg->orientation.x << ", "
			          << imu_msg->orientation.y << ", " << imu_msg->orientation.z << ", "
			          << imu_msg->orientation.w << std::endl;
			std::cout << "----------------------------------" << std::endl;
		}
	}

	// �ر� ROSBAG �ļ�
	bag.close();

	return 0;
}