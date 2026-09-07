# C Line Editor

## Team

- Kavya Bist R25EJ054
  Anjali Nair R25EJ008

## Project Overview

This is a lightweight, terminal-based line editor built in C. The document's lines are stored in memory using a dynamically resizing array of string pointers (`char **lines`) within a `Document` structure. This architecture was chosen to allow $O(1)$ random access for printing lines, while effectively utilizing pointer arithmetic (`memmove`) to shift memory addresses when inserting or deleting rows, avoiding the overhead of deep-copying full strings during shifts.

## Implemented Features

- **Insert a line:** Dynamically reallocates memory when capacity is reached and shifts pointers down.
- **Delete a line:** Frees the targeted string and shifts subsequent pointers up to avoid memory fragmentation.
- **Display the document:** Prints formatted line numbers.
- **Save / load a file:** Standard File I/O operations replacing the document state.

## Compilation & Execution

Ensure you have `gcc` installed on your system.

1. **Compile the source code:**
   ```bash
   gcc -Wall -Wextra editor.c -o editor
   ```
