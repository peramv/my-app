package com.ifdsgroup.ztsapitest;

import org.apache.log4j.BasicConfigurator;
import org.apache.log4j.Logger;

import com.ifds.iFast.api.JavaAPIConfig;
import com.ifds.iFast.api.ShareholderSearchRequest;
import com.ifds.iFast.api.ShareholderSearchView;
import com.ifds.iFast.api.SonicManager;

public class Test {

    //  01000000003                000000000000000000000F3470,F0,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,Fmsliqlnk,FENG,Fmsd,FLN,F,FY,FY,FAPI-[com.ifds.iFast.api.ShareholderSearchRequest],F0,FN,F,F,FN,FN,F,F,F,F,F
	
	public static void main(String[] args) {
	
		BasicConfigurator.configure();
		
		Logger log = Logger.getLogger(Test.class);
		
		System.setProperty("APICfg", "./config/config.xml");
		
		System.setProperty(JavaAPIConfig.ZTS_SSL_PRIVATE_KEY_PASSWORD, "lfdkglsakfd");
		System.setProperty(JavaAPIConfig.ZTS_SONIC_USER_ID, "smithd");
		System.setProperty(JavaAPIConfig.ZTS_SONIC_PASSWORD, "123456");
		
		SonicManager.init();
		
		ShareholderSearchView view = new ShareholderSearchView();
		
		ShareholderSearchRequest req = view.getRequest();

		req.setSrchAccountNum("3470");
		req.setUser_Id("msliqlnk");
		req.setLanguageCode("en");
		req.setCompanyId("msd");
		req.setSortBy("LN");
		req.setAllAccounts(Boolean.TRUE);
		
		try {
			
			if (view.receiveAll("msduat2")) {
				for (int i=0; i< view.getRecordCount(); i++) {
					view.getAccountNum(i);
				}
			}
			
			
		} catch (Exception e) {
			e.printStackTrace();
		}
		
	}
	
}
