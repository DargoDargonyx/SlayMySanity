/**
 * @file error.h
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Handles the logic for error handling.
 */

#ifndef ERROR_H
#define ERROR_H

#define ESTAT_NONE 0
#define ESTAT_WINDOW 1

typedef struct {
    int statusNum;
    char* msg;
} Error;


Error createError(int statusNum, char* msg);
char* getErrorStatusDesc(Error* err);


#endif
