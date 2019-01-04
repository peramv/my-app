/*********************************************************************************************
 * @file    GroupingInformation.Controller.js
 * @author    Aurkarn Mongkonrat
 * @desc    Controller JS file for Grouping Information screen
 *********************************************************************************************/
 /*
 *  History :
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached.  
 */
 
DesktopWeb.ScreenController = function(){    
    
    // PRIVATE VARIABLES *************************************
    var _self = null;
    var _resources = null;
    var _translationMap = DesktopWeb.Translation.getTranslationMap();
    var _dtGroupingInfoInqService = 'dtGroupingInfoInq';
    var _accountSearchService = "accountSearch";
    
    // PRIVATE METHODS ****************************************    
    function populateScreen(responseXML)
    {        
        _resources.fields['benefOwnerName'].setValue(IFDS.Xml.getNodeValue(responseXML, '//BenefOwnerName'));
        _resources.grids['acctGroupGrid'].loadData(IFDS.Xml.getNode(responseXML, '//AccountGroups'));
        _resources.grids['feeModelGrid'].loadData(IFDS.Xml.getNode(responseXML, '//AcctFeeModels'));
    }
    
    function loadDefaultAccount(acctNum)
    {
        var paramXML = IFDS.Xml.newDocument('data');
        
        IFDS.Xml.addSingleNode(paramXML, 'searchValue', acctNum);
        IFDS.Xml.addSingleNode(paramXML, 'incAllStat', 'yes');
        IFDS.Xml.addSingleNode(paramXML, 'maxRecord', '10');
        IFDS.Xml.addSingleNode(paramXML, 'startRecordNum', '1');
        
        DesktopWeb.Ajax.doSmartviewAjax(_accountSearchService, null, paramXML, responseHandler, _translationMap['ProcMsg_Loading']);

        function responseHandler(success, responseXML)
        {
            if (success)
            {
                _resources.fields['account'].getStore().loadData(IFDS.Xml.getNode(responseXML, "//PossibleMatches"));
                _resources.fields['account'].setValue(IFDS.Xml.getNodeValue(IFDS.Xml.getNode(responseXML, "//acctNum") , "."));
                groupingSearch(IFDS.Xml.getNodeValue(IFDS.Xml.getNode(responseXML, "//acctNum")));
            }
        }
    }
    
    function groupingSearch(acctNum)
    {
        var requestXML = IFDS.Xml.newDocument("data");
        IFDS.Xml.addSingleNode(requestXML, "runMode", 'reload');
        IFDS.Xml.addSingleNode(requestXML, "accountNum", acctNum);
        DesktopWeb.Ajax.doSmartviewAjax(_dtGroupingInfoInqService, null, requestXML, responseHandler, _translationMap['ProcMsg_Searching']);            
        
        function responseHandler(success, responseXML, contextErrors)
        {    
            if (success)
            {
                populateScreen(responseXML);
            }
        }
    }
    
    // PUBLIC ITEMS *************************************
    return {                
        init: function(res)
        {                
            _resources = res;
            _self = DesktopWeb._SCREEN_CONTROLLER;
            
            var acctNum = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
            if (acctNum && acctNum.length > 0)
            {
                _resources.fields['account'].disable();
                _resources.buttons['acctSearchBtn'].disable();
                
                loadDefaultAccount(acctNum);
            }
        }
        
        ,doGroupingSearch: function(account)
        {
            groupingSearch(account);
        }
    }    
}    