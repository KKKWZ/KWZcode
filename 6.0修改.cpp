#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h> 
#include<math.h>
#include <conio.h>
#include<ctype.h> 
#include<time.h> 
#define N 20
#define  SIZE  1000 
#define bool int
#define TRUE  1
#define FALSE 0

bool judge=TRUE;
FILE *fp;
char nam[80] ,pas[80];
char textstring[80];
int ok=0;


struct student_infor {
    char num[10];//学号 
    char name[20];//姓名 
    char sex[10];//性别 
    int age;//年龄 
    char major[20];//专业
	int math;//高数成绩
	int English;//英语成绩
	int Clanguage;//C语言成绩 
	int sum;//总分
	double average;//平均分 
    struct student_infor *next;
}stu[SIZE];


//管理员密码结构体
typedef struct leader{
    char name[100];
    char mima[100];
}lead; 


//学生登录密码结构体 
typedef struct 
{
    char suser[1000];
    char scode[1000]; 
}susers;
susers s;



void Window(char *);//初始窗口和界面 
void initleader(lead* );
void zhuce2();
int teacherdenglu(void); 
void zhuce3();
void studentdenglu();
void write3();
void captcha(char str[],int );//验证码
void login();//登录
void menu();//管理员菜单 
void menue(); //学生菜单
void judgement1();
void judgement2();
int infor_input(void);//录入 
int infor_show(void);//显示 
int infor_search(void);//查询 
int infor_add(void);//添加 
void infor_change();//修改 
int infor_delete(void);//删除
int infor_paixu(void);//排序
int infor_tongji1(void);//统计
int infor_tongji2(void); 
int out(void);//退出 







//一、初始窗口和界面
void Window(char *title){
	//设置窗口大小
	system("mode con:cols=90 lines=200");
	//设置窗口字体的颜色
	system("color 4E");
	//循环输出标题（条件：）
	while(*title!=0)
	{
		//输出字符指针所指向的内容
		printf("%c",*title);
		//将指针指向下一个字符
		title++;
		//休眠 
		Sleep(50);
	}
}


//管理员登录 
void initleader(lead* lea){
    printf("\n\n\n\t\t\t初次登录，请设置管理员信息：");
    printf("\n\t\t\t账号：");
    scanf("%s",lea->name);
    printf("\n\t\t\t密码：");
    scanf("%s",lea->mima);
    printf("\n\t\t\t设置完成，按任意键进入系统...");
	getch(); 
}


void initdata(lead* lea){
	
	//打开文件 
    FILE *fp = fopen("guanliyuan.txt","rt");
   //读取上次的管理员信息 
	fread(lea,sizeof(lead),1,fp );
    
    
    fclose(fp);
}


void readdata(lead* lea){
    FILE *fp = fopen("guanliyuan.txt","rt");
    if(fp == NULL){
    	//如果打不开，则证明是第一次使用，提示初始化管理员信息 
        initleader(lea);
        return;
    }
	else{
        fclose(fp);
        //如果打开了，就不是第一次使用 
        initdata(lea);
    }
}


int yanzhengleader(lead* lea){
	char a[100],b[100];
	char code[N],str[N];
    system("CLS");
    printf("\n\n\n\t\t\t需要进行管理员验证：");
    printf("\n\n\n\n\t\t\t请输入账号：");
    scanf("%s",a);
    printf("\n\n\n\n\t\t\t请输入密码：");
    scanf("%s",b);
    if((strcmp(a,lea->name ) == 0) && (strcmp(b,lea->mima) == 0) ){
        while(1){
        	captcha(code,4);
            printf("\n\n\n\n\t\t\t请输入验证码：%s\n",code);
            printf("\t\t\t\t");
            scanf("%s",str);
            printf("\t\t=========================================================================================\n");
            if(strcmp(code,str)==0){
			
            	gets(a);return 1;}
			
		}
			
			
    }
    else gets(a); return 0;

}


void savedata(lead* lea){
	//以只写的形式打开 
    FILE *fp = fopen("guanliyuan.txt","w");
	//写入管理员信息 
	fwrite(lea,sizeof(lead),1,fp);
    
    fclose(fp);
}

void print() {
    printf("   _______________________________________\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |                请选择                |\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |         我已注册过——请按 0         |\n");
    printf("   |                                      |\n");
    printf("   |         我是新用户——请按 1         |\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |______________________________________|\n");
    printf("请输入");
}
void zhuce2(){
    FILE *fp=fopen("user.txt","w");/*以写模式("w")打开文件user.txt,如果不存在,会自动创建*/
    printf("请输入账号");
    gets(nam);
    printf("请输入密码");
    gets(pas); /*输入名称和密码*/
    fputs(nam,fp);
    fputs(pas,fp);/*将名称和密码以字符串形式写入文件*/
    fputs("\n",fp);
    fflush(stdin);//清除缓存
    fclose(fp);/*关闭文件*/
    teacherdenglu();//注册完转到登录界面
}

