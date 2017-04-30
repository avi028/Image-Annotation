#include <stdio.h>
#include <iostream>
#include <queue>
#include <map>
#include <utility>
#include <climits>
#include <fstream>
#include <stack>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define ll long long int 
#define er(X) cout<<"error"<<X
#define mp(X,Y) make_pair(X,Y)
#define PI 3.14159265

using namespace std;
// prints vector of integers
void print_int(std::vector< std::vector<int> > v)
{
    int i,j;
    for (i = 0; i < v.size(); ++i)
    {
        for (j = 0; j < v[i].size(); ++j)
        {
            cout<<v[i][j] <<" ";            
        }
        cout<<endl;
    }
}

// print float 
void print_float(std::vector< std::vector<float> > v)
{
    int i,j;
    for (i = 0; i < v.size(); ++i)
    {
        for (j = 0; j < v[i].size(); ++j)
        {
            cout<<v[i][j] <<" ";            
        }
        cout<<endl;
    }
}
//prints unsigned integer
void print_unint16_t (std::vector< std::vector<uint16_t> > v)
{
    int i,j;
    for (i = 0; i < v.size(); ++i)
    {
        for (j = 0; j < v[i].size(); ++j)
        {
            cout<<v[i][j] <<" ";            
        }
        cout<<endl;
    }
}

//read hvec32 files
int hvec32_read(const char *file_in, uint32_t **data, int *n)
{
    // initialization
    int x,y;
    std::vector< std::vector<uint16_t> > data_set;
    std::vector<uint16_t> temp;
    int itr=0;
    uint16_t ** data;   
    uint16_t * tmp_float;
    size_t s=sizeof(uint16_t), i=0, nn;
    int j;
    uint16_t N=0;
    size_t s=sizeof(uint32_t),i=0,nn;
    uint32_t N=0;

    //rb read binary
    FILE * fid = fopen(file_in,"rb");
 //   s -> size of the line to be readf
  // & N no of llines to be read &N is the location of the vartiabkle N in memory 
  //   fid -> file object to read 
    i=fread(&N,s,1,fid);// to find no of lines in the file 
    // int and size_t 
    *n=(int) N;
    nn=(size_t) N;
    // calloc is used to assign memory calloc(no of memory , s) 
    *data = (uint32_t *) calloc(nn,s);
    i=fread(*data,s,nn,fid);
    i=fclose(fid);
}

std::vector<std::vector<uint16_t> > hvec_read(char file[])
{
    int x,y;
    std::vector< std::vector<uint16_t> > data_set;
    std::vector<uint16_t> temp;
    int itr=0;
    uint16_t ** data;   
    uint16_t * tmp_float;

    size_t s=sizeof(uint16_t), i=0, nn;
    int j;
    uint16_t N=0;
    FILE * fid = fopen(file,"rb");
    if (fid==NULL)
    return data_set;
    i=fread(&N,s,1,fid);
    if (i!=1)
    return data_set;
    nn = (size_t) N;
    tmp_float = (uint16_t *) calloc(nn,s);
    data = &tmp_float;

    if ((*data)==NULL) 
    {
        fprintf(stderr,"Can't allocate memory while reading file %s\n",file);
        return data_set;
    }

    i=fread(*data,s,nn,fid);

    if (i != nn)
        return data_set;
   
    j=fclose(fid);
   
    for (y = 0; y < N; ++y)
    {   
        temp.push_back(data[0][y]);
        data_set.push_back(temp);
        temp.clear();
    }

    if (j!=0)
        return data_set;
    return data_set;

}

std::vector< std::vector<float> > read_fvec(char file[])
{
    int x,y;
    std::vector< std::vector<float> > data_set;
    std::vector<float> temp;
    int itr=0;
	int *n;
	int *m;
	float ** data;	
    size_t s1=sizeof(int),s2=sizeof(float),i=0,N=0,M=0,k=0;
    int tmp=0;  
    off_t L=0,j;
    FILE * fid = fopen(file,"rb");
    if (fid==NULL)
	return data_set;
    i=fread(&tmp,s1,1,fid);
    if (i!=1)
	return data_set;
    m=&tmp; 
    M=tmp;
    j=fseeko(fid,0,SEEK_END); 
    L=ftello(fid); 
    N=(size_t) L/(s1+(*m)*s2); 
    tmp=(int) N;
    n=&tmp;
    j=fseeko(fid,0,SEEK_SET);
    float * tmp_float;
    tmp_float = (float *) calloc(N*M,s2);
    data = &tmp_float;
    for (k=0;k<N;k++) 
    {
        // i=fread(&tmp,s1,1,fid);
        // if (i!=1 || tmp!=((int)M))
        // {
        //     fprintf(stderr,"Incompatible vector temp\n");
        // }
		i=fread((tmp_float)+(k*(M)),s2,M,fid);
    }

    tmp=fclose(fid);

    for (y = 0; y < M*N; ++y)
    {	
    	if(itr==M)
    	{
    		data_set.push_back(temp);
    		temp.erase(temp.begin(),temp.end());
    		itr=0;
    	}
     	 temp.push_back(data[0][y]);    		
     	 itr++;
 	}
 	data_set.push_back(temp);
 	return data_set;
}

