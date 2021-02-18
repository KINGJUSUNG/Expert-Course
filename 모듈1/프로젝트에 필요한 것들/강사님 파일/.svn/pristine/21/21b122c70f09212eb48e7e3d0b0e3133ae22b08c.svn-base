import java.sql.Connection;
import java.util.ArrayList;

import dao.CategoryDAO;
import dao.ComicDAO;
import dao.MyConnection;
import vo.Category;

public class AppStart {
	
	public static void main(String[] args) {
		ArrayList<Category> categories = null;
		try {
			MyConnection.connect(); 
			categories = CategoryDAO.getCategory();
			for (Category category : categories) {
				category.setComics(ComicDAO.getComics(category));
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		finally {
			MyConnection.close();
		}
		System.out.println("프로그램종료");
	}
}