int teacherdenglu(void){
	system("CLS");
	fflush(stdin);
    printf("登录界面\n");
    printf("请输入账号");
    gets(nam);
    fflush(stdin);
    printf("请输入密码");
    gets(pas); /*输入名称和密码*/
    strcat(nam,pas);//合并字符
    strcat(nam,"\n");//添加换行字符
     int len = 0;

    FILE *fp = fopen("user.txt", "r");
    if(NULL == fp)
    {
        printf("failed to open dos.txt\n");
        return 1;
    }

    while(!feof(fp))
    {
        memset(textstring, 0, sizeof(textstring));
        fgets(textstring, sizeof(textstring) - 1, fp); // 包含了\n
        if(strcmp(nam,textstring)==0){//判断字符是否相等
           ok=1;
           break;
        }
    }
    if(ok){
	
    	printf("登录OK");
  		menu();
  }
    else
	
	
    printf("登录失败");
	login();

	fclose(fp);
    

}

//学生注册 
void zhuce3(){
	system("CLS");
	FILE *fp;
	char temp[100];
	do
	{
		printf("\t\t\t\t用户注册\n\t\t用户名：");
		scanf("%s",s.suser);
		fp=fopen(s.suser,"r");
		//判断用户名是否重复
		if(fp!=NULL)
		{
			printf("\n\t该用户已存在");
			fclose(fp);
			printf("\n\t继续注册？(Y/N)");
			if(getch()=='Y') 
				return zhuce3();
			else 
				return studentdenglu();  
		 }
		//确认两次密码输入是否一致
		printf("\n\t\t密码：");
		scanf("%s",s.scode); 
		printf("\n\t\t确认密码:");
		scanf("%s",temp);
		if(strcmp(s.scode,temp)!=0)
			printf("\n\t\t两次密码输入不一致，请重新输入\n"); 
	}while(strcmp(s.scode,temp)!=0);
	//用户名密码无误，写入文档储存用户信息
	fp=fopen(s.suser,"w");
	if(fp==NULL)
	{
		printf("\n\t注册失败\n");
		exit(0);
	}
	else
	{
		system("CLS");
		printf("\n\t注册成功");
		write3();
		judge = FALSE;
		studentdenglu();
	} 
}

void write3()
{
	
	if(fwrite(&s,sizeof(s.suser),1,fp)!=1)
	{
		printf("\n\t\t写入文件错误\n");	
	}
}

//学生登录 
void studentdenglu(){

	char u[1000],c[1000],temp[1000];
	printf("\n\t\t\t\t用户登录");
	printf("\n\t\t用户名：");
	scanf("%s",u);
	//判断用户名是否存在
	fp=fopen(u,"r+");
	temp[0]='0';
	if(fp==NULL)
	{
		printf("\n\t\t用户不存在，请注册");
		printf("\n\t\t1.注册	2.重新登录");
		temp[0]=getch();
		if(temp[0]=='1')
		{
			system("CLS");
			zhuce3();
		}
		else
			return studentdenglu();
	} 
	//验证密码是否正确
	do{
	
		if(judge==TRUE)
			fread(&s,sizeof(susers),1,fp);
			
			printf("\t\t密码：");
			scanf("%s",c);
			if(strcmp(s.scode,c)!=0)
			{
				printf("\n\t\t密码错误(1.退出 2.重新输入)");
				temp[0]=getch();
				printf("\n");
				if(temp[0]=='1')
				{
					fclose(fp);
					return login();
				}
		 }
		if(strcmp(s.scode,c)==0){
			printf("登陆成功！");
			Sleep(2000);
			menue();
		}	
		}while(temp[0]=='2');
			
			
		 
}



//二、密码登录
void login(){
	
	system("CLS");
	system("color 37");
	printf("请选择登录方式：\n1.管理员登录\n2.教师登录\n3.学生登录\n\n");
	int n,j=0;
	int settle=0;
    char c,password[6];
	scanf("%d",&n);
	switch(n){
		case 1: system("CLS");
				lead* lea;
				
			//申请一个管理员结点来保存管理员的信息 
    			lea = (lead*)malloc(sizeof(lead));
   			
    			readdata(lea);
    			//验证管理员函数 
    			while(yanzhengleader(lea) == 0);
    			savedata(lea);
    			while(1){
    				menu();
    				
				}
				break;
		case 2: print();
			    scanf("%d",&settle);
    			fflush(stdin);//清除缓存
    			if(settle)
       				zhuce2();
    			else
    				teacherdenglu();
				break;
      	case 3: zhuce3();
      			break;
		   
		}
	
}

