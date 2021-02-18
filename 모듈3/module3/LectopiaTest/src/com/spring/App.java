package com.spring;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

import com.spring.entity.Test;
import com.spring.ui.TestPrinter;

public class App {

	public static void main(String[] args) {
	
		// resource폴더는 클래스패스이므로 그 아래 있는 AppContext.xml은 그냥 이름만 써주면 됨
		ApplicationContext ctx = new ClassPathXmlApplicationContext("AppContext.xml");
		Test test = ctx.getBean("lectopiaTest", Test.class);
		
		TestPrinter printer = ctx.getBean("printer", TestPrinter.class);
		printer.print();
		
		TestPrinter printer2 = ctx.getBean("printer2", TestPrinter.class);
		printer2.print();
	}
}
