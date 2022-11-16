#include "world.h"
#include "material.h"


Color Material::shade(const Ray& incident, const bool isSolid) const
{
	// Vector3D Ls = Vector3D(1.0, 1.0, 1.0);
	// Vector3D Ld = Vector3D(0.7, 0.7, 0.7);
	// Vector3D La = Vector3D(0.6, 0.2, 0.2);

	// Vector3D ks = Vector3D(1.0, 1.0, 1.0);
	// Vector3D kd = Vector3D(0.5, 0.6, 0.4);
	// Vector3D ka = Vector3D(1.0, 1.0, 1.0);

	// float spec_exp = 4.0;
	/*
	Vector3D lightdir=incident.getPosition()-position;
	float dist= lightdir.length();
	lightDir = lightdir / dist;
	dist = dist * dist;
	Vector3D normal=lightdir;
	normal.w=0;
	normal.normalize();

	
	color.Ambient = dotProduct(Ia,ka);

	float NdotL = dotProduct(normal, lightDir);
	float Id = NdotL;
	color.Diffuse = Id * incident.diffuseColor * incident.diffusePower / dist;

	Vector3D H = normalize(lightDir + viewDir);
	Vector3D Ia = ka * La;
    //Vector3D Id = kd * max(dotProduct(lightdir, normal) * Ld, 0);
	//Intensity of the specular light
	float NdotH = dotProduct(normal, H);
	Vector3D Is = pow(NdotH, spec_exp);

	//Sum up the specular light factoring
	color.Specular = Is * incident.specularColor * incident.specularPower / dist; 
	*/
	return color;
	
}


