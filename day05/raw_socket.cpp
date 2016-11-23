/* ************************************************************************
 *       Filename:  raw_socket.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/04/2016 09:58:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "../h.h"
#include <linux/if_ether.h>
#include <linux/if.h>
#include <linux/sockios.h>
#include <linux/if_packet.h>
#include <linux/if_arp.h>
typedef struct eth_frame
{
    unsigned char dst[6];
    unsigned char src[6];
    unsigned short type;
} eth_frame;

typedef struct ip_frame
{
    unsigned char head_len:4; // 已4个字节为单位
    unsigned char version:4;
    unsigned char tos;   // 服务类型
    unsigned short total; // 总长度
    unsigned short id;  // 标识
    unsigned short flag:3;
    unsigned short off:13;
    unsigned char ttl; // 生存时间
    unsigned char protocol; // 协议：TCP／UDP
    unsigned short crc; // 校验和
    unsigned int src_addr;
    unsigned int dst_addr;
} ip_frame;

typedef struct tcp_frame
{
    unsigned short src_port;
    unsigned short dst_port;
    unsigned int seq;
    unsigned int ack_seq;
#if 0
    unsigned short head_len: 4;
    unsigned short reserve: 6;
    unsigned short URG:1;
    unsigned short ACK:1;
    unsigned short PSH:1;
    unsigned short RST:1;
    unsigned short SYN:1;
    unsigned short FIN:1;
#endif
    unsigned short xxx;

    unsigned short window_size;
    unsigned short crc;
    unsigned short mpointer;
} tcp_frame;

void dump_eth_frame(eth_frame* frame)
{
    if(ntohs(frame->type) != 0x0800)
    {
        return;
    }
    unsigned char* p = frame->dst;
    printf("dst is %02x:%02x:%02x:%02x:%02x:%02x\n", p[0], p[1], p[2], p[3], p[4], p[5]);
    p = frame->src;
    printf("src is %02x:%02x:%02x:%02x:%02x:%02x\n", p[0], p[1], p[2], p[3], p[4], p[5]);

    printf("frame type is 0x%x\n", ntohs(frame->type));
}

void dump_ip_frame(ip_frame* frame)
{
    printf("version is \t0x%x\n", frame->version);
    printf("headlen is \t0x%x\n", frame->head_len);
    printf("tos is \t0x%x\n", frame->tos);
    printf("total is \t0x%x\n", frame->total);
    printf("id is \t0x%x\n", frame->id);
    printf("flag is \t0x%x\n", frame->flag);
    printf("offset is \t0x%x\n", frame->off);
    printf("ttl is \t0x%x\n", frame->ttl);
    printf("protocol is \t0x%x\n", frame->protocol);
    printf("crc is \t0x%x\n", frame->crc);
    printf("src is \t0x%x\n", frame->src_addr);
    printf("dst is \t0x%x\n", frame->dst_addr);
}

int main()
{
    // 运行原始套接字需要root权限
    //int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_IP|ETH_P_ARP|ETH_P_ALL));
    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if(sock < 0)
    {
        perror("socket");
        return 1;
    }

    // 得到网卡信息，配置网卡为混在模式
    struct ifreq ifstruct; // 网卡信息
    strcpy(ifstruct.ifr_name, "ens33"); // 指定网卡
    
    // 调用ioctl获取网卡信息
    int ret;
    ret = ioctl(sock, SIOCGIFINDEX, &ifstruct);
    if(ret < 0)
    {
        perror("ioctl SIOCGIFINDEX");
        return 2;
    } 

    printf("get if index = %d\n", ifstruct.ifr_ifru.ifru_ivalue);

    // 绑定地址, ll = low level
    struct sockaddr_ll addr;
    addr.sll_family = AF_PACKET;
    addr.sll_ifindex = ifstruct.ifr_ifru.ifru_ivalue;
    addr.sll_protocol = htons(ETH_P_ALL);
    addr.sll_hatype = ARPHRD_ETHER;
#if 0
    24 #define PACKET_HOST     0       /* To us        */
         25 #define PACKET_BROADCAST    1       /* To all       */
          26 #define PACKET_MULTICAST    2       /* To group     */
           27 #define PACKET_OTHERHOST    3       /* To someone else  */
            28 #define PACKET_OUTGOING     4       /* Outgoing of any type */
             29 /* These ones are invisible by user level */