//管理员菜单 
void menu(){
	system("CLS");
	system("mode con:cols=250 lines=300");
	system("color 1F");
	printf("\t\t**********************\n\n");
	printf("\t\t学生管理系统\n\n");
	printf("1.录入学生成绩\n\n");
	printf("2.显示学生成绩\n\n");
	printf("3.查询学生成绩\n\n");
	printf("4.添加学生成绩\n\n");
	printf("5.修改学生成绩\n\n");
	printf("6.删除学生成绩\n\n");
	printf("7.学生成绩排序\n\n");
	printf("8.学生成绩统计\n\n");
	printf("9.退出当前登录\n\n"); 
	printf("0.退出系统\n\n");
	printf("\n\n请选择(0~9):\n\n");
	printf("\t\t**********************\n\n");
	
	int choose;
	
	while(1)
	{
		scanf("%d",&choose);
		switch(choose)
        {
            case 1:	system("CLS");
					infor_input();
					judgement1();
					break;
 			case 2: system("CLS");
			 		infor_show();
			 		judgement1();
					break;
			case 3: system("CLS");
					infor_search();
					judgement1();
					break;
			case 4: system("CLS");
					infor_add();
					judgement1();
			case 5: system("CLS");
					infor_change();
					judgement1();
					break;
			case 6: system("CLS");
					infor_delete();
					judgement1();
					break;
			case 7: system("CLS");
					infor_paixu();
					break;
			case 8: system("CLS");
				    infor_tongji1();
				    break;
			case 9: system("CLS");
					login();
					break;
            case 0:	system("CLS");
                    system("color 0C");
    				out();
                    exit(0);   
                    break;
			default:printf("您输入了一个无效的选择，请重新输入(0-9):\n ");
        			continue;
            }
            system("PAUSE");
        }
	
        
    
	
	
}




//学生菜单
void menue(){
	system("CLS");
	system("mode con:cols=250 lines=300");
	system("color 1F");
	printf("\t\t**********************\n\n");
	printf("\t\t欢迎进入学生管理系统\n\n");
	printf("1.显示学生成绩\n\n");
	printf("2.查询学生成绩\n\n");
	printf("3.学生成绩排序\n\n");
	printf("4.学生成绩统计\n\n");
	printf("5.退出当前登录\n\n"); 
	printf("0.退出系统\n\n");
	printf("\n\n请选择(0~5):\n\n");
	printf("\t\t**********************\n\n");
	
	int choose;
	
	while(1)
	{
		scanf("%d",&choose);
		switch(choose)
        {
 			case 1: system("CLS");
			 		infor_show();
			 		judgement2();
					break;
			case 2: system("CLS");
					infor_search();
					judgement2();
					break;
			case 3: system("CLS");
					infor_paixu();
					break;
			case 4: system("CLS");
				    infor_tongji2();
				    break;
			case 5: system("CLS");
					login();
					break;
            case 0:	system("CLS");
                    system("color 0C");
    				out();
                    exit(0);   
                    break;
			default:printf("您输入了一个无效的选择，请重新输入(0-5):\n ");
        			continue;
            }
            system("PAUSE");
        }
	
        
    
	
	
} 



//判断
void judgement1(){
	int m;
	printf("\n返回上一级菜单请按1，退出请按0: ");
    scanf("%d", &m);

    if (m == 0) 
	{
        system("CLS");
        system("color 0C");
    	out();
    	Sleep(1000);
		exit(0);
    }


    if (m == 1) 
	{
        	menu();
            
    } 
} 


void judgement2(){
	int m;
	printf("\n返回上一级菜单请按1，退出请按0: ");
    scanf("%d", &m);

    if (m == 0) 
	{
        system("CLS");
        system("color 0C");
    	out();
    	Sleep(1000);
		exit(0);
    }


    if (m == 1) 
	{
        menue();
            
    } 
}



int out(void)
{
	printf("\n\n\n\n\t\t\t\t\t\t\t\t\t感谢使用！\n");
	printf("\n\n\n\n\t\t\t\t\t\t\t\t\tSee you again.\n");
	printf("\n\n\n\n\t\t\t\t\t\t\t\t\tKWZ.\n");
}

// 1. 学生信息录入
int infor_input(void)
{
	system("color 80");
	FILE *fp;  
    fp=fopen("studentinfor.txt","wb");  
    if(fp==NULL)  
    {  
        printf(" cannot open file studentinfor.txt\n");  
        exit(0);  
    }  
    printf("输入要录入的学生数目：\n");  
    int n;  
    scanf("%d", &n);   
    for(int i = 0; i < n; i++)  
    {        
		  
        int len=0;
		while(1)
		{	
			
			printf("\n请输入要录入的学生信息的学号(8位)：");
			scanf("%s",stu[i].num);
			len=strlen(stu[i].num);
			if(strcmp(stu[i].num,stu[i-1].num)==0)
			{
				printf("该学生已存在！请重新输入"); 
			}
			
			int l=0,j;
			for(j=0;j<len;j++){
			
				if(!((stu[i].num[j]>57)||(stu[i].num[j]<48)))
					l++;}
			if(l==len&&len==8)
			{	
							break;
				
			}
			else printf("输入有误！");
		}
	printf("\n请输入要录入的学生信息的姓名：");
	scanf("%s",stu[i].name);
	while(1)
	{
		printf("\n请输入要录入的学生信息的性别(男或女):");
		scanf("%s",stu[i].sex);
		if(strcmp(stu[i].sex,"男")==0||strcmp(stu[i].sex,"女")==0)
		{
			break;
		}
		else printf("输入有误！");
	}
	while(1){
		int r;
		printf("\n请输入要录入的学生信息的年龄：");
		r = scanf("%d",&stu[i].age);
		if(r==1&&stu[i].age>0 && stu[i].age<100)
		{
			break;
		}
		else printf("输入有误！");
		
	}
	printf("\n请输入要录入的学生信息的专业：");
	scanf("%s",stu[i].major);
	while(1){
		int r;
		printf("\n请输入要录入的学生的高数成绩：");
		r = scanf("%d",&stu[i].math);
		if(r==1&&stu[i].math>=0 && stu[i].math<=100)
		{
			break;
		}
		else printf("输入有误！");
			fflush(stdin);
		}
	while(1){
		int r;
		printf("\n请输入要录入的学生的英语成绩：");
		r = scanf("%d",&stu[i].English);
		if(r==1&&stu[i].English>=0 && stu[i].English<=100)
		{
			break;
		}
		else printf("输入有误！");
			fflush(stdin);
		}
	while(1){
		int r;
		printf("\n请输入要录入的学生的C语言成绩：");
		r=scanf("%d",&stu[i].Clanguage);
		if(r==1&&stu[i].Clanguage>=0 && stu[i].Clanguage<=100)
		{
			break;
		}
		else printf("输入有误！");
		fflush(stdin);
	}
	stu[i].sum = stu[i].math + stu[i].English + stu[i].Clanguage;  
    stu[i].average = stu[i].sum / 3.0;
	printf("\n信息已经录入系统！"); 
      
    }
	
    for (int i = 0; i < n; i++)  
        if (fwrite(&stu[i], sizeof(struct student_infor),1,fp)!=1)  
            printf("file write error!\n");        
    fclose(fp);
	
}




