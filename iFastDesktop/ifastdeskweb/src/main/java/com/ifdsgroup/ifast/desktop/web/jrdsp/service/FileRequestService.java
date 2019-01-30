package com.ifdsgroup.ifast.desktop.web.jrdsp.service;

import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

import org.apache.commons.beanutils.BeanUtils;
import org.apache.commons.lang.WordUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpEntity;
import org.springframework.http.HttpMethod;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.util.MultiValueMap;
import org.springframework.web.client.RestTemplate;

import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.RecordDetails;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.RecordDetailsResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.RunRecord;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.SetStatusRequest;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.FileRecord;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.TransactionsRecordsResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.util.JRDSPUtil;

@Service
public class FileRequestService {
	
	@Value("${jrdsp.services.url}")
	private String jrdspServiceURL;
	
	@Autowired
	RestTemplate restTemplate;

	public TransactionsRecordsResponse getTransactions(long account, String inout, String type, String status,
																		 long start, int count) {
		String httpPath = "/fileTransactions";
		String URL = String.format("%s%s?accountNumber=%d&fileType=%s&recordType=%s&status=%s&start=%d&count=%d", jrdspServiceURL,
								httpPath, account, inout, type, status, start, count);
		MultiValueMap<String, String> headers = JRDSPUtil.addHeaders(httpPath, HttpMethod.GET.name(),
								MediaType.APPLICATION_JSON_VALUE, "1.0", JRDSPUtil.generateTraceId(),"");
		
		HttpEntity<Object> httpEntity = new HttpEntity<>(headers);	
		ResponseEntity<TransactionsRecordsResponse> response = restTemplate.exchange(URL, HttpMethod.GET,
															httpEntity, TransactionsRecordsResponse.class);
		return response.getBody();
	}
	
	
	public RecordDetails getRecordDetails(long eventId, int rowNum) throws IllegalAccessException, InvocationTargetException {
		
		String httpPath = "/recordDetails";
		String URL=jrdspServiceURL + httpPath + "/" + eventId + "/" + rowNum;
		MultiValueMap<String, String> headers = JRDSPUtil.addHeaders(httpPath, HttpMethod.GET.name(),
								MediaType.APPLICATION_JSON_VALUE, "1.0", JRDSPUtil.generateTraceId(),"");
		
		HttpEntity httpEntity = new HttpEntity<>(headers);	
		ResponseEntity<RecordDetailsResponse> response = restTemplate.exchange(URL, HttpMethod.GET,
															httpEntity, RecordDetailsResponse.class);
		
		RecordDetails recordDetails = populateRecordDetails(response.getBody()) ;
		return recordDetails;
	}
	
	public RecordDetails populateRecordDetails(RecordDetailsResponse recordDetailsResponse) throws IllegalAccessException, InvocationTargetException {
		RecordDetails recordDetails = new RecordDetails();
		
		if(recordDetailsResponse.getRecordDetails()!=null) {
			 Map<String, String> recordDetailsMap = new HashMap<>();
			 
			 for(Entry entry : recordDetailsResponse.getRecordDetails().entrySet()) {
				 String[] sbArray = entry.getKey().toString().split(" ");
				 StringBuilder builder = new StringBuilder(sbArray[0]);
				 for(int i=1; i< sbArray.length; i++) {					 
					 builder.append(WordUtils.capitalizeFully(sbArray[i]));
				 }
				 
				 recordDetailsMap.put(builder.toString(), entry.getValue().toString());
			 }
			 recordDetails = setData(recordDetails, recordDetailsMap);
		}
		return recordDetails;		
	}
	
	public RecordDetails setData(RecordDetails recordDetails, Map<String, String> fields) throws IllegalAccessException, InvocationTargetException {
		   for(Entry<String, String> entry : fields.entrySet()) {
		      BeanUtils.setProperty(recordDetails, entry.getKey(), entry.getValue());
		   }
		   return recordDetails;
		}
	public List<LinkedHashMap<String, Object>> setStatus(List<FileRecord> records) {
		String httpPath = "/file/status";
		String URL = String.format("%s%s", jrdspServiceURL, httpPath);
		MultiValueMap<String, String> headers = JRDSPUtil.addHeaders(httpPath, HttpMethod.PUT.name(),
								MediaType.APPLICATION_JSON_VALUE, "1.0", JRDSPUtil.generateTraceId(),"");
		
		SetStatusRequest request = new SetStatusRequest();
		request.setRecords(records);

		HttpEntity<SetStatusRequest> httpEntity = new HttpEntity<>(request, headers);
		ResponseEntity<List> response = restTemplate.exchange(URL, HttpMethod.PUT, httpEntity, List.class);
		return response.getBody();
	}
	
	public List<LinkedHashMap<String, Object>> getLatestRuns() {
		String httpPath = "/latestRuns";
		String URL = String.format("%s%s", jrdspServiceURL, httpPath);
		MultiValueMap<String, String> headers = JRDSPUtil.addHeaders(httpPath, HttpMethod.GET.name(),
								MediaType.APPLICATION_JSON_VALUE, "1.0", JRDSPUtil.generateTraceId(),"");
		
		HttpEntity<SetStatusRequest> httpEntity = new HttpEntity<>(headers);
		ResponseEntity<List> response = restTemplate.exchange(URL, HttpMethod.GET, httpEntity, List.class);
		return response.getBody();
	}
}