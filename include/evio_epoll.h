#ifndef __EVIO_EPOLL__
#define __EVIO_EPOLL__

#include <sys/epoll.h>

#define EVIO_IN	    EPOLLIN
#define EVIO_ET	    EPOLLET
#define EVIO_ERR	EPOLLERR
#define EVIO_OUT    EPOLLOUT 

typedef void (*evio_call_client)(void *data);
typedef void (*evio_call_accept)(int sockfd);

struct ev_ct
{
	int                      fd;	
	int                      event_count;
	unsigned int             max_events;
	struct epoll_event       *events;
};

struct ev_method 
{
	const char *name;
	void (*free)(struct ev_ct *ct);
	int  (*init)(struct ev_ct *ct, int max_events);
	int  (*wait)(struct ev_ct *ct, int timeout, int fd, evio_call_accept _accept, evio_call_client _client);
	int  (*add)(struct ev_ct *ct, int fd, int events, void *data);
	int  (*mod)(struct ev_ct *ct, int fd, int events, void *data);
	int  (*del)(struct ev_ct *ct, int fd);
};


extern struct ev_method em;

#endif

