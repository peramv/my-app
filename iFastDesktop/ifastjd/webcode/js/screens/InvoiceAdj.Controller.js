 /**********************************************************************************************
 *
 * Procedure: InvoiceAdj.Controller.js
 *
 * Purpose  : Invoice Adjustment screen for adjusting the Payments of Invoice			  
 *
 * Notes	: Open screen by -> Invoice Instructions screen (Invoice Button) 
 *
 * History  : 
 *	
 *		5 Mar 2013 Pannarasi Wongpakdee PETP0206635 FN01 MFR MFI Enhancments
 *			- Created
 *
 *     21 May 2013 Supareuk Sukjaitham  PETP0206635 FN01 T53598 IN3331655
 *          - Ignore error 15 - no data found when init search
 *
 *     27 May 2013 Pannarasi Wongpakdee PETP0206635 FN01 T53618 IN3336672
 *			- Added Max/Min Value for OffsetAmount field
 *			- Disabled Print button by checking three new fields on grid
 *			- Updated flag as NO to not allow modify all fields as blank
 *
 *     13 Jun 2013 Pannarasi Wongpakdee PETP0206635 FN01 T53714 IN3346061
 *			- Displayed OffeSetAmount as blank for new payment (status 05-Approved Verified)
 *			- Displayed Status from Misc-Info list
 *
 *     19 Aug 2013  G. Thawornwachirakun PETP0206635 FN01 T54037 DFT0013578
 *          - Modify split comment from the number of character to split by enter
 *
 *     11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54444
 *          - Fix display date format follows dateFormatDisplay parameter 
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *			- Fixed screens don't response when user's profile has too many slots attached.
 * 
 **********************************************************************************************/
 
 DesktopWeb.ScreenController = function()
 {		
	// PRIVATE VARIABLES *************************************
	var _MOD = 'm';
	
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();

	var _selectedInvoiceAdj = null;
	var _selectedInvoiceAdjIndex = null;

	var _invoiceAdjXML = null;
	var _invoiceAdjReqXML = null;
	
	var _initView = 'dtInvoiceAdjInq';
	var _updateView = 'dtInvoiceAdjUpd';	
	var _printView = 'dtInvoicePrint';	
	
	var _nextStartRecNum = 1;
	var _requestRecNum = 25;
	
	var _permissionsMap = {};
	
	
	// PRIVATE METHODS ****************************************	
	function storePermissions(xml)
	{
		_permissionsMap['mod'] = IFDS.Xml.getNodeValue(xml, '//Permissions/modPerm').toLowerCase();
		_permissionsMap['add'] = IFDS.Xml.getNodeValue(xml, '//Permissions/addPerm').toLowerCase();
		_permissionsMap['del'] = IFDS.Xml.getNodeValue(xml, '//Permissions/delPerm').toLowerCase();
		_permissionsMap['inq'] = IFDS.Xml.getNodeValue(xml, '//Permissions/inqPerm').toLowerCase();
	}
	
	function loadInvoiceAdj()
	{		
		var paramXML = IFDS.Xml.newDocument('data');
		var billInstrID = DesktopWeb._SCREEN_PARAM_MAP['billInstrID'];
		
		IFDS.Xml.addSingleNode(paramXML, 'billInstrID', billInstrID);
		IFDS.Xml.addSingleNode(paramXML, "startRecNum", _nextStartRecNum);
		IFDS.Xml.addSingleNode(paramXML, "requestRecNum", _requestRecNum);			
	
		DesktopWeb.Ajax.doSmartviewAjax(_initView, {ignoreErrorCode: '15'}, paramXML, responseHandler, _translationMap['Loading']);
		
		function responseHandler(success, responseXML)
		{				
			if (success)
			{
				_invoiceAdjXML = responseXML;
			}
			else
			{
				_invoiceAdjXML = null;
			}
			
			if(_invoiceAdjXML)
			{
				storePermissions(_invoiceAdjXML);
				displayInvoiceAdj();
			}
		}		
	}
	
	function displayInvoiceAdj()
	{
		clearGrid('grdInvAdj');
		
		
		if(_invoiceAdjXML)
		{			
			_resources.grids['grdInvAdj'].getStore().loadData(_invoiceAdjXML);
			_resources.grids['grdInvAdj'].getSelectionModel().selectFirstRow();

			_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(_invoiceAdjXML);
			
			if (_nextStartRecNum)
			{
				_resources.grids['grdInvAdj'].enableButton('cmdInvAdjMore');
			}
			else
			{
				_resources.grids['grdInvAdj'].disableButton('cmdInvAdjMore');
			}
			
			// Call to update the buttons and fields only when no error
			updateInvoiceAdjFields();
			updateInvoiceAdjButtons();			
		}
	}

	function clearGrid(name)
	{
		_selectedInvoiceAdj = null;
		
		_resources.grids[name].getStore().removeAll();
		_resources.grids[name].disableAllButtons();
	}
	
	function updateInvoiceAdjFields()
	{
		_resources.fields['offsetAmount'].disable();
		_resources.fields['adjmentDate'].disable();
		_resources.fields['comment'].disable();
	}
	
	function updateInvoiceAdjButtons()
	{
		var grid = _resources.grids['grdInvAdj'];

		if(_selectedInvoiceAdj && _permissionsMap['inq'] == 'yes')
		{
			var AllowAdj = _selectedInvoiceAdj.get('allowAdjust');
			
			// To allow adjusting for the payment that less than 6 months
			if(AllowAdj == 'yes' && _permissionsMap['mod'] == 'yes')
			{
				grid.enableButton('btnAdjDetail');
			}
			else
			{
				grid.disableButton('btnAdjDetail');
			}
			
			grid.enableButton('btnPrintIV');
			grid.enableButton('cmdInvAdjAdmin');
		}
		else
		{
			grid.disableButton('btnPrintIV');
			grid.disableButton('btnAdjDetail');
			grid.disableButton('cmdInvAdjMore');
			grid.disableButton('cmdInvAdjAdmin');
		}
		
		// Print is allowed for the adjustment that has been submitted to the database; disabled button
		if(_invoiceAdjReqXML != null && (_selectedInvoiceAdj.get('isChgOffsetAmt') == 'yes' ||
			_selectedInvoiceAdj.get('isChgAdjustDate') == 'yes' ||
			_selectedInvoiceAdj.get('isChgComment') == 'yes') )
		{
			grid.disableButton('btnPrintIV');
		}		
	}	
	
	function validateInvoiceAdjUpdate(action, popup)
	{
		var commentAll = popup.getField('commentDetl').getValue();
		var offSetAmountUpd = popup.getField('offsetAmountDetl').getValue().toString(); 
		var adjustmentDateUpd = popup.getField('adjmentDateDetl').getDisplayDateString(); 
		var errComment = false;	
		var commentList = {};
		
		var commentAll = popup.getField('commentDetl').getValue().split(_self.NEWLINE);
		
		for (var i = 0; i < 4; i++)
			commentList[i] = '';
			
		for (var i = 0; i < commentAll.length ; i++)
		{		
			if (i >= 4 && commentAll[i].trim() != '')
			{
				errComment = true;
				break;
			}
			else
			{
				if (commentAll[i] == undefined)
					IFDS.Xml.addSingleNode(xml, 'comment' + (i+1) ,  '');
				else
				{				
					if (commentAll[i].length > 80 )
					{
						errComment = true;
						break;
					} else						
						commentList[i] = commentAll[i];
				}
			}
		}
		
		// All fields cannot be blank then it inplies there is nothing changed		
		if (offSetAmountUpd == "" && adjustmentDateUpd == "" 
			&& popup.getField('commentDetl').getValue().trim() == "")
		{		
			DesktopWeb.Util.displayError(_translationMap['AdjustError']);
		}
		else if (errComment)
		{
			DesktopWeb.Util.displayError(_translationMap['CommentError']);
		}
		else if (offSetAmountUpd != '' || adjustmentDateUpd != '' 
			|| popup.getField('commentDetl').getValue().trim()  != '')
		{		
			// Mark flag if updating for validating the print invoice	
			if (offSetAmountUpd != _selectedInvoiceAdj.get('offsetAmount') ) 
			{
				_selectedInvoiceAdj.set('isChgOffsetAmt', 'yes');
			}
			else if (adjustmentDateUpd != _selectedInvoiceAdj.get('adjustDate') )
			{
				_selectedInvoiceAdj.set('isChgAdjustDate', 'yes');
			}
			else if (commentList[0] != _selectedInvoiceAdj.get('comment1') 
			         || commentList[1] != _selectedInvoiceAdj.get('comment2') 
					 || commentList[2] != _selectedInvoiceAdj.get('comment3') 
					 || commentList[3] != _selectedInvoiceAdj.get('comment4') 
			)
			{
				_selectedInvoiceAdj.set('isChgComment', 'yes');
			}		
			
			// Update fields
			_selectedInvoiceAdj.set('offsetAmount', offSetAmountUpd);
			_selectedInvoiceAdj.set('adjustDate', adjustmentDateUpd);
			
			_selectedInvoiceAdj.set('comment1', commentList[0]);
			_selectedInvoiceAdj.set('comment2', commentList[1]);
			_selectedInvoiceAdj.set('comment3', commentList[2]);
			_selectedInvoiceAdj.set('comment4', commentList[3]);
				
			// Update info from grdInvAdj
			_self.setSelectedInvoiceAdj(_resources.grids['grdInvAdj'].getSelectedRecord()
				,_selectedInvoiceAdjIndex);			
			
			var dataXML = IFDS.Xml.newDocument('data');
			var invoiceAdjXML = IFDS.Xml.addSingleNode(dataXML, 'AdjustDetl');
			IFDS.Xml.addSingleNode(invoiceAdjXML, 'billInstrID', _selectedInvoiceAdj.get('billInstrID'));
			IFDS.Xml.addSingleNode(invoiceAdjXML, 'pymtId', _selectedInvoiceAdj.get('pymtId'));
			IFDS.Xml.addAttribute(invoiceAdjXML, 'RecordSource', _selectedInvoiceAdj.get('pymtId'));
			
			IFDS.Xml.addSingleNode(invoiceAdjXML, 'offSetAmount', offSetAmountUpd);
			IFDS.Xml.addSingleNode(invoiceAdjXML, 'adjustmentDate', popup.getField('adjmentDateDetl').getSMVDateString());
			IFDS.Xml.addSingleNode(invoiceAdjXML, 'version', _selectedInvoiceAdj.get('version'));
			IFDS.Xml.addSingleNode(invoiceAdjXML, 'runMode', action);
			
			IFDS.Xml.addSingleNode(invoiceAdjXML, 'comment1', commentList[0]);
			IFDS.Xml.addSingleNode(invoiceAdjXML, 'comment2', commentList[1]);
			IFDS.Xml.addSingleNode(invoiceAdjXML, 'comment3', commentList[2]);
			IFDS.Xml.addSingleNode(invoiceAdjXML, 'comment4', commentList[3]);
		
			addinvoiceAdjXMLRequest(IFDS.Xml.getNode(dataXML, '//AdjustDetl'));
			
			// call to update Print button
			updateInvoiceAdjButtons();
			popup.hide();
		}
	}	
	
	function addinvoiceAdjXMLRequest(xml)
	{
		if(_invoiceAdjReqXML==null)
		{
			_invoiceAdjReqXML = IFDS.Xml.stringToXML('<data/>');
			IFDS.Xml.addSingleNode(_invoiceAdjReqXML, 'AdjustDetls');	
		}
		
		var newUpdatedInvoiceAdjID = IFDS.Xml.getNodeValue(xml, 'pymtId');
		var currInvoiceAdjReqXML = IFDS.Xml.getNode(_invoiceAdjReqXML, "//AdjustDetls/AdjustDetl[pymtId='" + newUpdatedInvoiceAdjID + "']");
		
		if(currInvoiceAdjReqXML)
		{	
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(currInvoiceAdjReqXML, 'offSetAmount'), IFDS.Xml.getNodeValue(xml, 'offSetAmount'));
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(currInvoiceAdjReqXML, 'adjustmentDate'), IFDS.Xml.getNodeValue(xml, 'adjustmentDate'));
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(currInvoiceAdjReqXML, 'comment1'), IFDS.Xml.getNodeValue(xml, 'comment1'));
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(currInvoiceAdjReqXML, 'comment2'), IFDS.Xml.getNodeValue(xml, 'comment2'));
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(currInvoiceAdjReqXML, 'comment3'), IFDS.Xml.getNodeValue(xml, 'comment3'));
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(currInvoiceAdjReqXML, 'comment4'), IFDS.Xml.getNodeValue(xml, 'comment4'));
		}
		else
		{
			IFDS.Xml.appendNode(IFDS.Xml.getNode(_invoiceAdjReqXML, "//AdjustDetls"), IFDS.Xml.cloneDocument(xml));
		}
		
		updateUpdatesFlag();
	}

	function getInvoiceAdjXML(pymtId)
	{
		return IFDS.Xml.getNode(_invoiceAdjXML, "//PaymentDetails/PaymentDetail[pymtId='" + pymtId + "']");
	}	
	
	function updateUpdatesFlag()
	{
		var invoiceAdjUpdates = IFDS.Xml.getNodes(_invoiceAdjReqXML, "//AdjustDetls/AdjustDetl[runMode!='UNCH']");
		
		if(invoiceAdjUpdates.length == 0)
		{
			_self.updatesFlag = false;
		}
		else
		{
			_self.updatesFlag = true;
		}
	}
	
	function storeContextErrors(errorNodes)
	{
		var firstErrRecIndex = -1;
		
		for (var i = 0; i < errorNodes.length; i++)
		{	
			var pymtIdErr = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
			var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');
				
			// Update main XML
			var invoiceAdjXML = IFDS.Xml.getNode(_invoiceAdjXML, "//PaymentDetails/PaymentDetail[pymtId='" + pymtIdErr + "']");
			IFDS.Xml.addSingleNode(invoiceAdjXML, 'errMsg', errMsg);
				
			// Update grdInvAdj
			var recordIndex = _resources.grids['grdInvAdj'].getStore().find('pymtId', pymtIdErr);
			var invoiceAdjRecord = _resources.grids['grdInvAdj'].getStore().getAt(recordIndex);
			
			invoiceAdjRecord.set('errMsg', errMsg);
			_resources.grids['grdInvAdj'].getStore().commitChanges();
			
			if(firstErrRecIndex==-1)firstErrRecIndex = recordIndex;
		}
		
		if(firstErrRecIndex==-1)
		{
			_resources.grids['grdInvAdj'].getSelectionModel().selectFirstRow();
		}
		else
		{
			_resources.grids['grdInvAdj'].getSelectionModel().selectRow(firstErrRecIndex);
			_resources.grids['grdInvAdj'].focusRow(firstErrRecIndex);
		}
	}
	
	function loadMoreInvoiceAdj(moreInvoiceAdjXML)
	{
		var cloneMoreInvoiceAdjXML = IFDS.Xml.cloneDocument(moreInvoiceAdjXML);
		var intRateCfgsNode = IFDS.Xml.getNode(_invoiceAdjXML, "//PaymentDetails");
		var moreInvoiceAdjNodes = IFDS.Xml.getNodes(moreInvoiceAdjXML, "//PaymentDetail");
		
		Ext.each(moreInvoiceAdjNodes, function(moreCommRedNode)
		{
			IFDS.Xml.appendNode(intRateCfgsNode, moreCommRedNode);
		});
		
		_resources.grids['grdInvAdj'].getStore().loadData(cloneMoreInvoiceAdjXML, true);
		_resources.grids['grdInvAdj'].focusRow(_selectedInvoiceAdjIndex);
	}
	
	function goToScreen(screenName,billInstrID,holdingEntityCode,invoiceID,invoiceDisp,enableholdingFlag,asOfDate,optSelectAsOfDate,rowSelectedIndex)
	{
		var params = {};
		
		params['prevScreen'] = 'InvoiceAdj';//_screenId;
		params['tidx'] = DesktopWeb._SCREEN_PARAM_MAP['tidx'];
		params['billInstrID'] = billInstrID;
		params['HoldingEntityCode'] = holdingEntityCode;
		params['invoiceID'] = invoiceID;
		params['invoiceDisp'] = invoiceDisp;
		params['enableholdingFlag'] = enableholdingFlag;
		params['asOfDate'] = asOfDate;
		params['optSelectAsOfDate'] = optSelectAsOfDate;
		params['rowSelectedIndex'] = rowSelectedIndex;
		
		DesktopWeb.Util.goToScreen(screenName, params);	
	}
	
	// PUBLIC ITEMS *************************************
	return {	
		MOD: _MOD
		,updatesFlag: false
		,NEWLINE : '\r\n'
		
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			loadInvoiceAdj();
		}	
		
		,setSelectedInvoiceAdj: function(record, index)
		{
			_selectedInvoiceAdj = record;
			_selectedInvoiceAdjIndex = index;
			
			var fieldsData = _resources.grids['grdInvAdj'].getSelectedRecord().data;
			
			// Display OffeSetAmount as blank for new payment with status 05-Approved Verified
			if ( (_selectedInvoiceAdj.get('status') == '05') && (_selectedInvoiceAdj.get('offsetAmount') == 0) &&
				 (_selectedInvoiceAdj.get('isChgOffsetAmt') != 'yes') )
			{
				_resources.fields['offsetAmount'].setValue('');
			}
			else
			{
				_resources.fields['offsetAmount'].setValue(fieldsData.offsetAmount);
			}
			
			_resources.fields['adjmentDate'].setValue(fieldsData.adjustDate);
			var allComment = fieldsData.comment1 + _self.NEWLINE
					+ fieldsData.comment2 + _self.NEWLINE
					+ fieldsData.comment3 + _self.NEWLINE
					+ fieldsData.comment4;
			_resources.fields['comment'].setValue(allComment);	
			
			// To prevent Java script error when the data is not returned from back-end.
			if(_selectedInvoiceAdj)
			{
				updateInvoiceAdjFields();
				updateInvoiceAdjButtons();
			}
		}	
		
		,setDeselectedInvoiceAdj: function()
		{
			_selectedInvoiceAdj = null;
		}

		,getListDisplay: function(listName, code)
		{
			var listNode = IFDS.Xml.getNode(_invoiceAdjXML, "//List[@listName = '" + listName + "']/Element[code='" + code + "']");
			return (listNode)?IFDS.Xml.getNodeValue(listNode, 'value'):code;
		}
		
		,openActionPopup: function(name, action)
		{
			var popup = _resources.popups[name];	
			
			popup.show();					
			popup.init(action);				
		}
		
		,openAdminPopup: function(recType)
		{					
			var title = null;	
			var xml = null;

			if (recType == 'PaymentDetail')
			{
				title = _translationMap['InvoiceAdj']+ ' - ' +_translationMap['Admin']
				xml = this.getSelectedInvoiceAdjXML();
			}
			
			var adminData = {};
			// The UserName is not required for this Admin screen
			adminData['procDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, 'processDate'));
			adminData['modUser'] = IFDS.Xml.getNodeValue(xml, 'modUser');
			adminData['modDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, 'modDate'));
			
			_resources.popups['admin'].init(title, adminData);
			_resources.popups['admin'].show();			
		}
		
		,invoiceAdjUpdate: function(action, popup)
		{
			validateInvoiceAdjUpdate(action, popup);
		}		

		,getSelectedInvoiceAdjXML: function()
		{
			return getInvoiceAdjXML(_selectedInvoiceAdj.get('pymtId'));
		}
		
		,getSelectedInvoiceAdj: function()
		{
			return _selectedInvoiceAdj;
		}	

		,goScreen: function()
		{
			var billInstrID = DesktopWeb._SCREEN_PARAM_MAP['billInstrID'];
			var holdingEntityCode = DesktopWeb._SCREEN_PARAM_MAP['holdingEntityCode'];
			var invoiceID = DesktopWeb._SCREEN_PARAM_MAP['invoiceID'];
			var invoiceDisp = DesktopWeb._SCREEN_PARAM_MAP['invoiceDisp'];
			var enableholdingFlag = DesktopWeb._SCREEN_PARAM_MAP['enableholdingFlag'];
			var asOfDate = DesktopWeb._SCREEN_PARAM_MAP['asOfDate'];
			var optSelectAsOfDate = DesktopWeb._SCREEN_PARAM_MAP['optSelectAsOfDate'];
			var rowSelectedIndex = DesktopWeb._SCREEN_PARAM_MAP['rowSelectedIndex'];
			
			if(_selectedInvoiceAdj)
			{
				goToScreen("InvoiceInstr",_selectedInvoiceAdj.get('billInstrID'),holdingEntityCode,invoiceID,invoiceDisp,enableholdingFlag,asOfDate,optSelectAsOfDate,rowSelectedIndex);	
			}
			else
			{
				goToScreen("InvoiceInstr",billInstrID,holdingEntityCode,invoiceID,invoiceDisp,enableholdingFlag,asOfDate,optSelectAsOfDate,rowSelectedIndex);	
			}
		}
		
		,doUpdate: function()
		{
			var updateStatus = null;
			
			if(_invoiceAdjReqXML)
			{
				DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, IFDS.Xml.cloneDocument(_invoiceAdjReqXML), responseHandler, _translationMap['Loading']);			

				function responseHandler(success, responseXML, contextErrors)
				{	
					if (success)
					{
						updateStatus = DesktopWeb._SUCCESS;
						_invoiceAdjReqXML = null;			
						
						// go back to main screen
						_self.goScreen();
					}
					else
					{
						storeContextErrors(contextErrors);
						updateStatus = DesktopWeb._FAIL 	
					}
				}
			}
			else
			{
				// go back to main screen
				_self.goScreen();
			}
			
			return updateStatus;
		}
		
		,doReload: function()
		{
			var paramXML = IFDS.Xml.newDocument('data');
			var billInstrID = DesktopWeb._SCREEN_PARAM_MAP['billInstrID'];
		
			IFDS.Xml.addSingleNode(paramXML, 'billInstrID', billInstrID);
			IFDS.Xml.addSingleNode(paramXML, 'startRecNum', _nextStartRecNum);
			IFDS.Xml.addSingleNode(paramXML, 'requestRecNum', _requestRecNum);

			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, paramXML, responseHandler, _translationMap['Loading']);

			function responseHandler(success, responseXML)
			{	
				if (success)
				{
					loadMoreInvoiceAdj(responseXML);
					
					_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
					
					if (_nextStartRecNum)
					{
						_resources.grids['grdInvAdj'].enableButton('cmdInvAdjMore');
					}
					else
					{
						_resources.grids['grdInvAdj'].disableButton('cmdInvAdjMore');
					}
				}
			}
		}
		
		,doPrint: function()
		{			
			// Print is allowed for the adjustment that has been submitted to the database
			if (_invoiceAdjReqXML == null || (_invoiceAdjReqXML != null || 
				(_selectedInvoiceAdj.get('isChgOffsetAmt') != 'yes' || 
				 _selectedInvoiceAdj.get('isChgAdjustDate') != 'yes' || 
				 _selectedInvoiceAdj.get('isChgComment') != 'yes') ) )			
			{	
				var paramXML = IFDS.Xml.newDocument('data');
				var updateStatus = null;
			
				IFDS.Xml.addSingleNode(paramXML, 'payEntityPymtID', _selectedInvoiceAdj.get('pymtId'));

				DesktopWeb.Ajax.doSmartviewAjax(_printView, null, paramXML, responseHandler, "Loading ...");								

				function responseHandler(success, responseXML, contextErrors)
				{	
					if (success)
					{
						updateStatus = DesktopWeb._SUCCESS;
						paramXML = null;
						DesktopWeb.Util.displayInfo(_translationMap['PrintMsg']);				
					}
					else
					{
						storeContextErrors(contextErrors);
						updateStatus = DesktopWeb._FAIL 	
					}
				}
				
				return updateStatus;			
			}	
		}
	}
}	