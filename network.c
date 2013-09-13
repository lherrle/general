//
//  network.c
//
//
//  Created by Laura Herrle on 5/10/13.
//
//

#include "kernel.h"
#include "chash.h"
#include "network.h"

#define RING_SIZE = 16;
#define BUFFER_SIZE 4000; //change

volatile struct dev_net* net;
volatile struct dma_ring_slot* ring;
volatile struct hashtable *evil1, *evil2, *spam1, *spam2, *vul1, *vul2;
int num_packets = 0, num_spammers = 0, num_vulnerable = 0, num_evil = 0;
unsigned char* pointer_buffer;
unsigned int* size_buffer;
int pointer_buffer_head, pointer_buffer_tail, pointer_buffer_cap;

unsigned long djb2(unsigned char *pkt, int n) {
    unsigned long hash = 5381;
    int i = 0;
    while (i < n-8) {
        hash = hash * 33 + pkt[i++];
        hash = hash * 33 + pkt[i++];
        hash = hash * 33 + pkt[i++];
        hash = hash * 33 + pkt[i++];
        hash = hash * 33 + pkt[i++];
        hash = hash * 33 + pkt[i++];
        hash = hash * 33 + pkt[i++];
        hash = hash * 33 + pkt[i++];
    }
    while (i < n)
        hash = hash * 33 + pkt[i++];
    return hash;
}

void lock(int loc) {
    ///ll and sc
}

void network_init() {
    /* Find out where network region is in memory. */
    for (int i = 0; i < 16; i++) {
        if (bootparams->devtable[i].type == DEV_TYPE_NETWORK) {
            puts("Detected network device...");
            // find a virtual address that maps to this I/O region
            net = physical_to_virtual(bootparams->devtable[i].start);
            //initialize ring buffer
            ring = (struct dma_ring_slot*) malloc(sizeof(struct dma_ring_slot) * RING_SIZE);
            for (int i = 0; i < RING_SIZE; ++i) {
                void* space = malloc(BUFFER_SIZE);
                ring[i]->dma_base = physical_to_virtual(space);
                ring[i]->dma_len = BUFFER_SIZE/8;
            }
            // set other data
            net->rx_base = virtual_to_physical(ring);
            net->rx_capacity = RING_SIZE;
            net->rx_head = 0;
            net->rx_tail = 0;
        }   
    }
    //allocate hashtables
    make(evil1, evil2);
    make(spam1, spam2);
    make(vul1, vul2);
    pointer_buffer = (unsigned char*) malloc((sizeof(char)) * 2000);
    size_buffer = (unsigned int*) malloc(sizeof(int) * 2000);
    pointer_buffer_head = 0;
    pointer_buffer_tail = 0;
    pointer_buffer_cap = 2000;
}

void command(unsigned char *p, int n) {
    if((short)(p->secret_big_endian)==(0x1034)) {
        unsigned short cmd = p->cmd_big_endian;
        unsigned int data = p->data_big_endian;
        if(cmd==HONEYPOT_ADD_SPAMMER) {
            insert(spam1, spam2, data, data);
        } else if(cmd==HONEYPOT_ADD_EVIL) {
            insert(evil1, evil2, data, data);
        } else if(cmd==HONEYPOT_ADD_VULNERABLE) {
            insert(vul1, vul2, data, data);
        } else if(cmd==HONEYPOT_DEL_SPAMMER) {
            delete(spam1, spam2, data, data);
        } else if(cmd==HONEYPOT_DEL_EVIL) {
            delete(evil1, evil2, data, data);
        } else if(cmd==HONEYPOT_DEL_VULNERALBE) {
            delete(vul1, vul2, data, data);
        } else if(cmd==HONEYPOT_PRINT) {
            //PRINT EVERYTHING
        }else {
            //output invalid command
        }
    }
}

void spam(unsigned char *p, int n) {
    if(contains(spam1, spam2, p->headers->ip_source_address_big_endian, p->headers->ip_source_address_big_endian)==1) {
        num_spammers++;
        insert(spam1, spam2, p->headers->ip_source_address_big_endian, p->headers->ip_source_address_big_endian) //updates count
    }
}

void evil(unsigned char *p, int n) {
    hash=djb2(p, n);
    if(contains(evil1, evil2, hash, hash)==1) {
        num_evil++;
        insert(evil1, evil2, hash, hash); //updates count
    }
}

void vulnerable(unsigned char *p, int n) {
    if(contains(vul1, vul2, p->headers->udp_dest_port_big_endian, p->headers->udp_dest_port_big_endian)==1) {
        num_vulnerable++;
        insert(vul1, vul2, p->headers->udp_dest_port_big_endian, p->headers->udp_dest_port_big_endian); //updates count
    }
}

void handle_packet(unsigned char *p, int n) {
    //handle: calls to pipeline, puts in pipeline buffer (later)
    //does all handling for now
    num_packets++;
   
    if (pointer_buffer_tail != pointer_buffer_head) {
        if(pointer_buffer_tail%pointer_buffer_cap == pointer_buffer_head%pointer_buffer_cap) {
            printf("capacity reached");
        }
    }
    
    pointer_buffer[pointer_buffer_head] = p;
    size_buffer[pointer_buffer_head] = n;
    pointer_buffer_head++;
}

struct pkt_info get_next_packet() {
    //note: if you run this on the same core that is polling bad things will happen
    while (1) {
        if (pointer_buffer_tail != pointer_buffer_head) {
            struct pkt_info pkt;
            pkt.pkt_address = pointer_buffer[pointer_buffer_tail];
            pkt.size = size_buffer[pointer_buffer_tail];
            pointer_buffer_tail++;
            return pkt;
        }
    }
}

void network_poll() {
    unsigned char* packet;
    while(1) {
        if (net->rx_head!=net->rx_tail) {
            packet = (char*)malloc(net->dma_len);
            for(int i=0; i<net->dma_len; i++) {
                packet[i] = physical_to_virtual(ring[net->rx_tail mod rx_capacity]->dma_base)[i];
            }
            net->rx_tail++;
            
            handle_packet(packet, net->dma_len);
        }
    }
}

void network_set_interrupts(int opt) {
    net->cmd = NET_SET_INTERRUPTS;
    net->data = ((opt == 0) ? 0 : 1);
}

void network_start_receive() {
    net->cmd = NET_SET_POWER;
    net->data = 1;
    net->cmd = NET_SET_RECEIVE;
    net->data = 1;
}
