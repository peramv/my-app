package com.ifdsgroup.ifast.desktop.web.jrdsp.service;

import com.ifdsgroup.ifast.desktop.web.jrdsp.config.JrdspConstants;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.AccountElectionHistoryDto;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.AccountEntityDto;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.AccountRdspDto;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.AccountRdspPutRequest;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.AccountRdspResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.EntityGetResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.EntityRelation;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.EntityType;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.GrantBondPaymentHistoryDto;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.AccountDetails;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.AccountResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.AccountUpdateRequest;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.BaseResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.Election;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.Elections;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.Entities;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.Entity;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.EntityInfo;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.GrantBondPaymentHistory;
import com.ifdsgroup.ifast.desktop.web.jrdsp.util.JRDSPUtil;

import org.apache.commons.collections.CollectionUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpEntity;
import org.springframework.http.HttpMethod;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.util.MultiValueMap;
import org.springframework.web.client.HttpServerErrorException;
import org.springframework.web.client.RestTemplate;

import java.text.ParseException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Date;
import java.util.List;
import java.util.Optional;

@Service
public class AccountService {
	
	@Value("${jrdsp.services.url}")
	private String jrdspServiceURL;
	
	@Autowired
	RestTemplate restTemplate;
	

	
	
	public BaseResponse updateAccountDetails(String accountId, AccountUpdateRequest accountUpdateRequest, String userId, String ignoreErrorCode) {
		String httpPath="/account/rdsp";
		
		String URL=jrdspServiceURL+httpPath+"/"+accountId;
		MultiValueMap<String, String> headers = JRDSPUtil.addHeaders(httpPath, HttpMethod.PUT.name(), "application/json", "1.0", JRDSPUtil.generateTraceId(),userId);

		
		AccountRdspPutRequest accountPutRequest=new AccountRdspPutRequest();
		
		AccountRdspDto accountRdspDto=new AccountRdspDto();
		
		accountRdspDto.setAccountNumber(Long.parseLong(accountId));
		accountRdspDto.setBond(JRDSPUtil.stringToBoolean(accountUpdateRequest.getBondRequested()));
		accountRdspDto.setGrant(JRDSPUtil.stringToBoolean(accountUpdateRequest.getGrantRequested()));
		accountRdspDto.setGrantDate(accountUpdateRequest.getGrantDate());
		accountRdspDto.setInceptionDate(accountUpdateRequest.getInceptionDate());
		accountRdspDto.setReportToESDC(JRDSPUtil.stringToBoolean(accountUpdateRequest.getReportToESDC()));
		accountRdspDto.setTransferredAccount(JRDSPUtil.stringToBoolean(accountUpdateRequest.getTransferredAccount()));
		accountRdspDto.setClosureReasonCode(accountUpdateRequest.getClosureReasonCode());
		accountRdspDto.setAccountUuid(accountUpdateRequest.getAccountUuid());
		accountRdspDto.setAccountStatus(accountUpdateRequest.getAccountStatus());
		accountRdspDto.setDtcStatusCode(accountUpdateRequest.getDtcEligible());
		accountRdspDto.setSdspStatusCode(accountUpdateRequest.getSdspElection());
		accountRdspDto.setDtcElectionStatusCode(accountUpdateRequest.getDtcElection());
		accountRdspDto.setClosureDate(accountUpdateRequest.getClosureDate());
		accountRdspDto.setRegistrationStatusCode(accountUpdateRequest.getContractStatusRegistration());
		accountRdspDto.setSpecifiedYearStatusCode(accountUpdateRequest.getSpecifiedYear());
		accountRdspDto.setCreatedBy(userId);

		if (accountUpdateRequest.getElections() != null
				&& accountUpdateRequest.getElections().getElection() != null) {
            accountRdspDto.setAccountElectionHistories(new ArrayList<>());
            accountUpdateRequest.getElections().getElection().forEach(election ->{
                AccountElectionHistoryDto electionHistory = new AccountElectionHistoryDto();

                electionHistory.setId(election.getId());
                electionHistory.setUuid(election.getUuid());
                electionHistory.setAccountNumber(accountRdspDto.getAccountNumber());
                electionHistory.setCertificationDate(election.getCertificationDate());
                electionHistory.setElectionStatusCode(election.getElected());
                electionHistory.setPeriodEndDate(election.getPeriodEnd());
                electionHistory.setPeriodStartDate(election.getPeriodStart());
                electionHistory.setReportingStatusCode(election.getReportingStatus());
                electionHistory.setCertificationDate(election.getCertificationDate());
                electionHistory.setElectionTypeCode(election.getType());
                electionHistory.setUuid(election.getUuid());
                electionHistory.setTransactionDate(election.getTransactionDate());
                electionHistory.setPeriodStartDate(election.getPeriodStart());
                electionHistory.setPeriodEndDate(election.getPeriodEnd());
                electionHistory.setEffectiveDate(election.getEffective());
                electionHistory.setStatus(election.getStatus());

                accountRdspDto.getAccountElectionHistories().add(electionHistory);
            });
        }
		
		GrantBondPaymentHistoryDto grantHistory = new GrantBondPaymentHistoryDto();
		grantHistory.setAccountNumber(accountId);
		grantHistory.setEffectiveFromDate(accountUpdateRequest.getGrantDate());
		grantHistory.setStatus(accountUpdateRequest.getGrantRequested());
		grantHistory.setPaymentTypeCode("15");
		
		GrantBondPaymentHistoryDto bondHistory = new GrantBondPaymentHistoryDto();
		bondHistory.setAccountNumber(accountId);
		bondHistory.setEffectiveFromDate(accountUpdateRequest.getCycleDate());
		bondHistory.setStatus(accountUpdateRequest.getBondRequested());
		bondHistory.setPaymentTypeCode("03");
		
		accountRdspDto.setAccountGrantBondPaymentHistories(Arrays.asList(grantHistory));

		accountPutRequest.setAccountRdsp(accountRdspDto);
		
		HttpEntity httpEntity = new HttpEntity(accountPutRequest, headers);
		
		JRDSPUtil.printObject(httpEntity);
		ResponseEntity<AccountRdspResponse> responseEntity = restTemplate.exchange(URL, HttpMethod.PUT, httpEntity,AccountRdspResponse.class);
		JRDSPUtil.printObject(responseEntity);

		return getAccountInquiryResponse(accountId, responseEntity);
	}
	
