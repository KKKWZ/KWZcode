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
    char num[10];//ѧ�� 
    char name[20];//���� 
    char sex[10];//�Ա� 
    int age;//���� 
    char major[20];//רҵ
	int math;//�����ɼ�
	int English;//Ӣ��ɼ�
	int Clanguage;//C���Գɼ� 
	int sum;//�ܷ�
	double average;//ƽ���� 
    struct student_infor *next;
}stu[SIZE];


//����Ա����ṹ��
typedef struct leader{
    char name[100];
    char mima[100];
}lead; 


//ѧ����¼����ṹ�� 
typedef struct 
{
    char suser[1000];
    char scode[1000]; 
}susers;
susers s;



void Window(char *);//��ʼ���ںͽ��� 
void initleader(lead* );
void zhuce2();
int teacherdenglu(void); 
void zhuce3();
void studentdenglu();
void write3();
void captcha(char str[],int );//��֤��
void login();//��¼
void menu();//����Ա�˵� 
void menue(); //ѧ���˵�
void judgement1();
void judgement2();
int infor_input(void);//¼�� 
int infor_show(void);//��ʾ 
int infor_search(void);//��ѯ 
int infor_add(void);//��� 
void infor_change();//�޸� 
int infor_delete(void);//ɾ��
int infor_paixu(void);//����
int infor_tongji1(void);//ͳ��
int infor_tongji2(void); 
int out(void);//�˳� 







//һ����ʼ���ںͽ���
void Window(char *title){
	//���ô��ڴ�С
	system("mode con:cols=90 lines=200");
	//���ô����������ɫ
	system("color 4E");
	//ѭ��������⣨��������
	while(*title!=0)
	{
		//����ַ�ָ����ָ�������
		printf("%c",*title);
		//��ָ��ָ����һ���ַ�
		title++;
		//���� 
		Sleep(50);
	}
}


//����Ա��¼ 
void initleader(lead* lea){
    printf("\n\n\n\t\t\t���ε�¼�������ù���Ա��Ϣ��");
    printf("\n\t\t\t�˺ţ�");
    scanf("%s",lea->name);
    printf("\n\t\t\t���룺");
    scanf("%s",lea->mima);
    printf("\n\t\t\t������ɣ������������ϵͳ...");
	getch(); 
}


void initdata(lead* lea){
	
	//���ļ� 
    FILE *fp = fopen("guanliyuan.txt","rt");
   //��ȡ�ϴεĹ���Ա��Ϣ 
	fread(lea,sizeof(lead),1,fp );
    
    
    fclose(fp);
}


void readdata(lead* lea){
    FILE *fp = fopen("guanliyuan.txt","rt");
    if(fp == NULL){
    	//����򲻿�����֤���ǵ�һ��ʹ�ã���ʾ��ʼ������Ա��Ϣ 
        initleader(lea);
        return;
    }
	else{
        fclose(fp);
        //������ˣ��Ͳ��ǵ�һ��ʹ�� 
        initdata(lea);
    }
}


