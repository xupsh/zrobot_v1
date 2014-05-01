package org.hustcse.wifirobot;

import android.util.Log;

public class ctrl_frame {
	String TAG = "Ctrl Frame";
	boolean D = true;
	int max_datasize = 1024;			/* 鏈�ぇ鐨勬暟鎹噺 */
	short ctrl_prefix_ack;						/* 鏄惁闇�ACK搴旂瓟 */
	short ctrl_prefix_operate;		/* 鎺у埗鍛戒护鍓嶇紑锛�鍛戒护鎿嶄綔绫诲瀷锛�璇�鍐�*/
	short ctrl_prefix_request;		/* 鎺у埗鍛戒护鍓嶇紑锛�鍛戒护鎿嶄綔璇锋眰鏁版嵁(濡傛灉鏈�鐨勯噺鐨勫ぇ灏� 澶ч噺鏁版嵁璇锋眰/灏戦噺鏁版嵁璇锋眰	*/
	short ctrl_prefix;				/* 鎺у埗鍛戒护鐨勫墠缂�紝涓昏鏄帶鍒跺懡浠ょ殑绫诲瀷璇存槑 */
	short ctrl_cmd;					/* 鎺у埗鍛戒护锛�杩欎釜鏄敤浜庤〃绀哄綋鍓嶇殑鍛戒护鐨勭紪鐮�*/
	short ctrlcode;					/* 鎺у埗瀛楋細鍖呭惈鎺у埗鍓嶇紑鍜屾帶鍒跺瓧 */
	short datalength;				/* 鏁版嵁闀垮害 */
	byte[] data = new byte[max_datasize];	/* 鍖呭惈鐨勬暟鎹�*/
	boolean show_data = false;

	private boolean available = false;				/* 鎺у埗甯ф槸鍚﹀彲鐢�*/

		
	/* 鏋勯�鍑芥暟 榛樿鍒濆鍖栧叏閮ㄤ负0 */
	public ctrl_frame (){
		this.construct_frame((short)0xff,  (short)0xffffff,  null);
		this.display_ctrl_frame();
	}
	
	/* 鏋勯�鍑芥暟 浼犲叆鍙傛暟涓烘帶鍒跺墠缂�鎺у埗鍛戒护 鏁版嵁(闇�鍙戦�鐨勬暟鎹� */
	public ctrl_frame (short ctrl_prefix, short ctrl_cmd, byte[] msg){
		this.construct_frame(ctrl_prefix,  ctrl_cmd,  msg);
		this.display_ctrl_frame();
		this.available = true;
	}
	
	/* 鏋勯�鍑芥暟 閲嶈浇 杩欐鏄彲浠ユ洿鏀�log鏃舵樉绀虹殑TAG */
	public ctrl_frame (short ctrl_prefix, short ctrl_cmd, byte[] msg, String DEBUG_TAG){
		this.TAG = DEBUG_TAG;
		this.construct_frame(ctrl_prefix,  ctrl_cmd,  msg);
		this.display_ctrl_frame();
		this.available = true;
	}
	
	/* 鍦↙OG涓樉绀哄抚鐨勮缁嗕俊鎭�*/
	public boolean display_ctrl_frame (){
		if(D && this.available) {
			Log.i(TAG, "------The Ctrl Frame Display Start-----");	
			Log.i(TAG, "Ctrl Prefix: " +  String.format("%1$#4x", ctrl_prefix));
			Log.i(TAG, "Ctrl Command: " +  String.format("%1$#4x", ctrl_cmd));
			Log.i(TAG, "Data Length: " +  String.format("%1$d", datalength));
			if (datalength > 0){
				if ((show_data == true) || (datalength < 10)){ /*鍗佷釜鏁版嵁浠ュ唴灏辫繘琛屾樉绀�*/
					String hexstring = "";
					for (short i = 0; i < datalength; i++){
						hexstring = hexstring.concat(String.format(" %1$#4x", data[i])) ;
					}
					Log.i(TAG, "Data Packets: " +  hexstring);
				}else{
					Log.i(TAG, "Data Packets is too big, or no need to show it!");
				}
			}else{
				Log.i(TAG, "No Data Packets!");
			}
			Log.i(TAG, "------The Ctrl Frame Display End-----");	
		}
		return this.available;
	}
	
