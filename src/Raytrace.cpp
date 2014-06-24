/*
 * Raytrace.cpp
 *
 *  Created on: Sep 10, 2013
 *      Author: bhikadiy
 */

#include "Raytrace.h"

void Ray_trace::ray_trace() {

	double a = 0, b = 0;
	int width = color_img.get_width();
	int height = color_img.get_height();


	focal_point = cam.get_prp();


	vectors vpn,vup,u,v;
	double d=cam.get_fl();

	vpn= cam.get_vpn();
	vup= cam.get_vup();
	u.cross(vup,vpn);
	u.normalize();
	v.cross(vpn,u);
	v.normalize();

	cout<<"fp is "<<focal_point.at(0)<<setw(10)<<focal_point.at(1)<<setw(10)<<focal_point.at(2)<<endl;
	cout<<"vpn is "<<vpn.vect.at(0)<<"\t\t"<<vpn.vect.at(1)<<"\t\t"<<vpn.vect.at(2)<<endl;
	cout<<"u is "<<u.vect.at(0)<<"\t\t"<<u.vect.at(1)<<"\t\t"<<u.vect.at(2)<<endl;
	cout<<"v is "<<v.vect.at(0)<<"\t\t"<<v.vect.at(1)<<"\t\t"<<v.vect.at(2)<<endl;


	vector<double>fp_minus_dvpn;
	fp_minus_dvpn.push_back(focal_point.at(0)-d*vpn.vect.at(0));
	fp_minus_dvpn.push_back(focal_point.at(1)-d*vpn.vect.at(1));
	fp_minus_dvpn.push_back(focal_point.at(2)-d*vpn.vect.at(2));
	vectors center(fp_minus_dvpn);
	cout<<"center of image :";
	center.printvect();
	cout<<endl;


	double twobyh = 2.0 / (height - 1), twobyw = 2.0 / (width - 1);

	for(int i=0; i<(int)objects.size();i++)
	{
		for(int j=0;j<(int)objects.at(i).face.size();j++)
		{
			objects.at(i).face.at(j).cal_fptov(focal_point, ver);
		}
	}

	for (unsigned int i = 0; i < spheres.size(); i++) {
			spheres.at(i).O_minus_focal_point(focal_point);
		}

	//near = cam.get_near();
	//far=cam.get_far();
//calculate O_minus_focal_point for all the spheres // this term is constant C for sphere intersection
//#pragma omp parallel for  schedule(dynamic,1)

	for (int i = 0; i < height; i++) {
//#pragma omp parallel
//#pragma omp parallel for
		for (int j = 0; j < width; j++) {
			recursion_refl = color_img.get_recursion();
			recursion_refr = color_img.get_recursion();

			a = twobyw * j - 1;
			b = twobyh * i - 1;
			//std::cout<<"a :"<<a<<"\t b : "<<b<<std::endl;
			std::vector<double> point, p_minus_fp;
			//find the point position on image plane of (-1,-1) to (1,1) which maps to pixel value of (0,0) to (256,256)
			point.push_back(fp_minus_dvpn.at(0) + a*u.vect.at(0) + b*v.vect.at(0));
			point.push_back(fp_minus_dvpn.at(1)+ a*u.vect.at(1) + b*v.vect.at(1));
			point.push_back(fp_minus_dvpn.at(2)+ a*u.vect.at(2) + b*v.vect.at(2));
			//find the ray direction -- Point on image plane minus focal point
			p_minus_fp.push_back(point.at(0) - focal_point.at(0));
			p_minus_fp.push_back(point.at(1) - focal_point.at(1));
			p_minus_fp.push_back(point.at(2) - focal_point.at(2));
			vectors ray(p_minus_fp);
			//ray_mag = ray.magnitude();
			ray.normalize();
			//ray.printvect();
			std::vector<double> color_value;
			ray_refl(color_value, ray,point);

			//std::cout<<"color at(i,j)  = "<<height-i-1<<" "<<j<<"  "<<color_value.at(0)<<"\t"<<color_value.at(1)<<"\t"<<color_value.at(2)<<"\n";
			color_img.fill_pixel(color_value, height - i - 1, j);
		}
		if((i%(int(width/20)))==0){cout<<(float(i)/float(width)*100)<<" % done\n";					}
	}

}

