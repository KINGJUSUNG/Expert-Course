package vo;

public class Comic {
	private int id;
	private String title;
	private int price;
	private String categoryCode;
	private String publisherCode;
	private Category category;

	public Comic() {}
	
	public Comic(int id, String title, int price, String categoryCode, String publisherCode, Category category) {
		this.id = id;
		this.title = title;
		this.price = price;
		this.categoryCode = categoryCode;
		this.publisherCode = publisherCode;
		this.category = category;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getTitle() {
		return title;
	}

	public void setTitle(String title) {
		this.title = title;
	}

	public int getPrice() {
		return price;
	}

	public void setPrice(int price) {
		this.price = price;
	}
	
	public void setCategory(Category category) {
		this.category = category;
	}

	public String getCategoryCode() {
		return categoryCode;
	}

	public void setCategoryCode(String categoryCode) {
		this.categoryCode = categoryCode;
	}

	public String getPublisherCode() {
		return publisherCode;
	}

	public void setPublisherCode(String publisherCode) {
		this.publisherCode = publisherCode;
	}
	
	public Category getCategory() {
		return this.category;
	}
}
