#pragma once

typedef struct ip_hdr
{
	unsigned char ip_ver : 4; // 4bit:IPv4����
	unsigned char ip_hdrLength : 4; // 4bit:��� ����
	unsigned char ip_tos; // IP TOS
	unsigned char ip_totalLength; // ��ü ����
	unsigned char ip_id; // ID
	unsigned short ip_offset; //3bit:flags(x, Do Not Fragment, More Fragment), 13bit:Fragment offset
	unsigned char ip_ttl; // TTL
	unsigned char ip_protocol; // ��������(TCP, UDP, etc)
	unsigned short ip_checksum; // IP checksum
	unsigned int ip_srcAddr; // source address
	unsigned int ip_destAddr; // destination address
}IPV4_HDR, *PIPV4_HDR;

// TCP ���
typedef struct tcp_hdr
{
	unsigned short src_port; // source port
	unsigned short dest_port; // dest port
	unsigned int seq_no; // sequence number
	unsigned int ack_no; // acknowlegement number
	unsigned short hdr_len : 4; // header length
	unsigned short reserved : 6; // ����
	unsigned short tcp_urg : 1; // Urgent�׸��� �����Ͱ� ��ȿ��
	unsigned short tcp_ack : 1; // Ȯ�� ���� ��ȣ�� ��ȿ��
	unsigned short tcp_psh : 1; // �ش� ���׸�Ʈ�� �����ʹ� ���ø����̼ǿ��� ��� ���޵Ǿ�� ��
	unsigned short tcp_rst : 1; // ������ �缳���ϰų� ��ȿ���� ���� ���׸�Ʈ�� ���� �������� ����
	unsigned short tcp_syn : 1; // ���� ���� �䱸�� ��Ÿ���� �ݵ�� ���εǾ����� ��
	unsigned short tcp_fin : 1; // ���� ���� ���ߵǴ� ������ ����� ���� ���������� ������ �帧�� ���� ��Ÿ��
	unsigned short win_size; // windows size
	unsigned short tcp_checksum; // checksum;
	unsigned short urg_ptr; // urgent pointer
							// `option max 40byte
}TCP_HDR, *PTCP_HDR;

// UDP ���
typedef struct udp_hdr
{
	unsigned short src_port; // source port number
	unsigned short dest_port; // dest port Number
	unsigned short udp_length; // UDP ��Ŷ�� ����
	unsigned short udp_checksum; // UDP checksum(option)
}UDP_HDR, *PUDP_HDR;
