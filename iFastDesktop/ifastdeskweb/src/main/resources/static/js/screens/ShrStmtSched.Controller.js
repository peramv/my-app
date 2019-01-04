 /*********************************************************************************************
 * @file	ShrStmtSched.Controller.js
 * @author	Cherdsak Sangkasen
 * @desc	Controller JS file for Shareholder Statement Schedule screen
 *********************************************************************************************/

DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;	
	var _initView = 'dtShrStmtSchedInit';
	var _vars = {};
	var _mstrXML = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// PRIVATE METHODS ****************************************	
	// Operate on XMLs
	
	function createMstrXML(xml)
	{	
		if (!_mstrXML || !more)
		{			
			_mstrXML = IFDS.Xml.newDocument("StmtScheds");
		}		
		
		var stmtSchedXMLArr = IFDS.Xml.getNodes(xml, '//StmtScheds/StmtSchedDetl');
		Ext.each(stmtSchedXMLArr, function(stmtSchedXML){
			IFDS.Xml.appendNode(_mstrXML, stmtSchedXML);	
		});
	}	
	
	function getInitRequest()
	{
		var requestXML = IFDS.Xml.newDocument("data");		
		if (_vars['AccountNum'] != _self.BLANK)
		{
			IFDS.Xml.addSingleNode(requestXML, "AccountNum", _vars['AccountNum']);	
		}
		else
		{
			IFDS.Xml.addSingleNode(requestXML, "AccountNum", 0);	
		}
		return requestXML;
	}
	
	// PUBLIC ITEMS *************************************
	// Operate on Objects
	return {				
		BLANK: ''
		, init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;			
			_vars['AccountNum'] = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];	
			
			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, getInitRequest(), responseHandler, _translationMap['Loading']);
			
			function responseHandler(success, responseXML)
			{
				if (success)
				{																		
					createMstrXML(responseXML);
					_self.refreshGrdStmtSched(0);
				}
			}	
			
		}
		
		, refreshGrdStmtSched: function (index)
		{		
			_resources.grids['grdStmtSched'].loadData(_mstrXML);
			_resources.grids['grdStmtSched'].setSelectedRecord(index);
		}
		
	}	
	
}	