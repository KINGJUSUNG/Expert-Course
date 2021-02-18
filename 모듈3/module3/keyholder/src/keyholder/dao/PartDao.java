package keyholder.dao;

import keyholder.exception.PartException;
import keyholder.vo.PartVo;

public interface PartDao {
	void insert(PartVo part) throws PartException;			// �Է�
	void update(PartVo part) throws PartException;			// ����
	void delete(int id) throws PartException;				// ����
	PartVo selectById(int id) throws PartException;  		// ���̵� �˻�
	PartVo selectByName(String name) throws PartException;	// �̸�  �˻�
}
