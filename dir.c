#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

off_t get_dir_size(char * path){
  DIR * dir = opendir(path);
  off_t retVal = 0;
  struct dirent *info;
  info = readdir(dir);
  while (info) {
    if (info->d_type == DT_REG) {
      char filepath[256];
      strcpy(filepath, path);
      strcpy(filepath, "/");
      strcpy(filepath, info->d_name);
      struct stat sb;
      stat(filepath, &sb);
      retVal += sb.st_size;
    }
    info = readdir(dir);
  }
  closedir(dir);
  return retVal;
}
/*
void analyze (char * path) {
  DIR * dir = opendir(path);
  struct dirent *info;
  struct dirent *directories[256];
  struct dirent *files[256];
  int dirctr = 0;
  int filectr = 0;
  
  info = readdir(dir);
  
  while (info) {
    if (info->d_type == DT_DIR) {
      directories[dirctr] = info;
      dirctr += 1;
    }
    else {
      files[filectr] = info;
      filectr += 1;
    }
    info = readdir(dir);
  }

  int i;
  printf("Statistics for directory: %s", path);
  printf("Total Diectory Size: %lu", get_dir_size(path));
  printf("Directories:");
  for (i = 0; i < dirctr; i++) {
    printf("%s\n", directories[dirctr]->d_name);
  }
  printf("Regular files:");
  for (i = 0; i < filectr; i++) {
    printf("%s\n", files[filectr]->d_name);
  }
  
  closedir(dir);

}
*/
int main() {

  char *path = ".";
  DIR * d;
  
  int filectr = 0;
  struct dirent *files[256];
  int dirctr = 0;
  struct dirent *directories[256];
  struct dirent *info;

  d = opendir(path);
  
  info = readdir(d);
  
  while (info) {
    if (info->d_type == DT_DIR) {
      directories[dirctr] = info;
      dirctr++;
    }
    else {
      files[filectr] = info;
      filectr++;
    }
    info = readdir(d);
  }

  int i;
  printf("Statistics for directory: %s\n", path);
  printf("Total Diectory Size: %lu\n", get_dir_size(path));
  printf("Directories:\n");
  for (i = 0; i < dirctr; i++) {
    printf("\t%s\n", directories[i]->d_name);
  }
  printf("Regular files:\n");
  for (i = 0; i < filectr; i++) {
    printf("\t%s\n", files[i]->d_name);
  }
  
  closedir(d);
}
