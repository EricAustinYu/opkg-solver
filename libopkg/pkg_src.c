/* pkg_src.c - the opkg package management system

   Carl D. Worth

   Copyright (C) 2001 University of Southern California

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2, or (at
   your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.
*/

#include <malloc.h>

#include "file_util.h"
#include "opkg_conf.h"
#include "opkg_message.h"
#include "opkg_verify.h"
#include "pkg_src.h"
#include "sprintf_alloc.h"
#include "xfuncs.h"

int pkg_src_init(pkg_src_t *src, const char *name, const char *base_url, const char *extra_data, int gzip)
{
    src->gzip = gzip;
    src->name = xstrdup(name);
    src->value = xstrdup(base_url);
    if (extra_data)
	src->extra_data = xstrdup(extra_data);
    else
	src->extra_data = NULL;
    return 0;
}

void pkg_src_deinit(pkg_src_t *src)
{
    free (src->name);
    free (src->value);
    if (src->extra_data)
	free (src->extra_data);
}

int
pkg_src_verify(pkg_src_t *src)
{
    int err = 0;
    char *feed;
    char *sigfile;
    const char *lists_dir;

    lists_dir = opkg_config->restrict_to_default_dest ?
        opkg_config->default_dest->lists_dir : opkg_config->lists_dir;
    sprintf_alloc(&feed, "%s/%s", lists_dir, src->name);
    sprintf_alloc(&sigfile, "%s.sig", feed);

    if (!file_exists(sigfile))
    {
	opkg_msg(ERROR, "Signature file is missing for %s. "
		"Perhaps you need to run 'opkg update'?\n",
		src->name);
	err = -1;
	goto cleanup;
    }

    err = opkg_verify_signature(feed, sigfile);
    if (err) {
        opkg_msg(ERROR, "Signature verification failed for %s.\n", src->name);
	goto cleanup;
    }

    opkg_msg(DEBUG, "Signature verification passed for %s.\n", src->name);

cleanup:
    free(sigfile);
    free(feed);
    return err;
}
