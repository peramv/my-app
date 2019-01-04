package com.ifdsgroup.ifast.desktop.web.jrdsp.service;


import java.math.BigDecimal;
import java.math.RoundingMode;

import org.apache.commons.lang3.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpEntity;
import org.springframework.http.HttpMethod;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.util.MultiValueMap;
import org.springframework.web.client.RestTemplate;

import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.RdspTransferDetailDto;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.TransferRdspPutRequest;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.TransferRdspResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.TransferUpdateRequest;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.Transfers;
import com.ifdsgroup.ifast.desktop.web.jrdsp.util.JRDSPUtil;


@Service
public class TransferInService {

	@Value("${jrdsp.services.url}")
	private String jrdspServiceURL;
	
	@Autowired
	RestTemplate restTemplate;
	

	
	/**
	 * Method to invoke JRDSP rest api to get TransferIn details. 
	 *
	 * @param  accountId  TransferIn transaction accountNumber 
	 * @param  transactionId TransferIn transaction Id
	 * @return  Transfers Complete TransferIn details
	 */
	public Transfers getTransferInDetails(String accountId, String transactionId) {
		String httpPath="/transaction";
		String URL=jrdspServiceURL + httpPath + "/" + accountId + "/" + transactionId + "/transfer";
	
		MultiValueMap<String, String> headers = JRDSPUtil.addHeaders(httpPath+"/transfer", HttpMethod.GET.name(), "application/json", "1.0", JRDSPUtil.generateTraceId());
		HttpEntity httpEntity = new HttpEntity(headers);	
		
		ResponseEntity<TransferRdspResponse> responseEntity = restTemplate.exchange(URL, HttpMethod.GET, httpEntity,TransferRdspResponse.class);
		Transfers transfersResponse = getTransfersRdsp(accountId, responseEntity);
		return transfersResponse;
	}
	
	/**
	 * Method to map REST api response object to Transfers object
	 *
	 * @param  responseEntity  reponse from Rest api 
	 * @return  Transfers Complete TransferIn details
	 */
	private Transfers getTransfersRdsp(String accountId, ResponseEntity<TransferRdspResponse> responseEntity) {
		RdspTransferDetailDto transfersRdsp = responseEntity.getBody().getRdspTransferDetail();
		Transfers transfers=new Transfers();
		
		if(transfersRdsp!=null) {
			transfers.setAccountNumber(transfersRdsp.getAccountNumber());
			transfers.setTransactionId(transfersRdsp.getTransactionId());
			transfers.setExtRDSPContNum(transfersRdsp.getExternalContractNumber());
			transfers.setExtSpecimenPlanNum(transfersRdsp.getExternalSpecimenPlanNumber());
			transfers.setInternalRDSPContNum(transfersRdsp.getContractNumber());
			transfers.setInternalSpecimenPlanNum(transfersRdsp.getSpecimenPlanNumber());
			transfers.setNonTaxablePrivateCntbns(scaleValue(transfersRdsp.getTotalPayments()));
			transfers.setCanadaDisabilitySavingsGrant(scaleValue(transfersRdsp.getGrantAmount()));
			transfers.setTaxableReportsRollovers(scaleValue(transfersRdsp.getRolloverAmount()));
			transfers.setCanadaDisabilitySavingsBond(scaleValue(transfersRdsp.getBondAmount()));
			transfers.setFairMarketValue(scaleValue(transfersRdsp.getOpeningFmv()));
			transfers.setGrantBondsPaid(scaleValue(transfersRdsp.getYearEndCdsaAmount()));
			transfers.setContributions(scaleValue(transfersRdsp.getYearEndContributionsAmount()));		
			transfers.setNonTaxablePriorDapLdap(scaleValue(transfersRdsp.getPriorYearRedemptionNonTaxableAmount()));
			transfers.setNonTaxablePresentDapLdap(scaleValue(transfersRdsp.getCurrentYearRedemptionNonTaxableAmount()));
			transfers.setTaxablePriorDapLdap(scaleValue(transfersRdsp.getPriorYearRedemptionTaxableAmount()));
			transfers.setTaxablePresentDapLdap(scaleValue(transfersRdsp.getCurrentYearRedemptionTaxableAmount()));
			transfers.setMoneyOutTrade(transfersRdsp.getMoneyOutTrade());
			transfers.setTransferInStatusTypeCode(transfersRdsp.getTransferInStatusTypeCode());	
			transfers.setTransactionStatusCode(transfersRdsp.getTransactionStatusCode());
			transfers.setFormEditableFlag(evaluateFormEditFlag(transfersRdsp));
		}
				
		return transfers;
	}
	
