/**
 * @file font.h
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Handles the logic for fonts.
 */

#ifndef FONT_H
#define FONT_H

#define F_JETBRAINS_MONO 1

typedef struct {
    char* filename;
    int size;
} Font;


Font createFont(int fontNum, int size);


#endif
