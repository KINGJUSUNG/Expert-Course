package jdbctemplate.dao;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

import jdbctemplate.mapper.MemberVOMapper;
import jdbctemplate.pstmt.SelectByEmailPassPstmtCreator;
import jdbctemplate.vo.MemberVO;

@Repository("memberDao")	// Component 부류로서 자동으로 스프링빈에 등록
public class MemberDaoImpl implements MemberDao {

	@Autowired
	@Qualifier("jdbcTemplate")
	private JdbcTemplate temp;

	@Override
	public void insert(MemberVO member) throws Exception {
		String sql = "INSERT INTO members VALUES(?, ?, ?, default, default)";
		temp.update(sql, member.getEmail(), member.getPass(), member.getNick());
	}

	@Override
	public void update(MemberVO member) throws Exception {

	}

	@Override
	public void delete(String email) throws Exception {

	}

	@Override
	public MemberVO selectByEmail(String email) throws Exception {
		List<MemberVO> members = null;
		String sql = "SELECT * FROM members WHERE email = ?";
		members = temp.query(sql, new MemberVOMapper(), email);
		return (members.size() == 0 ? null : members.get(0));
	}

	@Override
	public MemberVO selectByEmailPass(final String email, final String pass) throws Exception {
		List<MemberVO> members = null;
		members = temp.query(new SelectByEmailPassPstmtCreator(email, pass), new MemberVOMapper());
		return (members.size() == 0 ? null : members.get(0));
	}

	@Override
	public List<MemberVO> selectList(String column, String str) throws Exception {
		return null;
	}
}
