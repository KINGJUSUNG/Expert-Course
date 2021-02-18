import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class MultiChatServer {
	private Map<String, PrintWriter> clients;
	private ServerSocket serverSocket;
	
	public MultiChatServer(int portNumber) throws Exception {
		this.serverSocket = new ServerSocket(portNumber);
		this.clients = new HashMap<>();
	}
	
	public void addClient(Socket clientSocket) throws IOException {		
		String host = clientSocket.getInetAddress().getHostName();
		PrintWriter writer = new PrintWriter(
								new BufferedWriter(
									new OutputStreamWriter(
										clientSocket.getOutputStream()), 1024));
		synchronized (clients) {
			this.clients.put(host, writer);
		}
	}
	
	public void forward(String host, String message) {
		synchronized (clients) {
			Set<Map.Entry<String, PrintWriter>> entrySet = clients.entrySet();
			for (Map.Entry<String, PrintWriter> entry : entrySet) {
				String sendMessage = host + "> " + message;
				entry.getValue().println(sendMessage);
				entry.getValue().flush();
			}
		}
	}
	
	public void remove(String host) {
		synchronized (clients) {
			this.clients.remove(host);
		}
	}
	
	class ClientThread extends Thread {
		private BufferedReader clientReader;
		private String host;
		
		public ClientThread(Socket clientSocket) throws Exception {
			this.host = clientSocket.getInetAddress().getHostName();
			this.clientReader = new BufferedReader(
									new InputStreamReader(
										clientSocket.getInputStream()), 1024);
			MultiChatServer.this.forward("채팅서버> ", this.host + "님이 채팅방에 입장하였습니다.");
			MultiChatServer.this.addClient(clientSocket);			
		}
		
		public void run() {
			while (true) {
				try {
					String recvMessage = this.clientReader.readLine();
					if (recvMessage == null) {
						break;
					}
					MultiChatServer.this.forward(this.host, recvMessage);
					if (recvMessage.trim().toLowerCase().equals("bye")) {
						break;
					}
				}
				catch (IOException e) {
					System.err.println("클라이언트와의 연결이 비정상적으로 종료되었습니다.");
				}
			}
			System.out.println("채팅서버> " + this.host + "가 채팅방에서 퇴장하였습니다.");
			MultiChatServer.this.remove(this.host);
		}
	}
	
	public void serverStart() {
		try {
			while (true) {
				Socket clientSocket = null;
				try {
					clientSocket = serverSocket.accept();
					Thread ct = new ClientThread(clientSocket);
					ct.start();
				}
				catch (Exception e) {
					e.printStackTrace();
					break;
				}
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		System.out.println("채팅서버를 종료하였습니다.");
	}
	
	public static void main(String[] args) {
		int portNumber = 0;
		
		if (args.length != 1) {
			System.err.println("잘못된 명령 행입니다.");
			System.err.println("사용법> java Receiver 포트번호");
			System.exit(1);
		}
		
		try {
			portNumber = Integer.parseInt(args[0]);
			if ((portNumber < 1) || (portNumber > 65535)) {
				System.err.println("포트번호의 범위가 잘못되었습니다.");
				System.err.println("지정가능한 포트번호 범위 [1 ~ 65535]입니다.");
				System.exit(2);
			}
		}
		catch (Exception e) {
			System.err.println(e.getMessage());
			System.exit(3);
		}
		
		MultiChatServer app = null;
		try {
			app = new MultiChatServer(portNumber);
			System.out.println("채팅서버가 " + portNumber + "포트로 구동되었습니다.");
			app.serverStart();
		}
		catch (Exception e) {
			System.err.println("서버 구동에 실패하였습니다.");
		}
	}
	
}
