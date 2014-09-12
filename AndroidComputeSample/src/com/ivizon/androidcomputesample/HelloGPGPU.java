package com.ivizon.androidcomputesample;

import  com.ivizon.androidcomputesample.NativeComputeLoad;
import android.support.v7.app.ActionBarActivity;
import android.graphics.Color;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;


public class HelloGPGPU extends ActionBarActivity {


    public void iv_init()
    {
    	final TextView openclDevice = (TextView)findViewById(R.id.opencl_device_info);
    	final Button button_run = (Button)findViewById(R.id.button_run);
    	button_run.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				String deviceName = NativeComputeLoad.getDeviceName();
				int num_compute_units = NativeComputeLoad.getComputeUnits();
				openclDevice.setTextColor(Color.RED);
				openclDevice.setText( deviceName + "\n" + 
									 "Num ComputeUnits : " + num_compute_units + "\n" +
									 "Global memory    : " + NativeComputeLoad.getGlobalMemory()/1024/1024 + "MB\n" +
									 "Local memory    : " + NativeComputeLoad.getLocalMemory() + "bytes");
				button_run.setEnabled(false);
			}
		});
    }
	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_hello_gpgpu);
        NativeComputeLoad.initBoostCompute();
        iv_init();
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.hello_gpgpu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
}