	/**
	 * Method to invoke JRDSP rest api to update TransferIn details. 
	 *
	 * @param  accountId  TransferIn transaction accountNumber 
	 * @param  transactionId TransferIn transaction Id
	 * @param transferUpdateRequest updated transferIn details object
	 * @ignoreErrorCode
	 * @return  Transfers Complete TransferIn details
	 */
	public Transfers updateTransferInDetails(String accountId, String transactionId, TransferUpdateRequest transferUpdateRequest, String ignoreErrorCode) {
		String httpPath="/transaction";
		String URL=jrdspServiceURL + httpPath + "/" + accountId + "/" + transactionId + "/transfer";
		MultiValueMap<String, String> headers = JRDSPUtil.addHeaders(httpPath+"/transfer", HttpMethod.PUT.name(), "application/json", "1.0", JRDSPUtil.generateTraceId());
		
		TransferRdspPutRequest transferRdspPutRequest = new TransferRdspPutRequest();	
		RdspTransferDetailDto rdspTransferDetailDto = new RdspTransferDetailDto();
		
		rdspTransferDetailDto.setAccountNumber(transferUpdateRequest.getAccountNumber());
		rdspTransferDetailDto.setTransactionId(transferUpdateRequest.getTransactionId());
		rdspTransferDetailDto.setExternalContractNumber(transferUpdateRequest.getExtRDSPContNum());
		rdspTransferDetailDto.setExternalSpecimenPlanNumber(transferUpdateRequest.getExtSpecimenPlanNum());
		rdspTransferDetailDto.setOpeningFmv(transferUpdateRequest.getFairMarketValue());
		rdspTransferDetailDto.setYearEndCdsaAmount(transferUpdateRequest.getGrantBondsPaid());
		rdspTransferDetailDto.setYearEndContributionsAmount(transferUpdateRequest.getContributions());
		rdspTransferDetailDto.setPriorYearRedemptionTaxableAmount(transferUpdateRequest.getTaxablePriorDapLdap());		
		rdspTransferDetailDto.setPriorYearRedemptionNonTaxableAmount(transferUpdateRequest.getNonTaxablePriorDapLdap());		
		rdspTransferDetailDto.setCurrentYearRedemptionTaxableAmount(transferUpdateRequest.getTaxablePresentDapLdap());
		rdspTransferDetailDto.setCurrentYearRedemptionNonTaxableAmount(transferUpdateRequest.getNonTaxablePresentDapLdap());
		rdspTransferDetailDto.setContractNumber(transferUpdateRequest.getInternalRDSPContNum());
		rdspTransferDetailDto.setSpecimenPlanNumber(transferUpdateRequest.getInternalSpecimenPlanNum());
		rdspTransferDetailDto.setRolloverAmount(transferUpdateRequest.getTaxableReportsRollovers());
		rdspTransferDetailDto.setGrantAmount(transferUpdateRequest.getCanadaDisabilitySavingsGrant());		
		rdspTransferDetailDto.setBondAmount(transferUpdateRequest.getCanadaDisabilitySavingsBond());
		rdspTransferDetailDto.setTotalPayments(transferUpdateRequest.getNonTaxablePrivateCntbns());
		rdspTransferDetailDto.setMoneyOutTrade(transferUpdateRequest.getMoneyOutTrade());
		rdspTransferDetailDto.setTransferInStatusTypeCode(transferUpdateRequest.getTransferInStatusTypeCode());		
			
		transferRdspPutRequest.setRdspTransferDetail(rdspTransferDetailDto);		
		HttpEntity httpEntity = new HttpEntity(transferRdspPutRequest, headers);		
		ResponseEntity<TransferRdspResponse> responseEntity = null;
		responseEntity = restTemplate.exchange(URL, HttpMethod.PUT, httpEntity,TransferRdspResponse.class);
		Transfers transfers = getTransfersRdsp(accountId, responseEntity);
		
		return transfers;
	}
	
	/**
	 * Method to decide whether edits allowed on screen based on response details
	 *
	 * @param  response  TransferIn details from JRDSP PUT rest api
	 * @return  Boolean decides either to allow edits on Transfer in screen
	 */
	private Boolean evaluateFormEditFlag(RdspTransferDetailDto response) {
		Boolean editAllowFlag = false;
		String status = response.getTransferInStatusTypeCode();
		
		if(!StringUtils.isEmpty(response.getTransactionStatusCode()) && !response.getTransactionStatusCode().equalsIgnoreCase("03")
				&& !response.getTransactionStatusCode().equalsIgnoreCase("04")) {
			if(!StringUtils.isEmpty(status)) {		
				//After Notional details received from government (NTRF - Notional Transactions received and Reconciliation False (not reconciled) )
				if(status.equalsIgnoreCase("NTRF")) {
					if(!response.getMoneyOutTrade()) {
						editAllowFlag = true;
					}
				} 
				//Before Notional details received from government (TN - Transaction details Not received)
				else if(status.equalsIgnoreCase("NFRF")){
/*					if(!response.getMoneyOutTrade() && response.getEsdcSent().equals(response.getEsdcResponse())) {
						editAllowFlag = true;
					}*/
					if(!response.getMoneyOutTrade() && (response.getCdspRegStatus() == null || response.getCdspRegStatus().equals("ACKNOWLEDGED"))) {
						editAllowFlag = true;
					}
					
				}
			}		
		}
		return editAllowFlag;
	}
	
	private BigDecimal scaleValue(BigDecimal value) {
		if(value!=null) {
			value = value.setScale(2, RoundingMode.HALF_UP);
		}
		return value;		
	}
}
