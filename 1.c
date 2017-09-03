#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "time.h"
#include "stdio.h"
#define blocksize 1024
#define inodenum 80
#define blocknum 640
//FILE *fp;
char buffer[blocksize];
void Putblk(char buf[],int blk_no,int offset,FILE *fp) {
  fseek(fp,blk_no*blocksize+offset,SEEK_SET);
  fputs(buf,fp);
  //printf("len%lu",strlen(buf));
}
void Getblk(char buf[], int blk_no,FILE *fp){
	fseek(fp,blk_no*blocksize,SEEK_SET);
	fgets(buf,blocksize,fp);
	//printf("len%lu",strlen(buf));
	return;
}
void fill(char c[],int len) {
  int i;
  for(i=0;i<len;i++) {
    if(c[i]=='\0') {
      c[i]='0';
    }
  }
}
void del(char c[],int len) {
  int i;
  for(i=0;i<len;i++) {
    c[i]='\0';
  }
}
void del1(char c[],int len) {
  int i;
  for(i=0;i<len;i++) {
    c[i]='0';
  }
}

struct SuperBlock {//第二块 1
  char dbb;//datablockbitmap的位置
  char ib;//inodebitmap的位置
  char it;//inodetable的位置
  char db;//batablock的位置
}superblock={2,3,4,9}; 
struct Inode {
	char address[26];          //kuai bianhao 0 3*8=24
	char date[9];              //20170101
	char type;	           //1-mulu 0-wenjian
	char name[29];             //filename
}inode[80];      //64B*16
char DataBlockBitmap[blocksize]={'\0'};
char InodeBitmap[blocksize]={'\0'};

