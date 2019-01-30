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
	var _rdspIncepDate;
	
	var _beneDOB ;
	var _incepDate;
	var _minDate;
	var isNewRecord=false;
	
	var _actualGridDataStore = new Ext.data.XmlStore(
			{
				record: 'election'
				,fields: [
					'id','type', 'elected', 'certificationDate', 'transactionDate','reportingStatus', 'periodStart',
					'periodEnd', 'uuid', 'effective', 'status','runMode'
				]
	
			}
		);
	
	var _actualEligibilityDataStore = new Ext.data.XmlStore(
			{
				record: 'election'
				,fields: [
					'id','type', 'elected', 'periodStart','periodEnd'
				]
	
			}
		);
	
	_popupList['AddElection']                          = 'AddElection';
	_popupList['ModifyElection'] = 'ModifyElection';
	//Default Value
	
	var _electionModalFldsList = {};
	
	var validationFlag={certFlag:false,transFlag:false};
	var _dropDownResponse;
	
	var _contractRegistrationStatusCode;
	var _contractRegistrationStatus = {};
	
	function initResources(){
		_resources.buttons['okScreenButton'].disable();
		//_resources.buttons['cancelScreenButton'].disable();
		//_buttons['cancelScreenButton'].disable();
		var addElectionPopUp = _resources.popups[_self.popupList['AddElection']];
		var modElectionPopUp = _resources.popups[_self.popupList['ModifyElection']];
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
	
	function populateKeyValues(xmlData) {
		_contractRegistrationStatus = [];
		var code, description;
		var q = Ext.DomQuery;
		var entries = q.select('Element', xmlData);
		for (var i = 0; i < entries.length; ++i) {
			code = entries[i].childNodes[0].childNodes[0].nodeValue;
			description = entries[i].childNodes[1].childNodes[0].nodeValue;
			_contractRegistrationStatus[code] = description; 
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
		IFDS.Xml.addSingleNode(requestXML, 'grantDate', fields['GrantDate'].getDisplayDateString());
		IFDS.Xml.addSingleNode(requestXML, 'bondRequested', fields['BondRequested'].getValue());
		IFDS.Xml.addSingleNode(requestXML, 'contractStatusRegistration', _contractRegistrationStatusCode);
		IFDS.Xml.addSingleNode(requestXML, 'transferredAccount', fields['TransferredAccount'].getValue());
		IFDS.Xml.addSingleNode(requestXML, 'closureReasonCode', fields['ClosureReasonCode'].getValue());
		IFDS.Xml.addSingleNode(requestXML, 'accountStatus', fields['AccountStatus'].getValue());
		if (fields['ClosureDate'].getValue()) {
            IFDS.Xml.addSingleNode(requestXML, 'closureDate', fields['ClosureDate'].getValue());
        }
		IFDS.Xml.addSingleNode(requestXML, 'createdBy', fields['CreatedBy'].getValue());
		IFDS.Xml.addSingleNode(requestXML, 'accountUuid', fields['AccountUuid'].getValue());

		if(_actualGridDataStore.data.items.length>0)
		{
			var acctElectionsXML= IFDS.Xml.addSingleNode(requestXML, 'elections');
			for(var i=0;i<_actualGridDataStore.data.items.length;i++)
			{
				buildUpdateXMLAll(acctElectionsXML, _actualGridDataStore.data.itemAt(i) );
			}
		}
		
		function buildUpdateXMLAll(context,gridRecord){
			
			var acctElectionXML = IFDS.Xml.addSingleNode(context, 'election');
			IFDS.Xml.addSingleNode(acctElectionXML, 'id', gridRecord.get('id'));			
			IFDS.Xml.addSingleNode(acctElectionXML, 'type', gridRecord.get('type'));
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
                        	if(configList[i].childNodes[0].childNodes[0].data == 'RDSP_START'){
                        		_rdspIncepDate = JRDSP.Util.convertStringToDate(configList[i].childNodes[1].childNodes[0].data);
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
        var electionsList = IFDS.Xml.getNodes(response, '//elections');
        var eligiblityList = IFDS.Xml.getNodes(response, '//dtcEligiblities');
        _resources.fields['GrantDate'].setValue(IFDS.Xml.getNodeValue(response, '//effectiveDate'));
		_resources.fields['IncepDate'].setValue(IFDS.Xml.getNodeValue(response, '//inceptionDate'));
		_resources.fields['GrantRequested'].setOriginalValue(IFDS.Xml.getNodeValue(response, '//grantRequested'));
		_resources.fields['TransferredAccount'].setValue(IFDS.Xml.getNodeValue(response, '//transferredAccount'));
		_resources.fields['DTCEligibleCurrLabel'].setValue(IFDS.Xml.getNodeValue(response, '//dtcEligible'));
		_resources.fields['SpecifiedYearCurrLabel'].setValue(IFDS.Xml.getNodeValue(response, '//specifiedYear'));
		_resources.fields['ReportToESDC'].setValue(IFDS.Xml.getNodeValue(response, '//reportToESDC'));
		_resources.fields['BondRequested'].setValue(IFDS.Xml.getNodeValue(response, '//bondRequested'));
		
		_contractRegistrationStatusCode = IFDS.Xml.getNodeValue(response, '//contractStatusRegistration');
		if(_contractRegistrationStatusCode) {
			_resources.fields['ContractRegStatus'].setValue(_contractRegistrationStatus[_contractRegistrationStatusCode]);
		}
		_resources.fields['DTCElectionCurr'].setValue(IFDS.Xml.getNodeValue(response, '//dtcElection'));
		_resources.fields['SDSPElectionCurr'].setValue(IFDS.Xml.getNodeValue(response, '//sdspElection'));
		_resources.fields['AccountStatus'].setValue(IFDS.Xml.getNodeValue(response, '//accountStatus'));
		_resources.fields['ClosureReasonCode'].setValue(IFDS.Xml.getNodeValue(response, '//closureReasonCode'));
		_resources.fields['ClosureDate'].setValue(IFDS.Xml.getNodeValue(response, '//closureDate'));
		_resources.fields['CreatedBy'].setValue(IFDS.Xml.getNodeValue(response, '//createdBy'));
		_resources.fields['AccountUuid'].setValue(IFDS.Xml.getNodeValue(response, '//accountUuid'));
		_actualGridDataStore.loadData(electionsList,false);
		_actualEligibilityDataStore.loadData(eligiblityList,false);
		_resources.grids['rdspElectionsGrid'].getStore().loadData(electionsList,false);
		
		_resources.grids['rdspElectionsGrid'].getSelectionModel().selectFirstRow();
		
		consolidateEventRecords();
		
		
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
        
	}

	function loadEntity(){
	}

	function modifyEntityGrid(rec,action){
		if(action == this.ADD)
			{
			if(rec.type!="" && rec.elected!="")
				{
				rec.reportingStatus = 'No';
	
		isNewRecord=true;
				}
			if(rec.type == 1){
				createRecord(rec,'Yes',rec.certificationDate,rec.transactionDate,rec.periodStart,rec.periodEnd);	
			}else if(rec.type == 2){
				createRecord(rec,'Yes',rec.certificationDate,rec.transactionDate,rec.certificationDate,'');	
			}else if(rec.type == 3){
				createRecord(rec,'Yes',rec.certificationDate,rec.transactionDate,rec.certificationDate,rec.periodEnd);
			}
			

			}

		if(action == this.MOD)
		{
			var modifyRecord = _actualGridDataStore.getAt(0);
			var previousRecord = _actualGridDataStore.getAt(1);
			modifyRecord.data.certificationDate = rec.certificationDate;
			modifyRecord.data.transactionDate = rec.transactionDate;
			modifyRecord.data.periodStart=rec.periodStart;
			modifyRecord.data.periodEnd =rec.periodEnd;
			
			if(previousRecord){
				if(previousRecord.data.elected == 'No'){
					var dateParts = rec.certificationDate.split("/");
				}else{
					var dateParts = rec.transactionDate.split("/");
				}
			var yearStr=parseInt(dateParts[2]);
			var month=parseInt(dateParts[1]);
			var date=parseInt(dateParts[0])-1;
			var dayStr = (date < 10 ? "0" + date : date );
			var monStr = (month < 10 ? "0" + (month) : month);
			
			
			var dateString = dayStr + "/" + monStr + "/" + yearStr;
			previousRecord.data.periodEnd =  dateString;
			}
			if(getElectionTypeCode(modifyRecord.data.type)==3)
			{
				modifyRecord.data.periodStart=rec.certificationDate;
		
			
			if(modifyRecord.data.elected == 'Yes')
			{
				var dateParts = rec.certificationDate.split("/");
				
				var year=parseInt(dateParts[2])+5;
				var month=parseInt(dateParts[1]);
				var date=parseInt(dateParts[0]);
				
				var dateObject = new Date(year, month, date); // month is 0-based

				modifyRecord.data.periodEnd ="31/12/"+dateObject.getFullYear();
			}else{
				modifyRecord.data.periodEnd = rec.transactionDate;
			}
			}
			//_resources.grids['rdspElectionsGrid'].updateSelectedRecord(rec);
			consolidateEventRecords();
		}
		if(action == this.REVOKE)
		{
			var dateParts = rec.transactionDate.split("/");
			
			var year=parseInt(dateParts[2]);
			var month=parseInt(dateParts[1]);
			var date=parseInt(dateParts[0]);
			
			var dateObject = new Date(year-1, month, date); // month is 0-based


			if(getElectionTypeCode(rec.type)==2 || getElectionTypeCode(rec.type)==3)
			{
				rec.periodEnd =rec.transactionDate;
				
			}
			if(getElectionTypeCode(rec.type)==1)
			{
				rec.periodEnd ="31/12/"+dateObject.getFullYear();
				
			}
			
			
			
			createRecord(rec,'No','',rec.transactionDate,rec.transactionDate,rec.periodEnd);
		}
		
		_resources.fields['ElectionTypeDropDownFilter'].setValue('All');
		//setElectionGridBasedOnFilter('All');
	}
		
	
		function createRecord(rec,status,certDate,transDate,periodStart,periodEnd){
			var newRevokeRecord = [];
			if(rec.runMode == _self.REVOKE && rec.type!=3){
				 var gridRecordsRecordType= {
		            		"certificationDate": certDate,
		                    "periodEnd": '',
		                    "periodStart": periodStart,
		                    "reportingStatus": "No",
		                    "transactionDate":  transDate,
		                    "type":  rec.type,
		                    "id":"",
		                    "elected":status,
		                    "uuid":"",
		                    "effective":"",
		                    "status":"",
		                    "runMode" : rec.runMode
		            	};
			}
			if(rec.runMode == _self.REVOKE && rec.type==3){
				 var gridRecordsRecordType= {
		            		"certificationDate": certDate,
		                    "periodEnd": transDate,
		                    "periodStart": periodStart,
		                    "reportingStatus": "No",
		                    "transactionDate":  transDate,
		                    "type":  rec.type,
		                    "id":"",
		                    "elected":status,
		                    "uuid":"",
		                    "effective":"",
		                    "status":"",
		                    "runMode" : rec.runMode
		            	};
			}
			if(rec.runMode == _self.ADD && rec.type==1) {
				 var gridRecordsRecordType= {
		            		"certificationDate": certDate,
		                    "periodEnd": periodEnd,
		                    "periodStart": periodStart,
		                    "reportingStatus": "No",
		                    "transactionDate":  transDate,
		                    "type":  rec.type,
		                    "id":"",
		                    "elected":status,
		                    "uuid":"",
		                    "effective":"",
		                    "status":"",
		                    "runMode" : rec.runMode
		            	};
			}
			if(rec.runMode == _self.ADD && rec.type==2) {
				 var gridRecordsRecordType= {
		            		"certificationDate": certDate,
		                    "periodEnd": '',
		                    "periodStart": periodStart,
		                    "reportingStatus": "No",
		                    "transactionDate":  transDate,
		                    "type":  rec.type,
		                    "id":"",
		                    "elected":status,
		                    "uuid":"",
		                    "effective":"",
		                    "status":"",
		                    "runMode" : rec.runMode
		            	};
			}
			if(rec.runMode == _self.ADD && rec.type==3) {
				 var gridRecordsRecordType= {
		            		"certificationDate": certDate,
		                    "periodEnd": periodEnd,
		                    "periodStart": periodStart,
		                    "reportingStatus": "No",
		                    "transactionDate":  transDate,
		                    "type":  rec.type,
		                    "id":"",
		                    "elected":status,
		                    "uuid":"",
		                    "effective":"",
		                    "status":"",
		                    "runMode" : rec.runMode
		            	};
			}
           
			newRevokeRecord.push(new _actualGridDataStore.recordType(gridRecordsRecordType));
			for(var i=0;i<_actualGridDataStore.getCount();i++){
					if(i==0){
						if(rec.runMode == _self.ADD){
							var dateParts = gridRecordsRecordType.certificationDate.split("/");	
						}else{
							var dateParts = gridRecordsRecordType.transactionDate.split("/");	
						}
						var yearStr=parseInt(dateParts[2]);
						var month=parseInt(dateParts[1]);
						var date=parseInt(dateParts[0])-1;
						var dayStr = (date < 10 ? "0" + date : date );
						var monStr = (month < 10 ? "0" + (month) : month);
						
						
						var dateString = dayStr + "/" + monStr + "/" + yearStr;
						_actualGridDataStore.getAt(i).data.periodEnd = dateString;
					}
					newRevokeRecord.push(_actualGridDataStore.getAt(i));
			}
			_actualGridDataStore.removeAll();
			for(var i=0;i<newRevokeRecord.length;i++){
				_actualGridDataStore.insert(i,newRevokeRecord[i]);
			}
			consolidateEventRecords();
			
		}

	function consolidateEventRecords(runMode){
        // Check recordType = election
        var allElections=[];
        var gridRecords = [];
        for(var i=0;i<_actualGridDataStore.data.length;i++){
               var eventType = _actualGridDataStore.data.items[i].data.type;
               if(eventType == '1' || eventType == '2' || eventType == '3'){
                      allElections.push(_actualGridDataStore.data.items[i].data);
               }
        }
        for(var i=0;i<allElections.length;i++){
               if(allElections[i].elected == 'No'){
                      //combine with existing yes for a single record
            	  var gridRecordsRecordType= {
            			  "certificationDate": allElections[i+1].certificationDate,
                           "periodEnd": allElections[i].transactionDate,
                           "periodStart": allElections[i+1].periodStart,
                           "reportingStatus": allElections[i].reportingStatus,
                           "transactionDate":  allElections[i].transactionDate,
                           "type":  allElections[i].type,
                           "id":"",
                           "elected":"No",
                           "uuid":"",
                           "effective":"",
                           "status":"",
                           "runMode" : allElections[i].runMode,
                    	   "yesElectionId":allElections[i+1].id,
                    	   "noElectionId":allElections[i].id
                        		   
       }; 
                      
               
                      i=i+1;
        }else{
        	 var gridRecordsRecordType= {"certificationDate": allElections[i].certificationDate,
                     "periodEnd": allElections[i].periodEnd,
                     "periodStart": allElections[i].periodStart,
                     "reportingStatus": allElections[i].reportingStatus,
                     "transactionDate":  allElections[i].transactionDate,
                     "type":  allElections[i].type,
                     "id":"",
                     "elected":"Yes",
                     "uuid":"",
                     "effective":"",
                     "status":"",
                     "runMode" : allElections[i].runMode,
              	   	 "yesElectionId":allElections[i].id,
              	     "noElectionId":""
                  		   
 }; 
        	 
        	 if(runMode == _self.DEL && gridRecordsRecordType.type!=3){
        		 gridRecordsRecordType.periodEnd = '';
             }else if(runMode == _self.DEL && gridRecordsRecordType.type==3){
            	var dateParts = gridRecordsRecordType.certificationDate.split("/");	
					
				
				var yearStr=parseInt(dateParts[2])+5;
				var month=parseInt(dateParts[1]);
				var date=parseInt(dateParts[0]);
				var dayStr = (date < 10 ? "0" + date : date );
				var monStr = (month < 10 ? "0" + (month) : month);
				
				var dateObject = new Date(yearStr,monStr, dayStr); 
				var dateString = "31/12/" + dateObject.getFullYear();
				gridRecordsRecordType.periodEnd = dateString;
             }
        	 
        }
               gridRecords.push(new _actualGridDataStore.recordType(gridRecordsRecordType));
               //gridRecords.push(new _actualGridDataStore.recordType(allElections[i]));
        }
        
        // Consolidating DTC eligiblity records
       
        for(var i=0;i<_actualEligibilityDataStore.getCount();i++){
        	var dateParts = _actualEligibilityDataStore.data.items[i].data.periodStart.split("/");	
			var yearStr=parseInt(dateParts[2]);
			var month=parseInt(dateParts[1]);
			var date=parseInt(dateParts[0]);
			var dayStr = (date < 10 ? "0" + date : date );
			var monStr = (month < 10 ? "0" + (month) : month);
			var dateObject = new Date(yearStr,monStr, dayStr); 
			var dateString = "31/12/" + dateObject.getFullYear();
	     	var gridRecordsRecordType= {
	 		  
	            "periodEnd": dateString,
	            "periodStart": _actualEligibilityDataStore.data.items[i].data.periodStart,
	           // "reportingStatus": _actualEligibilityDataStore[i].reportingStatus,
	            "type":  _actualEligibilityDataStore.data.items[i].data.type,
	            "id":_actualEligibilityDataStore.data.items[i].data.id,
	            "elected":_actualEligibilityDataStore.data.items[i].data.elected
	     	  }; 
	     	 gridRecords.push(new _actualGridDataStore.recordType(gridRecordsRecordType));
        }
        //Delete existing records
        _resources.grids['rdspElectionsGrid'].getStore().removeAll();
        for(var i=0;i<gridRecords.length;i++){
               _resources.grids['rdspElectionsGrid'].getStore().insert(i,gridRecords[i]);
               
        }

        //Sort By PeriodEnd
        sortGridByPeriodEnd();
        _resources.grids['rdspElectionsGrid'].getSelectionModel().selectFirstRow();
  }
	
	function sortGridByPeriodEnd(){
      
        
        var queryRecords=  _resources.grids['rdspElectionsGrid'].getStore().queryBy(function(record) {
			return record;
		});
        queryRecords.each(function(record){
			record.data.periodEnd=JRDSP.Util.convertDateToStringFormat(record.data.periodEnd);
		});
		
        queryRecords.sort('DESC',function(a,b){
			if(a.data.periodEnd > b.data.periodEnd)
				return 1;
			if(a.data.periodEnd < b.data.periodEnd)
				return -1;
			
			return 0;
			
		});
        queryRecords.each(function(record){
			record.data.periodEnd=JRDSP.Util.convertStringToDate(record.data.periodEnd);
		});
        _resources.grids['rdspElectionsGrid'].getStore().removeAll();
        for(var i=0;i<queryRecords.length;i++){
        	 _resources.grids['rdspElectionsGrid'].getStore().insert(i,queryRecords.items[i]);
		}
	}
	
function sortStoreByPeriodEnd(store){
      
        
        var queryRecords=  store.queryBy(function(record) {
			return record;
		});
        queryRecords.each(function(record){
			record.data.periodEnd=JRDSP.Util.convertDateToStringFormat(record.data.periodEnd);
		});
		
        queryRecords.sort('DESC',function(a,b){
			if(a.data.periodEnd > b.data.periodEnd)
				return 1;
			if(a.data.periodEnd < b.data.periodEnd)
				return -1;
			
			return 0;
			
		});
        queryRecords.each(function(record){
			record.data.periodEnd=JRDSP.Util.convertStringToDate(record.data.periodEnd);
		});
      
        return queryRecords;
        
	}

function sortStoreByPeriodStart(store){
    
    
    var queryRecords=  store.queryBy(function(record) {
		return record;
	});
    queryRecords.each(function(record){
		record.data.periodStart=JRDSP.Util.convertDateToStringFormat(record.data.periodStart);
	});
	
    queryRecords.sort('DESC',function(a,b){
		if(a.data.periodStart> b.data.periodStart)
			return 1;
		if(a.data.periodStart < b.data.periodStart)
			return -1;
		
		return 0;
		
	});
    queryRecords.each(function(record){
		record.data.periodStart=JRDSP.Util.convertStringToDate(record.data.periodStart);
	});
  
    return queryRecords;
    
}
	
	function checkValidAction(action,rec){
		
		if(rec){
			
			if(rec.data.type == 1 || rec.data.type == 2 || rec.data.type == 3){			
		if(rec.data.reportingStatus == 'Yes'){
			if(action==_self.REVOKE && rec.data.elected == 'No' && rec.data.noElectionId!=null){
				return false;
			}else if (action==_self.MOD ||action==_self.DEL ){
				return false;
			}else{
				return true;
			}
		}else{
			if(action==_self.ADD){
				return false;
			}else if (action==_self.REVOKE){
				if(rec.data.type==3){
					return true;
				}
				return false;
			}else{
				return true;
			}
		}
			}else{
				if(checkIfAtleast1ElectionIsPresent()){
				return false;
				}else{
					return true;
				}
			}
		}else{
			if(action!=_self.ADD){
				return false;	
			}
				return true;
		}
		
	}
	
	function addBtnValidation(){
		var firstRecord = _actualGridDataStore.getAt(0);
		var sortedDtcEligibleRecords = sortStoreByPeriodStart(_actualEligibilityDataStore);
		var firstDTCRecord = sortedDtcEligibleRecords.items[0];
		if(firstDTCRecord && firstDTCRecord.data.type == '6'){
			return false;
		}
		if(firstRecord && firstRecord.data.elected == 'No' && firstRecord.data.reportingStatus == 'Yes'){
			return true;
		}
		if(firstRecord && firstRecord.data.elected == 'No' && firstRecord.data.reportingStatus == 'No'){
			return false;
		}
		if(firstRecord && firstRecord.data.elected == 'Yes'){
			return false;
		}
		if(!firstRecord){
			return true;
		}
	}
	
	function addBtnValidationMsg(){
		var firstRecord = _actualGridDataStore.getAt(0);
		var sortedDtcEligibleRecords = sortStoreByPeriodStart(_actualEligibilityDataStore);
		var firstDTCRecord = sortedDtcEligibleRecords.items[0];
		if(firstDTCRecord && firstDTCRecord.data.type == '6'){
			return _translationMap['ErrorNotAllowed'];
		}
		if(firstRecord && firstRecord.data.elected == 'Yes' && firstRecord.data.reportingStatus == 'No'){
			return _translationMap['ErrorPending'];
		}
		if(firstRecord && firstRecord.data.elected == 'Yes' && firstRecord.data.reportingStatus == 'Yes'){
			return _translationMap['ErrorReported'];
		}
		if(firstRecord && firstRecord.data.elected == 'No' && firstRecord.data.reportingStatus == 'No'){
			return _translationMap['ErrorReported'];
		}
		if(!firstRecord){
			return true;
		}
	}
	
	function checkIfAtleast1ElectionIsPresent(){
		var records = _resources.grids['rdspElectionsGrid'].getStore().queryBy(function(record) {
			return (record.data.type == 1 || record.data.type == 2 || record.data.type == 3 );
		});
		return records.length >0;
	}

	
	function getButtonErrorMsg(action,rec){
		if(rec){
			if(rec.data.type == 1 || rec.data.type == 2 || rec.data.type == 3){		
		if(rec.data.reportingStatus == 'Yes'){
			if(action==_self.REVOKE && rec.data.elected == 'No' && rec.data.noElectionId!=null){
				return _translationMap['ErrorReported'];
			}else if(action == _self.ADD || action==_self.MOD ||action==_self.DEL ){
				return _translationMap['ErrorReported'];
			}
		}else{
			if(action==_self.ADD){
				if(rec.data.type==3){
					return _translationMap['ErrorNotAllowed'];
				}else{
				return _translationMap['ErrorPending'];
				}
			}else if (action==_self.REVOKE){
				if(rec.data.type!=3){
					return _translationMap['ErrorPending'];
				}
			}else{
				return true;
			}
		
			if(action==_self.ADD ||action==_self.REVOKE ){
				return _translationMap['ErrorPending'];
			}
		} 
			}else{
				if(checkIfAtleast1ElectionIsPresent()){
					if(rec.data.type == 4 || rec.data.type == 5){
						return _translationMap['ErrorConfirmed'];
					}else if(rec.data.type == 6){
						return _translationMap['ErrorPending'];
					}
				} else{
					return true;
				}
				
			
		}
		
		}else{
			if(action!=_self.ADD){
				return  _translationMap['ErrorNotAllowed'];	
			}
		}
	}
		

	function getElectionType(electionCode){
		if(electionCode == '1')
		return 'DTC Election';
		if(electionCode == '2')
		return 'SDSP Election';
		if(electionCode == '3')
		return 'Specified Year';
		if(electionCode == '4')
			return 'DTC Eligible';
		if(electionCode == '5')
			return 'DTC Ineligible';
		if(electionCode == '6')
			return 'DTC Undetermined';
	}

	function getElectionTypeCode(electionType){
		if(electionType == 'DTC Election')
		return '1';
		if(electionType == 'SDSP Election')
		return '2';
		if(electionType == 'Specified Year')
		return '3';
		if(electionType == 'DTC Eligible')
			return '4';
		if(electionType == 'DTC Ineligible')
			return '5';
		if(electionType == 'DTC Undetermined')
			return '6';
	}
	
	function deleteSelectedElectionRecord(){
		var tempRecord = _resources.grids['rdspElectionsGrid'].getSelectedRecord();
		
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
			var records = _actualGridDataStore.queryBy(function(record) {
				if(tempRecord.data['noElectionId'] && tempRecord.data['yesElectionId']){
					return record.data.id == tempRecord.data['noElectionId'];	
				}else if (!tempRecord.data['noElectionId'] && tempRecord.data['yesElectionId']){
					return record.data.id == tempRecord.data['yesElectionId'];	
				} else{
					return (record.data.type == tempRecord.data['type'] 
					&& record.data.periodEnd == tempRecord.data['periodEnd']
					&& record.data.periodStart == tempRecord.data['periodStart']
					&& record.data.reportingStatus == tempRecord.data['reportingStatus']
					&& record.data.transactionDate == tempRecord.data['transactionDate']
					&& record.data.certificationDate == tempRecord.data['certificationDate']);
				}
				
			});
			var yesElectionId;
			var yesElectionRecord,lastElectionRecord;
			if(tempRecord.data['noElectionId'] && tempRecord.data['yesElectionId']){
				yesElectionId=tempRecord.data['yesElectionId'];
			}
			if(!tempRecord.data['noElectionId'] && tempRecord.data['yesElectionId']){
				lastElectionRecord = _actualGridDataStore.getAt(1);
			}
			
			if(yesElectionId){
				yesElectionRecord = _actualGridDataStore.queryBy(function(record) {
					return record.data.id == yesElectionId;
				});
				if(yesElectionRecord.items[0].data.type!=3){
					yesElectionRecord.items[0].data.periodEnd = '';
				}else{
					var dateParts = yesElectionRecord.items[0].data.certificationDate.split("/");	
					
					
					var yearStr=parseInt(dateParts[2])+5;
					var month=parseInt(dateParts[1]);
					var date=parseInt(dateParts[0]);
					var dayStr = (date < 10 ? "0" + date : date );
					var monStr = (month < 10 ? "0" + (month) : month);
					
					var dateObject = new Date(yearStr,monStr, dayStr); 
					var dateString = "31/12/" + dateObject.getFullYear();
					yesElectionRecord.items[0].data.periodEnd = dateString;
				}
				
			}else if(lastElectionRecord){
				if(getElectionTypeCode(lastElectionRecord.data.type)!=3){
					lastElectionRecord.data.periodEnd = '';
				}else{
					var dateParts = lastElectionRecord.data.certificationDate.split("/");	
					
					
					var yearStr=parseInt(dateParts[2])+5;
					var month=parseInt(dateParts[1]);
					var date=parseInt(dateParts[0]);
					var dayStr = (date < 10 ? "0" + date : date );
					var monStr = (month < 10 ? "0" + (month) : month);
					
					var dateObject = new Date(yearStr,monStr, dayStr); 
					var dateString = "31/12/" + dateObject.getFullYear();
					lastElectionRecord.data.periodEnd = '';
				}
			}
			_actualGridDataStore.remove(records.items[0]);
			_actualGridDataStore.commitChanges();
			consolidateEventRecords(_self.DEL);
			tempRecord.data['runMode'] = _self.DEL;
			//tempRecord.commit();
			_self.updatesFlag=true;
		
		}
		
	}
	
	function setElectionGridBasedOnFilter(electionType){
		if(electionType!='All')
			{
		_resources.grids['rdspElectionsGrid'].getStore().filter('type', electionType);
			}
		else
			{
			_resources.grids['rdspElectionsGrid'].getStore().clearFilter(true);
			_resources.grids['rdspElectionsGrid'].store.filterBy(function(record) {
				return record;
			});
			}
		if(_resources.grids['rdspElectionsGrid'].getStore().getCount() > 0)
			{
			_resources.grids['rdspElectionsGrid'].getSelectionModel().selectFirstRow();
			}
	}
	
	
	function validateCertDate(value){
		//Validation with DOB
		var valueDate=DesktopWeb.Util.stringToDate(value,'dmy');
		var dobDate=this._beneDOB;
		if(valueDate <= dobDate)
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
			if(selectedElection == '2')
			{
				//get records from grid for SDSP
				var gridRecords=_actualGridDataStore;
				if(gridRecords.data.length > 0)
				{
					var queryRecords=gridRecords.queryBy(function(record){
						return record.data.type == '2' && record.data.elected == 'No';
					});
					if(queryRecords.length >0){
						var prevSDSPEndDate=queryRecords.items[0].data.periodStart;
						var dateParts = prevSDSPEndDate.split("/");
						var year=parseInt(dateParts[2]);
						var month=parseInt(dateParts[1])+24;
						var date=parseInt(dateParts[0]);
						
						var dateObject = new Date(year, month, date); // month is 0-based
					//Compare dates
					if(dateObject > valueDate)
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
		if(valueDate < _rdspIncepDate)
		{
		return 'Inception date must be on or after RDSP start date ' +_rdspIncepDate;
		}	

		if(valueDate < dobDate)
			{
			return 'Inception Date must be on or after beneficiary\'s date of birth! ';
			}
			

		return true;
		
	}
	
	
	function setMinDate(){
		var dobDate=DesktopWeb.Util.stringToDate(_resources.fields['BeneDOB'].getValue(),'dmy');
		var incepDate=DesktopWeb.Util.stringToDate(_resources.fields['IncepDate'].getDisplayDateString(),'dmy');
		this._incepDate=incepDate;
		if(_rdspIncepDate < dobDate){
			this._minDate=dobDate;
			_resources.fields['IncepDate'].minValue = dobDate;
		}
		else{
			this._minDate=DesktopWeb.Util.stringToDate(_rdspIncepDate,'dmy');
			_resources.fields['IncepDate'].minValue = this._minDate;
		}	
		if(incepDate > this._minDate){
			_resources.fields['CertificationDatePicker'].minValue = incepDate;
			_resources.fields['TransactionDatePicker'].minValue = incepDate;
		}
		else
			{
			_resources.fields['CertificationDatePicker'].minValue = this._minDate;
			_resources.fields['TransactionDatePicker'].minValue = this._minDate;
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
		_resources.fields['TransactionDatePicker'].value = DesktopWeb.Util.stringToDate(date,'dmy');
	}
	
	function getLastDTCEligibleYear(){
		var sortedDtcEligibleRecords = sortStoreByPeriodEnd(_actualEligibilityDataStore);
		var lastDtcEligibleDate;
		for(var i=0;i<sortedDtcEligibleRecords.length;i++){
			if(sortedDtcEligibleRecords.items[i].data.type == '4'){
				lastDtcEligibleDate= sortedDtcEligibleRecords.items[i].data.periodEnd;
			}
		}
		if(lastDtcEligibleDate){
		var dateParts = lastDtcEligibleDate.split("/");
		return parseInt(dateParts[2]);
		}
		return "";
	}

	

	// PUBLIC ITEMS *************************************
	return {
		 ADD				: 'a'
		,MOD				: 'm'
		,DEL				: 'd'
		,REVOKE				: 'r'	
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
			
			JRDSP.Util.sendRequestToDesktopWeb('accountService','getContractRegistrationStatusDescription','','POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,contractRegistrationStatusResponseHandler);
			
			function contractRegistrationStatusResponseHandler(response) {
				var statusList = IFDS.Xml.getNode(response.responseXML, "//List[@listName='statusDescription']");
				populateKeyValues(statusList);							
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
		,validateCertDate:validateCertDate
		,validateTransactionDate:validateTransactionDate
		,getElectionTypeCode:getElectionTypeCode
		,enableOKButtonPopUp : enableOKButtonPopUp
		,validateIncepDate:validateIncepDate
		,setMinDate:setMinDate
		,populateDropdownList:populateDropdownList
		,getElectionType:getElectionType
		,resetList:resetList
		,checkFlagsForModification : checkFlagsForModification
		,getUpdatedRecordCount:getUpdatedRecordCount
		,setCycleDate:setCycleDate
		,checkValidAction:checkValidAction
		,getButtonErrorMsg:getButtonErrorMsg
		,getLastDTCEligibleYear:getLastDTCEligibleYear
		,addBtnValidation:addBtnValidation
		,addBtnValidationMsg:addBtnValidationMsg
	}
};