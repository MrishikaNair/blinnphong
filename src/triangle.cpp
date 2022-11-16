//triangle.cpp

#include "triangle.h"

bool Triangle::intersect(Ray& r) const
{
    const float EPSILON = 0.0000001;
    Vector3D v0(-10,0,-11);
    Vector3D v1(6,0,-11);
    Vector3D v2(-2,8,-11);
    Vector3D rayVector=r.getDirection();
    Vector3D edge1, edge2, h, s, q;
    float a,f,u,v;
    edge1 = v1 - v0;
    edge2 = v2 - v0;
    h = crossProduct(rayVector,edge2);
    a = dotProduct(edge1,h);
    if (a > -EPSILON && a < EPSILON)
        return false;    // This ray is parallel to this triangle.
    f = 1.0/a;
    s = r.getOrigin() - v0;
    u = f * dotProduct(s,h);
    if (u < 0.0 || u > 1.0)
        return false;
    q = crossProduct(s,edge1);
    v = f * dotProduct(rayVector,q);
    if (v < 0.0 || u + v > 1.0)
        return false;
    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = f * dotProduct(edge2,q);
    if (t > EPSILON) // ray intersection
    {
        //outIntersectionPoint = rayOrigin + rayVector * t;

        return r.setParameter(t,this);
    }
    else // This means that there is a line intersection but not a ray intersection.
        return false;
        /*
	if(discriminant >=0.0)
	{

		if(discriminant == 0)
		{
			double t;
			t = -b/(2.0*a);
			r.setParameter(t, this);
			return true;
		}
		else
		{
			//Calculate both roots
			double D = sqrt(discriminant);
			double t1 = (-b +D)/(2.0*a);
			double t2 = (-b -D)/(2.0*a);

			bool b1 = r.setParameter(t1, this);
			bool b2 = r.setParameter(t2, this);

			return b1||b2;    
		}
	}*/
	return false;

}
Color Triangle::shade(const Ray& ray) const{

    Vector3D v0(-10, -8,-10); 
    Vector3D v1(0, -2, -10); 
    Vector3D v2(-5, 3, -10);
    //Vector3D camera_position(0, 0, 10);
	Color color = material->shade(ray, isSolid);

	//ambient shading
	Color ambientColor = world->getAmbient() * material->ka;
	

	//Lambertian shading and specular shading over list of light sources

	//Getting normal at the point
	Vector3D v1v0 = v1 - v0;
	Vector3D v2v0 = v2 - v0;
	
	//Vector3D normal = crossProduct(sideOne, sideTwo);
	Vector3D normal = crossProduct(v2v0, v1v0);
	
	normal.normalize();
    //normal*=-1;
	//Iterating over each light source
	//Getting vector from light source to the point
	std::vector<LightSource*> lightSourceList = world->getLightSourceList();
	
	Color diffuseColor = Color(0.0);
	Color specularColor = Color(0.0);

	for(LightSource* light: lightSourceList){

		//Lambertian shading
		Vector3D lightRay = ray.getPosition() - light->getPosition();
		lightRay.normalize();

		double dotResult = dotProduct(normal, lightRay);

		if(dotResult >= 0){
			double coeff = material->kd * dotResult;
			diffuseColor = diffuseColor + (light->getIntensity() *coeff );


		}

		//Specular shading
		Vector3D halfwayVector = ray.getDirection() + lightRay;
		halfwayVector = halfwayVector / halfwayVector.length();

		double halfwayDot = dotProduct(normal, halfwayVector);
		halfwayDot = pow(halfwayDot, material->n);
		if(halfwayDot >= 0){
			specularColor = specularColor + (world->getSpecular() *material->ks *  halfwayDot);
		}

	}
	
	//Specular shading

	return ambientColor + diffuseColor + specularColor;
}
