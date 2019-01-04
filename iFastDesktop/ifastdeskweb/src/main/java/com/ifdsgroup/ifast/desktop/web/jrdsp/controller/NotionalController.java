package com.ifdsgroup.ifast.desktop.web.jrdsp.controller;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.apache.commons.lang.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.NotionalActivityDto;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.NotionalGetRequest;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.NotionalLotActivityBalancesResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.RdspTransaction;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.TransactionGetRequest;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.TransactionGetResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.TransactionGetResponseDto;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.ActivityDetails;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.AssociatedGrantDto;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.NotionalActivityTotalsDto;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.NotionalBalanceResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.RdspTransactions;
import com.ifdsgroup.ifast.desktop.web.jrdsp.service.NotionalActivityService;
import com.ifdsgroup.ifast.desktop.web.jrdsp.service.TransactionService;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.AccountResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.BaseResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.service.AccountService;

@RestController
@RequestMapping("/notional")
public class NotionalController {
	  
    @Autowired
    private TransactionService transactionService;
    
    @Autowired
	private AccountService accountService;

    @RequestMapping(value = "/user/{userId}/balance/{accountNumber}", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
	public NotionalBalanceResponse getNotionalBalance(
	        @PathVariable String userId, @PathVariable long accountNumber, @RequestParam String toDate,@RequestParam String cycleDate) {
		return transactionService.getNotionalBalance(userId, accountNumber, toDate,cycleDate);
	}
    
    @Autowired
	private NotionalActivityService notionalActivityService;
	
	
	
	// Temp method to load the default values for the page.
    @RequestMapping(value = "/getConfig", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
	public String getConfigValue() {
		return "<RDSPDropDownResponse><List listName=\"transactionType\">	"
				+ "<Element>		<code>ALL</code>		<value>All</value>	</Element>"
				+ "	<Element>		<code>ED</code>		<value>Purchases</value>	</Element>	"
				+ "<Element>		<code>PW</code>		<value>Redemption</value>	</Element>	"
				+ "<Element>		<code>TI</code>		<value>Transfer-In</value>	</Element>"
				+ "</List><List listName=\"description\">	"
				+ "<Element>		<code>All</code>		<value>All</value>	</Element>	"
				+ "<Element>		<code>1</code>		<value>Cash Deposit</value>	</Element>"
				+ "	<Element>		<code>2</code>		<value>PAC</value>	</Element>	"
				+ "<Element>		<code>67</code>		<value>External RDSP to RDSP Transfer</value>	</Element>	"
				+ "<Element>		<code>44</code>		<value>External RSP Rollover to RDSP</value>	</Element>	"
				+ "<Element>		<code>45</code>		<value>External RESP Rollover to RDSP</value>	</Element>	"
				+ "<Element>		<code>46</code>		<value>RDSP Income Adjustment</value>	</Element>	"
				+ "<Element>		<code>47</code>		<value>Internal RSP Rollover to RDSP</value>	</Element>"
				+ "	<Element>		<code>48</code>		<value>Internal RESP Rollover to RDSP</value>	</Element>"
				+ "	<Element>		<code>49</code>		<value>RDSP Grant</value>	</Element>	"
				+ "<Element>		<code>66</code>		<value>RDSP Bond</value>	</Element>"
				+ "	<Element>		<code>RT</code>		<value>External RDSP Transfer</value>	</Element>"
				+ "	<Element>		<code>GP</code>		<value>RDSP Grant Repayment</value>	</Element>	"
				+ "<Element>		<code>BP</code>		<value>RDSP Bond Repayment</value>	</Element>	"
				+ "<Element>		<code>DP</code>		<value>RDSP DAP Payment</value>	</Element>	"
				+ "<Element>		<code>LP</code>		<value>RDSP LDAP Payment</value>	</Element>"
				+ "	<Element>		<code>68</code>		<value>Internal Non-Reg Rollover to RDSP</value>	</Element>"
				+ "<Element>		<code>RG</code>		<value>RDSP Grant Return</value>	</Element>"
				+ "	<Element>		<code>RB</code>		<value>RDSP Bond Return</value>	</Element>"
				+ "	<Element>		<code>RT</code>		<value>Transfer Out</value>	</Element>"
				+ "</List><List listName=\"descriptionRedemption\">	"
				+ "<Element>		<code>All</code>		<value>All</value>	</Element>	"
				+ "<Element>		<code>RT</code>		<value>External RDSP Transfer</value>	</Element>	"
				+ "<Element>		<code>GP</code>		<value>RDSP Grant Repayment</value>	</Element>	"
				+ "<Element>		<code>BP</code>		<value>RDSP Bond Repayment</value>	</Element>	"
				+ "<Element>		<code>DP</code>		<value>RDSP DAP Payment</value>	</Element>"
				+ "	<Element>		<code>LP</code>		<value>RDSP LDAP Payment</value>	</Element>"
				+ "<Element>		<code>RG</code>		<value>RDSP Grant Return</value>	</Element>	"
				+ "<Element>		<code>RB</code>		<value>RDSP Bond Return</value>	</Element>"
				+ "	<Element>		<code>RT</code>		<value>Transfer Out</value>	</Element>"
				+ "</List><List listName=\"descriptionDeposit\">	"
				+ "<Element>		<code>All</code>		<value>All</value>	</Element>"
				+ "	<Element>		<code>1</code>		<value>Cash Deposit</value>	</Element>"
				+ "	<Element>		<code>2</code>		<value>PAC</value>	</Element>	"
				+ "<Element>		<code>67</code>		<value>External RDSP to RDSP Transfer</value>	</Element>"
				+ "	<Element>		<code>44</code>		<value>External RSP Rollover to RDSP</value>	</Element>"
				+ "	<Element>		<code>45</code>		<value>External RESP Rollover to RDSP</value>	</Element>"
				+ "	<Element>		<code>46</code>		<value>RDSP Income Adjustment</value>	</Element>	"
				+ "<Element>		<code>49</code>		<value>RDSP Grant</value>	</Element>	"
				+ "<Element>		<code>66</code>		<value>RDSP Bond</value>	</Element>"
				+ "</List><List listName=\"descriptionTransferIn\">	"
				+ "<Element>		<code>All</code>		<value>All</value>	</Element>	"
				+ "<Element>		<code>47</code>		<value>Internal RSP Rollover to RDSP</value>	</Element>"
				+ "	<Element>		<code>48</code>		<value>Internal RESP Rollover to RDSP</value>	</Element>"
				+ "	<Element>		<code>68</code>		<value>Internal Non-Reg Rollover to RDSP</value>	</Element>"
				+ "</List></RDSPDropDownResponse>";
	}
		
	@RequestMapping(value = "/transactions/{accountNum}", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
	public NotionalActivityDto getTransactionDetails(@PathVariable("accountNum")String accountNum,@RequestParam(value="TransNum", required=false) String transactionNumber,
			@RequestParam(value="NotionalCategory", required=false) String notionalCategory,@RequestParam(value="TransactionType", required=false) String transactionType,
			@RequestParam(value="Description", required=false) String description
			,@RequestParam(value="FromDate", required=false) String fromDate
			,@RequestParam(value="ToDate", required=false) String toDate) {
		
		accountNum= String.format("%s",StringUtils.isBlank(accountNum) ?"": accountNum );
		transactionNumber= String.format("%s",StringUtils.isBlank(transactionNumber) ? "": transactionNumber );
		TransactionGetRequest transactionGetRequest=new TransactionGetRequest(accountNum, transactionNumber, notionalCategory, transactionType, description, fromDate, toDate);
		TransactionGetResponse response=notionalActivityService.getTransactionDetails(accountNum, transactionGetRequest);
		
        /* get Beneficiary Name*/
		AccountResponse accountResponse = (AccountResponse) accountService.getEntityDetails(accountNum);
		String beneName = accountResponse.getEntityInfo().getBeneName();
		
		//Do the mapping for the Code and Status
		
		// hold list of transactions - field names are different than REST service
		NotionalActivityDto notionalActivityDto = new NotionalActivityDto();
		
		notionalActivityDto.setBeneficiaryName(beneName);
		
		List<RdspTransactions> transactions = new ArrayList<RdspTransactions>();
		
		if (null != response.getTransactions() && response.getTransactions().size() > 0) {
			
			TransactionGetResponseDto transDto = null;
			
			Iterator<TransactionGetResponseDto> it = response.getTransactions().iterator();
			
			 while (it.hasNext()) {
		            transDto = it.next();
		            RdspTransaction trans = new RdspTransaction();
		            RdspTransactions trns = new RdspTransactions();
					
		            
		            trans.setTransactionId(Long.toString(transDto.getTransactionId()));
		            trans.setTransactionType(transDto.getRdspTransactionTypeCode());
		            trans.setTransNumber(transDto.getTransactionNumber());
		         //   trans.setNotionalCategory("Contribution");
		            //trans.setNotionalCategory(transDto.getIfastTransactionTypeCode());
		          // trans.setDescription(transDto.get);
		            trans.setDepositCode(transDto.getDepositCode());
		            trans.setRedemptionCode(transDto.getRedemptionCode());
		            trans.setiFastTransactionType(transDto.getIfastTransactionTypeCode());
		            trans.setAccountNumber(transDto.getAccountNumber());
		            trans.setNotionalAmount(transDto.getAmount());
		            trans.setTradeDate(transDto.getEffectiveDate());
		            trans.setPaymentDate(transDto.getPaymentDate());
		            trans.setTransactionStatus(transDto.getTransactionStatusCode());
		            trans.setESDCTransStatus(transDto.getEsdcReportingStatusCode());
		            trans.setESDCTransID(transDto.getEsdcTransactionNumber());
		            trans.setRedemptionCode(transDto.getRedemptionCode());
		            trans.setDepositCode(transDto.getDepositCode());
		            
		            trns.setTransaction(trans);
		            transactions.add(trns);
		    }
			
		}
		
		if (null != transactions && transactions.size() > 0) {
			notionalActivityDto.setTransactions(transactions);
		}
		
		return notionalActivityDto;
		
		
		/* return "<transactions><transaction><TransactionType>2</TransactionType><TransNumber>63468670</TransNumber><NotionalCategory>Contribution</NotionalCategory><Description>PAC</Description><accountNumber>1435221001</accountNumber><NotionalAmount>100</NotionalAmount>"
				+ "<TradeDate>15/05/2016</TradeDate><paymentDate>15/05/2016</paymentDate><TransactionStatus>Processed</TransactionStatus>"
				+ "<ESDCTransStatus>Sent</ESDCTransStatus><ESDCTransID>123</ESDCTransID><redemptionCode>1</redemptionCode><depositCode>1</depositCode></transaction></transactions>";
		 */
		
	}
	
	@RequestMapping(value = "/activity/{accountNum}/{transId}/", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
	public ActivityDetails getNotionalDetails(@PathVariable("accountNum")String accountNum,@PathVariable("transId") String transactionId) {
		
		NotionalGetRequest notionalGetRequest = new NotionalGetRequest(accountNum, transactionId);
		NotionalLotActivityBalancesResponse nResponse = notionalActivityService.getNotionalDetails(notionalGetRequest);
		
		NotionalActivityTotalsDto notionalActivityTotalsDto = new NotionalActivityTotalsDto();
		
		ActivityDetails aDetails = new ActivityDetails();
		
		if (null != nResponse.getNotionalLotActivityBalances()) {
			aDetails.setContributionAmount(nResponse.getNotionalLotActivityBalances().getContributionAmount());
			aDetails.setGrantAmount(nResponse.getNotionalLotActivityBalances().getGrantAmount());
			aDetails.setBondAmount(nResponse.getNotionalLotActivityBalances().getBondAmount());
			aDetails.setRspAmount(nResponse.getNotionalLotActivityBalances().getRspRolloverAmount());
			aDetails.setRespAmount(nResponse.getNotionalLotActivityBalances().getRespRolloverAmount());
			aDetails.setBondPaymentDate(nResponse.getNotionalLotActivityBalances().getBondPaymentDate());
			aDetails.setGrantPaymentDate(nResponse.getNotionalLotActivityBalances().getGrantPaymentDate());
			aDetails.setRdspTransactionTypeCode(nResponse.getNotionalLotActivityBalances().getRdspTransactionTypeCode());
			aDetails.setTotalRolloverAmount(nResponse.getNotionalLotActivityBalances().getTotalRolloverAmount());
	
			AssociatedGrantDto assocGrant = new AssociatedGrantDto();
			
			if (null != nResponse.getNotionalLotActivityBalances().getAssociatedGrant()) {
				assocGrant.setTransNumber(nResponse.getNotionalLotActivityBalances().getAssociatedGrant().getTransactionNumber());
				assocGrant.setAmount(nResponse.getNotionalLotActivityBalances().getAssociatedGrant().getAmount());
				assocGrant.setPaymentDate(nResponse.getNotionalLotActivityBalances().getAssociatedGrant().getPaymentDate());
				
				assocGrant.setRdspTransactionTypeCode(nResponse.getNotionalLotActivityBalances().getRdspTransactionTypeCode());
				aDetails.setAssociatedGrant(assocGrant);
			}
			
		}
		notionalActivityTotalsDto.setActivityDetails(aDetails);
		
		return aDetails;
	//	 return "<ActivityDetails><contributionAmount>10000.00</contributionAmount><grantAmount>20000.00</grantAmount><bondAmount>10000.00</bondAmount><associatedGrant>	<transNumber>234</transNumber>	<amount>5000.00</amount></associatedGrant></ActivityDetails>"; 
		
		 
		
	}
	
	

}
