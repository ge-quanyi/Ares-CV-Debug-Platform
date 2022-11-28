//
// Created by quonone on 22-11-23.
//
#include "camera.h"
#include <umt/umt.hpp>
#include <pybind11/pybind11.h>


void show_img(){
    Camera cam(0,960,768,0.25);
    cam.init();
    cv::Mat frame;
    while(true){
        cam.update(frame);
    }
}



namespace py = pybind11;

PYBIND11_MODULE(webvideo, m) {
    m.doc() = "streaming video to web";
    m.def("show_img", &show_img, "a function showing image");
}

