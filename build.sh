g++ detect_road.cpp -o detect_road -I/usr/local/include/opencv -I/usr/local/include/opencv2 -L/usr/local/lib/ -g -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_stitching -lopencv_imgcodecs -lopencv_videoio `pkg-config opencv --cflags --libs`
./detect_road
rm detect_road