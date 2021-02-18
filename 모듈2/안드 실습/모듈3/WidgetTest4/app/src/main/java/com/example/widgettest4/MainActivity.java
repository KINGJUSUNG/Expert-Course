package com.example.widgettest4;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {
    final static String TAG = "MainActivity";
    EditText mInputEditText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mInputEditText = findViewById(R.id.inputEditText);
    }

    public void onButtonClick(View view) {
        String inputString = mInputEditText.getText().toString();
        if (!inputString.isEmpty())
            Log.i(TAG, inputString);
    }
}