#ifndef _SERVER_H
#define _SERVER_H

#define HROBOT_TCP_MAX_DATA_LENGTH	4
typedef struct t_ctrl_frame {
	uint16_t cmd;		/* cmd code */
	uint16_t length;	/* the length of data after command */
} TCP_CTRL_FRAME;

#define HROBOT_TCP_CTRL_FRAME_SIZE	sizeof(TCP_CTRL_FRAME)
#endif
