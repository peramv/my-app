var _disableDiv = null;
var _processingDiv = null;
var _updatesMade = false;

var _selectedRule = null;
var _selectedDoc = null;

var _ADD = "add";
var _MODIFY = "modify";
var _DELETE = "delete";

var _popupMode = null;

var _detailsHeight = 172;



/**
 *  
 */
function initRegStandards()
{
	IFDSTableManager.init();
	IFDSTableManager.getTable( "RegStandardsListTable" ).setOnRowSelectedFunction( selectHandler_RegStandardsListTable );	
	IFDSTableManager.getTable( "Popup_docListTable" ).setOnRowSelectedFunction( selectHandler_PopupDocListTable );
	
	IFDSDatepickerManager.init( _dateFormat, "calendarHolder", "calendarBtn" );
	
	// build divs for "showProcessing"
	_disableDiv = buildDisableDiv();
	_processingDiv = buildProcessingDiv();
	
	// fetch initial set of reg standards
	sendRegStandardsReloadRequest( _regRuleFilterValue, _startRecNum, _requestRecNum );
		
	enableAddRegStandardBtn();
	disableModifyRegStandardBtn();
	disableDeleteRegStandardBtn();
	
	resetPopup();	
}


/**
 * row select handler for DocList table 
 */
function selectHandler_RegStandardsListTable( rowIndex )
{	
	_selectedRule = UTL.getElem( "RegStandardsListTable" ).lastChild.childNodes[rowIndex];
	enableModifyRegStandardBtn()
	enableDeleteRegStandardBtn()			
}


/**
 * row select handler for DocList table 
 */
function selectHandler_PopupDocListTable( rowIndex )
{		
	_selectedDoc = UTL.getElem( "Popup_docListTable" ).lastChild.childNodes[rowIndex];	
	enablePopupDeleteDocBtn();		
}


/**
 * click handler for (row) expand button 
 */
function clickHandler_expandBtn( evt )
{
	var expandBtn = evt.currentTarget;
	var rowElem = expandBtn.parentNode.parentNode;
	expandRow( parseInt( rowElem.rowIndex ), _detailsHeight );	
	
	evt.stopPropagation();
}


/**
 * click handler for (row) collapse button 
 */
function clickHandler_collapseBtn( evt )
{
	var collapseBtn = evt.currentTarget;
	var rowElem = collapseBtn.parentNode.parentNode;
	collapseRow( parseInt( rowElem.rowIndex ), _detailsHeight );
	
	evt.stopPropagation();
}


/**
 * click handler for Add button 
 */
function clickHandler_addRegStandardBtn()
{	
	openAddPopup();
}


/**
 * click handler for Modify button 
 */
function clickHandler_modifyRegStandardBtn()
{
	openModifyPopup();	
}


/**
 * click handler for Delete button 
 */
function clickHandler_deleteRegStandardBtn()
{
	openDeletePopup()
}


/**
 * click handler for Save/OK button (on popup) 
 */
function clickHandler_saveBtn()
{
	var procXML = getProcXML( _popupMode );
	if ( procXML != null)
	{	 	
		sendRegStandardsProcRequest( _regRuleFilterValue, _startRecNum, _requestRecNum, _popupMode, procXML );
	}
}


function changeHandler_regulationRuleFld()
{
	var regRuleFld = UTL.getElem( "Popup_regRuleFld" );
	// no rule selected
	if ( regRuleFld.selectedIndex == 0 )
	{
		// disable all controls ...
		disableAllPopupControls()
		// ... except for regRule fld
		regRuleFld.disabled = false;							
				
		deleteAllDocsFromPopup();
		
		// need to clear any disabled fields that may have values already set 
		UTL.getElem( "Popup_provinceFld" ).selectedIndex = -1; 
		UTL.getElem( "Popup_taxTypeFld" ).selectedIndex = -1;
		UTL.getElem( "Popup_investorTypeFld" ).selectedIndex = -1;
		UTL.getElem( "Popup_invest3rdPartyFld" ).selectedIndex = -1;
	}
	// CC rule selected
	else if ( regRuleFld.options[regRuleFld.selectedIndex].closedCountry == "yes" )
	{
		// enable all controls ...
		enableAllPopupControls();
		// ... except for regCode, investType, investFor3rdParty, and docCode table
		UTL.getElem( "Popup_regCodeFld" ).disabled = true;
		UTL.getElem( "Popup_investorTypeFld" ).disabled = true;
		UTL.getElem( "Popup_invest3rdPartyFld" ).disabled = true;				
		UTL.getElem( "Popup_addDocBtn" ).disabled = true;
		UTL.getElem( "Popup_deleteDocBtn" ).disabled = true;							
		
		// need to clear any disabled fields that may have had values already set 		
		UTL.getElem( "Popup_investorTypeFld" ).selectedIndex = -1;
		UTL.getElem( "Popup_invest3rdPartyFld" ).selectedIndex = -1;
		deleteAllDocsFromPopup();
		
		// set the value of regCode field to the default value				
		var regCodeFld = UTL.getElem( "Popup_regCodeFld" );
		regCodeFld.value = regRuleFld.options[regRuleFld.selectedIndex].regCodeDflt;
	}
	else
	{
		// enable all controls
		UTL.getElem( "Popup_countryFld" ).disabled = false;
		UTL.getElem( "Popup_provinceFld" ).disabled = false;
		UTL.getElem( "Popup_regCodeFld" ).disabled = false;
		UTL.getElem( "Popup_descriptionFld" ).disabled = false;
		IFDSDatepickerManager.getDatepicker( "Popup_effDateFld" ).enable();
		IFDSDatepickerManager.getDatepicker( "Popup_stopDateFld" ).enable();				
		UTL.getElem( "Popup_investorTypeFld" ).disabled = false;
		UTL.getElem( "Popup_invest3rdPartyFld" ).disabled = false;
		UTL.getElem( "Popup_taxTypeFld" ).disabled = false;		
		UTL.getElem( "Popup_addDocBtn" ).disabled = false;
		UTL.getElem( "Popup_deleteDocBtn" ).disabled = true;							
	}
}