void Ray_trace::ray_refl(std::vector<double> & color_value,
	 vectors ray,vector<double>&origin) {

	vector<int> surf(3,0);
	double smin= DBL_MAX ;

		//cout<<"smin is "<<smin<<endl;
		//cout<<ellipse.size()<<endl;
	for(int i=0; i<(int)spheres.size();i++)
	{	double s=-1;
		s=intersection_sphere(ray,i,origin);
		if( s<smin && s>0)
		{
			smin=s;
			surf.at(2)=i+1;
		}
	}

	for(int i=0; i<(int)objects.size();i++)
	{
		for(int j=0;j<(int)objects.at(i).face.size();j++)
		{
			double s=-1;
			s=intersection_object(ray,i,j,origin);

			if(s<smin && s>0)
			{
				//cout<<"face"<<s<<endl;
				smin=s;
				//	cout<<"s min is for face "<<i;
				surf.at(2)=0;
				surf.at(0)=i+1;
				surf.at(1)=j+1;
			}
		}
	}
	//cout<<"surf :"<<surf.at(0)<<" "<<surf.at(1)<<" "<<surf.at(2)<<endl;
	if(surf.at(2)!=0)
	{
		color_value.push_back(0);
		color_value.push_back(0);
		color_value.push_back(0);
		//cout<<"inside ellipse\n";
		point_refl_ellipse(surf,smin,color_value,ray,origin);
	}
	else if(surf.at(0)!=0 && surf.at(1)!=0)
	{

		color_value.push_back(0);
		color_value.push_back(0);
		color_value.push_back(0);
		point_refl_objects(surf,smin,color_value,ray,origin);
	}
	else
	{
		color_value.push_back(0);
		color_value.push_back(0);
		color_value.push_back(0);

	}
}


double Ray_trace:: intersection_sphere(vectors r,int ell_index,vector<double>point_ons)
{
	double s=-1;
	vectors O_minus_P =spheres.at(ell_index).O_minus_focal_point(point_ons);

	double v=O_minus_P.dot(r);
	double v2=v*v;
	double c= O_minus_P.magnitude() * O_minus_P.magnitude();
	double d2=spheres.at(ell_index).r2- c + v2;
	if(d2>0)
	{
		if(n_current>1)
		{
			s=v+sqrt(d2);
		}
		else
		{
		s=v-sqrt(d2);
		}
	}
	return s;
}

double Ray_trace::intersection_object(vectors r,int obj_index, int face_index,vector<double>point_ons)
{

	double s=-1,det,u,v;
	vectors f2r,rf1,f1f2;
	f2r.cross(objects.at(obj_index).face.at(face_index).f2,r);
	rf1.cross(r,objects.at(obj_index).face.at(face_index).f1 );
	f1f2.cross(objects.at(obj_index).face.at(face_index).f1,objects.at(obj_index).face.at(face_index).f2  );

	det= (-1)*objects.at(obj_index).face.at(face_index).f1.dot(f2r);
	//cout<<det<<endl;
	if(det!=0)
	{//cout<<"hello\n";
		vectors ptov;
		ptov =objects.at(obj_index).face.at(face_index).cal_ptov(point_ons);
		u = (-1)*f2r.dot(ptov )/det;
		v = (-1)*rf1.dot(ptov)/det;
		if((u>0 || abs(u)==0) && (v>0|| abs(v)==0) && u+v<=1)
		{
			s = f1f2.dot(ptov )/det;
		}
		//cout<<"U is "<<u<<endl<<"v is "<<v<<endl<<"s is "<<s<<endl;
	}
	return s;
}

