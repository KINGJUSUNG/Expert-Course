package jdbc.dao;

import java.util.List;

import jdbc.vo.PartVO;

public interface PartDao {
	void insert(PartVO part);
	void update(PartVO part);
	void delete(int id);
	PartVO selectById(int id);
	List<PartVO> selectAll();
}
