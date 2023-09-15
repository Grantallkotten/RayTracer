#pragma once
#include "Object.h"
#include "ColorDBL.h"
#include "glm/glm.hpp"
#include "Camera.h"
#include "Triangle.h"


class Scene {
private:
    std::vector<Object*> theScene;
    Camera camera;

    // Draw an image and call all corners "pointX", then you can easy creat a room in theScene
    std::vector<glm::vec3> points{
        glm::vec3( 0.0f,  6.0f, 5.0f),   //p0  
        glm::vec3(10.0f,  6.0f, 5.0f),   //p1 
        glm::vec3(13.0f,  0.0f, 5.0f),   //p2  
        glm::vec3(10.0f, -6.0f, 5.0f),   //p3
        glm::vec3( 0.0f, -6.0f, 5.0f),   //p4  
        glm::vec3(-3.0f,  0.0f, 5.0f),   //p5  

        glm::vec3(0.0f,   6.0f, -5.0f),  //p6  
        glm::vec3(10.0f,  6.0f, -5.0f),  //p7  
        glm::vec3(13.0f,  0.0f, -5.0f),  //p8  
        glm::vec3(10.0f, -6.0f, -5.0f),  //p9  
        glm::vec3( 0.0f, -6.0f, -5.0f),  //p10 
        glm::vec3(-3.0f,  0.0f, -5.0f),  //p11 
        };
public:
    const ColorDBL SKYBOXCOLOR = ColorDBL(0.21, 0.32, 0.56);

	Scene( Camera c = Camera(glm::vec3(-1.0f, 0.0f, 0.0f), 800), std::vector<Object*> o = std::vector<Object*>()) : theScene{ o }, camera{c} {
        standardScene();
        camera.castRays(this);
		camera.writePPM();
	};


    void standardScene() {

        // Wall 1
        theScene.push_back(new Triangle(points[1], points[7], points[0], Material(1.0, 0.0, 0.0, ColorDBL(1.0, 0.0, 0.0)) ));
        theScene.push_back(new Triangle(points[0], points[7], points[6], Material(1.0, 0.0, 0.0, ColorDBL(1.0, 0.0, 0.0)) ));
        
        // Wall 2
        theScene.push_back(new Triangle(points[1], points[2], points[7], Material(1.0, 0.0, 0.0, ColorDBL(0.0, 0.8, 0.2)) ));
        theScene.push_back(new Triangle(points[2], points[8], points[7], Material(1.0, 0.0, 0.0, ColorDBL(0.0, 0.8, 0.2)) ));

        // Wall 3
        theScene.push_back(new Triangle(points[2], points[3], points[8], Material(1.0, 0.0, 0.0, ColorDBL(0.0, 0.0, 1.0))));
        theScene.push_back(new Triangle(points[3], points[9], points[8], Material(1.0, 0.0, 0.0, ColorDBL(0.0, 0.0, 1.0))));
        
        // Roof 1
        theScene.push_back(new Triangle(points[1], points[3], points[2], Material(1.0, 0.0, 0.0, ColorDBL(0.1, 0.0, 0.2))));

        // Wall 4
        theScene.push_back(new Triangle(points[3], points[4], points[9], Material(1.0, 0.0, 0.0, ColorDBL(1.0, 0.0, 0.6))));
        theScene.push_back(new Triangle(points[4], points[10], points[9], Material(1.0, 0.0, 0.0, ColorDBL(1.0, 0.0, 0.6))));

        // Roof 2
        theScene.push_back(new Triangle(points[0], points[4], points[1], Material(1.0, 0.0, 0.0, ColorDBL(0.1, 0.0, 0.2))));
        theScene.push_back(new Triangle(points[1], points[4], points[3], Material(1.0, 0.0, 0.0, ColorDBL(0.1, 0.0, 0.2))));

        // Roof 3
        theScene.push_back(new Triangle(points[10], points[5], points[4], Material(1.0, 0.0, 0.0, ColorDBL(0.1, 0.0, 0.2))));

        // Wall 5
        theScene.push_back(new Triangle(points[4], points[5], points[10], Material(1.0, 0.0, 0.0, ColorDBL(0.0, 0.0, 1.0))));
        theScene.push_back(new Triangle(points[5], points[11], points[10], Material(1.0, 0.0, 0.0, ColorDBL(0.0, 0.0, 1.0))));

        // Wall 6
        theScene.push_back(new Triangle(points[0], points[11], points[5], Material(1.0, 0.0, 0.0, ColorDBL(0.0, 0.8, 0.2))));
        theScene.push_back(new Triangle(points[0], points[6], points[11], Material(1.0, 0.0, 0.0, ColorDBL(0.0, 0.8, 0.2))));

        // Floor 1
        theScene.push_back(new Triangle(points[7], points[8], points[9], Material(1.0, 0.0, 0.0, ColorDBL(0.2, 0.2, 0.4))));

        // Floor 2      
        theScene.push_back(new Triangle(points[7], points[9], points[10], Material(1.0, 0.0, 0.0, ColorDBL(0.2, 0.2, 0.4))));
        theScene.push_back(new Triangle(points[7], points[10], points[6], Material(1.0, 0.0, 0.0, ColorDBL(0.2, 0.2, 0.4))));

        // Floor 3
        theScene.push_back(new Triangle(points[6], points[10], points[11], Material(1.0, 0.0, 0.0, ColorDBL(0.2, 0.2, 0.4))));

        theScene.push_back(new Triangle(glm::vec3(10.0f, 5.0f, 1.0f), glm::vec3(10.0f, 4.0f, 0.0f), glm::vec3(10.0f, 6.0f, 0.0f), Material(1.0, 0.0, 0.0, ColorDBL(0.5, 0.5, 0.0))));
        theScene.push_back(new Triangle(glm::vec3(10.0f, 3.0f, 1.0f), glm::vec3(10.0f, 2.0f, 0.0f), glm::vec3(10.0f, 4.0f, 0.0f), Material(1.0, 0.0, 0.0, ColorDBL(0.5, 0.5, 0.0))));
        theScene.push_back(new Triangle(glm::vec3(10.0f, 4.0f, 2.0f), glm::vec3(10.0f, 3.0f, 1.0f), glm::vec3(10.0f, 5.0f, 1.0f), Material(1.0, 0.0, 0.0, ColorDBL(0.5, 0.5, 0.0))));

        //theScene.push_back(new Triangle(points[3], points[9], points[1], Material(1.0, 0.0, 0.0, ColorDBL(0.3, 0.2, 0.0))));
        //theScene.push_back(new Triangle(glm::vec3(10.0f, 6.0f, 4.5f), glm::vec3(13.0f, 0.0f, 4.5f), glm::vec3(10.0f, -6.0f, 4.5f), Material(1.0, 0.0, 0.0, ColorDBL(1.0, 0.0, 0.0))));
        //theScene.push_back(new Triangle(glm::vec3(10.0f, -6.0f, 5.0f), glm::vec3(10.0f, -6.0f, -5.0f), glm::vec3(10.0f, 6.0f, 5.0f), Material(1.0, 0.0, 0.0, ColorDBL(0.2, 1.0, 1.0))));
    }

  std::vector<Object*> getoObjects() { return theScene; }
};
