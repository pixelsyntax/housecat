#ifndef H_BUILD_H
#define H_BUILD_H

#include "h_err.h"
#include "h_section.h"

#include <stdio.h>

typedef struct h_build_strs
{
	char* index;
	char* post;
	char* menu;
	char* menu_section;
} h_build_strs;

h_err* h_build(h_section* root, char* rootdir, struct h_build_strs str);

char* h_build_menu(h_section* root, h_section* current, h_build_strs strs);

h_err* h_build_section(h_section* root, h_section* section, FILE* file, h_build_strs srts);

#endif
