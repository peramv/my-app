/*******************************************************************************
 * @file RDSPTransactionsInterface.Controller.js
 * @author Danil Gorelic
 * @desc Controller JS file for RDSPTransactionsInterfaces.
 ******************************************************************************/

DesktopWeb.ScreenController = function() {
	// PRIVATE VARIABLES *************************************

	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	var _self = null;
	var errorMessageList = null;
	var refusalReasonList = null;
	var sinIssueList = null;
	var severeErrorDescList = null;
	var sirValidationList = null;
	var descriptionLabels = ['refusalReasonLabel','sinIssueLabel','severeErrorCodeLabel','sexIssueLabel','surnameIssueLabel','birthDateIssueLabel','givenNameIssueLabel'];
	var SIRValidations = ['sinIssueLabel','sexIssueLabel','surnameIssueLabel','birthDateIssueLabel','givenNameIssueLabel'];
	var _incomingRecordTypes = null;
	var _outgoingRecordTypes = null;
	var _allRecordTypes = null;
	
	function isValidStatus(newStatus, currStatus) {
		switch(newStatus) {
			case 'Hold':
				return currStatus === 'New';
				
			case 'ReadyToSend':
				return currStatus === 'Hold' || currStatus === 'Refused' || currStatus === 'Rejected';
		}
		
		return false;
	}
	
	function updateStatus() {
		if(!_resources.fields['NewStatus'].getSelectedRecord()) return;
		
		var status = _resources.fields['NewStatus'].getSelectedRecord().data.code;	
		var grid = _resources.grids['rdspTransGrid'];
		var valid = true;
		var changed = false;
		
		grid.store.each(function(record) {
			record.data.error = false;
			if (record.data.checked) {
				if (isValidStatus(status, record.data.serverStatus)) {
					changed = true;
					record.data.status = status;
					record.data.checked = false;
					record.data.changed = true;
				}
				else {
					valid = false;
					record.data.error = true;
				}	
			}
			else {
				changed |= record.data.changed;
			}
		});
		
		if (!valid) {

			Ext.Msg.show({
                title: 'Error',
                msg: 'Invalid status change',
                modal: false,
                icon: Ext.Msg.ERROR,
                buttons: Ext.Msg.OK
            });
		}
		
		grid.getView().refresh();
		return _self.updatesFlag = changed && valid;
	}
	
	function refresh(start, count) {
		clearRecordDetailsGrid();
		if (!_resources.fields['AccountNo'].validate()) {
			return;
		}
		
		var account = _resources.fields['AccountNo'].getValue();
		if (account.length == 0) {
			account = "0";
		}
		
		var contextPath="files";
		var routePath = "fileTransactions";

		DesktopWeb._SCREEN_PARAM_MAP.accountNumber = account;
		DesktopWeb._SCREEN_PARAM_MAP.fileType = _resources.fields['FileType'].getSelectedRecord().data.code;
		DesktopWeb._SCREEN_PARAM_MAP.recordType = _resources.fields['RecordType'].getSelectedRecord().data.code;
		DesktopWeb._SCREEN_PARAM_MAP.status = _resources.fields['Status'].getSelectedRecord().data.code;
		
		DesktopWeb._SCREEN_PARAM_MAP.start = start;
		DesktopWeb._SCREEN_PARAM_MAP.count = count;
		
		JRDSP.Util.sendRequestToDesktopWeb(contextPath, routePath, '', 'POST_Inquiry', DesktopWeb._SCREEN_PARAM_MAP, null, responseHandler);
        
		function responseHandler(success, responseXML) {
			var grid = _resources.grids['rdspTransGrid'];
			var records_count;
			
			if(start) {
				var store = grid.getStore();
				var records = IFDS.Xml.getNodes(success.responseXML, '/TransactionsRecordsResponse/records');
				records_count = records.length;
				
				for (var i = 0; i < records.length; i++) {
					var record = {};
					
					for(var j = 0; j < records[i].childNodes.length; ++j) {
						record[records[i].childNodes[j].nodeName] = records[i].childNodes[j].nodeTypedValue;
						record.checked = false;
						record.changed = false;
					}
					
					store.add(new store.recordType(record));
				}
			}
			else {
				var records = IFDS.Xml.getNodes(success.responseXML, '/TransactionsRecordsResponse');
				grid.getStore().loadData(records, false);
				grid.getSelectionModel().selectRow(0);
				records_count = grid.getStore().getCount();
			}
			
			if (records_count < _resources.pageSize) {
				_resources.buttons['moreBtn'].disable();
			}
			else {
				_resources.buttons['moreBtn'].enable();
			}	
		}
	}
	
	function initResources(config, account) {
		var defaultVal;
		var combo = _resources.fields['FileType'];
		var list = IFDS.Xml.getNode(config, "//List[@listName='FileTypes']");

		if (account) {
			_resources.fields['AccountNo'].setValue(account);
			_resources.fields['AccountNo'].setReadOnly(true);
			defaultVal = IFDS.Xml.getNode(list, "*[3]/value").text;
		} else {
			var all = IFDS.Xml.getNode(config, "//List[@listName='FileTypes']/Element[code='All']");
			var incoming = IFDS.Xml.getNode(config, "//List[@listName='FileTypes']/Element[code='02']");
			IFDS.Xml.deleteNode(all);
			IFDS.Xml.deleteNode(incoming);
			defaultVal = IFDS.Xml.getNode(list, "*[1]/value").text;
		} 

		combo.loadData(list);
		combo.setValue(defaultVal);
		
		combo = _resources.fields['RecordType'];
		list = IFDS.Xml.getNode(config, "//List[@listName='RecordTypes']");
		
		defaultVal = IFDS.Xml.getNode(list, "*[1]/value").text;
		combo.loadData(list);
		combo.setValue(defaultVal);
		
		initRecordTypes(config);
		
		combo = _resources.fields['Status'];
		list = IFDS.Xml.getNode(config, "//List[@listName='Statuses']");
		defaultVal = IFDS.Xml.getNode(list, "*[1]/value").text;
		combo.loadData(list);
		combo.setValue(defaultVal);
		
		combo = _resources.fields['NewStatus'];
		list = IFDS.Xml.getNode(config, "//List[@listName='NewStatuses']");
		combo.loadData(list);
		
		refresh(0, _resources.pageSize);
	}

	function initRecordTypes(config) {
		var recordTypesIncoming = IFDS.Xml.getNodes(config, "//Element[@fileType='incoming']");
		var recordTypesOutgoing = IFDS.Xml.getNodes(config, "//Element[@fileType='outgoing']");
		var recordTypesAllIncoming = IFDS.Xml.getNodes(config, "//Element[@fileType='all']");
		var copyOfconfig = IFDS.Xml.cloneDocument(config);
		var recordTypesAllOutgoing = IFDS.Xml.getNodes(copyOfconfig, "//Element[@fileType='all']");
		var recordTypes = IFDS.Xml.getNode(config, "//List[@listName='RecordTypes']");
		var i;
		
		_allRecordTypes = IFDS.Xml.cloneDocument(recordTypes);
		
		var xmlDoc = IFDS.Xml.newDocument("List");
		var lstIncoming = IFDS.Xml.getNode(xmlDoc, "//List");
		IFDS.Xml.addAttribute(lstIncoming, "listName", "RecordTypes");
		for(i = 0; i < recordTypesAllIncoming.length; i++) {
			IFDS.Xml.appendNode(lstIncoming, recordTypesAllIncoming[i]);
		}
		for(i = 0; i < recordTypesIncoming.length; i++) {
			IFDS.Xml.appendNode(lstIncoming, recordTypesIncoming[i]);
		}

		_incomingRecordTypes = lstIncoming;
		
		xmlDoc = IFDS.Xml.newDocument("List");
		var lstOutgoing = IFDS.Xml.getNode(xmlDoc, "//List");
		IFDS.Xml.addAttribute(lstOutgoing, "listName", "RecordTypes");
		for(i = 0; i < recordTypesAllOutgoing.length; i++) {
			IFDS.Xml.appendNode(lstOutgoing, recordTypesAllOutgoing[i]);
		}
		for(i = 0; i < recordTypesOutgoing.length; i++) {
			IFDS.Xml.appendNode(lstOutgoing, recordTypesOutgoing[i]);
		}
		
		_outgoingRecordTypes = lstOutgoing;
	}

	function updateRecordType(fileTypeCode) {
		var combo = _resources.fields['RecordType'];
		var data = null;
		if(fileTypeCode === '01') {
			data = _outgoingRecordTypes;
		} else if(fileTypeCode === '02') {
			data = _incomingRecordTypes;
		} else {
			data = _allRecordTypes;
		}
		combo.loadData(data);
		var defaultVal = IFDS.Xml.getNode(data, "*[1]/value").text;
		combo.setValue(defaultVal);
	}
	
	function initEventLogErrors(eventLogErrors) {
		var list = IFDS.Xml.getNode(eventLogErrors, "//List[@listName='Errors']");
		errorMessageList = IFDS.Xml.getNode(eventLogErrors, "//List[@listName='Errors']");
	}
	
	function initRefusalReasons(refusalReasons) {
		var list = IFDS.Xml.getNode(refusalReasons, "//List[@listName='RefusalReasons']");
		refusalReasonList = IFDS.Xml.getNode(refusalReasons, "//List[@listName='RefusalReasons']");
	}
	
	function initSinIssues(sinIssues) {
		var list = IFDS.Xml.getNode(sinIssues, "//List[@listName='SinIssues']");
		sinIssueList = IFDS.Xml.getNode(sinIssues, "//List[@listName='SinIssues']");
	}
	
	function initSevereErrorDescs(severeErrorDescriptions) {
		var list = IFDS.Xml.getNode(severeErrorDescriptions, "//List[@listName='SevereErrorDescriptions']");
		severeErrorDescList = IFDS.Xml.getNode(severeErrorDescriptions, "//List[@listName='SevereErrorDescriptions']");
	}
	
	function initSirValidations(sirValidations) {
		var list = IFDS.Xml.getNode(sirValidations, "//List[@listName='SirValidations']");
		sirValidationList = IFDS.Xml.getNode(sirValidations, "//List[@listName='SirValidations']");
	}
	
	function getIndividualEventLogDetails(eventId, rowNum) {
		var contextPath="files";
		var routePath="recordDetails/"+ eventId + "/" + rowNum;		
		_service = "RecordDetails";
			
		JRDSP.Util.sendRequestToDesktopWeb(contextPath,routePath,_service,'POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,
			null,responseHandlerSuccess,responseHandlerFailure);
		function responseHandlerSuccess(success, responseXML)
		{
			setRecordDetails(success.responseXML);
		}

        function responseHandlerFailure(failure, responseXML) {
            DesktopWeb.Util.displayError("No event log details found. Please contact Administrator!");
		}
	}
	
	function setRecordDetails(response) {
		var fieldNames;
		clearRecordDetailsGrid();
	
		var count = response.childNodes[1].childNodes.length;
		var firstColumn, secondColumn;
		
			
			if(count!=0) {
				if(count%2 == 0) {
					firstColumn = count/2;
				} else {
					firstColumn = (count+1)/2;
				}
				secondColumn = count - firstColumn;
			Ext.getCmp('errorDetails').hide();
			Ext.getCmp('recordDetails').hide();
				for(var i=0; i< firstColumn; i++) {
					var node = response.childNodes[1].childNodes[i];
				var compName = "recordDetails-id1";
					
				displayRecordDetails(response, node, compName);
					}
				for(var j=firstColumn; j< count; j++) {
					var node = response.childNodes[1].childNodes[j];
				var compName = "recordDetails-id2";
				displayRecordDetails(response, node, compName);										
			}
		}
	    Ext.getCmp('interfaceTransactions_id').doLayout();
	}
	function displayRecordDetails(response, node, compName) {		
		var recordType = IFDS.Xml.getNodeValue(response, '//' + "recordType"); 
					var fieldName = node.nodeName + 'Label';
		var nodeName = node.nodeName;
		if(nodeName == "errorCodes") {
			Ext.getCmp('errorDetails').show();
			var errorMessageString = IFDS.Xml.getNodeValue(response, '//' + nodeName);
			var errorCodes = errorMessageString.split(",");
			var completeErrors = ""; 
			for(var k=0; k<errorCodes.length; k++) {
				var listElement = IFDS.Xml.getNode(errorMessageList, "//Element[code='" + errorCodes[k] + "']");
				var errorDescription = listElement == null ? "Error Code: " + errorCodes[k] : IFDS.Xml.getNodeValue(listElement, 'value') ;
				completeErrors = completeErrors + errorDescription + "<br/><br/>&#8239;";
			}
			var fieldName = "errorMessagesLabel";
					_resources.fields[fieldName].destroy();
			_resources.fields[fieldName].setText(completeErrors, false);			
			Ext.getCmp('errorDetails-id1').add(_resources.fields[fieldName]);
		} else {	
			Ext.getCmp('recordDetails').show();
			_resources.fields[fieldName].destroy();
			_resources.fields[fieldName].setText(IFDS.Xml.getNodeValue(response, '//' + nodeName));
					if(descriptionLabels.indexOf(fieldName) > -1) {
						addFieldDescriptions(fieldName, recordType);
					}
			Ext.getCmp(compName).add(_resources.fields[fieldName]);
		}
	}
	
	function addFieldDescriptions(labelName, recordType) {
		if(labelName == 'sinIssueLabel') {
			var discList = sinIssueList;
		}
		if(recordType == "801") {
			if(SIRValidations.indexOf(labelName) > -1) {
				var discList = sirValidationList;
			}
		} 
		if(labelName == 'sexIssueLabel') {
			var discList = severeErrorDescList;
		}
		if(labelName == 'refusalReasonLabel') {
			var discList = refusalReasonList;
		} 

		if(labelName == 'severeErrorCodeLabel') {
			var discList = severeErrorDescList;
		}

		
		if(_resources.fields[labelName].text != null && _resources.fields[labelName].text != "") {
			var element = IFDS.Xml.getNode(discList, "//Element[code='" + _resources.fields[labelName].text + "']");
			var finalValue = IFDS.Xml.getNodeValue(element, 'value') ;
			_resources.fields[labelName].setValue(_resources.fields[labelName].text + "-" + finalValue);
		}
	}
	
	function createDocument(qualifiedName) {
	    var prefixedNs = '', doc = new ActiveXObject('MSXML2.DomDocument');

	    prefixedNs = ' xmlns=""';
	    doc.loadXML('<' + qualifiedName + prefixedNs + '/>');
	    return doc;
	}
	
	function getDescription(type, config) {
		var value = IFDS.Xml.getNode(config, "//List[@listName='FileTypes']/Element[code='" + type + "']/value");
		return value ? value.text: '';
	}
	
	function clearRecordDetailsGrid() {
		JRDSP.Util.clearComponentDetails('recordDetails-id1');
		JRDSP.Util.clearComponentDetails('recordDetails-id2');
		JRDSP.Util.clearComponentDetails('errorDetails-id1');
	}
	
	// PUBLIC ITEMS *************************************
	return {
		init : function(res) {
			var account = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;

			JRDSP.Util.sendRequestToDesktopWeb('files','getConfig','','POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,responseHandler);

			function responseHandler(success){
				initResources(success.responseXML, account);
			}
			JRDSP.Util.sendRequestToDesktopWeb('files','getEventLogErrors','','POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,eventLogErrorsResponseHandler);
			
			function eventLogErrorsResponseHandler(response) {
				initEventLogErrors(response.responseXML);
			}
			JRDSP.Util.sendRequestToDesktopWeb('files','getRefusalReason','','POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,refusalReasonResponseHandler);
			
			function refusalReasonResponseHandler(response) {
				initRefusalReasons(response.responseXML);
			}
			
			JRDSP.Util.sendRequestToDesktopWeb('files','getSinIssues','','POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,sinIssuesResponseHandler);
			
			function sinIssuesResponseHandler(response) {
				initSinIssues(response.responseXML);
			}
			
			JRDSP.Util.sendRequestToDesktopWeb('files','getSevereErrorDescriptions','','POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,severeErrorDescResponseHandler);
			
			function severeErrorDescResponseHandler(response) {
				initSevereErrorDescs(response.responseXML);
			}
			
			JRDSP.Util.sendRequestToDesktopWeb('files','getSirValidations','','POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,sirValidationResponseHandler);
			
			function sirValidationResponseHandler(response) {
				initSirValidations(response.responseXML);
			}
			
			
		},
		doUpdate: function() {
			var grid = _resources.grids['rdspTransGrid'];
			var requestXML = IFDS.Xml.newDocument('records');
			
			grid.store.each(function(record) {
				if (record.data.changed) {
					var tran = IFDS.Xml.addSingleNode(requestXML, 'record');
					IFDS.Xml.addSingleNode(tran, 'id', record.data.id);
					IFDS.Xml.addSingleNode(tran, 'row', record.data.row);
					IFDS.Xml.addSingleNode(tran, 'status', record.data.status);
				}
			});
									
			if(requestXML.firstChild.childNodes.length) {
				JRDSP.Util.sendRequestToDesktopWeb('files', 'status', '', 'POST', DesktopWeb._SCREEN_PARAM_MAP, requestXML, responseHandler);
				
				function responseHandler(success) {
					var failed = [];
					
					grid.store.each(function(record) {
						if (record.data.checked) {
							var selector = "//transaction[id=" + record.data.id + " and row=" + record.data.row + "]"
							var node = IFDS.Xml.getNode(success.responseXML, selector);
							
							if (node) {
								var isSuccess = IFDS.Xml.getNodeValue(node, "success") === "true";
								
								if (isSuccess) {
									record.data.checked = false;
									record.data.status = status;
								}
								else {
									failed.push(record.data.esdcTransNo);
								}
							}
							else {
								failed.push(record.data.esdcTransNo);
							}
						}
					});
					
					if (_self.updatesFlag = failed.length != 0) {
						Ext.Msg.show({
			                title: 'Error',
			                msg: 'Change failed for ' + failed.join(', '),
			                modal: false,
			                icon: Ext.Msg.ERROR,
			                buttons: Ext.Msg.OK
			            });
					}
					else {
						_resources.screenButtons.items[0].disable();
					}
					
					grid.getView().refresh();
				}
			}
		},
		
		openActionPopup : function(action, popupName, dtceligible) {
			_resources.popups[popupName].init(action, dtceligible);
			_resources.popups[popupName].show();
		},
		getServiceTitle : function(code) {
			if (code == null) {
				return 'Election';
			}
				
			if (code == "Fund") {
				return _translationMap['FIFundScreen'];
			}
		},
		updatesFlag: false,
		updateStatus : updateStatus,
		refresh: refresh,
		getIndividualEventLogDetails : getIndividualEventLogDetails,
		initRefusalReasons : initRefusalReasons,
		initSinIssues : initSinIssues,
		initSevereErrorDescs : initSevereErrorDescs,
		initSirValidations : initSirValidations,
		updateRecordType : updateRecordType
	}
};