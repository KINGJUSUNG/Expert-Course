import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;

public class Client {
	public static void main(String[] args) {
		Socket sock = null;
		PrintWriter sout = null;
		BufferedReader cin = null; 
		
		try {
			sock = new Socket("127.0.0.1", 9000);
			System.out.println("127.0.0.1 서버에 접속하였습니다.");
			sout = new PrintWriter(new BufferedWriter(new OutputStreamWriter(sock.getOutputStream())));
			cin = new BufferedReader(new InputStreamReader(System.in));
			while (true) {
				String str = cin.readLine();
				sout.println(str);
				sout.flush();
				if (str.toUpperCase().equals("BYE")) {
					break;
				}
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		finally {
			try { sock.close(); } catch (Exception e) {}
		} 
	}
}