/**
 * click handler for Cancel button (on popup) 
 */
function clickHandler_cancelBtn()
{	
	hidePopup();	
}


/**
 * click handler for Add doc button 
 */
function clickHandler_addDocBtn()
{
	addDoc();	
}


/**
 * click handler for delete doc button 
 */
function clickHandler_deleteDocBtn()
{
	deleteDoc();
}


/**
 * click handler for search button 
 */
function clickHandler_searchBtn()
{
	var regRuleFilterFld = UTL.getElem( "regRuleFilterFld" );
	_regRuleFilterValue = regRuleFilterFld.value;
	sendRegStandardsReloadRequest( _regRuleFilterValue, _startRecNum, _requestRecNum );
}


/**
 * click handler for More button 
 */
function clickHandler_moreBtn()
{
	sendRegStandardsReloadRequest( _regRuleFilterValue, _nextStartRecNum, _requestRecNum );
}


/**
 * change handler for the docDesc dropdown within the popup doclist table 
 */
function changeHandler_docDescFld( evt )
{
	var docDescFld = evt.currentTarget;
	docDescFld.codeFld.data = docDescFld.value;	
	docDescFld.codeFld.innerHTML = docDescFld.value;	
}


function enableAddRegStandardBtn()
{
	if ( _userPermissionMap["add"] == "yes" )
	{
    	UTL.getElem( "btnAddRegStandard" ).disabled = false;
	}	
}


function disableAddRegStandardBtn()
{
	UTL.getElem( "btnAddRegStandard" ).disabled = true;	
}


function enableModifyRegStandardBtn()
{
	if ( _userPermissionMap["mod"] == "yes" )
	{
    	UTL.getElem( "btnModifyRegStandard" ).disabled = false;
	}	
}


function disableModifyRegStandardBtn()
{
	UTL.getElem( "btnModifyRegStandard" ).disabled = true;	
}

function enableDeleteRegStandardBtn()
{
	if ( _userPermissionMap["del"] == "yes" )
	{
    	UTL.getElem( "btnDeleteRegStandard" ).disabled = false;
	}	
}


function disableDeleteRegStandardBtn()
{
	UTL.getElem( "btnDeleteRegStandard" ).disabled = true;	
}


function openAddPopup()
{
	if( _selectedRule )
	{					
		IFDSTableManager.getTable( "RegStandardsListTable" ).clearSelectedRowIndex();			
		_selectedRule = null;
		enableAddRegStandardBtn();
		disableModifyRegStandardBtn();
		disableDeleteRegStandardBtn();		
	}
		
	enablePopup( _ADD );
	showPopup();
	
	_popupMode = _ADD							
}


function openModifyPopup()
{
	if ( _selectedRule )
	{
		// load details from selected row
		populatePopupFieldsFromSelectedRule( _selectedRule );
	}
	else
	{
		throw new Error( Err.genErrMsg( "_selectedRule is null", "openModifyPopup()", "DocList.js" ) );								
	}		
		
	enablePopup( _MODIFY );
	showPopup();
	
	_popupMode = _MODIFY;
}


function openDeletePopup()
{
	if ( _selectedRule )
	{
		// load details from selected row
		populatePopupFieldsFromSelectedRule( _selectedRule );
	}
	else
	{
		throw new Error( Err.genErrMsg( "_selectedRule is null", "openDeletePopup()", "DocList.js" ) );								
	}		
		
	enablePopup( _DELETE );
	showPopup();
	
	_popupMode = _DELETE;
}


/**
 * returns the xml for Proc request, based on the action (add/modify/delete) 
 */