//2.显示学生信息
int infor_show()
{ 
    FILE  *fp;  
    int  i;  
    fp=fopen("studentinfor.txt","rb");                                           
    printf("※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n");  
    printf("                                  成绩列表\n");  
    printf("-----------------------------------------------------------------------------------\n");  
    printf("学号 	  姓名    性别   年龄    专业		高数	英语    C语言成绩    总成绩    平均成绩\n");  
    printf("-----------------------------------------------------------------------------------\n");        
	for(i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++)//for(i=0;fread(&stu[i],6,1,fp)==1;i++)  
    {  
    printf("%6s%10s%3s%10d%10s%10d%10d%10d%10d    %.2lf\n",stu[i].num,stu[i].name,stu[i].sex,stu[i].age,stu[i].major,stu[i].math,stu[i].English,stu[i].Clanguage,stu[i].sum,stu[i].average);  
    }  
	printf("-----------------------------------------------------------------------------------\n\n");  
    printf("※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n");  
    fclose(fp);  
	
	
} 



//3.查询学生信息
int infor_search(){
	FILE  *fp;  
    char  num[10];  
    fp=fopen("studentinfor.txt","rb");          
    printf("请输入要查找的学号:");  
    scanf("%s",&num);  
    printf("※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n");  
    printf("                                            查询结果\n");  
    printf("-----------------------------------------------------------------------------------\n");  
    printf("学号      姓名        性别        专业    	高数	    英语      C语言     总成绩     平均成绩\n");  
    printf("-----------------------------------------------------------------------------------\n");  
    for(int i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++)  
        if(strcmp(stu[i].num,num)==0) 
        {  
    	    printf("%6s%10s%3s%10d%10s%10d%10d%10d%10d    %.2lf\n",stu[i].num,stu[i].name,stu[i].sex,stu[i].age,stu[i].major,stu[i].math,stu[i].English,stu[i].Clanguage,stu[i].sum,stu[i].average);
		}
	printf("-----------------------------------------------------------------------------------\n\n");  
    printf("※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n\n\n");  
    fclose(fp);
	
} 






//4.添加学生成绩
int infor_add()
{
	FILE  *fp;  
    fp=fopen("studentinfor.txt","ab+");          
//        rewind(fp);  
    for(int i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++);  
    int n;  
    printf("请输入要添加学生信息数目：");  
    scanf("%d", &n);   
    for(int i = 0; i < n; i++)  
    {                  
        int len=0;
		while(1)
		{	
			
			printf("\n请输入要添加的学生信息的学号(8位)：");
			scanf("%s",stu[i].num);
			len=strlen(stu[i].num);
			if(strcmp(stu[i].num,stu[i-1].num)==0)
			{
				printf("该学生已存在！请重新输入");
			}
			
			int l=0,j;
			for(j=0;j<len;j++){
			
				if(!((stu[i].num[j]>57)||(stu[i].num[j]<48)))
					l++;}
			if(l==len&&len==8)
			{	
				break;
				
			}
			else printf("输入有误！");
		}
	printf("\n请输入要添加的学生信息的姓名：");
	scanf("%s",stu[i].name);
	while(1)
	{
		printf("\n请输入要添加的学生信息的性别(男或女):");
		scanf("%s",stu[i].sex);
		if(strcmp(stu[i].sex,"男")==0||strcmp(stu[i].sex,"女")==0)
		{
			break;
		}
		else printf("输入有误！");
	}
	while(1){
		int r;
		printf("\n请输入要添加的学生信息的年龄：");
		r=scanf("%d",&stu[i].age);
		if(r==1&&stu[i].age>0 && stu[i].age<100)
		{
			break;
		}
		else printf("输入有误！");
	}
	printf("\n请输入要添加的学生信息的专业：");
	scanf("%s",stu[i].major);
	while(1){
		int r;
		printf("\n请输入要添加的学生的高数成绩：");
		r=scanf("%d",&stu[i].math);
		if(r==1&&stu[i].math>=0 && stu[i].math<=100)
		{
			break;
		}
		else printf("输入有误！");}
	while(1){
		int r;
		printf("\n请输入要添加的学生的英语成绩：");
		r=scanf("%d",&stu[i].English);
		if(r==1&&stu[i].English>=0 && stu[i].English<=100)
		{
			break;
		}
		else printf("输入有误！");}
	while(1){
		int r;
		printf("\n请输入要添加的学生的C语言成绩：");
		r=scanf("%d",&stu[i].Clanguage);
		if(r==1&&stu[i].Clanguage>=0 && stu[i].Clanguage<=100)
		{
			break;
		}
		else printf("输入有误！");
	
	}
	stu[i].sum = stu[i].math + stu[i].English + stu[i].Clanguage;  
    stu[i].average = stu[i].sum / 3.0;
	printf("\n信息已经添入系统！"); 
        fwrite(&stu[i],sizeof(struct  student_infor),1,fp);  
    }  
    fclose(fp);  
   
} 


