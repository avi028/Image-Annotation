#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int hvec_read(const char * file_in, uint16_t ** data, int * n)
{
    size_t s=sizeof(uint16_t), i=0, nn;
    int j;
    uint16_t N=0;
    FILE * fid = fopen(file_in,"rb");
    if (fid==NULL)
	return EXIT_FAILURE;
    i=fread(&N,s,1,fid);
    if (i!=1)
	return EXIT_FAILURE;
    *n = (int) N;
    nn = (size_t) *n;
    *data = (uint16_t *) calloc(nn,s);
    if ((*data)==NULL) {
	fprintf(stderr,"Can't allocate memory while reading file %s\n",file_in);
	return EXIT_FAILURE;
    }
    i=fread(*data,s,nn,fid);
    if (i != nn)
	return EXIT_FAILURE;
    j=fclose(fid);
    if (j!=0)
	return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int hvecs_read(const char *file_in, uint16_t **data, int *n, int *m)
{
    size_t s1=sizeof(uint16_t),s2=sizeof(uint16_t),i=0,nn,mm;
    int N=0,k=0,tmp=0;
    uint16_t M=0;
    off_t L=0,j;
    FILE * fid = fopen(file_in,"rb");
    if (fid==NULL)
	return EXIT_FAILURE;
    i=fread(&M,s1,1,fid);
    if (i!=1)
	return EXIT_FAILURE;
    *m=(int) M; /* fvec vector length */
    mm=(size_t) M;
    j=fseeko(fid,0,SEEK_END); /* go to the end of the file */
    L=ftello(fid); /* get file length */
    N=(int) L/(s1+(*m)*s2); /* number of vectors in file */
    *n=N;
    nn=(size_t) N;
    printf("The vector length is %d\nThere are %d vectors\n",M,N); 
    j=fseeko(fid,0,SEEK_SET); /* back to begin of file */
    *data = (uint16_t *) calloc(nn*mm,s2);
    if ((*data)==NULL) {
	fprintf(stderr,"Can't allocate memory while reading file %s\n",file_in);
	return EXIT_FAILURE;
    }
    for (k=0;k<N;k++) {
	i=fread(&tmp,s1,1,fid);
	if (i!=1 || tmp!=(*m))
	    fprintf(stderr,"Incompatible vector\n");
	i=fread((*data)+(k*(*m)),s2,mm,fid);
	if (i!=mm)
	    fprintf(stderr,"Incompatible vector\n");
    }
    k=fclose(fid);
    if (k!=0)
	return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int hvec_write(const char *file_in, const uint16_t *data, const unsigned int n)
{
    size_t s=sizeof(uint16_t),i=0;
    FILE * fid = fopen(file_in,"wb");
    if (fid==NULL)
	return EXIT_FAILURE;
    i=fwrite(&n,s,1,fid);
    if (i!=1)
	return EXIT_FAILURE;
    i=fwrite(data,s,n,fid);
    if (i!=n)
	return EXIT_FAILURE;
    i=fclose(fid);
    if (i!=0)
	return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int hvecs_write(const char *file_in, const uint16_t *data, const unsigned int n, const unsigned int m)
{
    size_t s1=sizeof(uint16_t),s2=sizeof(uint16_t),k=0;
    unsigned int i;
    FILE * fid = fopen(file_in,"wb");
    if (fid==NULL)
	return EXIT_FAILURE;
    for (i=0;i<n;i++) {
	k=fwrite(&m,s1,1,fid);
	if (k!=1)
	    return EXIT_FAILURE;
	k=fwrite(data+i*m,s2,(size_t) m,fid);
	if (k!=(size_t) m)
	    return EXIT_FAILURE;
    }
    k=fclose(fid);
    if (k!=0)
	return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int hvec32_read(const char *file_in, uint32_t **data, int *n)
{
    size_t s=sizeof(uint32_t),i=0,nn;
    uint32_t N=0;
    FILE * fid = fopen(file_in,"rb");
    if (fid==NULL)
	return EXIT_FAILURE;
    i=fread(&N,s,1,fid);
    if (i!=1)
	return EXIT_FAILURE;
    *n=(int) N;
    nn=(size_t) N;
    *data = (uint32_t *) calloc(nn,s);
    if ((*data)==NULL) {
	fprintf(stderr,"Can't allocate memory while reading file %s\n",file_in);
	return EXIT_FAILURE;
    }
    i=fread(*data,s,nn,fid);
    if (i!=nn)
	return EXIT_FAILURE;
    i=fclose(fid);
    if (i!=0)
	return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int hvecs32_read(const char *file_in, uint32_t **data, int *n, int *m)
{
    int s1=sizeof(uint32_t),s2=sizeof(uint32_t),i=0,mm,N=0;
    int k=0,tmp=0;
    uint32_t M=0;
    off_t L=0,j;
    FILE * fid = fopen(file_in,"rb");
    if (fid==NULL)
	return EXIT_FAILURE;
    i=fread(&M,s1,1,fid);
    if (i!=1)
	return EXIT_FAILURE;
    *m=(int) M; /* fvec vector length */
    mm=(size_t) M;
    j=fseeko(fid,0,SEEK_END); /* go to the end of the file */
    L=ftello(fid); /* get file length */
    N=(size_t) L/(s1+(*m)*s2); /* number of vectors in file */
    *n=(int) N;
/*    printf("The vector length is %d\nThere are %d vectors\n",M,N); */
    i=fseek(fid,0,SEEK_SET); /* back to begin of file */
    *data = (uint32_t *) calloc(N*mm,s2);
    if ((*data)==NULL) {
	fprintf(stderr,"Can't allocate memory while reading file %s\n",file_in);
	return EXIT_FAILURE;
    }
    for (k=0;k<N;k++) {
	i=fread(&tmp,s1,1,fid);
	if (i!=1 || tmp!=(*m))
	    fprintf(stderr,"Incompatible vector\n");
	i=fread((*data)+(k*(*m)),s2,mm,fid);
	if (i!=m[0])
	    fprintf(stderr,"Incompatible vector\n");
    }
    k=fclose(fid);
    if (k!=0)
	return EXIT_FAILURE;
    return EXIT_SUCCESS;
}


int hvec32_write(const char *file_in, const uint32_t *data, const unsigned int n)
{
    size_t s=sizeof(uint32_t),i=0;
    FILE * fid = fopen(file_in,"wb");
    if (fid==NULL)
	return EXIT_FAILURE;
    i=fwrite(&n,s,1,fid);
    if (i!=1)
	return EXIT_FAILURE;
    i=fwrite(data,s,n,fid);
    if (i!=n)
	return EXIT_FAILURE;
    i=fclose(fid);
    if (i!=0)
	return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int hvecs32_write(const char *file_in, const uint32_t *data, const unsigned int n, const unsigned int m)
{
    size_t s1=sizeof(uint32_t),s2=sizeof(uint32_t),i=0,k=0;
    FILE * fid = fopen(file_in,"wb");
    if (fid==NULL)
	return EXIT_FAILURE;
    for (i=0;i<n;i++) {
	k=fwrite(&m,s1,1,fid);
	if (k!=1)
	    return EXIT_FAILURE;
	k=fwrite(data+i*m,s2,m,fid);
	if (k!=m)
	    return EXIT_FAILURE;
    }
    k=fclose(fid);
    if (k!=0)
	return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int fvec_read(const char *file_in, float **data, int *n, int *m)
{
    size_t s1=sizeof(int),s2=sizeof(float),i=0,N=0,M=0,k=0;
    int tmp=0;
    off_t L=0,j;
    FILE * fid = fopen(file_in,"rb");
    if (fid==NULL)
	return EXIT_FAILURE;
    i=fread(&tmp,s1,1,fid);
    if (i!=1)
	return EXIT_FAILURE;
    m=&tmp; 
    M=tmp;
    j=fseeko(fid,0,SEEK_END); 
    L=ftello(fid); 
    N=(size_t) L/(s1+(*m)*s2); 
    tmp=(int) N;
    n=&tmp;
    printf("The vector length is %d\nThere are %d vectors\n",M,N); 
    j=fseeko(fid,0,SEEK_SET); /* back to begin of file */
    float * tmp_float;
    tmp_float = (float *) calloc(N*M,s2);
    data = &tmp_float;
    if ((*data)==NULL) {
	fprintf(stderr,"Can't allocate memory while reading file %s\n",file_in);
	return EXIT_FAILURE;
    }
    for (k=0;k<N;k++) {
	i=fread(&tmp,s1,1,fid);
	if (i!=1 || tmp != (*m))
	    fprintf(stderr,"Incompatible vector\n");
	i=fread((*data)+(k*(*m)),s2,M,fid);
	if (i!=M)
	    fprintf(stderr,"Incompatible vector\n");
    }
    tmp=fclose(fid);
    if (tmp!=0)
	return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int fvec_write(const char *file_in, const float *data, const unsigned int n, const unsigned int m)
{
    size_t s1=sizeof(int),s2=sizeof(float),i=0,k=0;
    int j;
    FILE * fid = fopen(file_in,"wb");
    if (fid==NULL)
	return EXIT_FAILURE;
    for (i=0;i<n;i++) {
	k=fwrite(&m,s1,1,fid);
	if (k!=1)
	    return EXIT_FAILURE;
	k=fwrite(data+i*m,s2,m,fid);
	if (k!=m)
	    return EXIT_FAILURE;
    }
    j=fclose(fid);
    if (j!=0)
	return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