function getProcXML( action )
{
	var procXML = "";
	
	if ( action == _ADD )
	{
		procXML += XML.createNodeStr( "countryCode", 		XML.charEncode( UTL.getElem( "Popup_countryFld" ).value ) );
		procXML += XML.createNodeStr( "province", 			XML.charEncode( UTL.getElem( "Popup_provinceFld" ).value ) );
		procXML += XML.createNodeStr( "regRule", 			XML.charEncode( UTL.getElem( "Popup_regRuleFld" ).value ) );
		procXML += XML.createNodeStr( "complyCode", 		XML.charEncode( UTL.getElem( "Popup_regCodeFld" ).value ) );
		procXML += XML.createNodeStr( "description", 		XML.charEncode( UTL.getElem( "Popup_descriptionFld" ).value ) );
		procXML += XML.createNodeStr( "investorType", 		XML.charEncode( UTL.getElem( "Popup_investorTypeFld" ).value ) );
		procXML += XML.createNodeStr( "investFor3rdParty", 	XML.charEncode( UTL.getElem( "Popup_invest3rdPartyFld" ).value ) );
		procXML += XML.createNodeStr( "effDate", 			XML.charEncode( UTL.getElem( "Popup_effDateFld" ).value ) );
		procXML += XML.createNodeStr( "stopDate", 			XML.charEncode( UTL.getElem( "Popup_stopDateFld" ).value ) );
		
		// get selected tax type(s)
		var taxTypeXML = ""
		var taxTypeFld = UTL.getElem( "Popup_taxTypeFld" );
		for ( var i = 0; i < taxTypeFld.options.length; i++ )
		{
			if ( taxTypeFld.options[i].selected )
			{
				taxTypeXML += XML.createNodeStr( "TaxType", XML.createNodeStr( "code", taxTypeFld.options[i].value ) );
			}
		}
		procXML += XML.createNodeStr( "TaxTypeList", taxTypeXML );		
		
		var docListTable = UTL.getElem( "Popup_docListTable" );
		var docListAddXML = "";		
		for ( var i = 0; i < docListTable.lastChild.childNodes.length; i++ )
		{
			var docItem = docListTable.lastChild.childNodes[i];
			// added docItems do not have docItemId
			if ( docItem.docItemId == "" )
			{
				if ( docItem.firstChild.data != null )
				{
					docListAddXML += XML.createNodeStr( "docListItem",
				                                    	XML.createNodeStr( "action", "add" )
				                                    	+ XML.createNodeStr( "docCode", XML.charEncode( docItem.firstChild.data ) ) );
				}
				else
				{
					alert( "Please select a document before proceeding" );
					return;
				}		
			}
		}		
		
		procXML += XML.createNodeStr( "docList", docListAddXML );				
	}
	else if ( action == _MODIFY )
	{
		procXML += XML.createNodeStr( "regStandardId", 		XML.charEncode( UTL.getElem( "Popup_regStandardIdFld" ).value ) );
		procXML += XML.createNodeStr( "countryCode", 		XML.charEncode( UTL.getElem( "Popup_countryFld" ).value ) );
		procXML += XML.createNodeStr( "province", 		XML.charEncode( UTL.getElem( "Popup_provinceFld" ).value ) );
		procXML += XML.createNodeStr( "regRule", 			XML.charEncode( UTL.getElem( "Popup_regRuleFld" ).value ) );
		procXML += XML.createNodeStr( "complyCode", 		XML.charEncode( UTL.getElem( "Popup_regCodeFld" ).value ) );
		procXML += XML.createNodeStr( "description", 		XML.charEncode( UTL.getElem( "Popup_descriptionFld" ).value ) );
		procXML += XML.createNodeStr( "investorType", 		XML.charEncode( UTL.getElem( "Popup_investorTypeFld" ).value ) );
		procXML += XML.createNodeStr( "investFor3rdParty", 	XML.charEncode( UTL.getElem( "Popup_invest3rdPartyFld" ).value ) );
		procXML += XML.createNodeStr( "effDate", 			XML.charEncode( UTL.getElem( "Popup_effDateFld" ).value ) );		
		procXML += XML.createNodeStr( "stopDate", 			XML.charEncode( UTL.getElem( "Popup_stopDateFld" ).value ) );
		
		// get selected tax type(s)
		var taxTypeXML = ""
		var taxTypeFld = UTL.getElem( "Popup_taxTypeFld" );
		for ( var i = 0; i < taxTypeFld.options.length; i++ )
		{
			if ( taxTypeFld.options[i].selected )
			{
				taxTypeXML += XML.createNodeStr( "TaxType", XML.createNodeStr( "code", taxTypeFld.options[i].value ) );
			}
		}
		procXML += XML.createNodeStr( "TaxTypeList", taxTypeXML );				
		
		var docListTable = UTL.getElem( "Popup_docListTable" );
		var docListAddXML = "";		
		for ( var i = 0; i < docListTable.lastChild.childNodes.length; i++ )
		{
			var docItem = docListTable.lastChild.childNodes[i];
			// added docItems do not have docItemId
			if ( docItem.docItemId == "" )
			{
				if ( docItem.firstChild.data != null )
				{
					docListAddXML += XML.createNodeStr( "docListItem",
				                                    	XML.createNodeStr( "action", "add" )
				                                    	+ XML.createNodeStr( "docCode", XML.charEncode( docItem.firstChild.data ) ) );
				}
				else
				{
					alert( "Please select a document before proceeding" );
					return;
				}		
			}
		}
		var delDocIdFld = UTL.getElem( "Popup_delDocId" );
		var delDocIdArray = ( delDocIdFld.value == "" ? []: delDocIdFld.value.split( "," ) );			
		var docListDelXML = "";		
		for ( var i = 0; i < delDocIdArray.length; i++ )
		{
			docListDelXML += XML.createNodeStr( "docListItem",
			                                    XML.createNodeStr( "action", "delete" )
			                                    + XML.createNodeStr( "docItemId", XML.charEncode( delDocIdArray[i] ) ) );			
		}				
		
		procXML += XML.createNodeStr( "docList", docListAddXML + docListDelXML );		
	}
	else if ( action == _DELETE )
	{
		procXML += XML.createNodeStr( "regStandardId", 		XML.charEncode( UTL.getElem( "Popup_regStandardIdFld" ).value ) );
		procXML += XML.createNodeStr( "description", 		XML.charEncode( UTL.getElem( "Popup_descriptionFld" ).value ) );
		procXML += XML.createNodeStr( "investorType", 		XML.charEncode( UTL.getElem( "Popup_investorTypeFld" ).value ) );
		procXML += XML.createNodeStr( "investFor3rdParty", 	XML.charEncode( UTL.getElem( "Popup_invest3rdPartyFld" ).value ) );		
		procXML += XML.createNodeStr( "stopDate", 			XML.charEncode( UTL.getElem( "Popup_stopDateFld" ).value ) );
		
		var docListTable = UTL.getElem( "Popup_docListTable" );
		var docListAddXML = "";		
		for ( var i = 0; i < docListTable.lastChild.childNodes.length; i++ )
		{
			var docItem = docListTable.lastChild.childNodes[i];
			// added docItems do not have docItemId
			if ( docItem.docItemId == "" )
			{
				docListAddXML += XML.createNodeStr( "docListItem",
				                                   	XML.createNodeStr( "action", "add" )
				                                   	+ XML.createNodeStr( "docCode", XML.charEncode( docItem.firstChild.data ) ) );										                                    
			}
		}					
		
		procXML += XML.createNodeStr( "docList", docListAddXML + docListDelXML );	
	}
	
	procXML = XML.createNodeStr( "RegStandard", procXML );		
	return procXML;	
}


