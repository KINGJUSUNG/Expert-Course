package keyholder.pstmt;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import org.springframework.jdbc.core.PreparedStatementCreator;

public class PartInsertCreator implements PreparedStatementCreator {

	private String partName;
	private String[] columns;
	
	public PartInsertCreator(String partName, String[] columns) {
		this.partName = partName;
		this.columns = columns;
	}

	@Override
	public PreparedStatement createPreparedStatement(Connection con) throws SQLException {
		String sql = "INSERT INTO parts(partName) VALUES (?)";
		PreparedStatement pstmt = con.prepareStatement(sql, columns);
		pstmt.setString(1, partName);
		return pstmt;
	}
}
