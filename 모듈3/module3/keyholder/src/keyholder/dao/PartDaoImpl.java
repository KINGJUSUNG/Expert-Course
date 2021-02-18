package keyholder.dao;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.support.GeneratedKeyHolder;
import org.springframework.jdbc.support.KeyHolder;
import org.springframework.stereotype.Repository;

import keyholder.exception.PartException;
import keyholder.exception.PartInputException;
import keyholder.pstmt.PartInsertCreator;
import keyholder.vo.PartVo;

@Repository("partDao")
public class PartDaoImpl implements PartDao {

	@Autowired
	private JdbcTemplate jTemp;

	@Override
	public void insert(PartVo part) throws PartException {
		KeyHolder holder = new GeneratedKeyHolder();
		String[] columns = {"partId"};
		int result = jTemp.update(new PartInsertCreator(part.getPartName(), columns), holder);
		if (result == 0) {
			throw new PartInputException();
		}
		Number number = holder.getKey();
		int value = number.intValue();
		part.setPartId(value);
	}

	@Override
	public void update(PartVo part) throws PartException {

	}

	@Override
	public void delete(int id) throws PartException {

	}

	@Override
	public PartVo selectById(int id) throws PartException {
		return null;
	}

	@Override
	public PartVo selectByName(String name) throws PartException {
		return null;
	}
}
