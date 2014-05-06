package org.hustcse.wifirobot;

import java.io.*;
import java.net.*;
import java.sql.Date;
import java.text.SimpleDateFormat;

import org.apache.http.HttpResponse;
import org.apache.http.HttpStatus;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;

import android.R.integer;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.Dialog;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.OnSharedPreferenceChangeListener;
import android.content.pm.ActivityInfo;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.Display;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.Surface;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.MobileAnarchy.Android.Widgets.Joystick.JoystickMovedListener;
import com.MobileAnarchy.Android.Widgets.Joystick.JoystickView;

public class WifiRobotActivity extends Activity {
	/* TAG for debug*/
	private static String TAG = "ZRobot";
	/* for debugging */
	final static boolean D = true;	
	
	/*video address*/
	private static String CAR_VIDEO_ADDR = "http://192.168.1.100:8080/?action=stream";
	private static String ARM_VIDEO_ADDR = "http://192.168.1.100:8090/?action=snapshot";
	private static String OPENCV_VIDEO_ADDR = "http://192.168.1.100/detection.jpg";
	
	/*mode slelect*/
	private static String MOTOR_CONTROL_MODE = "MOTOR_CONTROL_MODE";
	private static String SPEED_DETECT_MODE = "SPEED_DETECT_MODE";

	/* default dist ip addr and port*/
	private static String DIST_TCPIPADDR = "192.168.1.100";
	private static int DIST_TCPPORT = 2001;

	/* reference for setting */
	private SharedPreferences preferences;
	
	/* video stream */
	//DrawVideo m_DrawVideo;
	mjpeg_sreamer mjpg;

	/* local dist tcp addr and port*/
	private String dist_tcp_addr;
	private int dist_tcp_port;

	/*video information*/
	final static int MSG_VIDEO_UPDATE = 1;
	final static int MSG_VIDEO_ERROR = 2;
	final static int MSG_VIDEO_END = 3;

	
	final static int MSG_DISPLAY_TOAST = 100;
	final static int MSG_FIX_PREFERENCE = 1000;

	final static int FIX_IP_PREFERENCE = 0;

	/*progress for connect imagecap videocap */
	ProgressDialog mDialog_Connect, mDialog_ImageCap, mDialog_VideoCap;
	private static final int CONNECT_DIALOG_KEY = 0;
	private static final int IMGCAP_DIALOG_KEY = 1;
	private static final int VIDEOCAP_DIALOG_KEY = 2;

	/*buttons*/
	Button btn_image;
	Button btn_video_srcsel;
	Button btn_video;
	Button btn_follow_road_mode_ctrl;
	Button btn_set_camera2LCD;
	Button btn_control_mode;
	Button btn_connect;
	Button btn_laser_ctrl;

	ImageView img_camera;
	
	JoystickView joystick;
	JoystickView joystickArm;

	TextView txtAngle, txtSpeed, txtTCPState;

	/* the flag for auto control */
	private boolean auto_control_mode = false;	
	
	/* laser control flag */
	private final static int LASER_OFF = 0;
	private final static int LASER_ON = 1;
	private int laser_ctrl = LASER_OFF;


	/* video source select : car. arm. opencv**/	
	final static int MAX_VIDEO_SRC_CNT = 3;
	
	private int video_source_sel = 0;
	
	final static int CAR_VIDEO_SRC = 0;
	final static int ARM_VIDEO_SRC = 1;
	final static int OPENCV_VIDEO_SRC = 2;

	/* video source address array */
	private String[] video_addr = new String[MAX_VIDEO_SRC_CNT];
	/* current video address */
	private String cur_video_addr; 

	/* detect if the image and video is ready*/
	private boolean image_ready_flag = false;
	private boolean video_ready_flag = false;

	/* tcp control*/
	short tcp_ctrl_code;
	short tcp_data_length;
	byte[] tcp_ctrl_data = new byte[1024];
	
	//tcp connection obj for speed detection
	tcp_ctrl tcp_speed_obj;
	//tcp connection obj for motor control
	tcp_ctrl tcp_ctrl_obj;
	//.......................................

	/*bit map*/
	Bitmap img_camera_bmp;
	
	/*video flag
	 * false : to the video is not ready
	 * true: the video is ready*/
	boolean video_flag = false;

	int operate_angle_last = 0;
	int operate_speed_last = 0;
	int operate_angle = 0;
	int operate_speed = 0;

	/* max speed unit*/
	private final static int MAX_SPEED_UNIT = 10;
	private final static int SPEED_SCALE = 5;
	
	/* arm related */
	int arm_x_offset = 0;
	int arm_y_offset = 0;
	int arm_x_offset_last = 0;
	int arm_y_offset_last = 0;
	private final static int MAX_ARM_UNIT = 10;
	private final static int ARM_X_SCALE = 9;
	private final static int ARM_Y_SCALE = 9;

	/* curent context */
	private Context mContext;

	private static final int REQ_SYSTEM_SETTINGS = 0x0;

	/* screen parameters*/
	Display display;
	private int screen_Width = 0;
	private int screen_Height = 0;
	private int screen_Orientation = 0;
	
	/* the two joyview*/
	LayoutParams joyviewParams;
	LayoutParams joyviewParamsArm;

	/* joystick parameters*/
	private float joystick_scale = 3;
	
	private float btn_scale = 42;
	private float txtview_scale = 42;

	/*the time interval */
	private long start_time = 0;
	private long end_time = 0;

	private long benchmark_start = 0;
	private long benchmark_end = 0;

	/*  */
	private static int MAX_PASS = 40;
	private long[] time_pass = new long[MAX_PASS + 1];
	private String[] pass_log = new String[MAX_PASS + 1];

