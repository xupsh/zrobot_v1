package org.hustcse.wifirobot;

import java.net.InetAddress;
import java.net.UnknownHostException;

import android.annotation.SuppressLint;
import android.content.Context;
import android.net.DhcpInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.Toast;

public class tcp_ctrl {
	final static boolean D = true;
	final static int SERVER = 1;
	final static int CLIENT = 2;
	private static String TAG = "TCP_CTRL";

	final static int MSG_DATA_REC = 1;
	final static int MSG_DISPLAY_TOAST = 100;
	final static int MSG_FIX_PREFERENCE = 1000;
	final static int FIX_IP_PREFERENCE = 0;

	ctrl_frame tcp_client_frame;

	tcp_ctrl_client mTcp_ctrl_client;

	Handler mHandler;
	Context mContext;

	public static int CLIENT_PORT = 1234;
	public static String CLIENT_IP = "192.168.0.200";

	public static String SERVER_IP = "127.0.0.1";

	InetAddress myBcastIPAddress; // my broadcast IP addresses
	InetAddress myIPAddress; // my IP addresses

	public tcp_ctrl(Context currentContext, Handler handler, String client_ip,
			int client_port) {
		mHandler = handler;
		mContext = currentContext;
		CLIENT_IP = client_ip;
		CLIENT_PORT = client_port;

		try {
			if (getMyWiFiBcastAndIPAddress()) {
				SERVER_IP = myIPAddress.getHostAddress();
			}
		} catch (Exception e) {
			disp_toast("Wifi Maybe Not Opened");
		}

		mTcp_ctrl_client = new tcp_ctrl_client(currentContext, mHandler_Client,
				CLIENT_IP, CLIENT_PORT);
		if (!mTcp_ctrl_client.isSocketOK()) {
			Log.e(TAG, "TCP Client NOT STARTED");
			return;
		} else {
			mTcp_ctrl_client.start();
		}
	}

	private void disp_toast(String msg) {
		Toast.makeText(mContext, msg, Toast.LENGTH_SHORT).show();
	}

	private final Handler mHandler_Client = new Handler() {
		@SuppressLint("HandlerLeak")
		@Override
		public void handleMessage(Message msg) {
			switch (msg.what) {
			case MSG_DATA_REC:
				if (D) {
					Log.d(TAG,"Message Received From TCP Client:"+ ctrl_prefixs.bytes2hexformatstring(((byte[]) msg.obj)));
				}
				break;
			case MSG_DISPLAY_TOAST:
				if (mHandler != null) {
					mHandler.obtainMessage(MSG_DISPLAY_TOAST, msg.obj)
							.sendToTarget();
				}
				break;
			case (MSG_FIX_PREFERENCE + FIX_IP_PREFERENCE):
				if (mHandler != null) {
					mHandler.obtainMessage(msg.what, msg.obj).sendToTarget();
				}
				break;
			default:
				break;
			}

			// handle_server_msg( ((byte[])msg.obj));
		}
	};


	private boolean getMyWiFiBcastAndIPAddress() throws UnknownHostException {
		if (D) {
			Log.d(TAG, "start get wifi status");
		}
		WifiManager mWifi = (WifiManager) (mContext
				.getSystemService(Context.WIFI_SERVICE));
		WifiInfo info = mWifi.getConnectionInfo();
		if (info == null) {
			if (D) {
				Log.e(TAG, "Cannot Get WiFi Info");
			}
			return false;
		} else {
			if (D) {
				Log.d(TAG, "\n\nWiFi Status: " + info.toString());
			}
		}

		/*
		 * DhcpInfo is a simple object for retrieving the results of a DHCP
		 * request
		 */
		DhcpInfo dhcp = mWifi.getDhcpInfo();
		if (dhcp == null) {
			Log.d(TAG, "Could not get dhcp info");
			return false;
		}

		int myIntegerIPAddress = dhcp.ipAddress;

		byte[] quads = new byte[4];
		for (int k = 0; k < 4; k++) {
			quads[k] = (byte) ((myIntegerIPAddress >> k * 8) & 0xFF);
		}
		myIPAddress = InetAddress.getByAddress(quads);

		int myIntBroadcast = (dhcp.ipAddress & dhcp.netmask) | ~dhcp.netmask;
		for (int k = 0; k < 4; k++) {
			quads[k] = (byte) ((myIntBroadcast >> k * 8) & 0xFF);
		}
		/* Returns the InetAddress corresponding to the array of bytes */
		myBcastIPAddress = InetAddress.getByAddress(quads);
		return true;

	}
}
