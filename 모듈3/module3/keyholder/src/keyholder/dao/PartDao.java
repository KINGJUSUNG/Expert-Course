package keyholder.dao;

import keyholder.exception.PartException;
import keyholder.vo.PartVo;

public interface PartDao {
	void insert(PartVo part) throws PartException;			// 입력
	void update(PartVo part) throws PartException;			// 편집
	void delete(int id) throws PartException;				// 삭제
	PartVo selectById(int id) throws PartException;  		// 아이디 검색
	PartVo selectByName(String name) throws PartException;	// 이름  검색
}
