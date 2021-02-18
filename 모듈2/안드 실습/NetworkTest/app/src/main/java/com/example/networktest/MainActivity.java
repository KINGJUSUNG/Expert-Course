package com.example.networktest;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

public class MainActivity extends AppCompatActivity {
    private final static String TAG = "MainActivity";
    private final int PORT_NUMBER = 6666;

    private EditText mInputEdit;
    private TextView mServerLogTextView;
    private TextView mClientLogTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mInputEdit = findViewById(R.id.inputEditText);
        mServerLogTextView = findViewById(R.id.serverLogTextView);
        mClientLogTextView = findViewById(R.id.clientLogTextView);

        Button startButton = findViewById(R.id.startButton);
        startButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // 서버 구동 코드
                startServer();
            }
        });

        Button sendButton = findViewById(R.id.sendButton);
        sendButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
               // 메시지 전송 코드
                String messsage = mInputEdit.getText().toString();
                if (messsage.isEmpty())
                    return;
                send(messsage);
            }
        });
    }

    private void printClientLog(String message) {
        mServerLogTextView.setText(message + "\n");
    }

    private void send(String message) {
        Socket socket = null;
        ObjectOutputStream oos = null;
        ObjectInputStream ois = null;

        try {
            socket = new Socket("localhost", PORT_NUMBER);
            printClientLog("서버 접속됨");

            oos = new ObjectOutputStream(socket.getOutputStream());
            oos.writeObject(message);
            oos.flush();
            printClientLog("메시지 전송");

            ois = new ObjectInputStream(socket.getInputStream());
            printClientLog("수신 메시지: " + ois.readObject());
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        finally {
            try { if (oos != null) oos.close(); } catch (Exception e) {}
            try { if (ois != null) ois.close(); } catch (Exception e) {}
            try { if (socket != null) socket.close(); } catch (Exception e) {}
        }
    }

    private void printServerLog(String message) {
        mServerLogTextView.setText(message + "\n");
    }

    private void startServer() {
        ServerSocket server = null;
        ObjectInputStream ois = null;
        ObjectOutputStream oos = null;
        try {
            server = new ServerSocket(PORT_NUMBER);
            printServerLog("서버 시작됨");

            while (true) {
                Socket socket = server.accept();
                int port = socket.getPort();
                InetAddress address = socket.getLocalAddress();
                printServerLog(String.format("%s(%d) 연결됨", address.toString(), port));

                ois = new ObjectInputStream(socket.getInputStream());
                Object object = ois.readObject();
                printServerLog("수신된 데이터: " + object);

                oos = new ObjectOutputStream(socket.getOutputStream());
                oos.writeObject(object);
                oos.flush();
                printServerLog("데이터 보냄");
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        finally {
            try { if (oos != null) oos.close(); } catch (Exception e) {}
            try { if (ois != null) ois.close(); } catch (Exception e) {}
            try { if (server != null) server.close(); } catch (Exception e) {}
        }
    }
}