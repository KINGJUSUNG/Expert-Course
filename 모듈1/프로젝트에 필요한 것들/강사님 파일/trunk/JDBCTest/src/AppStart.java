import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class AppStart {
	public static void main(String[] args) {
		Connection con = null;
		String url = "jdbc:mariadb://127.0.0.1:3306/kihee";
		String user = "kihee";
		String pass = "iloveyou7";
		try {
			Class.forName("org.mariadb.jdbc.Driver");
			System.out.println("JDBC 드라이버를 DriverManager에 등록하였습니다.");
			con = DriverManager.getConnection(url, user, pass);
			System.out.println("데이터베이스 서버에 정상적으로 접속하였습니다.");
		}
		catch (ClassNotFoundException e) {
			System.err.println("JDBC 드라이버 검색에 실패하였습니다.");
		}		
		catch (SQLException e) {
			e.printStackTrace();
		}
		finally {
			try { con.close(); } catch (Exception e) {}
		}
	}
}
