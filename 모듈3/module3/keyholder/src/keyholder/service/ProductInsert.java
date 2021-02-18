package keyholder.service;

public interface ProductInsert {
	void execute(String productName, int productPrice, int partId) throws Exception;
}