void Create(FILE* fp) {//在根目录创建
  int choice;
  char filename[20];
  printf("新建：1.文件 2.文件夹\n");
  scanf("%d",&choice);
  int i,j; 
  for(i=0;i<inodenum;i++) {
    if(InodeBitmap[i]=='\0') {
      InodeBitmap[i]='1';
      break;
    }//if
  }//for
  for(j=0;j<blocknum;j++) {
    if(DataBlockBitmap[j]=='\0') {
      DataBlockBitmap[j]='1';
      break;
    }//if
  }//for
  /*int k=0;
  while(address[k]!=0) {
    k++;
  }*/ 
  inode[i].address[0]='1';
  if(j<10) {
    inode[i].address[1]='0';
    inode[i].address[2]='0';
    inode[i].address[3]=(char)(j+48);
  }
  else if(j>=10&&j<100) {
    inode[i].address[1]='0';
    inode[i].address[2]=(char)(j/10+48);
    inode[i].address[3]=(char)(j%10+48);
  }
  else if(j>=100) {
    inode[i].address[1]=(char)(j/100+48);
    inode[i].address[2]=(char)(j/10+48);
    inode[i].address[3]=(char)(j%10+48);
  }
  if(choice==1) {//普通文件
    printf("请输入文件名：");
    scanf("%s",filename);
    strncpy(inode[i].name,filename,29);  
    fill(inode[i].name,29);  
    inode[i].type='0'; 
  }//1 
  if(choice==2) {//文件夹
    printf("请输入文件夹名：");
    scanf("%s",filename);
    strncpy(inode[i].name,filename,29); 
    fill(inode[i].name,29);  
    inode[i].type='1'; 
  }
   time_t rawtime;
    struct tm *timeinfo;
    
    time(&rawtime);				// 获取系统时间
    timeinfo = localtime(&rawtime);	// 转换本地时间
    char year[4];
    year[0]='2';
    year[1]='0';
    year[2]=(timeinfo->tm_year-100)/10+'0';
    year[3]=(timeinfo->tm_year-100)%10+'0';
    //printf("%s\n",year);
    char month[2];
    month[0]=(timeinfo->tm_mon +1)/10+'0';
    month[1]=(timeinfo->tm_mon +1)%10+'0';
    //printf("%s\n",month);
    char day[2];
    day[0]=timeinfo->tm_mday/10+'0';
    day[1]=timeinfo->tm_mday%10+'0';
    //printf("%s\n",day);
    strncat(inode[i].date,year,4);
    strncat(inode[i].date,month,2);
    strncat(inode[i].date,day,2);
    //printf("%smmm\n",inode[i].date);
}
void Create1(FILE* fp,int cur) {//在当前目录创建，cur为直接外层文件夹的索引节点号
  int choice;
  char filename[20];
  if(inode[cur].type=='1') {
     printf("新建：1.文件 2.文件夹\n");
  scanf("%d",&choice);
  int i,j; 
  for(i=0;i<inodenum;i++) {
    if(InodeBitmap[i]=='\0') {
      InodeBitmap[i]='1';
      break;
    }//if
  }//for
  for(j=0;j<blocknum;j++) {
    if(DataBlockBitmap[j]=='\0') {
      DataBlockBitmap[j]='1';
      break;
    }//if
  }//for
  /*int k=0;
  while(address[k]!=0) {
    k++;
  }*/ 
    inode[i].address[0]='1';
    if(j<10) {
    inode[i].address[1]='0';
    inode[i].address[2]='0';
    inode[i].address[3]=(char)(j+48);
     }
  else if(j>=10&&j<100) {
    inode[i].address[1]='0';
    inode[i].address[2]=(char)(j/10+48);
    inode[i].address[3]=(char)(j%10+48);
  }
  else if(j>=100) {
    inode[i].address[1]=(char)(j/100+48);
    inode[i].address[2]=(char)(j/10+48);
    inode[i].address[3]=(char)(j%10+48);
  }
  if(choice==1) {//普通文件
    printf("请输入文件名：");
    scanf("%s",filename);
    strcpy(inode[i].name,filename);
    fill(inode[i].name,29);  
    inode[i].type='0'; 
  }//1 
  if(choice==2) {//文件夹
    printf("请输入文件夹名：");
    scanf("%s",filename);
    strcpy(inode[i].name,filename); 
    fill(inode[i].name,29);  
    inode[i].type='1'; 
  }
  int sit;
  int now=(inode[cur].address[0]-'0')*3;
  sit=(inode[cur].address[now]-'0')+10*(inode[cur].address[now-1]-'0')+100*(inode[cur].address[now-2]-'0');
  
  //printf("%d\n",now);
  //printf("%d\n",sit);
  char buf[blocksize];
  Getblk(buf,sit+9,fp);
  int k=0;
  char t[2];
  if(i<10) {
    t[0]='0';
    t[1]=(char)(i+48);
  }
  else {
    t[0]=(char)(i/10+48);
    t[1]=(char)(i%10+48);
  }
  while(buf[k]&&buf[k]!='0') {
    k+=31;
  }
  if(k==1022) {
    inode[cur].address[0]+=1;
    for(j=0;j<blocknum;j++) {
      if(DataBlockBitmap[j]=='\0') {
        DataBlockBitmap[j]='1';
        break;
      }//if
    }//for
    if(j<10) {
      inode[cur].address[now+1]='0';
      inode[cur].address[now+2]='0';
      inode[cur].address[now+3]=(char)(j+48);
    }
    else if(j>=10&&j<100) {
      inode[cur].address[now+1]='0';
      inode[cur].address[now+2]=(char)(j/10+48);
      inode[cur].address[now+3]=(char)(j%10+48);
    }
    else if(j>=100) {
      inode[cur].address[now+1]=(char)(j/100+48);
      inode[cur].address[now+2]=(char)(j/10+48);
      inode[cur].address[now+3]=(char)(j%10+48);
    }
    Putblk(inode[i].name,j+9,0,fp);
    Putblk(t,j+9,29,fp);
    //printf("%s\n",inode[1].address);
  }
  else {
    Putblk(inode[i].name,sit+9,k,fp);
    Putblk(t,sit+9,k+29,fp);
  }
  time_t rawtime;
    struct tm *timeinfo;
    
    time(&rawtime);				// 获取系统时间
    timeinfo = localtime(&rawtime);	// 转换本地时间
    char year[4];
    year[0]='2';
    year[1]='0';
    year[2]=(timeinfo->tm_year-100)/10+'0';
    year[3]=(timeinfo->tm_year-100)%10+'0';
    //printf("%s\n",year);
    char month[2];
    month[0]=(timeinfo->tm_mon +1)/10+'0';
    month[1]=(timeinfo->tm_mon +1)%10+'0';
    //printf("%s\n",month);
    char day[2];
    day[0]=timeinfo->tm_mday/10+'0';
    day[1]=timeinfo->tm_mday%10+'0';
    //printf("%s\n",day);
    strncat(inode[i].date,year,4);
    strncat(inode[i].date,month,2);
    strncat(inode[i].date,day,2);
    //printf("%smmm\n",inode[i].date);
  }//mulu
  else {
    printf("不能在文件中创建文件\n");
  }//wenjian
}


void load_inodetable(FILE* fp){
int i,j;
	for(i=0;i<5;i++){
	    char buf[blocksize]={'\0'};
		Getblk(buf,(4+i),fp);
		//printf("%s\n",buf);
		for(j=0;j<1024;j=j+64){
			int ino=i*16+j/64;       //4*16+15=79
			if(InodeBitmap[ino]=='1') {
			  strncpy(inode[ino].address,&buf[j],26);
			  inode[ino].type=buf[j+34];
			  strncpy(inode[ino].name,&buf[j+35],29);
		      //printf("%s\n",inode[ino].name);
			}
		}
			
	}
	return;
}

