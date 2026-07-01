// ************************************************************************** //
//                                                                            //
//                                                            ::::::::        //
//   comm.c                                                  :+:    :+:       //
//                                                          +:+               //
//   By: rvolovoy <rvolovoy@student.codam.nl>              +#+                //
//                                                        +#+                 //
//   Created: 2026/07/01 23:03:52 by rvolovoy            #+#    #+#           //
//   Updated: 2026/07/02 00:36:33 by rvolovoy            ########   odam.nl   //
//                                                                            //
// ************************************************************************** //

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

char *get_full_path(char *base_path, char *username)
{
	char *path;

	path = calloc(sizeof(char), strlen(base_path) + strlen(username) + 2);
	strcat(path, base_path);
	strcat(path, "/");
	strcat(path, username);
	return (path);
}

t_comm_rx *comm_rx_open(t_comm_rx *rx, char *directory, char *username)
{
	char		*path;
	
	path = get_full_path(directory, username);
	rx->fd = open(path, O_RDONLY);
	free(path);
	if (rx->fd == -1)
	{
		return (NULL);
	}
	return (rx);
}

// reads one line at the time.
// Returns length read. Partial reads are not supported yet
// -1 is returned on error?
// For now, assume the max length is fixed
int	comm_rx_poll(t_comm_rx *rx, char *buff, int size)
{
	int	bytes_read;

	bytes_read = read(rx->fd, buff, size);
	return (bytes_read);
}

void	comm_rx_close(t_comm_rx *rx)
{
	close(rx->fd);
}

t_comm_tx *comm_tx_open(t_comm_tx *tx, char *directory, char *username)
{
	char		*path;
	
	path = get_full_path(directory, username);
	tx->fd = open(path, O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (tx->fd == -1)
	{
		free(path);
		return (NULL);
	}
	tx->path = path;
	return tx;
}

// closes transmission and deletes the underlying file
void	comm_tx_close(t_comm_tx *tx)
{
	close(tx->fd);
	unlink(tx->path);
	free(tx->path);
}

void	comm_tx_send(t_comm_tx *tx, char *data, int size)
{
	write(tx->fd, data, size);
}
