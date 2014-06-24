/*
 * Readobjects.cpp
 *
 *  Created on: Sep 18, 2012
 *      Author: bhikadiy
 */

#include "Read_objects.h"

vector<int> Read_objects::read_file(char* file_name)
{

	total_objects=0;
	total_vertices=0;
	total_spheres=0;

	obj_first_pass(file_name);
	obj_second_pass(file_name);


	vector<int> total_numbers;

	total_numbers.push_back(total_objects);
	total_numbers.push_back(total_spheres);
	total_numbers.push_back(total_vertices);
	//cout<<"here"<<endl;
	return total_numbers;
}

void Read_objects::obj_first_pass(char * obj_name) {
	ifstream object_file;									//Create file object

	object_file.open(obj_name);								//open input file
	cout << obj_name << " is now open to read content." << endl;
	cout << "Reading vertices and creating groups in 1st go." << endl;

	int g_count = 0, f_count = 0, e_count = 0;
	++g_count;
	pushback_g("default");

	if (object_file.is_open()) {
		while (!object_file.eof()) {
			string line;
			istringstream s;
			getline(object_file, line);
			string a, v = "v", g = "g", h = "#", n = " ", fa = "f";
			s.str(line);
			//cout<<"line is in stringstream"<<endl;
			s >> a;
			//char c='#';
			if (a == v) {

				cout<<"reading vertex number :"<<total_vertices<<std::endl;
				read_v(line, total_vertices);
			}
			else if (a == "mtllib") {
				read_mat(line, obj_name);
			}

			else if (a == g) {
				++g_count;
				string object_name;
				s >> object_name;
				int flag = 0;
				current_object = object_name;
				int g_index = get_group_index(current_object);

				if (g_index != -1) {
					--g_count;
					cout << endl << "group " << current_object
							<< " already exist." << endl;
					flag = 1;
				}

				if (flag == 0) {
					pushback_g(current_object);
				}

			}

		}

	}
	object_file.close();
}

void Read_objects::obj_second_pass(char * obj_name) {

	ifstream object_file;									//Create file object

	object_file.open(obj_name);								//opinput file
	cout << obj_name << " is again open to read content." << endl;
	current_object = "default";
	while ( !object_file.eof() )
	{
		string line,a,g="g",f="f",v="v",n="\0";
		getline(object_file,line);
		stringstream s;
		s<<line;
		s>>a;
		if(a=="usemtl")
		{
			//cout<<a;
			string material_name;
			s>>material_name;
			current_mat_index=get_material_index(material_name);
		}
		else if (a=="s")
		{
			total_spheres++;
			string sphere_name;
			s>>sphere_name;
			pushback_e(line,total_spheres);

		}
		else if(a==g)
		{
			//cout<<g_count<<endl<<endl;
			string object_name;
			int flag=0;
			s>>object_name;
			current_object=object_name;

		}
		else if (a == f)
		{
			total_faces++;
			vector<int> f;
			double value;
			string c;
			int g_index = get_group_index(current_object);
			int total_f = objects.at(g_index ).get_total_faces();
			while (!s.eof()) {
				s >> value;
				//cout<<value<<endl;
				//int g=s.tellg();
				//cout<<"get is at"<<g<<endl<<"material index is "<<current_mat_index<<endl;
				//read co-ordinates of vertex
				if (!s.fail()) {
					f.push_back(value);
				}

				else if (s.eof())
					break;
				else if (s.fail()) {
					cout << endl
							<< "encountered non number value for face co-ordinate."
							<< endl;
					cout << "check face number " << total_f + 1 << " of group "
							<< current_object << endl;
					exit(1);
				}

				s >> c;
				//cout<<"a"<<c<<"b"<<endl;
				if (!s.fail()) {
					if (c[0] == '/')
						continue;
					else
						s.seekg(-c.length(), ios::cur);
				}
			}
			face_errors(g_index, f);
			if (f.size() > 3) {
				vector<int> f_tri;
				for (unsigned i = 0; i < f.size() - 2; i++) {
					//	cout<<f_count<<endl;
					f_tri.push_back(f.at(0));
					f_tri.push_back(f.at(i + 1));
					f_tri.push_back(f.at(i + 2));
					objects.at(g_index ).assign_faces( f_tri,
							current_mat_index);
					f_tri.erase(f_tri.begin(), f_tri.end());

				}

			} else {
				objects.at(g_index ).assign_faces( f,
						current_mat_index);
			}
		}


	}

}
void Read_objects:: read_v(string &line ,int vcount)
{

	double value;
	istringstream s;
	s.str(line);
	char c;
	s>>c;

	vector<double>v;

	while(!s.eof())
	{
		s>>value;

		//read co-ordinates of vertex
		if(!s.fail())
		{	v.push_back(value);

		}

		else if(s.eof())
			break;

		else if(s.fail())
		{
			cout<<endl<<"encountered non number value for vertex co-ordinate."<<endl;
			cout<<"check vertex number "<< vcount;
			exit(1);
		}

	}

	// If only X,Y,Z are given then append W
	if(v.size()==4)
	{
		for(int i=0;i<4;i++)
		{
			if(v.at(3)!=0)
				v.at(i)=v.at(i)/v.at(3);
			//cout<<endl<<v.at(i);
		}

		//cout<<v.size();
	}

	else if(v.size()==3)
	{
		v.push_back(1);
		//cout<<v.size();
	}

	//if more than 4 or less than 3 vertices are given then thrown an error
	else if(v.size() < 3)
	{
		cout<<endl<<"encountered vertex with less than 3 coordinates"<<endl;
		cout<<"check vertex number "<< vcount;
		exit(1);
	}
	else if(v.size()>4)
	{
		cout<<endl<<"encountered vertex with more than 3 coordinates. "<<endl;
		cout<<"check vertex number "<< vcount;
		exit(1);
	}

	pushback_v(v);

	//int g_index=get_group_index(current_object);

	//objects.at(g_index-1).all_vertices.push_back(vcount);

}

