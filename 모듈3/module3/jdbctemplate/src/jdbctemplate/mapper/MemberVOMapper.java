package jdbctemplate.mapper;

import java.sql.ResultSet;
import java.sql.SQLException;

import org.springframework.jdbc.core.RowMapper;

import jdbctemplate.vo.MemberVO;

public class MemberVOMapper implements RowMapper<MemberVO> {

	@Override
	public MemberVO mapRow(ResultSet rs, int rowNum) throws SQLException {
		MemberVO member = new MemberVO();
		member.setEmail(rs.getString("email"));
		member.setPass(rs.getString("pass"));
		member.setNick(rs.getString("nick"));
		member.setRegisteredAt(rs.getTimestamp("registeredAt"));
		member.setRemovedAt(rs.getTimestamp("removedAt"));
		return member;
	}
}