void Ray_trace:: point_refl_ellipse(vector<int>surf, double smin, vector<double>&color,vectors r,vector<double> origin)
{


	vector<double> fp= cam.get_prp();
	vector<double> point;
	point.push_back(origin.at(0)+smin*r.vect.at(0));
	point.push_back(origin.at(1)+smin*r.vect.at(1));
	point.push_back(origin.at(2)+smin*r.vect.at(2));
	//cout<<"lights size is"<<lights.size()<<endl;
	for(unsigned int i=0;i<lights.size();i++)
	{
		vector<double> light_ray;
		light_ray.push_back( (lights.at(i).x - point.at(0)) );
		light_ray.push_back( (lights.at(i).y - point.at(1)) );
		light_ray.push_back( (lights.at(i).z - point.at(2)) );

		vectors l_ray(light_ray);
		double l_dist = l_ray.magnitude();
		l_ray.normalize();
		int flag=shadow(l_ray,point,surf,l_dist);
		if(flag==1)
		{	continue;}

		if(mat.size()!=0)
		{
			cal_diffuse_sphere(point,surf,i,color,l_ray);
			cal_spec_sphere(point,surf,i,color,r,l_ray);
		}
	}

	vector<double>refr;
	//cout<<"\t\tdepth_r is"<<recursion_refl<<endl;

	vector<double>refl;
	//	cout<<"\t\tdepth is"<<depth<<endl;
	if(recursion_refl>1)
	{	//cout<<"here \n";
		cal_reflection_sphere(point,surf,refl,r);
		//cout<<refl.at(0)<<" "<<refl.at(1)<<" "<<refl.at(2)<<" is  \n";
		color.at(0) = 20+color.at(0)+refl.at(0);
		color.at(1) = 20+color.at(1)+refl.at(1);
		color.at(2) = 20+color.at(2)+refl.at(2);
	}
	

	if(recursion_refr>1)
	{
		//cout<<"here1 \n";
		cal_refraction_sphere(point,surf,refr,r);
		//cout<<"here2 \n";
		//cout<<refr.at(0)<<" "<<refr.at(1)<<" "<<refr.at(2)<<" \n";
		
		double T= mat.at((spheres.at(surf.at(2)-1).mat_index)).Tr;
		color.at(0) = T*color.at(0) + (1-T)*refr.at(0);
		color.at(1) = T*color.at(1) + (1-T)*refr.at(1);
		color.at(2) = T*color.at(2) + (1-T)*refr.at(2);
//cout<<"refraction ray is"<<setw(10)<<refr.at(0)<<setw(10)<<refr.at(1)<<setw(10)<<refr.at(2);

	}

	
}

int Ray_trace:: shadow(vectors light, vector<double>point,vector<int>surf,double l_dist)
{
	int flag=0;
	for(unsigned int j=0; j<spheres.size();j++)
	{		double s=-1;
		if((int)j==surf.at(2)-1)
		{
			continue;
		}
		s=intersection_sphere(light,j,point);

		if(s>10e-6 && s<l_dist)
		{
			flag=1;
			return flag;
		}
	}

	for(unsigned int k=0; k<objects.size();k++)
	{
		double s=-1;
		for(unsigned int l=0;l<objects.at(k).face.size();l++)
		{
			if((int)k==surf.at(0)-1 && (int)l==surf.at(1)-1)
			{continue;}
			s=intersection_object(light,k,l,point);
			if(s>10e-6 && s<l_dist)
			{
				flag=1;
				return flag;
			}
	}
	return flag;
}
}


