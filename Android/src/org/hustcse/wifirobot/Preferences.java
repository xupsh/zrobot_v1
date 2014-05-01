package org.hustcse.wifirobot;

import android.os.Bundle;
import android.preference.Preference;
import android.preference.Preference.OnPreferenceChangeListener;
import android.preference.PreferenceActivity;
import android.util.Log;

public class Preferences extends PreferenceActivity implements OnPreferenceChangeListener{
	private static String TAG = "PreferenceZRobot";

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
	    super.onCreate(savedInstanceState);
	    addPreferencesFromResource(R.xml.preference);
	}

	@Override
	public boolean onPreferenceChange(Preference preference, Object newValue) {
		Log.v(TAG, "preference is changed:" + preference.getKey());  
		Log.v(TAG, preference.getKey() + newValue.toString());  

 		return false;
	}
	
}