//5.修改学生成绩
void infor_change(){
	FILE  *fp;  
    fp=fopen("studentinfor.txt","rb");   
    int  i,n;  
    int  flag=0;
	char num[10];          
    printf("请输入要修改学生的学号:");  
    scanf("%s",&num);  
    for(i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++)  
        if(strcmp(stu[i].num,num)==0)  
    {  
        printf("※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n");  
        printf("                                              成绩列表\n");  
        printf("-----------------------------------------------------------------------------------\n");  
        printf("学号  	 姓名    性别   年龄    专业		高数	英语    C语言成绩    总成绩    平均成绩\n");   
        printf("-----------------------------------------------------------------------------------\n");  
        printf("%6s%10s%3s%10d%10s%10d%10d%10d%10d    %.2lf\n",stu[i].num,stu[i].name,stu[i].sex,stu[i].age,stu[i].major,stu[i].math,stu[i].English,stu[i].Clanguage,stu[i].sum,stu[i].average);
        printf("-----------------------------------------------------------------------------------\n\n");  
        printf("※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n");  
        n=i;  
        flag=1;  
                
    }fclose(fp);   
        if(flag==0)  
    {  
        printf("※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n");  
        printf("                                                输入错误!\n");  
        printf("                                                  请返回!\n");  
        printf("※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n");  
        return;  
        }  
        printf("\n\n\n");    
            
        fp=fopen("studentinfor.txt","rb+");  
        fseek(fp,n*sizeof(struct  student_infor),0);  
			printf("\n要修改的学生信息的学号为：%s\n",num);
			strcpy(stu[i].num,num);
			
			printf("\n请输入修改后的学生信息的姓名：");
			scanf("%s",stu[i].name);
		while(1){
		
			printf("\n请输入修改后的学生信息的性别(男或女):");
			scanf("%s",stu[i].sex);
			if(strcmp(stu[i].sex,"男")==0||strcmp(stu[i].sex,"女")==0)
			{
				break;
			}
			else printf("输入有误！");
		}
		
		while(1){
		int r;
		printf("\n请输入修改后的学生信息的年龄：");
		r=scanf("%d",&stu[i].age);
		if(r==1&&stu[i].age>0 && stu[i].age<100)
		{
			break;
		}
		else printf("输入有误！");
	}
		printf("\n请输入修改后的学生信息的专业：");
		scanf("%s",stu[i].major);
		while(1){
		int r;
		printf("\n请输入修改后的学生的高数成绩：");
		r=scanf("%d",&stu[i].math);
		if(r==1&&stu[i].math>=0 && stu[i].math<=100)
		{
			break;
		}
		else printf("输入有误！");}
	while(1){
		int r;
		printf("\n请输入修改后的学生的英语成绩：");
		r=scanf("%d",&stu[i].English);
		if(r==1&&stu[i].English>=0 && stu[i].English<=100)
		{
			break;
		}
		else printf("输入有误！");}
	while(1){
		int r;
		printf("\n请输入修改后的学生的C语言成绩：");
		r=scanf("%d",&stu[i].Clanguage);
		if(r==1&&stu[i].Clanguage>=0 && stu[i].Clanguage<=100)
		{
			break;
		}
		else printf("输入有误！");
    	
    }
    	stu[i].sum = stu[i].math + stu[i].English + stu[i].Clanguage;  
    	stu[i].average = stu[i].sum / 3.0;
		fwrite(&stu[i],sizeof(struct  student_infor),1,fp);  
        fclose(fp);   
        fp=fopen("studentinfor.txt","rb"); 
		printf("\n\n修改成功！\n\n"); 
        printf("※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n");  
        printf("                                              成绩列表\n");  
        printf("-----------------------------------------------------------------------------------\n");  
    	printf("学号  	 姓名    性别   年龄    专业		高数	英语    C语言成绩    总成绩    平均成绩\n");  
        printf("-----------------------------------------------------------------------------------\n");  
        for(i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++)  
    {  
     printf("%6s%10s%3s%10d%10s%10d%10d%10d%10d    %.2lf\n",stu[i].num,stu[i].name,stu[i].sex,stu[i].age,stu[i].major,stu[i].math,stu[i].English,stu[i].Clanguage,stu[i].sum,stu[i].average);  
    }  
        printf("-----------------------------------------------------------------------------------\n\n");  
        printf("※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n");  
        fclose(fp);  
	
	
	
	
	
} 