int yanzhengleader(lead* lea){
	char a[100],b[100];
	char code[N],str[N];
    system("CLS");
    printf("\n\n\n\t\t\t��Ҫ���й���Ա��֤��");
    printf("\n\n\n\n\t\t\t�������˺ţ�");
    scanf("%s",a);
    printf("\n\n\n\n\t\t\t���������룺");
    scanf("%s",b);
    if((strcmp(a,lea->name ) == 0) && (strcmp(b,lea->mima) == 0) ){
        while(1){
        	captcha(code,4);
            printf("\n\n\n\n\t\t\t��������֤�룺%s\n",code);
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
	//��ֻд����ʽ�� 
    FILE *fp = fopen("guanliyuan.txt","w");
	//д�����Ա��Ϣ 
	fwrite(lea,sizeof(lead),1,fp);
    
    fclose(fp);
}

void print() {
    printf("   _______________________________________\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |                ��ѡ��                |\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |         ����ע��������밴 0         |\n");
    printf("   |                                      |\n");
    printf("   |         �������û������밴 1         |\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |______________________________________|\n");
    printf("������");
}
void zhuce2(){
    FILE *fp=fopen("user.txt","w");/*��дģʽ("w")���ļ�user.txt,���������,���Զ�����*/
    printf("�������˺�");
    gets(nam);
    printf("����������");
    gets(pas); /*�������ƺ�����*/
    fputs(nam,fp);
    fputs(pas,fp);/*�����ƺ��������ַ�����ʽд���ļ�*/
    fputs("\n",fp);
    fflush(stdin);//�������
    fclose(fp);/*�ر��ļ�*/
    teacherdenglu();//ע����ת����¼����
}

int teacherdenglu(void){
	system("CLS");
	fflush(stdin);
    printf("��¼����\n");
    printf("�������˺�");
    gets(nam);
    fflush(stdin);
    printf("����������");
    gets(pas); /*�������ƺ�����*/
    strcat(nam,pas);//�ϲ��ַ�
    strcat(nam,"\n");//��ӻ����ַ�
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
        fgets(textstring, sizeof(textstring) - 1, fp); // ������\n
        if(strcmp(nam,textstring)==0){//�ж��ַ��Ƿ����
           ok=1;
           break;
        }
    }
    if(ok){
	
    	printf("��¼OK");
  		menu();
  }
    else
	
	
    printf("��¼ʧ��");
	login();

	fclose(fp);
    

}

//ѧ��ע�� 
void zhuce3(){
	system("CLS");
	FILE *fp;
	char temp[100];
	do
	{
		printf("\t\t\t\t�û�ע��\n\t\t�û�����");
		scanf("%s",s.suser);
		fp=fopen(s.suser,"r");
		//�ж��û����Ƿ��ظ�
		if(fp!=NULL)
		{
			printf("\n\t���û��Ѵ���");
			fclose(fp);
			printf("\n\t����ע�᣿(Y/N)");
			if(getch()=='Y') 
				return zhuce3();
			else 
				return studentdenglu();  
		 }
		//ȷ���������������Ƿ�һ��
		printf("\n\t\t���룺");
		scanf("%s",s.scode); 
		printf("\n\t\tȷ������:");
		scanf("%s",temp);
		if(strcmp(s.scode,temp)!=0)
			printf("\n\t\t�����������벻һ�£�����������\n"); 
	}while(strcmp(s.scode,temp)!=0);
	//�û�����������д���ĵ������û���Ϣ
	fp=fopen(s.suser,"w");
	if(fp==NULL)
	{
		printf("\n\tע��ʧ��\n");
		exit(0);
	}
	else
	{
		system("CLS");
		printf("\n\tע��ɹ�");
		write3();
		judge = FALSE;
		studentdenglu();
	} 
}

void write3()
{
	
	if(fwrite(&s,sizeof(s.suser),1,fp)!=1)
	{
		printf("\n\t\tд���ļ�����\n");	
	}
}

//ѧ����¼ 
void studentdenglu(){

	char u[1000],c[1000],temp[1000];
	printf("\n\t\t\t\t�û���¼");
	printf("\n\t\t�û�����");
	scanf("%s",u);
	//�ж��û����Ƿ����
	fp=fopen(u,"r+");
	temp[0]='0';
	if(fp==NULL)
	{
		printf("\n\t\t�û������ڣ���ע��");
		printf("\n\t\t1.ע��	2.���µ�¼");
		temp[0]=getch();
		if(temp[0]=='1')
		{
			system("CLS");
			zhuce3();
		}
		else
			return studentdenglu();
	} 
	//��֤�����Ƿ���ȷ
	do{
	
		if(judge==TRUE)
			fread(&s,sizeof(susers),1,fp);
			
			printf("\t\t���룺");
			scanf("%s",c);
			if(strcmp(s.scode,c)!=0)
			{
				printf("\n\t\t�������(1.�˳� 2.��������)");
				temp[0]=getch();
				printf("\n");
				if(temp[0]=='1')
				{
					fclose(fp);
					return login();
				}
		 }
		if(strcmp(s.scode,c)==0){
			printf("��½�ɹ���");
			Sleep(2000);
			menue();
		}	
		}while(temp[0]=='2');
			
			
		 
}



//���������¼
void login(){
	
	system("CLS");
	system("color 37");
	printf("��ѡ���¼��ʽ��\n1.����Ա��¼\n2.��ʦ��¼\n3.ѧ����¼\n\n");
	int n,j=0;
	int settle=0;
    char c,password[6];
	scanf("%d",&n);
	switch(n){
		case 1: system("CLS");
				lead* lea;
				
			//����һ������Ա������������Ա����Ϣ 
    			lea = (lead*)malloc(sizeof(lead));
   			
    			readdata(lea);
    			//��֤����Ա���� 
    			while(yanzhengleader(lea) == 0);
    			savedata(lea);
    			while(1){
    				menu();
    				
				}
				break;
		case 2: print();
			    scanf("%d",&settle);
    			fflush(stdin);//�������
    			if(settle)
       				zhuce2();
    			else
    				teacherdenglu();
				break;
      	case 3: zhuce3();
      			break;
		   
		}
	
}

//����Ա�˵� 
void menu(){
	system("CLS");
	system("mode con:cols=250 lines=300");
	system("color 1F");
	printf("\t\t**********************\n\n");
	printf("\t\tѧ������ϵͳ\n\n");
	printf("1.¼��ѧ���ɼ�\n\n");
	printf("2.��ʾѧ���ɼ�\n\n");
	printf("3.��ѯѧ���ɼ�\n\n");
	printf("4.���ѧ���ɼ�\n\n");
	printf("5.�޸�ѧ���ɼ�\n\n");
	printf("6.ɾ��ѧ���ɼ�\n\n");
	printf("7.ѧ���ɼ�����\n\n");
	printf("8.ѧ���ɼ�ͳ��\n\n");
	printf("9.�˳���ǰ��¼\n\n"); 
	printf("0.�˳�ϵͳ\n\n");
	printf("\n\n��ѡ��(0~9):\n\n");
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
			default:printf("��������һ����Ч��ѡ������������(0-9):\n ");
        			continue;
            }
            system("PAUSE");
        }
	
        
    
	
	
}




