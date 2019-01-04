/*********************************************************************************************
 * @file	ClassCopy.Controller.js
 * @author	Rod Walker	
 * @desc	Controller JS file for Fund Class Copy screen
 *********************************************************************************************/
 /*
 *  History : 
 *
 *  11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54443
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached.   
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _classSearchView = 'classSearch';
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	var _addClassXML = null;
	
	var _addClassValidateService = 'validateFundInfo';
	var _commitService = 'dtCopyClassUpd';
	
	// PRIVATE METHODS ****************************************	
	function populateClassData(classSearchXML)
	{		
		_resources.grids['classes'].loadData(IFDS.Xml.getNode(classSearchXML, '*/Classes'), null);
	}
	
	function storeContextErrors(errorNodes)
	{
		for (var i = 0; i < errorNodes.length; i++)
		{
			var table = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/xmlElementName');
			var elementSource = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
			var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');
			
			var record = _resources.grids['classes'].getStore().getAt(elementSource);
			record.set('errMsg', errMsg);
			_resources.grids['classes'].getStore().commitChanges();
		}
	}

	// PUBLIC ITEMS *************************************
	return {
		ADD: 'add'
		,MOD: 'mod'
		,updatesFlag: false
						
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			_resources.grids['classes'].disableAllButtons();
			_self.updateClassButtons();
			
			var initXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(initXML, 'runMode', 'init');
			
			/*Assign initial value to copyFromFund and copyFund for screen initiation*/
			IFDS.Xml.addSingleNode(initXML, 'copyFromFund', 'dummy');
			IFDS.Xml.addSingleNode(initXML, 'copyToFund', 'dummy');
			DesktopWeb.Ajax.doSmartviewUpdate(_commitService, null, initXML, responseHandler, _translationMap['ProcMsg_Saving']);
			
			function responseHandler(success, responseXML, contextErrors)
			{
				
	            var allOptions = ["basicInfo","feeParameters","shareholderGroup","registeredTrustee","perfFeeParms","eventSchedule","cusTrdeAndValtDate","partnership"];
				var currentNode;
			
			    if (success)
			    {				  
				    for(i=0 ; i < allOptions.length; i++){
					
						currentNode = IFDS.Xml.getNode(responseXML,'//'+allOptions[i]);
						
						if(currentNode.getAttribute('check') == 'yes'){
							_resources.fields[allOptions[i]].setValue(true);
					    }else{
							_resources.fields[allOptions[i]].setValue(false);
						}
						        			
					    if(IFDS.Xml.getNodeValue(responseXML, '//'+allOptions[i]) == "yes"){
							_resources.fields[allOptions[i]].enableField();
						}else{
							_resources.fields[allOptions[i]].disableField();
						}
						
					}
			    }else{
					//IN3240505 - DesktopWeb.Ajax.doSmartviewUpdate is handling to display messages for warning an error.
				    //alert("Error occurs during fund class copy screen initiation.");
					Ext.getCmp("fundClassCopyScreen").disable();
					Ext.getCmp("okBtn").disable();
					
			    }
		    }
			
		}
		
		,doLookup: function()
		{			
			var dataXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(dataXML, 'fundCode', _resources.fields['fromFund'].getValue());

			DesktopWeb.Ajax.doSmartviewAjax(_classSearchView, null, dataXML, responseHandler, "Searching ...")
			
			function responseHandler(success, responseXML)
			{		
				if (success)
				{
					populateClassData(responseXML);
					_self.updatesFlag = true;
				}
			}
		}
		
		,doValidate: function()
		{
		   var warningList = _resources.grids['classes'].getStore().queryBy(
			    function(record){
				return (record.get('perfFeeFlag') == 'no')?record:null;
			    }
		   );	
		    
           if(warningList.length > 0 && _resources.fields['perfFeeParms'].getValue() ){
			    
			  var listResult = '';
			  var fundClass = '';
			  
			  for(i = 0; i < warningList.length; i++)
			  {
			    fundClass = _resources.fields['fromFund'].getValue() + '/' + warningList.itemAt(i).get('classCode');
				
				if (listResult.indexOf(fundClass) < 0){
					listResult += ',' + fundClass;
			    }
			  }
			  listResult = listResult.substring(1);
				
	          var warningMsg  = listResult + " : Not be Performance Fee Fund Class so it can be copied for other options excepting Performance Fee Parameter option."
			                               + " Do you want to continue copy?";

			  DesktopWeb.Util.displayYesNo(warningMsg, confirmHandler);
			  
			  function confirmHandler(btn)
			  {
				if (btn == 'yes')
				{
					validateStatus = true;
					DesktopWeb.Util.commitScreen();
				}
			  }
		   
		  }else{	  
		        validateStatus = true;
				DesktopWeb.Util.commitScreen();
		  }
		}
				
		,doUpdate: function()
		{
		    var recordNumber = 0;
            var updateStatus = null;
		    var classNode = null;
			var classInfoNode = null;
			var updateXML = IFDS.Xml.newDocument('data');
			var records = _resources.grids['classes'].getAllRecords();
			
			IFDS.Xml.addSingleNode(updateXML, 'runMode', 'update');
			IFDS.Xml.addSingleNode(updateXML, 'copyFromFund', _resources.fields['fromFund'].getValue());
			IFDS.Xml.addSingleNode(updateXML, 'copyToFund', _resources.fields['toFund'].getValue());
			IFDS.Xml.addSingleNode(updateXML, 'copyBasicClsInfo', transformChkbk(_resources.fields['basicInfo'].getValue()));
			IFDS.Xml.addSingleNode(updateXML, 'copyFeeParms', transformChkbk(_resources.fields['feeParameters'].getValue()));
			IFDS.Xml.addSingleNode(updateXML, 'copyShGrpFunds', transformChkbk(_resources.fields['shareholderGroup'].getValue()));
			IFDS.Xml.addSingleNode(updateXML, 'copyRegTrustee', transformChkbk(_resources.fields['registeredTrustee'].getValue()));
			IFDS.Xml.addSingleNode(updateXML, 'copyPerfFeeParms', transformChkbk(_resources.fields['perfFeeParms'].getValue()));
			IFDS.Xml.addSingleNode(updateXML, 'copyEventSchedule', transformChkbk(_resources.fields['eventSchedule'].getValue()));
			IFDS.Xml.addSingleNode(updateXML, 'copyCusTrdeAndValtDate', transformChkbk(_resources.fields['cusTrdeAndValtDate'].getValue()));
			IFDS.Xml.addSingleNode(updateXML, 'copyPShip', transformChkbk(_resources.fields['partnership'].getValue()));
			classNode = IFDS.Xml.addSingleNode(updateXML, 'Classes');
			
			Ext.each(records, function(record){
			classInfoNode = IFDS.Xml.addSingleNode(classNode, 'CopyClassInfo');
			IFDS.Xml.addAttribute(classInfoNode, 'RecordSource', recordNumber++);
			IFDS.Xml.addSingleNode(classInfoNode, 'copyFromClass',record.get('classCode'));
			IFDS.Xml.addSingleNode(classInfoNode, 'copyToClass',record.get('newClassCode'));
			IFDS.Xml.addSingleNode(classInfoNode, 'deff', DesktopWeb.Util.getSMVDateValue(record.get('dateEff')));
			IFDS.Xml.addSingleNode(classInfoNode, 'isin',record.get('isin'));
			IFDS.Xml.addSingleNode(classInfoNode, 'cusip',record.get('cusip'));
			IFDS.Xml.addSingleNode(classInfoNode, 'wkn',record.get('wkn'));
			IFDS.Xml.addSingleNode(classInfoNode, 'extID',record.get('extFundId'));
			IFDS.Xml.addSingleNode(classInfoNode, 'fundLoadGrp',record.get('fundLoadGrp'));
			});
				
			DesktopWeb.Ajax.doSmartviewUpdate(_commitService, null, updateXML, responseHandler, _translationMap['ProcMsg_Saving']);
			
			function responseHandler(success, responseXML, contextErrors)
			{	
			    if (success)
			    {
				    alert("Fund class copy submitted successfully.");
						updateStatus = DesktopWeb._SUCCESS;
						updateXML = null;
			    }else{
						alert("Errors occured during fund class copy. Operation could not be completed.");
						storeContextErrors(contextErrors);
						updateStatus = DesktopWeb._FAIL 	
			    }
		    }
		    
			
			function transformChkbk(value)
			{
				return (value == 0)?'no':'yes';
			}
		
		return updateStatus;
		}
		
		,updateClassButtons: function()
		{
			if (_resources.grids['classes'].getAllRecords().length > 0)
			{				
				_resources.grids['classes'].enableButton('selectAllBtn');
			}
			else
			{		
				_resources.grids['classes'].disableButton('selectAllBtn');
			}
						
			if (_resources.fields['toFund'].getRawValue() != "")
			{
				_resources.grids['classes'].enableButton('addBtn');
			}
			else
			{
				_resources.grids['classes'].disableButton('addBtn');
			}
			
			if (_resources.grids['classes'].getSelectedRecord())
			{				
				_resources.grids['classes'].enableButton('removeBtn');
			}
			else
			{			
				_resources.grids['classes'].disableButton('removeBtn');
			}

			if (_resources.grids['classes'].getSelectionModel().getCount() == 1)
			{
				_resources.grids['classes'].enableButton('modBtn');
			}
			else
			{
				_resources.grids['classes'].disableButton('modBtn');	
			}		
		}
		
		,clearAll: function()
		{
			_resources.grids['classes'].clearData();
			_self.updateClassButtons();
		}

		,selectAll: function()
		{
			_resources.grids['classes'].getSelectionModel().selectAll();
			_self.updateClassButtons();
		}
		
		,remove: function()
		{
			var selectedRecords = _resources.grids['classes'].getSelectionModel().getSelections();			
			for (var i = 0; i < selectedRecords.length; i++)
			{
				_resources.grids['classes'].getStore().remove(selectedRecords[i]);
			}
			_self.updateClassButtons();
			_self.updatesFlag = true;
		}
		
		,openPopup: function(action)
		{
			if (action == _self.ADD)
			{
				_resources.grids['classes'].clearSelectedRecord();
			}
			else
			{
				var selectedRecords = _resources.grids['classes'].getSelectionModel().getSelections();			
				for (var i = 1; i < selectedRecords.length; i++)
				{
					_resources.grids['classes'].getSelectionModel().deselectRow(_resources.grids['classes'].getRecordIndex(selectedRecords[i]));
				}	
			}
						
			_resources.popups['classCopy'].init(action);
			_resources.popups['classCopy'].show();	
		}
		
		,saveFundClass: function(action, data)
		{

			var validateXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(validateXML, 'fundCodeFrom', _resources.fields['fromFund'].getValue());
			IFDS.Xml.addSingleNode(validateXML, 'classCodeFrom', data['classCode']);
			IFDS.Xml.addSingleNode(validateXML, 'fundCodeTo', _resources.fields['toFund'].getValue());
			IFDS.Xml.addSingleNode(validateXML, 'classCodeTo', data['newClassCode']);
			IFDS.Xml.addSingleNode(validateXML, 'deff', DesktopWeb.Util.getSMVDateValue(data['dateEff']));
			IFDS.Xml.addSingleNode(validateXML, 'wkn', data['wkn']);
			IFDS.Xml.addSingleNode(validateXML, 'isin', data['isin']);
			IFDS.Xml.addSingleNode(validateXML, 'cusip', data['cusip']);
			IFDS.Xml.addSingleNode(validateXML, 'extID', data['extFundId']);
			IFDS.Xml.addSingleNode(validateXML, 'fundLoadGrp', data['fundLoadGrp']);

			DesktopWeb.Ajax.doSmartviewAjax(_addClassValidateService, null,validateXML, responseHandler, _translationMap['ProcMsg_Validating']);
			
			function responseHandler(success,responseXML)
			{
				var perfFeeFlag = IFDS.Xml.getNodeValue(responseXML, '//perfFeeFlag');
				data['perfFeeFlag'] = perfFeeFlag;
				
				if(success){
					if(action == 'add'){
						_resources.grids['classes'].addRecord(data);
						_resources.grids['classes'].getSelectionModel().selectLastRow(false);
					}else if(action == 'mod'){
						data['errMsg'] = '';
						_resources.grids['classes'].updateSelectedRecord(data);								
					}
					_resources.grids['classes'].getSelectionModel().selectLastRow(false);
					_resources.popups['classCopy'].hide();
					_self.updatesFlag = true;
				}
			}
		}
	}	
}	