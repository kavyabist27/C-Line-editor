# Line Editor - Help Guide

This editor operates entirely via terminal commands. Commands are single letters, followed by a space and the necessary arguments.

## Supported Commands

- **Insert a Line (`i`)**
  - **Syntax:** `i <line_number> <text>`
  - **Description:** Inserts a new line of text at the specified line number. All subsequent lines are shifted down.
  - **Example:** `i 1 Hello World` (Inserts "Hello World" at line 1).

- **Delete a Line (`d`)**
  - **Syntax:** `d <line_number>`
  - **Description:** Deletes the text at the specified line number. All subsequent lines are shifted up to fill the gap.
  - **Example:** `d 2` (Deletes the 2nd line in the document).

- **Print Document (`p`)**
  - **Syntax:** `p`
  - **Description:** Displays all current lines in the document with their corresponding line numbers.

- **Save File (`s`)**
  - **Syntax:** `s <filename>`
  - **Description:** Writes the current in-memory document to a text file.
  - **Example:** `s output.txt`

- **Load File (`l`)**
  - **Syntax:** `l <filename>`
  - **Description:** Clears the current document and loads text from the specified file.
  - **Example:** `l input.txt`

- **Quit (`q`)**
  - **Syntax:** `q`
  - **Description:** Safely frees memory and exits the editor.
