

#ifndef CTRLPREFIX_H_
#define CTRLPREFIX_H_

//#include <t_stddef.h>

#define CTRL_PREFIX_OFFSET							(12)
#define CTRL_PREFIX_MASK							(0xf)

#define CTRL_CMD_OFFSET								(0)
#define CTRL_CMD_MASK								(0xfff)

#define ACK_OFFSET									(3)
#define WITHOUT_ACK									(0 << ACK_OFFSET)
#define WITH_ACK									(1 << ACK_OFFSET)

#define	 OP_OFFSET									(2)
#define WRITE_OP									(0 << OP_OFFSET)
#define READ_OP										(1 << OP_OFFSET)

#define DATA_REQUEST_OFFSET							(0)
#define TCP_DATA									(0 << DATA_REQUEST_OFFSET)
#define UDP_DATA									(1 << DATA_REQUEST_OFFSET)

#define SHIFT_CODE(value, mask, offset)				( ((value) & (mask)) << (offset) )

#define MAKE_CTRL_PREFIX(ack, operate, request)		((ack) | (operate) | (request))

#define MAKE_CTRL_CODE(ctrlprefix, ctrlcmd)			((uint16_t)(SHIFT_CODE(ctrlprefix, CTRL_PREFIX_MASK, CTRL_PREFIX_OFFSET) | \
													SHIFT_CODE(ctrlcmd, CTRL_CMD_MASK, CTRL_CMD_OFFSET) ))

#define GET_ACK(ctrlcode)							(((ctrlcode) >> CTRL_PREFIX_OFFSET) & (1 << ACK_OFFSET))
#define GET_OP(ctrlcode)							(((ctrlcode) >> CTRL_PREFIX_OFFSET) & (1 << OP_OFFSET))
#define GET_DATA_REQUSET(ctrlcode)					(((ctrlcode) >> CTRL_PREFIX_OFFSET) & (1 << DATA_REQUEST_OFFSET))
#define GET_CMD(ctrlcode)							(((ctrlcode) >> CTRL_CMD_OFFSET) & (CTRL_CMD_MASK))

#endif /* CTRLPREFIX_H_ */
