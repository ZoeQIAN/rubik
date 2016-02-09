#ifndef TEXTURE_H
 #define TEXTURE_H

 struct Image
 {
     unsigned char* pixels;
     int width;
     int height;
     int numChannels;
 };

 class Texture
 {
     public:
     Texture ();
     void createTexture (int texN);

     void readImage (char *fn);

     GLuint texName;
     Image image;
 };

 #endif
 
