/*********************************************************************************************
 * @file	RESPNotional.Controller.js		
 * @author	Rod Walker
 * @desc	Controller JS file for RESP Notional Info screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  01 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54333
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *  30 Apr 2014 G. Thawornwachirakun P0220132 FN03 T55087
 *					- Enhanced for CCS - SAGES RESP Program
 *
 *  30 May 2014 Narin Suanlamyai P0220132 FN03 DFT0034351 T55198
 *					- Disable SAGES fields for non-SAGES environment
 *
 *  12 Jun 2014 Narin Suanlamyai P0220132 FN03 DFT0034936 T55247
 *					- Add version for SAGES
 *
 *  21 Jul 2014 Narin Suanlamyai P0220132 FN03 DFT0037101 T55450
 *					- Hide SAGES section for non-SAGES environment.
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached.   
 *
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _initView = "dtRESPNotlInit";
	var _reloadView = "dtRESPNotlReload";
	var _updateView = "dtRESPNotlUpd";
		
	var _modPerm = null;
	var _defaultValues = null;
	var _periodOptionsMap = null;
	var _versionNotl = null;
	var _versionPNotl = null;
	var _versionPNotlSAGES = null;
	var _respNotlInfoId = null;
	var _contributionAndIncomeData = null;
	var _grantsData = null;
	var _qesiData = null;	
	
	var _showQESI = false;
	var _showSAGES = false;
	var _notlExists = false;
	
	// PRIVATE METHODS ***************************************
	function storeDefaultValues()
	{
		_defaultValues = {};
		_defaultValues['period'] = '9999';
	}
	
	function storePermissions(initDataXML)
	{
		_modPerm = IFDS.Xml.getNodeValue(initDataXML, '*/Permission/modPerm').toLowerCase() == 'yes';
	}

	function populateScreen(responseXML)
	{
		var periodsAvailable = IFDS.Xml.getNodes(responseXML, '*/List[@listName="' + DesktopWeb._SCREEN_PARAM_MAP['AccountNum'] + 'PeriodOptions"]/Element').length != 0;
		
		if (periodsAvailable)
		{
			populateFilters(responseXML);
			populateNotionalDetails(responseXML, _resources.fields['periodRadio'].checked);
		}
		else
		{
			DesktopWeb.Util.displayError(_translationMap['NoPeriodWarning']);
		}
	}
		
	function populateFilters(initDataXML)
	{
		_periodOptionsMap = {};
		var infoLevelNodes = IFDS.Xml.getNodes(initDataXML, '*/List[@listName="InfoLevelOptions"]/Element');
		for (var i = 0; i < infoLevelNodes.length; i++)
		{
			var infoLevel = IFDS.Xml.getNodeValue(infoLevelNodes[i], 'code');
			_periodOptionsMap[infoLevel] = IFDS.Xml.getNode(initDataXML, '*/List[@listName="' + infoLevel + 'PeriodOptions"]');			
		}
		
		_resources.grids['infoLevel'].loadData(IFDS.Xml.getNode(initDataXML, '*/List[@listName="InfoLevelOptions"]'));
		_resources.fields['periodRadio'].setValue(true);

		_resources.fields['period'].setValue(_resources.fields['period'].getStore().getAt(0).data['code']);
		
		_resources.fields['periodRadio'].enable();
		_resources.fields['period'].enable();
		_resources.fields['asOfRadio'].enable();
		_resources.fields['asOfDate'].enable();
		_resources.buttons['refreshBtn'].enable();								
	}
	
	function clearNotionalDetails()
	{
		_resources.fields['marketValue'].reset();
		Ext.getCmp('contributionAndIncome').removeAll();
		Ext.getCmp('contributionAndIncome').hide();
		
		Ext.getCmp('grants').removeAll();
		Ext.getCmp('grants').hide();
		
		Ext.getCmp('qesi').removeAll();
		Ext.getCmp('qesi').hide();
		
		Ext.getCmp('sagesContributionFS').removeAll();
		Ext.getCmp('sagesContributionFS').hide();
	}
	
	function populateNotionalDetails(dataXML)
	{
		var notlDataNode = IFDS.Xml.getNode(dataXML, '*/NotionalInformation');
		_notlExists = IFDS.Xml.getNodeValue(notlDataNode, 'notlExist').toLowerCase() == 'yes';
		_showQESI = IFDS.Xml.getNodeValue(dataXML, '*/NotlOtherInfo/showQESI').toLowerCase() == 'yes';		
		_showSAGES = IFDS.Xml.getNodeValue(dataXML, '*/NotlOtherInfo/showSAGES').toLowerCase() == 'yes';

		_versionNotl = IFDS.Xml.getNodeValue(notlDataNode, 'versionNotl');
		_versionPNotl = IFDS.Xml.getNodeValue(notlDataNode, 'versionPNotl');
		_versionPNotlSAGES = IFDS.Xml.getNodeValue(notlDataNode, 'versionPNotlSAGES');
		_respNotlInfoId = IFDS.Xml.getNodeValue(notlDataNode, 'respNotlInfoID');
		
		var periodFilterUsed = _resources.fields['periodRadio'].checked;
		
		_resources.fields['marketValue'].setValue(IFDS.Xml.getNodeValue(notlDataNode, 'mktValue'));
	
		populateContributionAndIncome(notlDataNode, periodFilterUsed);
		populateSAGESContribution(notlDataNode, periodFilterUsed);
		populateGrants(notlDataNode, periodFilterUsed);
		populateQESI(notlDataNode, periodFilterUsed, IFDS.Xml.getNodeValue(dataXML, '*/NotlOtherInfo/ytdLabel'));
		
		Ext.getCmp('notional-details').doLayout();
		Ext.getCmp('sagesContributionFS').setVisible(_showSAGES);
		Ext.getCmp('qesi').setVisible(_showQESI);
	}
	
	function populateContributionAndIncome(notlDataNode, periodFilterUsed)
	{		
		var container = Ext.getCmp('contributionAndIncome')
		container.show();
		var dataRow = new DesktopWeb.ScreenResources.DataRow({
			rowLabel: _translationMap['Income']
			,staticRow: !_modPerm || !_notlExists
			,allowEdit: periodFilterUsed
			,purchase: {id: 'purIncome', value: IFDS.Xml.getNodeValue(notlDataNode, 'purIncome')}
			,redemption: {id: 'redIncome', value: IFDS.Xml.getNodeValue(notlDataNode, 'redIncome')}
			,repayments: {id: 'rpyIncome', value: IFDS.Xml.getNodeValue(notlDataNode, 'rpyIncome')}
			,balance: {id: 'balIncome', value: IFDS.Xml.getNodeValue(notlDataNode, 'balIncome')}							
		});
		container.add(dataRow);
		var dataRow = new DesktopWeb.ScreenResources.DataRow({
			rowLabel: _translationMap['TotalContribution']
			,staticRow: !_modPerm || !_notlExists
			,allowEdit: periodFilterUsed
			,purchase: {id: 'purContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'purContrib')}
			,redemption: {id: 'redContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'redContrib')}
			,repayments: {id: 'rpyContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'rpyContrib')}
			,balance: {id: 'balTotContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'balTotContrib')}			
		});		 
		container.add(dataRow);
		var dataRow = new DesktopWeb.ScreenResources.DataRow({
			rowLabel: _translationMap['AssistedContribution']
			,staticRow: !_modPerm || !_notlExists
			,allowEdit: periodFilterUsed
			,purchase: {id: 'purACContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'purACContrib')}
			,redemption: {id: 'redACContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'redACContrib')}
			,repayments: {id: 'rpyACContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'rpyACContrib')}
			,balance: {id: 'balACContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'balACContrib')}				
		});		 
		container.add(dataRow);
		var dataRow = new DesktopWeb.ScreenResources.DataRow({
			rowLabel: _translationMap['UnassistedContribution']
			,staticRow: !_modPerm || !_notlExists
			,allowEdit: periodFilterUsed
			,purchase: {id: 'purUCContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'purUCContrib')}
			,redemption: {id: 'redUCContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'redUCContrib')}
			,repayments: {id: 'rpyUCContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'rpyUCContrib')}
			,balance: {id: 'balUCContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'balUCContrib')}				
		});		 
		container.add(dataRow);
		var dataRow = new DesktopWeb.ScreenResources.DataRow({
			rowLabel: _translationMap['Pre1998']
			,staticRow: !_modPerm || !_notlExists
			,allowEdit: periodFilterUsed
			,purchase: {id: 'purPre98', value: IFDS.Xml.getNodeValue(notlDataNode, 'purPre98')}
			,redemption: {id: 'redPre98', value: IFDS.Xml.getNodeValue(notlDataNode, 'redPre98')}
			,repayments: {id: 'rpyPre98', value: IFDS.Xml.getNodeValue(notlDataNode, 'rpyPre98')}
			,balance: {id: 'balPre98', value: IFDS.Xml.getNodeValue(notlDataNode, 'balPre98')}				
		});		 
		container.add(dataRow);		
	}
	
	function populateSAGESContribution(notlDataNode, periodFilterUsed)
	{
	
		var container = Ext.getCmp('sagesContributionFS')
		container.show();
		
		//SAGES Assisted Contribution
		var dataRow = new DesktopWeb.ScreenResources.DataRow({
			rowLabel: _translationMap['sagesAssistedContribution']
			,staticRow: !_modPerm || !_notlExists
			,allowEdit: periodFilterUsed
			,purchase:   {id: 'sPurACContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'sPurACContrib')}
			,redemption: {id: 'sRedACContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'sRedACContrib')}
			,repayments: {id: 'sRpyACContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'sRpyACContrib')}
			,balance:    {id: 'sBalACContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'sBalACContrib')}				
		});			
		container.add(dataRow);
		
		//SAGES Unassisted Contribution
		var dataRow = new DesktopWeb.ScreenResources.DataRow({
			rowLabel: _translationMap['sagesUnassistedContribution']
			,staticRow: !_modPerm || !_notlExists
			,allowEdit: periodFilterUsed
			,purchase:   {id: 'sPurUCContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'sPurUCContrib')}
			,redemption: {id: 'sRedUCContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'sRedUCContrib')}
			,repayments: {id: 'sRpyUCContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'sRpyUCContrib')}
			,balance:    {id: 'sBalUCContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'sBalUCContrib')}					
		});	
		container.add(dataRow);
	}
	
	function populateGrants(notlDataNode, periodFilterUsed)
	{
		var container = Ext.getCmp('grants')
		container.show();
		var dataRow = new DesktopWeb.ScreenResources.DataRow({
			rowLabel: _translationMap['TotalCESG']
			,staticRow: !_modPerm || !_notlExists
			,allowEdit: periodFilterUsed
			,purchase: {id: 'purCESGTotal', value: IFDS.Xml.getNodeValue(notlDataNode, 'purCESGTotal')}
			,redemption: {id: 'redCESGTotal', value: IFDS.Xml.getNodeValue(notlDataNode, 'redCESGTotal')}
			,repayments: {id: 'rpyCESGTotal', value: IFDS.Xml.getNodeValue(notlDataNode, 'rpyCESGTotal')}
			,balance: {id: 'balTotCESG', value: IFDS.Xml.getNodeValue(notlDataNode, 'balTotCESG')}				
		});				
		container.add(dataRow);
		var dataRow = new DesktopWeb.ScreenResources.DataRow({
			rowLabel: _translationMap['BasicCESG']
			,staticRow: !_modPerm || !_notlExists
			,allowEdit: periodFilterUsed
			,purchase: {id: 'purCESGGrant', value: IFDS.Xml.getNodeValue(notlDataNode, 'purCESGGrant')}
			,redemption: {id: 'redCESGGrant', value: IFDS.Xml.getNodeValue(notlDataNode, 'redCESGGrant')}
			,repayments: {id: 'rpyCESGGrant', value: IFDS.Xml.getNodeValue(notlDataNode, 'rpyCESGGrant')}
			,balance: {id: 'balCESG', value: IFDS.Xml.getNodeValue(notlDataNode, 'balCESG')}				
		});		 
		container.add(dataRow);
		var dataRow = new DesktopWeb.ScreenResources.DataRow({
			rowLabel: _translationMap['AdditionalCESG']
			,staticRow: !_modPerm || !_notlExists
			,allowEdit: periodFilterUsed
			,purchase: {id: 'purAddlGrant', value: IFDS.Xml.getNodeValue(notlDataNode, 'purAddlGrant')}
			,redemption: {id: 'redAddlGrant', value: IFDS.Xml.getNodeValue(notlDataNode, 'redAddlGrant')}
			,repayments: {id: 'rpyAddlGrant', value: IFDS.Xml.getNodeValue(notlDataNode, 'rpyAddlGrant')}
			,balance: {id: 'balAddlGrant', value: IFDS.Xml.getNodeValue(notlDataNode, 'balAddlGrant')}				
		});		 
		container.add(dataRow);
		var dataRow = new DesktopWeb.ScreenResources.DataRow({
			rowLabel: _translationMap['CLB']
			,staticRow: !_modPerm || !_notlExists
			,allowEdit: periodFilterUsed
			,purchase: {id: 'purCLB', value: IFDS.Xml.getNodeValue(notlDataNode, 'purCLB')}
			,redemption: {id: 'redCLB', value: IFDS.Xml.getNodeValue(notlDataNode, 'redCLB')}
			,repayments: {id: 'rpyCLB', value: IFDS.Xml.getNodeValue(notlDataNode, 'rpyCLB')}
			,balance: {id: 'balCLB', value: IFDS.Xml.getNodeValue(notlDataNode, 'balCLB')}				
		});		 
		container.add(dataRow);		
		var dataRow = new DesktopWeb.ScreenResources.DataRow({
			rowLabel: _translationMap['PGrantACES']
			,staticRow: !_modPerm || !_notlExists
			,allowEdit: periodFilterUsed
			,purchase: {id: 'purpGrant', value: IFDS.Xml.getNodeValue(notlDataNode, 'purpGrant')}
			,redemption: {id: 'redpGrant', value: IFDS.Xml.getNodeValue(notlDataNode, 'redpGrant')}
			,repayments: {id: 'rpypGrant', value: IFDS.Xml.getNodeValue(notlDataNode, 'rpypGrant')}
			,balance: {id: 'balACES', value: IFDS.Xml.getNodeValue(notlDataNode, 'balACES')}				
		});		 
		container.add(dataRow);
		
		if (_showSAGES)
		{
			var dataRow = new DesktopWeb.ScreenResources.DataRow({
				rowLabel: _translationMap['PGrantSAGES']
				,staticRow: !_modPerm || !_notlExists
				,allowEdit: periodFilterUsed
				,purchase:   {id: 'purSAGES', value: IFDS.Xml.getNodeValue(notlDataNode, 'purSAGES')}
				,redemption: {id: 'redSAGES', value: IFDS.Xml.getNodeValue(notlDataNode, 'redSAGES')}
				,repayments: {id: 'rpySAGES', value: IFDS.Xml.getNodeValue(notlDataNode, 'rpySAGES')}
				,balance:    {id: 'balSAGES', value: IFDS.Xml.getNodeValue (notlDataNode, 'balSAGES ')}				
			});		 
			container.add(dataRow);
		}
		
		var dataRow = new DesktopWeb.ScreenResources.DataRow({
			rowLabel: _translationMap['CESGReceivedOther']
			,staticRow: !_modPerm || !_notlExists
			,allowEdit: periodFilterUsed
			,purchase: {id: 'purCesgPaid', value: IFDS.Xml.getNodeValue(notlDataNode, 'purCesgPaid')}
			,redemption: {id: 'redCesgPaid', value: IFDS.Xml.getNodeValue(notlDataNode, 'redCesgPaid')}
			,repayments: {id: 'rpyCesgPaid', value: IFDS.Xml.getNodeValue(notlDataNode, 'rpyCesgPaid')}
			,balance: {id: 'balCesgPaid', value: IFDS.Xml.getNodeValue(notlDataNode, 'balCesgPaid')}				
		});		 
		container.add(dataRow);
							
		if (_showQESI)
		{
			var totalQESIDataRow = new DesktopWeb.ScreenResources.DataRow({
				rowLabel: _translationMap['TotalQESI']
				,staticRow: !_modPerm || !_notlExists
				,allowEdit: periodFilterUsed
				,purchase: {id: 'totQGrant', value: IFDS.Xml.getNodeValue(notlDataNode, 'totQGrant')}
				,redemption: {id: 'grantRed', value: IFDS.Xml.getNodeValue(notlDataNode, 'grantRed')}
				,repayments: {id: 'grantRepymt', value: IFDS.Xml.getNodeValue(notlDataNode, 'grantRepymt')}
				,balance: {id: 'balGrant', value: IFDS.Xml.getNodeValue(notlDataNode, 'balGrant')}					
			});		 
			container.add(totalQESIDataRow);
			var basicQESIDataRow = new DesktopWeb.ScreenResources.DataRow({
				rowLabel: _translationMap['BasicQESI']
				,staticRow: !_modPerm || !_notlExists
				,allowEdit: periodFilterUsed
				,purchase: {id: 'grantBasicPur', value: IFDS.Xml.getNodeValue(notlDataNode, 'grantBasicPur')}
				,redemption: {id: 'redBasic', value: IFDS.Xml.getNodeValue(notlDataNode, 'redBasic')}
				,repayments: {id: 'rpyBasic', value: IFDS.Xml.getNodeValue(notlDataNode, 'rpyBasic')}
				,balance: {id: 'balGrantBasic', value: IFDS.Xml.getNodeValue(notlDataNode, 'balGrantBasic')}					
				,listeners: {
					edit: function(){updateTotalQESI()}
				}
			});		 
			container.add(basicQESIDataRow);
			var increaseQESIDataRow = new DesktopWeb.ScreenResources.DataRow({
				rowLabel: _translationMap['IncreaseQESI']
				,staticRow: !_modPerm || !_notlExists
				,allowEdit: periodFilterUsed
				,purchase: {id: 'grantAddlPur', value: IFDS.Xml.getNodeValue(notlDataNode, 'grantAddlPur')}
				,redemption: {id: 'redAddl', value: IFDS.Xml.getNodeValue(notlDataNode, 'redAddl')}
				,repayments: {id: 'rpyAddl', value: IFDS.Xml.getNodeValue(notlDataNode, 'rpyAddl')}
				,balance: {id: 'balGrantAddl', value: IFDS.Xml.getNodeValue(notlDataNode, 'balGrantAddl')}					
				,listeners: {
					edit: function(){updateTotalQESI()}
				}
			});		 
			container.add(increaseQESIDataRow);	
			var QESIPaidinEAPbyOtherDataRow = new DesktopWeb.ScreenResources.DataRow({
				rowLabel: _translationMap['QESIPaid']
				,staticRow: true
				,allowEdit: periodFilterUsed
				,purchase: {id: 'purQESIPaid', value: IFDS.Xml.getNodeValue(notlDataNode, 'purQESIPaid')}
				,redemption: {id: 'redQESIPaid', value: IFDS.Xml.getNodeValue(notlDataNode, 'redQESIPaid')}
				,repayments: {id: 'rpyQESIPaid', value: IFDS.Xml.getNodeValue(notlDataNode, 'rpyQESIPaid')}
				,balance: {id: 'balQESIPaid', value: IFDS.Xml.getNodeValue(notlDataNode, 'balQESIPaid')}				
			});
			container.add(QESIPaidinEAPbyOtherDataRow);	
		}
		
		function updateTotalQESI()
		{
			totalQESIDataRow.purchaseFld.setValue((Number(basicQESIDataRow.purchaseFld.getValue()) 
				+ Number(increaseQESIDataRow.purchaseFld.getValue())).toFixed(2));
			totalQESIDataRow.onEdit();
		}
	}
	
	function populateQESI(notlDataNode, periodFilterUsed, ytdLabel)
	{
		var container = Ext.getCmp('qesi')
		container.show();
		if (periodFilterUsed)
		{				
			var dataRow = new DesktopWeb.ScreenResources.DataRow({
				rowLabel: ytdLabel
				,staticRow: true
				,allowEdit: periodFilterUsed
				,purchase: {id: 'ytdPurContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'ytdPurContrib')}
				,redemption: {id: 'ytdRedContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'ytdRedContrib')}
				,repayments: {id: 'ytdRpyContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'ytdRpyContrib')}
				,balance: {id: 'balYTDContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'balYTDContrib')}					
			});				
			container.add(dataRow);
			var totalContribDataRow = new DesktopWeb.ScreenResources.DataRow({
				rowLabel: _translationMap['TotalContribution']
				,staticRow: true
				,allowEdit: periodFilterUsed
				,purchase: {id: 'qPurContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'qPurContrib')}
				,redemption: {id: 'qRedContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'qRedContrib')}
				,repayments: {id: 'qRpyContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'qRpyContrib')}
				,balance: {id: 'balQTotContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'balQTotContrib')}					
			});				
			container.add(totalContribDataRow);
			var assistedContribDataRow = new DesktopWeb.ScreenResources.DataRow({
				rowLabel: _translationMap['AssistedContribution']
				,staticRow: !_modPerm || !_notlExists
				,allowEdit: periodFilterUsed
				,purchase: {id: 'qPurACContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'qPurACContrib')}
				,redemption: {id: 'qRedACContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'qRedACContrib')}
				,repayments: {id: 'qRpyACContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'qRpyACContrib')}
				,balance: {id: 'balQACContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'balQACContrib')}			
				,listeners: {
					edit: function(){
						updateTotalContribPurchase()
						updateTotalContribRedemption()
					}
				}
			});				
			container.add(assistedContribDataRow);
			var unassistedContribDataRow = new DesktopWeb.ScreenResources.DataRow({
				rowLabel: _translationMap['UnassistedContribution']
				,staticRow: !_modPerm || !_notlExists
				,allowEdit: periodFilterUsed
				,purchase: {id: 'qPurUCContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'qPurUCContrib')}
				,redemption: {id: 'qRedUCContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'qRedUCContrib')}
				,repayments: {id: 'qRpyUCContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'qRpyUCContrib')}
				,balance: {id: 'balQUCContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'balQUCContrib')}					
				,listeners: {
					edit: function(){
						updateTotalContribPurchase()
						updateTotalContribRedemption()
					}
				}
			});				
			container.add(unassistedContribDataRow);
			var dataRow = new DesktopWeb.ScreenResources.DataRow({
				rowLabel: _translationMap['PreFeb212007']
				,staticRow: !_modPerm || !_notlExists
				,allowEdit: periodFilterUsed
				,purchase: {id: 'prePurContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'prePurContrib')}
				,redemption: {id: 'preRedContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'preRedContrib')}
				,repayments: {id: 'preRpyContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'preRpyContrib')}
				,balance: {id: 'balPreContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'balPreContrib')}					
			});				
			container.add(dataRow);
			var dataRow = new DesktopWeb.ScreenResources.DataRow({
				rowLabel: _translationMap['Pre1998']
				,staticRow: !_modPerm || !_notlExists
				,allowEdit: periodFilterUsed
				,purchase: {id: 'pre98PurContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'pre98PurContrib')}
				,redemption: {id: 'pre98RedContrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'pre98RedContrib')}
				,repayments: {id: 'rpyPre98Contrib', value: IFDS.Xml.getNodeValue(notlDataNode, 'rpyPre98Contrib')}
				,balance: {id: 'balQPre98', value: IFDS.Xml.getNodeValue(notlDataNode, 'balQPre98')}					
			});				
			container.add(dataRow);
		}
		else
		{
			container.setTitle(_translationMap['QESIContribution'] + ' (' + _translationMap['QESIUnavailable'] + ')');
		}
		
		function updateTotalContribPurchase()
		{
			totalContribDataRow.purchaseFld.setValue((Number(assistedContribDataRow.purchaseFld.getValue()) 
				+ Number(unassistedContribDataRow.purchaseFld.getValue())).toFixed(2));
			totalContribDataRow.onEdit();
		}
		
		function updateTotalContribRedemption()
		{
			totalContribDataRow.redemptionFld.setValue((Number(assistedContribDataRow.redemptionFld.getValue()) 
				+ Number(unassistedContribDataRow.redemptionFld.getValue())).toFixed(2));
			totalContribDataRow.onEdit();
		}
	}
	
	function buildUpdateXML()
	{
		var updateXML = IFDS.Xml.newDocument("data");
		
		IFDS.Xml.addSingleNode(updateXML, 'AccountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);		
		IFDS.Xml.addSingleNode(updateXML, 'versionNotl', _versionNotl);
		IFDS.Xml.addSingleNode(updateXML, 'versionPNotl', _versionPNotl);		
		IFDS.Xml.addSingleNode(updateXML, 'versionPNotlSAGES', _versionPNotlSAGES);		
		
		var selectedInfoLevelRecord = _resources.grids['infoLevel'].getSelectedRecord();
		if (_resources.grids['infoLevel'].getRecordIndex(selectedInfoLevelRecord) == 0)
		{
			IFDS.Xml.addSingleNode(updateXML, 'notlLevel', 'acct');
		}
		else
		{
			IFDS.Xml.addSingleNode(updateXML, "notlLevel", "ben");
			IFDS.Xml.addSingleNode(updateXML, "benefID", selectedInfoLevelRecord.data['code']);
		}
		
		if (_resources.fields['periodRadio'].checked)
		{
			IFDS.Xml.addSingleNode(updateXML, "period", _resources.fields['period'].getValue());
		}
		else
		{
			IFDS.Xml.addSingleNode(updateXML, "asOfDate", _resources.fields['asOfDate'].getSMVDateString());
		}
		
		buildDataXML(Ext.getCmp('contributionAndIncome'));
		buildDataXML(Ext.getCmp('grants'));
		buildDataXML(Ext.getCmp('qesi'));
		buildDataXML(Ext.getCmp('sagesContributionFS'));
		
		return updateXML;		

		
		function buildDataXML(container)
		{
			var dataRows = container.items.items;
			for (var i = 0; i < dataRows.length; i++)
			{
				var data = dataRows[i].getData();				
				for (var d in data)
				{
					if (!isNaN(data[d]))
					{
						IFDS.Xml.addSingleNode(updateXML, d, data[d]);					
					}					
				}
			}
		}	
	}
	
	// PUBLIC ITEMS ******************************************
	return {
		updatesFlag: false
		
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			var requestXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(requestXML, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);			
			
			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading']);
			
			function responseHandler(success, responseXML)
			{											
				if (success)
				{												
					storePermissions(responseXML);
					storeDefaultValues(responseXML);					
					populateScreen(responseXML);					
				}
			}				
		}
		
		,updatePeriodFilter: function(){
			var infoLevelCode = _resources.grids['infoLevel'].getSelectedRecord().data['code'];
			var curPeriod = _resources.fields['period'].getValue();
								
			_resources.fields['period'].loadData(_periodOptionsMap[infoLevelCode]);
			if (IFDS.Xml.getNode(_periodOptionsMap[infoLevelCode], 'Element[code="' + curPeriod + '"]') == null)
			{
				_resources.fields['period'].reset();
				/* IN3005653 Default the period option to Life to Date when the previous period is blank */
				if (IFDS.Xml.getNode(_periodOptionsMap[infoLevelCode], 'Element[code="9999"]') != null)
				{
					_resources.fields['period'].setValue(_resources.fields['period'].getStore().getAt(0).data['code']);
				}
			}
		}
		
		,toggleFilterFields: function()
		{
			if (_resources.fields['periodRadio'].getValue())
			{
				_resources.fields['period'].enable();
				_resources.fields['asOfDate'].disable();
				_resources.fields['asOfDate'].reset();
			}
			else
			{
				_resources.fields['asOfDate'].enable();
				_resources.fields['period'].disable();
				_resources.fields['period'].reset();
			}
		}
		
		,doRefresh: function()
		{
			var requestXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(requestXML, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			
			var selectedInfoLevelRecord = _resources.grids['infoLevel'].getSelectedRecord();
			if (_resources.grids['infoLevel'].getRecordIndex(selectedInfoLevelRecord) == 0)
			{
				IFDS.Xml.addSingleNode(requestXML, 'notlLevel', 'acct');
			}
			else
			{
				IFDS.Xml.addSingleNode(requestXML, "notlLevel", "ben");
				IFDS.Xml.addSingleNode(requestXML, "benefID", selectedInfoLevelRecord.data['code']);
			}
			
			if (_resources.fields['periodRadio'].checked)
			{
				IFDS.Xml.addSingleNode(requestXML, "period", _resources.fields['period'].getValue());
			}
			else
			{
				IFDS.Xml.addSingleNode(requestXML, "asOfDate", _resources.fields['asOfDate'].getSMVDateString());
			}			
			
			clearNotionalDetails();			
			DesktopWeb.Ajax.doSmartviewAjax(_reloadView, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading']);
			
			function responseHandler(success, responseXML)
			{											
				if (success)
				{																	
					populateNotionalDetails(responseXML, _resources.fields['periodRadio'].checked);														
				}
			}	
		}
		
		,openHistoricalPopup: function(recType)
		{
			var viewParam = {}
			var title = _translationMap['RESPNotional'] + ' - ' + _translationMap['History']
			viewParam['auditType'] = 'RESPNotl';
			viewParam['searchValue1'] = _respNotlInfoId;
			
			_resources.popups['history'].init(title, 'dtHistRESPNotl', viewParam,true);			
			_resources.popups['history'].show();
		}
		
		,doUpdate: function()
		{
			var updateStatus = null;			
			DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, buildUpdateXML(), responseHandler, null);
			function responseHandler(success, responseXML)
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
			return updateStatus;
		}
	}	
}	