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
		var status = _resources.fields['NewStatus'].getSelectedRecord().data.code;	
		var grid = _resources.grids['rdspTransGrid'];
		var valid = true;
		
		grid.store.each(function(record) {
			record.data.error = false;
			if (record.data.checked) {
				if (!isValidStatus(status, record.data.status)) {
					valid = false;
					record.data.error = true;
				}	
			}
		});
			
		if (valid) {
			_self.updatesFlag = true;
			DesktopWeb.Util.commitScreen();
		}
		else {
			Ext.Msg.show({
                title: 'Error',
                msg: 'Invalid status change',
                modal: false,
                icon: Ext.Msg.ERROR,
                buttons: Ext.Msg.OK
            });
			
			grid.getView().refresh();
		}
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
			var records = IFDS.Xml.getNodes(success.responseXML, '/TransactionsRecordsResponse');
			
			grid.getStore().loadData(records, false);
			grid.getSelectionModel().selectRow(0);
			
			if (grid.getStore().getCount() < _resources.pageSize) {
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
	
	function initEventLogErrors(eventLogErrors) {
		var list = IFDS.Xml.getNode(eventLogErrors, "//List[@listName='Errors']");
		errorMessageList = IFDS.Xml.getNode(eventLogErrors, "//List[@listName='Errors']");
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
		
		if(response.childNodes[1].childNodes[0].nodeName == "errorCodes") {
			_resources.fields['errorMessagesLabel'].setText(IFDS.Xml.getNodeValue(response, '//' + response.childNodes[1].childNodes[0].nodeName));
			var errorMessageString = IFDS.Xml.getNodeValue(response, '//' + response.childNodes[1].childNodes[0].nodeName);
			var errorCodes = errorMessageString.split(",");
			
			var completeErrors = ""; 
			for(var i=0; i<errorCodes.length; i++) {
				var listElement = IFDS.Xml.getNode(errorMessageList, "//Element[code='" + errorCodes[i] + "']");
				var errorDescription = listElement == null ? "Error Code: " + errorCodes[i] : IFDS.Xml.getNodeValue(listElement, 'value') ;
				completeErrors = completeErrors + errorDescription + "<br/><br/>&#8239;";
			}
			var fieldName = "errorMessagesLabel";
			_resources.fields[fieldName].destroy();
			_resources.fields[fieldName].setText(completeErrors, false);			
			Ext.getCmp('recordDetails-id3').add(_resources.fields['errorMessagesLabel']);
		} else {		
			if(count!=0) {
				if(count%2 == 0) {
					firstColumn = count/2;
				} else {
					firstColumn = (count+1)/2;
				}
				secondColumn = count - firstColumn;
				for(var i=0; i< firstColumn; i++) {
					var node = response.childNodes[1].childNodes[i];
					var fieldName = node.nodeName + 'Label';
					_resources.fields[fieldName].destroy();
					_resources.fields[fieldName].setText(IFDS.Xml.getNodeValue(response, '//' + response.childNodes[1].childNodes[i].nodeName));
					Ext.getCmp('recordDetails-id1').add(_resources.fields[fieldName]);
				}
				for(var j=firstColumn; j< count; j++) {
					var node = response.childNodes[1].childNodes[j];
					var fieldName = node.nodeName + 'Label';
					_resources.fields[fieldName].destroy();
					_resources.fields[fieldName].setText(IFDS.Xml.getNodeValue(response, '//' + response.childNodes[1].childNodes[j].nodeName));
					Ext.getCmp('recordDetails-id2').add(_resources.fields[fieldName]);
				}
			}
		}
	    Ext.getCmp('interfaceTransactions_id').doLayout();
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
		JRDSP.Util.clearComponentDetails('recordDetails-id3');
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
		},
		doUpdate: function() {
			var status = _resources.fields['NewStatus'].getSelectedRecord().data.code;	
			var grid = _resources.grids['rdspTransGrid'];
			var requestXML = IFDS.Xml.newDocument('records');
			
			grid.store.each(function(record) {
				if (record.data.checked) {
					var tran = IFDS.Xml.addSingleNode(requestXML, 'record');
					IFDS.Xml.addSingleNode(tran, 'id', record.data.id);
					IFDS.Xml.addSingleNode(tran, 'row', record.data.row);
				}
			});
									
			if(requestXML.firstChild.childNodes.length) {
				var contextPath="files";
				var routePath = 'status/' + status;
				
				JRDSP.Util.sendRequestToDesktopWeb(contextPath, routePath, '', 'POST', DesktopWeb._SCREEN_PARAM_MAP, requestXML, responseHandler);
		        
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
		getIndividualEventLogDetails : getIndividualEventLogDetails
	}
};