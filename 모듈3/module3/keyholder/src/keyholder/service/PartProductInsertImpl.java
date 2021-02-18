package keyholder.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import keyholder.dao.PartDao;
import keyholder.dao.ProductDao;
import keyholder.vo.PartVo;
import keyholder.vo.ProductVo;

@Service("partProductInsert")
public class PartProductInsertImpl implements PartProductInsert {

	@Autowired
	ProductDao productDao;
	@Autowired
	PartDao partDao;

	@Transactional
	@Override
	public void execute(String partName, String productName, int productPrice) throws Exception {
		PartVo part = new PartVo();
		part.setPartName(partName);
		partDao.insert(part);
		
		ProductVo product = new ProductVo();
		product.setProductName(productName);
		product.setProductPrice(productPrice);
		product.setPartId(part.getPartId());
		// product.setPartId(2000);
		productDao.insert(product);
		
		System.out.println(part);
		System.out.println(product);
	}
}
