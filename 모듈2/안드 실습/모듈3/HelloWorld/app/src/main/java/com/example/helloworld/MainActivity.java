package com.example.helloworld;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // 앱에서 로그를 출력하려면 자바의 표준 출력 객체를 사용할 수 있습니다.
        // 단, 오래된 시스템에서는 동작하지 않습니다.
        // System.out.println("HelloWorld: MainActivity-onCreate()");

        // Log.d("MainActivity", "onCreate");

        Log.i(TAG, "onCreate()");   // 태그명은 보통 클래스 이름을 사용합니다.
        Log.d(TAG, "onCreate()");
        Log.v(TAG, "onCreate()");
        Log.w(TAG, "onCreate()");
        Log.e(TAG, "onCreate()");

        // 컨트롤러에서 뷰의 객체를 참조하는 방법
        // 1. 뷰 객체에 id를 설정합니다. android:id="@+id/사용하고자하는아이디"
        // 2. 컨트롤러에서 해당 아이디로 객체의 참조를 얻어옵니다.
        TextView textView = findViewById(R.id.byeTextView);
        textView.setText("hello, world");





    }
}