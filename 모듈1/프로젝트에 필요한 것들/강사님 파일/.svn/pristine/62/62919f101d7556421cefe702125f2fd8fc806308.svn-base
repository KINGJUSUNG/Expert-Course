import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class EmployeeDAO {
	public static EmployeeDAO instance = null;
	
	private EmployeeDAO() {}
	
	public static EmployeeDAO getInstance() {
		return instance;
	}
	
	public boolean executeUpdate(Connection con, String sql) throws SQLException {
		Statement stmt = null;
				
		try {
			stmt = con.createStatement();
			stmt.executeUpdate(sql);
			return true;
		}
		catch (SQLException e) {
			e.printStackTrace();
			throw e;
			
		}
		finally {
			try { stmt.close(); } catch (Exception e) {}
		}				
	}
	
	public boolean validate(Connection con, String code) {
		Statement stmt = null;
		ResultSet rs = null;
		boolean result = false;
		try {
			stmt = con.createStatement();
			rs = stmt.executeQuery("SELECT COUNT(*) AS cnt FROM employees WHERE emp_code = '" + code + "'");
			if (rs.next()) {
				result = (rs.getInt("cnt") > 0);
			}
		}
		catch (SQLException e) {
			e.printStackTrace();
			return false;
		}
		finally {
			try { rs.close(); } catch (Exception e) {}
			try { stmt.close(); } catch (Exception e) {}
		}
		return result;
	}
	
	public boolean insert(Connection con, String code, String name, String deptCode, String dutieCode, String typeCode, String seniorCode, int income, int worktime) {
		return insert(con, new Employee(code, name, deptCode, dutieCode, typeCode, seniorCode, income, worktime));
	}
	
	public boolean insert(Connection con, Employee employee) {
		PreparedStatement stmt = null;
		boolean result = false;
		try {
			stmt = con.prepareStatement(SQLManager.SQL_INSERT_EMPLOYEE);
			stmt.setString(1, employee.getCode());
			stmt.setString(2, employee.getName());
			stmt.setString(3, employee.getDeptCode());
			stmt.setString(4, employee.getDutieCode());
			stmt.setString(5, employee.getTypeCode());
			stmt.setString(6, employee.getSeniorCode());
			stmt.setInt(7, employee.getIncome());
			stmt.setInt(8, employee.getWorktime());
			result = (stmt.executeUpdate() > 0); 
		}
		catch (SQLException e) {
			e.printStackTrace();
			return false;
		}
		finally {
			try { stmt.close(); } catch (Exception e) {}
		}
		return result;
	}
	
	public boolean delete(Connection con, String code) throws SQLException {
		Employee employee = new Employee();
		employee.setCode(code);
		return delete(con, employee);
	}
	
	public boolean delete(Connection con, Employee employee) throws SQLException {
		PreparedStatement stmt = null;
		
		try {
			stmt = con.prepareStatement(SQLManager.SQL_DELETE_EMPLOYEE);
			stmt.setString(1, employee.getCode());
			stmt.executeUpdate();
		}
		catch (SQLException e) {
			e.printStackTrace();
			throw e;
		}
		finally {
			try { stmt.close(); } catch (Exception e) {}
		}
		return true;
	}
	
	public boolean update(Connection con, String code) {
		Employee employee = new Employee();
		employee.setCode(code);
		return update(con, employee);
	}
	
	public boolean update(Connection con, Employee employee) {
		PreparedStatement stmt = null;
		boolean result = false;
		
		try {
			stmt = con.prepareStatement(SQLManager.SQL_UPDATE_EMPLOYEE);
			stmt.setString(1, employee.getName());
			stmt.setString(2, employee.getDeptCode());
			stmt.setString(3, employee.getDutieCode());
			stmt.setString(4, employee.getTypeCode());
			stmt.setString(5, employee.getSeniorCode());
			stmt.setInt(6, employee.getIncome());
			stmt.setInt(7, employee.getWorktime());
			stmt.setString(8, employee.getCode());
			result = (stmt.executeUpdate() > 0);
		}
		catch (SQLException e) {
			e.printStackTrace();
			return false;
		}
		finally {
			try { stmt.close(); } catch (Exception e) {}
		}
		return result;
	}
}
