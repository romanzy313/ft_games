// ************************************************************************** //
//                                                                            //
//                                                            ::::::::        //
//   main.h                                                  :+:    :+:       //
//                                                          +:+               //
//   By: rvolovoy <rvolovoy@student.codam.nl>              +#+                //
//                                                        +#+                 //
//   Created: 2026/07/01 23:07:21 by rvolovoy            #+#    #+#           //
//   Updated: 2026/07/02 00:34:05 by rvolovoy            ########   odam.nl   //
//                                                                            //
// ************************************************************************** //

// UART style communication via shared files.
// to play a game, each user creates 2 pipes:
// First to write own events (TX)
// Second to read other player events (RX)
// A player can write to their own file. Others can only read.

// This is a "wire" to recieve data
typedef struct s_comm_rx {
	int		fd;
} t_comm_rx;

t_comm_rx *comm_rx_open(t_comm_rx *rx, char *directory, char *username);
int	comm_rx_poll(t_comm_rx *rx, char *buff, int size);
void	comm_rx_close(t_comm_rx *rx);

// This is a "wire" to transmit (send) data
typedef struct s_comm_tx {
	int		fd;
	char	*path;
} t_comm_tx;

t_comm_tx	*comm_tx_open(t_comm_tx *tx, char *directory, char *username);
void	comm_tx_close(t_comm_tx *tx);
void	comm_tx_send(t_comm_tx *tx, char *data, int size);
