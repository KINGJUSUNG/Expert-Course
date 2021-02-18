package jdbctemplate.service;

public interface MemberSelectByEmailPass {
	void execute(String email, String pass) throws Exception;
}