//ѧ���˵�
void menue(){
	system("CLS");
	system("mode con:cols=250 lines=300");
	system("color 1F");
	printf("\t\t**********************\n\n");
	printf("\t\t��ӭ����ѧ������ϵͳ\n\n");
	printf("1.��ʾѧ���ɼ�\n\n");
	printf("2.��ѯѧ���ɼ�\n\n");
	printf("3.ѧ���ɼ�����\n\n");
	printf("4.ѧ���ɼ�ͳ��\n\n");
	printf("5.�˳���ǰ��¼\n\n"); 
	printf("0.�˳�ϵͳ\n\n");
	printf("\n\n��ѡ��(0~5):\n\n");
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
			default:printf("��������һ����Ч��ѡ������������(0-5):\n ");
        			continue;
            }
            system("PAUSE");
        }
	
        
    
	
	
} 



//�ж�
void judgement1(){
	int m;
	printf("\n������һ���˵��밴1���˳��밴0: ");
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
	printf("\n������һ���˵��밴1���˳��밴0: ");
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
	printf("\n\n\n\n\t\t\t\t\t\t\t\t\t��лʹ�ã�\n");
	printf("\n\n\n\n\t\t\t\t\t\t\t\t\tSee you again.\n");
	printf("\n\n\n\n\t\t\t\t\t\t\t\t\tKWZ.\n");
}

// 1. ѧ����Ϣ¼��
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
    printf("����Ҫ¼���ѧ����Ŀ��\n");  
    int n;  
    scanf("%d", &n);   
    for(int i = 0; i < n; i++)  
    {        
		  
        int len=0;
		while(1)
		{	
			
			printf("\n������Ҫ¼���ѧ����Ϣ��ѧ��(8λ)��");
			scanf("%s",stu[i].num);
			len=strlen(stu[i].num);
			if(strcmp(stu[i].num,stu[i-1].num)==0)
			{
				printf("��ѧ���Ѵ��ڣ�����������"); 
			}
			
			int l=0,j;
			for(j=0;j<len;j++){
			
				if(!((stu[i].num[j]>57)||(stu[i].num[j]<48)))
					l++;}
			if(l==len&&len==8)
			{	
							break;
				
			}
			else printf("��������");
		}
	printf("\n������Ҫ¼���ѧ����Ϣ��������");
	scanf("%s",stu[i].name);
	while(1)
	{
		printf("\n������Ҫ¼���ѧ����Ϣ���Ա�(�л�Ů):");
		scanf("%s",stu[i].sex);
		if(strcmp(stu[i].sex,"��")==0||strcmp(stu[i].sex,"Ů")==0)
		{
			break;
		}
		else printf("��������");
	}
	while(1){
		int r;
		printf("\n������Ҫ¼���ѧ����Ϣ�����䣺");
		r = scanf("%d",&stu[i].age);
		if(r==1&&stu[i].age>0 && stu[i].age<100)
		{
			break;
		}
		else printf("��������");
		
	}
	printf("\n������Ҫ¼���ѧ����Ϣ��רҵ��");
	scanf("%s",stu[i].major);
	while(1){
		int r;
		printf("\n������Ҫ¼���ѧ���ĸ����ɼ���");
		r = scanf("%d",&stu[i].math);
		if(r==1&&stu[i].math>=0 && stu[i].math<=100)
		{
			break;
		}
		else printf("��������");
			fflush(stdin);
		}
	while(1){
		int r;
		printf("\n������Ҫ¼���ѧ����Ӣ��ɼ���");
		r = scanf("%d",&stu[i].English);
		if(r==1&&stu[i].English>=0 && stu[i].English<=100)
		{
			break;
		}
		else printf("��������");
			fflush(stdin);
		}
	while(1){
		int r;
		printf("\n������Ҫ¼���ѧ����C���Գɼ���");
		r=scanf("%d",&stu[i].Clanguage);
		if(r==1&&stu[i].Clanguage>=0 && stu[i].Clanguage<=100)
		{
			break;
		}
		else printf("��������");
		fflush(stdin);
	}
	stu[i].sum = stu[i].math + stu[i].English + stu[i].Clanguage;  
    stu[i].average = stu[i].sum / 3.0;
	printf("\n��Ϣ�Ѿ�¼��ϵͳ��"); 
      
    }
	
    for (int i = 0; i < n; i++)  
        if (fwrite(&stu[i], sizeof(struct student_infor),1,fp)!=1)  
            printf("file write error!\n");        
    fclose(fp);
	
}