void put_inodetable(FILE* fp){
int i,j;
	for(i=0;i<5;i++){
	    char s[blocksize]={'\0'};
		for(j=0;j<16;j++){
			if(inode[i*16+j].name[0]!='\0'&&InodeBitmap[i*16+j]=='1') {
			  fill(inode[i*16+j].address,26);
			  strncat(s,inode[i*16+j].address,26);
			  strncat(s,inode[i*16+j].date,8);
			  char t[2];
			  t[0]=inode[i*16+j].type;
			  t[1]='\0';
			  strncat(s,t,2);
			  strncat(s,inode[i*16+j].name,29);
			  //printf("%smmm\n",s);
			}
			else
			  break;
		}
		Putblk(s,i+4,0,fp);	
	}
}
int C_ino(char s2[29]){
int i;
		for(i=0;i<inodenum;i++)
		{
			//printf("%s   sss\n",s2);
			//printf("%s   inodename\n",inode[0].name);
			if(strncmp(inode[i].name,s2,29)==0)
			{
				if(InodeBitmap[i]=='1')
					return i;
				
			}
		}
		return -1;
}

int Ino_ino(int ino,char s1[29],FILE* fp){
int j;
	int k=inode[ino].address[0]-'0';
			int k1=0;
			for(j=0;j<k*3;j=j+3){
				k1=(inode[ino].address[j+1]-'0')*100+(inode[ino].address[j+2]-'0')*10+(inode[ino].address[j+3]-'0'); //data逻辑块号
				//printf("%d ",k1);
				Getblk(buffer,k1+9,fp);       //29+2=31
				//printf("buf%s   s1%s\n",buffer,s1);
				for(int p=0;p<(blocksize-30);p=p+31){										
				    char s[29]={'\0'};
					strncpy(s,&buffer[p],29);
					fill(s,29);
					//printf("sss%s",s);
					if(strncmp(s1,s,29)==0){
						int ino2=(buffer[p+29]-'0')*10+(buffer[p+30]-'0');
						if(InodeBitmap[ino2]=='1')				
							return ino2;
						else
							return -1;
					}
				}				
			}
			return -1;
}	

int Search(FILE* fp){    //return最后节点的索引号
	printf("Input (eg:/d0/d1/filename)");
	char path[100]={""};
	scanf("%s",path);
	if(path[0]!='/') {
		printf("path error!");	
		return -1;
	}
	char* s=NULL;
	//strtok(path,"/");
	int flag=0;
	int ino;
	if((s=strtok(path,"/"))){
	    char c[29]={'\0'};
	    strcpy(c,s);
	    fill(c,29);
	    //printf("%s111\n",c);
		ino=C_ino(c);
		if(ino==-1) {
			//printf("%s ",s);
			printf("error!  没有此节点1 ");
			return -1;
		}
		if(inode[ino].type=='0')            //最终文件
		{
			printf("打开文件 %s\n",s);
			return ino;
		}
		else if(inode[ino].type=='1'){
			printf("打开目录 %s\n",s);
		}  
	}
	else{
		printf("打开目录%s\n",s);
		return ino;
	}
	while((s=strtok(NULL,"/"))){
	    char c[29]={'\0'};
	    strcpy(c,s);
	    fill(c,29);
	    //printf("%s222\n",c);
		ino=Ino_ino(ino,c,fp);
		//printf("%s222\n",c);
		if((ino==-1)||(InodeBitmap[ino]!='1')){
			printf("error!没有此节点2 %s\n",s);
			return -1;
		}
		else if(inode[ino].type=='0')            //最终文件
		{
			printf("打开文件 %s\n",s);
			return ino;
		}
		else if(inode[ino].type=='1'){
			printf("打开目录1 %s\n",s);
		}
	}
	return ino;
}
	