	public BaseResponse getAccountDetails(String accountId) {
		String httpPath="/account/rdsp";
		String URL=jrdspServiceURL+httpPath+"/"+accountId;
	
		MultiValueMap<String, String> headers = JRDSPUtil.addHeaders(httpPath, HttpMethod.GET.name(), "application/json", "1.0", JRDSPUtil.generateTraceId(),"");
		HttpEntity httpEntity = new HttpEntity( headers);
		
		
		JRDSPUtil.printObject(httpEntity);
		ResponseEntity<AccountRdspResponse> responseEntity=null;

		responseEntity = restTemplate.exchange(URL, HttpMethod.GET, httpEntity,AccountRdspResponse.class);

		JRDSPUtil.printObject(responseEntity);
		return getAccountInquiryResponse(accountId, responseEntity);
	}

	private AccountResponse getAccountInquiryResponse(String accountId, ResponseEntity<AccountRdspResponse> responseEntity) {
		AccountRdspDto account = responseEntity.getBody().getAccountRdsp();
		AccountResponse accountResponse=new AccountResponse();

		AccountDetails accountDetails=new AccountDetails();

		accountResponse.setAccountId(accountId);
		if(account!=null)
		{
		accountDetails.setBondRequested(JRDSPUtil.booleanToString(account.getBond()));
		accountDetails.setContractStatusRegistration(account.getRegistrationStatusCode());
		accountDetails.setGrantRequested(JRDSPUtil.booleanToString(account.getGrant()));
		accountDetails.setInceptionDate(account.getInceptionDate());
		accountDetails.setReportToESDC(JRDSPUtil.booleanToString(account.getReportToESDC()));

		accountDetails.setTransferredAccount(JRDSPUtil.booleanToString(account.getTransferredAccount()));
		accountDetails.setClosureReasonCode(account.getClosureReasonCode());
		accountDetails.setAccountStatus(account.getAccountStatus());
		accountDetails.setClosureDate(account.getClosureDate());
		accountDetails.setCreatedBy(account.getCreatedBy());
		accountDetails.setAccountUuid(account.getAccountUuid());
		

		accountDetails.setDtcEligible((account.getDtcStatusCode()==null)?"Yes":account.getDtcStatusCode());
		accountDetails.setDtcElection((account.getDtcElectionStatusCode()==null)?"No":account.getDtcElectionStatusCode());
		accountDetails.setSdspElection((account.getSdspStatusCode()==null)?"No":account.getSdspStatusCode());
		accountDetails.setSpecifiedYear((account.getSpecifiedYearStatusCode()==null)?"No":account.getSpecifiedYearStatusCode());

		accountResponse.setAccountDetails(accountDetails);

		List<AccountElectionHistoryDto> electionsHistoryList=account.getAccountElectionHistories();

		List<Election> electionList=new ArrayList<>();
		Elections elections=new Elections();
		if(electionsHistoryList!=null)
		{
			for(AccountElectionHistoryDto electionHistory:electionsHistoryList)
			{
				Election election=new Election();
				election.setId(electionHistory.getId());
				election.setCertificationDate(electionHistory.getCertificationDate());
				election.setElected(electionHistory.getElectionStatusCode());
				election.setReportingStatus(electionHistory.getReportingStatusCode());
				election.setType(electionHistory.getElectionTypeCode());
				election.setUuid(electionHistory.getUuid());
				election.setTransactionDate(electionHistory.getTransactionDate());
				election.setPeriodStart(electionHistory.getPeriodStartDate());
				election.setPeriodEnd(electionHistory.getPeriodEndDate());
				election.setEffective(electionHistory.getEffectiveDate());
				election.setStatus(electionHistory.getStatus());
                electionList.add(election);
			}
			
			//Sort Based on Transaction Date
			
			
			Comparator<Election> compareEligiblities = (a, b) -> {
				Date dateA = null;
				Date dateB = null;
				try {
					dateA = JRDSPUtil.convertStringToDate(a.getTransactionDate());
					dateB = JRDSPUtil.convertStringToDate(b.getTransactionDate());
				} catch (ParseException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				if(dateB.compareTo(dateA)==0) {
					long idA = a.getId();
					long idB = b.getId();
					return (idB>idA)?1:-1;
				}
				return dateB.compareTo(dateA);
			};
			
			electionList.sort(compareEligiblities);
			elections.setElection(electionList);
		}
		accountResponse.setElections(elections);
		
		List<AccountElectionHistoryDto> dtcEligiblityHistoryList=account.getDtcEligibilityHistories();

		List<Election> dtcEligibilityList=new ArrayList<>();
		Elections dtcEligibilities=new Elections();
		if(dtcEligiblityHistoryList!=null)
		{
			for(AccountElectionHistoryDto eligibilityHistory:dtcEligiblityHistoryList)
			{
				Election eligibility=new Election();
				eligibility.setId(eligibilityHistory.getId());
				eligibility.setCertificationDate(eligibilityHistory.getCertificationDate());
				eligibility.setElected(eligibilityHistory.getElectionStatusCode());
				eligibility.setReportingStatus(eligibilityHistory.getReportingStatusCode());
				eligibility.setType(JRDSPUtil.getEligibilityType(eligibilityHistory.getElectionTypeCode(),eligibilityHistory.getElectionStatusCode()));
				eligibility.setUuid(eligibilityHistory.getUuid());
				eligibility.setTransactionDate(eligibilityHistory.getTransactionDate());
				eligibility.setPeriodStart(eligibilityHistory.getPeriodStartDate());
				eligibility.setPeriodEnd(eligibilityHistory.getPeriodEndDate());
				eligibility.setEffective(eligibilityHistory.getEffectiveDate());
				eligibility.setStatus(eligibilityHistory.getStatus());
				dtcEligibilityList.add(eligibility);
			}
			
			//Sort Based on Transaction Date
			
			
			Comparator<Election> compareElections = (a, b) -> {
				Date dateA = null;
				Date dateB = null;
				try {
					dateA = JRDSPUtil.convertStringToDate(a.getTransactionDate());
					dateB = JRDSPUtil.convertStringToDate(b.getTransactionDate());
				} catch (ParseException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				if(dateB.compareTo(dateA)==0) {
					long idA = a.getId();
					long idB = b.getId();
					return (idB>idA)?1:-1;
				}
				return dateB.compareTo(dateA);
			};
			
			dtcEligibilityList.sort(compareElections);
			dtcEligibilities.setElection(dtcEligibilityList);
			
		}
		accountResponse.setDtcEligiblities(dtcEligibilities);
		
		List<GrantBondPaymentHistoryDto> accountGrantBondPaymentHistories = account.getAccountGrantBondPaymentHistories();

		
		Comparator<GrantBondPaymentHistoryDto> comparator = Comparator.comparing( GrantBondPaymentHistoryDto::getEffectiveFromDate);
		//Sort by EffectiveDate descending
				Comparator<GrantBondPaymentHistoryDto> compareGBPaymentHistory = (a, b) -> {
					Date dateA = null;
					Date dateB = null;
					try {
						dateA = JRDSPUtil.convertStringToDate(a.getEffectiveFromDate());
						dateB = JRDSPUtil.convertStringToDate(b.getEffectiveFromDate());
					} catch (ParseException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					if(dateB.compareTo(dateA)==0) {
						String idA = a.getId();
						String idB = b.getId();
						return (idB.compareTo(idA)>0)?1:-1;
					}
					return dateB.compareTo(dateA);
				};
		
		if(CollectionUtils.isNotEmpty(accountGrantBondPaymentHistories)) {
			accountGrantBondPaymentHistories.sort(compareGBPaymentHistory);
			GrantBondPaymentHistoryDto currentGrant = accountGrantBondPaymentHistories
					.stream()
					.filter(grantBond -> grantBond.getPaymentTypeCode().equals("15"))
					.findFirst().get();
					
			Optional<GrantBondPaymentHistoryDto> lastNoGrant = accountGrantBondPaymentHistories.stream()
					.filter(grantBond -> grantBond.getPaymentTypeCode().equals("15"))
					.filter(grant -> grant.getStatus().equalsIgnoreCase(JrdspConstants.GRANT_BOND_STATUS_NO))
					.findFirst();
			
			String lastNoGrantDate;
				GrantBondPaymentHistory gbHistory = new GrantBondPaymentHistory();
				gbHistory.setAccountNumber(currentGrant.getAccountNumber());
				gbHistory.setPaymentTypeCode(currentGrant.getPaymentTypeCode());
				gbHistory.setStatus(currentGrant.getStatus());
				gbHistory.setEffectiveFromDate(currentGrant.getEffectiveFromDate());
				gbHistory.setEffectiveToDate(currentGrant.getEffectiveToDate());
				gbHistory.setReportingStatusCode(currentGrant.getReportingStatusCode());
				if(lastNoGrant.isPresent()) {
					lastNoGrantDate = lastNoGrant.get().getEffectiveFromDate();
					
				}else {
					lastNoGrantDate = accountDetails.getInceptionDate();
				}
				
				gbHistory.setLastNoGrant(lastNoGrantDate);
				accountDetails.setGrantDate(currentGrant.getEffectiveFromDate());
				accountResponse.setGrantBondHistory(gbHistory);
			
		}
		
		}
		return accountResponse;
	}


	public BaseResponse getEntityDetails(String accountId)  {


		String httpPath1="/account/accountinfo/entity";
		String httpPath2="/account/accountinfo/"+accountId+"/entity";
		String URL=jrdspServiceURL+httpPath2;

		MultiValueMap<String, String> headers = JRDSPUtil.addHeaders(httpPath1, HttpMethod.GET.name(), "application/json", "1.0", JRDSPUtil.generateTraceId(),"");

		HttpEntity httpEntity = new HttpEntity( headers);
		
		JRDSPUtil.printObject(httpEntity);
		ResponseEntity<EntityGetResponse> responseEntity = restTemplate.exchange(URL, HttpMethod.GET, httpEntity,EntityGetResponse.class);

		JRDSPUtil.printObject(responseEntity);
		
		EntityGetResponse entityResponse = responseEntity.getBody();

		List<AccountEntityDto> entities=entityResponse.getEntities();

		if(entities!=null && entities.size() > 0) {
			AccountResponse accountResponse=new AccountResponse();
			EntityInfo entityInfo=new EntityInfo();
			List<Entity> entityList=new ArrayList<>();
			Entities entitiesList=new Entities();
			for(AccountEntityDto entity : entities) {

				// Find Bene and set required Fields
				if(EntityType.BENEFICIARY.getCode().equals(entity.getAccountRoleTypeCode()))
				{
					if(entity.getFirstName()!=null)
					{
						entityInfo.setBeneName(entity.getLastName().concat(", ").concat(entity.getFirstName()));
					}
					else
					{
						entityInfo.setBeneName(entity.getLastName());
					}

					entityInfo.setBeneDateOfDeath(entity.getDateOfDeath());
					entityInfo.setBeneDOB(entity.getDateOfBirth());
					entityInfo.setBeneSIN(entity.getSin());
					entityInfo.setBondEligEndDate(entity.getBondEligibilityEndDate());
					entityInfo.setContributionEndDate(entity.getContributionEndDate());
					entityInfo.setGrantEligEndDate(entity.getGrantEligibilityEndDate());
					entityInfo.setSpecimenPlanNumber("TBD");
					continue;
				}

				// Add relavant fields to all entities

				Entity e1=new Entity();
				if(entity.getFirstName()!=null)
				{
					e1.setName(entity.getLastName().concat(", ").concat(entity.getFirstName()));
				}
				else
				{
					e1.setName(entity.getLastName());
				}

				e1.setSinOrBn(entity.getSin());
				if (entity.getEntityRelationshipTypeCode() != null) {
					e1.setRelationToBene(EntityRelation.valueOf(entity.getEntityRelationshipTypeCode()).getCode());
				}
				e1.setEffectiveDate(entity.getAccountEntityEffFromDate());
			    e1.setEntityType(entity.getAccountRoleTypeCode());

				entityList.add(e1);
			}
			entitiesList.setEntity(entityList);
			entityInfo.setEntities(entitiesList);


			accountResponse.setEntityInfo(entityInfo);

			return accountResponse;
		} else {
			throw new HttpServerErrorException(HttpStatus.NOT_FOUND);
		}
	}
	
	public String getBeneName(long accountNumber) {
		BaseResponse baseResponse=getEntityDetails(String.valueOf(accountNumber));
		if(baseResponse instanceof AccountResponse)
		{
			AccountResponse accountResponse=(AccountResponse)baseResponse;
			
			return (accountResponse.getEntityInfo() != null ? (accountResponse.getEntityInfo().getBeneName() != null ? accountResponse.getEntityInfo().getBeneName() : null) : null);
		}
		else 
			return null;
	}
	
	public String getInceptionDate(String accountId) {
		// TODO Inception date being NULL here means an error!!!
		BaseResponse responseEntity = getAccountInfo(accountId);
		if(responseEntity instanceof AccountResponse)
		{
			AccountResponse accountResponse=(AccountResponse)responseEntity;
			return (accountResponse.getAccountDetails() != null ? (accountResponse.getAccountDetails().getInceptionDate() != null ? accountResponse.getAccountDetails().getInceptionDate() : null ) : null );
		}
		
		return null;
		
	}
	
	private BaseResponse getAccountInfo(String accountId) {
		String httpPath="/account/rdsp";
		String URL=jrdspServiceURL+httpPath+"/"+accountId;
	
		MultiValueMap<String, String> headers = JRDSPUtil.addHeaders(httpPath, HttpMethod.GET.name(), "application/json", "1.0", JRDSPUtil.generateTraceId(),"");
		HttpEntity httpEntity = new HttpEntity( headers);
		
		
		JRDSPUtil.printObject(httpEntity);
		ResponseEntity<AccountRdspResponse> responseEntity=null;

		responseEntity = restTemplate.exchange(URL, HttpMethod.GET, httpEntity,AccountRdspResponse.class);

		return getAccountInquiryResponse(accountId, responseEntity);
	}
}
