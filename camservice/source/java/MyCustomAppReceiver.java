package cn.edu.tsinghua.rtlab.camphoto;

import cn.edu.tsinghua.rtlab.camphoto.R;
import cn.edu.tsinghua.rtlab.camphoto.MyCustomAppService;

import android.app.Service;
import android.os.IBinder;
import android.content.BroadcastReceiver;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import org.qtproject.qt5.android.bindings.QtActivity;
import org.qtproject.qt5.android.bindings.QtService;

import android.content.Context;

public class MyCustomAppReceiver extends BroadcastReceiver
{

    static final String ACTION = "android.intent.action.BOOT_COMPLETED";

    @Override
    public void onReceive(Context context, Intent intent)
    {
        if (intent.getAction().equals(ACTION))
        {
            Intent i = new Intent(context,
                                  cn.edu.tsinghua.rtlab.camphoto.MyCustomAppService.class);
            context.startService(i);


        }
    }
}

