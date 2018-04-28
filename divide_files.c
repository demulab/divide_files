// divide_files.c for Yolo
// Compile:  gcc -o divide_files divide_files.c
// Usage:    ./divide_files [portion]
//           portion: the portion of test data 
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#define TEST_FILENAME  "test2.list"
#define TRAIN_FILENAME "train2.list"
float g_portion = 0.3;


int compar(const struct dirent **s1, const struct dirent **s2)
{
    return strcmp( (*s1)->d_name, (*s2)->d_name);
}

int selects(struct dirent *dir)
{
    if(dir->d_name[0] == '.') {
        return (0);
    }
    if (strstr(dir->d_name, ".jpg") != NULL) {
        return (1);
    } else {
        return 0;
    }
}


int main (int argc, char *argv[])
{
    FILE *fp_test, *fp_train;

    int i, test_no=0, train_no=0;
    float j=0,skip;
    const char *dirname = ".";
    struct dirent **namelist;
    char buf[1024];


    if (argc == 1) {
        printf("Input the portion of test data:");
        scanf("%f", &g_portion);
    }
    if (argc > 2) {
        printf("Usage: divide_files [portion] \n");
        printf("        portion: the portion of test data\n");
        exit(1);
    }

    int file_no = scandir(dirname, &namelist, (int (*)(const struct dirent *)) selects, compar);

    if ((fp_test = fopen(TEST_FILENAME, "w")) == NULL) {
        err(EXIT_FAILURE, "cannot open %s", TEST_FILENAME);
    }
    if ((fp_train = fopen(TRAIN_FILENAME, "w")) == NULL) {
        err(EXIT_FAILURE, "cannot open %s", TRAIN_FILENAME);
    }

    if(file_no == -1) {
        err(EXIT_FAILURE, "%s", dirname);
    }

    getcwd(buf, sizeof(buf));
    skip = file_no /  (file_no * g_portion);

    for (i = 0; i < file_no; i++) {
        if (j >= file_no) {
            break;
        }
        if (i < (int) j) {
            train_no++;
            printf("%d:train(%d):%s/%s\n", i+1,train_no, buf,namelist[i]->d_name);
            fprintf(fp_train, "%s/%s\n", buf,namelist[i]->d_name);
        } else if (i == (int) j) {
            j += skip;
            test_no++;
            printf("%d:test(%d):%s/%s\n", i+1,test_no,buf,namelist[i]->d_name);
            fprintf(fp_test, "%s/%s\n", buf,namelist[i]->d_name);
        }
    }


    for (i=0; i< file_no;i++) free(namelist[i]);
    free(namelist);

    printf("all  =%d\n", file_no);
    printf("train=%d\n", train_no);
    printf("test =%d\n", test_no);
    printf("portion=%f\n", (float)test_no/file_no);
    exit(EXIT_SUCCESS);
}
