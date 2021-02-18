package jdbctemplate.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;

import jdbctemplate.dao.MemberDao;
import jdbctemplate.vo.MemberVO;

@Service("memberRegister")
public class MemberRegisterImpl implements MemberRegister {

	@Autowired
	@Qualifier("memberDao")
	private MemberDao dao;

	@Override
	public void execute(String email, String pass, String pass2, String nick) throws Exception {
		MemberVO member = new MemberVO(email, pass, nick, null, null);
		try {
			dao.insert(member);
			System.out.println("회원가입 처리가 완료되었습니다.");
		}
		catch (Exception e) {
			System.err.println("회원가입 도중 문제가 발생하였습니다.");
		}
	}
}
