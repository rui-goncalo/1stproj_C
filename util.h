/**
 * @file util.h
 * @author Micael Dias
 * @date 10/12/20
 * @brief Helper functions
 */

#ifndef UTIL_H
#define UTIL_H

/**
 * Reads a file from given path
 * @param path The file path
 * @param size Updates the size (num of lines read) of the file from a ptr
 * @return char*
 */
char* h_util_file_read(const char* path, int* size);

/**
 * Read a string from stdin
 * @param length The length of the string to read
 * @param msg The message to displays
 * @return char* Returns the readed string
 */
char* h_util_get_string(int length, const char* msg);

/**
 * Gets an alphabetical letter from stdin
 * @param msg Sets a message to display
 * @return char Returns the alpha char readed
 */
char h_util_get_alphabetical_char(const char* msg);

/**
 * Gets an int from stdin
 * @param min Sets a min value to input
 * @param max Sets a max value to input
 * @param msg Sets a message to display
 * @return int Returns the readed integer
 */
int h_util_get_int(int min, int max, const char* msg);

/**
 * Gets a float from stdin
 * @param min Sets a min value to input
 * @param max Sets a max value to input
 * @param msg Sets a message to display
 * @return float
 */
float h_util_get_float(float min, float max, const char* msg);

/**
 * Cleans buffer from stdin
 */
void h_util_clean_buffer();

#endif //UTIL_H