void Read_objects:: pushback_v(vector<double>&v)
{
	vertices vertex;
	ver.push_back(vertex);
	total_vertices++;
	ver.at(total_vertices-1).assign_values(v);
	//cout<<"vertex "<<total_vertices<<" is assigned now"<<endl;

}


void Read_objects:: read_mat(string line,char * file)
{
	istringstream s;
	s.str(line);
	string name;
	s>>name;
	s>>name;
	cout<<"\nreading materials\n";
	string path=get_filepath(file);
	if(path.length()!=0)
	{
		path.append("/");
	}
	//cout<<"\npath is "<<path<<endl;
	path.append(name);
	//cout<<"\npath is "<<path<<endl;

	char * mat_path;
	mat_path = new char [path.size()+1];
	strcpy (mat_path, path.c_str());
	//cout<<mat_path;
	ifstream mat_file;										//Create file object
	mat_file.open(mat_path);
	if (mat_file.is_open())
	{


		while ( !mat_file.eof() )
		{	string l,temp;
		getline(mat_file,l);
		//cout<<endl<<l;
		stringstream s;
		s<<l;
		s>>temp;
		int m_index=1;
		if(temp=="newmtl")
		{
			//cout<<"reading new material"<<endl;
			s>>temp;
			a :
			material m;
			mat.push_back(m);
			mat.at(m_index-1).assign_name(temp,m_index-1);

			while( !mat_file.eof())
			{
				stringstream ss;
				getline(mat_file,l);

				ss<<l;
				ss>>temp;
				//		cout<<endl<<"line is:"<<l<<endl<<"first is:"<<temp<<endl;;
				if(temp=="Ka")
				{ 	mat.at(m_index-1).assign_ka(l);
				//cout<<"\nka is assigned";
				}
				else if(temp=="Kd")
				{	mat.at(m_index-1).assign_kd(l);
				//cout<<"\nkd is assigned";
				}
				else if(temp=="Ks")
				{	mat.at(m_index-1).assign_ks(l);
				//cout<<"\nks is assigned";
				}
				else if(temp=="Ns")
				{	mat.at(m_index-1).assign_ns(l);
				//cout<<"\nns is assigned";
				}
				else if(temp=="n1")
				{	mat.at(m_index-1).assign_n1(l);
				//cout<<"\nns is assigned";
				}
				else if(temp=="Tr")
				{	mat.at(m_index-1).assign_Tr(l);
				//cout<<"\nns is assigned";
				}
				else if(temp=="Kr")
				{	mat.at(m_index-1).assign_Kr(l);
				//cout<<"\nns is assigned";
				}
				else if(temp=="Krf")
				{	mat.at(m_index-1).assign_Krf(l);
				//cout<<"\nns is assigned";
				}

				else if(temp=="newmtl")
				{
					ss>>temp;
					m_index++;
					goto a;
				}
				else
					continue;
			}

		}
		}
		//cout<<endl<<endl<<endl;

	}
	else
	{
		cout<<"material file not found.\nPlease check that file name is with proper extension and is in the same directory as obj file\n";
	}

	cout<<"total "<<mat.size()<<" material are loaded\n";

}

