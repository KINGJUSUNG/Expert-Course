import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class AppStart {
	public static void main(String[] args) {
		Connection con = null;
		PreparedStatement pstmt = null;
		String url = "jdbc:mariadb://localhost:3306/example?user=example&password=1234";
		
		try {
			Class.forName("org.mariadb.jdbc.Driver");
			con = DriverManager.getConnection(url);
			pstmt = con.prepareStatement("INSERT INTO members VALUES (?, ?, ?, MD5(?));");
			pstmt.setString(1, "wonchang");
			pstmt.setString(2, "¹Ú¿øÃ¢");
			pstmt.setString(3, "Mr Park");
			pstmt.setString(4, "1234");			
			int result = pstmt.executeUpdate();
			System.out.println("result : " + result);
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		finally {
			try { pstmt.close(); } catch (Exception e) {}
			try { con.close(); } catch (Exception e) {}
		}
		
	}
}
