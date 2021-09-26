#define VIDEO_MEMORY 0xb8000;

void print_string(char *string) {
    char *current_pos = (char*) VIDEO_MEMORY;
    int i = 0;
    while (i < 20000) {
        *current_pos = string[i];
        current_pos = current_pos + 2;
        i++;
    }
    return;
}

void main() {
    init_idt();
    print_string("Hello world ODAOJ OASJFDOISJD FOIASJDOI JAOISD JOAIFDJ GOIADJFGIOJSDOIFG JDSGJIODSGJIJ");
}