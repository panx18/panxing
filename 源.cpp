#include<iostream>
#include<algorithm>
#include<Windows.h>
#include<conio.h>
#include<vector>
#include<string>
#include<fstream>
#include<iomanip>
#pragma warning(disable:4996)
using namespace std;
int recordnum=0;
//record:getGPA  stu:getaveGPA  CLASS:getclassGPA
void charpro(char a,int n,int t)
{
	for(int i=0;i<n;i++)
	{
		Sleep(t);
		cout<<a;
	}
}

class record
{
private:
	char name[20];
	int ID;
	char sex[6];
	int gradenum;//grade number;
	int classnum;//class number;
	char course[30];
	double score;
	double GPA;
	char rank[6];
public:
	void setrecord();
	record(){strcpy(name,"none");}
	string getname(){string a;a=name;return a;}
	string getsex(){string a;a=sex;return a;}
	string getcourse(){string a;a=course;return a;}
	string getrank(){string a;a=rank;return a;}
	double getscore(){return score;}
	double getgpa(){return GPA;}
	int getID(){return ID;}
	int getgradenum(){return gradenum;}
	int getclassnum(){return classnum;}
	void mark(double a);
	friend ostream& operator<<(ostream &output,record &t);
	
};
void record::mark(double a)
{
	if(a>=95) {GPA=4.0;strcpy(rank,"A");}
	else if(a>=90&&a<95) {GPA=3.7;strcpy(rank,"A-");}
	else if(a>=85&&a<90) {GPA=3.3;strcpy(rank,"B+");}
	else if(a>=80&&a<85) {GPA=3.0;strcpy(rank,"B");}
	else if(a>=70&&a<80) {GPA=2.7;strcpy(rank,"B-");}
	else {GPA=2.3;strcpy(rank,"C");}
}
void record::setrecord()
{  Sleep(500);
	cout<<"输入记录：姓名、 学号、 性别、 年级、 班级、 课程名称、 得分 "<<endl;
	charpro('-',60,10);
	cout<<endl;
	cin>>name>>ID>>sex>>gradenum>>classnum>>course>>score;
	charpro('-',60,10);
	mark(score);
}
ostream& operator<<(ostream &output,record &t)
{
	cout<<t.name<<" "<<t.ID<<" "<<t.sex<<" "<<t.gradenum<<" "<<t.classnum<<" "<<t.course<<" "<<t.score<<endl;
	return output;
}

class stu
{
private:
	string NAME;
	double aveGPA;
	record x[20];
	int stuID;
	string stusex;
	int NUM;
public:
	stu(vector<record>&RECORD,int &recordnum,string s="NONE");
	stu(vector<record>&RECORD,int &recordnum,int id);
	stu(){NAME="NONE";}
	int getNUM(){return NUM;}//如果NUM=-1，那么就是没有他的信息！
	void setaveGPA();
	double getaveGPA()const{return aveGPA;}
	string getname()const{string temp;temp=NAME;return temp;}
	friend ostream&operator<<(ostream&output,stu &s);        //重载了操作符<<，用来输出学生的信息，而且当不存在学生信息的时候会有提示。
};
stu::stu(vector<record>&RECORD,int &recordnum,string s)
{   NUM=-1;
    NAME=s;
	for(int i=0;i<recordnum;i++)
		if(NAME==RECORD[i].getname())
			{++NUM;x[NUM]=RECORD[i];}
	setaveGPA();
}
stu::stu(vector<record>&RECORD,int &recordnum,int id)
{
	NUM=-1;
	stuID=id;
	for(int i=0;i<recordnum;i++)
		if(stuID==RECORD[i].getID())
		{++NUM;x[NUM]=RECORD[i];}
	setaveGPA();
}	
void stu::setaveGPA()
{   aveGPA=0.0;
	for(int i=0;i<=NUM;i++)
		aveGPA+=x[i].getgpa();
	aveGPA/=(NUM+1);

}
ostream &operator<<(ostream &output,stu &s)
{
	if(s.NUM==-1)
	{output<<"没有查找到这个学生！"<<endl;}
	else
	{   output<<s.x[0].getname()<<"  "<<"性别："<<s.x[0].getsex()<<" "<<"学号："<<s.x[0].getID()<<endl<<endl;
	 for(int i=0;i<=s.NUM;i++)
	 {  output<<i+1<<"."<<setw(12)<<setiosflags(ios_base::left)<<s.x[i].getcourse()<<setw(7)<<s.x[i].getscore()<<setw(8)<<s.x[i].getgpa()<<s.x[i].getrank()<<endl;}
	}
	output<<endl<<"平均GPA为："<<setprecision(3)<<s.aveGPA<<endl;
	return output;
}

