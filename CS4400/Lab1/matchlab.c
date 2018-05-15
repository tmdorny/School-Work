/*  CS 4400 Lab 1 Tim Dorny u0829896 */
#include "string.h"
// Functions
int checkPatternA(char* arg, int tFlag);
int checkPatternB(char* arg, int tFlag);
int checkPatternC(char* arg, int tFlag);


int main (int argc, char **argv){

// Check Flags
int mode = 0;
int tMode =0; // 0 = false, 1 = true
int defaultMode = 0;
// Number of flags passed
int flags = 0;
// Check first argument for flags
if (strcmp(argv[1], "-a") == 0){
mode = 0;
flags = 1;
}
else if (strcmp(argv[1], "-b") == 0){
mode = 1;
flags = 1;
}
else if (strcmp(argv[1], "-c") == 0){
mode = 2;
flags = 1;
}
else if(strcmp(argv[1], "-t") == 0){
tMode = 1;
flags = 1;
}
else{
defaultMode = 1;
}
// Check second argument (if applicable)
if (defaultMode == 0){
  if (strcmp(argv[2], "-a") == 0){
  mode = 0;
  flags = 2;
  }
  else if (strcmp(argv[2], "-b") == 0){
  mode = 1;
  flags = 2;
  }
  else if (strcmp(argv[2], "-c") == 0){
  mode = 2;
  flags = 2;
  }
  else if(strcmp(argv[2], "-t") == 0){
  tMode = 1;
  flags = 2;
  }
}
int i = flags + 1;
for (i; i < argc; i++){
    // -a or default
    if (mode == 0){
        int pass = checkPatternA(argv[i], tMode);
        if (pass == 1){
            printf("yes\n");
        }
        else if (tMode == 0){
            printf("no\n");
        }
    }
    // -b
    else if (mode ==1){
        int pass = checkPatternB(argv[i], tMode);
        if (pass == 1){
            printf("yes\n");
        }
        else if (tMode == 0){
            printf("no\n");
        }
    }
    // -c
    else if (mode ==2){
        int pass = checkPatternC(argv[i], tMode);
        if (pass == 1){
            printf("yes\n");
        }
        else if (tMode == 0){
            printf("no\n");
        }
    }
}
return 0;
}

int checkPatternA(char* arg, int tFlag){
    char *word = arg;
    int length = strlen(arg);
    // Ints to help handle checking if the argument matches the sequence
    // the *Valid ints become 1 once the corresponding part of the sequence is
    // properly met
    int hCount = 0;
    int sCount = 0;
    int dCount = 0;
    while (*word != '\0'){
        if (*word == 'h'){
            hCount++;
        }
        else{
            break;
        }
        *word++;
    }
    // If not enough h's were present, return false (0).
    if (hCount < 3){
        return 0;
    }
    // Check for s's
    while (*word != '\0'){
        if (*word == 's'){
            sCount++;
        }
        else{
            break;
        }
        *word++;
    }
    // If invalid # of s's, return 0
    if (sCount < 4){
        if (sCount > 7){
            return 0;
        }
        return 0;
    }
    // Check for decimal digits
    while (*word != '\0'){
        if (*word > 47 && *word < 58){
            dCount++;
        }
        else{
            break;
        }
        *word++;
    }
    // Final validity checks.
    if (dCount > 0 && dCount < 4){
        // Modified string
        if (tFlag){
            int j = 0;
            char printer[length + 1];
            for (j; j < length; j++){
                printer[j] = 'h';
            }
            printer[length] = '\0';
            printf("%s\n", printer);
            return 0;
        }
        else{
            return 1;
        }
    }
    return 0;
}
 int checkPatternB(char* arg, int tFlag){
     char* word = arg;
     int length = strlen(arg);
     // To build string required for t flag.
     char *strBuild = arg;
     // Track # of chars
     int dCount = 0;
     int upperCount = 0;
     int vCount = 0;
     int decCount = 0;

     while(*word != '\0'){
         if (*word == 'd'){
             dCount++;
         }
         else{
             break;
         }
         *word++;
     }
     // Determine if there was an odd # of d's
     if (dCount & 1 != 1){
         return 0;
     }
    int index = 0;
    char oddLetters[length];
    while(*word != '\0'){
        if (*word > 64 && *word < 91){
            upperCount++;
        }
        else{
            break;
        }
        if (upperCount & 1 == 1){
            oddLetters[index] = *word;
            index++;
        }
        *word++;
    }
    if (upperCount & 1 != 1){
        return 0;
    }
    while(*word != '\0'){
        if (*word == 'v'){
            vCount++;
        }
        else{
            break;
        }
        *word++;
    }
    // Determine if there was an odd # of v's
    if (vCount & 1 != 1){
        return 0;
    }
    int newIndex = 0;
    while(*word != '\0'){
        if(newIndex == index){
            break;
        }
        else if(*word != oddLetters[newIndex]){
            return 0;
        }
        newIndex++;
        *word++;
    }
    // Check for decimal digits
    while (*word != '\0'){
        if (*word > 47 && *word < 58){
            decCount++;
        }
        else{
            break;
        }
        *word++;
    }
    // Final validity checks.
    if (decCount > 0 && decCount < 4){
        if (tFlag){
            // Print t flag string
            index = 0;
            char printer[length + 15];
            while (*strBuild != '\0'){
                if (*strBuild == 'A'){
                    printer[index] = 'B';
                    index++;
                }
                printer[index] = *strBuild;
                index++;
                *strBuild++;
            }
            printer[index] = '\0';
            printf("%s\n", printer);
            return 0;
        }
        else{
            return 1;
        }
    }
    return 0;

}
int checkPatternC(char* arg, int tFlag){
    char* word = arg;
    int length = strlen(arg);
    // To build string required for t flag.
    char *strBuild = arg;
    // Track # of chars
    int dCount = 0;
    int sCount = 0;
    int upperCount = 0;
    int decCount = 0;

    while(*word != '\0'){
        if (*word == 'd'){
            dCount++;
        }
        else{
            break;
        }
        *word++;
    }
    // Determine if there was an odd # of d's
    if (dCount & 1 != 1){
        return 0;
    }
    char oddDigits[length];
    int index = 0;
    // Check for decimal digits
    while (*word != '\0'){
        if (*word > 47 && *word < 58){
            decCount++;
        }
        else{
            break;
        }
        if (decCount & 1 == 1){
            oddDigits[index] = *word;
            index++;
        }
        *word++;
    }
    if (decCount < 1 || decCount > 3){
        return 0;
    }
    // Check for s's
    while (*word != '\0'){
        if (*word == 's'){
            sCount++;
        }
        else{
            break;
        }
        *word++;
    }
    if (sCount < 4){
        return 0;
    }
    // odd in X
    int newIndex = 0;
    while(*word != '\0'){
        if(newIndex == index){
            break;
        }
        else if(*word != oddDigits[newIndex]){
            return 0;
        }
        newIndex++;
        *word++;
    }
    while(*word != '\0'){
        if (*word > 64 && *word < 91){
            upperCount++;
        }
        else{
            break;
        }
    }
    if (upperCount & 1 != 1){
        return 0;
    }
    if (tFlag == 1){
        // Print t flag string
        index = 0;
        char printer[length + 15];
        while (*strBuild != '\0'){
            if (*strBuild == 'F' || *strBuild == 'D'){
                *strBuild++;
                continue;
            }
            printer[index] = *strBuild;
            index++;
            *strBuild++;
        }
        printer[index] = '\0';
        printf("%s\n", printer);
        return 0;
    }
    else {
        return 1;
    }
    return 0;
}
