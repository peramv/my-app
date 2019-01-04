package com.ifdsgroup.ifast.desktop.web.jrdsp.service;

import java.util.Formatter;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpEntity;
import org.springframework.http.HttpMethod;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.util.MultiValueMap;
import org.springframework.web.client.RestTemplate;

import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.NotionalGetRequest;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.NotionalLotActivityBalancesResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.TransactionGetRequest;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.TransactionGetResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.util.JRDSPUtil;

@Service
public class NotionalActivityService {
	
	@Value("${jrdsp.services.url}")
	private String jrdspServiceURL;
	
	@Autowired
	RestTemplate restTemplate;
	

	

	public TransactionGetResponse getTransactionDetails(String accountId, TransactionGetRequest transactionGetRequest) {
		String httpPath="/transaction";
		String URL=jrdspServiceURL+httpPath+"/"+accountId;
	
		MultiValueMap<String, String> headers = JRDSPUtil.addHeaders(httpPath, HttpMethod.GET.name(), "application/json", "1.0", JRDSPUtil.generateTraceId());

		HttpEntity httpEntity = new HttpEntity( headers);
		
		
		JRDSPUtil.printObject(httpEntity);

		ResponseEntity<TransactionGetResponse> responseEntity = restTemplate.exchange(buildURLwithParameters(URL,transactionGetRequest), HttpMethod.GET, httpEntity,TransactionGetResponse.class);
		
		JRDSPUtil.printObject(responseEntity);

		//TransactionGetResponse transactionGetResponse = buildTransactionGetResponse(accountId, responseEntity);
		return responseEntity.getBody();
		
	}
	
	public NotionalLotActivityBalancesResponse getNotionalDetails(NotionalGetRequest notionalGetRequest) {
		String httpPath="/transaction";
		String URL=jrdspServiceURL+httpPath+"/"+notionalGetRequest.getAccountNumber() + "/" + notionalGetRequest.getTransactionId() + "/notionalActivity";
	
		MultiValueMap<String, String> headers = JRDSPUtil.addHeaders(httpPath+"/notionalActivity", HttpMethod.GET.name(), "application/json", "1.0", JRDSPUtil.generateTraceId());

		HttpEntity httpEntity = new HttpEntity( headers);
		
		
		JRDSPUtil.printObject(httpEntity);

		ResponseEntity<NotionalLotActivityBalancesResponse> responseEntity = restTemplate.exchange(URL, HttpMethod.GET, httpEntity, NotionalLotActivityBalancesResponse.class);
		
		JRDSPUtil.printObject(responseEntity);

		//TransactionGetResponse transactionGetResponse = buildTransactionGetResponse(accountId, responseEntity);
		return responseEntity.getBody();
		
	}


	private String buildURLwithParameters(String URL, TransactionGetRequest transactionGetRequest) {
		
		URL+=String.format("?transactionNumber=%s",transactionGetRequest.getTransactionNumber() == null?"":transactionGetRequest.getTransactionNumber() );
		URL+=String.format("&notionalCategory=%s",transactionGetRequest.getNotionalCategory() == null?"":transactionGetRequest.getNotionalCategory() );
		URL+=String.format("&transactionType=%s",transactionGetRequest.getTransactionType() == null?"":transactionGetRequest.getTransactionType() );
		URL+=String.format("&description=%s",transactionGetRequest.getDescription() == null?"":transactionGetRequest.getDescription() );
		URL+=String.format("&fromDate=%s",transactionGetRequest.getFromDate() == null?"":transactionGetRequest.getFromDate() );
		URL+=String.format("&toDate=%s",transactionGetRequest.getToDate() == null?"":transactionGetRequest.getToDate() );
		
		
		return URL;
		
	}


}
