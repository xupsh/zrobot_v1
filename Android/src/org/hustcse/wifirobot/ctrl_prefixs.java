package org.hustcse.wifirobot;

public class ctrl_prefixs { /*主要是对帧的控制位进行补充说明的一些前缀*/
	public static final  short ctrl_prefix_mask = 0xf;
	public static final  short ctrl_prefix_offset = 12;
	
	public static final  short withoutack = 0;
	public static final  short withack = 1;
	public static final  short ack_offset = 3;
	public static final  short ack_mask = (1 << ack_offset);
	
	public static final  short write_request = 0;
	public static final  short read_request = 1;
	public static final  short operate_offset = 2;
	public static final  short operate_mask = (1 << operate_offset);

	public static final  short less_data_request = 0;
	public static final  short mass_data_request = 1;
	public static final  short data_request_offset = 0;
	public static final  short data_request_mask = (1 << data_request_offset);

	public static final  short ctrl_mask = 0xfff;
	public static final  short ctrl_offset = 0;

		
	public static short make_ctrl_code(short ctrl, short ctrlprefix){
  		 return (short) ( ( (ctrl & (ctrl_mask)) << ctrl_offset) | 
    			( (ctrlprefix & ctrl_prefix_mask) << ctrl_prefix_offset) );
    }

	public static short encode_ctrlprefix(short operate, short data_request, short ack){
		short ctrlprefix;
		
		ctrlprefix = (short) ( ((operate << (operate_offset) ) & operate_mask ) |
				((ack << (ack_offset)) & ack_mask ) |
				((data_request << (data_request_offset)) & data_request_mask ) );
		
		return ctrlprefix;
	}
	
	public static  String bytes2hexformatstring(byte[] msg){
		String hexString = "";
		/*refer: http://developer.android.com/reference/java/util/Formatter.html*/
		for (int i = 0; i < msg.length; i++){
			hexString = hexString.concat(String.format("%1$#x ", msg[i]));
		}
		return hexString;
	}
}
