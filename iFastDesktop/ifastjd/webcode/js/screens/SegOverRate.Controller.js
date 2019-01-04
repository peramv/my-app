/*********************************************************************************************
 * @file    SegOverRate.Controller.js
 * @author  Matira Thanetkulabut
 * @desc    Controller JS file for Override screen
 *********************************************************************************************/
/*
 *  Navigate: Menu > Account > Contract Information > Override Screen
 *  
 *  History : 
 *  
 *  28-Sep-2016 Matira Thanetkulabut P0256533 T84091 MSF - Desktop
 *              - Initial
 */
 
DesktopWeb.ScreenController = function(){
    
    // PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	var _dtSegOvrRateInq = 'dtSegOvrRateReload';
	var _dtSegOvrRateUpd = 'dtSegOvrRateUpd';
	var _INIT_XML;
	
	// PRIVATE METHODS ****************************************	
	function populateScreen(responseXML)
	{		
        _INIT_XML = responseXML;
        _resources.grids['guarOver'].store.loadData(IFDS.Xml.getNode(_INIT_XML, '//SEGOvrRates'));
        _resources.grids['guarOver'].getSelectionModel().select(0,0);
    }
    
    function createUpdXML(store)
    {
        var numberOfRows = store.getCount();
        var updCount = 0;
        
        var dataXML2 = IFDS.Xml.newDocument("SEGOvrRates");
        
			for (var i = 0; i < numberOfRows; i++)
			{
                var type = store.getAt(i).data.guarType;
				var newRate = store.getAt(i).data.guarRate;
                var bfChg = IFDS.Xml.getNodeValue(_INIT_XML, '//SEGOvrRates/SEGOvrRate[guarType="' + type + '"]/guarRate');
				if (newRate != bfChg)
                {
                    var uuid = IFDS.Xml.getNodeValue(_INIT_XML, '//SEGOvrRates/SEGOvrRate[guarType="' + type + '"]/@UUID');
                       
                    var xml = IFDS.Xml.addSingleNode(dataXML2,"SEGOvrRate");
                    IFDS.Xml.addAttribute(xml, 'UUID', uuid);
                    IFDS.Xml.addSingleNode(xml, 'UUID', uuid);
                    IFDS.Xml.addSingleNode(xml, 'guarType', type);
                    IFDS.Xml.addSingleNode(xml, 'guarTypeCode', IFDS.Xml.getNodeValue(_INIT_XML, '//SEGOvrRates/SEGOvrRate[guarType="' + type + '"]/guarTypeCode'));
                    IFDS.Xml.addSingleNode(xml, 'newGuarRate', newRate);
                    IFDS.Xml.addSingleNode(xml, 'defaultRate', IFDS.Xml.getNodeValue(_INIT_XML, '//SEGOvrRates/SEGOvrRate[guarType="' + type + '"]/defaultRate'));
                    IFDS.Xml.appendNode(dataXML2,xml);
                    updCount += 1;
                }
			}

            if (updCount > 0){    
                var updXML = IFDS.Xml.newDocument('data');
                IFDS.Xml.addSingleNode(updXML, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);	
                IFDS.Xml.addSingleNode(updXML, 'contractType', DesktopWeb._SCREEN_PARAM_MAP['ContractType']);	
                IFDS.Xml.addSingleNode(updXML, 'contractVer', DesktopWeb._SCREEN_PARAM_MAP['ContractVer']);	
                IFDS.Xml.appendNode(updXML,dataXML2);
                return updXML;
            }else{
                return null;
            }
    }
    
    // PUBLIC ITEMS *************************************
	return {
        updatesFlag: false
        
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
            
            var requestXML = IFDS.Xml.newDocument('data');
            IFDS.Xml.addSingleNode(requestXML, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);	
            IFDS.Xml.addSingleNode(requestXML, 'contractType', DesktopWeb._SCREEN_PARAM_MAP['ContractType']);	
            IFDS.Xml.addSingleNode(requestXML, 'contractVer', DesktopWeb._SCREEN_PARAM_MAP['ContractVer']);	
            
            DesktopWeb.Ajax.doSmartviewAjax(_dtSegOvrRateInq, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading']);			
		
            function responseHandler(success, responseXML)
            {	
                if (success)
                {
                    populateScreen(responseXML);
					_INIT_XML = responseXML
                }
            }
		}
        
        ,openAdminPopup: function () {
            if (_resources.grids['guarOver'].getSelectionModel().hasSelection()) {
               var selectedRecord = _resources.grids['guarOver'].getSelectionModel().getSelectedCell();
               var ind = selectedRecord[0];
               
               var title = _translationMap['Admin'] + " " + _translationMap['Dates']
                var data = _resources.grids['guarOver'].store.getAt(ind).data;
                
                var adminData = {};
                adminData['userName'] = data.userName;
                adminData['procDate'] = DesktopWeb.Util.getDateDisplayValue(data.processedDate);
                adminData['modUser'] = data.modUser;
                adminData['modDate'] = DesktopWeb.Util.getDateDisplayValue(data.modDate);

                _resources.popups['admin'].init(title, adminData);
                _resources.popups['admin'].show();
            }
        }	
        
		,getApplRate: function(guarType)
		{
			var guarNode = IFDS.Xml.getNode(_INIT_XML, '//SEGOvrRates/SEGOvrRate[guarType="' + guarType + '"]');
			var txtOpt = [];
		   
		   
				var rateNodes = IFDS.Xml.getNodes(_INIT_XML, '//SEGOvrRates/SEGOvrRate[guarType="' + guarType + '"]/ApplRates/applRate');
				
				for (var j = 0; j < rateNodes.length; j++) {
					var rate = IFDS.Xml.getNodeValue(rateNodes[j])
					var opt = [rate];
					txtOpt.push(opt);
				}	
			return txtOpt;
		}
        
        ,doUpdate: function()
        {
            var updateStatus = DesktopWeb._SUCCESS;
            var updXml = createUpdXML(_resources.grids['guarOver'].getStore());
            if(updXml != null)
            {
             DesktopWeb.Ajax.doSmartviewUpdate(_dtSegOvrRateUpd, null, updXml, responseHandler, _translationMap['ProcMsg_Saving']);				
             function responseHandler(success, responseXML, contextErrors)
                {	
                    if (success)
                    {
                        updateStatus = DesktopWeb._SUCCESS;
                    }
                    else
                    {
                        updateStatus = DesktopWeb._FAIL 	
                    }
                }
            }
            return updateStatus;
        }
        
        ,isEnabled: function(type)
        {
            var t = IFDS.Xml.getNodeValue(_INIT_XML, '//SEGOvrRates/SEGOvrRate[guarType="' + type + '"]/enableOvrRate');
            if (t == 'yes') 
                return true;
            else 
                return false;
        }
	}	
}