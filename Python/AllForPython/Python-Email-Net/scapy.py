#!/usr/bin/python3
'''exe with the super root
1. pcap = sniff(offline='xx/xx.pcap'): add the offline pcap file
2. dpkt = sniff(iface='wlan0', count=100): without count default capture forever
3. print(dpkt): can show the information of all the captures file, dpkt is the list
4. dpkt[0] can use dict type to get the information
   * dpkt[0][Ether].type: Type of the package
   * dpkt[0][Ether].src
   * dpkt[0][Ether].dst
   * dpkt[0][Ether].load: acces to the data of the packet
5. callback function
   dpkt = sniff(iface='wlan0', count=100, filter="tcp", prn=function_name)
   prn function receive the packet as the argument to solve
6. ls(): show the scapy class for user
   ls()
   ls(Ether)
   ...
'''

from scapy.all import *
import ipdb
import time

verbose = True
verbose = False

def show(packet):
    '''
    Ether:
        * dst
        * src
        * type
    IPV6
        * version
        * src
        * dst
    TCP
        * src port
        * dst port
        * seq
        * ack
        * window
    '''
    print('-' * 12, time.ctime(), '-' * 12)
    
    if verbose:
        packet.show()
        return 

    # save the pcap file first
    with open(str(int(time.time())) + '.pcap', 'w') as f:
        f.write(str(packet)) 

    # show the pcap, show TCP only
    # packet.show()
    # ipdb.set_trace()
    for item in [Ether, IPv6, TCP]:
        if item == Ether:
            print('[ Ether ]:')
            print('\tdst:\t', packet[item].dst)
            print('\tsrc:\t', packet[item].src)
            print('\ttype:\t', packet[item].type)
        elif item == IPv6:
            try:
                # check the IPv6 packet
                packet[item]
            except:
                continue

            print('[ IPv6 ]:\t')
            print('\tversion:\t', 'IPv6')
            print('\tsrc:\t', packet[item].src)
            print('\tdst:\t', packet[item].dst)
        elif item == TCP:
            print('[ TCP ]:')
            print('\tsrcport:\t', packet[item].sport)
            print('\tdstport:\t', packet[item].dport)
            print('\tseqnum:\t', packet[item].sport)
            print('\tacknum:\t', packet[item].sport)
            print('\twindow:\t', packet[item].sport)
        else:
            pass

    print('-' * 50)

if __name__ == "__main__":
    try:
        dpkt = sniff(filter="tcp", iface='wlan0', count = 3, prn=show)
    except Exception as e:
        print(e)
        exit(1)