std::vector< std::vector<uint16_t> > read_hvec(char file[])
{
    int x,y;
    std::vector< std::vector<uint16_t> > data_set;
    std::vector<uint16_t> temp;
    int itr=0;
	uint16_t ** data;	
    uint16_t * tmp_float;
    size_t s1=sizeof(uint16_t),s2=sizeof(unsigned int),i=0,nn,mm;
    int N=0,k=0,tmp=0;
    uint16_t M=0;
    off_t L=0,j;
    FILE * fid = fopen(file,"rb");
    
    if (fid==NULL)
        return data_set;
    
    i=fread(&tmp,s1,1,fid);
    if (i!=1)
        return data_set;
    
    mm=(size_t) tmp;
    M = tmp;
    j=fseeko(fid,0,SEEK_END); /* go to the end of the file */
    L=ftello(fid); /* get file length */
    N=(int) L/(s1+(M)*s2); /* number of vectors in file */
    nn=(size_t) N;
    j=fseeko(fid,0,SEEK_SET); /* cack to begin of file */

    tmp_float = (uint16_t *) calloc(nn*mm,s2);
    data = &tmp_float;
    
    if ((*data)==NULL) 
    {
        fprintf(stderr,"Can't allocate memory while reading file %s\n",file);
        return data_set;
    }

    for (k=0;k<N;k++) 
    {
       // i=fread(&tmp,s1,1,fid);
       // if (i!=1 || tmp!=(int)M)
       // {
       //     fprintf(stderr,"Incompatible vector temp =%d and N =%u M =%u\n",tmp,nn,mm);
       //  }
        i=fread((*data)+(k*(M)),s2,mm,fid);
    
        if (i!=mm)
            fprintf(stderr,"Incompatible vector\n");
    }

    k=fclose(fid);
    if (k!=0)
    return data_set;

    tmp=fclose(fid);
    for (y = 0; y < M*N; ++y)
    {	
    	if(itr==M)
    	{
    		data_set.push_back(temp);
    		temp.clear();
    		itr=0;
    	}
     	 temp.push_back(data[0][y]);    		
     	 itr++;
 	}
 	data_set.push_back(temp);
 	return data_set;
}

void size_vector_float(std::vector<std::vector<float> > v)
{
    cout<<"vector_size"<<v.size()<<endl;
    cout<<"vector[0]_size"<<v[0].size()<<endl;
}

void size_vector_uint16_t(std::vector<std::vector<uint16_t> > v)
{
    cout<<"vector_size"<<v.size()<<endl;
    cout<<"vector[0]_size"<<v[0].size()<<endl;
}


void write_float (std::vector<std::vector<float> > v , char c [])
{

    ofstream of ;
    of.open(c);
    int i,j;
    for (i = 0; i < v.size(); ++i)
    {
        for (j = 0; j < v[i].size(); ++j)
        {
            if(v[i][j]>0.000001)
               of<<v[i][j] <<" ";            
        }
        of<<endl;
    }
    of.close();
}
    
int main(int argc, char const *argv[])
{
	int i,j=0;
	std::vector<std::vector<uint16_t> > test_annotation_data_set;
	std::vector<std::vector<uint16_t> > training_annotation_data_set;
	char file_annotation_test[]="corel5k_test_annot.hvecs";
	char file_annotation_training[]="corel5k_train_annot.hvecs";

	std::vector<std::vector<float> > test_data_set;
	std::vector<std::vector<float> > training_data_set;
	char file_test[]="corel5k_test_Gist.fvec";
	char file_training[]="corel5k_train_Gist.fvec";
    char file[]="corel5k_train_HarrisSift.hvecs";
	
    test_annotation_data_set = read_hvec(file_annotation_test);
	training_annotation_data_set = read_hvec(file_annotation_training);
	test_data_set = read_fvec(file_test);
	training_data_set = read_fvec(file_training); 
    
    char  c []= "training_data.txt";
    char c2 []= "test_data.txt";

    write_float(training_data_set,c);
    write_float(test_data_set,c2);
}
