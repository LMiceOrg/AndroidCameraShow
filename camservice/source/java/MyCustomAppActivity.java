package cn.edu.tsinghua.rtlab.camphoto;

import cn.edu.tsinghua.rtlab.camphoto.R;
import cn.edu.tsinghua.rtlab.camphoto.MyCustomAppService;

import org.qtproject.qt5.android.bindings.QtActivity;
import org.qtproject.qt5.android.bindings.QtService;

import android.content.Intent;
import android.util.Log;
import android.os.Bundle;

public class MyCustomAppActivity extends QtActivity {
    @Override
    public void onCreate(Bundle bundle) {
        super.onCreate(bundle);
        Log.i("Activity", "hehao says: Starting service!");
        Intent serviceIntent = new Intent(this, cn.edu.tsinghua.rtlab.camphoto.MyCustomAppService.class);
        startService(serviceIntent);
    }
    @Override
    protected void onResume() {
        super.onResume();
    }
    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
    }
    @Override
    public void onPause() {
        super.onPause();
    }
    @Override
    public void onDestroy() {
        Log.i("Activity", "hehao says: onDestroy service!");
        super.onDestroy();
    }
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
    }
}