void Ray_trace:: cal_diffuse_sphere(vector<double>pt, vector<int>surf,int l_index,vector<double>&color,vectors l_ray)
{

	vectors surf_normal;
	surf_normal = spheres.at(surf.at(2)-1).surf_normal(pt);
	double cosi=l_ray.dot(surf_normal);
	if(cosi>0)
	{
	color.at(0) += cosi *( mat.at((spheres.at(surf.at(2)-1).mat_index)).kd.at(0) ) * lights.at(l_index).r;

	color.at(1) += cosi *( mat.at((spheres.at(surf.at(2)-1).mat_index)).kd.at(1) ) * lights.at(l_index).g;

	color.at(2) += cosi *( mat.at((spheres.at(surf.at(2)-1).mat_index)).kd.at(2) ) * lights.at(l_index).b;
	}
}
void Ray_trace:: cal_spec_sphere(vector<double>pt, vector<int>surf,int l_index,vector<double>&color,vectors ray, vectors l_ray)
{
	vectors surf_normal;
	surf_normal =  spheres.at(surf.at(2)-1).surf_normal(pt);
	vectors R;
	double ln= 2* l_ray.dot(surf_normal);
	R.vect.at(0)= ln*surf_normal.vect.at(0)-l_ray.vect.at(0);
	R.vect.at(1)= ln*surf_normal.vect.at(1)-l_ray.vect.at(1);
	R.vect.at(2)= ln*surf_normal.vect.at(2)-l_ray.vect.at(2);
	double cosi = (-1)*ray.dot(R);
	if(cosi>0)
	{	double cosp = pow(cosi,mat.at((spheres.at(surf.at(2)-1).mat_index)).ns);

		color.at(0) += cosp *( mat.at((spheres.at(surf.at(2)-1).mat_index)).ks.at(0) ) * lights.at(l_index).r;

		color.at(1) += cosp *(mat.at((spheres.at(surf.at(2)-1).mat_index)).ks.at(1) ) * lights.at(l_index).g;

		color.at(2) += cosp *( mat.at((spheres.at(surf.at(2)-1).mat_index)).ks.at(2) ) * lights.at(l_index).b;
	}
}



void Ray_trace:: point_refl_objects(vector<int>surf, double smin, vector<double>&color,vectors r,vector<double>origin)
{
	vector<double> fp= cam.get_prp();

	vector<double> point;
	point.push_back(origin.at(0)+smin*r.vect.at(0));
	point.push_back(origin.at(1)+smin*r.vect.at(1));
	point.push_back(origin.at(2)+smin*r.vect.at(2));

	for(unsigned int i=0;i<lights.size();i++)
	{
		vector<double> light_ray;
		light_ray.push_back( (lights.at(i).x - point.at(0)) );
		light_ray.push_back( (lights.at(i).y - point.at(1)) );
		light_ray.push_back( (lights.at(i).z - point.at(2)) );

		vectors l_ray(light_ray);
		double l_dist = l_ray.magnitude();
		l_ray.normalize();
		point.at(0)=point.at(0)+l_ray.vect.at(0)*10e-5;
		point.at(1)=point.at(1)+l_ray.vect.at(1)*10e-5;
		point.at(2)=point.at(2)+l_ray.vect.at(2)*10e-5;
		int flag= shadow(l_ray,point,surf,l_dist);
		//cout<<"intersection\n";
		if(flag==1)
		{
			//cout<<"shadoe\n";
			continue;
		}
//		cout<<"light ray normalized is "<<setw(10)<<l_ray.vect.at(0)<<setw(10)<<l_ray.vect.at(1)<<setw(10)<<l_ray.vect.at(2)<<setw(10)<<endl;
		if(mat.size()!=0)
		{
				cal_diffuse_objects(point,surf,i,color,l_ray);
				cal_spec_objects(point,surf,i,color,r,l_ray);
		}
	}
	color.at(0) = 20 + color.at(0);
	color.at(1) = 20 + color.at(1);
	color.at(2) = 20 + color.at(2);


	vector<double>refr;
	vector<double>refl;

	if(recursion_refl>1)
	{
		cal_reflection_objects(point,surf,refl,r);
		//cout<<refl.at(0)<<" "<<refl.at(1)<<" "<<refl.at(2)<<" \n";
	color.at(0) = 20+color.at(0)+refl.at(0);
	color.at(1) = 20+color.at(1)+refl.at(1);
	color.at(2) = 20+color.at(2)+refl.at(2);
	}
	

/*	if(depth>0)
	{
		cal_reflection_objects(point,surf,refl,r);
	}

	double T=mat.at((objects.at(surf.at(0)-1).face.at(surf.at(1)-1).mat_index)-1).Tr;

	ref.at(0) = T*ref.at(0) + (1-T)*refr.at(0);
	ref.at(1) = T*ref.at(1) + (1-T)*refr.at(1);
	ref.at(2) = T*ref.at(2) + (1-T)*refr.at(2);
*/


}




