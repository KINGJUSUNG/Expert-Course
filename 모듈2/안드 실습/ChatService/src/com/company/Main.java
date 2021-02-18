package com.company;

import jdk.jshell.spi.ExecutionControlProvider;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Iterator;

public class Main {
    public static void main(String[] args) throws IOException {
        new Main(6666).run();
    }

    private class Client {
        Socket socket;
        String email;   // ID
        BufferedWriter writer;
        BufferedReader reader;

        public Client(Socket socket) throws IOException {
            this.socket = socket;
            writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        }
    }

    private ArrayList<Client>  clients = new ArrayList<>();
    private Object lock = new Object();
    private ServerSocket serverSocket = null;

    public Main(int port) throws IOException {
        serverSocket = new ServerSocket(port);
    }

    public void run() {
        System.out.println("[server] running...");
        while (true) {
            try {
                Socket socket = serverSocket.accept();
                new ChatReceiver(socket).start();
            }
            catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    private class ChatReceiver extends Thread {
        Socket socket;

        public ChatReceiver(Socket socket) {
            this.socket = socket;
        }

        @Override
        public void run() {
            Client client = null;
            try {
                client = new Client(socket);
                client.email = client.reader.readLine(); // 사용자로부터 이메일 주소를 수신합니다.
                System.out.println(String.format("[server] %s:%d connected\n",
                        socket.getInetAddress().getHostAddress(), socket.getPort()));

                synchronized (lock) {
                    clients.add(client);
                }
                broadcast(client.email + " entered");

                String message = null;
                while (true) {
                    message = client.reader.readLine();
                    if (message == null || message.equals("bye"))
                        break;
                    broadcast(String.format("[%s] %s", client.email, message));
                }
            }
            catch (Exception e) {
                e.printStackTrace();
            }
            finally {
                synchronized (lock) { clients.remove(client); }
                broadcast(client.email + " left");

                if (client.reader != null) try { client.reader.close(); } catch (Exception e) {}
                if (client.writer != null) try { client.writer.close(); } catch (Exception e) {}
                if (client.socket != null) try { client.socket.close(); } catch (Exception e) {}
            }
        }
    }

    private synchronized void broadcast(String message) {
        Iterator<Client> itr = clients.iterator();
        while (itr.hasNext()) {
            Client client = itr.next();

            try {
                client.writer.write(message + "\n");
                client.writer.flush();
            }
            catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
