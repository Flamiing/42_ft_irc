/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:28:56 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/22 17:52:16 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_HPP
# define ERRORS_HPP

# include <errno.h>

/* PRINTING MODES */
# define NORMAL 0
# define W_ERRNO 1

/* ERROR MESSAGES */
# define BAD_PORT "Error: invalid port."
# define ERROR_SOCKET "Error: socket(): "
# define ERROR_BIND "Error: bind(): "
# define ERROR_LISTEN "Error: listen(): "
# define ERROR_POLL "Error: poll(): "
# define ERROR_ACCEPT "Error: accept(): "
# define ERROR_SETSOCKOPT "Error: setsockopt(): "

/* ERRORS */
# define INVALID_SOCKET -1
# define SOCKET_ERROR -1
# define POLL_FAILED -1
# define ERROR -1

/* PROTOTYPE */
int printError(const std::string error, int mode);

#endif