//6.删除学生成绩
int infor_delete()
{
	FILE  *fp;  
    fp=fopen("studentinfor.txt","rb");   
    printf("请输入要删除的学生学号：");  
    int i, k;
	char num[10];  
    scanf("%s", &num);  
	printf("确定要删除如下信息吗？\n");
	printf("※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n");   
    printf("-----------------------------------------------------------------------------------\n");  
    printf("学号      姓名        性别        专业    	高数	    英语      C语言     总成绩     平均成绩\n");  
    printf("-----------------------------------------------------------------------------------\n");  
    for(int i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++) 
	
        if(strcmp(stu[i].num,num)==0)  
        {  
    	    printf("%6s%10s%3s%10d%10s%10d%10d%10d%10d    %.2lf\n",stu[i].num,stu[i].name,stu[i].sex,stu[i].age,stu[i].major,stu[i].math,stu[i].English,stu[i].Clanguage,stu[i].sum,stu[i].average);
	
	printf("-----------------------------------------------------------------------------------\n\n");  
    printf("※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n\n\n");  
	}fclose(fp);
	
	printf("\n1.是\n2.否\n");
	scanf("%d",&k);
	
	if(k==1){
 	
		if ((fp = fopen("studentinfor.txt","rb+")) == NULL)
    {
        printf("打开文件失败");
    }
    
    int m = 0;
    for (int i = 0; fread(&stu[i], sizeof(student_infor), 1, fp); i++)
    {
        m++;
    }
    
    int del = 0;
    for (int i = 0; i < m; i++)
    {
        if(strcmp(stu[i].num,num)==0)
        {
            del = i;
            break;
        }
    }
    
    for (int i = del; i < m; i++)
    {
        strcpy(stu[i].num,stu[i+1].num);
        strcpy(stu[i].name,stu[i+1].name);
        strcpy(stu[i].sex,stu[i+1].sex);
        stu[i].age=stu[i+1].age;
        strcpy(stu[i].major,stu[i+1].major);
        stu[i].math=stu[i+1].math;
        stu[i].English=stu[i+1].English;
        stu[i].Clanguage=stu[i+1].Clanguage;
        stu[i].sum = stu[i+1].sum;
        stu[i].average = stu[i+1].average;
        
    }
    
    if ((fp = fopen("studentinfor.txt","w+")) == NULL)
    {
        printf("打开文件失败");
    }
    
    for (int i = 0; i < m -1; i++)
    {
        if (fwrite(&stu[i], sizeof(student_infor), 1, fp) != 1)
        {
            printf("写文件失败");
        }
    }
    fclose(fp);
	
	printf("\n删除成功！\n");
	
	}
	
	else{
		system("CLS");
		menu();
	}
	
     
    
	
 } 


