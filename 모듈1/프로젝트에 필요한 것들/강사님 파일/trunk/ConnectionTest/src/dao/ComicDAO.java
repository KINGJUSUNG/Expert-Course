package dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;

import vo.Category;
import vo.Comic;

public class ComicDAO {
	
	public static boolean insert(Connection con, Comic comic) {
		boolean result = false;
		PreparedStatement pstmt = null;
		
		try {
			pstmt = con.prepareStatement("INSERT INTO comics VALUES(?, ?, ?, ?, ?);");
			pstmt.setInt(1, comic.getId());
			pstmt.setString(2, comic.getTitle());
			pstmt.setInt(3, comic.getPrice());
			pstmt.setString(4, comic.getCategoryCode());
			pstmt.setString(5, comic.getPublisherCode());
			result = (pstmt.executeUpdate() > 0);
		}
		catch (SQLException e) {
			e.printStackTrace();
		}
		finally {
			try { pstmt.close(); } catch (Exception e) {}
		}
		return result;
	}
	
	
	public static ArrayList<Comic> getComics(Connection con, Category category) {
		ArrayList<Comic> list = new ArrayList<>();
		Statement stmt = null;
		ResultSet rs = null;

		try {
			stmt = con.createStatement();
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
