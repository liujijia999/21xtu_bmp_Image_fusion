#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> 

typedef unsigned char  U8;
typedef unsigned short U16;
typedef unsigned int   U32;

#pragma pack(1)
typedef struct BMPFileHeader//λͼ�ļ�ͷ
{
	U16	bfType;			// �ļ���ʶ�� 
	U32	bfSize;			// �ļ��Ĵ�С
	U16	bfReserved1;	// ����ֵ
	U16	bfReserved2;	// ����ֵ
	U32	bfOffBits;		// �ļ�ͷ�����ͼ������λ��ʼ��ƫ����
}BMPFi;// 14 �ֽ�

typedef struct BMPInformation//λͼ��Ϣͷ
{
	U32	bSize;			// ��Ϣͷ�Ĵ�С
	U32	bWidth;			// ͼ��Ŀ���
	U32	bHeight;		// ͼ��ĸ߶� 
	U16	bPlanes;		// ͼ���λ����
	U16 bBitCount;		// ÿ�����ص�λ��
	U32	bCompression;	// ѹ������
	U32	bmpImageSize;   // ͼ��Ĵ�С,���ֽ�Ϊ��λ
	U32	bXPelsPerMeter; // ˮƽ�ֱ���  ����/�� 
	U32	bYPelsPerMeter; // ��ֱ�ֱ��� 
	U32	bClrUsed;       // ʹ�õ�ɫ����
	U32	bClrImportant;  // ��Ҫ����ɫ��
}BMPIn;// 40 �ֽ�

#pragma  pack()
typedef struct cut_image//��¼�����Դ�Ľṹ�� 
{
	int da;				//��ֵΪ1����Ӧ������ͼһ ����ֵΪ2����Ӧ������ͼ�� 
	int cnt1;			//����������¼����Χ����ͼһ�Ŀ������ 
	int cnt2;			//����������¼����Χ����ͼ���Ŀ������ 
}cut;
void print (BMPFi * bmpf,BMPIn * bmpi)
{
	printf("�ļ���ʶ��=%c%c\n",					bmpf->bfType%256,bmpf->bfType/256);
	printf("BMP�ļ���С��%dkb\n",				bmpf->bfSize/1024);
    printf("�����ֱ���Ϊ0��%d\n",  				bmpf->bfReserved1);
    printf("�����ֱ���Ϊ0��%d\n",				bmpf->bfReserved2);
    printf("ʵ��λͼ���ݵ�ƫ���ֽ���: %d\n",	bmpf->bfOffBits);
	printf("λͼ��Ϣͷ:\n" );   
    printf("��Ϣͷ�Ĵ�С:%d\n" ,				bmpi->bSize);   
    printf("λͼ����:%d\n" ,					bmpi->bWidth);   
    printf("λͼ�߶�:%d\n" ,					bmpi->bHeight);   
    printf("��ɫ�������,Ĭ��Ϊ1����ɫ��:%d\n",	bmpi->bPlanes);   
    printf("ÿ�����ص�λ��:%d\n" ,				bmpi->bBitCount);   
    printf("ѹ����ʽ:%d\n" ,					bmpi->bCompression);   
    printf("ͼ��Ĵ�С:%d\n" ,					bmpi->bmpImageSize);   
    printf("ˮƽ����ֱ���:%d\n" ,				bmpi->bXPelsPerMeter);   
    printf("��ֱ����ֱ���:%d\n" ,				bmpi->bYPelsPerMeter);   
    printf("ʹ�õ���ɫ��:%d\n" ,				bmpi->bClrUsed);   
    printf("��Ҫ��ɫ��:%d\n" ,					bmpi->bClrImportant);  
}
U8 * read_image (BMPFi * bmpf, BMPIn * bmpi,U8 *pallet,U8 * date)
{
	FILE*f=NULL;									// �ļ�ָ�� 
	char bmp_name [100];							//�洢·�����ַ��� 
	printf("������ԭʼͼ���ļ�·��:\n");
	scanf ("%s",bmp_name);							//����ͼ��·�� 
	f=fopen (bmp_name,"rb");						//��ͼ�� 
	//���ļ�ͷ 
	fread (bmpf,sizeof(BMPFi),1,f);
	fread (bmpi,sizeof(BMPIn),1,f);
	int width=(int)bmpi->bWidth;
	int hight=(int)bmpi->bHeight;
	date=(U8 *)calloc(width*hight,sizeof(U8 ));
	//����ɫ�� 
	fread (pallet,1024,1,f);
	//��ȡλͼ���� 
	fread (date,width*hight*sizeof(U8 ),1,f);
	fclose(f);
	return date;									//����λͼ���ݵ�ָ�� 
}

