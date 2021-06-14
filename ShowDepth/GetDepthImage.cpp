#define _CRT_SECURE_NO_WARNINGS  

#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>

int main()
{
	rs2::pipeline pipe;
	rs2::config cfg;
	//cfg.enable_stream(RS2_STREAM_DEPTH, 640, 360, RS2_FORMAT_Z16, 30); //RS2_STREAM_DEPTH  RS2_STREAM_COLOR
	//pipe.start(cfg);
	pipe.start();

	rs2::colorizer color_map;
	rs2::align align(rs2_stream::RS2_STREAM_COLOR);

	rs2::frameset frames, aligned_frames;
	for (int i = 0; i < 30; i++) {
		frames = pipe.wait_for_frames();
	}

	aligned_frames = align.process(frames);
	rs2::frame depth_frame = aligned_frames.get_depth_frame().apply_filter(color_map); //frames
	rs2::frame color_frame = aligned_frames.get_color_frame(); //frames
	
	// Get the depth frame's dimensions
	//float width = depth_frame.get_width();
	//float height = depth_frame.get_height();
	cv::Mat depth(cv::Size(1280, 720), CV_8UC3, (void *)depth_frame.get_data(), cv::Mat::AUTO_STEP);
	cv::Mat color(cv::Size(1280, 720), CV_8UC3, (void *)color_frame.get_data(), cv::Mat::AUTO_STEP);

	cv::namedWindow("Depth Image", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Color Image", cv::WINDOW_AUTOSIZE);
	cv::imshow("Depth Image", depth);
	cv::imshow("Color Image", color);
	cv::waitKey(0);

	return 0;
}