function showPopup()
{
	displayDisabler();	
	UTL.getElem( "PopupIframe" ).style.display = "block";
	UTL.getElem( "RegStandardsPopup" ).style.display = "block";
}


function hidePopup()
{
	hideDisabler();
	UTL.getElem( "PopupIframe" ).style.display = "none";
	UTL.getElem( "RegStandardsPopup" ).style.display = "none";
	resetPopup();
}


/**
 * enables the appropriate fields and buttons of the popup, based on the mode
 */
function enablePopup( mode )
{	
	if ( mode == _ADD )
	{
		// initially we leave everything disabled, except the regRuleFld, others enabled based on regRule selected		
		UTL.getElem( "Popup_regRuleFld" ).disabled = false;
				
		showPopupSaveBtn();				
	}
	else if ( mode == _MODIFY )
	{
		// enable everything ...
		enableAllPopupControls();		
		// except for regRuleFld, regRuleCode
		UTL.getElem( "Popup_regRuleFld" ).disabled = true;
		UTL.getElem( "Popup_regCodeFld" ).disabled = true;		
																						
		var regRuleFld = UTL.getElem( "Popup_regRuleFld" );
		if ( regRuleFld.options[regRuleFld.selectedIndex].closedCountry == "yes" )
		{
			// and for closeCountry, we disable the investType, invest3rdParty, and docCode table
			UTL.getElem( "Popup_investorTypeFld" ).disabled = true;
			UTL.getElem( "Popup_invest3rdPartyFld" ).disabled = true;
			UTL.getElem( "Popup_addDocBtn" ).disabled = true;
			UTL.getElem( "Popup_deleteDocBtn" ).disabled = true;			
		}		
		
		showPopupSaveBtn();				
	}
	else if ( mode == _DELETE )
	{
		showDeleteConfirmation();
		showPopupOKBtn()		
	}
	
	 IFDSTableManager.reInitTable( "Popup_docListTable" );	
}


/**
 * populate the popup fields with values from the given row 
 */
function populatePopupFieldsFromSelectedRule( regStandardRecord )
{	
	UTL.getElem( "Popup_regStandardIdFld" ).value = regStandardRecord.regStandardId;
	UTL.getElem( "Popup_regRuleFld" ).value = regStandardRecord.regRule;
	UTL.getElem( "Popup_countryFld" ).value = regStandardRecord.countryCode;	
	UTL.getElem( "Popup_regCodeFld" ).value = regStandardRecord.complyCode;
	UTL.getElem( "Popup_descriptionFld" ).value = regStandardRecord.description
	UTL.getElem( "Popup_effDateFld" ).value = regStandardRecord.effDate;
	UTL.getElem( "Popup_stopDateFld" ).value = regStandardRecord.stopDate;
	UTL.getElem( "Popup_investorTypeFld" ).value = regStandardRecord.investorType;
	UTL.getElem( "Popup_invest3rdPartyFld" ).value = regStandardRecord.investFor3rdParty;
	UTL.getElem( "Popup_provinceFld" ).value = regStandardRecord.provinceCode;
	
	var taxTypeFld = UTL.getElem( "Popup_taxTypeFld" );
	var recordTaxTypeArray = regStandardRecord.taxTypes.split( "," );	
	for( var i = 0; i < taxTypeFld.options.length; i++ )
	{
		for ( var j = 0; j < recordTaxTypeArray.length; j++ )
		{
			var recordTaxTypeValue = recordTaxTypeArray[j];
			
			if ( taxTypeFld.options[i].value == recordTaxTypeArray[j] )
			{
				taxTypeFld.options[i].selected = true;	
			}
		}	
	}
	
	var detailsDocListTableElem = UTL.getElem( "DetailsDocListTable_" + regStandardRecord.rowIndex );
	for ( var i = 0; i < detailsDocListTableElem.lastChild.childNodes.length; i++ )
	{
		var row = detailsDocListTableElem.lastChild.childNodes[i];		
		insertDoc( row.docItemId, row.firstChild.data );
	}		
}


