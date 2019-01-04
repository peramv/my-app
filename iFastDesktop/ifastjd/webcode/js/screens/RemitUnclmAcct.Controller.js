/*********************************************************************************************
 * @file	RemitUnclmAcct.Controller.js
 * @author	Kittichai Sopitwetmontree
 * @desc	Controller JS file for Remit Unclaimed Property Account screen
 *********************************************************************************************/

DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;	
	var _mstrXML = null;
	var _originalXML = null;
	var _initView = "dtRemitUnclmInit";
	var _reloadView = "dtRemitUnclmReload";
	var _vldtView = "dtRemitUnclmProc";
	var _updateView = "dtRemitUnclmProc";
	var _defaultValues = {};
	
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// PRIVATE METHODS ****************************************	
	function populateDropdowns(xml)
	{
		_resources.fields['cboPayType'].loadData(IFDS.Xml.getNode(xml, "//List[@listName='PayTypeList']"));	
	}	
	function storeDefaultValues(xml)
	{
		_defaultValues['PayTypeList'] = IFDS.Xml.getNodeValue(xml, "//ListSelection[@id='PayTypeList']");	
		
	}	
	function createMstrXML(xml)
	{	
	
		_mstrXML = null;
		_mstrXML = IFDS.Xml.newDocument("RemitUnclmAccts");		
		var remitUnclmAcctXMLArr = IFDS.Xml.getNodes(xml, '//RemitUnclmAccts/RemitUnclmAcct');
		var valnXML = null;
		var crysXML = null;
		
		Ext.each(remitUnclmAcctXMLArr, function(remitUnclamAcctXML){
			IFDS.Xml.appendNode(_mstrXML, remitUnclamAcctXML);	
			
		});	
	}	

	function getUpdateRequest(pDoMarkBadExist, pRunMode)
	{		
		var requestXML = IFDS.Xml.newDocument("data");
		var xml; // = IFDS.Xml.newDocument("RemitUnclmAccts");
		var xmlScales;
		
		IFDS.Xml.addSingleNode(requestXML, 'requestAccount', IFDS.Xml.getNodeValue(_mstrXML, "//RemitUnclmAccts/RemitUnclmAcct/accountNum"));		
		IFDS.Xml.addSingleNode(requestXML, 'doMarkBadExist', pDoMarkBadExist);
		IFDS.Xml.addSingleNode(requestXML, 'payType', _resources.fields['cboPayType'].getValue());
		IFDS.Xml.addSingleNode(requestXML, 'runMode', pRunMode);		
		
		return requestXML;
	}	

	// PUBLIC ITEMS *************************************
	return {
		ADD: 'add'
		, MOD: 'mod'
		, DEL: 'del'
		, UNCH: 'unch'	
		, SEQADD: '3'
		, SEQMOD: '2'
		, SEQDEL: '1'
		, SEQUNCH: '0'
		, YES: 'yes'
		, NO: 'no'
		, NONE: 'none'
		, ALL: 'all'
		, updatesFlag: false	
		, init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;

			var requestXML = IFDS.Xml.newDocument("data");
			
			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, requestXML, responseHandler, _translationMap['DoLoading']);
			
			function responseHandler(success, responseXML)
			{
				if (success)
				{			
					populateDropdowns(responseXML);	
					storeDefaultValues(responseXML);					
					_self.initDefaultValues();
					// disable all action buttons.
					_resources.buttons['cmdScreenButtonSubmit'].disable();
					_resources.fields['cboPayType'].disable();				

				}
			}
		}
		, openActionPopup: function(popupName, action)
		{		
			_resources.popups[popupName].show();
		}
		, doSearch: function(more)
		{
			var requestXML = IFDS.Xml.newDocument("data");		
			if (_self.readyToSearch())
			{
				IFDS.Xml.addSingleNode(requestXML, "requestAccount", _resources.fields['suggestAccount'].getValue());
				
				if (requestXML)
				{
					DesktopWeb.Ajax.doSmartviewAjax(_reloadView, null, requestXML, responseHandler, _translationMap['DoSearching']);

					function responseHandler(success, responseXML)
					{
						if (success)
						{				
							createMstrXML(responseXML);			
							// display information
							
							var remitUnclmAcctXMLArr = IFDS.Xml.getNodes(_mstrXML, '//RemitUnclmAccts/RemitUnclmAcct');
							for (var i = 0; i < remitUnclmAcctXMLArr.length; i++)
							{							
								var Name = '';
								Name = IFDS.Xml.getNodeValue(remitUnclmAcctXMLArr[i],'lastName') + ', ' + IFDS.Xml.getNodeValue(remitUnclmAcctXMLArr[i],'firstName');
								
								_resources.fields['valName'].setValue(Name); 
								_resources.fields['valSIN'].setValue(IFDS.Xml.getNodeValue(remitUnclmAcctXMLArr[i],'sinNum')); 
								_resources.fields['valTaxType'].setValue(IFDS.Xml.getNodeValue(remitUnclmAcctXMLArr[i],'taxTypeDesc')); 
								_resources.fields['cboPayType'].enable();									
							}
							_resources.buttons['cmdScreenButtonSubmit'].enable();

						}else{
								_resources.fields['valName'].setValue(''); 
								_resources.fields['valSIN'].setValue(''); 
								_resources.fields['valTaxType'].setValue(''); 
								_resources.fields['cboPayType'].disable();	
								_resources.buttons['cmdScreenButtonSubmit'].disable();
								
						}
						// init default value everytimes user search the new account even it's error or not. Actually, it is reset.
						_self.initDefaultValues();						
					}
				}
			
			}
		}
		, readyToSearch: function()
		{
			var retVal = true;
			_self.clearInfo();

			return retVal;
		}
		, clearInfo: function()
		{
			_resources.fields['valName'].setValue(''); 
			_resources.fields['valSIN'].setValue(''); 
			_resources.fields['valTaxType'].setValue(''); 
		}
		, translateTransType: function(pCode)
		{	

			return retVal==""?pCode:retVal;		
		}
		, doUpdate: function ()
		{
			/* Backup */
			var backupXML = IFDS.Xml.cloneDocument(_mstrXML);
			var updateStatus = null;	
			
			var isUPTradeExist = IFDS.Xml.getNodeValue(_mstrXML, "//RemitUnclmAccts/RemitUnclmAcct/isUPTradeExist");
			if(isUPTradeExist.toUpperCase() == "YES")
			{
				DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, getUpdateRequest("Yes", "Proc"), responseHandler, _translationMap['DoUpdate']);			
			}
			else
			{
				DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, getUpdateRequest("No", "Proc"), responseHandler, _translationMap['DoUpdate']);			
			}
			
			
			function responseHandler(success, responseXML, contextErrors)
			{
				_resources.popups['frmRemitUnclmAcct'].hide();
				if (success)
				{
					updateStatus = DesktopWeb._SUCCESS;					
				}
				else 
				{					
					updateStatus = DesktopWeb._FAIL; 	
				}
			}	

			return updateStatus;	
		}
		, doPreUpdate: function()
		{
			var isUPTradeExist = IFDS.Xml.getNodeValue(_mstrXML, "//RemitUnclmAccts/RemitUnclmAcct/isUPTradeExist");			
	
			if(isUPTradeExist.toUpperCase() == "YES")
			{	
			  DesktopWeb.Util.displayYesNo(_translationMap['PendingTradeExist'], confirmhandler);
			  
			  function confirmhandler(btn)
			  {
				if (btn == 'yes')
				{				
					DesktopWeb.Ajax.doSmartviewUpdate(_vldtView, null, getUpdateRequest("YES", "Val"), responseHandler, _translationMap['DoValidation']);			
					
					function responseHandler(success, responseXML, contextErrors)
					{
						
						if (success)
						{
							_self.updatesFlag = true;						
							DesktopWeb.Util.commitScreen();						
						}
						else 
						{					
							return;
						}
					}						
				
				}
			  }
			}
			else
			{		
				DesktopWeb.Ajax.doSmartviewUpdate(_vldtView, null, getUpdateRequest("NO", "Val"), responseHandler, _translationMap['DoValidation']);			
					
				function responseHandler(success, responseXML, contextErrors)
				{						
					if (success)
					{
						_self.updatesFlag = true;						
						DesktopWeb.Util.commitScreen();						
					}
					else 
					{					
						return;
					}
				}									

			}
			
		}
		, initDefaultValues: function()
		{
			_resources.fields['cboPayType'].setValue(_defaultValues['PayTypeList']);					
		}		
	
	}	
}	