//2.��ʾѧ����Ϣ
int infor_show()
{ 
    FILE  *fp;  
    int  i;  
    fp=fopen("studentinfor.txt","rb");                                           
    printf("����������������������������������������������������������������������������������\n");  
    printf("                                  �ɼ��б�\n");  
    printf("-----------------------------------------------------------------------------------\n");  
    printf("ѧ�� 	  ����    �Ա�   ����    רҵ		����	Ӣ��    C���Գɼ�    �ܳɼ�    ƽ���ɼ�\n");  
    printf("-----------------------------------------------------------------------------------\n");        
	for(i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++)//for(i=0;fread(&stu[i],6,1,fp)==1;i++)  
    {  
    printf("%6s%10s%3s%10d%10s%10d%10d%10d%10d    %.2lf\n",stu[i].num,stu[i].name,stu[i].sex,stu[i].age,stu[i].major,stu[i].math,stu[i].English,stu[i].Clanguage,stu[i].sum,stu[i].average);  
    }  
	printf("-----------------------------------------------------------------------------------\n\n");  
    printf("����������������������������������������������������������������������������������\n");  
    fclose(fp);  
	
	
} 



//3.��ѯѧ����Ϣ
int infor_search(){
	FILE  *fp;  
    char  num[10];  
    fp=fopen("studentinfor.txt","rb");          
    printf("������Ҫ���ҵ�ѧ��:");  
    scanf("%s",&num);  
    printf("����������������������������������������������������������������������������������\n");  
    printf("                                            ��ѯ���\n");  
    printf("-----------------------------------------------------------------------------------\n");  
    printf("ѧ��      ����        �Ա�        רҵ    	����	    Ӣ��      C����     �ܳɼ�     ƽ���ɼ�\n");  
    printf("-----------------------------------------------------------------------------------\n");  
    for(int i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++)  
        if(strcmp(stu[i].num,num)==0) 
        {  
    	    printf("%6s%10s%3s%10d%10s%10d%10d%10d%10d    %.2lf\n",stu[i].num,stu[i].name,stu[i].sex,stu[i].age,stu[i].major,stu[i].math,stu[i].English,stu[i].Clanguage,stu[i].sum,stu[i].average);
		}
	printf("-----------------------------------------------------------------------------------\n\n");  
    printf("����������������������������������������������������������������������������������\n\n\n");  
    fclose(fp);
	
} 






//4.���ѧ���ɼ�
int infor_add()
{
	FILE  *fp;  
    fp=fopen("studentinfor.txt","ab+");          
//        rewind(fp);  
    for(int i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++);  
    int n;  
    printf("������Ҫ���ѧ����Ϣ��Ŀ��");  
    scanf("%d", &n);   
    for(int i = 0; i < n; i++)  
    {                  
        int len=0;
		while(1)
		{	
			
			printf("\n������Ҫ��ӵ�ѧ����Ϣ��ѧ��(8λ)��");
			scanf("%s",stu[i].num);
			len=strlen(stu[i].num);
			if(strcmp(stu[i].num,stu[i-1].num)==0)
			{
				printf("��ѧ���Ѵ��ڣ�����������");
			}
			
			int l=0,j;
			for(j=0;j<len;j++){
			
				if(!((stu[i].num[j]>57)||(stu[i].num[j]<48)))
					l++;}
			if(l==len&&len==8)
			{	
				break;
				
			}
			else printf("��������");
		}
	printf("\n������Ҫ��ӵ�ѧ����Ϣ��������");
	scanf("%s",stu[i].name);
	while(1)
	{
		printf("\n������Ҫ��ӵ�ѧ����Ϣ���Ա�(�л�Ů):");
		scanf("%s",stu[i].sex);
		if(strcmp(stu[i].sex,"��")==0||strcmp(stu[i].sex,"Ů")==0)
		{
			break;
		}
		else printf("��������");
	}
	while(1){
		int r;
		printf("\n������Ҫ��ӵ�ѧ����Ϣ�����䣺");
		r=scanf("%d",&stu[i].age);
		if(r==1&&stu[i].age>0 && stu[i].age<100)
		{
			break;
		}
		else printf("��������");
	}
	printf("\n������Ҫ��ӵ�ѧ����Ϣ��רҵ��");
	scanf("%s",stu[i].major);
	while(1){
		int r;
		printf("\n������Ҫ��ӵ�ѧ���ĸ����ɼ���");
		r=scanf("%d",&stu[i].math);
		if(r==1&&stu[i].math>=0 && stu[i].math<=100)
		{
			break;
		}
		else printf("��������");}
	while(1){
		int r;
		printf("\n������Ҫ��ӵ�ѧ����Ӣ��ɼ���");
		r=scanf("%d",&stu[i].English);
		if(r==1&&stu[i].English>=0 && stu[i].English<=100)
		{
			break;
		}
		else printf("��������");}
	while(1){
		int r;
		printf("\n������Ҫ��ӵ�ѧ����C���Գɼ���");
		r=scanf("%d",&stu[i].Clanguage);
		if(r==1&&stu[i].Clanguage>=0 && stu[i].Clanguage<=100)
		{
			break;
		}
		else printf("��������");
	
	}
	stu[i].sum = stu[i].math + stu[i].English + stu[i].Clanguage;  
    stu[i].average = stu[i].sum / 3.0;
	printf("\n��Ϣ�Ѿ�����ϵͳ��"); 
        fwrite(&stu[i],sizeof(struct  student_infor),1,fp);  
    }  
    fclose(fp);  
   
} 


