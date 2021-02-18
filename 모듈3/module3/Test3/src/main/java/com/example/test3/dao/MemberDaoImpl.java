package com.example.test3.dao;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.stereotype.Repository;

import com.example.test3.exception.MemberException;
import com.example.test3.exception.MemberInsertFailedException;
import com.example.test3.vo.MemberVo;

@Repository("memberDao")
public class MemberDaoImpl implements MemberDao {

	@Autowired
	@Qualifier("jdbcTemplate")
	private JdbcTemplate jTemp;

	@Override
	public void insert(MemberVo member) throws MemberException {
		String sql = "INSERT INTO members VALUES(?, ?, ?, default, default)";
		int result = 0;
		try {
			result = jTemp.update(sql, member.getEmail(), member.getPass(), member.getNick());
			if (result == 0) {
				throw new MemberInsertFailedException();
			}
		}
		catch (Exception e) {
			throw new MemberInsertFailedException();
		}
	}

	@Override
	public void delete(String email, String pass) throws MemberException {
		String sql = "DELETE FROM members WHERE email=?";
		int result = 0;
		result = jTemp.update(sql, email);
		if (result == 0) {
			// 예외 처리
		}
	}

	@Override
	public MemberVo login(String email, String pass) throws MemberException {
		String sql = "SELECT * FROM members WHERE email=? AND pass=?";
		List<MemberVo> members = jTemp.query(sql, new RowMapper<MemberVo>() {

			@Override
			public MemberVo mapRow(ResultSet rs, int rowNum) throws SQLException {
				MemberVo member = new MemberVo();
				member.setEmail(rs.getString("email"));
				member.setPass(rs.getString("pass"));
				member.setNick(rs.getString("nick"));
				member.setRegisteredAt(rs.getTimestamp("registeredAt"));
				member.setRemovedAt(rs.getTimestamp("removedAt"));
				return member;
			}
			
		}, email, pass);
		return (members.size() > 0 ? members.get(0) : null);
	}
}
