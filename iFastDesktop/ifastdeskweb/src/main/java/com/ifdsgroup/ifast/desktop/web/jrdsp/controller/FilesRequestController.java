package com.ifdsgroup.ifast.desktop.web.jrdsp.controller;

import java.lang.reflect.InvocationTargetException;
import java.util.LinkedHashMap;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.LatestRunsResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.RecordDetails;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.SetStatusResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.StatusUpdateRequest;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.TransactionsRecordsResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.service.FileRequestService;

@RestController
@RequestMapping("/files")
public class FilesRequestController {
	@Autowired
	FileRequestService filesService;
	
	@RequestMapping(value = "/fileTransactions", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
    public ResponseEntity<TransactionsRecordsResponse> getRecords(@RequestParam("accountNumber") long accountNumber, @RequestParam("fileType") String fileType,
    		@RequestParam("recordType") String recordType, @RequestParam("status") String status,
								@RequestParam("start") long start, @RequestParam("count") int count) {
		TransactionsRecordsResponse response = filesService.getTransactions(accountNumber, fileType, recordType, status, start, count);
		return ResponseEntity.ok().body(response);
	}
	@RequestMapping(value = "/recordDetails/{eventId}/{rowNum}", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
    public ResponseEntity<RecordDetails> getRecordDetails(@PathVariable long eventId, @PathVariable int rowNum) throws IllegalAccessException, InvocationTargetException {
		RecordDetails response = filesService.getRecordDetails(eventId, rowNum);
		return ResponseEntity.ok().body(response);
	}
	
	@RequestMapping(value = "/status", method = RequestMethod.POST, produces = MediaType.APPLICATION_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
    public ResponseEntity<SetStatusResponse> setStatus(@RequestBody StatusUpdateRequest request) {
		List<LinkedHashMap<String, Object>> res = filesService.setStatus(request.getRecord());
		return ResponseEntity.ok().body(SetStatusResponse.toXML(res));
	}
	
	@RequestMapping(value = "/latestRuns", method = RequestMethod.POST, produces = MediaType.APPLICATION_XML_VALUE)
    public ResponseEntity<LatestRunsResponse> getLatestRuns() {
		List<LinkedHashMap<String, Object>> res = filesService.getLatestRuns();
		return ResponseEntity.ok().body(LatestRunsResponse.toXML(res));
	}
	
	@RequestMapping(value = "/getConfig", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
	public String getConfig() {
		return "<config>\n" + 
				"	<List listName=\"FileTypes\">\n" + 
				"		<Element><code>01</code><value>Outgoing</value></Element>\n" + 
				"		<Element><code>02</code><value>Incoming</value></Element>\n" + 
				"		<Element><code>All</code><value>All</value></Element>\n" + 
				"	</List>\n" + 
				"	<List listName=\"RecordTypes\">\n" + 
				"		<Element fileType=\"all\"><code>All</code><value>All</value></Element>\n" + 
				"		<Element fileType=\"outgoing\"><code>101</code><value>RT101</value></Element>\n" + 
				"		<Element fileType=\"outgoing\"><code>102</code><value>RT102</value></Element>\n" + 
				"		<Element fileType=\"outgoing\"><code>201</code><value>RT201</value></Element>\n" + 
				"		<Element fileType=\"outgoing\"><code>202</code><value>RT202</value></Element>\n" + 
				"		<Element fileType=\"outgoing\"><code>401</code><value>RT401</value></Element>\n" + 
				"		<Element fileType=\"outgoing\"><code>501</code><value>RT501</value></Element>\n" + 
				"		<Element fileType=\"outgoing\"><code>701</code><value>RT701</value></Element>\n" + 
				"		<Element fileType=\"incoming\"><code>801</code><value>RT801</value></Element>\n" + 
				"		<Element fileType=\"incoming\"><code>851</code><value>RT851</value></Element>\n" + 
				"		<Element fileType=\"incoming\"><code>901</code><value>RT901</value></Element>\n" + 
				"		<Element fileType=\"incoming\"><code>921</code><value>RT921</value></Element>\n" +
				"		<Element fileType=\"incoming\"><code>951</code><value>RT951</value></Element>\n" + 
				"		<Element fileType=\"incoming\"><code>952</code><value>RT952</value></Element>\n" +
				"		<Element fileType=\"incoming\"><code>953</code><value>RT953</value></Element>\n" +
				"		<Element fileType=\"incoming\"><code>971</code><value>RT971</value></Element>\n" +
				"	</List>\n" +
				"	<List listName=\"Statuses\">\n" + 
				"		<Element><code>All</code><value>All</value></Element>\n" + 
				"		<Element><code>New</code><value>New</value></Element>\n" + 
				"		<Element><code>Hold</code><value>Hold</value></Element>\n" + 
				"		<Element><code>ReadyToSend</code><value>Ready To Send</value></Element>\n" + 
				"		<Element><code>Rejected</code><value>Rejected</value></Element>\n" + 
				"		<Element><code>Refused</code><value>Refused</value></Element>\n" + 
				"		<Element><code>Failed</code><value>Failed</value></Element>\n" + 
				"		<Element><code>Sent</code><value>Sent</value></Element>\n" + 
				"		<Element><code>Accepted</code><value>Accepted</value></Element>\n" + 
				"	</List>\n" + 
				"	<List listName=\"NewStatuses\">\n" + 
				"		<Element><code>Hold</code><value>Hold</value></Element>\n" + 
				"		<Element><code>ReadyToSend</code><value>Ready To Send</value></Element>\n" + 
				"	</List>\n" + 
				"</config>";
	}
	
	@RequestMapping(value = "/getEventLogErrors", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
	public String getEventLogErrors() {
		return "<eventLogErrors>\n" + 
				"	<List listName=\"Errors\">\n" + 
				"		<Element><code>10000</code><value>City is mandatory</value></Element>\n" +	
				"		<Element><code>10001</code><value>Province mandatory for Canadian resident</value></Element>\n" +
				"		<Element><code>10002</code><value>Country is mandatory</value></Element>\n" +	
				"		<Element><code>10003</code><value>Postal Code mandatory for Canadian resident</value></Element>\n" +	
				"		<Element><code>10004</code><value>Invalid SIN or Business Number</value></Element>\n" +	
				"		<Element><code>10005</code><value>Invalid Account holder relationship with beneficiary</value></Element>\n" +	
				"		<Element><code>100050</code><value>MoneyOut transactions are present after the original transaction</value></Element>\n" +	
				"		<Element><code>100052</code><value>Required Parameter is missing</value></Element>\n" +
				"		<Element><code>10006</code><value>Contract sign date is mandatory</value></Element>\n" +	
				"		<Element><code>10007</code><value>Contract sign date before 2008-12-1</value></Element>\n" +	
				"		<Element><code>10008</code><value>Contract sign date before Beneficiary DOB</value></Element>\n" +	
				"		<Element><code>10009</code><value>Contract Creation Date must be on or after Contract Signature date.</value></Element>\n" +	
				"		<Element><code>10014</code><value>Contract sign date after account holder effective date</value></Element>\n" +	
				"		<Element><code>10050</code><value>MoneyOut transactions are present after the original transaction</value></Element>\n" +	
				"		<Element><code>10060</code><value>Certificate Date must be before the reporting Date</value></Element>\n" +	
				"		<Element><code>10061</code><value>Account has DTC Ineligible period of more than 5 years</value></Element>\n" +	
				"		<Element><code>10062</code><value>Account has overlapping Episodic DTC elections</value></Element>\n" +	
				"		<Element><code>10063</code><value>Certification Date cannot be null</value></Element>\n" +	
				"		<Element><code>10064</code><value>Beneficiary Date of Birth cannot be null</value></Element>\n" +	
				"		<Element><code>10066</code><value>Transaction Date cannot be prior to Inception date</value></Element>\n" +	
				"		<Element><code>10067</code><value>Transaction Date cannot be prior to Beneficiary birth date</value></Element>\n" +	
				"		<Element><code>10068</code><value>Transaction Date must be before the reporting Date</value></Element>\n" +	
				"		<Element><code>10081</code><value>No Validation is performed in JRDSP</value></Element>\n" +	
				"		<Element><code>10082</code><value>Associated TransactionNum Validation Failed.</value></Element>\n" +	
				"		<Element><code>10083</code><value>Repayment reason does not have validation.</value></Element>\n" +	
				"		<Element><code>2049</code><value>Beneficiary must be a Canadian resident</value></Element>\n" +	
				"		<Element><code>2050</code><value>Beneficiary must be no more than 59</value></Element>\n" +	
				"		<Element><code>2051</code><value>Primary Care Giver is mandatory as beneficiary is minor</value></Element>\n" +	
				"		<Element><code>2071</code><value>Beneficiary must be a Canadian resident</value></Element>\n" +	
				"		<Element><code>2072</code><value>Beneficiary must be no more than 59 years of age</value></Element>\n" +	
				"		<Element><code>2090</code><value>Trade not allowed for a RDSP account SDSP elect</value></Element>\n" +	
				"		<Element><code>2091</code><value>Trade not allowed for a RDSP account DTC elect</value></Element>\n" +	
				"		<Element><code>2092</code><value>RDSP Registration Status doesn't allow contributions</value></Element>\n" +	
				"		<Element><code>2093</code><value>Trade date is after Beneficiary's Date of Death</value></Element>\n" +	
				"		<Element><code>2094</code><value>RDSP Maximum Contributions LTA exceeded</value></Element>\n" +	
				"		<Element><code>2095</code><value>Invalid deposit and redemption code combination</value></Element>\n" +	
				"		<Element><code>2098</code><value>Closure Date is invalid.</value></Element>\n" +	
				"		<Element><code>2101</code><value>Invalid Date Format</value></Element>\n" +	
				"		<Element><code>2102</code><value>EffectiveDate is required</value></Element>\n" +	
				"		<Element><code>2103</code><value>RuserId is required</value></Element>\n" +	
				"		<Element><code>2104</code><value>AccountNumber should be a positive number</value></Element>\n" +
				"		<Element><code>2105</code><value>Entity is required</value></Element>\n" +	
				"		<Element><code>2106</code><value>AccountEntity is required</value></Element>\n" +	
				"		<Element><code>2107</code><value>FirstName is required</value></Element>\n" +	
				"		<Element><code>2108</code><value>LastName is required</value></Element>\n" +	
				"		<Element><code>2109</code><value>DOB is required</value></Element>\n" +	
				"		<Element><code>2110</code><value>Sex is required</value></Element>\n" +	
				"		<Element><code>2111</code><value>Language is required</value></Element>\n" +	
				"		<Element><code>2112</code><value>SIN is required</value></Element>\n" +	
				"		<Element><code>2113</code><value>BusinessNumber is required</value></Element>\n" +	
				"		<Element><code>2114</code><value>AgencyName is required</value></Element>\n" +
				"		<Element><code>2115</code><value>Beneficiary is required</value></Element>\n" +	
				"		<Element><code>2116</code><value>Invalid relationship to beneficiary</value></Element>\n" +	
				"		<Element><code>2117</code><value>Only 2 pcgs are allowed</value></Element>\n" +	
				"		<Element><code>2118</code><value>Beneficiary can not be more than one</value></Element>\n" +	
				"		<Element><code>2119</code><value>CreatedBy is required</value></Element>\n" +	
				"		<Element><code>2120</code><value>CreatedDate is required</value></Element>\n" +	
				"		<Element><code>2121</code><value>ClientCode is required</value></Element>\n" +	
				"		<Element><code>2122</code><value>Category is invalid</value></Element>\n" +	
				"		<Element><code>2123</code><value>Invalid gender</value></Element>\n" +	
				"		<Element><code>2124</code><value>Taxjurisdiction is required</value></Element>\n" +	
				"		<Element><code>2125</code><value>Invalid TaxJurisdiction</value></Element>\n" +	
				"		<Element><code>2126</code><value>Invalid consent</value></Element>\n" +	
				"		<Element><code>2127</code><value>Invalid entityType</value></Element>\n" +	
				"		<Element><code>2132</code><value>Account Number is invalid</value></Element>\n" +	
				"		<Element><code>2133</code><value>EntityID is invalid</value></Element>\n" +	
				"		<Element><code>2134</code><value>Account Number already exists</value></Element>\n" +	
				"		<Element><code>2136</code><value>Attribute Type should not be empty</value></Element>\n" +	
				"		<Element><code>2137</code><value>Attribute Value should not be null</value></Element>\n" +	
				"		<Element><code>2138</code><value>Invalid attribute type</value></Element>\n" +	
				"		<Element><code>2139</code><value>No LookUp configurations found in JRDSP repository</value></Element>\n" +	
				"		<Element><code>2140</code><value>External RDSP Account Contract Number  is Mandatory</value></Element>\n" +	
				"		<Element><code>2141</code><value>External RDSP Specimen Plan Number  is Mandatory</value></Element>\n" +	
				"		<Element><code>2143</code><value>AccountHolder is required</value></Element>\n" +	
				"		<Element><code>2144</code><value>AccountStatus is required</value></Element>\n" +	
				"		<Element><code>2145</code><value>EntityType is required</value></Element>\n" +	
				"		<Element><code>2146</code><value>ClosureReason is invalid</value></Element>\n" +	
				"		<Element><code>2147</code><value>ClosureDate and ClosureReason must coexist</value></Element>\n" +	
				"		<Element><code>2148</code><value>SessionId is required</value></Element>\n" +
				"		<Element><code>2149</code><value>Unable to update inception date when record has been sent to ESDC</value></Element>\n" +	
				"		<Element><code>2150</code><value>Empty Request</value></Element>\n" +
				"		<Element><code>2151</code><value>Invalid election type code</value></Element>\n" +	
				"		<Element><code>2152</code><value>Transaction Date must be on or after Certification Date</value></Element>\n" +	
				"		<Element><code>2153</code><value>Certification Date should not be blank if Election status code is Yes</value></Element>\n" +
				"		<Element><code>2154</code><value>Period start date Cannot be after Period end date</value></Element>\n" +	
				"		<Element><code>2155</code><value>Cannot update Election if the record has been submitted to ESDC</value></Element>\n" +	
				"		<Element><code>2156</code><value>24 months have not passed since the prior SDSP election end date</value></Element>\n" +	
				"		<Element><code>2157</code><value>Certification Date should be blank if Elected value is No</value></Element>\n" +
				"		<Element><code>2158</code><value>Certification Date and Period Start Date should be same</value></Element>\n" +	
				"		<Element><code>2159</code><value>Transaction date cannot be null</value></Element>\n" +	
				"		<Element><code>2160</code><value>Date cannot be prior to Beneficiary birth date</value></Element>\n" +	
				"		<Element><code>2161</code><value>Date cannot be future date</value></Element>\n" +	
				"		<Element><code>2162</code><value>Date cannot be prior to Dec 1,2008</value></Element>\n" +	
				"		<Element><code>2163</code><value>Certification Date cannot be prior to Beneficiary birth date</value></Element>\n" +	
				"		<Element><code>2164</code><value>Certification Date cannot be prior to Inception date</value></Element>\n" +
				"		<Element><code>2165</code><value>Election Status code cannot be same as previous election</value></Element>\n" +	
				"		<Element><code>2166</code><value>More than one election cannot be added or modified</value></Element>\n" +	
				"		<Element><code>2167</code><value>Election missing in repository</value></Element>\n" +	
				"		<Element><code>2168</code><value>Cannot add election with status-NO</value></Element>\n" +	
				"		<Element><code>2169</code><value>Cannot add DTC election when customer is DTC eligible</value></Element>\n" +
				"		<Element><code>2170</code><value>Cannot add Specified Year or SDSP election when customer is not DTC eligible</value></Element>\n" +	
				"		<Element><code>2171</code><value>Period end date Cannot be null for Specified year election</value></Element>\n" +	
				"		<Element><code>2172</code><value>Period start date Cannot be null for Specified year election with status YES</value></Element>\n" +	
				"		<Element><code>2173</code><value>Period end date should be equal to transaction date of Specified year election with status NO</value></Element>\n" +
				"		<Element><code>2174</code><value>InterfaceName is required</value></Element>\n" +	
				"		<Element><code>2175</code><value>AddressId is required</value></Element>\n" +	
				"		<Element><code>2176</code><value>AddressLine1 is required</value></Element>\n" +
				"		<Element><code>2178</code><value>Account should not be active if the number is 1</value></Element>\n" +	
				"		<Element><code>2181</code><value>Repayment reason must be specified on RDSP withdrawal</value></Element>\n" +	
				"		<Element><code>2184</code><value>FMV is less than AHA amount, payment may be rejected</value></Element>\n" +
				"		<Element><code>2185</code><value>Repayment reason does not match for DAP</value></Element>\n" +	
				"		<Element><code>2186</code><value>Repayment reason does not match for LDAP</value></Element>\n" +	
				"		<Element><code>2187</code><value>Repayment reason does not match for All Funds Full Withdrawal</value></Element>\n" +
				"		<Element><code>2188</code><value>Amount not in Min/Max Range</value></Element>\n" +
				"		<Element><code>2205</code><value>Invalid consent effective date</value></Element>\n" +	
				"		<Element><code>2207</code><value>No data in the event log for Record Type</value></Element>\n" +	
				"		<Element><code>2208</code><value>No log found for the Record Types</value></Element>\n" +	
				"		<Element><code>2210</code><value>Reconciled External RDSP Transfer-In transaction cannot be cancelled</value></Element>\n" +	
				"		<Element><code>2211</code><value>External RDSP Transfer-In transaction which is reported to ESDC cannot be cancelled</value></Element>\n" +	
				"		<Element><code>2262</code><value>Date cannot be prior to July 1,2011</value></Element>\n" +	
				"		<Element><code>500</code><value>Invalid date range provided</value></Element>\n" +	
				"		<Element><code>10292</code><value>Date cannot be prior to January 1,2014</value></Element>\n" +
				"		<Element><code>10392</code><value>Amount must be greater than 0</value></Element>\n" +
				"		<Element><code>10492</code><value>Date must be on or after contract signature date</value></Element>\n" +
				"		<Element><code>10592</code><value>Amount must be greater than or equal to zero</value></Element>\n" +
				"		<Element><code>2244</code><value>Invalid Issuer BN</value></Element>\n" +	
				"		<Element><code>2245</code><value>Invalid Specimen Plan Number</value></Element>\n" +	
				"		<Element><code>2246</code><value>Invalid Account Number</value></Element>\n" +	
				"		<Element><code>2247</code><value>Invalid Outgoing Record Type</value></Element>\n" +	
				"		<Element><code>2248</code><value>Invalid Outgoing Sub Record Type</value></Element>\n" +	
				"		<Element><code>2249</code><value>Invalid Transaction Origin</value></Element>\n" +
				"		<Element><code>2250</code><value>Account Number does not exist</value></Element>\n" +
				"		<Element><code>2251</code><value>Invalid Issuer Transaction Number</value></Element>\n" +
				"		<Element><code>2252</code><value>Matching SIN not found</value></Element>\n" +
				"		<Element><code>2253</code><value>Outgoing Record Not Found</value></Element>\n" +			
				"	</List>\n" + 
				"</eventLogErrors>";
	}
	
	@RequestMapping(value = "/getRefusalReason", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
	public String getRefusalReason() {
		return "<refusalReasons>\n" + 
				"	<List listName=\"RefusalReasons\">\n" + 
				"		<Element><code>01</code><value>Maximum Current Entitlement of grant/bond paid</value></Element>\n" +	
				"		<Element><code>02</code><value>Lifetime Contribution Limit Exceeded</value></Element>\n" +
				"		<Element><code>03</code><value>Lifetime Limit Exceeded</value></Element>\n" +	
				"		<Element><code>04</code><value>Age of Beneficiary</value></Element>\n" +	
				"		<Element><code>05</code><value>Specimen Plan not valid</value></Element>\n" +	
				"		<Element><code>06</code><value>No grant requested</value></Element>\n" +	
				"		<Element><code>08</code><value>SIN not usable</value></Element>\n" +	
				"		<Element><code>10</code><value>Invalid Beneficiary SIN</value></Element>\n" +
				"		<Element><code>19</code><value>Contract not registered</value></Element>\n" +	
				"		<Element><code>21</code><value>Last bond payment under this application � new 18+ bond request required</value></Element>\n" +	
				"		<Element><code>22</code><value>Bond request is not/no longer designated to attract bond for the beneficiary</value></Element>\n" +	
				"		<Element><code>24</code><value>Contract status conditions for adjustment of payment not met</value></Element>\n" +	
				"		<Element><code>26</code><value>Bond resubmission date is not within issuer approval dates</value></Element>\n" +	
				"		<Element><code>29</code><value>Beneficiary is a non-resident</value></Element>\n" +	
				"		<Element><code>30</code><value>Beneficiary DTC eligibility not confirmed</value></Element>\n" +	
				"		<Element><code>32</code><value>Beneficiary DTC eligibility not confirmed for two or more consecutive non-election years</value></Element>\n" +	
				"		<Element><code>33</code><value>Beneficiary DTC eligibility not confirmed for five or more consecutive years</value></Element>\n" +	
				"		<Element><code>99</code><value>Other</value></Element>\n" +	
				"		<Element><code>90</code><value>Contract Status not Registered</value></Element>\n" +	
				"		<Element><code>91</code><value>Age of Beneficiary</value></Element>\n" +	
				"		<Element><code>92</code><value>Lifetime Contribution Limit Exceeded</value></Element>\n" +	
				"		<Element><code>93</code><value>SIN not usable</value></Element>\n" +	
				"		<Element><code>94</code><value>Beneficiary is not a resident</value></Element>\n" +	
				"		<Element><code>95</code><value>Beneficiary DTC eligibility not confirmed</value></Element>\n" +	
				"		<Element><code>96</code><value>Rollover is made during an Episodic DTC Election Period</value></Element>\n" +	
				"	</List>\n" + 
				"</refusalReasons>";
	}
	
	@RequestMapping(value = "/getSinIssues", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
	public String getSinIssue() {
		return "<sinIssues>\n" + 
				"	<List listName=\"SinIssues\">\n" + 
				"		<Element><code>1</code><value>SIN is not usable</value></Element>\n" +	
				"		<Element><code>2</code><value>SIN is Usable</value></Element>\n" +
				"		<Element><code>3</code><value>Linked SIN</value></Element>\n" +	
				"	</List>\n" + 
				"</sinIssues>";
	}
	
	@RequestMapping(value = "/getSevereErrorDescriptions", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
	public String getSevereErrorDescription() {
		return "<severeErrorDescriptions>\n" + 
				"	<List listName=\"SevereErrorDescriptions\">\n" + 
				"		<Element><code>1</code><value>Duplicate issuer transaction number</value></Element>\n" +	
				"		<Element><code>2</code><value>Invalid record type/transaction type</value></Element>\n" +
				"		<Element><code>3</code><value>Issuer transaction number not provided</value></Element>\n" +	
				"		<Element><code>4</code><value>Issuer BN is not 15 characters</value></Element>\n" +	
				"	</List>\n" + 
				"</severeErrorDescriptions>";
	}
	
	@RequestMapping(value = "/getSirValidations", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
	public String getSirValidation() {
		return "<sirValidations>\n" + 
				"	<List listName=\"SirValidations\">\n" + 
				"		<Element><code>0</code><value>Failed SIR Validation</value></Element>\n" +	
				"		<Element><code>1</code><value>Passed SIR Validation</value></Element>\n" +
				"		<Element><code>2</code><value>Exact year and month matched</value></Element>\n" +	
				"		<Element><code>3</code><value>Exact year and day matched</value></Element>\n" +	
				"	</List>\n" + 
				"</sirValidations>";
	}
}