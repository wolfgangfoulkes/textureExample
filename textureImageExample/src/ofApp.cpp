#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	


	w = 250;
	h = 200;
	
	
	texGray.allocate(w,h,GL_LUMINANCE);
	texColor.allocate(w,h,GL_RGB);
	texColorAlpha.allocate(w,h,GL_RGBA);
    
    ofLoadImage(inImage, "pixelkid.jpg"); //people talk about the redundancy of ofImage. should just use ofPixels.
    outImage = inImage;
    outImage.resize(w, h); //can do this with pixels as well.
    outImage.setImageType(OF_IMAGE_COLOR_ALPHA);
    cout << "inImage.getImageType():" << inImage.getImageType() << "\n"; //returns "type 1" meaning without alpha
    cout << "outImage.getImageType():" << outImage.getImageType() << "\n"; //returns "type 2" meaning there's alpha
    cout << "outImage.getHeight" << outImage.getHeight() << "\n";
    cout << "outImage.getWidth" << outImage.getWidth() << "\n";


    /*
    switch (outImage.type)
    {
        case 0:
        case 1:
        case 2:
    }
     */
    
	
	grayPixels			= new unsigned char [w*h];
	colorPixels 		= new unsigned char [w*h*3];
	colorAlphaPixels	= new unsigned char [w*h*4];
    outImagePixels      = outImage.getPixels();
    //getPixelsRef is safer, because it returns an ofPixels object. this could be RGB or RGBA, meaning different sizes.
    
    
    for (int i = 0; i < h; i++) //actual height is h * bpp
    {
        for (int ii = 0; ii < w; ii++)
        {
            int index = (ii + (i * w)) * 4;
            unsigned char r = outImagePixels[index + 0]; //0 * 4 + 0
            unsigned char g = outImagePixels[index + 1]; //0 * 4 + 1
            unsigned char b = outImagePixels[index + 2]; //0 * 4 + 2
            unsigned char a = outImagePixels[index + 3]; //0 * 4 + 2;
            //if (b >= 255/2) { outImagePixels[index + 3] = 0; }
            if (b > r && b > g) { outImagePixels[index + 3] = 0; }
            
            cout << r << "," << g << "," << b << "," << a << "\n" ;
        }
    }

	// gray pixels, set them randomly
	for (int i = 0; i < w*h; i++){
		grayPixels[i] = (unsigned char)(ofRandomuf() * 255);
		
	}
	
	// color pixels, use w and h to control red and green
	for (int i = 0; i < w; i++){
		for (int j = 0; j < h; j++){
			colorPixels[(j*w+i)*3 + 0] = i;	// r
			colorPixels[(j*w+i)*3 + 1] = j;	// g
			colorPixels[(j*w+i)*3 + 2] = 0; // b
		}
	}
	
	// color alpha pixels, use w and h to control red and green
	for (int i = 0; i < w; i++){
		for (int j = 0; j < h; j++){
			colorAlphaPixels[(j*w+i)*4 + 0] = 255;	// r
			colorAlphaPixels[(j*w+i)*4 + 1] = 133;	// g
			colorAlphaPixels[(j*w+i)*4 + 2] = 200; 	// b
			colorAlphaPixels[(j*w+i)*4 + 3] = i; 	// alpha
		}
	}
	
	texGray.loadData(grayPixels, w,h, GL_LUMINANCE); 
	texColor.loadData(colorPixels, w,h, GL_RGB);
	texColorAlpha.loadData(colorAlphaPixels, w,h, GL_RGBA);
    texOutImage.loadData(outImagePixels, w, h, GL_RGBA);
}
 

//--------------------------------------------------------------
void ofApp::update(){
	
	ofBackground(255,255,255);
	
	for (int i = 0; i < w; i++){
		for (int j = 0; j < h; j++){
			grayPixels[j*w+i] = (unsigned char)(ofRandomuf() * 255);
		}
	}
	texGray.loadData(grayPixels, w,h, GL_LUMINANCE); 
	
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetHexColor(0xffffff);
	
	texGray.draw(100,100,w,h);
	texColor.draw(350,300,w,h);
	
	// 	blending had to be enabled 
	// 	for transparency to work:
	
	ofEnableAlphaBlending();
	texColorAlpha.draw(250,200,w,h);
    texOutImage.draw(450, 400,w,h);
	ofDisableAlphaBlending();

}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
	// when the mouse moves, we change the color image:
	float pct = (float)x / (float)ofGetWidth();
	for (int i = 0; i < w; i++){
		for (int j = 0; j < h; j++){
			colorPixels[(j*w+i)*3 + 0] = i;	// r
			colorPixels[(j*w+i)*3 + 1] = j;	// g
			colorPixels[(j*w+i)*3 + 2] = (unsigned char)(pct*255); // b
		}
	}
	// finally, load those pixels into the texture
	texColor.loadData(colorPixels, w,h, GL_RGB);
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}