#pragma once

typedef struct ip_hdr
{
	unsigned char ip_ver : 4; // 4bit:IPv4버전
	unsigned char ip_hdrLength : 4; // 4bit:헤더 길이
	unsigned char ip_tos; // IP TOS
	unsigned char ip_totalLength; // 전체 길이
	unsigned char ip_id; // ID
	unsigned short ip_offset; //3bit:flags(x, Do Not Fragment, More Fragment), 13bit:Fragment offset
	unsigned char ip_ttl; // TTL
	unsigned char ip_protocol; // 프로토콜(TCP, UDP, etc)
	unsigned short ip_checksum; // IP checksum
	unsigned int ip_srcAddr; // source address
	unsigned int ip_destAddr; // destination address
}IPV4_HDR, *PIPV4_HDR;

// TCP 헤더
typedef struct tcp_hdr
{
	unsigned short src_port; // source port
	unsigned short dest_port; // dest port
	unsigned int seq_no; // sequence number
	unsigned int ack_no; // acknowlegement number
	unsigned short hdr_len : 4; // header length
	unsigned short reserved : 6; // 예약
	unsigned short tcp_urg : 1; // Urgent항목의 포인터가 유효함
	unsigned short tcp_ack : 1; // 확인 응답 번호가 유효함
	unsigned short tcp_psh : 1; // 해당 세그먼트의 데이터는 애플리케이션에게 즉시 전달되어야 함
	unsigned short tcp_rst : 1; // 연결을 재설정하거나 유효하지 않은 세그먼트에 대한 응답으로 사용됨
	unsigned short tcp_syn : 1; // 연결 설정 요구를 나타내며 반드시 승인되어져야 함
	unsigned short tcp_fin : 1; // 한쪽 끝에 유발되는 연결의 종료와 일정 방향으로의 데이터 흐름의 끝을 나타냄
	unsigned short win_size; // windows size
	unsigned short tcp_checksum; // checksum;
	unsigned short urg_ptr; // urgent pointer
							// `option max 40byte
}TCP_HDR, *PTCP_HDR;

// UDP 헤더
typedef struct udp_hdr
{
	unsigned short src_port; // source port number
	unsigned short dest_port; // dest port Number
	unsigned short udp_length; // UDP 패킷의 길이
	unsigned short udp_checksum; // UDP checksum(option)
}UDP_HDR, *PUDP_HDR;
