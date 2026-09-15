void print(char text[]);

typedef struct
{
    char* message;
    int error;
} error_message;

error_message cp_it(char* options[], int opc, char* flags[], int flc, char* path);
error_message find_content(char* options[], int opc, char* flags[], int flc);
error_message find_name(char* options[], int opc, char* flags[], int flc);
char* concat(char* first, char* second);