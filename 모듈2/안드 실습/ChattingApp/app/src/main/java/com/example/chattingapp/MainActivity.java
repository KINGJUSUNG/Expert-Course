package com.example.chattingapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;

public class MainActivity extends AppCompatActivity {
    private final static String TAG = "MainActivity";

    private final static String SERVER_ADDRESS = "192.168.30.7";
    private final static int PORT_NUMBER = 6666;

    private EditText mEmailEdit;
    private EditText mInputEdit;
    private TextView mChatTextView;

    private Socket mSocket;
    private BufferedReader mReader;
    private BufferedWriter mWriter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mEmailEdit = findViewById(R.id.emailEditText);
        mInputEdit = findViewById(R.id.messageEditText);
        mChatTextView = findViewById(R.id.chatTextView);

        Button connectButton = findViewById(R.id.connectButton);
        connectButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
               connectServer();
            }
        });

        Button sendButton = findViewById(R.id.sendButton);
        sendButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                final String message = mInputEdit.getText().toString();
                mInputEdit.setText(null);
                new Thread(new Runnable() {
                    @Override
                    public void run() { send(message) ; }
                }).start();
            }
        });
    }

    private void connectServer() {
        final String email = mEmailEdit.getText().toString();
        if (email.isEmpty()) {
            Toast.makeText(MainActivity.this,
                    "이메일을 입력하세요", Toast.LENGTH_LONG).show();
            return;
        }

        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    mSocket = new Socket(SERVER_ADDRESS, PORT_NUMBER);
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            Toast.makeText(MainActivity.this,
                                    "서버에 접속하였습니다.", Toast.LENGTH_LONG).show();
                        }
                    });

                    mWriter = new BufferedWriter(new OutputStreamWriter(mSocket.getOutputStream()));
                    mReader = new BufferedReader(new InputStreamReader(mSocket.getInputStream()));

                    mWriter.write(email + "\n");
                    mWriter.flush();

                    while (true) {
                        final String message = mReader.readLine();
                        if (message == null)
                            continue;

                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() { mChatTextView.append(message + "\n"); }
                        });
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }).start();
    }

    private void send(String data) {
        try {
            mWriter.write(data + "\n");
            mWriter.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}