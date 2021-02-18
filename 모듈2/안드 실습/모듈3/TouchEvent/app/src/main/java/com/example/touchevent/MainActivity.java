package com.example.touchevent;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    final static String TAG = "MainActivity";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView textView = findViewById(R.id.textView);
        textView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                // Log.d(TAG, "Textview is touched!");

                // 사용자가 어떤 액션을 수행했는지를 추출합니다.
                int action = motionEvent.getAction();
                switch (action) {
                    case MotionEvent.ACTION_DOWN:
                        // 뷰를 눌렀을 때
                        Log.i(TAG, "DOWN");
                        break;
                    case MotionEvent.ACTION_MOVE:
                        // 뷰를 누른 상태로 이동했을 때
                        Log.i(TAG, "MOVE");
                        break;
                    case MotionEvent.ACTION_UP:
                        // 뷰로부터 떨어졌을 때
                        Log.i(TAG, "UP");
                        break;
                }
                return true;
            }
        });
    }
}