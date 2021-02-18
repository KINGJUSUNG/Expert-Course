import java.sql.Connection;
import java.sql.Statement;
import java.sql.DriverManager;

public class AppStart {
	public static void main(String[] args) {
		Connection con = null;
		String url = "jdbc:mariadb://localhost:3306/example?user=example&password=1234";
		Statement stmt = null;
		
		try {
			Class.forName("org.mariadb.jdbc.Driver");
			con = DriverManager.getConnection(url);
			stmt = con.createStatement();
			int result = stmt.executeUpdate("INSERT INTO members VALUES ('stone', 'æ∆¿ŒΩ¥≈∏¿Œ', 'stone@google.com', MD5('1234'));");
			System.out.println("result : " + result);
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		finally {
			try { stmt.close(); } catch (Exception e) {}
			try { con.close(); } catch (Exception e) {}
		}
	}
}
