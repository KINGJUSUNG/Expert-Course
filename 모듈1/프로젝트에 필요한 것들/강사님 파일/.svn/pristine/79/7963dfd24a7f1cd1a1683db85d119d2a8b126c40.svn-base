import java.sql.Connection;
import java.sql.SQLException;
import java.util.Properties;
import java.sql.DriverManager;
import java.io.FileReader;
import java.io.IOException;
import java.sql.Statement;
import java.sql.ResultSet;

public class AppStart {
	public static void main(String[] args) {
		Properties prop = new Properties();
		Connection con = null;
		Statement stmt = null;
		ResultSet rs = null;
		try {
			prop.load(new FileReader("config.txt"));
			Class.forName("org.mariadb.jdbc.Driver");
			System.out.println("JDBC 드라이버가 검색되었습니다.");
			con = DriverManager.getConnection(
					prop.getProperty("url"), 
					prop.getProperty("user"), 
					prop.getProperty("pass"));
			System.out.println("데이터베이스 서버와 접속되었습니다.");
			stmt = con.createStatement();
			rs = stmt.executeQuery("SELECT * FROM members");
			while (rs.next()) {
				System.out.printf("%s %s\n", 
									rs.getString("member_name"),
									rs.getString("member_email"));
			}
		}
		catch (ClassNotFoundException e) {
			System.err.println("JDBC 드라이버 검색에 실패하였습니다.");
		}
		catch (SQLException e) {
			e.printStackTrace();
		}
		catch (IOException e) {
			e.printStackTrace();
		}
		finally {
			try { rs.close(); } catch (Exception e) {}
			try { stmt.close(); } catch (Exception e) {}
			try { con.close(); } catch (Exception e) {}
		}
	}
}
