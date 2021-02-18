package com.example.networktest2;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStreamWriter;
import java.net.Socket;

public class MainActivity extends AppCompatActivity {
    private final static String TAG = "MainActivity";
    private final static int PORT_NUMBER = 6666;

    private EditText mInputEdit;
    private TextView mClientLogTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mInputEdit = findViewById(R.id.inputEditText);
        mClientLogTextView = findViewById(R.id.clientLogTextView);
        Button sendButton = findViewById(R.id.sendButton);
        sendButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // 메시지 전송 코드
                final String message = mInputEdit.getText().toString();
                if (message.isEmpty())
                    return;

                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        send(message);
                    }
                }).start();
            }
        });
    }

    private void printClientLog(final String message) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                mClientLogTextView.append(message + "\n");
            }
        });
    }

    private void send(String message) {
        Socket socket = null;
        BufferedReader reader = null;
        BufferedWriter writer = null;

        try {
            // 서버의 주소는 노트북 운영체제에 할당된 아이피 주소를 입력해야 합니다.
            socket = new Socket("192.168.30.7", PORT_NUMBER);
            printClientLog("서버 접속됨");

           reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
           writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));

            writer.write(message+ "\n");
            writer.flush();
            printClientLog("데이터 전송함");

            String s = reader.readLine();
            if (s == null) {
                Log.i(TAG, "수신된 메시지 없음");
                return;
            }
            printClientLog(s);
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        finally {
            try { if (reader != null) reader.close(); } catch (Exception e) {}
            try { if (writer != null) writer.close(); } catch (Exception e) {}
            try { if (socket != null) socket.close(); } catch (Exception e) {}
        }
    }
}