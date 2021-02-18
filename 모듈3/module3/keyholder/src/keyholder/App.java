package keyholder;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

import keyholder.service.PartProductInsert;

public class App {

	public static void main(String[] args) throws Exception {
		ApplicationContext ctx = new ClassPathXmlApplicationContext("AppContext.xml");

		PartProductInsert service = ctx.getBean(PartProductInsert.class);
		service.execute("전자", "노트북", 10000000);
	}
}
