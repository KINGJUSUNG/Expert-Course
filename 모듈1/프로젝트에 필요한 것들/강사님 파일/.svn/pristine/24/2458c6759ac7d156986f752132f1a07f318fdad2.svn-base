import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.MessageFormat;
import java.util.ArrayList;

public class TypeDAO {
	private static TypeDAO instance; 
	private String currentType;
	private ArrayList<Type> list;
	
	static {
		instance = new TypeDAO();
	}
	
	private TypeDAO() {		
		list = new ArrayList<>();
	}
	
	public static TypeDAO getInstance() {
		return instance;
	}
	
	public void setList(ArrayList<Type> list) {
		this.list = list;
	}
	
	public ArrayList<Type> getList() {
		return this.list;
	}
		
	public boolean setTypeList(Connection con, String type) {
		PreparedStatement stmt = null;
		ResultSet rs = null;
		boolean result = false;
		
		try {
			if (type == null) {
				stmt = con.prepareStatement(SQLManager.Select.TYPE_ALL);				
			}
			else {
				stmt = con.prepareStatement(SQLManager.Select.TYPE);
				stmt.setString(1, type);
			}
			rs = stmt.executeQuery();
			
			list.clear();			
			if (rs.next()) {
				String code = rs.getString("type_code");
				String name = rs.getString("type_name");
				Type t = new Type(code, name);
				list.add(t);
			}			
			
			this.currentType = type;
			if (this.currentType == null) {
				this.currentType = "ALL";
			}
			result = true;
		}
		catch (SQLException e) {
			e.printStackTrace();
			return result;
		}
		finally {
			try { rs.close(); } catch(Exception e) {}
			try { stmt.close(); } catch(Exception e) {}
		}
		return result;
	}
		
	public String getCurrentType() {
		return currentType;
	}
	
	public boolean validate(Connection con, String code) {
		PreparedStatement stmt = null;
		ResultSet rs = null;
		boolean result = false;
		try {
			stmt = con.prepareStatement(SQLManager.Select.TYPE_CODE_COUNT);
			stmt.setString(1, code);
			rs = stmt.executeQuery();
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
	
	public boolean insert(Connection con, String code, String name) {
		return insert(con, new Type(code, name));
	}
	
	public boolean insert(Connection con, Type type) {
		PreparedStatement stmt = null;
		boolean result = false;
		try {
			stmt = con.prepareStatement(SQLManager.Insert.TYPE);
			stmt.setString(1, type.getCode());
			stmt.setString(2, type.getName());
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
	
	public boolean delete(Connection con, String code) {		
		return delete(con, new Type(code, null));
	}
	
	public boolean delete(Connection con, Type type) {
		PreparedStatement stmt = null;
		boolean result = false;
				
		if (type.getCode() == null) {
			return false;
		}
				
		try {
			con.setAutoCommit(false);
			String sql = String.format(SQLManager.Delete.EMPLOYEES_CODE_ALL, type.getCode());
			if (EmployeeDAO.getInstance().executeUpdate(con, sql)) {			
				stmt = con.prepareStatement(SQLManager.Delete.TYPE);			
				stmt.setString(1, type.getCode());
				result = (stmt.executeUpdate() > 0);
				if (result) {
					con.commit();
				}
			}
		}
		catch (SQLException e) {
			e.printStackTrace();			
			return result;
		}
		finally {
			try { stmt.close(); } catch (Exception e) {}
			try { con.rollback(); } catch (Exception e) {}
			try { con.setAutoCommit(true); } catch (Exception e) {}
		}
		return result;
	}
	
	public boolean update(Connection con, String code, String type) {
		return update(con, new Type(code, type));
	}
	
	public boolean update(Connection con, Type type) {
		PreparedStatement stmt = null;
		boolean result = false;
		
		try {
			stmt = con.prepareStatement(SQLManager.Update.TYPE);
			stmt.setString(1, type.getName());
			stmt.setString(2, type.getCode());
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