void Ray_trace:: cal_diffuse_objects(vector<double>pt, vector<int>surf,int l_index,vector<double>&color,vectors l_ray)
{


	double cosi=l_ray.dot(objects.at(surf.at(0)-1).face.at(surf.at(1)-1).normal);

//	cout<<"normal is "<<setw(10)<<objects.at(surf.at(0)-1).face.at(surf.at(1)-1).normal.vect.at(0)<<setw(10)<<objects.at(surf.at(0)-1).face.at(surf.at(1)-1).normal.vect.at(1)<<setw(10)<<objects.at(surf.at(0)-1).face.at(surf.at(1)-1).normal.vect.at(2)<<setw(10)<<endl;
	if(cosi>0)
	{
	color.at(0) += cosi *( mat.at((objects.at(surf.at(0)-1).face.at(surf.at(1)-1).mat_index)).kd.at(0) ) * lights.at(l_index).r;
	//cout<<cosi<<" "<< mat.at((objects.at(surf.at(0)-1).face.at(surf.at(1)-1).mat_index)).kd.at(0)<< " "<<lights.at(l_index).r<<endl;
	color.at(1) += cosi *( mat.at((objects.at(surf.at(0)-1).face.at(surf.at(1)-1).mat_index)).kd.at(1) ) * lights.at(l_index).g;

	color.at(2) += cosi *( mat.at((objects.at(surf.at(0)-1).face.at(surf.at(1)-1).mat_index)).kd.at(2) ) * lights.at(l_index).b;
	//cout<<color.at(0)<<endl;
	}
}


void Ray_trace:: cal_spec_objects(vector<double>pt, vector<int>surf,int l_index,vector<double>&color,vectors ray, vectors l_ray)
{
	vectors R;
	double ln= 2* l_ray.dot(objects.at(surf.at(0)-1).face.at(surf.at(1)-1).normal);
	R.vect.at(0)= ln*objects.at(surf.at(0)-1).face.at(surf.at(1)-1).normal.vect.at(0)-l_ray.vect.at(0);
	R.vect.at(1)= ln*objects.at(surf.at(0)-1).face.at(surf.at(1)-1).normal.vect.at(1)-l_ray.vect.at(1);
	R.vect.at(2)= ln*objects.at(surf.at(0)-1).face.at(surf.at(1)-1).normal.vect.at(2)-l_ray.vect.at(2);
	//cout<<"normal is "<<setw(8)<< objects.at(surf.at(0)-1).face.at(surf.at(1)-1).normal.vect.at(0)<<setw(8)<< objects.at(surf.at(0)-1).face.at(surf.at(1)-1).normal.vect.at(1)<<setw(8)<< objects.at(surf.at(0)-1).face.at(surf.at(1)-1).normal.vect.at(2)<<endl;
	//cout<<"reflected is"<<setw(8)<<R.vect.at(0)<<setw(8)<<R.vect.at(1)<<setw(8)<<R.vect.at(2);


	double cosi = (-1)*ray.dot(R);
	if(cosi>0)
	{	double cosp = pow(cosi,mat.at((objects.at(surf.at(0)-1).face.at(surf.at(1)-1).mat_index)).ns);

		color.at(0) += cosp *( mat.at((objects.at(surf.at(0)-1).face.at(surf.at(1)-1).mat_index)).ks.at(0) ) * lights.at(l_index).r;

		color.at(1) += cosp *( mat.at((objects.at(surf.at(0)-1).face.at(surf.at(1)-1).mat_index)).ks.at(1) ) * lights.at(l_index).g;

		color.at(2) += cosp *( mat.at((objects.at(surf.at(0)-1).face.at(surf.at(1)-1).mat_index)).ks.at(2) ) * lights.at(l_index).b;
	}
}

