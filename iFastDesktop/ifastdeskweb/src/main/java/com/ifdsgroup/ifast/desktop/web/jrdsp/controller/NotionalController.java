package com.ifdsgroup.ifast.desktop.web.jrdsp.controller;

import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.List;
import java.util.StringTokenizer;

import org.apache.commons.lang.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import com.ifdsgroup.ifast.desktop.web.jrdsp.config.JrdspConstants;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.CdspRegistration;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.NotionalActivityDto;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.NotionalGetRequest;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.NotionalLotActivityBalancesResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.RdspTransaction;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.TransactionGetRequest;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.TransactionGetResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.TransactionGetResponseDto;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.AccountResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.ActivityDetails;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.AssociatedGrantDto;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.CDSPRegistrationResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.LotIdDetailsDto;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.LotIdDetailsResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.NotionalActivityTotalsDto;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.NotionalBalanceResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.NotionalLotActivityDetailsDto;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.NotionalLotActivityDetailsRequest;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.NotionalLotActivityDetailsResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.RdspTransactions;
import com.ifdsgroup.ifast.desktop.web.jrdsp.service.AccountService;
import com.ifdsgroup.ifast.desktop.web.jrdsp.service.NotionalActivityService;
import com.ifdsgroup.ifast.desktop.web.jrdsp.service.TransactionService;

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
				+ "<Element>		<code>PW,AW</code>		<value>Redemption</value>	</Element>	"
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
				+ "	<Element>		<code>TW</code>		<value>RDSP Termination Withdrawal</value>	</Element>"
				+ "	<Element>		<code>RDSP_TAG</code>		<value>RDSP Termination Adj - Grant</value>	</Element>"
				+ "	<Element>		<code>RDSP_TAB</code>		<value>RDSP Termination Adj - Bond</value>	</Element>"
				+ "	<Element>		<code>RDSP_LC</code>		<value>Loss On Contribution</value>	</Element>"
				+ "	<Element>		<code>RDSP_LB</code>		<value>Loss On Bond</value>	</Element>"
				+ "	<Element>		<code>RDSP_LG</code>		<value>Loss On Grant</value>	</Element>"
				+ "	<Element>		<code>RDSP_LR</code>		<value>Loss On Rollover</value>	</Element>"
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
				+ "	<Element>		<code>TW</code>		<value>RDSP Termination Withdrawal</value>	</Element>"
				+ "	<Element>		<code>RDSP_TAG</code>		<value>RDSP Termination Adj - Grant</value>	</Element>"
				+ "	<Element>		<code>RDSP_TAB</code>		<value>RDSP Termination Adj - Bond</value>	</Element>"
				+ "	<Element>		<code>RDSP_LC</code>		<value>Loss On Contribution</value>	</Element>"
				+ "	<Element>		<code>RDSP_LB</code>		<value>Loss On Bond</value>	</Element>"
				+ "	<Element>		<code>RDSP_LG</code>		<value>Loss On Grant</value>	</Element>"
				+ "	<Element>		<code>RDSP_LR</code>		<value>Loss On Rollover</value>	</Element>"
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
				+ "</List><List listName=\"refilesupress\">	"
				+ "<Element>		<code>Re-file</code>		<value>Re-file</value>	</Element>	"
				+ "<Element>		<code>Suppress</code>		<value>Suppress</value>	</Element>"
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
		            if(!(JrdspConstants.RED_TERMINATION_ADJ_CONTRIB.equalsIgnoreCase(transDto.getRedemptionCode()) 
		            		|| JrdspConstants.RED_TERMINATION_ADJ_ROLLOVER.equalsIgnoreCase(transDto.getRedemptionCode()))) {
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
			aDetails.setRepaymentReason(nResponse.getNotionalLotActivityBalances().getRepaymentReason());
	
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
	
	@RequestMapping(value = "/lotActivity", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
	public NotionalLotActivityDetailsResponse getNotionalLotDetails(@RequestParam(value = "AccountNum", required = true) String accountNumber,
			@RequestParam(value = "NotionalCategory", required = false) String notionalCategory,
			@RequestParam(value = "TransactionType", required = false) String transactionType,
			@RequestParam(value = "FromDate", required = false) String fromDate,
			@RequestParam(value = "ToDate", required = false) String toDate,
			@RequestParam(value = "TransactionNumber", required = false) String transactionNumber,
			@RequestParam(value = "LotId", required = false) String lotId,
			@RequestParam(value = "start", required = true) String start, 
			@RequestParam(value = "count", required = true) String count) {
	 
		NotionalLotActivityDetailsRequest request = new NotionalLotActivityDetailsRequest(accountNumber, notionalCategory,transactionType,fromDate,toDate,transactionNumber,lotId,start,count);
		NotionalLotActivityDetailsResponse nResponse = notionalActivityService.getNotionalLotDetailsResponse(request);

		return nResponse;
	}
	
	// Temp method to load the default values for RDSPNotionalLotInquiry page.
    @RequestMapping(value = "/getNotionalLotConfig", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
	public String getNotionalLotConfigValue() {
		return "<RDSPDropDownResponse><List listName=\"notionalCategory\">	"
				+ "<Element>		<code>ALL</code>		<value>All</value>	</Element>"
				+ "	<Element>		<code>01</code>		<value>Bond</value>	</Element>	"
				+ "<Element>		<code>02</code>		<value>Grant</value>	</Element>	"
				+ "<Element>		<code>03</code>		<value>Contribution</value>	</Element>"
				+ "	<Element>		<code>04</code>		<value>RSP Rollover</value>	</Element>	"
				+ "<Element>		<code>05</code>		<value>RESP Rollover</value>	</Element>	"
				+ "</List><List listName=\"transactionTypeAll\">	"
				+ "<Element>		<code>All</code>		<value>All</value>	</Element>	"
				+ "<Element>		<code>RP</code>		<value>Repayments</value>	</Element>	" 
				+ "<Element>		<code>RT</code>		<value>Returned</value>	</Element> "
				+ "<Element>		<code>ED</code>		<value>Purchases</value>	</Element>	"
				+ "<Element>		<code>PW</code>		<value>Redemptions</value>	</Element>	" 
				+ "</List><List listName=\"transactionTypeGrBd\">  " 
				+ "<Element>		<code>All</code>		<value>All</value>	</Element>	" 
				+ "<Element>		<code>RP</code>		<value>Repayments</value>	</Element>	" 
				+ "<Element>		<code>RT</code>		<value>Returned</value>	</Element> "
				+ "<Element>		<code>ED</code>		<value>Purchases</value>	</Element>	"
				+ "<Element>		<code>PW</code>		<value>Redemptions</value>	</Element>	" 
				+ "</List><List listName=\"transactionType\"> "
				+ "<Element>		<code>All</code>		<value>All</value>	</Element>	"
				+ "<Element>		<code>ED</code>		<value>Purchase</value>	</Element>	"
				+ "<Element>		<code>PW</code>		<value>Redemption</value>	</Element>	" 
				+ "</List></RDSPDropDownResponse>";
	}
    
    @RequestMapping(value ="/getLotIdBalances/{lotId}", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
	public LotIdDetailsDto getLotIdBalances(@PathVariable("lotId")Integer lotId) {
    	LotIdDetailsResponse nResponse = notionalActivityService.getLotIdBalances(lotId);
		
		return nResponse.getLotIdDetailsDto();
	}
    
	@RequestMapping(value = "/updateCdspRegistraion/{refileSupress}/{transId}/", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
	public CdspRegistration updateCdspRegistraion(@PathVariable("refileSupress") String refileSupress,
			@PathVariable("transId") String transactionId) {
		StringTokenizer st = new StringTokenizer(transactionId, ",");
		List<String> list = new ArrayList<String>();
		while (st.hasMoreElements()) {
			list.add((String) st.nextElement());
		}
		notionalActivityService.updateCdspRegistraion(list, refileSupress);
		return null;
	}

}
