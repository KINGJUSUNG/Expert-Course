import java.sql.Connection;
import java.sql.DriverManager;

public class ServerManager {
	public final static String URL = "jdbc:mariadb://192.168.30.200:3306/test?user=tester&password=1234";
	private static ServerManager instance = new ServerManager();
	private Connection connection;
	
	private ServerManager() {
		connection = null;
	}
	
	public static ServerManager getInstance() {
		return instance;
	}
	
	public void open() throws Exception {
		if (connection == null) {
			connection = DriverManager.getConnection(URL);
		}
	}
	
	public Connection getConnection() {
		return connection;
	}
	
	public void close() {
		try {
			connection.close();
		} 
		catch (Exception e) {}
		finally {
			connection = null;
		}
	}
	
}