//5.�޸�ѧ���ɼ�
void infor_change(){
	FILE  *fp;  
    fp=fopen("studentinfor.txt","rb");   
    int  i,n;  
    int  flag=0;
	char num[10];          
    printf("������Ҫ�޸�ѧ����ѧ��:");  
    scanf("%s",&num);  
    for(i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++)  
        if(strcmp(stu[i].num,num)==0)  
    {  
        printf("����������������������������������������������������������������������������������\n");  
        printf("                                              �ɼ��б�\n");  
        printf("-----------------------------------------------------------------------------------\n");  
        printf("ѧ��  	 ����    �Ա�   ����    רҵ		����	Ӣ��    C���Գɼ�    �ܳɼ�    ƽ���ɼ�\n");   
        printf("-----------------------------------------------------------------------------------\n");  
        printf("%6s%10s%3s%10d%10s%10d%10d%10d%10d    %.2lf\n",stu[i].num,stu[i].name,stu[i].sex,stu[i].age,stu[i].major,stu[i].math,stu[i].English,stu[i].Clanguage,stu[i].sum,stu[i].average);
        printf("-----------------------------------------------------------------------------------\n\n");  
        printf("����������������������������������������������������������������������������������\n");  
        n=i;  
        flag=1;  
                
    }fclose(fp);   
        if(flag==0)  
    {  
        printf("����������������������������������������������������������������������������������\n");  
        printf("                                                �������!\n");  
        printf("                                                  �뷵��!\n");  
        printf("����������������������������������������������������������������������������������\n");  
        return;  
        }  
        printf("\n\n\n");    
            
        fp=fopen("studentinfor.txt","rb+");  
        fseek(fp,n*sizeof(struct  student_infor),0);  
			printf("\nҪ�޸ĵ�ѧ����Ϣ��ѧ��Ϊ��%s\n",num);
			strcpy(stu[i].num,num);
			
			printf("\n�������޸ĺ��ѧ����Ϣ��������");
			scanf("%s",stu[i].name);
		while(1){
		
			printf("\n�������޸ĺ��ѧ����Ϣ���Ա�(�л�Ů):");
			scanf("%s",stu[i].sex);
			if(strcmp(stu[i].sex,"��")==0||strcmp(stu[i].sex,"Ů")==0)
			{
				break;
			}
			else printf("��������");
		}
		
		while(1){
		int r;
		printf("\n�������޸ĺ��ѧ����Ϣ�����䣺");
		r=scanf("%d",&stu[i].age);
		if(r==1&&stu[i].age>0 && stu[i].age<100)
		{
			break;
		}
		else printf("��������");
	}
		printf("\n�������޸ĺ��ѧ����Ϣ��רҵ��");
		scanf("%s",stu[i].major);
		while(1){
		int r;
		printf("\n�������޸ĺ��ѧ���ĸ����ɼ���");
		r=scanf("%d",&stu[i].math);
		if(r==1&&stu[i].math>=0 && stu[i].math<=100)
		{
			break;
		}
		else printf("��������");}
	while(1){
		int r;
		printf("\n�������޸ĺ��ѧ����Ӣ��ɼ���");
		r=scanf("%d",&stu[i].English);
		if(r==1&&stu[i].English>=0 && stu[i].English<=100)
		{
			break;
		}
		else printf("��������");}
	while(1){
		int r;
		printf("\n�������޸ĺ��ѧ����C���Գɼ���");
		r=scanf("%d",&stu[i].Clanguage);
		if(r==1&&stu[i].Clanguage>=0 && stu[i].Clanguage<=100)
		{
			break;
		}
		else printf("��������");
    	
    }
    	stu[i].sum = stu[i].math + stu[i].English + stu[i].Clanguage;  
    	stu[i].average = stu[i].sum / 3.0;
		fwrite(&stu[i],sizeof(struct  student_infor),1,fp);  
        fclose(fp);   
        fp=fopen("studentinfor.txt","rb"); 
		printf("\n\n�޸ĳɹ���\n\n"); 
        printf("����������������������������������������������������������������������������������\n");  
        printf("                                              �ɼ��б�\n");  
        printf("-----------------------------------------------------------------------------------\n");  
    	printf("ѧ��  	 ����    �Ա�   ����    רҵ		����	Ӣ��    C���Գɼ�    �ܳɼ�    ƽ���ɼ�\n");  
        printf("-----------------------------------------------------------------------------------\n");  
        for(i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++)  
    {  
     printf("%6s%10s%3s%10d%10s%10d%10d%10d%10d    %.2lf\n",stu[i].num,stu[i].name,stu[i].sex,stu[i].age,stu[i].major,stu[i].math,stu[i].English,stu[i].Clanguage,stu[i].sum,stu[i].average);  
    }  
        printf("-----------------------------------------------------------------------------------\n\n");  
        printf("����������������������������������������������������������������������������������\n");  
        fclose(fp);  
	
	
	
	
	
} 




