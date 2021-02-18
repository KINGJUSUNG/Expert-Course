package dao;

import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.sql.Connection;

public class MyConnection {
	public static final String URL = "jdbc:mariadb://localhost:3306/example?user=example&password=1234";
	public static Connection connection;
	
	public static void connect() throws Exception {
		connection = DriverManager.getConnection(URL);
	}
	
	public static Connection getConnection() {
		return connection;
	}
	
	public static void close() {
		try { connection.close(); } catch (Exception e) {}
	}
}
