// image3.cpp

#include "image3.hpp"
#include <iostream>
#include <fstream>
#include <stdint.h> // for uint8_t
#include <stdlib.h>
#include <stdio.h>
using namespace std;
Image::Image()
{
	cols = 0;
	rows = 0;
	pixels = NULL;//
}

 Image::~Image()
 {
 	if (pixels != NULL){
 		for (int i = 0; i < rows; i++) {
		    delete[] pixels[i]; // delete sub array
		}
		delete [] pixels;
 	}
 }

 int Image::resize( unsigned int width,  unsigned int height, uint8_t fillcolor ){
	int i,j; 
 	if (pixels != NULL){
 		for (i = 0; i < rows; i++) {
 		    delete[] pixels[i]; // delete sub array
		}
		delete [] pixels;
 	}
 	pixels= new uint8_t*[height];
	for(int i = 0; i < height; i++){
	    pixels[i] = new uint8_t[width];
	} 	
 	if (pixels == NULL){
 		return 1;
 	}
 	cols = width ;
 	rows = height ;
 	
 	for (i = 0 ; i < rows ; i++){
 		for(j = 0 ; j < cols ; j++){
 			pixels[i][j] = fillcolor;
 		}
 	}
 	
 	return 0;
 }  

 int Image::set_pixel( unsigned int x, unsigned int y, uint8_t color ){
 	if (x >= cols || y >= rows ){
 		return 1;
 	}
 	pixels[y][x] = color;
 	//pixels[y*cols+x] = color;
 	return 0;
 }
  

 int Image::get_pixel( unsigned int x, unsigned int y, uint8_t* colorp ){
 	if (x >= cols || y >= rows ){
 		return 1;
 	}
 	if (colorp == NULL || pixels == NULL)
 	{
 		return 1;
 	}
 	*colorp = pixels[y][x];
 	return 0;
 }
 int Image::save( const char* filename ){
 	if (filename == NULL){
 		return 1;
 	}
 	fstream fp;
	fp.open(filename, fstream::out); /* Read-write. */
 	//FILE *fp = fopen(filename,"w");
 	if (!fp.is_open()){
 		cout << "Error Opening File for saving." << endl;
 		return 1;
 	}
 	if ((rows == 0 && cols > 0) || (rows > 0 && cols == 0)){
		cout << "Error pixels for saving." << endl;
		return 1;
	}
 	if (cols == 0 && rows == 0){		
 		fp.close();
 		cout << "Saving empty File." << endl;
 		return 0;
 	}
 	//cout << "0" <<endl;
 	int i,j;
 	for (i=0;i<rows;i++){
 		j=0;
 		for(j=0;j<cols;j++){
 			fp<<(int)pixels[i][j]<<" ";
 		}
 		fp<<endl;
 	}
 	
    fp.close();
 	return 0; 	 	
}
 int Image::load( const char* filename ){
 	if (filename == NULL){
 		cout << "Error filename for loading"<<endl;
		return 1;
	}
	cout << "1" << endl;
	fstream fp;
	fp.open(filename,ios::in);
	if(!fp.is_open()){
		cout << "Error opening file for loading"<<endl;
		return 1;
	}
	fp.seekg (0, fp.end);
    int length = fp.tellg();
    fp.seekg (0, fp.beg);
    cout << "2" << endl;
    if (length == 0) {
 		cols = 0;
 		rows = 0;
 		pixels = NULL;
 		fp.close();
 		cout << "Loading Empty File@." << endl;
    	return 0;
 	}
	cout << "3" << endl;
	int pix;
	int i,j,total_num=0,cline=0,ccol;
	char line[1500];
	while (!fp.eof()){
		fp >> pix;
		total_num++;
	}
	total_num = total_num -1;	
	fp.clear();
	fp.seekg (0, fp.beg);
	
	cout << "4" << endl;
	while (!fp.eof()){
		fp.getline(line,1500,'\n');
		cline ++;
	}
	cline = cline - 1;	
	fp.clear();
	fp.seekg (0, fp.beg);
	if (cline == 0){
		ccol = 0;
		cols = ccol;
		rows = 0;
		if (pixels != NULL){
 			for (int i = 0; i < rows; i++) {
		  	  delete[] pixels[i]; // delete sub array
			}
			delete [] pixels;
			pixels = NULL;	
 		}
		cout << "loading empty image successful@."<<endl;
		fp.close();
		return 0;
	}
	else{
		ccol = total_num/cline;
		cols = ccol;
		rows = cline;	
	}
	cout << "loading rows: "<< rows << endl; 
	cout << " cols: " << cols <<endl;		
	if (pixels != NULL){
 			for (int i = 0; i < rows; i++) {
		  	  delete[] pixels[i]; // delete sub array
			}
			delete [] pixels;
 	}		
	cout << "6" << endl;
	pixels = new uint8_t*[rows];  	                                     //create new pixels
	for(i = 0; i < rows; ++i){
	    pixels[i] = new uint8_t[cols];
	} 		
	for (i=0;i<rows;i++){
 		for(j=0;j<cols;j++){
 			fp >> pix;
 			pixels[i][j] = pix;
 		}
 	}
	cout << "7" << endl;
	fp.close();
	cout << "Finish loading image."<<endl;
	return 0;
 }