//6.ɾ��ѧ���ɼ�
int infor_delete()
{
	FILE  *fp;  
    fp=fopen("studentinfor.txt","rb");   
    printf("������Ҫɾ����ѧ��ѧ�ţ�");  
    int i, k;
	char num[10];  
    scanf("%s", &num);  
	printf("ȷ��Ҫɾ��������Ϣ��\n");
	printf("����������������������������������������������������������������������������������\n");   
    printf("-----------------------------------------------------------------------------------\n");  
    printf("ѧ��      ����        �Ա�        רҵ    	����	    Ӣ��      C����     �ܳɼ�     ƽ���ɼ�\n");  
    printf("-----------------------------------------------------------------------------------\n");  
    for(int i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++) 
	
        if(strcmp(stu[i].num,num)==0)  
        {  
    	    printf("%6s%10s%3s%10d%10s%10d%10d%10d%10d    %.2lf\n",stu[i].num,stu[i].name,stu[i].sex,stu[i].age,stu[i].major,stu[i].math,stu[i].English,stu[i].Clanguage,stu[i].sum,stu[i].average);
	
	printf("-----------------------------------------------------------------------------------\n\n");  
    printf("����������������������������������������������������������������������������������\n\n\n");  
	}fclose(fp);
	
	printf("\n1.��\n2.��\n");
	scanf("%d",&k);
	
	if(k==1){
 	
		if ((fp = fopen("studentinfor.txt","rb+")) == NULL)
    {
        printf("���ļ�ʧ��");
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
        printf("���ļ�ʧ��");
    }
    
    for (int i = 0; i < m -1; i++)
    {
        if (fwrite(&stu[i], sizeof(student_infor), 1, fp) != 1)
        {
            printf("д�ļ�ʧ��");
        }
    }
    fclose(fp);
	
	printf("\nɾ���ɹ���\n");
	
	}
	
	else{
		system("CLS");
		menu();
	}
	
     
    
	
 } 


