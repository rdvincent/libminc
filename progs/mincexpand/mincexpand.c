/* ----------------------------- MNI Header -----------------------------------
@NAME       : mincexpand
@INPUT      : argc, argv - command line arguments
@OUTPUT     : (none)
@RETURNS    : status
@DESCRIPTION: Program to expand a compressed minc image volume, if necessary.
@METHOD     : 
@GLOBALS    : 
@CALLS      : 
@CREATED    : January 20, 1995 (Peter Neelin)
@MODIFIED   : $Log: mincexpand.c,v $
@MODIFIED   : Revision 1.3  1995-01-24 09:06:19  neelin
@MODIFIED   : Added -name_only option.
@MODIFIED   :
 * Revision 1.2  95/01/24  08:48:57  neelin
 * Added optional output file argument.
 * 
 * Revision 1.1  95/01/23  08:33:31  neelin
 * Initial revision
 * 
 * Revision 1.1  95/01/20  15:51:32  neelin
 * Initial revision
 * 
@COPYRIGHT  :
              Copyright 1995 Peter Neelin, McConnell Brain Imaging Centre, 
              Montreal Neurological Institute, McGill University.
              Permission to use, copy, modify, and distribute this
              software and its documentation for any purpose and without
              fee is hereby granted, provided that the above copyright
              notice appear in all copies.  The author and McGill University
              make no representations about the suitability of this
              software for any purpose.  It is provided "as is" without
              express or implied warranty.
---------------------------------------------------------------------------- */

#ifndef lint
static char rcsid[]="$Header: /private-cvsroot/minc/progs/mincexpand/mincexpand.c,v 1.3 1995-01-24 09:06:19 neelin Exp $";
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <minc.h>
#include <ParseArgv.h>
#include <minc_def.h>

/* Constants */
#ifndef TRUE
#  define TRUE 1
#  define FALSE 0
#endif

/* Variables used for argument parsing */
int header_only = FALSE;
int name_only = FALSE;

/* Argument table */
ArgvInfo argTable[] = {
   {"-header_only", ARGV_CONSTANT, (char *) TRUE, (char *) &header_only,
       "Expand only enough file to get the header."},
   {"-all_data", ARGV_CONSTANT, (char *) FALSE, (char *) &header_only,
       "Expand the whole file (default)."},
   {"-name_only", ARGV_CONSTANT, (char *) TRUE, (char *) &name_only,
       "Print out only the file name."},
   {NULL, ARGV_END, NULL, NULL, NULL}
};

/* Main program */

int main(int argc, char *argv[])
{
   char *filename, *tempfile, *newfile;
   int created_tempfile;

   /* Check arguments */
   if (ParseArgv(&argc, argv, argTable, 0) || 
       (argc < 2) || (argc > 3)) {
      (void) fprintf(stderr, 
                     "\nUsage: %s [<options>] <infile> [<outfile>]\n", 
                     argv[0]);
      (void) fprintf(stderr,
                       "       %s -help\n\n", argv[0]);
      exit(EXIT_FAILURE);
   }
   filename  = argv[1];
   if (argc == 3)
      tempfile = argv[2];
   else
      tempfile = NULL;

   /* Expand the file */
   ncopts = 0;
   newfile = miexpand_file(filename, tempfile, header_only, &created_tempfile);
   if (newfile == NULL)
      newfile = strdup(filename);

   /* Print out file name and message about temporary file */
   (void) printf("%s\n", newfile);
   if (!name_only) {
      if (created_tempfile) {
         (void) printf("Temporary\n");
      }
      else {
         (void) printf("Original\n");
      }
   }

   /* Free the temporary file name string */
   FREE(newfile);

   exit(EXIT_SUCCESS);
}