function disableAllPopupControls()
{	
	UTL.getElem( "Popup_regRuleFld" ).disabled = true;
	UTL.getElem( "Popup_countryFld" ).disabled = true;
	UTL.getElem( "Popup_provinceFld" ).disabled = true;
	UTL.getElem( "Popup_regCodeFld" ).disabled = true;		
	UTL.getElem( "Popup_descriptionFld" ).disabled = true;	
	UTL.getElem( "Popup_taxTypeFld" ).disabled = true;
	IFDSDatepickerManager.getDatepicker( "Popup_effDateFld" ).disable();			
	IFDSDatepickerManager.getDatepicker( "Popup_stopDateFld" ).disable();		
	UTL.getElem( "Popup_investorTypeFld" ).disabled = true;	
	UTL.getElem( "Popup_invest3rdPartyFld" ).disabled = true;
		
	UTL.getElem( "Popup_addDocBtn" ).disabled = true;			
}


function enableAllPopupControls()
{
	UTL.getElem( "Popup_regRuleFld" ).disabled = false;
	UTL.getElem( "Popup_countryFld" ).disabled = false;
	UTL.getElem( "Popup_provinceFld" ).disabled = false;
	UTL.getElem( "Popup_regCodeFld" ).disabled = false;		
	UTL.getElem( "Popup_descriptionFld" ).disabled = false;	
	UTL.getElem( "Popup_taxTypeFld" ).disabled = false;
	IFDSDatepickerManager.getDatepicker( "Popup_effDateFld" ).enable();			
	IFDSDatepickerManager.getDatepicker( "Popup_stopDateFld" ).enable();		
	UTL.getElem( "Popup_investorTypeFld" ).disabled = false;	
	UTL.getElem( "Popup_invest3rdPartyFld" ).disabled = false;	
		
	UTL.getElem( "Popup_addDocBtn" ).disabled = false;			
}


function setPopupFieldsToDefaultValues()
{
	UTL.getElem( "Popup_regStandardIdFld" ).value = "";	
	UTL.getElem( "Popup_regRuleFld" ).value = "";
	UTL.getElem( "Popup_countryFld" ).value = _defaultValueMap["regCountries"]; /*default value is UnAssigned (0000)*/	
	UTL.getElem( "Popup_regCodeFld" ).value = "";			
	UTL.getElem( "Popup_descriptionFld" ).value = "";		
	UTL.getElem( "Popup_effDateFld" ).value = _defaultValueMap["effDate"];	
	UTL.getElem( "Popup_stopDateFld" ).value = _defaultValueMap["stopDate"];	
	UTL.getElem( "Popup_investorTypeFld" ).value = "";	
	UTL.getElem( "Popup_invest3rdPartyFld" ).value = "";
	UTL.getElem( "Popup_provinceFld" ).value = _defaultValueMap["regProvinces"];	
	UTL.getElem( "Popup_taxTypeFld" ).value = _defaultValueMap["taxTypes"];		
	UTL.getElem( "Popup_delDocId" ).value = "";
		
	deleteAllDocsFromPopup();
}


function hideDeleteConfirmation()
{
	UTL.getElem( "Popup_deleteConfirm" ).style.display = "none";
}


function showDeleteConfirmation()
{
	UTL.getElem( "Popup_deleteConfirm" ).style.display = "block";
}

function showPopupOKBtn()
{
	UTL.getElem( "btnOK" ).style.display = "inline";
}

function hidePopupOKBtn()
{
	UTL.getElem( "btnOK" ).style.display = "none";
}

function showPopupSaveBtn()
{
	UTL.getElem( "btnSave" ).style.display = "inline";
}

function hidePopupSaveBtn()
{
	UTL.getElem( "btnSave" ).style.display = "none";
}


/**
 * resets the popup 
 */
function resetPopup()
{
	disableAllPopupControls();
	setPopupFieldsToDefaultValues();
	hideDeleteConfirmation();
	disablePopupAddDocBtn();
	disablePopupDeleteDocBtn();
	hidePopupOKBtn();
	hidePopupSaveBtn();
}


/**
 * clears the doc list table 
 */
function clearTable()
{
	var regStandardsListDiv = UTL.getElem( "RegStandardsListDiv" );
	var regStandardsListTable = UTL.getElem( "RegStandardsListTable" );
	
	var numRows = regStandardsListTable.lastChild.childNodes.length;
	for ( var i = 0; i < numRows; i++ )
	{
		IFDSTableManager.removeTable( "DetailsDocListTable_" + i );
	}		
	
	regStandardsListDiv.removeChild( regStandardsListTable );	
}


function enablePopupAddDocBtn()
{
	if ( _docListPermissionMap["add"] == "yes" )
	{
    	UTL.getElem( "Popup_addDocBtn" ).disabled = false;
	}
}


