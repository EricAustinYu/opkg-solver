
AM_CFLAGS=-Wall -DHOST_CPU_STR=\"@host_cpu@\" -DDATADIR=\"@datadir@\" \
	-I$(top_srcdir)	$(LIBARCHIVE_CFLAGS) $(BIGENDIAN_CFLAGS) $(CURL_CFLAGS) \
	$(GPGME_CFLAGS) $(GPGERR_CFLAGS) $(PATHFINDER_CFLAGS) $(SOLVER_CFLAGS)

libopkg_includedir=$(includedir)/libopkg

opkg_headers = active_list.h cksum_list.h conffile.h conffile_list.h \
	file_util.h hash_table.h list.h md5.h nv_pair.h nv_pair_list.h \
	opkg_archive.h opkg_cmd.h opkg_conf.h opkg_configure.h \
	opkg_download.h opkg_install.h opkg_message.h \
	opkg_remove.h opkg_utils.h parse_util.h pkg.h \
	pkg_depends.h pkg_dest.h pkg_dest_list.h pkg_extract.h pkg_hash.h \
	pkg_parse.h pkg_src.h pkg_src_list.h pkg_vec.h release.h \
	release_parse.h sha256.h sprintf_alloc.h str_list.h void_list.h \
	xregex.h xsystem.h xfuncs.h opkg_verify.h

opkg_sources = opkg_cmd.c opkg_configure.c opkg_download.c \
	opkg_install.c opkg_remove.c opkg_conf.c release.c \
	release_parse.c opkg_utils.c pkg.c pkg_depends.c pkg_extract.c \
	hash_table.c pkg_hash.c pkg_parse.c pkg_vec.c conffile.c \
	conffile_list.c nv_pair.c nv_pair_list.c pkg_dest.c pkg_dest_list.c \
	pkg_src.c pkg_src_list.c str_list.c void_list.c active_list.c \
	file_util.c opkg_message.c md5.c parse_util.c cksum_list.c \
	sprintf_alloc.c xregex.c xsystem.c xfuncs.c opkg_archive.c \
	opkg_verify.c

if HAVE_CURL
opkg_sources += opkg_download_curl.c
else
opkg_sources += opkg_download_wget.c
endif
if HAVE_SHA256
opkg_sources += sha256.c
opkg_headers += sha256.h
endif
if HAVE_OPENSSL
opkg_sources += opkg_openssl.c
opkg_headers += opkg_openssl.h
endif
if HAVE_GPGME
opkg_sources += opkg_gpg.c
opkg_headers += opkg_gpg.h
endif
if HAVE_LIBOPKG_API
opkg_sources += opkg.c
opkg_headers += opkg.h
endif
if HAVE_SOLVER
opkg_sources += opkg_solver.c
opkg_headers += opkg_solver.h
if HAVE_SOLVER_LIBSOLV
opkg_sources += opkg_solver_libsolv.c
opkg_headers += opkg_solver_libsolv.h
endif
else
opkg_sources += opkg_action.c opkg_upgrade.c
opkg_headers += opkg_action.h opkg_upgrade.h
endif

lib_LTLIBRARIES = libopkg.la
libopkg_la_SOURCES = $(opkg_sources) $(opkg_headers)

# Only install headers if we're building the API
if HAVE_LIBOPKG_API
libopkg_include_HEADERS = $(opkg_headers)
endif

libopkg_la_LIBADD = $(LIBARCHIVE_LIBS) \
		    $(CURL_LIBS) $(GPGME_LIBS) $(GPGERR_LIBS) $(OPENSSL_LIBS) \
		    $(PATHFINDER_LIBS) $(SOLVER_LIBS)

libopkg_la_LDFLAGS = -version-info 1:0:0
