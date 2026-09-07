#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 256
#define INITIAL_CAPACITY 10

/*
 * Utilizing a dynamic array of string pointers within a struct.
 * This approach offers O(1) random access for printing and saves memory
 * compared to a static 2D array, while requiring explicit pointer
 * shifting (memmove) during insertions and deletions.
 */
typedef struct
{
    char **lines;
    int count;
    int capacity;
} Document;

void init_document(Document *doc)
{
    doc->capacity = INITIAL_CAPACITY;
    doc->count = 0;
    doc->lines = malloc(doc->capacity * sizeof(char *));
    if (!doc->lines)
    {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
}

void free_document(Document *doc)
{
    for (int i = 0; i < doc->count; i++)
    {
        free(doc->lines[i]);
    }
    free(doc->lines);
}

void insert_line(Document *doc, int line_num, const char *text)
{
    if (line_num < 1 || line_num > doc->count + 1)
    {
        printf("Error: Invalid line number. Valid range: 1 to %d\n", doc->count + 1);
        return;
    }

    if (doc->count == doc->capacity)
    {
        doc->capacity *= 2;
        doc->lines = realloc(doc->lines, doc->capacity * sizeof(char *));
        if (!doc->lines)
        {
            perror("Failed to reallocate memory");
            exit(EXIT_FAILURE);
        }
    }

    int index = line_num - 1;

    // Shift existing lines down using pointer arithmetic
    if (index < doc->count)
    {
        memmove(&doc->lines[index + 1], &doc->lines[index], (doc->count - index) * sizeof(char *));
    }

    doc->lines[index] = strdup(text);
    // Remove newline character if present
    doc->lines[index][strcspn(doc->lines[index], "\n")] = 0;
    doc->count++;
    printf("Line %d inserted.\n", line_num);
}

void delete_line(Document *doc, int line_num)
{
    if (line_num < 1 || line_num > doc->count)
    {
        printf("Error: Invalid line number.\n");
        return;
    }

    int index = line_num - 1;
    free(doc->lines[index]);

    // Shift lines up
    if (index < doc->count - 1)
    {
        memmove(&doc->lines[index], &doc->lines[index + 1], (doc->count - index - 1) * sizeof(char *));
    }

    doc->count--;
    printf("Line %d deleted.\n", line_num);
}

void display_document(const Document *doc)
{
    if (doc->count == 0)
    {
        printf("Document is empty.\n");
        return;
    }
    for (int i = 0; i < doc->count; i++)
    {
        printf("%3d | %s\n", i + 1, doc->lines[i]);
    }
}

void save_document(const Document *doc, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("Error opening file for writing");
        return;
    }
    for (int i = 0; i < doc->count; i++)
    {
        fprintf(file, "%s\n", doc->lines[i]);
    }
    fclose(file);
    printf("Document saved to %s.\n", filename);
}

void load_document(Document *doc, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file for reading");
        return;
    }

    // Clear current document
    for (int i = 0; i < doc->count; i++)
        free(doc->lines[i]);
    doc->count = 0;

    char buffer[MAX_LINE_LEN];
    while (fgets(buffer, MAX_LINE_LEN, file))
    {
        insert_line(doc, doc->count + 1, buffer);
    }
    fclose(file);
    printf("Document loaded from %s.\n", filename);
}

int main()
{
    Document doc;
    init_document(&doc);
    char input[MAX_LINE_LEN + 20];
    char command;
    int line_num;
    char arg[MAX_LINE_LEN];

    printf("Line Editor Started. Type 'h' for help, 'q' to quit.\n");

    while (1)
    {
        printf("> ");
        if (!fgets(input, sizeof(input), stdin))
            break;

        command = input[0];

        switch (command)
        {
        case 'i':
            if (sscanf(input, "i %d %[^\n]", &line_num, arg) == 2)
            {
                insert_line(&doc, line_num, arg);
            }
            else
            {
                printf("Usage: i <line_number> <text>\n");
            }
            break;
        case 'd':
            if (sscanf(input, "d %d", &line_num) == 1)
            {
                delete_line(&doc, line_num);
            }
            else
            {
                printf("Usage: d <line_number>\n");
            }
            break;
        case 'p':
            display_document(&doc);
            break;
        case 's':
            if (sscanf(input, "s %s", arg) == 1)
            {
                save_document(&doc, arg);
            }
            else
            {
                printf("Usage: s <filename>\n");
            }
            break;
        case 'l':
            if (sscanf(input, "l %s", arg) == 1)
            {
                load_document(&doc, arg);
            }
            else
            {
                printf("Usage: l <filename>\n");
            }
            break;
        case 'h':
            printf("Commands:\n");
            printf("  i <num> <text>  - Insert <text> at line <num>\n");
            printf("  d <num>         - Delete line <num>\n");
            printf("  p               - Print entire document\n");
            printf("  s <filename>    - Save to file\n");
            printf("  l <filename>    - Load from file\n");
            printf("  q               - Quit\n");
            break;
        case 'q':
            free_document(&doc);
            printf("Exiting...\n");
            return 0;
        default:
            if (command != '\n')
                printf("Unknown command. Type 'h' for help.\n");
        }
    }
    free_document(&doc);
    return 0;
}