void Ray_trace:: cal_reflection_sphere(vector<double>pt,vector<int >surf, vector<double> &ref,vectors r )
{
	//cout<<"\nrecursion "<<recursion_refl;
	recursion_refl--;
//	/cout<<"\npoint is "<<pt.at(0)<<setw(10)<<pt.at(1)<<setw(10)<<pt.at(2);
	vectors surf_normal;
	surf_normal = spheres.at(surf.at(2)-1).surf_normal(pt);
//	cout<<"reflected is"<<setw(10)<<surf_normal.vect.at(0)<<setw(10)<<surf_normal.vect.at(1)<<setw(10)<<surf_normal.vect.at(2)<<endl;
	double rn= 2 * r.dot(surf_normal);
	vectors R;
//	cout<<"in reflection\n";

	R.vect.at(0)= r.vect.at(0)-rn*surf_normal.vect.at(0);
	R.vect.at(1)= r.vect.at(1)-rn*surf_normal.vect.at(1);
	R.vect.at(2)= r.vect.at(2)-rn*surf_normal.vect.at(2);
	R.normalize();
//	cout<<"reflected is"<<setw(10)<<R.vect.at(0)<<setw(10)<<R.vect.at(1)<<setw(10)<<R.vect.at(2)<<endl;
	pt.at(0)=pt.at(0)+R.vect.at(0)*10e-5;
	pt.at(1)=pt.at(1)+R.vect.at(1)*10e-5;
	pt.at(2)=pt.at(2)+R.vect.at(2)*10e-5;
//	 depth_r=d_actual;
	recursion_refr = color_img.get_recursion();
	ray_refl(ref,R,pt);
	//ref.at(0) *= mat.at((ellipse.at(surf.at(2)-1).mat_index)-1).Kr;
	//ref.at(1) *= mat.at((ellipse.at(surf.at(2)-1).mat_index)-1).Kr;
	//ref.at(2) *= mat.at((ellipse.at(surf.at(2)-1).mat_index)-1).Kr;
}

void Ray_trace:: cal_reflection_objects(vector<double>pt,vector<int >surf, vector<double> &ref,vectors r )
{
	recursion_refl--;
	vectors surf_normal= objects.at(surf.at(0)-1).face.at(surf.at(1)-1).normal;
	double rn= 2* r.dot(surf_normal);
	vectors R;
	//	cout<<"in reflection\n";

	R.vect.at(0)= r.vect.at(0)-rn*surf_normal.vect.at(0);
	R.vect.at(1)= r.vect.at(1)-rn*surf_normal.vect.at(1);
	R.vect.at(2)= r.vect.at(2)-rn*surf_normal.vect.at(2);
	R.normalize();
	//	cout<<"reflected is"<<setw(10)<<R.vect.at(0)<<setw(10)<<R.vect.at(1)<<setw(10)<<R.vect.at(2)<<endl;
	pt.at(0)=pt.at(0)+R.vect.at(0)*10e-5;
	pt.at(1)=pt.at(1)+R.vect.at(1)*10e-5;
	pt.at(2)=pt.at(2)+R.vect.at(2)*10e-5;
	recursion_refr = color_img.get_recursion();
	ray_refl(ref,R,pt);
	//ref.at(0) *= mat.at((objects.at(surf.at(0)-1).face.at(surf.at(1)-1).mat_index)-1).Kr;
	//ref.at(1) *= mat.at((objects.at(surf.at(0)-1).face.at(surf.at(1)-1).mat_index)-1).Kr;
	//ref.at(2) *= mat.at((objects.at(surf.at(0)-1).face.at(surf.at(1)-1).mat_index)-1).Kr;
}

