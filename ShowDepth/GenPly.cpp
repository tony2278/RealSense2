// C++ ��׼��
#include <iostream>
#include <string>
#include <io.h>
#include <vector>
using namespace std;

// OpenCV ��
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

// PCL ��
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>

// �����������
typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloud;

// ����ڲ�
const double camera_factor = 1000;
const double camera_cx = 633.776;
const double camera_cy = 346.241;
const double camera_fx = 918.431;
const double camera_fy = 915.632;

void getFiles(std::string path, std::vector<std::string>& files)
{
	intptr_t   hFile = 0;//intptr_t��uintptr_t������:typedef long int�� typedef unsigned long int
	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1)//assign�������Ƚ�ԭ�ַ�����գ�Ȼ�����µ�ֵ���滻��
	{
		do
		{
			if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
			{
				files.push_back(p.assign(path).append("/").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

// ������ 
int main(int argc, char** argv)
{
	vector <string> files1;
	vector <string> files2;
	//��Ҫ��ȡ���ļ���·����ʹ�õ���б�ܡ�/��
	string depth_path = "depth1.png";
	string color_path = "color1.png";
	
	// ͼ�����
	cv::Mat rgb, depth;
	// ʹ��cv::imread()����ȡͼ��
	// rgb ͼ����8UC3�Ĳ�ɫͼ��
	// depth ��16UC1�ĵ�ͨ��ͼ��ע��flags����-1,��ʾ��ȡԭʼ���ݲ����κ��޸�
	rgb = cv::imread(color_path);
	depth = cv::imread(depth_path, -1);

	// ���Ʊ���
	// ʹ������ָ�룬����һ���յ��ơ�����ָ��������Զ��ͷš�
	PointCloud::Ptr cloud(new PointCloud);
	// �������ͼ
	for (int m = 0; m < depth.rows; m++)
		for (int n = 0; n < depth.cols; n++)
		{
			// ��ȡ���ͼ��(m,n)����ֵ
			ushort d = depth.ptr<ushort>(m)[n];
			// d ����û��ֵ������ˣ������˵�
			if (d == 0)
				continue;
			// d ����ֵ�������������һ����
			PointT p;

			// ���������Ŀռ�����
			p.z = double(d) / camera_factor;
			p.x = (n - camera_cx) * p.z / camera_fx;
			p.y = (m - camera_cy) * p.z / camera_fy;

			// ��rgbͼ���л�ȡ������ɫ
			// rgb����ͨ����BGR��ʽͼ�����԰������˳���ȡ��ɫ
			p.b = rgb.ptr<uchar>(m)[n * 3];
			p.g = rgb.ptr<uchar>(m)[n * 3 + 1];
			p.r = rgb.ptr<uchar>(m)[n * 3 + 2];

			// ��p���뵽������
			cloud->points.push_back(p);
		}
	int size = cloud->points.size();
	// ���ò��������
	cloud->height = 1;
	cloud->width = cloud->points.size();
	cloud->is_dense = false;
	string name = "pointcloud1";

	pcl::io::savePLYFile(name + ".ply", *cloud);   //���������ݱ���Ϊply�ļ�
	//pcl::io::savePCDFile(name + ".pcd", *cloud);   //���������ݱ���Ϊpcd�ļ�
	// ������ݲ��˳�
	cloud->points.clear();
	cout << "point cloud size = " << size << endl;
	cout << "End" << endl;

	return 0;
}

