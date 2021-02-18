package keyholder.vo;

public class ProductVo {
	private int productId;
	private String productName;
	private int productPrice;
	private int partId;
	private PartVo part;
	
	public ProductVo () {
		this(0, null, 0, 0);
	}
	public ProductVo(int productId, String productName, int productPrice, int partId) {
		this(productId, productName, productPrice, partId, null);
	}
	public ProductVo(int productId, String productName, int productPrice, int partId, PartVo part) {
		this.productId = productId;
		this.productName = productName;
		this.productPrice = productPrice;
		this.partId = partId;
		this.part = part;
	}
	public int getProductId() {	return productId; }
	public void setProductId(int productId) { this.productId = productId; }
	public String getProductName() { return productName; }
	public void setProductName(String productName) { this.productName = productName; }
	public int getProductPrice() { return productPrice; }
	public void setProductPrice(int productPrice) { this.productPrice = productPrice; }
	public int getPartId() { return partId; }
	public void setPartId(int partId) { this.partId = partId; }
	public PartVo getPart() { return part; }
	public void setPart(PartVo part) { this.part = part; }

	@Override
	public String toString() {
		return String.format("%d %s %d %d",  productId, productName, productPrice, partId);
	}
}