	private static int MAX_INFO_CNT = 40;
	private String[] SystemInfo = new String[MAX_INFO_CNT];
	private int SystemInfoCnt = 0;

	private int pass_cnt = 0;
	private String MYLOG_PATH_SD = "hrrobotlog";


	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		Log.i(TAG, "program startup");
		init_log_time();

		start_time = System.currentTimeMillis();
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		log_pass_time("Set ContentView OK");
		/* get the setting preference for update the setting information */
		preferences = PreferenceManager.getDefaultSharedPreferences(this);

		display = getWindowManager().getDefaultDisplay();
		screen_Orientation = display.getOrientation();
		if ((screen_Orientation == Surface.ROTATION_0)
				|| (screen_Orientation == Surface.ROTATION_180)) {
			screen_Width = display.getHeight();
			screen_Height = display.getWidth();
		} else {
			screen_Width = display.getWidth();
			screen_Height = display.getHeight();
		}

		Log.i(TAG, "Screen Resolution:" + screen_Height + " X " + screen_Width);
		log_pass_time("screen info ok");

		/* findview by id*/
		btn_video_srcsel = (Button) findViewById(R.id.button_video_src);
		btn_video = (Button) findViewById(R.id.button_video);
		btn_control_mode = (Button) findViewById(R.id.button_control);
		btn_connect = (Button) findViewById(R.id.button_connect);
		btn_laser_ctrl = (Button) findViewById(R.id.button_laser_ctrl);

		img_camera = (ImageView) findViewById(R.id.imageView_camera);

		/* car direction control joystick initialize */
		joystick = (JoystickView) findViewById(R.id.joystickView); 
		/* machine arm control joystick initialize */
		joystickArm = (JoystickView) findViewById(R.id.joystickARM); 

		txtAngle = (TextView) findViewById(R.id.TextViewX);
		txtSpeed = (TextView) findViewById(R.id.TextViewY);
		txtTCPState = (TextView) findViewById(R.id.TextViewTCPState);

		/* set the background to half alpha*/
		btn_video_srcsel.getBackground().setAlpha(100); 
		btn_video.getBackground().setAlpha(100); 
		btn_control_mode.getBackground().setAlpha(100);
		btn_connect.getBackground().setAlpha(100);
		btn_laser_ctrl.getBackground().setAlpha(100);

	
		
		/* set the text size to adaptor the screen*/
		btn_video_srcsel.setTextSize(screen_Width / btn_scale);
		btn_video.setTextSize(screen_Width / btn_scale);
		btn_control_mode.setTextSize(screen_Width / btn_scale);
		btn_connect.setTextSize(screen_Width / btn_scale);
		btn_laser_ctrl.setTextSize(screen_Width / btn_scale);

		/*textview setting*/
		((TextView) findViewById(R.id.TextViewAngle)).setTextSize(screen_Width
				/ txtview_scale);
		((TextView) findViewById(R.id.TextViewSpeed)).setTextSize(screen_Width
				/ txtview_scale);
		((TextView) findViewById(R.id.TextViewTCPStateTxt))
				.setTextSize(screen_Width / txtview_scale);
		txtAngle.setTextSize(screen_Width / txtview_scale);
		txtSpeed.setTextSize(screen_Width / txtview_scale);
		txtTCPState.setTextSize(screen_Width / txtview_scale);

		/* set the button Listener */
		btn_video_srcsel.setOnClickListener(video_src_acquire_listener);
		btn_video.setOnClickListener(video_acquire_listener);

		btn_control_mode.setOnClickListener(ctrl_btn_listener);
		btn_connect.setOnClickListener(connect_listener);
		btn_laser_ctrl.setOnClickListener(laser_ctrl_listener);

		log_pass_time("all objects init ok");

		update_preference();
		
		/* init the tcp control obj */
		tcp_ctrl_obj = new tcp_ctrl(getApplicationContext(),
				mHandler_UpdateUI, dist_tcp_addr, dist_tcp_port);
		tcp_speed_obj = new tcp_ctrl(getApplicationContext(), mHandler_UpdateUI, dist_tcp_addr, dist_tcp_port);
		log_pass_time("tcp ok");

		mContext = getApplicationContext();
		//if the tcp is connecting
		if (tcp_ctrl_obj.mTcp_ctrl_client.isSocketOK()
				&& tcp_speed_obj.mTcp_ctrl_client.isSocketOK()) {
			txtTCPState.setText(R.string.tcpstate_online);
		} else {
			txtTCPState.setText(R.string.tcpstate_offline);
		}
		
		/* adaptor the joyview to the screen*/
		joyviewParams = joystick.getLayoutParams();
		joyviewParams.width = (int) (screen_Width / joystick_scale);
		joyviewParams.height = (int) (screen_Width / joystick_scale);
		joystick.setLayoutParams(joyviewParams);
		/* set the joystick listener*/
		joystick.setOnJostickMovedListener(joystickctrl_listener);

		joyviewParams = joystickArm.getLayoutParams();
		joyviewParams.width = (int) (screen_Width / joystick_scale);
		joyviewParams.height = (int) (screen_Width / joystick_scale);
		joystickArm.setLayoutParams(joyviewParams);
		joystickArm.setOnJostickMovedListener(joystickarm_listener);

		log_pass_time("joystick ok");

		end_time = System.currentTimeMillis();

