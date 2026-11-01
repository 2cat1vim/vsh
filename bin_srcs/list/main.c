#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <string.h>

const char *normalize_date(long int d) {
	struct tm tm;
	tm.tm_year = d / 10000 - 1900;
	tm.tm_mon = (d % 10000) / 100 - 1;
	tm.tm_mday = d % 100;
	tm.tm_hour = tm.tm_min = tm.tm_sec = 0;
	tm.tm_isdst = -1;
	time_t tt = mktime(&tm);
	return ctime(&tt);
}

int main(void) {
	char *dir_name = get_current_dir_name();
	if (!dir_name) {
		perror("get_current_dir_name");
		exit(EXIT_FAILURE);
	}

	DIR *dir = opendir(dir_name);
	if (!dir) {
		free(dir_name);
		perror("opendir");
		exit(EXIT_FAILURE);
	}
	free(dir_name);
	
	while (1) {
		errno = 0;
		struct dirent *sdir = readdir(dir);
		if (!sdir && errno != 0) {
			perror("sdir");
			exit(EXIT_FAILURE);
		}
		else if (!sdir) {
			break;
		}
		struct stat sb;
		if (stat(sdir->d_name, &sb) == -1) {
			perror("stat");
			exit(EXIT_FAILURE);
		}
		const char *date = normalize_date(sb.st_mtime);
		char smode[32];
		// view man 7 inode to convert mode to smode
		fprintf(stdout, "%s mode:%s bytes:%ld uid:%u gid:%u date:%.12s\n",
			       	sdir->d_name, smode, sb.st_size,
				sb.st_uid, sb.st_gid, date + 4);
	}
	if (closedir(dir) == -1) {
		perror("closedir");
		exit(EXIT_FAILURE);
	}
}
