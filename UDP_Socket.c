/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::Network:Service
 * Copyright (c) 2004-2019 Arm Limited (or its affiliates). All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    UDP_Socket.c
 * Purpose: UDP Socket Code Template
 * Rev.:    V7.0.0
 *----------------------------------------------------------------------------*/
//! [code_UDP_Socket]
#include "rl_net.h"
#include <stdio.h>
#include <string.h>
 
int32_t udp_sock;                       // UDP socket handle
volatile int dhcp_ready=0;

static void print_address (void) {
  uint8_t ip4_addr[NET_ADDR_IP4_LEN];
  char    ip4_ascii[16];

  if (netIF_GetOption (NET_IF_CLASS_ETH, netIF_OptionIP4_Address,
                                         ip4_addr, sizeof(ip4_addr)) == netOK) {
  /* Print IPv4 network address */
    netIP_ntoa (NET_ADDR_IP4, ip4_addr, ip4_ascii, sizeof(ip4_ascii));
    printf ("IP4=%-15s\n", ip4_ascii);    
  }
}
 
/* IP address change notification */
void netDHCP_Notify (uint32_t if_num, uint8_t option, const uint8_t *val, uint32_t len) {

  (void)if_num;
  (void)val;
  (void)len;

  if (option == NET_DHCP_OPTION_IP_ADDRESS) {
    /* IP address change, trigger LCD update */
    print_address ();
  }
	dhcp_ready=1;
}
 
// Notify the user application about UDP socket events.
uint32_t udp_cb_func (int32_t socket, const  NET_ADDR *addr, const uint8_t *buf, uint32_t len) {
 
  // Data received
  /* Example
  if ((buf[0] == 0x01) && (len == 2)) {
    // Switch LEDs on and off
    // LED_out (buf[1]);
  }
  */
  return (0);
}


// Send UDP data to destination client.
void send_udp_data (void) {
	
	uint8_t buffer[]="Hello Vives";
 
  if (udp_sock > 0) {
    //Example
    // IPv4 address: 192.168.0.1
    NET_ADDR addr = { NET_ADDR_IP4, 1001, 192, 168, 137, 1 };
    // IPv6 address: [fe80::1c30:6cff:fea2:455e]
//  NET_ADDR addr = { NET_ADDR_IP6, 2000,
//                    0xfe, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//                    0x1c, 0x30, 0x6c, 0xff, 0xfe, 0xa2, 0x45, 0x5e };
    uint8_t *sendbuf;
    
    sendbuf = netUDP_GetBuffer (sizeof(buffer));
    memcpy(sendbuf,buffer,sizeof(buffer));
 
    netUDP_Send (udp_sock, &addr, sendbuf, sizeof(buffer));    
  }
}
 
// Allocate and initialize the socket.
//* Example
int main_udp (void) {
 
	printf("before netinitialize\n");
  netInitialize ();
	printf("after netinitialize\n");
	
	while(dhcp_ready==0)
		;
 
  // Initialize UDP socket and open port 2000
  udp_sock = netUDP_GetSocket (udp_cb_func);
  if (udp_sock > 0) {
    netUDP_Open (udp_sock, 2000);
  }
	send_udp_data();
	return 0;
}
//*/
//! [code_UDP_Socket]
