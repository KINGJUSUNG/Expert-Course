package com.example.volleytest;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;

public class MainActivity extends AppCompatActivity {
    private final static String TAG = "MainActivity";

    // Volley는 내부적으로 큐를 사용하는데 한 번 생성하면 재사용이 가능합니다.
    // 따라서 정적 객체로 생성합니다.
    private static RequestQueue requestQueue;
    private TextView mTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mTextView = findViewById(R.id.textView);

        if (requestQueue == null)
            requestQueue = Volley.newRequestQueue(getApplicationContext());

        // 특정 페이지를 요청하려면 StringRequest 객체를 사용하면 됩니다.
        StringRequest request = new StringRequest(Request.Method.GET, "https://www.google.com",
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        // 정상적으로 응답이 온 경우, 호출됩니다.
                        mTextView.setText(response);
                    }
                },
                new Response.ErrorListener() {
                    @Override
                    public void onErrorResponse(VolleyError error) {
                       // 오류가 발생될 경우, 호출됩니다.
                        mTextView.setText("오류: " + error.getMessage());
                    }
                }
        );

        request.setShouldCache(false);
        requestQueue.add(request);
    }
}