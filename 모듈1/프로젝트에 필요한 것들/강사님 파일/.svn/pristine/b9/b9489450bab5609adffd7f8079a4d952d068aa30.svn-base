import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;

public class ObjectOutput {
	public static void main(String[] args) {
		ObjectOutputStream out = null;
		
		try {
			out = new ObjectOutputStream(
					new BufferedOutputStream(
						new FileOutputStream("C:/temp/data.dat")));
			out.writeObject(new Box(10, 10));
			out.writeObject(new Box(15, 8));
			out.writeObject(new Box(13, 12));
			out.flush();
			System.out.println("객체 내보내기가 완료되었습니다.");
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		finally {
			try { out.close(); } catch (Exception e) {}
		}
	}
}