void Ray_trace:: cal_refraction_sphere(vector<double>pt,vector<int >surf, vector<double> &refr,vectors r )
{
	recursion_refr--;
	vectors surf_normal;
	surf_normal = spheres.at(surf.at(2)-1).surf_normal(pt);
	double n1=1;
	double n2 = mat.at(spheres.at(surf.at(2)-1).mat_index).n1;
	double N=n1/n2;
	double cosi=(-1)*surf_normal.dot(r),sint=2;
	if(cosi<0.9999)
	{
		sint=N*sqrt(1-cosi*cosi);
	}
	//cout<<"crash\n";
	if(sint*sint<(1-10e-6))
	{
		vectors R;
		R.vect.at(0)= N*r.vect.at(0)-(N*cosi+sqrt(1-sint*sint))*surf_normal.vect.at(0);
		R.vect.at(1)= N*r.vect.at(1)-(N*cosi+sqrt(1-sint*sint))*surf_normal.vect.at(1);
		R.vect.at(2)= N*r.vect.at(2)-(N*cosi+sqrt(1-sint*sint))*surf_normal.vect.at(2);
		R.normalize();
		//cout<<"refraction ray is"<<setw(10)<<R.vect.at(0)<<setw(10)<<R.vect.at(1)<<setw(10)<<R.vect.at(2)<<endl;
		//cout<<"Point is"<<setw(10)<<pt.at(0)<<setw(10)<<pt.at(1)<<setw(10)<<pt.at(2)<<endl;
		//cout<<"N is "<<N<<endl;
		vectors O_minus_P =spheres.at(surf.at(2)-1).O_minus_focal_point(pt);
		double v = O_minus_P.dot(R);
		//cout<<"\nv is "<<v;
		vector<double> point(3,0);
		point.at(0)=pt.at(0)+R.vect.at(0)*2*v;
		point.at(1)=pt.at(1)+R.vect.at(1)*v*2;
		point.at(2)=pt.at(2)+R.vect.at(2)*v*2;
		N=1/N;
		//cout<<"N is "<<N<<endl;
		surf_normal = spheres.at(surf.at(2)-1).surf_normal(point);
		double cosi=(-1)*surf_normal.dot(R),sint=2;
		if(cosi<0.9999)
		{
			sint=N*sqrt(1-cosi*cosi);
		}
		if(sint*sint<(1-10e-6))
		{
			vectors R_out;
			R_out.vect.at(0)= N*R.vect.at(0)-(N*cosi+sqrt(1-sint*sint))*surf_normal.vect.at(0);
			R_out.vect.at(1)= N*R.vect.at(1)-(N*cosi+sqrt(1-sint*sint))*surf_normal.vect.at(1);
			R_out.vect.at(2)= N*R.vect.at(2)-(N*cosi+sqrt(1-sint*sint))*surf_normal.vect.at(2);
			//cout<<"re-refraction ray is"<<setw(10)<<R_out.vect.at(0)<<setw(10)<<R_out.vect.at(1)<<setw(10)<<R_out.vect.at(2)<<endl;
			R_out.normalize();
			//cout<<"refraction ray is"<<setw(10)<<R.vect.at(0)<<setw(10)<<R.vect.at(1)<<setw(10)<<R.vect.at(2);
			point.at(0)=point.at(0)+R_out.vect.at(0)*10e-5;
			point.at(1)=point.at(1)+R_out.vect.at(1)*10e-5;
			point.at(2)=point.at(2)+R_out.vect.at(2)*10e-5;
			recursion_refl = color_img.get_recursion();
			ray_refl(refr,R_out,point);
		}
		else{
		refr.push_back(0);
		refr.push_back(0);
		refr.push_back(0);}
			
	}
	else{
		refr.push_back(0);
		refr.push_back(0);
		refr.push_back(0);}
		


}



Ray_trace::~Ray_trace() {
	// TODO Auto-generated destructor stub
}