function disablePopupAddDocBtn()
{
	UTL.getElem( "Popup_addDocBtn" ).disabled = true;	
}


function enablePopupDeleteDocBtn()
{
	if ( _docListPermissionMap["del"] == "yes" )
	{
    	UTL.getElem( "Popup_deleteDocBtn" ).disabled = false;
	}
}


function disablePopupDeleteDocBtn()
{
	UTL.getElem( "Popup_deleteDocBtn" ).disabled = true;	
} 
 

/**
 * inserts a document records into the popup doclist table 
 */
function insertDoc( docItemId, docCode )
{
	var docListTable = IFDSTableManager.getTable( "Popup_docListTable" );
	var docListTableElem = UTL.getElem( "Popup_docListTable" );
	var newRow = docListTableElem.lastChild.appendChild( document.createElement( "tr" ) );
	newRow.docItemId = docItemId;
	newRow.appendChild( document.createElement( "td" ) );
	newRow.appendChild( document.createElement( "td" ) );
		
	newRow.firstChild.style.height = 25;
	newRow.firstChild.style.paddingBottom = 3;
	newRow.firstChild.data = docCode;
	newRow.firstChild.innerHTML = docCode;
		
	newRow.lastChild.style.height = 25;
	newRow.lastChild.style.paddingBottom = 3;
	newRow.lastChild.data = _docMap[docCode];
	newRow.lastChild.innerHTML = _docMap[docCode];
	
	IFDSTableManager.reInitTable( "Popup_docListTable" );
	
	UTL.getElem( "Popup_docListDiv" ).scrollTop = UTL.getElem( "Popup_docListTable" ).offsetHeight;
	IFDSTableManager.getTable( "Popup_docListTable" ).scrollHandler();
}


/**
 * adds new document record to the popup doclist table (ie. after clicking add button) 
 */
function addDoc()
{
	var docListTable = IFDSTableManager.getTable( "Popup_docListTable" );
	var docListTableElem = UTL.getElem( "Popup_docListTable" );
	var newRow = docListTableElem.lastChild.appendChild( document.createElement( "tr" ) );
	newRow.docItemId = "";
	newRow.appendChild( document.createElement( "td" ) );
	newRow.appendChild( document.createElement( "td" ) );
	
	newRow.firstChild.data = null;
	newRow.firstChild.innerHTML = " ";
	newRow.firstChild.style.height = 25;
	newRow.firstChild.style.paddingBottom = 3;	
	
	var docDescFld = newRow.lastChild.appendChild( document.createElement( "select" ) );
	newRow.lastChild.style.position = "relative";
	docDescFld.style.position = "absolute";
	docDescFld.style.top = 1;
	var option = document.createElement( "option" );
	option.text = "Select document ...";	
	option.value = null;	
	docDescFld.add( option );
	for ( var i in _docMap )
	{
		var option = document.createElement( "option" );	
		option.value = i;
		option.text = _docMap[i];		
		docDescFld.add( option );
	}	
	docDescFld.style.fontSize = "10px";
	docDescFld.style.width = "640";
	docDescFld.codeFld = newRow.firstChild;	
				
	EvtHandler.add( docDescFld, "click", function( evt ){ evt.stopPropagation() } );
	EvtHandler.add( docDescFld, "change", changeHandler_docDescFld );
	
	if( docListTable.getSelectedRowIndex() != null )
	{
		docListTable.clearSelectedRowIndex();
		disablePopupDeleteDocBtn();
								
	}						
	
	IFDSTableManager.reInitTable( "Popup_docListTable" );
	
	UTL.getElem( "Popup_docListDiv" ).scrollTop = UTL.getElem( "Popup_docListTable" ).offsetHeight;
	IFDSTableManager.getTable( "Popup_docListTable" ).scrollHandler();	
}


/**
 * deletes document record from doclist in popup 
 */
function deleteDoc()
{
	var docListTable = IFDSTableManager.getTable( "Popup_docListTable" );
	
	if ( _selectedDoc.docItemId != "" )
	{
		if ( UTL.getElem( "Popup_delDocId" ).value == "" )
		{
			UTL.getElem( "Popup_delDocId" ).value = _selectedDoc.docItemId;
		}
		else
		{
			UTL.getElem( "Popup_delDocId" ).value += "," + _selectedDoc.docItemId;
		}
	}
	
	_selectedDoc.parentNode.removeChild( _selectedDoc );
	
	IFDSTableManager.reInitTable( "Popup_docListTable" );
	
	disablePopupDeleteDocBtn();	
	
	UTL.getElem( "Popup_docListDiv" ).scrollTop = 0;
	IFDSTableManager.getTable( "Popup_docListTable" ).scrollHandler();			
}


function deleteAllDocsFromPopup()
{
	var docListTable = UTL.getElem( "Popup_docListTable" );
	
	var rows = docListTable.lastChild.childNodes;
	
	for ( var i = 0; i < rows.length; i++ )
	{
		rows[i].parentNode.removeChild( rows[i] );	
	}
	
	IFDSTableManager.reInitTable( "Popup_docListTable" );
	
	UTL.getElem( "Popup_docListDiv" ).scrollTop = 0;
	IFDSTableManager.getTable( "Popup_docListTable" ).scrollHandler();		
}


