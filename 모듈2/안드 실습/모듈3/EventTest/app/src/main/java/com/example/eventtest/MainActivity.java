package com.example.eventtest;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    final static String TAG = "MainActivity";

    // 외부에서 이 콜백 메서드가 호출되어야 하므로 반드시
    // 접근 지정자는 public을 사용해야 하며 인자는 View 객체를 전달받도록
    // 정의해야 합니다.
    public void OnClickButton(View view) {
        Log.d(TAG, "button is clicked!");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button clickButton = findViewById(R.id.clickButton);
//        MyOnClickListener listener = new MyOnClickListener();
//        clickButton.setOnClickListener(listener);

        // clickButton.setOnClickListener(this);
//        View.OnClickListener listener = new View.OnClickListener() {
//            @Override
//            public void onClick(View view) {
//                Log.i(TAG, "Button is clicked!");
//            }
//        };
//        clickButton.setOnClickListener(listener);

        // 익명 임시 객체를 사용한 리스너 등록
//        clickButton.setOnClickListener(new View.OnClickListener(){
//            @Override
//            public void onClick(View view) {
//                Log.i(TAG, "Button is clicked!");
//            }
//        });

        // clickButton.setOnClickListener(view -> Log.d(TAG, "Button is clicked!"));
    }

    @Override
    public void onClick(View view) {
        Log.i(TAG, "Button is clicked!");
    }
}

class MyOnClickListener implements View.OnClickListener {
    @Override
    public void onClick(View view) {
        Log.i(MainActivity.TAG, "Button is clicked!");
    }
}