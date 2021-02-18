import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

class Receiver extends Thread {
	private BufferedReader in;
	
	public Receiver(BufferedReader in) {
		this.in = in;
	}
	
	public void run() {
		while (true) {
			try {
				String recvMessage = in.readLine();
				System.out.println(recvMessage);
				try {
					Thread.sleep(1);
				}
				catch (InterruptedException e) {
					break;
				}
			}
			catch (IOException e) {
				System.err.println("서버와의 연결이 종료되었습니다.");
				break;
			}
		}
		System.out.println("메시지 수신 스레드를 종료하였습니다.");
	}
}

public class ChatClient {
	public static void main(String[] args) {
		if (!(args.length == 1 || args.length == 2)) {
			System.err.println("잘못된 명령행입니다.");
			System.err.println("사용법> java Sender [서버주소] 포트번호");
			System.exit(1);
		}
		
		int portNumber = 0;
		int posPort = 0;
		InetAddress ia = InetAddress.getLoopbackAddress();
		
		if (args.length == 2) {
			try {
				ia = InetAddress.getByName(args[0]);
			}
			catch (UnknownHostException e) {
				System.err.println(args[0] + "호스트를 찾을 수 없습니다.");
				System.exit(2);
			}
			posPort++;
		}
		
		try {
			portNumber = Integer.parseInt(args[posPort]);
			if (portNumber < 1 || portNumber > 65535) {
				System.err.println("잘못된 포트번호입니다.");
				System.err.println("지정가능한 포트번호는 [1 ~ 65535]입니다.");
				System.exit(4);
			}
		}
		catch (NumberFormatException e) {
			System.err.println("잘못된 포트번호입니다.");
			System.exit(3);
		}
		
		Socket socket = null;
		PrintWriter socketWriter = null;
		BufferedReader consoleReader = null;
		Thread receiveThread = null;
		
		try {
			socket = new Socket(ia, portNumber);
			System.out.println(ia.getHostName() + " 채팅서버에 접속하였습니다.");
			consoleReader = new BufferedReader(new InputStreamReader(System.in), 1024);
			socketWriter = new PrintWriter(
							new BufferedWriter(
								new OutputStreamWriter(
									socket.getOutputStream()), 1024));
			receiveThread = new Receiver(
								new BufferedReader(
									new InputStreamReader(
										socket.getInputStream()), 1024));
			receiveThread.start();
			
			while (true) {
				String sendMessage = consoleReader.readLine();
				socketWriter.println(sendMessage);
				socketWriter.flush();
				if (sendMessage.trim().toLowerCase().equals("bye")) {
					break;
				}
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		finally {
			receiveThread.interrupt();
			try { socket.close(); } catch (Exception e) {}
		}
		System.out.println("프로그램을 종료합니다.");
	}
}














