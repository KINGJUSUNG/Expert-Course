package kr.co.dinner41.controller;

import java.util.List;

import javax.servlet.http.HttpSession;

import kr.co.dinner41.service.review.ReviewListService;
import kr.co.dinner41.service.store.*;
import kr.co.dinner41.vo.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

import kr.co.dinner41.command.StoreInsertCommand;
import kr.co.dinner41.exception.ReviewException;
import kr.co.dinner41.exception.store.StoreException;

@Controller
@RequestMapping()
public class StoreController {
	@Autowired
	@Qualifier("storeInsertService")
	StoreInsertService storeInsertService;
	
	
	@Autowired
	@Qualifier("storeViewByStoreService")
	StoreViewByStoreService storeViewByStoreService;
	
	@Autowired
	@Qualifier("storeListByUserService")
	StoreListByUserService storeListByUserService;
	
	@Autowired
	@Qualifier("storeListByManagerService")
	StoreListByManagerService storeListByManagerService;

	@Autowired
	@Qualifier("storeViewByUserService")
	StoreViewByUserService storeViewByUserService;

	@Autowired
	@Qualifier("reviewListService")
	ReviewListService reviewListService;
	
	@RequestMapping(value="/sm/store",method=RequestMethod.GET)
	public String insert(HttpSession session,Model model) {
		UserVO user = (UserVO)session.getAttribute("loginUser");
		int userId = user.getId();
		StoreVO store = null;
		store = storeViewByStoreService.execute(userId);
		
		if(store==null) {
			return "store/storeRegister";
		}
		
		model.addAttribute("store",store);
		return "store/storeView";
	}
	@RequestMapping(value="/sm/store",method=RequestMethod.POST)
	public String insert(StoreInsertCommand command,Model model,HttpSession session) {
		
		StoreVO store = new StoreVO();
		
		UserVO user = new UserVO();
		user.setId(14);
		
		StoreCategoryVO storeCategory = new StoreCategoryVO();
		storeCategory.setId("KOR");
		
		StoreStateVO storeState = new StoreStateVO();
		storeState.setId(2);
		
		store.setUser(user);
		store.setCategory(storeCategory);
		store.setState(storeState);
		store.setBusinessNumber(command.getBusinessNumber());
		store.setName(command.getName());
		store.setAddress(command.getAddress());
		store.setSubAddress(command.getSubAddress());
		store.setLatitude(37.482417);//store.setLatitude(command.getLatitude());
		store.setLongitude(126.953073);//store.setLongitude(command.getLongitude());
		store.setPhone(command.getPhone());
		store.setOperateTime(command.getOperateTime());
		store.setPhoto(command.getPhoto());
		store.setIntroduction(command.getIntroduction());
	
		storeInsertService.execute(store);
		return "store/storeHome";
	}
	
	@RequestMapping(value="/sm/update/store",method=RequestMethod.GET)
	public String update(HttpSession session,Model model) {
		UserVO user = (UserVO)session.getAttribute("loginUser");
		int userId = user.getId();
		StoreVO store = null;
		store = storeViewByStoreService.execute(userId);
		model.addAttribute("store",store);
		
		return "store/storeUpdate";
	}
	
	
	
	@RequestMapping(value="/gm/{category}/{keyword}/{page}/store",method=RequestMethod.GET)
	public String listByUser(@PathVariable("category") String category, @PathVariable("keyword") String keyword,
							@PathVariable("page") String page, Model model, HttpSession session) {
		int intPage = Integer.parseInt(page);
		UserVO user = (UserVO)session.getAttribute("loginUser");
		double userLatitude = user.getLatitude();
		double userLongitude = user.getLongitude();
		
		List<StoreListByUserViewVO> storeListByUserViews =null;
		try {
			storeListByUserViews = storeListByUserService.execute(category,keyword,userLatitude,userLongitude,intPage);
		} catch (StoreException | ReviewException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		System.out.println(storeListByUserViews);
		model.addAttribute("category",category);
		model.addAttribute("keyword",keyword);
		model.addAttribute("stores",storeListByUserViews); //이름주의! stores로 담아놓음
		
		return "user/storeList";
	}

	@RequestMapping(value="/ad/{store-state-name}/{store-name}/{page}/store",method=RequestMethod.GET)
	public String listByManager(@PathVariable("store-state-name") String storeStateName, @PathVariable("store-name") String storeName, @PathVariable("page") String page, HttpSession session, Model model) {
		int intPage = Integer.parseInt(page);
		List<StoreVO> stores;
		
		UserVO user = (UserVO)session.getAttribute("loginUser");
		
		model.addAttribute("storeStateName",storeStateName);
		model.addAttribute("storeName",storeName);
		model.addAttribute("page",page);

		stores = storeListByManagerService.execute(storeStateName, storeName, intPage);
		
		model.addAttribute("stores",stores);
		
		return "manage/storeList";
	}

	@RequestMapping(value = "/gm/{id}/{type}/store", method = RequestMethod.GET)
	public String ViewByUser(@PathVariable("id") String id, HttpSession session, Model model, @PathVariable("type") String type){
		int storeId = Integer.parseInt(id);
		UserVO user = (UserVO) session.getAttribute("loginUser");
		model.addAttribute("address", user.getAddress());

		StoreVO store = storeViewByUserService.execute(storeId);
		model.addAttribute("store", store);

		double total_score = reviewListService.getTotalScore(storeId);
		model.addAttribute("score", total_score);

		model.addAttribute("type", type);

		List<MenuVO> list = storeViewByUserService.getMenus(storeId);
		model.addAttribute("list", list);

		List<ReviewVO> reviews = reviewListService.execute(storeId, 1);
		model.addAttribute("reviews", reviews);

		return "user/storeView";
	}
}
