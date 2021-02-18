package jdbc.dao;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.stereotype.Repository;

import jdbc.vo.PartVO;

@Repository("partDao")
public class PartDaoImpl implements PartDao {

	@Autowired
	@Qualifier("jdbcTemplate")
	private JdbcTemplate temp;

	@Override
	public void insert(PartVO part) {
		String sql = "INSERT INTO parts VALUES (default, ?)";
		int result = temp.update(sql, part.getPartName());
		if (result > 0) {
			System.out.println("등록 성공!");
		}
		else {
			System.out.println("등록 실패!");
		}
	}

	@Override
	public void update(PartVO part) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void delete(int id) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public PartVO selectById(int id) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public List<PartVO> selectAll() {
		String sql = "SELECT * FROM parts ORDER BY partId";
		List<PartVO> parts = temp.query(sql, new RowMapper<PartVO>() {

			@Override
			public PartVO mapRow(ResultSet rs, int rowNum) throws SQLException {
				int partId = rs.getInt("partId");
				String partName = rs.getString("partName");
				PartVO part = new PartVO(partId, partName);
				return part;
			}
		});
		return parts;
	}
}
