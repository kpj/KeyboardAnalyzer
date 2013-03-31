CC=gcc

makeKeylogger: keylog.c inet_utils.c x_utils.c file_utils.c
	$(CC) -Wall -lXtst -lX11 -lresolv -o keylogger keylog.c inet_utils.c x_utils.c file_utils.c
