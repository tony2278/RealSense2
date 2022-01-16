
1 使用realsense 获取对齐的深度图和彩色图。
(pro: rs-align)

获取realsense相机内参
(pro: rs-sensor-control)

Principal Point         : 633.776, 346.241
Focal Length            : 918.431, 915.632
Distortion Model     : Inverse Brown Conrady
Distortion Coefficients : [0,0,0,0,0]

相机的内参矩阵是:
K =  fx     	 s         x0
        0	 fy       y0
        0	 0          1

fx,fy为焦距，一般情况下，二者相等 
x0,y0为主坐标（相对于成像平面） 
s为坐标轴倾斜参数，理想情况下为0
（世界坐标系的原点是左摄像头凸透镜的光心。）

2 ：获取点云

SDL检查： 否



next：Use 点云
to be continue



Reference

1 彩色显示RealSense的深度图像
   https://panqiincs.me/2020/06/19/realsense-depth-image/

2 批量彩色图+深度图转点云文件（ply & pcd）
   https://blog.csdn.net/y18771025420/article/details/110872626

3 VS2017安装PCL1.8.1
   https://www.cnblogs.com/li-yao7758258/p/8066352.html



D:\Program Files\PCL 1.9.1\3rdParty\Boost\include\boost-1_68
D:\Program Files\PCL 1.9.1\3rdParty\Eigen\eigen3
D:\Program Files\PCL 1.9.1\3rdParty\FLANN\include
D:\Program Files\OpenNI2\Include
D:\Program Files\PCL 1.9.1\3rdParty\Qhull\include
D:\Program Files\PCL 1.9.1\3rdParty\VTK\include
D:\Program Files\PCL 1.9.1\include\pcl-1.9


D:\Program Files\PCL 1.9.1\lib
D:\Program Files\PCL 1.9.1\3rdParty\Boost\lib
D:\Program Files\PCL 1.9.1\3rdParty\FLANN\lib
D:\Program Files\OpenNI2\Lib
D:\Program Files\PCL 1.9.1\3rdParty\Qhull\lib
D:\Program Files\PCL 1.9.1\3rdParty\VTK\lib


gd.lib
pcl_common_release.lib
pcl_features_release.lib
pcl_filters_release.lib
pcl_io_ply_release.lib
pcl_io_release.lib


Please don't use this for any production purposes.

Created by Tony2278
