package com.example.calcapp;

import androidx.appcompat.app.AppCompatActivity;

import android.content.IntentFilter;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

public class MainActivity extends AppCompatActivity {
    private final static String TAG = "MainActivity";

    private final static String SERVER_ADDRESS = "192.168.30.7";
    private final static int PORT_NUMBER = 6666;

    private EditText mNumber1Edit;
    private EditText mNumber2Edit;
    private TextView mResultTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mNumber1Edit = findViewById(R.id.number1EditText);
        mNumber2Edit = findViewById(R.id.number2EditText);
        mResultTextView = findViewById(R.id.resultTextView);
    }

    public void onClickButton(View view) {
        String stringNumber1 = mNumber1Edit.getText().toString();
        String stringNumber2 = mNumber2Edit.getText().toString();
        if (stringNumber1.isEmpty() || stringNumber2.isEmpty())
            return;

        int number1 = Integer.parseInt(stringNumber1);
        int number2 = Integer.parseInt(stringNumber2);
        int opcode = 0;
        switch (view.getId()) {
            case R.id.addButton: opcode = ValueObject.ADD; break;
            case R.id.subButton: opcode = ValueObject.SUB; break;
            case R.id.mulButton: opcode = ValueObject.MUL; break;
            case R.id.divButton: opcode = ValueObject.DIV; break;
        }

        final ValueObject vo = new ValueObject(number1, number2, opcode);
        new Thread(new Runnable() {
            @Override
            public void run() {
                Socket socket = null;
                ObjectOutputStream oos = null;
                ObjectInputStream ois = null;

                try {
                    socket = new Socket(SERVER_ADDRESS, PORT_NUMBER);
                    oos = new ObjectOutputStream(socket.getOutputStream());
                    ois = new ObjectInputStream(socket.getInputStream());

                    oos.writeObject(vo);
                    oos.flush();

                    String result = (String)ois.readObject();
                    if (result == null) {
                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                Toast.makeText(MainActivity.this,
                                        "수신 오류: null", Toast.LENGTH_LONG).show();
                            }
                        });
                    }
                    mResultTextView.setText(result);
                } catch (Exception e) {
                    e.printStackTrace();
                }
                finally {
                    if (oos != null) try { oos.close(); } catch (Exception e) {}
                    if (ois != null) try { ois.close(); } catch (Exception e) {}
                    if (socket != null) try { socket.close(); } catch (Exception e) {}
                }
            }
        }).start();
    }
}