/**
 * sends reload request 
 */
function sendRegStandardsReloadRequest( regRule, startRecNum, requestRecNum )
{
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "RegStandards_Reload";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
    
	paramMap["regRule"] = regRule;
	paramMap["startRecNum"] = startRecNum;
	paramMap["requestRecNum"] = requestRecNum;	
            
    var url = HTTP.buildURL( _vServletPath, paramMap );
                		    	 
	displayProcessing();
	    	   
	var req = HTTP.getGETRequest( url );
	req.setAsynch( false );
	req.setCallbackFunction( sendRegStandardsReloadRequest_callback );
	req.send();		   
}


/**
 * sends Proc request 
 */
function sendRegStandardsProcRequest( regRule, startRecNum, requestRecNum, action, procXML )
{
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "RegStandards_Process";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
        
    paramMap["action"] = action;
    
    paramMap["regRuleRel"] = "";
    paramMap["startRecNumRel"] = 1;
    paramMap["requestRecNumRel"] = 100;    
    
    var url = HTTP.buildURL( _vServletPath, paramMap );
                		    	 
	displayProcessing();
	    	   
	var req = HTTP.getPOSTRequest( url );
	req.setAsynch( false );
	req.setCallbackFunction( sendRegStandardsProcRequest_callback );
	req.send( procXML );		   
}


/**
 * parses response text from Reload or Proc request 
 */
function parseResponse( responseText )
{	
	var success = true;
	
	var responseXML = XML.parseToXML( responseText );

    var errorNode = XML.getNode( "/responseContents/Error", responseXML );
    
    if ( errorNode )
    {
    	var errorType = XML.getNode( "type", errorNode ).firstChild.nodeValue;
    	var errorMsg = XML.getNode( "msg", errorNode ).firstChild.nodeValue;
    	if ( errorType.toLowerCase() == "environment" )
    	{
    		DesktopError.displayProcessingError( "Regulatory Standards", errorMsg );  
    	}
    	else
    	{
    		alert( errorMsg );
    	}
    	
    	success = false;        
    }
    else
    {   
    	// clear existing list
    	clearTable();
    	
    	// populate table with response
    	var tableUpdateNode = XML.getNode( "/responseContents/tableUpdate", responseXML );
    	var tableHTML = tableUpdateNode.firstChild.xml;
    	loadRegStandardsTable( tableHTML );
    	
    	var recordRangeNode = XML.getNode( "/responseContents/RecordRange", responseXML );
    	if ( recordRangeNode )
    	{    	
	    	var rangeStartNode = XML.getNode( "rangeStart", recordRangeNode );
	    	_startRecNum = rangeStartNode.firstChild.nodeValue;    	
	    	var moreRecordsExistNode = XML.getNode( "moreRecordsExist", recordRangeNode );
	    	if ( moreRecordsExistNode && moreRecordsExistNode.firstChild.nodeValue.toLowerCase() == "yes" )
	    	{    		
	    		var rangeStartForNextNode = XML.getNode( "rangeStartForNext", recordRangeNode );    		
	    		_nextStartRecNum = rangeStartForNextNode.firstChild.nodeValue;
	    		UTL.getElem( "btnMore" ).disabled = false; 
	    	}
	    	else
	    	{
	    		_nextStartRecNum = "";
	    		UTL.getElem( "btnMore" ).disabled = true;
	    	}
    	}    
    } 
    
    return success;
}


/**
 * call back function from reload request 
 */
function sendRegStandardsReloadRequest_callback( responseText )
{
	parseResponse( responseText );
			
	//setRuleActionButtonsState( false );
    hideProcessing( false );        
}


/**
 * callback function for the RegStandardsProc request
 */
function sendRegStandardsProcRequest_callback( responseText )
{	
	hideProcessing( true );
	if ( parseResponse( responseText ) )
	{		
		hidePopup();
		_updatesMade = true;
	}	
	disableDeleteRegStandardBtn();
	disableModifyRegStandardBtn();
	
	// Proc response includes ALL regRules, so need to update filter dropdown
	UTL.getElem( "regRuleFilterFld" ).value = "";            
}


/**
 * load the reg standards table with the given html, and then
 * reInit the corresponding IFDSTAble object
 */
function loadRegStandardsTable( tableHTML )
{
	UTL.getElem( "RegStandardsListDiv" ).innerHTML = tableHTML;
		
	IFDSTableManager.reInitTable( "RegStandardsListTable" );
	
	var tableElem = UTL.getElem( "RegStandardsListTable" );	
	for ( var r = 0; r < tableElem.lastChild.childNodes.length; r++ )
	{
		var rowElem = tableElem.lastChild.childNodes[r];
		rowElem.style.position = "relative";
		rowElem.style.top = 0;
		
		var tdElem = rowElem.firstChild; 
		var expandBtn = tdElem.firstChild;		
		var collapseBtn = tdElem.lastChild;
		
		expandBtn.style.display = "block";
		addClickHandler( expandBtn, clickHandler_expandBtn );
		collapseBtn.style.display = "none";
		addClickHandler( collapseBtn, clickHandler_collapseBtn );
		
		EvtHandler.add( rowElem.lastChild.lastChild, "click", function( evt ){ evt.stopPropagation(); } );
		
		IFDSTableManager.addTable( "DetailsDocListTable_" + r );		
	}
}


