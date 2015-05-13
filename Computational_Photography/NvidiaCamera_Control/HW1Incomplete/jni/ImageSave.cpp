//----------------------------------------------------------------------------------
//
// Copyright (c) 2014, NVIDIA CORPORATION. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//
//----------------------------------------------------------------------------------

#include "ImageSave.h"

#include <fstream>

const std::string ImageSave::OUTPUT_DIR = "/mnt/sdcard/pictures";

void ImageSave::writePGM( nv::camera2::CameraBuffer &img,
        const std::string& filename )
{

    if ( img.format() == nv::camera2::YCbCr_420_888 )
    {
        std::string filenameY = OUTPUT_DIR + "/" + filename + "-Y.pgm";
        std::string filenameU = OUTPUT_DIR + "/" + filename + "-U.pgm";
        std::string filenameV = OUTPUT_DIR + "/" + filename + "-V.pgm";

        std::ofstream outfile( filenameY, std::ofstream::binary );

        nv::camera2::CameraBuffer::Data imgPlane;

        imgPlane = img.data(0);
        outfile << "P5 " << imgPlane.stride << " ";
        outfile << imgPlane.height << " " << 255 << std::endl;
        outfile.write( (char* ) imgPlane.ptr,
                imgPlane.stride * imgPlane.height );

        outfile.close();
        outfile.open( filenameU, std::ofstream::binary );

        imgPlane = img.data(1);
        outfile << "P5 " << imgPlane.stride << " ";
        outfile << imgPlane.height << " " << 255 << std::endl;
        outfile.write( (char* ) imgPlane.ptr,
                imgPlane.stride * imgPlane.height );

        outfile.close();
        outfile.open( filenameV, std::ofstream::binary );

        imgPlane = img.data(2);
        outfile << "P5 " << imgPlane.stride << " ";
        outfile << imgPlane.height << " " << 255 << std::endl;
        outfile.write( (char* ) imgPlane.ptr,
                imgPlane.stride * imgPlane.height );
        outfile.close();
    }
    else if( img.format() == nv::camera2::RAW16 )
    {
        std::string filepath = OUTPUT_DIR + "/" + filename + ".pgm";
        std::ofstream outfile( filepath, std::ofstream::binary );

        nv::camera2::CameraBuffer::Data imgPlane;

        imgPlane = img.data(0);
        outfile << "P5 " << imgPlane.stride << " ";
        outfile << imgPlane.height << " " << 16384 << std::endl;
        outfile.write( (char* ) imgPlane.ptr,
                imgPlane.stride * imgPlane.height * 2 );

        outfile.close();

    }
}

void ImageSave::writeJPG( nv::camera2::CameraBuffer &img,
        const std::string& filename )
{

    if ( img.format() == nv::camera2::JPEG )
    {
        std::string filepath = OUTPUT_DIR + "/" + filename + ".jpg";
        std::ofstream outfile( filepath, std::ofstream::binary );

        nv::camera2::CameraBuffer::Data imgPlane;
        imgPlane = img.data(0);
        outfile.write( (char* ) imgPlane.ptr,
                imgPlane.stride  );
    }
}

void ImageSave::writeRAW( nv::camera2::CameraBuffer &img,
        const std::string& filename )
{
    if ( img.format() == nv::camera2::RAW16 )
    {
        std::string filepath = OUTPUT_DIR + "/" + filename + ".raw";
        std::ofstream outfile( filepath, std::ofstream::binary );

        nv::camera2::CameraBuffer::Data imgPlane;
        imgPlane = img.data(0);
        outfile.write( (char* ) imgPlane.ptr,
                imgPlane.stride * imgPlane.height * 2 );
    }
}