//7.ѧ���ɼ�����
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
	printf("�Ը����ɼ������밴��1\n");
	printf("��Ӣ��ɼ������밴��2\n");
	printf("��C���Գɼ������밴��3\n");
	printf("���ܷ������밴��4\n");
	printf("��ƽ���������밴��5\n");
 
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
		printf("``````````````````````````````````�����ɼ�����````````````````````````````````````\n");  
        printf("����������������������������������������������������������������������������������\n");  
        printf("                                              �ɼ��б�  \n");  
        printf("-----------------------------------------------------------------------------------\n");  
        printf("ѧ��      	����	        �Ա�     ����   רҵ    ����    Ӣ��      C����     �ܳɼ�     ƽ���ɼ�\n");  
        printf("-----------------------------------------------------------------------------------\n");  
        for(i=0;i<n;i++)  
    {  
         
     printf("%6s%10s%3s%10d%10s%10d%10d%10d%10d    %.2lf\n",stu[i].num,stu[i].name,stu[i].sex,stu[i].age,stu[i].major,stu[i].math,stu[i].English,stu[i].Clanguage,stu[i].sum,stu[i].average);  
    }  
        printf("����������������������������������������������������������������������������������\n");  
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
		printf("``````````````````````````````````Ӣ��ɼ�����````````````````````````````````````\n"); 
        printf("����������������������������������������������������������������������������������\n");  
        printf("                                              �ɼ��б�  \n");  
        printf("-----------------------------------------------------------------------------------\n");  
        printf("ѧ��      	����	        �Ա�     ����   רҵ    ����    Ӣ��      C����     �ܳɼ�     ƽ���ɼ�\n");  
        printf("-----------------------------------------------------------------------------------\n");  
        for(i=0;i<n;i++)  
    {  
         
     printf("%6s%10s%3s%10d%10s%10d%10d%10d%10d    %.2lf\n",stu[i].num,stu[i].name,stu[i].sex,stu[i].age,stu[i].major,stu[i].math,stu[i].English,stu[i].Clanguage,stu[i].sum,stu[i].average);  
    }  
        printf("����������������������������������������������������������������������������������\n");  
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
		printf("`````````````````````````````````C���Գɼ�����````````````````````````````````````\n"); 
        printf("����������������������������������������������������������������������������������\n");  
        printf("                                              �ɼ��б�  \n");  
        printf("-----------------------------------------------------------------------------------\n");  
        printf("ѧ��      	����	        �Ա�     ����   רҵ    ����    Ӣ��      C����     �ܳɼ�     ƽ���ɼ�\n");  
        printf("-----------------------------------------------------------------------------------\n");  
        for(i=0;i<n;i++)  
    {  
         
     printf("%6s%10s%3s%10d%10s%10d%10d%10d%10d    %.2lf\n",stu[i].num,stu[i].name,stu[i].sex,stu[i].age,stu[i].major,stu[i].math,stu[i].English,stu[i].Clanguage,stu[i].sum,stu[i].average);  
    }  
        printf("����������������������������������������������������������������������������������\n");  
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
		printf("``````````````````````````````````�ܷ�����````````````````````````````````````\n");  
        printf("����������������������������������������������������������������������������������\n");  
        printf("                                              �ɼ��б�  \n");  
        printf("-----------------------------------------------------------------------------------\n");  
        printf("ѧ��      	����	        �Ա�     ����   רҵ    ����    Ӣ��      C����     �ܳɼ�     ƽ���ɼ�\n");  
        printf("-----------------------------------------------------------------------------------\n");  
        for(i=0;i<n;i++)  
    {  
         
     printf("%6s%10s%3s%10d%10s%10d%10d%10d%10d    %.2lf\n",stu[i].num,stu[i].name,stu[i].sex,stu[i].age,stu[i].major,stu[i].math,stu[i].English,stu[i].Clanguage,stu[i].sum,stu[i].average);  
    }  
        printf("����������������������������������������������������������������������������������\n");  
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
		printf("``````````````````````````````````ƽ��������````````````````````````````````````\n");  
        printf("����������������������������������������������������������������������������������\n");  
        printf("                                              �ɼ��б�  \n");  
        printf("-----------------------------------------------------------------------------------\n");  
        printf("ѧ��      	����	        �Ա�     ����   רҵ    ����    Ӣ��      C����     �ܳɼ�     ƽ���ɼ�\n");  
        printf("-----------------------------------------------------------------------------------\n");  
        for(i=0;i<n;i++)  
    {  
         
     printf("%6s%10s%3s%10d%10s%10d%10d%10d%10d    %.2lf\n",stu[i].num,stu[i].name,stu[i].sex,stu[i].age,stu[i].major,stu[i].math,stu[i].English,stu[i].Clanguage,stu[i].sum,stu[i].average);  
    }  
        printf("����������������������������������������������������������������������������������\n");  
        fclose(fp);
	
	} 


	
	if(h<1&&h>5)
	{
		printf("�������\n");	
	}
	int m;
	printf("\n������һ���˵��밴1���������˵��밴2���˳��밴0: ");
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


