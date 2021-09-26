#define VIDEO_MEMORY 0xb8000;

void print_string(char *string) {
    char *current_pos = (char*) VIDEO_MEMORY + 1000;
    int i = 0;
    while (i < 11) {
        *current_pos = string[i];
        current_pos = current_pos + 2;
        i++;
    }
    return;
}

void main() {
    init_idt();
    print_string("Hello world");
}