#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

 
#define BUF_SIZE 8192

void Append(char* outputFile, char* filePath, char* suffix) {
  int input_fd, output_fd;
  char buffer[BUF_SIZE];
  char infilePath[BUF_SIZE];
  DIR *dirp;
  struct dirent *dp;
  int ret_in, ret_out;


  output_fd = open(outputFile, O_WRONLY | O_CREAT, 0644);
  if(output_fd == -1){
     perror("open");
  } else {
    printf("open output file: %s\n", outputFile);
  }
  

  if ((dirp = opendir(filePath)) == NULL) {
        perror("couldn't open '.'");
        return;
  } else {
    printf("open dir: %s\n", filePath);
  }


  do {
    errno = 0;
    if ((dp = readdir(dirp)) != NULL) {
      

      /* check suffix */
      /* printf(" file: %s suffix: %s\n", dp->d_name, suffix); */

      if( strstr(dp->d_name, suffix) == NULL ) {
	printf("%s do NOT contain %s substring\n", dp->d_name, suffix);
	continue;
      }

      sprintf(infilePath, "%s/%s", filePath, dp->d_name);
       
      input_fd = open (infilePath, O_RDONLY);
      printf("open input file: %s\n", infilePath);
      if (input_fd == -1) {
	perror ("unable to open");
	return;
      }

      /* Copy process */
      printf("copy %s\n", infilePath);
      while((ret_in = read (input_fd, &buffer, BUF_SIZE)) > 0){
	ret_out = write (output_fd, &buffer, (ssize_t) ret_in);
	if(ret_out != ret_in){
	  perror("write");
	}
      }
      close (input_fd);
    }
  } while (dp != NULL);

  close (output_fd);

}

int main(int argc, char** argv) {
  if (argc != 4)
    {
      printf("%s OutputFile Folder suffix\n", argv[0]);
      exit(0);
    }
  char* outputFile=argv[1];
  char* filePath=argv[2];
  char* suffix=argv[3];
  Append(outputFile, filePath, suffix);
 return 0;
}
