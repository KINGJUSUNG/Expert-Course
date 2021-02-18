package com.company;

import java.io.*;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

public class Main {
    public static void main(String[] args) {
        ServerSocket serverSocket = null;
        Socket clientSocket = null;
        BufferedReader reader = null;
        BufferedWriter writer = null;
        try {
            serverSocket = new ServerSocket(6666);
            System.out.println("[server] running...");

            clientSocket = serverSocket.accept();
            InetAddress address = clientSocket.getInetAddress();
            int port = clientSocket.getPort();
            System.out.println(String.format("[server] %s:%d connected", address, port));

            OutputStream out = clientSocket.getOutputStream();
            InputStream in = clientSocket.getInputStream();

            reader = new BufferedReader(new InputStreamReader(in));
            writer = new BufferedWriter(new OutputStreamWriter(out));

            String line = reader.readLine();
            if (line != null) {
                System.out.println("from client: " + line);
                writer.write(line);
                writer.flush();
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        finally {
            if (reader != null) { try { reader.close(); } catch (Exception e) {} }
            if (writer != null) { try { writer.close(); } catch (Exception e) {} }
            if (clientSocket != null) { try { serverSocket.close(); } catch (Exception e) {} }
            if (serverSocket != null) { try { serverSocket.close(); } catch (Exception e) {} }
        }
    }
}
