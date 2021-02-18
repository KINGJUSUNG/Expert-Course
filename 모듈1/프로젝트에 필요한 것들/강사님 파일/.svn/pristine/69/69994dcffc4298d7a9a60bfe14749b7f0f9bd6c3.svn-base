import java.io.BufferedInputStream;
import java.io.EOFException;
import java.io.FileInputStream;
import java.io.ObjectInputStream;

public class ObjectIn {
	public static void main(String[] args) {
		ObjectInputStream in = null;
		
		try {
			in = new ObjectInputStream(new BufferedInputStream(new FileInputStream("C:/temp/data.dat")));
			while (true) {
				try {
					Object obj = in.readObject();
					if (!(obj instanceof Box)) {
						throw new Exception();
					}
					Box box = (Box)obj;
					System.out.println(box);
				}
				catch (EOFException e) {
					break;
				}
				catch (Exception e) {
					System.out.println("해당 객체는 Box타입이 아닙니다.");
				}
			}
			System.out.println("모든 객체를 읽어들였습니다.");
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		finally {
			try { in.close(); } catch (Exception e) {}
		}
	}
}
