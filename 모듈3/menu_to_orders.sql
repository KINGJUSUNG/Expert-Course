CREATE TABLE menu_to_orders (
	order_id INT UNSIGNED NOT NULL,
	store_id INT UNSIGNED NOT NULL,
	menu_id INT UNSIGNED NOT NULL,
	menu_to_order_amount INT UNSIGNED NOT NULL,
	PRIMARY KEY(order_id, store_id, menu_id),
	FOREIGN KEY(order_id) REFERENCES orders(order_id),
	FOREIGN KEY(store_id, menu_id) REFERENCES menus(store_id, menu_id)
);