char* Read_objects:: get_filepath(char* file_name)
{
	//cout<<"\nextractiong file path";
	int pos=0;
	string temp=file_name;
	for(unsigned int i=0;i<temp.size();i++)
	{

		if(*file_name=='/')
		{
			pos=i;
		}
		file_name++;
	}
	file_name=file_name-temp.size();
	//cout<<"\npos is "<<pos<<endl;
	char* path;
	path = new char [pos+1];
	strncpy(path,file_name,pos);
	path[pos]='\0';
	/*for(int i=0;i<pos;i++)
	{
		path=*file_name;
		path++;
		file_name++;
	}
	 */

	return path;
}

void Read_objects:: pushback_g(string name)
{
	groups g;
	objects.push_back(g);
	objects.at(total_objects).assign_name(name,(total_objects));
	total_objects++;
}

void Read_objects:: pushback_e(string line ,int e_index )
{

	Sphere temp;
	temp.assign(line,current_mat_index);
	spheres.push_back(temp);

}


int Read_objects::get_group_index(string &name1)
{

	int ind=-1;
	for (int i=0;i< (int)objects.size();i++)
	{ ind=(objects.at(i)).get_index(name1);
		if(ind!=-1)
		{//cout<<"this is existed group"<<ind;
		return ind;
		}
	}
	cout<<"\ngroup "<<name1<<" doed not exist"<<endl;
	return -1;
}

int Read_objects::get_material_index(string &name1)
{
	//cout<<"gettin material index "<<name1<<endl;
	int ind=-1;
	for (int i=0;i< (int)mat.size();i++)
	{ ind=(mat.at(i)).get_index(name1);
		if(ind!=-1)
		{//cout<<"this is existed group"<<ind;
		return ind;
		}
	}
	cout<<"material "<<name1<<" doed not exist"<<endl;
	exit(1);
	return -1;
}

void Read_objects::face_errors(int &g_index,vector<int>&f)
{

	int total_f=objects.at(g_index).get_total_faces();
	string name=objects.at(g_index).get_name();
	//1. add vertices of 1st face to list.
	/*if (total_f==0)
		{
			//for(int i=0;i<(int)f.size();i++)
			//{
				objects.at(g_index-1).vertices_number.push_back(f.at(0));
			//}

		}
	//
	//2. from second face check whether particular vertex is already on list
	//else
	{	for(int i=0;i<(int)f.size();i++)
		{
				int flag1=0;

				//cout<<"no"<<endl;
				for(int j=0;j<(int)(objects.at(g_index-1).vertices_number.size() );j++)
				{
					//cout<<"yea"<<endl;
					if((f.at(i))==objects.at(g_index-1).vertices_number.at(j))
					{			//objects.at(g_index-1).vertices_number.push_back(f.at(i));
						flag1=1;
						break;
					}

				}
				if(flag1==0)
				{
					objects.at(g_index-1).vertices_number.push_back(f.at(i));
					cout<<f.at(i)<<endl;
				}
		}
	}*/
	//check face with less than two vertices
	if (f.size()<3)
	{
		cout<<endl<<"encountered face with less than 3 vertices"<<endl<<"check face number: "<<total_f+1<<" of group:"<<name<<endl;
		exit(1);
	}
	//check whether vertix number exist or not
	for(unsigned int i=0;i<f.size();i++)
	{
		if(f.at(i)>total_vertices)
		{
			cout<<"vertice number "<<f.at(i)<<" does not exist at all"<<endl;
			cout<<"check face number :"<<total_f+1<<" of group : "<<name<<endl;
			exit(1);
		}
	}

	vector<vectors>vect;
	convert2vectors(vect,f);
	/*for(int i=0;i<vect.size();i++)
	{
		vect.at(i).printvect();
	}*/

	bool good=check_colinear(vect);
	if(good==0)
	{
		cout<<endl<<"face number "<<total_f+1<<" of group "<<name<<" is co-linear"<<endl;
		exit(1);
	}
	if(vect.size()>3)
	{
		bool good1=check_coplanar(vect);
		if(good1==0)
		{
			cout<<endl<<"face number "<<total_f+1<<" of group "<<name<<" is not co-planar"<<endl;
			exit(1);
		}
	}
	bool good2=check_convex(vect);
	if(good2==0)
	{
		cout<<endl<<"face number "<<total_f+1<<" of group "<<name<<" is not convex"<<endl;
		exit(1);
	}


	//	check_coplanar(g_index,f);

}