#endif
#if  0
             177 struct ifreq {
                 178 #define IFHWADDRLEN 6
                     179     union
                     180     {
                         181         char    ifrn_name[IFNAMSIZ];        /* if name, e.g. "en0" */
                         182     } ifr_ifrn;
                 183 
                     184     union {
                         185         struct  sockaddr ifru_addr;
                         186         struct  sockaddr ifru_dstaddr;
                         187         struct  sockaddr ifru_broadaddr;
                         188         struct  sockaddr ifru_netmask;
                         189         struct  sockaddr ifru_hwaddr;
                         190         short   ifru_flags;
                         191         int ifru_ivalue;
                         192         int ifru_mtu;
                         193         struct  ifmap ifru_map;
                         194         char    ifru_slave[IFNAMSIZ];   /* Just fits the size */
                         195         char    ifru_newname[IFNAMSIZ];
                         196         void *  ifru_data;
                         197         struct  if_settings ifru_settings;
                         198     } ifr_ifru;
                 199 };

#endif
    addr.sll_pkttype = PACKET_OTHERHOST;
    addr.sll_halen = ETH_ALEN; // 6 [0~5]
    addr.sll_addr[6] = 0; 
    addr.sll_addr[7] = 0;


    // 只是打印一下本机的硬件地址，跟此程序无关
    ret = ioctl(sock, SIOCGIFHWADDR, &ifstruct);
    if(ret < 0)
    {
        perror("get hwaddr");
        return 4;
    }
    struct sockaddr* hwaddr = &ifstruct.ifr_ifru.ifru_hwaddr;
    const unsigned char* p =(unsigned char*) hwaddr->sa_data;
    printf("hw addr is %02x:%02x:%02x:%02x:%02x:%02x\n", p[0], p[1], p[2], p[3], p[4], p[5]);

    // 获取模式
    ret = ioctl(sock, SIOCGIFFLAGS, &ifstruct);
    if(ret < 0)
    {
        perror("get flags");
        return 5;
    }
    // 加上混杂功能
    ifstruct.ifr_ifru.ifru_flags |= IFF_PROMISC;
    // 设置混杂模式
    ret = ioctl(sock, SIOCSIFFLAGS, &ifstruct);
    if(ret < 0)
    {
        perror("set IFF_PROMISC");
        return 6;
    }

    ret = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        return 3;
    }

    char buf[2048];
    while(1)
    {
        printf("reading eth frame ...\n");
        ret = recv(sock, buf, sizeof(buf), 0);
        if(ret < 0)
        {
            perror("recv");
            return 7;
        }
        printf("eth frame size: %d\n", ret);

        eth_frame* eth = (eth_frame*)buf;
//        dump_eth_frame(eth);

        // 如果不是ip报文，则不分析
        if(ntohs(eth->type) != 0x0800)
        {
            continue;
        }

        // 通过偏移获得ip的报文首地址，并强制转换
        ip_frame* ip = (ip_frame*)(buf + 14);
  //      dump_ip_frame(ip);

        if(ip->protocol != 6) // TCP
        {
            continue;
        }

        tcp_frame* tcp = (tcp_frame*)(buf + 14 + ip->head_len*4);
 //       printf("tcp head len=%d\n", tcp->head_len);
        unsigned short yyy = ntohs(tcp->xxx);

        unsigned int head_len = yyy & 0xf000; //1111000000000000
        head_len >>= 12;
        printf("tcp head is %d\n", head_len);

        unsigned char* data =(unsigned char*) (buf+14+ip->head_len*4 + head_len*4);
        printf("%s\n", (char*)data);

        if(tcp->src_port == ntohs(9999) && tcp->dst_port == ntohs(9998))
        {

         //   unsigned char* data = (buf + 14 + ip->head_len * 4 + tcp->head_len * 4);
         //   printf("");
        }

        printf("******************************************************\n");
        
    }

    return 0;
}