int main()
{
	int size;										//sizeΪҪ�ֳɶ��ٳ˶��ٵĿ� 
	printf ("����Ҫ��ͼƬ�ֳɶ��ٳ˶��ٵģ���������ֳ�8*8��64�飬����8���ɡ�\n������һ�����֣�\n");
	scanf ("%d",&size);
	//��ȡ���� 
	BMPFi bmpf1;										//λͼ�ļ�ͷ 
	BMPIn bmpi1;										//λͼ��Ϣͷ 
	U8 pallet1[1024];									//��ɫ��				
	U8 * date1;											//λͼ���� 
	date1=read_image (&bmpf1,&bmpi1,pallet1,date1);		//��ȡ����	����print���� 
	print(&bmpf1,&bmpi1);								//��ӡ��Ϣ 	
	
	BMPFi bmpf2;										//λͼ�ļ�ͷ 
	BMPIn bmpi2;										//λͼ��Ϣͷ 
	U8 pallet2[1024];									//��ɫ��
	U8 * date2;											//λͼ���� 
	date2=read_image (&bmpf2,&bmpi2,pallet2,date2);		//��ȡ����	����print����	
	print(&bmpf2,&bmpi2);								//��ӡ��Ϣ 	
	
	int width=(int)bmpi1.bWidth;						//ͼ����� 
	int hight=(int)bmpi1.bHeight;						//ͼ��߶� 
	
	//����ת��ά 
	int i,j,k=0;
	U8** date_1;										//����ָ����������ռ�洢תΪ��ά��λͼ���� 
	U8** date_2;
	date_1=(U8**)malloc(sizeof(U8*)*hight);				//����ָ������һ��ָ�� 
	date_2=(U8**)malloc(sizeof(U8*)*hight);
	for (i=0;i<hight;i++){								//����洢�ռ� 
		date_1[i]=(U8*)malloc(sizeof(U8)*width);
		date_2[i]=(U8*)malloc(sizeof(U8)*width);
	}
	for (i=0;i<hight;i++){				
		for (j=0;j<width;j++){		
			date_1[i][j]=date1[k];						//��һά����תΪ��ά���������Ĵ��� 
			date_2[i][j]=date2[k];
			if(i==0||j==0||i%(hight/size)==0||j%(hight/size)==0) {
				date1[k]=(U8)255;						//��ԭ�������ݷֿ� 
				date2[k]=(U8)255;
			}
			k++;
		}
	}
	//���ԭͼ�ֿ�ͼ 
	printf("\n�����Ƿ�Ҫ���ԭͼ�ֿ�ͼ\n������1��0 1Ϊ�����0Ϊ�����:\n");
	int d;
	scanf ("%d",&d);
	if (d){
		FILE* fp=NULL;									//�ļ�ָ�� 
		FILE* fq=NULL;
		char name1[20]="Block_1.bmp";					//����ֿ�ͼ������ 
		char name2[20]="Block_2.bmp";
		fp=fopen (name1,"wb");							//���ļ� 
		fq=fopen (name2,"wb");
		if (fp==NULL){
			printf ("����ʧ��\n");
		}
		fwrite(&bmpf1,sizeof (BMPFi),1,fp);				//д������ 
		fwrite(&bmpi1,sizeof (BMPIn),1,fp);
		fwrite(&bmpf2,sizeof (BMPFi),1,fq);
		fwrite(&bmpi2,sizeof (BMPIn),1,fq);
		fwrite(pallet1,sizeof(U8)*1024,1,fp);
		fwrite(pallet2,sizeof(U8)*1024,1,fq);
		fwrite(date1,sizeof(U8)*hight*width,1,fp);
		fwrite(date2,sizeof(U8)*hight*width,1,fq);
		printf ("�ֿ�ͼ������\n");
		fclose(fp);
		fclose(fq);
	}
	free(date1);										//�ͷ�ָ���ֹ�ڴ�й© 
	free(date2);
	//����
	U8 date_11[(hight/size+1)*size][(width/size+1)*size];			// ����洢����֮������ݵĿռ� 
	U8 date_22[(hight/size+1)*size][(width/size+1)*size];
	if (hight%size!=0&&width%size!=0){								// ���͸߶�������size����� 
		for (i=0;i<(hight/size+1)*size;i++){			//����ͼƬ		(hight/size+1)*sizeΪ����֮��ĸ� 
			for (j=0;j<(width/size+1)*size;j++){					// (width/size+1)*sizeΪ����֮��Ŀ� 
				if (i<hight&&j<width){								// ��������δ����ԭͼ 
					date_11[i][j]=date_1[i][j];						// �������� 
					date_22[i][j]=date_2[i][j];
				}
				else if (i>=hight&&j<width){						//�������򳬹�ԭͼ����ߵ�δ���������Գ������ֿ�ʼ���أ� 
					date_11[i][j]=date_1[2*hight-i-1][j];			//�������ֵ������±�Ϊ 2*hight-i-1
					date_22[i][j]=date_2[2*hight-i-1][j];
				}
				else if (i<hight&&j>=width){						// �������򳬹�ԭͼ�������δ�����ߣ��Գ������ֿ�ʼ���أ� 
					date_11[i][j]=date_1[i][2*width-j-1];
					date_22[i][j]=date_2[i][2*width-j-1];
				}
				else if (i>=hight&&j>=width){						// �������򳬹�ԭͼ������͸ߣ��Գ������ֿ�ʼ���أ� 
					date_11[i][j]=date_1[2*hight-i-1][2*width-j-1];
					date_22[i][j]=date_2[2*hight-i-1][2*width-j-1];
				}
			}
		}
		hight=(hight/size+1)*size;						//��Ϊ���أ����ݵĸ߸ı� 
		width=(width/size+1)*size;						//��Ϊ���أ����ݵĿ��ı� 
	}
	else if (hight%size!=0&&width%size==0){				//�߳�����size����� 
		for (i=0;i<(hight/size+1)*size;i++){
			for (j=0;j<width;j++){
				if (i<hight&&j<width){
					date_11[i][j]=date_1[i][j];
					date_22[i][j]=date_2[i][j];
				}
				else if (i>=hight&&j<width){
					date_11[i][j]=date_1[2*hight-i-1][j];
					date_22[i][j]=date_2[2*hight-i-1][j];
				}
			}
		}
		hight=(hight/size+1)*size;
	}
	else if (hight%size==0&&width%size!=0){				//��������size����� 
		for (i=0;i<hight;i++){
			for (j=0;j<(width/size+1)*size;j++){
				if (i<hight&&j<width){
					date_11[i][j]=date_1[i][j];
					date_22[i][j]=date_2[i][j];
				}
				else if (i<hight&&j>=width){
					date_11[i][j]=date_1[i][2*width-j-1];
					date_22[i][j]=date_1[i][2*width-j-1];
				}
			}
		}
		width=(width/size+1)*size;	
	}
	else{												//���ܳ�������� 
		for (i=0;i<hight;i++){
			for (j=0;j<width;j++){
				date_11[i][j]=date_1[i][j];
				date_22[i][j]=date_2[i][j];
			}
		}
	}	
	free(date_1);
	free(date_2);
	//�����ȼ��� 
	double definition1[size][size];						//��������������ȵĶ�ά���� 
	double definition2[size][size];
	for (i=0;i<size;i++){								//���� 
		for (j=0;j<size;j++){
			int x,y;
			//ˮƽ
			double HD1=0; 												//HD1Ϊ��һ�����ˮƽ������ 	HD2Ϊ�ڶ������ˮƽ������
			double HD2=0; 												//�ֿ����
			for (y=i*hight/size;y<(i+1)*(hight/size);y++){				// i*hight/sizeΪ�鿪ʼ�ĸ�     (i+1)*(hight/size)������ĸ�
				for (x=j*width/size;x<(j+1)*(width/size);x++){			// j*width/sizeΪ�鿪ʼ�Ŀ� 	(j+1)*(width/size)������Ŀ� 
					HD1+=(double)pow(date_11[y][x]-date_11[y][x+1],2);	//����ˮƽ������ 
					HD2+=(double)pow(date_22[y][x]-date_22[y][x+1],2);
				}
			}
			HD1/=(double)(width*hight/size);
			HD2/=(double)(width*hight/size);
			//��ֱ
			double VD1=0;												//VD1Ϊ��һ����Ĵ�ֱ������ 	VD2Ϊ�ڶ�����Ĵ�ֱ������
			double VD2=0;
			for (x=j*width/size;x<(j+1)*(width/size);x++){
				for (y=i*hight/size;y<(i+1)*(hight/size);y++){
					VD1+=(double)pow(date_11[y][x]-date_11[y+1][x],2);	//���㴹ֱ������ 
					VD2+=(double)pow(date_22[y][x]-date_22[y+1][x],2);
				}
			}
			VD1/=(double)(hight*width/size);		
			VD2/=(double)(hight*width/size);
			definition1[i][j]=sqrt(HD1+VD1);			//����������
			definition2[i][j]=sqrt(HD2+VD2);
		}
	} 
	for (i=size-1;i>=0;i--){//��ӡ������1 
		for (j=0;j<size;j++){
			printf ("%lf ",definition1[i][j]);
			if(j==size-1){
				printf ("\n");
			}
		}
	}
	printf ("\n");
	for (i=size-1;i>=0;i--){//��ӡ������2
		for (j=0;j<size;j++){
			printf ("%lf ",definition2[i][j]);
			if(j==size-1){
				printf ("\n");
			}
		}
	}
	//�Ƚ�������
	cut def[size][size];								//���е�ֵ�������յĿ�����������ͼƬ��ֵΪ1��ÿ����Ե�һ��ͼƬ��ֵΪ2��ÿ����Եڶ���ͼƬ���±�Ϊ���λ�� 
	for (i=0;i<size;i++){
		for (j=0;j<size;j++){
			if (definition1[i][j]>=definition2[i][j]){	//�Ƚ������������������ 
				def[i][j].da=1;				//ͼһ�����ȴ�����ͼ��Ӧ�Ŀ�����ͼһ 
				def[i][j].cnt1=0;			//def[i][j].cnt1Ϊ����������¼��def[i][j]��Χ���Ե�һ��ͼ�Ŀ���������������ǰ�����ʼ��Ϊ0 
				def[i][j].cnt2=0;			//def[i][j].cnt2Ϊ����������¼��def[i][j]��Χ���Եڶ���ͼ�Ŀ���������������ǰ�����ʼ��Ϊ0 
			}
			else{							//ͼ�������ȴ�����ͼ��Ӧ�Ŀ�����ͼ�� 
				def[i][j].da=2;
				def[i][j].cnt1=0;
				def[i][j].cnt2=0;
			}
		}
	} 
	for (i=size-1;i>=0;i--){//��ӡ�����Դ
		for (j=0;j<size;j++){
			printf ("%d ",def[i][j].da);
			if(j==size-1){
				printf ("\n");
			}
		}
	}
	printf ("\n");
	//һ����У��
	for (i=0;i<size;i++){
		for (j=0;j<size;j++){
			if (i!=size-1&&def[i+1][j].da==1)					def[i][j].cnt1++;	//�ֱ��¼��һ������Χ��������ͼ�Ŀ������ 
			else if (i!=size-1&&def[i+1][j].da==2)				def[i][j].cnt2++;
			if (j!=size-1&&def[i][j+1].da==1)					def[i][j].cnt1++;	
			else if (j!=size-1&&def[i][j+1].da==2)				def[i][j].cnt2++;
			if (j!=0&&def[i][j-1].da==1)						def[i][j].cnt1++;	
			else if (j!=0&&def[i][j-1].da==2)					def[i][j].cnt2++;
			if (i!=0&&def[i-1][j].da==1)						def[i][j].cnt1++;	
			else if (i!=0&&def[i-1][j].da==2)					def[i][j].cnt2++;
			if (i!=size-1&&j!=size-1&&def[i+1][j+1].da==1)		def[i][j].cnt1++;	
			else if (i!=size-1&&j!=size-1&&def[i+1][j+1].da==2)	def[i][j].cnt2++;
			if (i!=0&&j!=0&&def[i-1][j-1].da==1)				def[i][j].cnt1++;	
			else if (i!=0&&j!=0&&def[i-1][j-1].da==2)			def[i][j].cnt2++;
			if (i!=0&&j!=size-1&&def[i-1][j+1].da==1)			def[i][j].cnt1++;	
			else if (i!=0&&j!=size-1&&def[i-1][j+1].da==2)		def[i][j].cnt2++;
			if (i!=size-1&&j!=0&&def[i+1][j-1].da==1)			def[i][j].cnt1++;	
			else if (i!=size-1&&j!=0&&def[i+1][j-1].da==2)		def[i][j].cnt2++;
		}	
	} 
	for (i=0;i<size;i++){							//�����Ƚ�һ������Χ��������ͼ�Ŀ������ 
		for (j=0;j<size;j++){						//����������һ��ͼ�����������������Կ����Դ 
			if (def[i][j].cnt1>=def[i][j].cnt2){
				def[i][j].da=1;
			}
			if (def[i][j].cnt1<def[i][j].cnt2){
				def[i][j].da=2;
			}
			def[i][j].cnt1=0;
			def[i][j].cnt2=0;
		}
	}
	for (i=size-1;i>=0;i--){//��ӡ�����Դ ��һ����У��� 
		for (j=0;j<size;j++){
			printf ("%d ",def[i][j].da);
			if(j==size-1){
				printf ("\n");
			}
		}
	}
	printf ("\n");
	//�����ͼƬ����
	U8 date[hight][width];											//����������洢��ͼƬ���� 
	int x=0,y=0;
	for (i=0;i<size;i++){
		for (j=0;j<size;j++){
			if (def[i][j].da==1){									//�жϿ����Դ����������Դ������� 
				for (y=i*(hight/size);y<(i+1)*(hight/size);y++){
					for (x=j*(width/size);x<(j+1)*(width/size);x++){
						date[y][x]=date_11[y][x];
					}
				}
			}
			else if (def[i][j].da==2){
				for (y=i*(hight/size);y<(i+1)*(hight/size);y++){
					for (x=j*(width/size);x<(j+1)*(width/size);x++){
						date[y][x]=date_22[y][x];
					}
				}
			}
		}
	}
	//����תһά��ȥ����������
	hight=(int)bmpi1.bHeight;
	width=(int)bmpi1.bWidth;	
	U8 finaldate[hight*width];
	k=0;
	for (i=0;i<hight;i++){
		for (j=0;j<width;j++){
			finaldate[k]=date[i][j];
			k++;
		}
	}
	//����ں�ͼ��ֿ�ͼ 
	printf("\n�����Ƿ�Ҫ����ں�ͼ��ֿ�ͼ\n������1��0 1Ϊ�����0Ϊ�����:\n");
	int s;
	scanf ("%d",&s);
	if (s){
		U8 finaldate_block[hight*width];				//�ֿ�ͼͼ������ 
		k=0;
		for (i=0;i<hight;i++){
			for (j=0;j<width;j++){
				if(i==0||j==0||i%(hight/size)==0||j%(hight/size)==0) {
					date[i][j]=255;
				}
				finaldate_block[k]=date[i][j];
				k++;
			}
		}
		FILE* fp=NULL;
		char u[30]="OUTPUT_block.bmp";
		fp=fopen (u,"wb");
		if (fp==NULL){
			printf ("����ʧ��\n");
		}
		fwrite(&bmpf1,sizeof (BMPFi),1,fp);
		fwrite(&bmpi1,sizeof (BMPIn),1,fp);
		fwrite(pallet1,sizeof(U8)*1024,1,fp);
		fwrite(finaldate_block,sizeof(U8)*hight*width,1,fp);
	}
	//����ͼƬ 
	FILE* fp=NULL;
	char name[100];
	printf ("��������ͼƬ����\n");
	scanf ("%s",name);
	fp=fopen (name,"wb");
	fwrite(&bmpf1,sizeof (BMPFi),1,fp);		//д������ 
	fwrite(&bmpi1,sizeof (BMPIn),1,fp);
	fwrite(pallet1,sizeof(U8)*1024,1,fp);
	fwrite(finaldate,sizeof(U8)*hight*width,1,fp);
	printf ("OK\n");
	return 0;
}