void Show_ino(int ino,FILE* fp){
int i,j;
	int k=inode[ino].address[0]-'0';
	for(j=0;j<k*3;j=j+3){
		int k1=(inode[ino].address[j+1]-'0')*100+(inode[ino].address[j+2]-'0')*10+(inode[ino].address[j+3]-'0'); //data逻辑块号
		//printf("%d\n",k1);
		if(InodeBitmap[ino]=='1') {
		  Getblk(buffer,k1+9,fp); 
		printf("show%s\n",buffer);	      //29+2=31
		if(inode[ino].type=='0') {
		  //printf("show%s\n",buffer);	
		}//wenjian
		else if(inode[ino].type=='1') {
		  for(i=0;i<strlen(buffer);i++) {
		    if((i%31)<=28&&buffer[i]!='0') {
		      printf("%c",buffer[i]);
		    }
		    if((i%31)==30) {
		      printf(" ");
		    }
		  }//for
		}//mulu
		else {
		  printf("内容为空！\n");
		}//none			
		}//zai
		else {
		  printf("无法打开！\n");
		}
	}//for
}	
void CopyOut(FILE* fp){
 char s1[29],s2[2];
 printf("请输入要拷贝的外部文件路径：\n");
 scanf("%s",s1);
 FILE *f1;
   f1=fopen(s1,"rb+");
   if(f1==NULL){
    printf("找不到文件\n");
    return;
   }
   printf("拷贝至的文件");
   int ino=Search(fp);
   if(ino!=-1&&inode[ino].type=='0') {
      int k;
   k=(inode[ino].address[1]-'0')*100+(inode[ino].address[2]-'0')*10+(inode[ino].address[3]-'0');
   Getblk(buffer,0,f1);
   Putblk(buffer,k+9,0,fp);
   int i,j;
   for(i=1;i<8;i++){
    char buf[blocksize]={'\0'};
    Getblk(buf,i,f1);
    if(buf[0]=='\0') break;
    for(j=0;j<blocknum;j++) {
      if(DataBlockBitmap[j]=='\0') {
         DataBlockBitmap[j]='1';
         break;
        }
      }
      Putblk(buf,j+9,0,fp);
      inode[ino].address[i*3+1]=j/100;
      j=j%100;
      inode[ino].address[i*3+2]=j/10;
      j=j%10;
      inode[ino].address[i*3+3]=j;
  }
     char buf[blocksize]={'\0'};
     Getblk(buf,8,f1);
     if(buf[0]!='\0'){
      printf("外部文件过大，仅拷贝8K");
     }
     inode[ino].address[0]=i+'0';
     Putblk(DataBlockBitmap,2,0,fp);   
   } //find
   else {
     printf("复制路径不正确!\n");
   }//not
   fclose(f1);
   return ;
}
void Delete(FILE* fp) {
 int j;
 char path[100]={""};
 printf("请输入要删除的文件的目录:\n");
 scanf("%s",path);
 if(path[0]!='/') {
  printf("path error!"); 
  return ;
 }
 char* s=NULL;
 //strtok(path,"/");
 int flag=0;
 int duo=0;
 int ino;
 int ino2;
 if((s=strtok(path,"/"))){
     char c[29]={'\0'};
     strcpy(c,s);
     fill(c,29);
     //printf("%s111\n",c);
  ino=C_ino(c);
  if(ino==-1) {
   //printf("%s ",s);
   printf("error!  没有此节点%s ",s);
   flag=-1;
  }
  flag=1;
 }
else{
  printf("没有输入");
  flag=-1;
 }
 char s5[30]={'\0'};
 while((s=strtok(NULL,"/"))){
     duo=1;
 	 strcpy(s5,s);
     char c[29]={'\0'};
     strcpy(c,s);
     fill(c,29);
     ino2=ino;
  ino=Ino_ino(ino,c,fp);
  if((ino==-1)||(InodeBitmap[ino]!='1')){
   printf("error!没有此节点 %s\n",s);
   flag=-1;
  }
  else if(strncmp(inode[ino].name,s,29)==0)            
  {
   flag=1;
   break;
  }  
 }//while
 if(duo==1) {
    int i1,j1;                                        //父目录
  int k2=inode[ino2].address[0]-'0';
  int k3=0;
  int inumber=0;
  int index=0;
  char ch[264][31]={'\0'};                                    //30个inode-no
  int flag1=0;
  for(i1=0;i1<k2*3;i1=i1+3){
   k3=(inode[ino2].address[i1+1]-'0')*100+(inode[ino].address[i1+2]-'0')*10+(inode[ino].address[i1+3]-'0');   //data block 号
   Getblk(buffer,k3+9,fp);
   for(j1=0;j1<1024;j1=j1+31){
    if(buffer[j1]=='\0'){
     flag1=1;
     break;
    }
    strncpy(ch[inumber],&buffer[j1],31);                        //load进ch[][]数组
    if(strncmp(ch[inumber],s5,29)==0) index=inumber;              //此记录存在第index号
    inumber++;
   }
   if(flag1==1) break;  
  }
   //del(ch[index],31);
   //printf("%dmmm\n",index);
   del1(ch[index],31);
   Putblk(ch[index],index/31+9,index%31*31,fp);
  }
 if(flag==-1){
  printf("删除失败\n%s",s);
 }
 else if(flag==1){
  del(inode[ino].name,29);
  del(inode[ino].address,26);
  del(inode[ino].date,8);
  inode[ino].type='\0';
  //printf("%dmia",ino);
  InodeBitmap[ino]='\0';
  int k=inode[ino].address[0]-'0';
  int k1=0;
 for(j=0;j<k*3;j=j+3){
   k1=(inode[ino].address[j+1]-'0')*100+(inode[ino].address[j+2]-'0')*10+(inode[ino].address[j+3]-'0');
   DataBlockBitmap[k1]='\0';
  }
  
  
  //  所有记录在ch[264][31] 里   0---inumber-1 ; 
  //  要删去的节点是 i=index 时的
  
  // 需写回，块号为for(i1=0;i1<k2*3;i1=i1+3){
  //  k3=(inode[ino2].address[i1+1]-'0')*100+(inode[ino].address[i1+2]-'0')*10+(inode[ino].address[i1+3]-'0');  
  // 
  //
  //    
  }
}
void Write_block(FILE* fp) {
  int cur;
  cur=Search(fp);
  if(cur!=-1) {
    if(inode[cur].type=='1') {
      printf("当前位于文件夹中\n");
    }
    else if(inode[cur].type=='0') {
      char s[8192]={'\0'};
      printf("请输入内容:\n");
      scanf("%s",s);
      int now=(inode[cur].address[0]-'0')*3;
      int sit=(inode[cur].address[now]-'0')+10*(inode[cur].address[now-1]-'0')+100*(inode[cur].address[now-2]-'0');
      if(strlen(s)<=1024) {
        Putblk(s,sit+9,0,fp);
      }//1
      int i;
      for(i=1;i<8;i++) {
        now=(inode[cur].address[0]-'0')*3;
        char buf[blocksize]={'\0'};
        strncpy(buf,&s[1024],blocksize);
        if(buf[0]=='\0')break;
        else {
          int j;
          inode[cur].address[0]+=1;
          for(j=0;j<blocknum;j++) {
          if(DataBlockBitmap[j]=='\0') {
          DataBlockBitmap[j]='1';
          break;
        }//if
       }//for
      if(j<10) {
        inode[cur].address[now+1]='0';
        inode[cur].address[now+2]='0';
        inode[cur].address[now+3]=(char)(j+48);
      }
      else if(j>=10&&j<100) {
        inode[cur].address[now+1]='0';
        inode[cur].address[now+2]=(char)(j/10+48);
        inode[cur].address[now+3]=(char)(j%10+48);
      }
      else if(j>=100) {
        inode[cur].address[now+1]=(char)(j/100+48);
        inode[cur].address[now+2]=(char)(j/10+48);
        inode[cur].address[now+3]=(char)(j%10+48);
      }
       sit=(inode[cur].address[now]-'0')+10*(inode[cur].address[now-1]-'0')+100*(inode[cur].address[now-2]-'0');
       Putblk(buf,sit+9,0,fp);
        }//else
      }//>1
    } 
  }
  else
    printf("wrong\n");
}
int main() {
  FILE *fp;
  fp=fopen("2.txt","rb+");
  Getblk(DataBlockBitmap,2,fp);
  Getblk(InodeBitmap,3,fp);
  load_inodetable(fp);
  int i;
  int choice;
  for(i=0;;i++) {
    printf("请选择操作：1.新建 2.删除 3.打开 4.修改 5.复制 6.退出\n");
    scanf("%d",&choice);
    if(choice==1) {//新建
      int c=0;
       printf("1.在根目录创建 2.在某一文件夹下创建\n");
       scanf("%d",&c);
       if(c==1) {
         Create(fp);
         //printf("%s\n",inode[0].name);
       }//gen
       else if(c==2) {
         int cur;
         cur=Search(fp);
         if(cur!=-1) {
           Create1(fp,cur);
           //printf("%s\n",inode[0].name);
         }
       }//lujing
    }//1
    if(choice==2) {
      Delete(fp);
    }//2
    if(choice==3) { 
      int cur;
      cur=Search(fp);
      if(cur!=-1) {
        Show_ino(cur,fp);
      }
    }//3
    if(choice==4) {
      Write_block(fp);
    }
    if(choice==5) {
      CopyOut(fp);
    }//5
    if(choice==6) {
      break;
    }//6
  }
  Putblk(DataBlockBitmap,2,0,fp);
  Putblk(InodeBitmap,3,0,fp);
  put_inodetable(fp);
  fclose(fp);
}
