//
// Created by quonone on 22-11-28.
//
#include <umt/umt.hpp>
#include "camera.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <pybind11/numpy.h>

void Publisher_A(){ //auto aim run

    umt::Publisher<cv::Mat> pub("debug_img");
    Camera cam(0,640,480,0.25);
    cam.init();
    cv::Mat frame;
    while (true){
        cam.update(frame);
        pub.push(frame);
        //std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
/**
 *
 * no use
 */
//void Subscriber(){
//    umt::Subscriber<cv::Mat> sub("debug_img", 1);
//
//    cv::Mat img;
//    while(true){
//        try {
//            img = sub.pop();
//            std::cout<< " [info] img size : "<< img.rows <<std::endl;
//        } catch(...) {
//            std::cout << "[WARNING] pub_A not ready." << std::endl;
//            std::this_thread::sleep_for(std::chrono::milliseconds(200));
//        }
//    }
//}

void background_task_run(){
    std::thread(Publisher_A).detach();
}

namespace py = pybind11;
py::array_t<uint8_t> cvMat2npArray(const cv::Mat &mat) {
    py::array_t<uint8_t> array({mat.rows, mat.cols, mat.channels()});
    cv::Mat ref_mat(mat.rows, mat.cols, CV_8UC(mat.channels()), array.mutable_data());
    mat.copyTo(ref_mat);
    return array;
}

// numpy.ndarray --> cv::Mat
cv::Mat npArray2cvMat(const py::array_t<uint8_t> &array) {
    cv::Mat mat;
    return mat;
}

UMT_EXPORT_MESSAGE_ALIAS(cvMat, cv::Mat, c) {

    c.def(py::init<cv::Mat>());
    c.def(py::init(&npArray2cvMat));
    c.def("get_nparray", cvMat2npArray);
}

PYBIND11_EMBEDDED_MODULE(Autoaim, m){
    namespace py = pybind11;
    m.def("background_task_run", background_task_run);
}