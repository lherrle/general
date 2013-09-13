//
//  network.h
//  
//
//  Created by Laura Herrle on 5/12/13.
//
//

#ifndef _network_h
#define _network_h

//this is a struct that contains the stuff about a packet that you need for a function call
struct pkt_info {
    unsigned char* pkt_address;
    int size;
}

void lock(int loc);

void network_init();

void command(unsigned char *p, int n);

void spam(unsigned char *p, int n);

void evil(unsigned chvimar *p, int n);

void vulnerable(unsigned char *p, int n);

void handle_packet(unsigned char *p, int n);

struct pkt_info get_next_packet();

void network_poll();

void network_set_interrupts(int opt);

void network_start_receive();

#endif
