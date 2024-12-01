
📜 Get Next Line - 42 Project
The Get Next Line project is one of the foundational challenges at 42 that focuses on file I/O and memory management. The task is to create a function that reads a file line by line, returning each line as a string, with memory properly managed for each read.

🎯 Project Goal
The goal of this project is to implement a function called get_next_line(), which reads a file descriptor and returns a line from the file, one line at a time. It should handle the following requirements:

Efficient memory management: Allocate memory dynamically to store each line and handle reallocation as necessary.
Multiple file descriptors: Support reading from multiple files at the same time.
Handling various edge cases: Properly handle files of different sizes, empty files, and EOF (End of File).
🛠️ Key Skills & Concepts
This project helps you develop a deep understanding of:

File handling: Working with file descriptors, reading from files in a non-blocking manner.
Memory management: Dynamically allocating and freeing memory, especially when dealing with variable-length strings and buffers.
String manipulation: Efficiently working with string buffers and handling newline characters.
Edge case handling: Dealing with files with no lines, very large files, or cases where memory runs out.
📚 Learning Outcomes
By completing this project, you will:

Improve your understanding of low-level file I/O operations in C.
Gain a stronger grasp of how memory is allocated and freed when working with strings and buffers.
Develop debugging skills by handling tricky edge cases and ensuring your solution works across all possible scenarios.
