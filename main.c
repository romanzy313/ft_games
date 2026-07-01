#include <stdio.h>
#include "main.h"

// idea is to open file for reading and read it line by line
// each line is a game event
int	main(int argc, char **argv)
{
	char	*directory;
	char	*my_username;
	char	*peer_username;

	if (argc != 1 + 3)
	{
		printf("Usage: \n");
		printf("%s <directory> <my_username> <peer_username>\n", argv[0]);
		return (1);
	}
	directory = argv[1];
	my_username = argv[2];
	peer_username = argv[3];

	printf("filename: %s\n", directory);
	printf("my username: %s\n", my_username);
	printf("other username: %s\n", peer_username);

	t_comm_tx	my_tx;
	t_comm_rx	my_rx;
	t_comm_tx	peer_tx;
	t_comm_rx	peer_rx;
	//
	// comm_tx_open(&my_tx, directory, my_username);
	// comm_tx_open(&peer_tx, directory, peer_username);
	// comm_rx_open(&my_rx, directory, peer_username);
	// comm_rx_open(&peer_rx, directory, my_username);
	//
	// comm_rx_close(&my_rx);
	// comm_rx_close(&peer_rx);
	// comm_tx_close(&my_tx);
	// comm_tx_close(&peer_tx);

	// this is ugly... the comm should allocate structs itself
	t_comm	my_comm = {
		.rx = &my_rx,
		.tx = &my_tx,
	};
	t_comm	peer_comm = {
		.rx = &peer_rx,
		.tx = &peer_tx,
	};

	comm_open(&my_comm, directory, my_username, peer_username);
	comm_open(&peer_comm, directory, peer_username, my_username);

	comm_close(&my_comm);
	comm_close(&peer_comm);

	return (0);
}