//7.学生成绩排序
int infor_paixu(void) 
{
	int  i,j,n;  
    FILE  *fp;  
    struct  student_infor  t;  
    fp=fopen("studentinfor.txt","rb");    
    for(i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++)  
    {  
		
    }  
    
    fclose(fp);  
    n=i; 
	int h;
	printf("对高数成绩排序请按：1\n");
	printf("对英语成绩排序请按：2\n");
	printf("对C语言成绩排序请按：3\n");
	printf("对总分排序请按：4\n");
	printf("对平均分排序请按：5\n");
 
	scanf("%d",&h);
	if(h==1){
		system("CLS");
		for(i=0;i<n;i++)  
    	for(j=i+1;j<n;j++)  
       		if(stu[i].math<stu[j].math)  
          	{  
            	t=stu[i];  
                stu[i]=stu[j];  
                stu[j]=t;  
          	}  
        fp=fopen("studentinfor.txt","r");  
        printf("\n\n\n");
		printf("``````````````````````````````````高数成绩排序````````````````````````````````````\n");  
        printf("※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n");  
        printf("                                              成绩列表  \n");  
        printf("-----------------------------------------------------------------------------------\n");  
        printf("学号      	姓名	        性别     年龄   专业    高数    英语      C语言     总成绩     平均成绩\n");  
        printf("-----------------------------------------------------------------------------------\n");  
        for(i=0;i<n;i++)  
    {  
         
     printf("%6s%10s%3s%10d%10s%10d%10d%10d%10d    %.2lf\n",stu[i].num,stu[i].name,stu[i].sex,stu[i].age,stu[i].major,stu[i].math,stu[i].English,stu[i].Clanguage,stu[i].sum,stu[i].average);  
    }  
        printf("※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n");  
        fclose(fp);
	}
	
	if(h==2){
		system("CLS");
		for(i=0;i<n;i++)  
    	for(j=i+1;j<n;j++)  
       		if(stu[i].English<stu[j].English)  
          	{  
            	t=stu[i];  
                stu[i]=stu[j];  
                stu[j]=t;  
          	}  
        fp=fopen("studentinfor.txt","r");  
        printf("\n\n\n");
		printf("``````````````````````````````````英语成绩排序````````````````````````````````````\n"); 
        printf("※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n");  
        printf("                                              成绩列表  \n");  
        printf("-----------------------------------------------------------------------------------\n");  
        printf("学号      	姓名	        性别     年龄   专业    高数    英语      C语言     总成绩     平均成绩\n");  
        printf("-----------------------------------------------------------------------------------\n");  
        for(i=0;i<n;i++)  
    {  
         
     printf("%6s%10s%3s%10d%10s%10d%10d%10d%10d    %.2lf\n",stu[i].num,stu[i].name,stu[i].sex,stu[i].age,stu[i].major,stu[i].math,stu[i].English,stu[i].Clanguage,stu[i].sum,stu[i].average);  
    }  
        printf("※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n");  
        fclose(fp);
	}
	
	if(h==3){
		system("CLS");
		for(i=0;i<n;i++)  
    	for(j=i+1;j<n;j++)  
       		if(stu[i].Clanguage<stu[j].Clanguage)  
          	{  
            	t=stu[i];  
                stu[i]=stu[j];  
                stu[j]=t;  
          	}  
        fp=fopen("studentinfor.txt","r");  
        printf("\n\n\n"); 
		printf("`````````````````````````````````C语言成绩排序````````````````````````````````````\n"); 
        printf("※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n");  
        printf("                                              成绩列表  \n");  
        printf("-----------------------------------------------------------------------------------\n");  
        printf("学号      	姓名	        性别     年龄   专业    高数    英语      C语言     总成绩     平均成绩\n");  
        printf("-----------------------------------------------------------------------------------\n");  
        for(i=0;i<n;i++)  
    {  
         
     printf("%6s%10s%3s%10d%10s%10d%10d%10d%10d    %.2lf\n",stu[i].num,stu[i].name,stu[i].sex,stu[i].age,stu[i].major,stu[i].math,stu[i].English,stu[i].Clanguage,stu[i].sum,stu[i].average);  
    }  
        printf("※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n");  
        fclose(fp);
	}
	
	if(h==4){
		system("CLS");
		for(i=0;i<n;i++)  
    	for(j=i+1;j<n;j++)  
       		if(stu[i].sum<stu[j].sum)  
          	{  
            	t=stu[i];  
                stu[i]=stu[j];  
                stu[j]=t;  
          	}  
        fp=fopen("studentinfor.txt","r");  
        printf("\n\n\n");
		printf("``````````````````````````````````总分排序````````````````````````````````````\n");  
        printf("※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n");  
        printf("                                              成绩列表  \n");  
        printf("-----------------------------------------------------------------------------------\n");  
        printf("学号      	姓名	        性别     年龄   专业    高数    英语      C语言     总成绩     平均成绩\n");  
        printf("-----------------------------------------------------------------------------------\n");  
        for(i=0;i<n;i++)  
    {  
         
     printf("%6s%10s%3s%10d%10s%10d%10d%10d%10d    %.2lf\n",stu[i].num,stu[i].name,stu[i].sex,stu[i].age,stu[i].major,stu[i].math,stu[i].English,stu[i].Clanguage,stu[i].sum,stu[i].average);  
    }  
        printf("※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n");  
        fclose(fp);
	
	} 
    if(h==5){
		system("CLS");
		for(i=0;i<n;i++)  
    	for(j=i+1;j<n;j++)  
       		if(stu[i].average<stu[j].average)  
          	{  
            	t=stu[i];  
                stu[i]=stu[j];  
                stu[j]=t;  
          	}  
        fp=fopen("studentinfor.txt","r");  
        printf("\n\n\n");
		printf("``````````````````````````````````平均分排序````````````````````````````````````\n");  
        printf("※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n");  
        printf("                                              成绩列表  \n");  
        printf("-----------------------------------------------------------------------------------\n");  
        printf("学号      	姓名	        性别     年龄   专业    高数    英语      C语言     总成绩     平均成绩\n");  
        printf("-----------------------------------------------------------------------------------\n");  
        for(i=0;i<n;i++)  
    {  
         
     printf("%6s%10s%3s%10d%10s%10d%10d%10d%10d    %.2lf\n",stu[i].num,stu[i].name,stu[i].sex,stu[i].age,stu[i].major,stu[i].math,stu[i].English,stu[i].Clanguage,stu[i].sum,stu[i].average);  
    }  
        printf("※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n");  
        fclose(fp);
	
	} 


	
	if(h<1&&h>5)
	{
		printf("输入错误\n");	
	}
	int m;
	printf("\n返回上一级菜单请按1，返回主菜单请按2，退出请按0: ");
    scanf("%d", &m);

    if (m == 0) 
	{
        system("CLS");
        system("color 0C");
    	out();
    	Sleep(1000);
		exit(0);
    }
	
	if(m == 1){
		system("CLS"); 
		infor_paixu();
	} 

    if (m == 2) 
	{
        	menu();
            
    }  
    

}


