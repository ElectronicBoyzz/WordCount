#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 30//ÿ�����ʵ���󳤶�Ϊ30
typedef struct node{
	char word[MAXSIZE];//����
	int fre;//����Ƶ��
	struct node *nextW;//ָ����һ���ڵ�
}NODE,*wordNode;//�ʽڵ�
//�ִʱ�
typedef struct {
	//����26����ĸ����з�����ڽӱ�
	wordNode first;//ָ��ĵ�һ����
}WordList;
void getWord(FILE*fp,char *string){//���ļ���ѡ������
	char ch=fgetc(fp);
	int i=0;
	while(!feof(fp)&&(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z')){//д��
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
	wordNode p;//ָ��
	if((fp=fopen(filename,"r"))==NULL){
		printf("failed to open the file!\n");
		return 0;
	}
	WordList wlist[26];//26Ӣ����ĸ
	for(i=0;i<26;i++){
		wordNode firstHead=(wordNode)malloc(sizeof(NODE));
		firstHead->nextW=NULL;
		wlist[i].first=firstHead;//���ͷ�ڵ���г�ʼ��,���ͷ���Ŀ���Ƿ������ڵ�
	}
	while(!feof(fp)){//��δ���ļ�ĩβʱ
		getWord(fp,temp);//��ȡword
		if(temp[0]!='\0'){//���˵���ַ�����Ϊ��ʱ
			char ch=temp[0];
			if(ch>='A'&&ch<='Z')
				ch=ch+'a'-'A';//��дתСд
			ch-='a';//ת������
			p=wlist[ch].first;
			while(p->nextW){
				//Ѱ�Һ��ʵĲ���λ��
				int result=strcmp(temp,p->nextW->word);
				if(result<=0)//�ҵ�����λ��
				{
					if(result==0){//��ͬ
						p->nextW->fre+=1;//Ƶ�μ�һ�˳�
						break;
					}else{
						//�µĵ��ʣ����ٿռ���д���
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
			if(p->nextW==NULL){//δ�ҵ���ͬ������ӵ���
				wordNode q=(wordNode)malloc(sizeof(NODE));
				q->fre=1;
				strcpy(q->word,temp);
				q->nextW=p->nextW;
				p->nextW=q;
			}
		}
	}//��ʾ���
	int j = 0;
	for(j=0;j<26;j++){
		p=wlist[j].first;
		while(p->nextW){
 
			printf("%s's frequent=%d\n",p->nextW->word,p->nextW->fre);
			p=p->nextW;
		}
	}
	//�����Ҫ�������Ļ����Խ⿪ע�����´���
	/*FILE *fp2=fopen("data.txt","w");//data.txtΪ����Ҫ���������ļ�����
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