void Read_objects:: convert2vectors(vector<vectors>&vect,vector<int>&f)
{
	int f_size=f.size();
	//vector<vectors>vect;
	for(int i=0;i<f_size-1;i++)
	{
		vector<double> value1 = ver.at(f.at(i)-1).get_values();
		vector<double> value2 = ver.at(f.at(i+1)-1).get_values();
		vector<double> value;
		for(int j=0; j<3;j++)
		{
			value.push_back(value2.at(j)-value1.at(j));
		}

		vectors v(value);
		vect.push_back(v);
	}
	vector<double> value1 = ver.at(f.back()-1).get_values();
	vector<double> value2 = ver.at(f.front()-1).get_values();
	vector<double> value;
	for(int j=0; j<3;j++)
	{
		value.push_back(value2.at(j)-value1.at(j));
	}
	vectors v(value);
	vect.push_back(v);



	//cout<<endl<<vect.size()<<endl;
}

bool Read_objects:: check_colinear(vector<vectors>vect)
{
	vect.push_back(vect.at(0));
	const double zero= 10e-6;
	for(unsigned int i=0;i<(vect.size()-1);i++)
	{
		vectors cross_pro;
		cross_pro.cross(vect.at(i),vect.at(i+1));
		double mag=cross_pro.magnitude();
		//vect.at(i).printvect();
		//vect.at(i+1).printvect();
		//cross_pro.printvect();
		//cout<<endl<<mag<<endl;
		if(mag<zero)
		{return 0;
		}
	}

	return 1;

}
bool Read_objects:: check_coplanar(vector<vectors>&vect)
{
	const double zero= 10e-6;

	vectors cross_pro;
	cross_pro.cross(vect.at(0),vect.at(1));
	for(unsigned i=2;i<vect.size();i++)
	{
		double dot= cross_pro.dot(vect.at(i));
		dot = dot*dot;
		dot=sqrt(dot);
		if(dot>zero)
		{
			return 0;
		}
	}
	return 1;
}
bool Read_objects:: check_convex(vector<vectors>&vect)
{
	vect.push_back(vect.at(0));
	//const double zero= 10e-6;
	vector<vectors>all_cross;
	for(unsigned int i=0;i<(vect.size()-1);i++)
	{
		vectors local_cross;
		local_cross.cross(vect.at(i),vect.at(i+1));
		//vect.at(i).printvect();
		//vect.at(i+1).printvect();
		//local_cross.printvect();

		all_cross.push_back(local_cross);
	}

	for(unsigned int i=0;i<(all_cross.size()-1);i++)
	{
		double dot1= all_cross.at(i).dot(all_cross.at(i+1));
		if(dot1<0)
		{
			return 0;
		}

	}
	return 1;
}

Read_objects::~Read_objects() {
	// TODO Auto-generated destructor stub
}

/* namespace std */
