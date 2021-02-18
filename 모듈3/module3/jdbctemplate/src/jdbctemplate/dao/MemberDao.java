package jdbctemplate.dao;

import java.util.List;

import jdbctemplate.vo.MemberVO;

public interface MemberDao {
	void insert(MemberVO member) throws Exception;
	void update(MemberVO member) throws Exception;
	void delete(String email) throws Exception;
	MemberVO selectByEmail(String email) throws Exception;
	MemberVO selectByEmailPass(String email, String pass) throws Exception;
	List<MemberVO> selectList(String column, String str) throws Exception;	// 특정 컬럼에서 특정 문자열을 가지고 있는 멤버 검색
}
