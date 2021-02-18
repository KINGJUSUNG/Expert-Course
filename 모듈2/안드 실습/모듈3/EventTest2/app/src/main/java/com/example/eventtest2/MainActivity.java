package com.example.eventtest2;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.LinearLayout;

public class MainActivity extends AppCompatActivity {

    public void OnClickButton(View view) {
        LinearLayout layout = findViewById(R.id.layout);
        switch (view.getId()) {
            case R.id.redButton:  layout.setBackgroundColor(Color.RED); break;
            case R.id.greenButton:  layout.setBackgroundColor(Color.GREEN); break;
        }
    }

    @Override

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
}