/**
 * helper function when adding a document - need to add click handler for the dropdown
 * that's part of the newly added document record
 */
function addClickHandler( btn, handlerFn )
{	
	EvtHandler.add( btn, "click", handlerFn );	
}


/**
 * expands the details of the given row
 */
function expandRow( rowIndex, expandHeight )
{	
	var tableElem = UTL.getElem( "RegStandardsListTable" );
	var targetRowElem = tableElem.lastChild.childNodes[rowIndex];
	var rowCount = tableElem.lastChild.childNodes.length;
		
	for ( var r = rowIndex + 1; r < tableElem.lastChild.childNodes.length; r++ )
	{		
		var rowElem = tableElem.lastChild.childNodes[r];		
		rowElem.style.top = parseInt( rowElem.style.top ) + expandHeight;				
	}
	
	var detailsDiv = targetRowElem.lastChild.lastChild;
	detailsDiv.style.display = "block";
	
	toggleExpandCollapseBtn( rowIndex );
}


/**
 * collapses the details of the given row
 */
function collapseRow( rowIndex, expandHeight )
{
	var tableElem = UTL.getElem( "RegStandardsListTable" );
	var targetRowElem = tableElem.lastChild.childNodes[rowIndex];
	var rowCount = tableElem.lastChild.childNodes.length;
	
	for ( var r = rowIndex + 1; r < tableElem.lastChild.childNodes.length; r++ )
	{		
		var rowElem = tableElem.lastChild.childNodes[r];		
		rowElem.style.top = parseInt( rowElem.style.top ) - expandHeight;					
	}
	
	var detailsDiv = targetRowElem.lastChild.lastChild;
	detailsDiv.style.display = "none";
	
	toggleExpandCollapseBtn( rowIndex );
	
	// because collapsing affects the scroller of the div, we call
	// the scroll handler of the table
	IFDSTableManager.getTable( "RegStandardsListTable" ).scrollHandler();
}


/**
 * flips between the expand/collapse buttons for the given row
 */
function toggleExpandCollapseBtn( rowIndex )
{
	var tableElem = UTL.getElem( "RegStandardsListTable" );	
	var rowElem = tableElem.lastChild.childNodes[rowIndex];
	var expandBtn = rowElem.firstChild.firstChild;
	var collapseBtn = rowElem.firstChild.lastChild;
		
	if ( expandBtn.style.display == "none")
	{
		expandBtn.style.display = "block";
		collapseBtn.style.display = "none";
	}	
	else
	{
		expandBtn.style.display = "none";
		collapseBtn.style.display = "block";
	}
}


/**
 * build the page disable div
 */
function buildDisableDiv()
{
	var screenDiv = UTL.getElem( "ScreenDiv" );
	var d = screenDiv.appendChild( document.createElement( "div" ) );	
	d.style.position = "absolute";	
	d.style.left = 0;	
	d.style.top = 0;
	d.style.width = screenDiv.offsetWidth; 		
	d.style.height = screenDiv.offsetHeight;
	d.style.zIndex = 1;
	d.style.display = "none";
	d.style.background = "black";
	d.style.filter = "alpha(opacity=20)";
	
	return d;	   
}


/**
 * build the "processing" div
 */
function buildProcessingDiv()
{
	var screenDiv = UTL.getElem( "ScreenDiv" );
	var d = screenDiv.appendChild( document.createElement( "div" ) );
	d.style.position = "absolute";
	
	var width = 200;
	var height = 50;
	
	d.style.width = width;
	d.style.height = height
		
	d.style.left = ( screenDiv.offsetWidth - width ) / 2;	
	d.style.top = ( screenDiv.offsetHeight - height ) / 2;
	
	d.style.zIndex = 4;
	d.style.paddingTop = 10;
	d.style.textAlign = "center";
	d.style.display = "none";	
	d.style.border = "2px solid black";
	d.style.background = "white";
	d.style.fontSize = "14px";
	d.style.fontStyle = "italic";
	d.innerHTML = "Processing ...";
	
	return d;
}


/**
 * display the disabler div
 */
function displayDisabler()
{
	_disableDiv.style.display = "block";
	
	// rather than re-drawing the disableDiv to cover the whole browser 
	// screen (whose size may vary), we just have it cover the screenDiv 
	// and make the rest of the document background a matching color 
	document.body.style.backgroundColor = "#BCBABE";	
}


/**
 * remove disabler div
 */
function hideDisabler()
{
	document.body.style.backgroundColor = _desktopColor;
	_disableDiv.style.display = "none";
}


/**
 * disables the screen and displays "processing" msg 
 */
function displayProcessing()
{
	displayDisabler();
	_processingDiv.style.display = "block";
}


/**
 * re-enables the screen and hides the "processing" msg 
 */
function hideProcessing( popupOpen )
{
	if ( !popupOpen )
	{
		hideDisabler();
	}
	_processingDiv.style.display = "none";
}


function clickHandler_closeBtn()
{
	UTL.getElem( "btnConfirmDlg" ).click();
}


/**
 * returns true/false depending on whether updates have been done
 */
function getUpdateStatus()
{	
	return _updatesMade;	
}