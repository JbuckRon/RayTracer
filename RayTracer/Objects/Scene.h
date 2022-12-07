#pragma once
#include "../Math/Color.h"
#include <vector>
#include <memory>
class Object;

struct Ray;

struct RaycastHit;



class Scene

{

public:

    Scene() = default;
    color3 Trace(const Ray& ray, float min, float max, RaycastHit& hit, int depth);
    void AddObject(std::unique_ptr<Object> object);



private:

    std::vector <std::unique_ptr<Object>> m_objects;

};