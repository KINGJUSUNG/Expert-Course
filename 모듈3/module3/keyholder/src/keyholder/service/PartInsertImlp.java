package keyholder.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import keyholder.dao.PartDao;
import keyholder.exception.PartException;
import keyholder.vo.PartVo;

@Service("partInsert")
public class PartInsertImlp implements PartInsert {

	@Autowired
	private PartDao dao;

	@Override
	public void execute(String partName) throws PartException {
		PartVo part = new PartVo();
		part.setPartName(partName);
		dao.insert(part);
		System.out.println(part);
	}
}
