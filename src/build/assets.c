#include "../build.h"
#include "../util.h"
#include "../file.h"

#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

h_err* h_build_assets(const char* rootdir)
{
	char* assetsdir = h_util_path_join(rootdir, H_FILE_ASSETS);
	char* outassetsdir = h_util_path_join(
		rootdir,
		H_FILE_OUTPUT "/" H_FILE_OUT_META "/" H_FILE_OUT_ASSETS
	);

	//Check status of rootdir/assets, returning if it doesn't exist
	{
		int err = h_util_file_err(assetsdir);
		if (err == ENOENT)
			return NULL;
		if (err && err != EEXIST)
			return h_err_from_errno(err, assetsdir);
	}

	//Create rootdir/public/_/assets if it doesn't exist
	if (mkdir(assetsdir, 0777) == -1 && errno != EEXIST)
		return h_err_from_errno(errno, assetsdir);

	//Make sure dirs are okay
	DIR* d1 = opendir(assetsdir);
	if (d1 == NULL)
		return h_err_from_errno(errno, assetsdir);
	closedir(d1);
	if (mkdir(outassetsdir, 0777) == -1 && errno != EEXIST)
		return h_err_from_errno(errno, assetsdir);

	h_util_cp_dir(assetsdir, outassetsdir);
	free(assetsdir);
	free(outassetsdir);

	return NULL;
}