		Log.i(TAG, "app startup use " + (end_time - start_time) + " ms");
		log_pass_time("program started");
		end_log_time();
		log_system_info();
		write_log2file("hrrobotup", false);
	}

	@Override
	protected void onResume() {
		if(D)
			Log.e(TAG, "++on resume");
		if (getRequestedOrientation() != ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE) {
			setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
		}
		super.onResume();
	}

	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.menu, menu);
		return true;
	}

	/* update the setting*/
	public void update_preference() {
		int temp;
		try {
			video_addr[0] = preferences.getString(
					getResources().getString(R.string.videoaddr1),
					CAR_VIDEO_ADDR);
			video_addr[1] = preferences.getString(
					getResources().getString(R.string.videoaddr2),
					ARM_VIDEO_ADDR);
			video_addr[2] = preferences.getString(
					getResources().getString(R.string.videoaddr3),
					OPENCV_VIDEO_ADDR);
			dist_tcp_addr = preferences.getString(
					getResources().getString(R.string.distipaddr),
					DIST_TCPIPADDR);
			
			try {
				//check the TCP port 
				temp = Integer.parseInt((preferences.getString(getResources()
						.getString(R.string.disttcpport), String
						.valueOf(DIST_TCPPORT))));
				dist_tcp_port = temp;
			} catch (Exception e) {
				SharedPreferences.Editor editor = preferences.edit();
				editor.putString(
						getResources().getString(R.string.disttcpport),
						String.valueOf(dist_tcp_port));
				editor.commit();
			}
		} catch (Exception e) { 
			Log.d(TAG, e.toString());
		}
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		int ItemId; 
		
		ItemId = item.getItemId() ;
		
		switch (ItemId){
		case R.id.Settings:
			startActivityForResult(new Intent(this, Preferences.class),
					REQ_SYSTEM_SETTINGS);
			break;
		default:
			break;
		}
		return true;
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_BACK && event.getRepeatCount() == 0) {
			Log.d(TAG, "Program Exit!");
			System.exit(0);
		}
		return super.onKeyDown(keyCode, event);
	}

	/* connect button listener  */
	private OnClickListener connect_listener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			/*update the tcp address and port*/
			update_preference();
			showDialog(CONNECT_DIALOG_KEY);
		}
	};
	
	/* video src acquire button listener */
	private OnClickListener video_src_acquire_listener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			process_video_src_select(v.getId());
		}
	};

	private OnClickListener video_acquire_listener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			post_ctrl_btnclk_msg(v.getId());
		}
	};

	/* auto control button listener */
	private OnClickListener ctrl_btn_listener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			post_ctrl_btnclk_msg(v.getId());
		}
	};

	/*laser control button listener */
	private OnClickListener laser_ctrl_listener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			postLaserCtrlMsg(v.getId());
		}
	};
	
	private JoystickMovedListener joystickctrl_listener = new JoystickMovedListener() {
		@Override
		public void OnMoved(int pan, int tilt) {
			int operate_x = 0;
			int operate_y = 0;

			operate_x = pan;
			operate_y = -tilt;
			calc_speed_and_angle(operate_x, operate_y);
			txtAngle.setText(Integer.toString(operate_angle));
			txtSpeed.setText(Integer.toString(operate_speed));
			checkSendOperateCarMsg();
			Thread.yield(); 
		}

		@Override
		public void OnReleased() {
			txtAngle.setText("released");
			txtSpeed.setText("released");
			Thread.yield();
		}

		@Override
		public void OnReturnedToCenter() {
			txtAngle.setText("stopped");
			txtSpeed.setText("stopped");
			operate_angle = 0;
			operate_speed = 0;
			checkSendOperateCarMsg();
			Thread.yield();
		};
	};

	private JoystickMovedListener joystickarm_listener = new JoystickMovedListener() {
		@Override
		public void OnMoved(int pan, int tilt) {
			int operate_x = 0;
			int operate_y = 0;

			operate_x = pan;
			operate_y = -tilt;
			calc_arm_xy(operate_x, operate_y);

			checkSendOperateArmMsg();
			Thread.yield(); 
		}

		@Override
		public void OnReleased() {
			Thread.yield();
		}

		@Override
		public void OnReturnedToCenter() {
			arm_x_offset = 0;
			arm_y_offset = 0;
			checkSendOperateArmMsg();
			Thread.yield();
		};
	};

	/*** OPERATE CAR ***/
	/* post tcp msg*/
	private void postOperateCarMessage(int angle, int speed) {
		short ctrl_cmd;
		short ctrl_prefix;
		byte[] msg = new byte[4];

		ctrl_prefix = ctrl_prefixs.encode_ctrlprefix(
				ctrl_prefixs.write_request, ctrl_prefixs.less_data_request,
				ctrl_prefixs.withoutack);
		ctrl_cmd = ctrlcmds.OPERATE_CAR;
		msg[0] = (byte) (angle & 0xff);
		msg[1] = (byte) ((angle >> 8) & 0xff);
		msg[2] = (byte) (speed & 0xff);
		msg[3] = (byte) ((speed >> 8) & 0xff);

		post_tcp_msg(ctrl_prefix, ctrl_cmd, msg);
	}
	
	private void checkSendOperateCarMsg() {
		if (!((operate_angle == operate_angle_last) && (operate_speed == operate_speed_last))) {
			if ((tcp_ctrl_obj.mTcp_ctrl_client.isSocketOK())) { 
				postOperateCarMessage(operate_angle, operate_speed);
			}
			operate_angle_last = operate_angle;
			operate_speed_last = operate_speed;
		}
	}

	/*calculate the angle and speed*/
	private void calc_speed_and_angle(int operate_x, int operate_y) {
		operate_speed = (int) Math.sqrt((operate_x * operate_x)
				+ (operate_y * operate_y));

		if (operate_y < 0) {
			operate_speed = -operate_speed;
		}

		if (operate_x == 0) {
			if (operate_y == 0) {
				operate_angle = 0;
			} else if (operate_y > 0) {
				operate_angle = 90;
			} else {
				operate_angle = -90;
			}
		} else if (operate_y == 0) {
			if (operate_x == 0) {
				operate_angle = 0;
			} else if (operate_x > 0) {
				operate_angle = 0;
			} else {
				operate_angle = 180;
			}
		} else {
			operate_angle = (int) ((Math.atan2(operate_y, operate_x) / Math.PI) * 180);
		}

		if (operate_speed == 0) {
			operate_angle = 0;
		} else if (operate_speed > 0) {
			operate_angle = 90 - operate_angle;
		} else {
			operate_angle = operate_angle + 90;
		}

		if (operate_speed > MAX_SPEED_UNIT) {
			operate_speed = MAX_SPEED_UNIT;
		} else if (operate_speed < -MAX_SPEED_UNIT) {
			operate_speed = -MAX_SPEED_UNIT;
		}
		operate_speed = operate_speed * SPEED_SCALE;

	}



	/*** OPERATE_ARM ***/
	private void postOperateArmMessage(int x, int y) {
		short ctrl_cmd;
		short ctrl_prefix;
		byte[] msg = new byte[4];

		ctrl_prefix = ctrl_prefixs.encode_ctrlprefix(
				ctrl_prefixs.write_request, ctrl_prefixs.less_data_request,
				ctrl_prefixs.withoutack);
		ctrl_cmd = ctrlcmds.OPERATE_ARM;
		msg[0] = (byte) (x & 0xff);
		msg[1] = (byte) ((x >> 8) & 0xff);
		msg[2] = (byte) (y & 0xff);
		msg[3] = (byte) ((y >> 8) & 0xff);

		post_tcp_msg(ctrl_prefix, ctrl_cmd, msg);
	}
	
	private void checkSendOperateArmMsg() {
		if (!((arm_x_offset == arm_x_offset_last) && (arm_y_offset == arm_y_offset_last))) {
			if ((tcp_ctrl_obj.mTcp_ctrl_client.isSocketOK())) {
				postOperateArmMessage(arm_x_offset, arm_y_offset);
			}
			arm_x_offset_last = arm_x_offset;
			arm_y_offset_last = arm_y_offset;
		}
	}
	
	private void calc_arm_xy(int operate_x, int operate_y) {
		if (operate_x > MAX_ARM_UNIT) {
			operate_x = MAX_ARM_UNIT;
		} else if (operate_x < -MAX_ARM_UNIT) {
			operate_x = -MAX_ARM_UNIT;
		}

		if (operate_y > MAX_ARM_UNIT) {
			operate_y = MAX_ARM_UNIT;
		} else if (operate_y < -MAX_ARM_UNIT) {
			operate_y = -MAX_ARM_UNIT;
		}

		arm_x_offset = operate_x * ARM_X_SCALE;
		arm_y_offset = operate_y * ARM_Y_SCALE;
	}



	private final Handler mHandler_UpdateUI = new Handler() {
		@Override
		public void handleMessage(Message msg) {
			switch (msg.what) {
			case MSG_DISPLAY_TOAST:
				disp_toast((String) msg.obj);
				break;
			case (MSG_FIX_PREFERENCE + FIX_IP_PREFERENCE):
				String ip = (String) msg.obj;
				SharedPreferences.Editor editor = preferences.edit();
				editor.putString(getResources().getString(R.string.distipaddr),
						ip);
				editor.commit();
				break;
			default:
				break;
			}

		}
	};



	@Override
	protected Dialog onCreateDialog(int id) {
		switch (id) {
		case CONNECT_DIALOG_KEY:
			mDialog_Connect = new ProgressDialog(WifiRobotActivity.this);
			mDialog_Connect.setMessage("Trying to connect to TCP server...");
			mDialog_Connect.setCancelable(false);
			return mDialog_Connect;
		case IMGCAP_DIALOG_KEY:
			mDialog_ImageCap = new ProgressDialog(WifiRobotActivity.this);
			mDialog_ImageCap.setMessage("Trying to obtain image ...");
			mDialog_ImageCap.setCancelable(false);
			return mDialog_ImageCap;
		case VIDEOCAP_DIALOG_KEY:
			mDialog_VideoCap = new ProgressDialog(WifiRobotActivity.this);
			mDialog_VideoCap.setMessage("Trying to obtain video ...");
			mDialog_VideoCap.setCancelable(false);
			return mDialog_VideoCap;
		default:
			return null;
		}
	}



	@Override
	protected void onPrepareDialog(int id, Dialog dialog) {
		switch (id) {
		case CONNECT_DIALOG_KEY:
			ConnectProgressThread mConnectProgressThread = new ConnectProgressThread(
					progress_handler);
			mConnectProgressThread.start();
			break;
		case IMGCAP_DIALOG_KEY:
			ImageCapProgressThread mCapProgressThread = new ImageCapProgressThread(
					progress_handler, IMGCAP_DIALOG_KEY);
			mCapProgressThread.start();
			break;
		case VIDEOCAP_DIALOG_KEY:
			ImageCapProgressThread mCapProgressThread2 = new ImageCapProgressThread(
					progress_handler, VIDEOCAP_DIALOG_KEY);
			mCapProgressThread2.start();
			break;
		default:
			break;
		}

	}

	final Handler progress_handler = new Handler() {
		@Override
		public void handleMessage(Message msg) {
			if (msg.what <= VIDEOCAP_DIALOG_KEY) {
				dismissDialog(msg.what);
			}

			switch (msg.what) {
			case CONNECT_DIALOG_KEY:
				if (msg.obj != null) {
					disp_toast((String) msg.obj);
				}
				if (tcp_ctrl_obj.mTcp_ctrl_client.isSocketOK()) {
					txtTCPState.setText(R.string.tcpstate_online);
				} else {
					txtTCPState.setText(R.string.tcpstate_offline);
				}
				break;
			case IMGCAP_DIALOG_KEY:
				image_ready_flag = (Boolean) (msg.obj);
				if (image_ready_flag == true) {
					img_camera.setImageBitmap(img_camera_bmp);
				} else {
					disp_toast("Get remote image failed,please check the video address!");
				}
				break;
			case VIDEOCAP_DIALOG_KEY:
				video_ready_flag = (Boolean) (msg.obj);
				if (video_ready_flag == true) {
					img_camera.setImageBitmap(img_camera_bmp);
					mjpg = new mjpeg_sreamer(cur_video_addr, mHandler_video_process);
					mjpg.start();
					//m_DrawVideo = new DrawVideo(cur_video_addr,
					//		mHandler_video_process);
					//m_DrawVideo.start();
					btn_video.setText(R.string.button_video_stop);
					video_flag = true;
				} else {
					disp_toast("Get remote video failed,please check the video address!");
				}
				break;
			case MSG_DISPLAY_TOAST:
				break;

			default:
				break;
			}
		}
	};

	/* tcp connection thread */
	private class ConnectProgressThread extends Thread {
		Handler mHandler;
		String msg = null;

		ConnectProgressThread(Handler h) {
			mHandler = h;
		}

		@Override
		public void run() {
			if (tcp_ctrl_obj.mTcp_ctrl_client.updateIPandPort(dist_tcp_addr,
					dist_tcp_port)
					|| (tcp_ctrl_obj.mTcp_ctrl_client.isSocketOK() == false)) {
				tcp_ctrl_obj.mTcp_ctrl_client.tcp_connect(true);
				tcp_ctrl_obj.mTcp_ctrl_client.post_msg(new String(MOTOR_CONTROL_MODE).getBytes());
			} else {
				msg = new String("Already Connected to TCP Server @"
						+ dist_tcp_addr + ":" + dist_tcp_port);
			}
			mHandler.obtainMessage(CONNECT_DIALOG_KEY, msg).sendToTarget();
		}
	}

	/* image capture thread */
	private class ImageCapProgressThread extends Thread {
		Handler mHandler;
		boolean image_ok = false;
		int dialog_key;

		ImageCapProgressThread(Handler h, int id) {
			mHandler = h;
			dialog_key = id;
		}

		@Override
		public void run() {
			image_ok = get_remote_image(cur_video_addr);
			mHandler.obtainMessage(dialog_key, image_ok).sendToTarget();
		}
	}


	/*** LASER_CTRL ***/
	private void postLaserCtrlMsg(int btn_id) {
		short ctrl_cmd;
		short ctrl_prefix;
		byte[] msg = new byte[1];
		Button btn;

		ctrl_prefix = ctrl_prefixs.encode_ctrlprefix(
				ctrl_prefixs.write_request, ctrl_prefixs.less_data_request,
				ctrl_prefixs.withoutack);
		ctrl_cmd = ctrlcmds.LASER_CTRL;

		btn = (Button) findViewById(btn_id);

		if (laser_ctrl == LASER_OFF) {
			btn.setText(R.string.button_laser_off);
			laser_ctrl = LASER_ON;
		} else {
			btn.setText(R.string.button_laser_on);
			laser_ctrl = LASER_OFF;
		}

		msg[0] = (byte) (laser_ctrl & 0xff);

		Log.d(TAG, "Switch Laser Ctrl " + " to  " + laser_ctrl);
		post_tcp_msg(ctrl_prefix, ctrl_cmd, msg);
	}


	/*** ADJUST_VIDEO_MODE ***/
	private void postSwitchVideoModeMsg(int videomode) {
		short ctrl_cmd;
		short ctrl_prefix;
		byte[] msg = new byte[1];

		ctrl_prefix = ctrl_prefixs.encode_ctrlprefix(
				ctrl_prefixs.write_request, ctrl_prefixs.less_data_request,
				ctrl_prefixs.withoutack);
		ctrl_cmd = ctrlcmds.ADJUST_VIDEO_MODE;
		msg[0] = (byte) (videomode & 0xff);

		Log.d(TAG, "Switch Video Mode " + " to  " + videomode);
		post_tcp_msg(ctrl_prefix, ctrl_cmd, msg);
	}


	private void checkSendSwitchVideoModeMsg(int videomode) {
		if (tcp_ctrl_obj.mTcp_ctrl_client.isSocketOK()) { 
			postSwitchVideoModeMsg(videomode);
		}
	}

	private void process_video_src_select(int btn_id) {
		Button btn;
		String toast_str;

		switch (btn_id) {
		case R.id.button_video_src:
			update_preference();
			btn = (Button) findViewById(R.id.button_video_src);
			video_source_sel += 1;
			if (video_source_sel >= MAX_VIDEO_SRC_CNT) {
				video_source_sel = 0;
			}
			cur_video_addr = video_addr[video_source_sel]; 
			toast_str = new String(" Address : " + cur_video_addr);
			switch (video_source_sel) {
			case CAR_VIDEO_SRC:
				btn.setText(R.string.button_video_src_car);
				toast_str = "Switch to car video ," + toast_str;
				break;
			case ARM_VIDEO_SRC:
				btn.setText(R.string.button_video_src_arm);
				toast_str = "Switch to arm video ," + toast_str;
				break;
			case OPENCV_VIDEO_SRC:
				btn.setText(R.string.button_video_src_opencv);
				toast_str = "Switch to openCV video ," + toast_str;
				break;
			}
			checkSendSwitchVideoModeMsg(video_source_sel);

			// disp_toast(toast_str);
			if (video_flag == true) {
				if (mjpg != null) {
					mjpg.exit_thread();
				}
				btn_video.setText(R.string.button_video_start);
				img_camera.setImageResource(R.drawable.zynq_logo);
				video_flag = false;
				showDialog(VIDEOCAP_DIALOG_KEY);
			}

			break;
		default:
			return;
		}

	}

	/*** 
	 * ENTER_REAL_CONTROL_MODE
	 * ENTER_AUTO_NAV_MODE 
	 * IMAGE AND VIDEO
	 * ***/
	private void post_ctrl_btnclk_msg(int btn_id) {
		short ctrl_cmd = 0;
		short ctrl_prefix = 0;
		byte[] msg = null;
		Button btn;
		
		ctrl_prefix = ctrl_prefixs.encode_ctrlprefix(
				ctrl_prefixs.write_request, ctrl_prefixs.less_data_request,
				ctrl_prefixs.withoutack);
		switch (btn_id) {
		case R.id.button_image:
			update_preference();
			showDialog(IMGCAP_DIALOG_KEY);
			return; /* no break, direct return */

		case R.id.button_video:
			btn = (Button) findViewById(R.id.button_video);
			update_preference();
			if (video_flag == false) {
				cur_video_addr = video_addr[video_source_sel]; 
				showDialog(VIDEOCAP_DIALOG_KEY);
			} else {
				if (mjpg != null) {
					mjpg.exit_thread();
					// m_DrawVideo.stop();
				}
				btn.setText(R.string.button_video_start);
				img_camera.setImageResource(R.drawable.zynq_logo);
				video_flag = false;
			}
			return; /* no break, direct return */
			
			/*** 
			 * ENTER_REAL_CONTROL_MODE
			 * ENTER_AUTO_NAV_MODE 
			 * ***/
		case R.id.button_control:
			if (auto_control_mode == false) {
				ctrl_cmd = (ctrlcmds.ENTER_AUTO_NAV_MODE);
				btn_control_mode.setText(R.string.button_realcontrol);
				auto_control_mode = true;
			} else {
				ctrl_cmd = (ctrlcmds.ENTER_REAL_CONTROL_MODE);
				btn_control_mode.setText(R.string.button_autocontrol);
				auto_control_mode = false;
			}
			break;

		default:
			return;
		}
		post_tcp_msg(ctrl_prefix, ctrl_cmd, msg);
	}

	/*get a remote image for testint the http server*/
	public boolean get_remote_image(String url_addr) {
		boolean flag = false;

		String m_video_addr = CAR_VIDEO_ADDR;
		HttpURLConnection m_video_conn = null;
		InputStream m_InputStream = null;
		HttpGet httpRequest;
		HttpClient httpclient = null;
		HttpResponse httpResponse;

		try {
			m_video_addr = url_addr;
			Log.d(TAG, "start get url");
			httpRequest = new HttpGet(m_video_addr);

			Log.d(TAG, "open connection");
			httpclient = new DefaultHttpClient();

			Log.d(TAG, "begin connect");
			httpResponse = httpclient.execute(httpRequest);
			Log.d(TAG, "get InputStream");
			if (httpResponse.getStatusLine().getStatusCode() == HttpStatus.SC_OK) {
				Log.d(TAG, "decodeStream");
				m_InputStream = httpResponse.getEntity().getContent();
				img_camera_bmp = BitmapFactory.decodeStream(m_InputStream);
			}
			Log.d(TAG, "decodeStream end");

			flag = true;
		} catch (Exception e) {
			Log.e(TAG, "Error In Get Image Msg:" + e.getMessage());
			flag = false;
		} finally {
			if (m_video_conn != null) {
				m_video_conn.disconnect();
			}
			if ((httpclient != null)
					&& (httpclient.getConnectionManager() != null)) {
				httpclient.getConnectionManager().shutdown(); 
			}
		}

		return flag;
	}
	
	/*send the tcp msg to socket*/
	private void post_tcp_msg(short ctrl_prefix, short ctrl_cmd, byte[] msg) {
		ctrl_frame mCtrl_frame = new ctrl_frame(ctrl_prefix, ctrl_cmd, msg);
		byte[] tcp_msg = new byte[4 + mCtrl_frame.datalength];
		mCtrl_frame.encode_frametobytes(tcp_msg);
		tcp_ctrl_obj.mTcp_ctrl_client.post_msg(tcp_msg);
		if (D) {
			Log.d(TAG, "The Sent TCP Message is As Follows:");
			mCtrl_frame.display_ctrl_frame();
		}
	}
	
	private void disp_toast(String msg) {
		Toast.makeText(mContext, msg, Toast.LENGTH_SHORT).show();
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		switch (requestCode) {
		case REQ_SYSTEM_SETTINGS:
			systemsettingchange(resultCode, data);
			break;

		default:
			break;
		}
		super.onActivityResult(requestCode, resultCode, data);
	}

	private boolean systemsettingchange(int resultCode, Intent data) {
		boolean ifSucess = true;

		if (resultCode == RESULT_OK) {

		} else {
			Log.i(TAG, "None settings change");
		}
		return ifSucess;
	}

		/* NO USE */
	private OnSharedPreferenceChangeListener sys_set_chg_listener = new OnSharedPreferenceChangeListener() {

		@Override
		public void onSharedPreferenceChanged(
				SharedPreferences sharedPreferences, String key) {
			if (key == getResources().getString(R.string.videoaddr1)) {
				video_addr[0] = preferences.getString(key, CAR_VIDEO_ADDR);
			} else if (key == getResources().getString(R.string.videoaddr2)) {
				video_addr[1] = preferences.getString(key, ARM_VIDEO_ADDR);
			} else if (key == getResources().getString(R.string.videoaddr3)) {
				video_addr[2] = preferences.getString(key, OPENCV_VIDEO_ADDR);
			} else if ((key == getResources().getString(R.string.distipaddr))
					|| (key == getResources().getString(R.string.disttcpport))) {
				dist_tcp_addr = preferences.getString(
						getResources().getString(R.string.distipaddr),
						DIST_TCPIPADDR);
				dist_tcp_port = Integer.parseInt((preferences.getString(
						getResources().getString(R.string.disttcpport),
						String.valueOf(DIST_TCPPORT)))); 
				tcp_ctrl_obj.mTcp_ctrl_client.tcpreconnect(dist_tcp_addr,
						dist_tcp_port);
			}
		}
	};



	/**************USER LOG FUNCTIONS DEFINITION START**************/
	public void log_pass_time(String Tag) {
		long pass_time;

		benchmark_end = System.currentTimeMillis();
		if (true) {
			if (pass_cnt > MAX_PASS) {
				return;
			} else {
				pass_time = benchmark_end - benchmark_start;
				time_pass[pass_cnt] = pass_time;
				pass_log[pass_cnt] = "PASS " + pass_cnt + " : " + Tag + ":"
						+ "costs " + pass_time + "ms";
				pass_cnt++;
			}
		}
		benchmark_start = System.currentTimeMillis();
	}

	public void init_log_time() {
		benchmark_start = System.currentTimeMillis();
		benchmark_end = System.currentTimeMillis();
		start_time = System.currentTimeMillis();
		end_time = System.currentTimeMillis();
	}
	public void end_log_time() {
		end_time = System.currentTimeMillis();

		if (true) {
			if (pass_cnt > (MAX_PASS + 1)) {
				return;
			} else {
				long pass_time = end_time - start_time;
				time_pass[pass_cnt] = pass_time;
				pass_log[pass_cnt] = "Program Startup Costs " + pass_time
						+ "ms";
				pass_cnt++;
			}
		}
	}

	public void log_system_info() {
		String ScreenInfo = "Screen Resolution:" + screen_Height + " X "
				+ screen_Width;
		String CpuInfo = "";
		String VersionInfo = "";

		CpuInfo = readfile2str("/proc/cpuinfo");
		VersionInfo = readfile2str("proc/version");

		SystemInfo[0] = CpuInfo;
		SystemInfo[1] = VersionInfo;
		SystemInfo[2] = ScreenInfo;
		SystemInfo[3] = getphoneinfo();

		SystemInfoCnt = 4;
	}

	public String getphoneinfo() {
		String phoneInfo = "Product: " + android.os.Build.PRODUCT;
		phoneInfo += "\n CPU_ABI: " + android.os.Build.CPU_ABI;
		phoneInfo += "\n TAGS: " + android.os.Build.TAGS;
		phoneInfo += "\n VERSION_CODES.BASE: "
				+ android.os.Build.VERSION_CODES.BASE;
		phoneInfo += "\n MODEL: " + android.os.Build.MODEL;
		phoneInfo += "\n SDK: " + android.os.Build.VERSION.SDK;
		phoneInfo += "\n VERSION.RELEASE: " + android.os.Build.VERSION.RELEASE;
		phoneInfo += "\n DEVICE: " + android.os.Build.DEVICE;
		phoneInfo += "\n DISPLAY: " + android.os.Build.DISPLAY;
		phoneInfo += "\n BRAND: " + android.os.Build.BRAND;
		phoneInfo += "\n BOARD: " + android.os.Build.BOARD;
		phoneInfo += "\n FINGERPRINT: " + android.os.Build.FINGERPRINT;
		phoneInfo += "\n ID: " + android.os.Build.ID;
		phoneInfo += "\n MANUFACTURER: " + android.os.Build.MANUFACTURER;
		phoneInfo += "\n USER: " + android.os.Build.USER;

		return phoneInfo;
	}

	public String readfile2str(String file_path) {
		String res = "";

		File file = new File(file_path);
		if (file.exists()) {
			try {
				String temp;
				FileReader fileReader = new FileReader(file);
				BufferedReader bufferedReader = new BufferedReader(fileReader);
				while (((temp = bufferedReader.readLine()) != null)) {
					res = res + "\n" + temp;
				}
				fileReader.close();
				bufferedReader.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		return res;
	}

	public void write_log2file(String log_file_name, boolean need_sd_log) {
		update_preference();
		if (need_sd_log) {
			SimpleDateFormat formatter = new SimpleDateFormat(
					"yyyy-MM-dd HH_mm_ss");
			Date curDate = new Date(System.currentTimeMillis());
			String log_file_date = formatter.format(curDate);
			String full_log_filename = log_file_name + "_" + log_file_date
					+ ".txt";
			String log_file_path = "";

			String sd_status = Environment.getExternalStorageState();
			if (!(sd_status.equals(Environment.MEDIA_MOUNTED))) {
				log_file_path = "/mnt/flash" + File.separator + MYLOG_PATH_SD;
			} else {
				log_file_path = Environment.getExternalStorageDirectory()
						+ File.separator + MYLOG_PATH_SD;
			}
			File log_file_Dir = new File(log_file_path);
			File log_file = new File(log_file_path, full_log_filename);
			try { 
				if (!log_file_Dir.exists()) {
					if (!log_file_Dir.mkdir()) {
						return;
					} else {
						if (!log_file.exists()) {
							log_file.createNewFile(); 
						}
					}
				}
				FileWriter filerWriter = new FileWriter(log_file, true);
				BufferedWriter bufWriter = new BufferedWriter(filerWriter);
				for (int cnt = 0; cnt < pass_cnt; cnt++) {
					bufWriter.write(pass_log[cnt]);
					bufWriter.newLine();
				}
				bufWriter.newLine();

				for (int cnt = 0; cnt < SystemInfoCnt; cnt++) {
					bufWriter.write(SystemInfo[cnt]);
					bufWriter.newLine();
				}
				bufWriter.close();
				filerWriter.close();
			} catch (Exception e) {
				Log.e(TAG, "Write Log File Failed! " + e.getMessage());
			}
		}
	}
	
	/**************USER LOG FUNCTIONS DEFINITION END**************/


	@SuppressLint("HandlerLeak")
	private final Handler mHandler_video_process = new Handler() {
		@Override
		public void handleMessage(Message msg) {
			switch (msg.what) {
			case MSG_VIDEO_UPDATE:
				img_camera.setImageBitmap(img_camera_bmp);
				break;
			case MSG_VIDEO_ERROR:
				((Button) findViewById(R.id.button_video))
						.setText(R.string.button_video_start);
				disp_toast("Getting remote video failed,please check the video address!");
				img_camera.setImageResource(R.drawable.zynq_logo);
				break;
			case MSG_VIDEO_END:
				((Button) findViewById(R.id.button_video))
						.setText(R.string.button_video_start);
				img_camera.setImageResource(R.drawable.zynq_logo);
				break;
			default:
				break;
			}
		}
	};
	/*
	class DrawVideo extends Thread {
		private String m_video_addr = CAR_VIDEO_ADDR;
		private Handler video_Handler;
		private HttpURLConnection m_video_conn;
		HttpGet httpRequest;
		HttpClient httpclient = null;
		HttpResponse httpResponse;
		Bitmap bmp = null;
		private boolean exit_flag = false;

		public DrawVideo(String url_addr, Handler handler) {
			m_video_addr = url_addr;
			video_Handler = handler;
		}
		public void exit_thread() {
			exit_flag = true;
		}
		@Override
		public void run() {
			try {
				httpRequest = new HttpGet(m_video_addr);
				httpclient = new DefaultHttpClient();
				while (!exit_flag) {
					httpResponse = httpclient.execute(httpRequest);
					if (httpResponse.getStatusLine().getStatusCode() == 200) {
						MjpegInputStream jStream = new MjpegInputStream( httpResponse.getEntity().getContent());
						img_camera_bmp = BitmapFactory.decodeByteArray(jStream.readMjpegFrame(),0, jStream.mContentLength);
					}
					if (img_camera_bmp != null) {
						video_Handler.obtainMessage(MSG_VIDEO_UPDATE)
								.sendToTarget();
					}
					sleep(5);
				}
				exit_flag = false;
			} catch (Exception e) {
				video_flag = false;
				Log.e(TAG, "Error In Get Video Msg:" + e.getMessage());
				video_Handler.obtainMessage(MSG_VIDEO_ERROR).sendToTarget();
			} finally {
				if (m_video_conn != null) {
					m_video_conn.disconnect();
				}
				if ((httpclient != null)
						&& (httpclient.getConnectionManager() != null)) {
					httpclient.getConnectionManager().shutdown(); 
				}
				video_Handler.obtainMessage(MSG_VIDEO_END).sendToTarget();
			}
		}
	}*/
	class mjpeg_sreamer extends Thread{
		
		private String m_video_addr = CAR_VIDEO_ADDR;
		private Handler video_Handler;
		
		private String server_ip="192.168.1.100";
		private int server_port = 8080;
		
		private Socket socket;
		private InputStream inputStream;
		private OutputStream outputStream;
		private PrintWriter out;
		private MjpegInputStream jStream;
		
		Bitmap bitmap;
		private boolean exit;
		
		public mjpeg_sreamer(String video_addr,Handler handler){
			m_video_addr = video_addr;
			video_Handler = handler;
		}
		
		public void exit_thread()
		{
			exit = true;
		}
		
		@Override
		public void run()
		{	
			try {
				//create socket connection
				socket = new Socket(server_ip, server_port);
				inputStream = socket.getInputStream();
				outputStream = socket.getOutputStream();
				//send http get requestCode
				out = new PrintWriter(outputStream);
				out.print("GET /?action=stream\r\n\r\n");
				out.flush();
				//wait for the http header response
				byte[] http_head = new byte[1024];
				inputStream.read(http_head);
				String header = new String(http_head);
				if(header.contains("200 OK"))
				{
					exit = false;
				}
				else {
					exit = true;
				}
				//http ok, get the frame now
				jStream = new MjpegInputStream(inputStream);
				while(!exit){
					img_camera_bmp = BitmapFactory.decodeByteArray(jStream.readMjpegFrame(), //the byte[]
							0,  //start
							jStream.mContentLength);//end
					if (img_camera_bmp != null) {
						video_Handler.obtainMessage(MSG_VIDEO_UPDATE)
								.sendToTarget();
					}
					sleep(10); //sleep 10 ms
				}
			} catch(UnknownHostException e){
				Log.e(TAG, "unkonw host");
				video_Handler.obtainMessage(MSG_VIDEO_ERROR).sendToTarget();
				return;
			}catch (IOException e) {
				// TODO: handle exception
				Log.e(TAG, "socket error:" + e.getMessage());
				video_Handler.obtainMessage(MSG_VIDEO_ERROR).sendToTarget();
				return;
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				Log.e(TAG, "sleep error:" + e.getMessage());
			}
			finally{//close socket				
				try {
					if(socket != null)
						socket.close();
					if(jStream != null)
						jStream.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				video_flag = false;
				video_Handler.obtainMessage(MSG_VIDEO_END).sendToTarget();
			}
		}
	}
}