//8.学生成绩统计
int infor_tongji1(void)
{
	int x,k;  
  
    printf("********************输入统计选项**********************\n"); /*选择功能菜单*/  
    printf("统计高数成绩不及格率请按:1\n");  
    printf("统计英语成绩不及格率请按:2\n");  
    printf("统计C语言成绩不及格率请按:3\n");             
  
    scanf("%d",&x);//用户选择变量                          
    FILE  *fp;  
    fp=fopen("studentinfor.txt","rb");   
    if(x==1)  

    {  
        k=0;
        printf("高数未及格的学生有：\n");
        for(int i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++)/*统计高数成绩不及格率*/  
       {  
       		
        	if(stu[i].math<60)
			{
				k++;
				printf("学号：%s\t\t姓名：%s\t\t专业：%s\t\t分数：%d\t\t\n",stu[i].num,stu[i].name,stu[i].major,stu[i].math);  
       		}
	   }  
        printf("共%d人高数未及格\n",k);
		  
  
        printf("************************************************************\n");  
    }  
  
    
    if(x==2)  
    {  
     	k=0;  
     	printf("英语未及格的学生有：\n");
        for(int i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++)/*统计英语成绩不及格率*/  
       {  
           if(stu[i].English<60)
		   {
				k++;
				printf("学号：%s\t\t姓名：%s\t\t专业：%s\t\t分数：%d\t\t\n",stu[i].num,stu[i].name,stu[i].major,stu[i].English);  
       		}    
       }  
        printf("共%d人英语不及格\n",k);  
        printf("  **********************************************************\n");  
    }  
    if(x==3)  
    {  
     	k=0;
		printf("C语言未及格的学生有：\n");  
        for(int i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++)/*统计英语成绩不及格率*/  
       {  
           if(stu[i].Clanguage<60)
		   {
				k++;
				printf("学号：%s\t\t姓名：%s\t\t专业：%s\t\t分数：%d\t\t\n",stu[i].num,stu[i].name,stu[i].major,stu[i].Clanguage);  
       		}       
       }  
        printf("共%d人C语言成绩不及格\n",k);  
        printf("  **********************************************************");  
    }
    int m;
	printf("\n返回上一级菜单请按1，返回主菜单请按2，退出请按0: ");
    scanf("%d", &m);

    if (m == 0) 
	{
        system("CLS");
        system("color 0C");
    	out();
    	Sleep(1000);
		exit(0);
    }
	
	if(m == 1){
		infor_tongji1();
	} 

    if (m == 2) 
	{
        	menu();
            
    }  
    
    
 } 


int infor_tongji2(void)
{
	int x,k;  
  
    printf("********************输入统计选项**********************\n"); /*选择功能菜单*/  
    printf("统计高数成绩不及格率请按:1\n");  
    printf("统计英语成绩不及格率请按:2\n");  
    printf("统计C语言成绩不及格率请按:3\n");             
  
    scanf("%d",&x);//用户选择变量                          
    FILE  *fp;  
    fp=fopen("studentinfor.txt","rb");   
    if(x==1)  
  
    {  
        k=0;  
        for(int i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++)/*统计高数成绩不及格率*/  
       {  
           if(stu[i].math<60)  
                k++,  
                printf("不及格的分数为%d\n",stu[i].math);  
       }  
        printf("共%d人高数未及格\n",k);  
  
        printf("************************************************************\n");  
    }  
  
    
    if(x==2)  
    {  
     k=0;  
        for(int i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++)/*统计英语成绩不及格率*/  
       {  
           if(stu[i].English<60)  
                 k++,  
            printf("不及格的分数为%d\n",stu[i].English);       
       }  
        printf("共%d人英语不及格\n",k);  
        printf("  **********************************************************");  
    }  
    if(x==3)  
    {  
     k=0;  
        for(int i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++)/*统计英语成绩不及格率*/  
       {  
           if(stu[i].Clanguage<60)  
                 k++,  
            printf("不及格的分数为%d\n",stu[i].Clanguage);       
       }  
        printf("共%d人C语言成绩不及格\n",k);  
        printf("  **********************************************************");  
    }
    int m;
	printf("\n返回上一级菜单请按1，返回主菜单请按2，退出请按0: ");
    scanf("%d", &m);

    if (m == 0) 
	{
        system("CLS");
        system("color 0C");
    	out();
    	Sleep(1000);
		exit(0);
    }
	
	if(m == 1){
		infor_tongji2();
	} 

    if (m == 2) 
	{
        menue();
            
    }  
    
    
 } 

void captcha(char str[],int n)//验证码
{
    char a[]="1234567890abcdefghijkmnopqrstuvwxyzABCDEFGHIJLMNPQRSTUVWXYZ";
    int i,j,k;
    k=strlen(a);//k表示字符串的长度
    srand(time(0));//随机数初始化
    for(i=0;i<n;i++)
    {
        j=rand()%k;//取0-58的随机数
        str[i]=a[j];
    }
    str[i]='\0';
}


int main(int argc, char *argv[])
{
	
	char result=' ';
	char choice=' ';
	char title[]="\t\t\t*********欢迎进入学生信息管理系统！********\n\n\n\n\n\n\n\t\t\t\t    2018年5月30日\n\n\n\n\n\n\n\t\t\t\t      KangWenZhe\n";
	//1:初始化窗口和界面
	Window(title);
	
	
	Sleep(3000);
	lead *lea;
	//申请一个管理员结点来保存管理员的信息 
    lea = (lead*)malloc(sizeof(lead));
	
    
	login();

	
	return 0;
	
} 

