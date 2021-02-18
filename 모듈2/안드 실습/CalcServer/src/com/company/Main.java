package com.company;

import com.example.calcapp.ValueObject;
import com.sun.jdi.Value;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class Main {
    public static void main(String[] args) {
        Socket socket = null;
        ObjectOutputStream oos = null;
        ObjectInputStream ois = null;

        try {
            ServerSocket serverSocket = new ServerSocket(6666);
            System.out.println("[server] running...");

            socket = serverSocket.accept();
            System.out.println("[server] " + socket.getInetAddress().getHostAddress());

            oos = new ObjectOutputStream(socket.getOutputStream());
            ois = new ObjectInputStream(socket.getInputStream());
            ValueObject object = (ValueObject)ois.readObject();
            if (object == null) {
                System.out.println("수신 오류: null");
                return;
            }

            int op1 = object.getOp1();
            int op2 = object.getOp2();
            int opcode = object.getOpcode();
            switch (opcode) {
                case ValueObject.ADD:
                    oos.writeObject(op1 + " + " + op2 + " = " + (op1 + op2));
                    oos.flush();
                    break;
                case ValueObject.SUB:
                    oos.writeObject(op1 + " - " + op2 + " = " + (op1 - op2));
                    oos.flush();
                    break;
                case ValueObject.MUL:
                    oos.writeObject(op1 + " x " + op2 + " = " + (op1 * op2));
                    oos.flush();
                    break;
                case ValueObject.DIV:
                    oos.writeObject(op1 + " / " + op2 + " = " + (op1 / op2));
                    oos.flush();
                    break;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        finally {
            // 자원 정리를 해야 합니다.
        }
    }
}
