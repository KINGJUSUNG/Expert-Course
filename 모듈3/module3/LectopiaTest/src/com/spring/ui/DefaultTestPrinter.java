package com.spring.ui;

import com.spring.entity.Test;

public class DefaultTestPrinter implements TestPrinter {
	
	private Test test;
	public DefaultTestPrinter(Test test) {
		this.test = test;
	}
	
	public void setTest(Test test) {
		this.test = test;
	}

	@Override
	public void print() {
		System.out.printf("ÃÑÁ¡ : %d, Æò±Õ : %.2f\n", test.tot(), test.avg());
	}
}