class CLASS
{
public:
	CLASS(int gradenum,int classnum,vector<record>&RECORD,int &recordnum);
	~CLASS(){}
	double getclassgpa();
	double getvariance();
	void printclass();
private:
	double classgpa;
	double variance;
	int classsize;
	string namelist[50];   //储存了这个班级的学生名单
    vector<stu>myclass;   //将班级中的每个学生都生成一个stu对象
	
};
bool compare(const stu &a,const stu &b)
{
	if(a.getaveGPA()>b.getaveGPA())
		return 1;
	if(a.getaveGPA()<b.getaveGPA())
		return 0;
	if(a.getname()>b.getname())
		return 1;
	return 0;
}
CLASS::CLASS(int gradenum,int classnum,vector<record>&RECORD,int &recordnum)
{   myclass.resize(1);
	string tempname;             ///这个用来临时储存是该班级的学生的名字，当然还要求和已有学生名字进行比对，防止重名
	classsize=0;
	for(int j=0;j<recordnum;j++)   ///对容器中的记录进行遍历，首先找到属于该班级的记录，用临时String类存储姓名，在与已经存储的姓名进行比对
		{  
			bool flag=1;
			if(RECORD[j].getclassnum()==classnum&&RECORD[j].getgradenum()==gradenum)  ///如果情况符合，进行比对环节. 
			{  
			tempname=RECORD[j].getname();
			
			for(int i=1;i<=classsize;i++)
				if(namelist[i]==tempname) flag=0;         //和已经得到的学生姓名进行比对
			if(flag)
			{namelist[++classsize]=tempname;}
			}
		}
	
	for(int i=1;i<=classsize;i++)      ///塞进myclass容器中
		{myclass.push_back(stu (RECORD,recordnum,namelist[i]));}
	
	sort(myclass.begin(),myclass.end(),compare);   ///进行排序
}
double CLASS::getclassgpa()
{
	classgpa=0;
	for(int i=0;i<classsize;i++)
		classgpa+=myclass[i].getaveGPA();
	classgpa/=classsize;
	return classgpa;
}
double CLASS::getvariance()
{
	variance=0;
	for(int i=0;i<classsize;i++)
		variance+=((myclass[i].getaveGPA()-classgpa)*(myclass[i].getaveGPA()-classgpa));
	variance/=classsize;
	return variance;
}
void CLASS::printclass()
{   if(classsize==0){}
    else
    {
	 for(int i=0;i<classsize;i++)
	   {
		cout<<i+1<<" ";cout.width(15);cout<<setiosflags(ios_base::left)<<myclass[i].getname()<<"  "
			<<"平均GPA: "<<myclass[i].getaveGPA()<<endl;

	    }
	 cout<<"班级平均GPA为： "<<getclassgpa()<<endl;
	 cout<<"方差为： "<<getvariance()<<endl;
    }
}

class COURSE:public record
{
private:
	string coursename;
	double coursegpa;
	double coursevariance;
public:
	int NUM[300];
	int number;
	COURSE(vector<record>&RECORD,int &recordnum);
	~COURSE(){}
	void printcourse(vector<record>&RECORD);
	double getcoursegpa(vector<record>&RECORD);
	double getcoursevariance(vector<record>&RECORD);
};
COURSE::COURSE(vector<record>&RECORD,int &recordnum)
{   number=-1;
	cout<<"请输入课程名称:"<<endl;
	cin>>coursename;
	for(int i=0;i<recordnum;i++)
	{
		if(RECORD[i].getcourse()==coursename)
		{
		++number;NUM[number]=i;}
	}
	if(number==-1)
		cout<<"没有该课程信息！"<<endl;
}
void COURSE::printcourse(vector<record>&RECORD)
{
	if(number!=-1)
	for(int k=0;k<=number;k++)
		{cout<<k<<" ";
		 cout<<RECORD[NUM[k]];}
}
double COURSE::getcoursegpa(vector<record>&RECORD)
{
	coursegpa=0;
	for(int i=0;i<number;i++)
		coursegpa+=RECORD[NUM[i]].getgpa();
	coursegpa/=number;
	return coursegpa;
}
double COURSE::getcoursevariance(vector<record>&RECORD)
{
	coursevariance=0;
	for(int i=0;i<number;i++)
		coursevariance+=((RECORD[NUM[i]].getgpa()-coursegpa)*(RECORD[NUM[i]].getgpa()-coursegpa));
	coursevariance/=number;
	return coursevariance;
}

