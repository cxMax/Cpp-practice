package com.cxmax.nativebitmapfactory;

import android.graphics.Bitmap;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("NativeBitmapFactory");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = (TextView) findViewById(R.id.sample_text);
    }

    private static native boolean init();

    private static native boolean release();

    private static native Bitmap createBitmap(int width, int height, int nativeConfig, boolean hasAlpha);

    private static native Bitmap createBitmap19(int width, int height, int nativeConfig, boolean hasAlpha);

}
