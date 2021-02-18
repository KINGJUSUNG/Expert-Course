import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
	public static void main(String[] args) {
		ServerSocket sSock = null;
		BufferedReader in = null;
		
		try {
			sSock = new ServerSocket(9000);
			System.out.println("서버가 9000번 포트로 대기중입니다.");

			Socket cSock = sSock.accept();
			InetAddress cInet = cSock.getInetAddress();
			System.out.println(cInet.getHostName() + "가 접속하였습니다.");				
			in = new BufferedReader(new InputStreamReader(cSock.getInputStream()));

			while (true) {
				String str = in.readLine();
				System.out.println(str);
				if (str.toUpperCase().equals("BYE")) {
					break;
				}
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		finally {
			try { sSock.close(); } catch (Exception e) {}
		}
	}
}