	/* 瀵熺湅褰撳墠甯ф槸鍚﹀彲鐢�*/
	public boolean available(){
		return this.available;
	}
	
	public  boolean encode_frametobytes(byte[] msg){
		int tmp2 = 0;
		
		if (msg == null){
			return false;
		}
		if (this.available){
			tmp2 = (ctrlcode << 16) + datalength;
			msg[0] = (byte) ((tmp2 >> 24) & 0xff);
			msg[1] = (byte) ((tmp2 >> 16) & 0xff);
			msg[2] = (byte) ((tmp2 >> 8) & 0xff);
			msg[3] = (byte) ((tmp2 >> 0) & 0xff);
		
			if (datalength > 0){
				System.arraycopy(data, 0, msg, 4, datalength);
			}
		}

		return this.available;
	}
	
	/* 灏嗕紶鍏ョ殑瀛楄妭鏁扮粍杞寲涓轰竴甯ф暟鎹紝鎴愬姛鐨勮瘽杩斿洖true锛屽け璐ヨ繑鍥瀎alse */
	public boolean decode_framefrombytes(byte[] msg){
		boolean ercd;
		if (msg == null){
			ercd = false;
		}else{
			if (msg.length >= 4){
				this.ctrl_prefix = (short) ( (msg[0] >> 4) );
				this.ctrl_cmd = (short) ( ( (msg[0] & 0xf) << 8) + msg[1]);
				decode_ctrlprefix();
				encode_ctrlcode();
				if (this.datalength > 0){
					System.arraycopy(data, 0, msg, 4, this.datalength);
				}
				Log.i(TAG, "Construct A new Frame From bytes Input Success!");	
				ercd = true;
				available = true;
			}else{
				Log.e(TAG, "Construct A new Frame From bytes Input Failed!Input Bytes is not enough,only " + msg.length);	
				ercd = false;
			}
		}
		return ercd;
	}
	
	/* 鏍规嵁浼犲叆鍙傛暟鏋勯�涓�抚 */
	private void construct_frame(short ctrl_prefix, short ctrl_cmd, byte[] msg){
		this.ctrl_prefix = (short) (ctrl_prefix & ctrl_prefixs.ctrl_prefix_mask);
		this.ctrl_cmd = (short) (ctrl_cmd & ctrl_prefixs.ctrl_mask);
		decode_ctrlprefix();
		encode_ctrlcode();
		if (msg == null){
			this.datalength =  (short) 0;
		}else{
			//this.datalength =  (short) Math.min((short) msg.length, this.max_datasize);
			this.datalength =  (short) msg.length;
			if (this.datalength > this.max_datasize){
				this.datalength = (short) this.max_datasize;
			}
		}
		if (this.datalength > 0) { /* 杩涜鏁版嵁鎷疯礉*/
			System.arraycopy(msg, 0, this.data, 0, this.datalength);
		}
	}
	
	/* 灏嗘帶鍒跺墠缂�В鏋愪负鏇村皬鐨勫崟浣�*/
	private void decode_ctrlprefix(){
		this.ctrl_prefix_operate = (short) ( ( (this.ctrl_prefix & (ctrl_prefixs.operate_mask)) 
				>> (ctrl_prefixs.operate_offset)) );
		this.ctrl_prefix_request = (short) ( (this.ctrl_prefix & (ctrl_prefixs.data_request_mask)) 
				>> (ctrl_prefixs.data_request_offset) );
		this.ctrl_prefix_ack = (short) ( (this.ctrl_prefix & (ctrl_prefixs.ack_mask) ) 
				>> (ctrl_prefixs.ack_offset));
	}
	/* 灏嗘帶鍒跺墠缂�拰鎺у埗鍛戒护鏁村悎涓烘帶鍒跺瓧 */
	private void encode_ctrlcode(){
		this.ctrlcode = (short) ( (this.ctrl_prefix << ctrl_prefixs.ctrl_prefix_offset) | this.ctrl_cmd );
	}
	
}
