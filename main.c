#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 30//每个单词的最大长度为30
typedef struct node{
	char word[MAXSIZE];//单词
	int fre;//出现频次
	struct node *nextW;//指向下一个节点
}NODE,*wordNode;//词节点
//分词表
typedef struct {
	//按照26个字母表进行分类的邻接表
	wordNode first;//指向的第一个词
}WordList;
void getWord(FILE*fp,char *string){//从文件中选出单词
	char ch=fgetc(fp);
	int i=0;
	while(!feof(fp)&&(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z')){//写入
		string[i++]=ch;
		ch=fgetc(fp);
	}
	string[i]='\0';
}
int main(void){
	FILE *fp;
	char temp[MAXSIZE];
	int i=0;
	char *filename="./test.txt";
	wordNode p;//指针
	if((fp=fopen(filename,"r"))==NULL){
		printf("failed to open the file!\n");
		return 0;
	}
	WordList wlist[26];//26英文字母
	for(i=0;i<26;i++){
		wordNode firstHead=(wordNode)malloc(sizeof(NODE));
		firstHead->nextW=NULL;
		wlist[i].first=firstHead;//添加头节点进行初始化,添加头结点目的是方便插入节点
	}
	while(!feof(fp)){//当未到文件末尾时
		getWord(fp,temp);//获取word
		if(temp[0]!='\0'){//如果说该字符串不为空时
			char ch=temp[0];
			if(ch>='A'&&ch<='Z')
				ch=ch+'a'-'A';//大写转小写
			ch-='a';//转成数字
			p=wlist[ch].first;
			while(p->nextW){
				//寻找合适的插入位置
				int result=strcmp(temp,p->nextW->word);
				if(result<=0)//找到插入位置
				{
					if(result==0){//相同
						p->nextW->fre+=1;//频次加一退出
						break;
					}else{
						//新的单词，开辟空间进行储存
						wordNode q=(wordNode)malloc(sizeof(NODE));
						q->fre=1;
						strcpy(q->word,temp);
						q->nextW=p->nextW;
						p->nextW=q;
					}
				}else{
					p=p->nextW;
				}
			}			
			if(p->nextW==NULL){//未找到相同词则添加单词
				wordNode q=(wordNode)malloc(sizeof(NODE));
				q->fre=1;
				strcpy(q->word,temp);
				q->nextW=p->nextW;
				p->nextW=q;
			}
		}
	}//显示结果
	int j = 0;
	for(j=0;j<26;j++){
		p=wlist[j].first;
		while(p->nextW){
 
			printf("%s's frequent=%d\n",p->nextW->word,p->nextW->fre);
			p=p->nextW;
		}
	}
	//如果想要保存结果的话可以解开注释以下代码
	/*FILE *fp2=fopen("data.txt","w");//data.txt为你想要保存结果的文件名称
	for(int j=0;j<26;j++){
		p=wlist[j].first;
		while(p->nextW){
			fprintf(fp2,"%s's frequent=%d\n",p->nextW->word,p->nextW->fre);
			p=p->nextW;
		}
	}
	fclose(fp2);*/
	fclose(fp);
}
