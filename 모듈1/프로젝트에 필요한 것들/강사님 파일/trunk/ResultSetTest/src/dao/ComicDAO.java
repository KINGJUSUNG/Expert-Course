package dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;

import vo.Category;
import vo.Comic;

public class ComicDAO {
	
	public static ArrayList<Comic> getComics(Category category) {
		ArrayList<Comic> list = new ArrayList<>();
		Statement stmt = null;
		ResultSet rs = null;

		try {
			stmt = MyConnection.getConnection().createStatement();
			rs = stmt.executeQuery("SELECT * FROM comics WHERE category_code = '" + category.getCode() + "'");
			while (rs.next()) {
				Comic c = new Comic();
				c.setId(rs.getInt("id"));
				c.setTitle(rs.getString("title"));
				c.setPrice(rs.getInt("price"));
				c.setCategoryCode(rs.getString("category_code"));
				c.setPublisherCode(rs.getString("publisher_code"));
				c.setCategory(category);
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
