//sphere.cpp

#include "sphere.h"

bool Sphere::intersect(Ray& r) const
{
	Vector3D centerVector = r.getOrigin() - position;
	double a = 1.0;
	double b = 2*dotProduct(r.getDirection(), centerVector);
	double c = dotProduct(centerVector, centerVector) - radius*radius;
	double discriminant = b*b - 4.0*a*c;

	//now check if discr. is posivtive or zero, then only we have an intersection!
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
	}
	return false;


}
Color Sphere::shade(const Ray& incident)const
{
	Color color = material->shade(incident, isSolid);
	
	Color Ambient = world->getAmbient() * material->ka;
	Color Diffuse=Color(0.0);
	Color Specular=Color(0.0);

	Vector3D raydir = incident.getDirection();
	float dist = raydir.length();
	raydir.normalize();

	Vector3D normal=position-incident.getPosition();
	normal.normalize();
	
	std::vector<LightSource*> lightSourceList =world->getLightSourceList();
	for(LightSource* light: lightSourceList)
	{
		Vector3D lightdir = incident.getPosition() - light->getPosition();
		lightdir.normalize();

		float NdotL = dotProduct(normal, lightdir);

		if(NdotL>=0){
			
			Diffuse = Diffuse + (light->getIntensity()*material->kd * NdotL);
		}
		Vector3D H= incident.getDirection() + lightdir;
		H = H/H.length();

		double NdotH = dotProduct(normal, H);
		NdotH = pow(NdotH, material->n);
		if(NdotH >= 0){
			Specular = Specular + (world->getSpecular() *material->ks *NdotH);
		}

	}
	
	return Ambient+Diffuse+Specular;
}
/*	
Vector3D CalculateLocalNormal(Vector3D localPoint, Intersection i = null) { 
	Vector3D p(0,0,0);
	//Determine the normal in local space
	Vector normal = localPoint - p;
	//W coordinates in a 4x4 may mess up our vector
	normal.W() = 0;
	normal.normalize();
	return normal;
}
*/




