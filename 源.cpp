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
	cout<<"�����¼�������� ѧ�š� �Ա� �꼶�� �༶�� �γ����ơ� �÷� "<<endl;
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
	int getNUM(){return NUM;}//���NUM=-1����ô����û��������Ϣ��
	void setaveGPA();
	double getaveGPA()const{return aveGPA;}
	string getname()const{string temp;temp=NAME;return temp;}
	friend ostream&operator<<(ostream&output,stu &s);        //�����˲�����<<���������ѧ������Ϣ�����ҵ�������ѧ����Ϣ��ʱ�������ʾ��
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
	{output<<"û�в��ҵ����ѧ����"<<endl;}
	else
	{   output<<s.x[0].getname()<<"  "<<"�Ա�"<<s.x[0].getsex()<<" "<<"ѧ�ţ�"<<s.x[0].getID()<<endl<<endl;
	 for(int i=0;i<=s.NUM;i++)
	 {  output<<i+1<<"."<<setw(12)<<setiosflags(ios_base::left)<<s.x[i].getcourse()<<setw(7)<<s.x[i].getscore()<<setw(8)<<s.x[i].getgpa()<<s.x[i].getrank()<<endl;}
	}
	output<<endl<<"ƽ��GPAΪ��"<<setprecision(3)<<s.aveGPA<<endl;
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
	string namelist[50];   //����������༶��ѧ������
    vector<stu>myclass;   //���༶�е�ÿ��ѧ��������һ��stu����
	
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
	string tempname;             ///���������ʱ�����Ǹð༶��ѧ�������֣���Ȼ��Ҫ�������ѧ�����ֽ��бȶԣ���ֹ����
	classsize=0;
	for(int j=0;j<recordnum;j++)   ///�������еļ�¼���б����������ҵ����ڸð༶�ļ�¼������ʱString��洢�����������Ѿ��洢���������бȶ�
		{  
			bool flag=1;
			if(RECORD[j].getclassnum()==classnum&&RECORD[j].getgradenum()==gradenum)  ///���������ϣ����бȶԻ���. 
			{  
			tempname=RECORD[j].getname();
			
			for(int i=1;i<=classsize;i++)
				if(namelist[i]==tempname) flag=0;         //���Ѿ��õ���ѧ���������бȶ�
			if(flag)
			{namelist[++classsize]=tempname;}
			}
		}
	
	for(int i=1;i<=classsize;i++)      ///����myclass������
		{myclass.push_back(stu (RECORD,recordnum,namelist[i]));}
	
	sort(myclass.begin(),myclass.end(),compare);   ///��������
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
			<<"ƽ��GPA: "<<myclass[i].getaveGPA()<<endl;

	    }
	 cout<<"�༶ƽ��GPAΪ�� "<<getclassgpa()<<endl;
	 cout<<"����Ϊ�� "<<getvariance()<<endl;
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
	cout<<"������γ�����:"<<endl;
	cin>>coursename;
	for(int i=0;i<recordnum;i++)
	{
		if(RECORD[i].getcourse()==coursename)
		{
		++number;NUM[number]=i;}
	}
	if(number==-1)
		cout<<"û�иÿγ���Ϣ��"<<endl;
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

void input(vector<record>&RECORD,int &recordnum) ///��Ҫ˼�룺���ȸı��������������������ֵ�������뵽�ļ��У�֮��Ĳ���ֱ�Ӷ��������м���
{   Sleep(100);
	record temp;
    char flag;
	do  
 	{   temp.setrecord();RECORD.push_back(temp);recordnum++;
	    cout<<"����������Ԫ�ص�����Ϊ��"<<recordnum;
		cout<<endl<<"�Ƿ��������? yes/no(1/0)"<<endl;
		flag=getch();
		while(flag!='1'&&flag!='0')
		flag=getch();
	}while(flag=='1');
}
void searchstu(vector<record>&RECORD,int &recordnum)
{   
	cout<<"����ѧ��������"<<endl;
	string s;
	cin>>s;
	cout<<"��ѯ��";
	charpro('.',5,200);
	cout<<endl<<endl;
	stu astudent(RECORD,recordnum,s);
	cout<<astudent;
}
void searchclass(vector<record>&RECORD,int &recordnum)
{
	cout<<"�������꼶����ţ�";
	int a,b;
	cin>>a>>b;
	CLASS aclass(a,b,RECORD,recordnum);
	aclass.printclass();
}
void searchcourse(vector<record>&RECORD,int &recordnum,bool flag)
{
	if(recordnum==0)
		cout<<"û�м�¼�ɹ����ң�"<<endl;
	else
		{
			COURSE mycourse(RECORD,recordnum);
			mycourse.printcourse(RECORD);
			if(mycourse.number!=-1)
			{
			if(flag==true)
			{
			cout<<"��������Ҫ�޸ĵĿγ̱�ţ�"<<endl;
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
	cout<<"            ��ӭ����ѧ���ɼ�����ϵͳ��"<<endl;
	charpro('>',50,10);
	Sleep(500);
	cout<<endl;
	char flag='0';
	while(flag=='0')
	{
	cout<<"0.�����������"<<endl
	    <<"1.������Ϣ"<<endl
	    <<"2.��ѯѧ���ɼ�"<<endl
	    <<"3.��ѯ�༶��Ϣ"<<endl
		<<"4.��ѯ�γ���Ϣ"<<endl
	    <<"5.�޸���Ϣ"<<endl;
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
	cout<<"�������˵�/�˳�ϵͳ��0/1)"<<endl;
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

   cout<<"���е��ܼ�¼��Ϊ��"<<recordnum<<endl;
   menu(RECORD,recordnum);
   
   write(RECORD,recordnum);
   cout<<"���е��ܼ�¼��Ϊ��"<<recordnum<<endl;
   return 0;
}