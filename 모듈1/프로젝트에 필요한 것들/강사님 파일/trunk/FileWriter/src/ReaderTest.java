import java.io.BufferedReader;
import java.io.FileReader;
import java.util.StringTokenizer;

public class ReaderTest {
	public static void main(String[] args) {
		BufferedReader in = null;
		
		try {
			in = new BufferedReader(new FileReader("C:/temp/data.txt"), 1024);
			while (true) {
				String line = in.readLine();
				if (line == null) {
					break;
				}
				StringTokenizer tokens = new StringTokenizer(line, ":");
				try {
					if (tokens.countTokens() != 2) {
						throw new Exception();
					}
					else {
						String name = tokens.nextToken();
						int age = Integer.parseInt(tokens.nextToken());
						System.out.println("이름 : " + name + ", 연령 : " + age);
					}
				}
				catch (NumberFormatException e) {
					System.out.println("데이터 변환중에 문제가 발생하였습니다.");
				}
				catch (Exception e) {
					System.out.println("데이터에 문제가 발생하였습니다.");
				}
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		finally {
			try { in.close(); } catch (Exception e) {}
		}
	}
}
