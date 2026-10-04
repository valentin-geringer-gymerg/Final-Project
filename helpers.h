typedef unsigned char BYTE;

typedef struct
{
    char* message;
    int error;
} error_message;

// Commands
error_message cp_it(char* options[], int opc, char* flags[], int flc, char* path);
error_message find_content(char* options[], int opc, char* flags[], int flc);
error_message find_name(char* options[], int opc, char* flags[], int flc);

// Functions for code
char* concat(char* first, char* second);
int get_digits(int num);
char* itoa(int num);
void print(char text[]);
int tenToThe(int n);
char todigit(int digit);