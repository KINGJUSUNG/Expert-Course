package dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;

import vo.Category;

public class CategoryDAO {

	public static ArrayList<Category> getCategory() {
		ArrayList<Category> list = new ArrayList<>();
		Statement stmt = null;
		ResultSet rs = null;
		
		try {
			stmt = MyConnection.getConnection().createStatement();
			rs = stmt.executeQuery("SELECT * FROM category");
			while (rs.next()) {
				Category c = new Category();
				c.setCode(rs.getString("category_code"));
				c.setName(rs.getString("category_name"));
				list.add(c);
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		finally {
			try { rs.close(); } catch (Exception e) {}
			try { stmt.close(); } catch (Exception e) {}
		}
				
		return list;
	}
}
