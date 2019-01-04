/*********************************************************************************************
 * @file	RDSPAccountInfo.Controller.js
 * @author	Balaji Rajendra babu
 * @desc	Controller JS file for RDSPAccountInfo.
 *********************************************************************************************/

DesktopWeb.ScreenController = function(){
	// PRIVATE VARIABLES *************************************
	
	var _translationMap     = DesktopWeb.Translation.getTranslationMap();
	var _self               = null;
	var _resources          = null;
	var _popupList		     = {};
	var _cycleDate;
	
	var _beneDOB ;
	var _incepDate;
	var _minDate;
	var isNewRecord=false;
	
	_popupList['AddElection']                          = 'AddElection';
	_popupList['ModifyElection'] = 'ModifyElection';
	//Default Value
	
	var _electionModalFldsList = {};
	
	var validationFlag={certFlag:false,transFlag:false};
	var _dropDownResponse;

	function initResources(){
		_resources.buttons['fileScreenButton'].disable();
		_resources.buttons['okScreenButton'].disable();
		//_resources.buttons['cancelScreenButton'].disable();
		//_buttons['cancelScreenButton'].disable();
		var addElectionPopUp = _resources.popups[_self.popupList['AddElection']];
		var modElectionPopUp = _resources.popups[_self.popupList['ModifyElection']];
/*
		JRDSP.Util.sendRequestToDesktopWeb('accountService','getConfig','','POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,responseHandler);

		function responseHandler(success, responseXML){
			_dropDownResponse=success.responseXML;
			populateDropdownList(_dropDownResponse);
		}*/
		
		
		
		
		
		
		
		
		
	}

	/** Store user permission **/
	
	/** Load All Dropdown Lists **/
	function populateDropdownList(dom){
	/*	var mockResponseXML = '<dtFinanInstInqResponse><List listName="booleanList"><Element><code>Yes</code><value>Yes</value>'+
			'</Element><Element><code>No</code><value>No</value></Element></List><List listName="electionTypeList"><Element><code>1</code><value>DTC Election</value></Element><Element><code>2</code><value>SDSP Election</value></Element><Element><code>3</code><value>Specified Year</value></Element></List>'+
		'<List listName="electionTypeFilterList"><Element><code>All</code><value>All</value></Element><Element><code>1</code><value>DTC Election</value></Element><Element><code>2</code><value>SDSP Election</value></Element><Element><code>3</code><value>Specified Year</value></Element></List></dtFinanInstInqResponse>';
		var dom = document.implementation.createDocument('', 'SmartviewResponse', null);
		dom.documentElement.innerHTML = mockResponseXML;
*/
		var electionTypeListNode = IFDS.Xml.getNode(dom, "//List[@listName='electionTypeList']");
		if (electionTypeListNode)
		{
			_resources.fields['ElectionTypeDropDown'].loadData(electionTypeListNode);

		}
		var booleanListNode = IFDS.Xml.getNode(dom, "//List[@listName='booleanList']");
		var electionTypeFilterList=IFDS.Xml.getNode(dom, "//List[@listName='electionTypeFilterList']");
		if (booleanListNode)
		{
			_resources.fields['GrantRequested'].loadData(booleanListNode);
			_resources.fields['TransferredAccount'].loadData(booleanListNode);
			_resources.fields['ReportToESDC'].loadData(booleanListNode);
			_resources.fields['BondRequested'].loadData(booleanListNode);
			_resources.fields['ElectedDropDown'].loadData(booleanListNode);

			

		}
		if(electionTypeFilterList)
			{
		_resources.fields['ElectionTypeDropDownFilter'].loadData(electionTypeFilterList);
		_resources.fields['ElectionTypeDropDownFilter'].setValue('All');
			}
		
		loadDefaults();
		
	}

	function resetList(){
		/*var mockResponseXML = '<dtFinanInstInqResponse><List listName="booleanList"><Element><code>Yes</code><value>Yes</value>'+
		'</Element><Element><code>No</code><value>No</value></Element></List><List listName="electionTypeList"><Element><code>1</code><value>DTC Election</value></Element><Element><code>2</code><value>SDSP Election</value></Element><Element><code>3</code><value>Specified Year</value></Element></List>'+
		'<List listName="electionTypeFilterList"><Element><code>All</code><value>All</value></Element><Element><code>1</code><value>DTC Election</value></Element><Element><code>2</code><value>SDSP Election</value></Element><Element><code>3</code><value>Specified Year</value></Element></List></dtFinanInstInqResponse>';
		var dom = document.implementation.createDocument('', 'SmartviewResponse', null);

		dom.documentElement.innerHTML = mockResponseXML;*/

		var booleanListNode = IFDS.Xml.getNode(_dropDownResponse, "//List[@listName='booleanList']");
		_resources.fields['ElectedDropDown'].loadData(booleanListNode);
	}
	
	function loadDefaults()
	{
		_resources.fields['GrantRequested'].setValue('Yes')
		_resources.fields['BondRequested'].setValue('Yes')
		_resources.fields['ReportToESDC'].setValue('Yes')
		_resources.fields['TransferredAccount'].setValue('No');
	}
	
	function goToScreen()
	{
		var params = {};
		params['prevScreen'] = 'RDSPAccountInfo';
		params['tidx'] = DesktopWeb._SCREEN_PARAM_MAP['tidx'];

		if(DesktopWeb._SCREEN_PARAM_MAP['prevScreen']){
			DesktopWeb.Util.goToScreen(DesktopWeb._SCREEN_PARAM_MAP['prevScreen'],params);
		}else{
			DesktopWeb.Util.cancelScreen();
		}
			
	}
	
	function updateAccount(accountId, fields, gridRecords)
	{
		var contextPath="accountService";
		var routePath="update/"+accountId;
		var requestXML = IFDS.Xml.newDocument('data');
		
		IFDS.Xml.addSingleNode(requestXML, 'accountId', accountId);

        IFDS.Xml.addSingleNode(requestXML, 'dtcEligible',fields['DTCEligibleCurrLabel'].getValue());
        IFDS.Xml.addSingleNode(requestXML, 'specifiedYear',fields['SpecifiedYearCurrLabel'].getValue());
        IFDS.Xml.addSingleNode(requestXML, 'reportToESDC',fields['ReportToESDC'].getValue());
        IFDS.Xml.addSingleNode(requestXML, 'dtcElection',fields['DTCElectionCurr'].getValue());
        IFDS.Xml.addSingleNode(requestXML, 'sdspElection',fields['SDSPElectionCurr'].getValue());
        if (fields['IncepDate'].getDisplayDateString()) {
            IFDS.Xml.addSingleNode(requestXML, 'inceptionDate', fields['IncepDate'].getDisplayDateString());
        }
		IFDS.Xml.addSingleNode(requestXML, 'grantRequested', fields['GrantRequested'].getValue());
		IFDS.Xml.addSingleNode(requestXML, 'bondRequested', fields['BondRequested'].getValue());
		IFDS.Xml.addSingleNode(requestXML, 'contractStatusRegistration', fields['ContractRegStatus'].getValue());
		IFDS.Xml.addSingleNode(requestXML, 'transferredAccount', fields['TransferredAccount'].getValue());
		IFDS.Xml.addSingleNode(requestXML, 'closureReasonCode', fields['ClosureReasonCode'].getValue());
		IFDS.Xml.addSingleNode(requestXML, 'accountStatus', fields['AccountStatus'].getValue());
		if (fields['ClosureDate'].getValue()) {
            IFDS.Xml.addSingleNode(requestXML, 'closureDate', fields['ClosureDate'].getValue());
        }
		IFDS.Xml.addSingleNode(requestXML, 'createdBy', fields['CreatedBy'].getValue());
		IFDS.Xml.addSingleNode(requestXML, 'accountUuid', fields['AccountUuid'].getValue());

		if(gridRecords.data.items.length>0)
		{
			
			var acctElectionsXML= IFDS.Xml.addSingleNode(requestXML, 'elections');
			for(var i=0;i<gridRecords.data.items.length;i++)
			{
				buildUpdateXMLAll(acctElectionsXML, gridRecords.data.itemAt(i) );
			}
		}
		
		function buildUpdateXMLAll(context,gridRecord){
			
			var acctElectionXML = IFDS.Xml.addSingleNode(context, 'election');
			IFDS.Xml.addSingleNode(acctElectionXML, 'id', gridRecord.get('id'));			
			IFDS.Xml.addSingleNode(acctElectionXML, 'type', getElectionTypeCode(gridRecord.get('type')));
			IFDS.Xml.addSingleNode(acctElectionXML, 'elected', gridRecord.get('elected'));
			if (gridRecord.get('certificationDate')) {
                IFDS.Xml.addSingleNode(acctElectionXML, 'certificationDate', gridRecord.get('certificationDate'));
            }
            if (gridRecord.get('transactionDate')) {
                IFDS.Xml.addSingleNode(acctElectionXML, 'transactionDate', gridRecord.get('transactionDate'));
            }
            IFDS.Xml.addSingleNode(acctElectionXML, 'reportingStatus', gridRecord.get('reportingStatus'));
            if (gridRecord.get('periodStart')) {
                IFDS.Xml.addSingleNode(acctElectionXML, 'periodStart', gridRecord.get('periodStart'));
            }
            if (gridRecord.get('periodEnd')) {
                IFDS.Xml.addSingleNode(acctElectionXML, 'periodEnd', gridRecord.get('periodEnd'));
            }
            if (gridRecord.get('uuid')) {
                IFDS.Xml.addSingleNode(acctElectionXML, 'uuid', gridRecord.get('uuid'));
            }
            if (gridRecord.get('effective')) {
                IFDS.Xml.addSingleNode(acctElectionXML, 'effective', gridRecord.get('effective'));
            }
			IFDS.Xml.addSingleNode(acctElectionXML, 'status', gridRecord.get('status'));
		}

		var _service = "AcctUpdate";
		
		JRDSP.Util.sendRequestToDesktopWeb(contextPath,routePath,_service,'POST',DesktopWeb._SCREEN_PARAM_MAP,requestXML,responseHandlerSuccess,responseHandlerFailure);

		function responseHandlerSuccess(success, responseXML)
		{
			goToScreen();
           // setAccountDetails(success.responseXML);
		}
		
		function responseHandlerFailure(success, responseXML)
		{
			DesktopWeb.Util.displayError( " Processing Failed . Please contact Administrator!!");//, callbackFnUpdate);
			function callbackFnUpdate(buttonId){
				if(buttonId == 'ok')
					{
				goToScreen();
					}
			}

         
		}
	}
	
	function getConfigurationDetails(){
		JRDSP.Util.sendRequestToDesktopWeb("configService","getConfiguration",null,'POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,responseHandler,responseHandlerFailure);
		
		function responseHandler(success, responseXML)
		{	
                        var configList = IFDS.Xml.getNodes(success.responseXML, '//configList/configuration');
                        for(var i=0;i<configList.length;i++){
                        	if(configList[i].childNodes[0].childNodes[0].data == 'NEXT-NR'){
                        		_cycleDate = configList[i].childNodes[1].childNodes[0].data;
                        	}
                        }
                        setCycleDate(JRDSP.Util.convertStringToDate(_cycleDate));
		}
		
		function responseHandlerFailure(response, options)
		{
			DesktopWeb.Util.displayError( " Processing Failed . Please contact Administrator!!");//, callbackFnUpdate);
			function callbackFnUpdate(buttonId){
			if(buttonId == 'ok')
				{
			goToScreen();
				}
		}
		}
	
	}

	

	function getAccountDetails(){
		var accountId= DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
		var contextPath="accountService";
		var routePath="details/"+accountId;
		
		var _service = "AcctInq";
		
/*		  setAccountDetails("");
			 initResources();
			 loadEntity();
			 setMinDate();*/
		
		JRDSP.Util.sendRequestToDesktopWeb(contextPath,routePath,_service,'POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,responseHandler,responseHandlerFailure);
		
		function responseHandler(success, responseXML)
		{	
			initResources();
            loadEntity();
            setMinDate();
            setAccountDetails(success.responseXML);
            setBenefDetails(success.responseXML);
		}
		
		function responseHandlerFailure(response, options)
		{
			DesktopWeb.Util.displayError( " Data not found . Please contact Administrator!!", callbackFn);
			
			function callbackFn(buttonId){
				if(buttonId == 'ok')
				{
				goToScreen();
				}
			}
            initResources();
            loadEntity();
            setMinDate();
            setAccountDetails(response.responseXML);
            setBenefDetails(response.responseXML);
		}
	}
	
	function setAccountDetails(response){
		 /* var dom="<accountDetails>	<bondRequested>Yes</bondRequested>	<contractStatusRegistration>Registered</contractStatusRegistration>	<dtcElection>Yes</dtcElection>	<dtcEligible>Yes</dtcEligible>	<grantRequested>YES</grantRequested>	" +
		  		"<inceptionDate>15/05/2017</inceptionDate>	" +
		  		"<reportToESDC>NO</reportToESDC>	<sdspElection>No</sdspElection>	<specifiedYear>-</specifiedYear>	<transferredAccount>NO</transferredAccount>	<closureReasonCode>NO</closureReasonCode>	<accountStatus>Active</accountStatus>	<closureDate>NO</closureDate>	<createdBy>NO</createdBy></accountDetails><accountId>1263026001</accountId><elections>	<election>			<id>2</id>		<certificationDate>15/04/2018</certificationDate>		<elected>Yes</elected>		<periodEnd/>		<periodStart>15/07/2017</periodStart>		<reportingStatus>No</reportingStatus>		<transactionDate>15/01/2018</transactionDate>		<type>SDSP Election</type>	</election>	<election>	<id>3</id>		<certificationDate>15/07/2017</certificationDate>		<elected>Yes</elected>		<periodEnd/>		<periodStart>15/07/2017</periodStart>		<reportingStatus>Yes</reportingStatus>		<transactionDate>15/06/2017</transactionDate>		<type>DTC Election</type>	</election>	<election>	<id>4</id>		<certificationDate>15/07/2017</certificationDate>		<elected>Yes</elected>		<periodEnd/>		<periodStart>15/07/2016</periodStart>		<reportingStatus>Yes</reportingStatus>		<transactionDate>15/04/2018</transactionDate>		<type>Specified Year</type>	</election></elections><entityInfo><beneDOB>16/05/1972</beneDOB><beneName>Paw Patrol</beneName><beneSIN>421897455</beneSIN><bondEligEndDate>31/12/2021</bondEligEndDate><contributionEndDate>31/12/2031</contributionEndDate><entities>	<entity>		<name>Paw Patrol</name>		<relationToBene>Self</relationToBene>		<sinOrBn>421897455</sinOrBn>	</entity>	<entity>		<name>Paw Patrol</name>		<relationToBene>Self</relationToBene>		<sinOrBn>421897455</sinOrBn>	</entity></entities><grantEligEndDate>31/12/2021</grantEligEndDate><specimenPlanNumber>TBD</specimenPlanNumber></entityInfo>";
         
		  var response = document.implementation.createDocument('', 'AcctInqResponse', null);
         
		  response.documentElement.innerHTML = dom;*/

        var electionsList = IFDS.Xml.getNodes(response, '//elections');

		_resources.fields['IncepDate'].setValue(IFDS.Xml.getNodeValue(response, '//inceptionDate'));
		_resources.fields['GrantRequested'].setValue(IFDS.Xml.getNodeValue(response, '//grantRequested'));
		_resources.fields['TransferredAccount'].setValue(IFDS.Xml.getNodeValue(response, '//transferredAccount'));
		_resources.fields['DTCEligibleCurrLabel'].setValue(IFDS.Xml.getNodeValue(response, '//dtcEligible'));
		_resources.fields['SpecifiedYearCurrLabel'].setValue(IFDS.Xml.getNodeValue(response, '//specifiedYear'));
		_resources.fields['ReportToESDC'].setValue(IFDS.Xml.getNodeValue(response, '//reportToESDC'));
		_resources.fields['BondRequested'].setValue(IFDS.Xml.getNodeValue(response, '//bondRequested'));
		_resources.fields['ContractRegStatus'].setValue(IFDS.Xml.getNodeValue(response, '//contractStatusRegistration'));
		_resources.fields['DTCElectionCurr'].setValue(IFDS.Xml.getNodeValue(response, '//dtcElection'));
		_resources.fields['SDSPElectionCurr'].setValue(IFDS.Xml.getNodeValue(response, '//sdspElection'));
		_resources.fields['AccountStatus'].setValue(IFDS.Xml.getNodeValue(response, '//accountStatus'));
		_resources.fields['ClosureReasonCode'].setValue(IFDS.Xml.getNodeValue(response, '//closureReasonCode'));
		_resources.fields['ClosureDate'].setValue(IFDS.Xml.getNodeValue(response, '//closureDate'));
		_resources.fields['CreatedBy'].setValue(IFDS.Xml.getNodeValue(response, '//createdBy'));
		_resources.fields['AccountUuid'].setValue(IFDS.Xml.getNodeValue(response, '//accountUuid'));

		_resources.grids['rdspElectionsGrid'].getStore().loadData(electionsList,false);
		
		_resources.grids['rdspElectionsGrid'].getSelectionModel().selectFirstRow();
		
		checkElections();
		
	}
	
	function setBenefDetails(response){
		 // var dom="<accountDetails>	<bondRequested>Yes</bondRequested>	<contractStatusRegistration>Registered</contractStatusRegistration>	<dtcElection>Yes</dtcElection>	<dtcEligible>Yes</dtcEligible>	<grantRequested>YES</grantRequested>	" +
		 // 		"<inceptionDate>15/05/2017</inceptionDate>	" +
		 // 		"<reportToESDC>NO</reportToESDC>	<sdspElection>No</sdspElection>	<specifiedYear>-</specifiedYear>	<transferredAccount>NO</transferredAccount>	<closureReasonCode>NO</closureReasonCode>	<accountStatus>Active</accountStatus>	<closureDate>NO</closureDate>	<createdBy>NO</createdBy></accountDetails><accountId>1263026001</accountId><elections>	<election>			<id>2</id>		<certificationDate>15/04/2018</certificationDate>		<elected>Yes</elected>		<periodEnd/>		<periodStart>15/07/2017</periodStart>		<reportingStatus>No</reportingStatus>		<transactionDate>15/01/2018</transactionDate>		<type>SDSP Election</type>	</election>	<election>	<id>3</id>		<certificationDate>15/07/2017</certificationDate>		<elected>Yes</elected>		<periodEnd/>		<periodStart>15/07/2017</periodStart>		<reportingStatus>Yes</reportingStatus>		<transactionDate>15/06/2017</transactionDate>		<type>DTC Election</type>	</election>	<election>	<id>4</id>		<certificationDate>15/07/2017</certificationDate>		<elected>Yes</elected>		<periodEnd/>		<periodStart>15/07/2016</periodStart>		<reportingStatus>Yes</reportingStatus>		<transactionDate>15/04/2018</transactionDate>		<type>Specified Year</type>	</election></elections><entityInfo><beneDOB>16/05/1972</beneDOB><beneName>Paw Patrol</beneName><beneSIN>421897455</beneSIN><bondEligEndDate>31/12/2021</bondEligEndDate><contributionEndDate>31/12/2031</contributionEndDate><entities>	<entity>		<name>Paw Patrol</name>		<relationToBene>Self</relationToBene>		<sinOrBn>421897455</sinOrBn>	</entity>	<entity>		<name>Paw Patrol</name>		<relationToBene>Self</relationToBene>		<sinOrBn>421897455</sinOrBn>	</entity></entities><grantEligEndDate>31/12/2021</grantEligEndDate><specimenPlanNumber>TBD</specimenPlanNumber></entityInfo>";
         //
		 // var response = document.implementation.createDocument('', 'AcctInqResponse', null);
         //
		 // response.documentElement.innerHTML = dom;

		//load entity information
		_resources.fields['BeneName'].setValue(IFDS.Xml.getNodeValue(response, '//entityInfo/beneName'));
		_resources.fields['BeneDOB'].setValue(IFDS.Xml.getNodeValue(response, '//entityInfo/beneDOB'));
		this._beneDOB=IFDS.Xml.getNodeValue(response, '//entityInfo/beneDOB');
		
		_resources.fields['ContEndDate'].setValue(IFDS.Xml.getNodeValue(response, '//entityInfo/contributionEndDate'));
		_resources.fields['GrantEligibleEndDate'].setValue(IFDS.Xml.getNodeValue(response, '//entityInfo/grantEligEndDate'));
		_resources.fields['SpecimenPlanNum'].setValue(IFDS.Xml.getNodeValue(response, '//entityInfo/specimenPlanNumber'));
		_resources.fields['DateOfDeath'].setValue(IFDS.Xml.getNodeValue(response, '//entityInfo/beneDateOfDeath'));
		_resources.fields['SIN'].setValue(IFDS.Xml.getNodeValue(response, '//entityInfo/beneSIN'));
		_resources.fields['BondEligibleEndDate'].setValue(IFDS.Xml.getNodeValue(response, '//entityInfo/bondEligEndDate'));

        _resources.grids['rdspAccountInfoGrid'].getStore().loadData(IFDS.Xml.getNodes(response, '//entities'),false);
        
		setMinInceptionDate();
	}

	function loadEntity(){
	}

	function modifyEntityGrid(rec,action){
		if(action == this.ADD)
			{
			rec.type=getElectionType(rec.type);
			if(rec.type!="" && rec.elected!="")
				{
				rec.reportingStatus = 'No';
		_resources.grids['rdspElectionsGrid'].addRecord(rec);
		_resources.grids['rdspElectionsGrid'].selectLastRecord();
		_resources.grids['rdspElectionsGrid'].disableButton('addBtn');
		
		isNewRecord=true;
				}
			}

		if(action == this.MOD)
		{
			//rec.type=getElectionTypeCode(rec.type);
			if(getElectionTypeCode(rec.type)==3)
			{
				rec.periodStart=rec.certificationDate;
		
			
			if(rec.elected == 'Yes')
			{
				var dateParts = rec.certificationDate.split("/");
				
				var year=parseInt(dateParts[2])+5;
				var month=parseInt(dateParts[1]);
				var date=parseInt(dateParts[0]);
				
				var dateObject = new Date(year, month, date); // month is 0-based

				rec.periodEnd ="31/12/"+dateObject.getFullYear();
			}
			else
				{
				rec.periodEnd =rec.transactionDate;
				}
			}
			_resources.grids['rdspElectionsGrid'].updateSelectedRecord(rec);
		}
		
		_resources.fields['ElectionTypeDropDownFilter'].setValue('All');
		setElectionGridBasedOnFilter('All');
	}

	function getElectionType(electionCode){
		if(electionCode == '1')
		return 'DTC Election';
		if(electionCode == '2')
		return 'SDSP Election';
		if(electionCode == '3')
		return 'Specified Year';
	}

	function getElectionTypeCode(electionType){
		if(electionType == 'DTC Election')
		return '1';
		if(electionType == 'SDSP Election')
		return '2';
		if(electionType == 'Specified Year')
		return '3';
	}
	
	function deleteSelectedElectionRecord(){
		
		var tempRecord = _resources.grids['rdspElectionsGrid'].getSelectedRecord();
		var index  = _resources.grids['rdspElectionsGrid'].store.indexOf(tempRecord)
		
		
		
		if (tempRecord.data['runMode'] == _self.ADD )
		{
			_resources.grids['rdspElectionsGrid'].removeSelectedRecord();
			_self.updatesFlag=false;
		}
		else if (tempRecord.data['runMode'] == _self.MOD ){
			if(isNewRecord){
				_resources.grids['rdspElectionsGrid'].removeSelectedRecord();
				_self.updatesFlag=false;
			}
			else{
				_resources.grids['rdspElectionsGrid'].removeSelectedRecord();
				_self.updatesFlag=true;
				
			}
			
		}
		else
		{
			tempRecord.data['runMode'] = _self.DEL;
			tempRecord.commit();
			_self.updatesFlag=true;
		
		}
		_resources.grids['rdspElectionsGrid'].removeSelectedRecord();
		_resources.grids['rdspElectionsGrid'].selectLastRecord();

	}
	
	function setElectionGridBasedOnFilter(electionType){
		if(electionType!='All')
			{

		_resources.grids['rdspElectionsGrid'].getStore().filter('type', getElectionType(electionType));
		
			}
	
		
		else
			{

			_resources.grids['rdspElectionsGrid'].getStore().clearFilter(true);
			_resources.grids['rdspElectionsGrid'].store.filterBy(function(record) {
				return record;//.data.runMode != _self.DEL;
			});
			}
		
		if(_resources.grids['rdspElectionsGrid'].getStore().getCount() <= 0)
			{
			// enable modify buttons
			_resources.grids['rdspElectionsGrid'].disableButton('modBtn');
			_resources.grids['rdspElectionsGrid'].disableButton('delBtn');
			}
		else
			{
			_resources.grids['rdspElectionsGrid'].getSelectionModel().selectFirstRow();
			}
		
	}
	
	function setEnableCertDate(comboValue){
		
		if(comboValue == 'Yes')
		{
		_resources.fields['CertificationDatePicker'].enable();
		}
		if(comboValue == 'No')
		{
		_resources.fields['CertificationDatePicker'].disable();
		}
	}
	
	function enableButtons(record){
		
		if(record.data.reportingStatus == 'Yes')
		{
			//addBtn
			_resources.grids['rdspElectionsGrid'].disableButton('modBtn');
			_resources.grids['rdspElectionsGrid'].disableButton('delBtn');
		}
		if(record.data.reportingStatus == 'No')
		{
			_resources.grids['rdspElectionsGrid'].enableButton('modBtn');
			_resources.grids['rdspElectionsGrid'].enableButton('delBtn');
		}
		if(record.data.reportingStatus == 'NA')
		{

			_resources.grids['rdspElectionsGrid'].enableButton('modBtn');
			_resources.grids['rdspElectionsGrid'].enableButton('delBtn');
		}
		
	}
	
	function validateCertDate(value){
		//Validation with DOB
		var valueDate=DesktopWeb.Util.stringToDate(value,'dmy');
		var dobDate=this._beneDOB;
		if(valueDate < dobDate)
			{
			_resources.popups['AddElection'].getField('pTransactionDatePicker').disable();
			return 'Certificate Date must be on or after beneficiary\'s date of birth!';
			}
		_resources.popups['AddElection'].getField('pTransactionDatePicker').enable();
		return true;
	}
	
	function validateTransactionDate(value){
		var valueDate=DesktopWeb.Util.stringToDate(value,'dmy');
		var certDate=DesktopWeb.Util.stringToDate(_resources.popups['AddElection'].getField('pCertificationDatePicker').getDisplayDateString(),'dmy');

		var selectedElection=_resources.popups['AddElection'].getField('pElectionTypeDropDown').getValue();
			if(valueDate < certDate)
			{
			return 'Transaction Date must be on or after Certificate Date!';
			}
			if(selectedElection == _self.getElectionTypeCode('SDSP Election'))
			{
				//get records from grid for SDSP
				var gridRecords=_resources.grids['rdspElectionsGrid'].getStore();
				if(gridRecords.data.length > 0)
				{
					var queryRecords=gridRecords.query('type','SDSP Election');
					if(queryRecords.length >0){

						var prevSDSPEndDate=queryRecords.items[0].data.periodEnd;

						
						var dateParts = prevSDSPEndDate.split("/");
						
						var year=parseInt(dateParts[2]);
						var month=parseInt(dateParts[1])+24;
						var date=parseInt(dateParts[0]);
						
						var dateObject = new Date(year, month, date); // month is 0-based

					//Compare dates
					if(!dateObject >= valueDate)
					{
					return 'SDSP election can be done only 24 months after the last SDSP Election End Date!';
					}
					}
					
				}
			}	
			
		return true;
	}
	
	function enableOKButtonPopUp(value)	{
		if(value != true)
			{
			_resources.popups['AddElection'].disableButton('okBtn');
			}
		else
			{
			_resources.popups['AddElection'].enableButton('okBtn');
			}
			
	}

	
	function validateIncepDate(value){
		
		var valueDate=DesktopWeb.Util.stringToDate(value,'dmy');
		var dobDate=DesktopWeb.Util.stringToDate(_resources.fields['BeneDOB'].getValue(),'dmy');
		this._beneDOB=dobDate;
		//  need to get the dateformat for rdsp inception date from BA.
		var rdspIncepDate=DesktopWeb.Util.stringToDate('01/12/2008','dmy');
		//var dobDate=DesktopWeb.Util.stringToDate(_resources.popups['AddElection'].getField('pCertificationDatePicker').getDisplayDateString(),'dmy');
		if(valueDate < rdspIncepDate)
		{
		return 'Inception date must be on or after RDSP start date 01/12/2008';
		}	

		if(valueDate < dobDate)
			{
			return 'Inception Date must be on or after beneficiary\'s date of birth! ';
			}
			

		return true;
		
	}
	
	function setMinInceptionDate(){
		var rdspIncepDate=DesktopWeb.Util.stringToDate('01/12/2008','dmy');
		if(this._beneDOB < rdspIncepDate){
			_resources.fields['IncepDate'].minValue = rdspIncepDate;
			return rdspIncepDate;
		}
		_resources.fields['IncepDate'].minValue = DesktopWeb.Util.stringToDate(this._beneDOB,'dmy');
		return this._beneDOB;
		
	}
	
	function setMinDate(){
		var dobDate=DesktopWeb.Util.stringToDate(_resources.fields['BeneDOB'].getValue(),'dmy');
		var incepDate=DesktopWeb.Util.stringToDate(_resources.fields['IncepDate'].getDisplayDateString(),'dmy');
		var rdspIncepDate=DesktopWeb.Util.stringToDate('01/12/2008','dmy');

		this._incepDate=incepDate;
		
		if(rdspIncepDate < dobDate){
			this._minDate=dobDate;
			_resources.fields['IncepDate'].minValue = dobDate;
		
		}
		else{
			
			this._minDate=rdspIncepDate;
			_resources.fields['IncepDate'].minValue = rdspIncepDate;
			
		}	
		
		if(incepDate > this._minDate){
			_resources.fields['CertificationDatePicker'].minValue = incepDate;
			_resources.fields['TransactionDatePicker'].minValue = incepDate;
			
			return incepDate;
		}
		else
			{
			_resources.fields['CertificationDatePicker'].minValue = this._minDate;
			_resources.fields['TransactionDatePicker'].minValue = this._minDate;

			return this._minDate;
			
			}
		
		return this._minDate;

		
	}
	
	function checkElections(){
		
/*		 var dtcElectionCurr=_resources.fields['DTCElectionCurr'].getValue();
		 var sdspElectionCurr=_resources.fields['SDSPElectionCurr'].getValue();
		 var specifiedYearElectionCurr=_resources.fields['SpecifiedYearCurrLabel'].getValue();
		 if(dtcElectionCurr == 'Yes' || sdspElectionCurr == 'Yes' || specifiedYearElectionCurr == 'Yes')
			 {
			 _resources.grids['rdspElectionsGrid'].disableButton('addBtn');
			 }
	*/
		
		var gridRecords=_resources.grids['rdspElectionsGrid'].getStore();
		if(gridRecords.data.length > 0)
		{	
		var electionType=gridRecords.data.items[0].data.type;
		var electionReportingStatus=gridRecords.data.items[0].data.reportingStatus;
		
		if(electionReportingStatus == 'No')
			{
			_resources.grids['rdspElectionsGrid'].disableButton('addBtn');
			}
		}
		else
			{
			_resources.grids['rdspElectionsGrid'].disableButton('modBtn');
			_resources.grids['rdspElectionsGrid'].disableButton('delBtn');
			}
	}
	
	function checkFlagsForModification(){
		var screenModified=0;
		for(var i=0;i<arguments.length;i++){
			screenModified+=arguments[i];
		}
		
		if(screenModified > 0)
			return true;
		else
			return false;
		
	}
	
	function getUpdatedRecordCount()
	{
		var store = _resources.grids['rdspElectionsGrid'].getStore();

		
		
		var result =
			store.query('runMode', _self.ADD).length +
			//store.query('runMode', _self.MOD).length +
			store.query('runMode', _self.DEL).length ;

		return result;
	}
	
	
	function setCycleDate(date){
		_resources.fields['IncepDate'].maxValue = DesktopWeb.Util.stringToDate(date,'dmy');
		_resources.fields['CertificationDatePicker'].maxValue = DesktopWeb.Util.stringToDate(date,'dmy');
		_resources.fields['TransactionDatePicker'].maxValue = DesktopWeb.Util.stringToDate(date,'dmy');
		_resources.fields['CertificationDatePicker'].value = DesktopWeb.Util.stringToDate(date,'dmy');
		_resources.fields['TransactionDatePicker'].value = DesktopWeb.Util.stringToDate(date,'dmy');
	}
	

	

	// PUBLIC ITEMS *************************************
	return {
		 ADD				: 'a'
		,MOD				: 'm'
		,DEL				: 'd'
		,UNCHANGE			: 'u'
		,INQ				: 'inq'
		,VAL				: 'val'
		,UPD				: 'upd'
		,ERROR				: 'error'
		,BLANK				: ''
		,FUND_LEVEL			: '01'
		,FUNDGROUP_LEVEL	: '02'
		,LEGALENTITY_LEVEL	: '03'
		,BROKER_LEVEL		: '04'
		,INTERMEDIARY_LEVEL	: '05'
		,YES				: 'yes'
		,NO					: 'no'
		,SEPERATOR			: ';'
		,NO_REPORTINGFFI    : '03'
		,YES_REPORTINGFFI	: '02'
		,DEFAULT_ENV_REPORTINGFFI : '01'
		,REPORTING_UNIT_REPORTINGFFI: '04'
		,FI_SPONSOR			: '05'
		,NO_THRESHOLD	    : '02'
		,updatesFlag		: false
		,NEWFFI				: 'NEWFFI'
		,NEWIDEN			: 'NEWIDEN'
		,REGULATIONCODECRSRP: 'CRSRP'
		,REGULATIONCODEFATCA: 'FA'
		,GROUPTYPECRSRP		: 'CRS'
		,GROUPTYPEFATCA		: 'FATCA'
		,popupList		      : _popupList
		,electionModalFldsList:_electionModalFldsList
		,beneDOB:_beneDOB
		,incepDate:_incepDate
		,minDate:_minDate
		,dropDownResponse: _dropDownResponse
		

		,init: function(res)
		{
			
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			getConfigurationDetails();
			JRDSP.Util.sendRequestToDesktopWeb('accountService','getConfig','','POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,responseHandler);

			function responseHandler(success, responseXML){
				_dropDownResponse=success.responseXML;
				populateDropdownList(_dropDownResponse);
			}
			getAccountDetails();


		}
		
		
		,openActionPopup: function(action, popupName,dtceligible) {

			setMinDate();
			_resources.popups[popupName].init(action,dtceligible);
			_resources.popups[popupName].show();
		}
		,getServiceTitle: function(code)
		{
			if(code == null) {
				return 'Election';
			}
			else if (code == "Fund")
			{
				return _translationMap['FIFundScreen'];
			}
		}
		,goToScreen:goToScreen
		,getAccountDetails:getAccountDetails
		,getDisplay: function(listName, code)
		{
			
		}
		,getUpdateFlags : function()
		{
			_self.updatesFlag = (getUpdatedRecordCount() > 0);
			return _self.updatesFlag;
		}
		,doUpdate: function() {
			var accountId = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
			var fields = _resources.fields;
			var gridRecords=_resources.grids['rdspElectionsGrid'].getStore();
			gridRecords.clearFilter(false);
			updateAccount(accountId, fields, gridRecords)
		}
		,loadEntity : loadEntity
		,modifyEntityGrid:modifyEntityGrid
		,deleteSelectedElectionRecord : deleteSelectedElectionRecord
		,setElectionGridBasedOnFilter:setElectionGridBasedOnFilter
		,setEnableCertDate:setEnableCertDate
		,enableButtons:enableButtons
		,validateCertDate:validateCertDate
		,validateTransactionDate:validateTransactionDate
		,getElectionTypeCode:getElectionTypeCode
		,enableOKButtonPopUp : enableOKButtonPopUp
		,validateIncepDate:validateIncepDate
		,setMinDate:setMinDate
		,setMinInceptionDate:setMinInceptionDate
		,populateDropdownList:populateDropdownList
		,getElectionType:getElectionType
		,resetList:resetList
		,checkElections:checkElections
		,checkFlagsForModification : checkFlagsForModification
		,getUpdatedRecordCount:getUpdatedRecordCount
		,setCycleDate:setCycleDate
	}
};