//object.h
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "ray.h"
#include "vector3D.h"
#include "color.h"
#include "material.h"
#include "world.h"

class Object
{
protected:
	Material *material;
	bool isSolid;
	World *world;
public:
	Object(Material *mat, World *world): material(mat), world(world) {}	
	virtual bool intersect(Ray& ray) const = 0;
	virtual Color shade(const Ray& ray) const
	{
		return material->shade(ray, isSolid);
	}
	Material* getMaterial() const {return material;}
};

#endif
