#include "world.h"

using namespace std;

float World::firstIntersection(Ray& ray)
{
	for(int i=0; i<objectList.size(); i++)
		objectList[i]->intersect(ray);
	return ray.getParameter();
}


Color World::shade_ray(Ray& ray)
{	
	firstIntersection(ray);
	if(ray.didHit())
	{
			Color diffuseColor = Color(0);
			for(LightSource* light: lightSourceList){
				Ray shadowRay(ray.getPosition(), light->getPosition() - ray.getPosition());
				firstIntersection(shadowRay);
				if(shadowRay.didHit()){
					diffuseColor = diffuseColor + (ambient * shadowRay.intersected()->getMaterial()->ka);
				}
				else{
					diffuseColor = diffuseColor + (ray.intersected())->shade(ray);		
				}
			}
			return diffuseColor;
		}
		
	return background;
}


