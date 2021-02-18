package jdbctemplate.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;

import jdbctemplate.dao.MemberDao;
import jdbctemplate.vo.MemberVO;

@Service("memberSelectByEmail")
public class MemberSelectByEmailImpl implements MemberSelectByEmail {

	@Autowired
	@Qualifier("memberDao")
	private MemberDao dao;

	@Override
	public void execute(String email) throws Exception {
		MemberVO member = null;
		try {
			member = dao.selectByEmail(email);
			if (member == null) {
				System.out.println("�ش� �̸����� �������� �ʽ��ϴ�.");
			}
			else {
				System.out.println(member);
			}
		}
		catch (Exception e) {
			System.err.println("������ �߻��Ͽ����ϴ�.");
		}
	}
}