//8.ѧ���ɼ�ͳ��
int infor_tongji1(void)
{
	int x,k;  
  
    printf("********************����ͳ��ѡ��**********************\n"); /*ѡ���ܲ˵�*/  
    printf("ͳ�Ƹ����ɼ����������밴:1\n");  
    printf("ͳ��Ӣ��ɼ����������밴:2\n");  
    printf("ͳ��C���Գɼ����������밴:3\n");             
  
    scanf("%d",&x);//�û�ѡ�����                          
    FILE  *fp;  
    fp=fopen("studentinfor.txt","rb");   
    if(x==1)  

    {  
        k=0;
        printf("����δ�����ѧ���У�\n");
        for(int i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++)/*ͳ�Ƹ����ɼ���������*/  
       {  
       		
        	if(stu[i].math<60)
			{
				k++;
				printf("ѧ�ţ�%s\t\t������%s\t\tרҵ��%s\t\t������%d\t\t\n",stu[i].num,stu[i].name,stu[i].major,stu[i].math);  
       		}
	   }  
        printf("��%d�˸���δ����\n",k);
		  
  
        printf("************************************************************\n");  
    }  
  
    
    if(x==2)  
    {  
     	k=0;  
     	printf("Ӣ��δ�����ѧ���У�\n");
        for(int i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++)/*ͳ��Ӣ��ɼ���������*/  
       {  
           if(stu[i].English<60)
		   {
				k++;
				printf("ѧ�ţ�%s\t\t������%s\t\tרҵ��%s\t\t������%d\t\t\n",stu[i].num,stu[i].name,stu[i].major,stu[i].English);  
       		}    
       }  
        printf("��%d��Ӣ�ﲻ����\n",k);  
        printf("  **********************************************************\n");  
    }  
    if(x==3)  
    {  
     	k=0;
		printf("C����δ�����ѧ���У�\n");  
        for(int i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++)/*ͳ��Ӣ��ɼ���������*/  
       {  
           if(stu[i].Clanguage<60)
		   {
				k++;
				printf("ѧ�ţ�%s\t\t������%s\t\tרҵ��%s\t\t������%d\t\t\n",stu[i].num,stu[i].name,stu[i].major,stu[i].Clanguage);  
       		}       
       }  
        printf("��%d��C���Գɼ�������\n",k);  
        printf("  **********************************************************");  
    }
    int m;
	printf("\n������һ���˵��밴1���������˵��밴2���˳��밴0: ");
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
  
    printf("********************����ͳ��ѡ��**********************\n"); /*ѡ���ܲ˵�*/  
    printf("ͳ�Ƹ����ɼ����������밴:1\n");  
    printf("ͳ��Ӣ��ɼ����������밴:2\n");  
    printf("ͳ��C���Գɼ����������밴:3\n");             
  
    scanf("%d",&x);//�û�ѡ�����                          
    FILE  *fp;  
    fp=fopen("studentinfor.txt","rb");   
    if(x==1)  
  
    {  
        k=0;  
        for(int i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++)/*ͳ�Ƹ����ɼ���������*/  
       {  
           if(stu[i].math<60)  
                k++,  
                printf("������ķ���Ϊ%d\n",stu[i].math);  
       }  
        printf("��%d�˸���δ����\n",k);  
  
        printf("************************************************************\n");  
    }  
  
    
    if(x==2)  
    {  
     k=0;  
        for(int i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++)/*ͳ��Ӣ��ɼ���������*/  
       {  
           if(stu[i].English<60)  
                 k++,  
            printf("������ķ���Ϊ%d\n",stu[i].English);       
       }  
        printf("��%d��Ӣ�ﲻ����\n",k);  
        printf("  **********************************************************");  
    }  
    if(x==3)  
    {  
     k=0;  
        for(int i=0;fread(&stu[i],sizeof(struct  student_infor),1,fp)==1;i++)/*ͳ��Ӣ��ɼ���������*/  
       {  
           if(stu[i].Clanguage<60)  
                 k++,  
            printf("������ķ���Ϊ%d\n",stu[i].Clanguage);       
       }  
        printf("��%d��C���Գɼ�������\n",k);  
        printf("  **********************************************************");  
    }
    int m;
	printf("\n������һ���˵��밴1���������˵��밴2���˳��밴0: ");
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

void captcha(char str[],int n)//��֤��
{
    char a[]="1234567890abcdefghijkmnopqrstuvwxyzABCDEFGHIJLMNPQRSTUVWXYZ";
    int i,j,k;
    k=strlen(a);//k��ʾ�ַ����ĳ���
    srand(time(0));//�������ʼ��
    for(i=0;i<n;i++)
    {
        j=rand()%k;//ȡ0-58�������
        str[i]=a[j];
    }
    str[i]='\0';
}


int main(int argc, char *argv[])
{
	
	char result=' ';
	char choice=' ';
	char title[]="\t\t\t*********��ӭ����ѧ����Ϣ����ϵͳ��********\n\n\n\n\n\n\n\t\t\t\t    2018��5��30��\n\n\n\n\n\n\n\t\t\t\t      KangWenZhe\n";
	//1:��ʼ�����ںͽ���
	Window(title);
	
	
	Sleep(3000);
	lead *lea;
	//����һ������Ա������������Ա����Ϣ 
    lea = (lead*)malloc(sizeof(lead));
	
    
	login();

	
	return 0;
	
} 

