package com.ifdsgroup.ifast.desktop.web.jrdsp.service;

import java.util.ArrayList;
import java.util.Date;
import java.util.Formatter;
import java.util.List;
import java.util.stream.Collectors;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpEntity;
import org.springframework.http.HttpMethod;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.util.MultiValueMap;
import org.springframework.web.client.RestTemplate;

import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.CDSPRegistrationRequest;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.NotionalGetRequest;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.NotionalLotActivityBalancesResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.TransactionGetRequest;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.TransactionGetResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.TransferRdspResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.CDSPRegistrationResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.LotIdDetailsDto;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.LotIdDetailsResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.NotionalBalanceResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.NotionalLotActivityDetailsDto;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.NotionalLotActivityDetailsRequest;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.NotionalLotActivityDetailsResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.Transfers;
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
	
		MultiValueMap<String, String> headers = JRDSPUtil.addHeaders(httpPath, HttpMethod.GET.name(), "application/json", "1.0", JRDSPUtil.generateTraceId(),"");

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
	
		MultiValueMap<String, String> headers = JRDSPUtil.addHeaders(httpPath+"/notionalActivity", HttpMethod.GET.name(), "application/json", "1.0", 
				JRDSPUtil.generateTraceId(),"");

		HttpEntity httpEntity = new HttpEntity( headers);
		
		
		JRDSPUtil.printObject(httpEntity);

		ResponseEntity<NotionalLotActivityBalancesResponse> responseEntity = restTemplate.exchange(URL, HttpMethod.GET, httpEntity, NotionalLotActivityBalancesResponse.class);
		
		JRDSPUtil.printObject(responseEntity);

		//TransactionGetResponse transactionGetResponse = buildTransactionGetResponse(accountId, responseEntity);
		return responseEntity.getBody();
		
	}
	
	public NotionalLotActivityDetailsResponse getNotionalLotDetailsResponse(NotionalLotActivityDetailsRequest request) {
		String httpPath="/notionalLotActivity";
		String URL=jrdspServiceURL+httpPath+"/"+request.getAccountNumber();
	
		MultiValueMap<String, String> headers = JRDSPUtil.addHeaders(httpPath, HttpMethod.GET.name(), "application/json", "1.0", JRDSPUtil.generateTraceId(),"");

		HttpEntity httpEntity = new HttpEntity( headers);
		ResponseEntity<NotionalLotActivityDetailsResponse> responseEntity = restTemplate.exchange(buildNotionalLotDetailsURL(URL, request), HttpMethod.GET, httpEntity,NotionalLotActivityDetailsResponse.class);
		List<NotionalLotActivityDetailsDto> notionalLotActivityDetails = new ArrayList<>();
		
		if(responseEntity.getBody()!=null && responseEntity.getBody().getNotionalLotActivityDetails()!=null) {
			notionalLotActivityDetails = responseEntity.getBody().getNotionalLotActivityDetails().stream().filter(a -> !a.getNotionalCategory().equalsIgnoreCase("06")).collect(Collectors.toList());
		}
		
		responseEntity.getBody().setNotionalLotActivityDetails(notionalLotActivityDetails);
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
	
	private String buildNotionalLotDetailsURL(String URL, NotionalLotActivityDetailsRequest request) {
		URL+=String.format("?accountNumber=%s",request.getAccountNumber() == null?"":request.getAccountNumber());
		URL+=String.format("&notionalCategory=%s",request.getNotionalCategory() == null?"":request.getNotionalCategory() );
		URL+=String.format("&transactionType=%s",request.getTransactionType() == null?"":request.getTransactionType() );
		URL+=String.format("&fromDate=%s",request.getFromDate() == null?"":request.getFromDate() );
		URL+=String.format("&toDate=%s",request.getToDate() == null?"":request.getToDate() );
		URL+=String.format("&transactionNumber=%s",request.getTransactionNumber() == null?"":request.getTransactionNumber() );
		URL+=String.format("&lotId=%s",request.getLotId() == null?"":request.getLotId());
		URL+=String.format("&start=%s",request.getStart() == null?"":request.getStart());
		URL+=String.format("&count=%s",request.getCount() == null?"":request.getCount());
		
		
		return URL;
		
	}
	
	public LotIdDetailsResponse getLotIdBalances(Integer lotId) {
		String httpPath="/notionalLotActivity/balances";
		String URL=jrdspServiceURL+httpPath+"/"+lotId;
	
		MultiValueMap<String, String> headers = JRDSPUtil.addHeaders(httpPath, HttpMethod.GET.name(), "application/json", "1.0", JRDSPUtil.generateTraceId(),"");

		HttpEntity httpEntity = new HttpEntity( headers);
		ResponseEntity<LotIdDetailsResponse> responseEntity = restTemplate.exchange(URL, HttpMethod.GET, httpEntity, LotIdDetailsResponse.class);

		return responseEntity.getBody();
	}

	public ResponseEntity<CDSPRegistrationResponse> updateCdspRegistraion(List<String> records, String refileSupress) {
		String httpPath = "/account/cdspUpdate";
		String URL = String.format("%s%s", jrdspServiceURL, httpPath);
		MultiValueMap<String, String> headers = JRDSPUtil.addHeaders(httpPath, HttpMethod.POST.name(),
				MediaType.APPLICATION_JSON_VALUE, "1.0", JRDSPUtil.generateTraceId(), "");
		CDSPRegistrationRequest request = new CDSPRegistrationRequest();
		request.setTransactioID(records);
		request.setRefileSupress(refileSupress);
		HttpEntity<CDSPRegistrationRequest> httpEntity = new HttpEntity<>(request, headers);
		ResponseEntity<CDSPRegistrationResponse> response = restTemplate.exchange(URL, HttpMethod.POST, httpEntity,
				CDSPRegistrationResponse.class);
		return response;
	}
	

}