void input(vector<record>&RECORD,int &recordnum) ///主要思想：首先改变容器，最后将整个容器的值重新输入到文件中，之后的操作直接对容器进行即可
{   Sleep(100);
	record temp;
    char flag;
	do  
 	{   temp.setrecord();RECORD.push_back(temp);recordnum++;
	    cout<<"现在容器中元素的数量为："<<recordnum;
		cout<<endl<<"是否继续输入? yes/no(1/0)"<<endl;
		flag=getch();
		while(flag!='1'&&flag!='0')
		flag=getch();
	}while(flag=='1');
}
void searchstu(vector<record>&RECORD,int &recordnum)
{   
	cout<<"输入学生姓名："<<endl;
	string s;
	cin>>s;
	cout<<"查询中";
	charpro('.',5,200);
	cout<<endl<<endl;
	stu astudent(RECORD,recordnum,s);
	cout<<astudent;
}
void searchclass(vector<record>&RECORD,int &recordnum)
{
	cout<<"请输入年级、班号：";
	int a,b;
	cin>>a>>b;
	CLASS aclass(a,b,RECORD,recordnum);
	aclass.printclass();
}
void searchcourse(vector<record>&RECORD,int &recordnum,bool flag)
{
	if(recordnum==0)
		cout<<"没有记录可供查找！"<<endl;
	else
		{
			COURSE mycourse(RECORD,recordnum);
			mycourse.printcourse(RECORD);
			if(mycourse.number!=-1)
			{
			if(flag==true)
			{
			cout<<"请输入需要修改的课程编号："<<endl;
			char k;
			k=getch();
			while(k-'0'<0||k-'0'>mycourse.number)
				k=getch();
			RECORD[mycourse.NUM[k-'0']].setrecord();
			}
			}
	    }
}
void modify(vector<record>&RECORD,int &recordnum)
{
	searchcourse(RECORD,recordnum,true);
}
void menu(vector<record>&RECORD,int &recordnum)
{   
	cout<<"            欢迎进入学生成绩管理系统！"<<endl;
	charpro('>',50,10);
	Sleep(500);
	cout<<endl;
	char flag='0';
	while(flag=='0')
	{
	cout<<"0.清除所有数据"<<endl
	    <<"1.输入信息"<<endl
	    <<"2.查询学生成绩"<<endl
	    <<"3.查询班级信息"<<endl
		<<"4.查询课程信息"<<endl
	    <<"5.修改信息"<<endl;
	charpro('*',60,3);
	cout<<endl;

	char m;
	m=getch();
	while(m!='0'&&m!='1'&&m!='2'&&m!='3'&&m!='4'&&m!='5')
		m=getch();

	switch(m)
	{
	case('0'):{ofstream outfile("123.txt",ios_base::trunc|ios_base::binary);outfile.close();RECORD.clear();recordnum=0;break;}
	case('1'):input(RECORD,recordnum);break;
	case('2'):searchstu(RECORD,recordnum);break;
	case('3'):searchclass(RECORD,recordnum);break;
	case('4'):searchcourse(RECORD,recordnum,false);break;
	case('5'):modify(RECORD,recordnum);break;
	}
	cout<<endl;
	cout<<"返回主菜单/退出系统（0/1)"<<endl;
	flag=getch();
	while(flag!='1'&&flag!='0')
	  flag=getch();
	}
}
void copy(vector<record>&RECORD,int &recordnum)       ///copy the data from the file
{  
	ifstream infile("123.txt",ios_base::in|ios_base::binary);
   if(infile.good())
   {
	   record tempre;
	   while(1)
	   {
		   infile.read((char *)&tempre,sizeof(record));
		   if(!infile.good())
			   break;
		   RECORD.push_back(tempre);
		   recordnum++;
	   }
		   infile.close();
   }
	   else
		   cout<<"cannot open the file!";
}
void write(vector<record>&RECORD,int &recordnum)
{
	ofstream outfile("123.txt",ios_base::trunc|ios_base::binary);
	if(outfile.good())
	{
		for(int i=0;i<recordnum;i++)
			outfile.write((char *)&RECORD[i],sizeof(record));
	}
	outfile.close();
}
void displayrecord(vector<record>&RECORD,int &recordnum)
{
	for(int i=1;i<=recordnum;i++)
		cout<<RECORD[i];
}
int main()
{  
   int recordnum=0;
   vector<record>RECORD;

   copy(RECORD,recordnum);

   cout<<"现有的总记录数为："<<recordnum<<endl;
   menu(RECORD,recordnum);
   
   write(RECORD,recordnum);
   cout<<"现有的总记录数为："<<recordnum<<endl;
   return 0;
}