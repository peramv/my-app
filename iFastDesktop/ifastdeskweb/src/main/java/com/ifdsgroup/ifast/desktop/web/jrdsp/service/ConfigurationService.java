package com.ifdsgroup.ifast.desktop.web.jrdsp.service;

import java.util.ArrayList;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpEntity;
import org.springframework.http.HttpMethod;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.util.MultiValueMap;
import org.springframework.web.client.RestTemplate;

import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.AccountRdspResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.BaseResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.ConfigGetResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.Configuration;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.ConfigurationList;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.ConfigurationResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.util.JRDSPUtil;

@Service
public class ConfigurationService {
	
	@Value("${jrdsp.services.url}")
	private String jrdspServiceURL;
	
	@Autowired
	RestTemplate restTemplate;
	
	public BaseResponse getConfigurationDetails() {
		String httpPath="/getConfig";
		String URL=jrdspServiceURL+httpPath;
	
		MultiValueMap<String, String> headers = JRDSPUtil.addHeaders(httpPath, HttpMethod.GET.name(), "application/json", "1.0", JRDSPUtil.generateTraceId(),"");
		HttpEntity httpEntity = new HttpEntity( headers);
		
		
		JRDSPUtil.printObject(httpEntity);
		ResponseEntity<ConfigGetResponse> responseEntity=null;

		responseEntity = restTemplate.exchange(URL, HttpMethod.GET, httpEntity,ConfigGetResponse.class);

		JRDSPUtil.printObject(responseEntity);
		List<Configuration> configurationListResponse = responseEntity.getBody().getConfigurationList();
		List<Configuration> configurationList = new ArrayList<>();
		configurationListResponse.forEach(conf->{
			Configuration configuration = new Configuration();
			configuration.setConfCode(conf.getConfCode());
			configuration.setConfValue(conf.getConfValue());
			configurationList.add(configuration);
		});
		ConfigurationList list=new ConfigurationList();
		list.setConfiguration(configurationList);
		ConfigurationResponse response =new ConfigurationResponse();
		response.setConfigList(list);
		return response;
		
		
	}

}
