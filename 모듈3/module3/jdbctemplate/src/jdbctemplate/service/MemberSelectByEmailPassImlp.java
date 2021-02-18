package jdbctemplate.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;

import jdbctemplate.dao.MemberDao;
import jdbctemplate.vo.MemberVO;

@Service("memberSelectByEmailPass")
public class MemberSelectByEmailPassImlp implements MemberSelectByEmailPass {

	@Autowired
	@Qualifier("memberDao")
	private MemberDao dao;

	@Override
	public void execute(String email, String pass) throws Exception {
		MemberVO member = new MemberVO();
		try {
			member = dao.selectByEmailPass(email, pass);
			if (member == null) {
				System.out.println("해당 이메일, 비밀번호는 존재하지 않습니다.");
			}
			else {
				System.out.println(member);
			}
		}
		catch (Exception e) {
			System.err.println("오류가 발생하였습니다.");
		}
	}
}
