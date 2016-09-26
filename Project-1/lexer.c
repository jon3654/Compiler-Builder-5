#include<stdio.h>

int main(int argc,char* argv[]){
    FILE *ifp = fopen(argv[1],"r");
    char temp[13];
  
  while(!feof(ifp)){
    temp = fscanf(ifp);
    
    StringReader(temp);
  }
  
    return 0;
}
