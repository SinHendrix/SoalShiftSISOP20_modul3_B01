#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<dirent.h>
#include<stdlib.h>

// int move_file()
//  {
//  FILE *f1,*f2;
//  char ch,s[10],fn1[20];
//  int a;
//  printf("\nAre u see the privious files(1/0)?");
//  scanf("%d",&a);
//  if(a==1)
//  print_file();
//  printf("Enter the source file name:");
//  scanf("%s",&fn1);
//  printf("Enter the Destination file name:");
//  scanf("%s",&fn2);
//
// f1=fopen(fn1,"r");
//  if(f1==NULL)
//   printf("Can't open the file");
//  else {
//   f2=fopen(fn2,"w");
//   while((ch=getc(f1))!=EOF)
//    putc(ch,f2);
//   printf("One File moved");
//   fclose(f2);
//   remove(fn1);
// 	  }
//   fclose(f1);
//   return 0;
//  }


int main (int argc, char **argv){// .3/ == 1    ./3 -f argv[1] == -f
  char* point;
  // char* fullname;
  int status;


  if (argc > 2){
    // printf("%s\n", argv[1]);
    if (strcmp(argv[1], "-f") == 0){
      for (int i = 2; i < argc; i++){
        char ext[100] = {0}, fullname[100] = {0};
        char dir[1000] = {0}, filename[1000] = {0};
        if((point = strrchr(argv[i],'.')) != NULL ) {
          // printf("%s\n", point+1);
          strcpy(ext, point+1);

          if((point = strrchr(argv[i],'/')) != NULL ){
              // filename = strrchr(argv[i],'/');
              strcpy(filename, point);
          }
          printf("ini filename : %s\n", filename);
          sprintf(dir, "/home/sin/modul3/%s", ext);
          // printf("filename : %s\ndir : %s\n",filename, dir);
          // printf("%s\n", ext);
          // if(strcmp(point,".csv") == 0) {
          //
          // }
          chdir(dir);
          mkdir(ext, 0777);
          size_t len = 0 ;
          const char a[1000];
          const char b[1000];
          strcpy(a, filename);
          strcpy(b, dir);
          sprintf(b, "%s%s", b, filename);
          printf("%s\n%s\n%s\n", argv[i], a, b);
          FILE *f1,*f2;
          char ch,s[10],fn1[1000],fn2[1000];
          // int a;
          // printf("\nAre u see the privious files(1/0)?");
          // scanf("%d",&a);
          // if(a==1)
          // print_file();
          // printf("Enter the source file name:");
          // scanf("%s",&fn1);
          strcpy(fn1, argv[i]);
          // printf("Enter the Destination file name:");
          // scanf("%s",&fn2);
          strcpy(fn2, b);

          f1=fopen(fn1,"r");
          if(f1==NULL){
            printf("Can't open the file");
          }

          else {
           f2=fopen(fn2,"w");
           while((ch=getc(f1))!=EOF){
             putc(ch,f2);
           }
           printf("One File moved");
           fclose(f2);
           remove(fn1);
         	}
           fclose(f1);

        }
      }
    }
  }
  else {
    printf("invalid input\n");
  }
}
// .txt
// TXT
// .jpg
// JPG
// JPEG
// ZIP
// PNG
// png
// zip
// gz
// bin
// hex
// js
// JS
// c
// GIF
// sh
// pdf
