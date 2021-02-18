package keyholder.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import keyholder.dao.ProductDao;
import keyholder.vo.ProductVo;

@Service("productInsert")
public class ProductInsertImpl implements ProductInsert {

	@Autowired
	private ProductDao dao;

	@Override
	public void execute(String productName, int productPrice, int partId) throws Exception {
		ProductVo product = new ProductVo();
		product.setProductName(productName);
		product.setProductPrice(productPrice);
		product.setPartId(partId);
		dao.insert(product);
		System.out.println(product);
	}
}
