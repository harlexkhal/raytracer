/* MIT License
Copyright (c) 2018 Biro Eniko
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include "util/ray.h"
#include "util/util.h"
#include "util/randomGenerator.h"

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// fov - field of view
// image is not square => fow is different horizontally and vertically

class Camera
{
    public:
        vec3 origin;
        vec3 lowerLeftCorner;
        vec3 horizontal;
        vec3 vertical;
        vec3 u, v, w;
        float lensRadius;

        vec3 lookFrom;
        vec3 lookAt;

        vec3 vup;
        float vfov;
        float aspect;
        float aperture;
        float focusDist;

        float halfWidth;
	    float halfHeight;

        Camera():   lowerLeftCorner(vec3(-2.0f, -1.0f, -1.0f)), 
                    horizontal(vec3(4.0f, 0.0f, 0.0f)),
                    vertical(vec3(0.0f, 2.0f, 0.0f)),
                    origin(vec3(0.0f, 0.0f, 0.0f)) {};
        
        // vfov is top to bottom in degrees
        Camera(vec3 lookFrom, vec3 lookAt, vec3 vup, float vfov, float aspect);

        // another constructor
        Camera(vec3 lookFrom, vec3 lookAt, vec3 vup, float vfov, float aspect, float focusDist, float aperture = 0.0f);

        void update();

        // Spherical coordinate system implementation - rotate the lookFrom location by theta polar angle and phi azimuth angle - keeping the distance 
        void rotate(float theta, float phi);

        void zoom(float zoomScale);

        void translate(CameraMovement direction, float stepScale);

        ray getRay(RandomGenerator& rng, float s, float t);
};
