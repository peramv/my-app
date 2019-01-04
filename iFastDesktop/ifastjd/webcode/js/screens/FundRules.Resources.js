/*********************************************************************************************
 * @file	FundRules.Resources.js
 * @author	Matira Thanetkulabut
 * @desc	Resources file for FundRules screen
 *********************************************************************************************/
/*
 *  Navigate: Menu > Fund Level Maintenance > Fund Rules Maintenance
 *  
 *  History : 
 *  
 *  01-Feb-2016 Matira Thanetkulabut P0250394 T82268
 *              - Initial (allow user to maintain the rule type setup)
 *
 *  03-Mar-2016 Matira Thanetkulabut P0250394 DFT0060514 T82372 
 *              - Fix error when create multiple record
 *				- Application category
 *				- Details Button
 *
 *  07-Mar-2016 Matira Thanetkulabut P0250394 DFT0060866 T82383 
 *				- Modify the Historical,Details button.
 *              - Fix cannot create new record after error message is show.
 *              - Change order sequence.
 *
 *  11-Mar-2016 Matira Thanetkulabut P0250394 DFT0060896 T82439     
 *              - hide column OverrideValue when rule type is nonOverride.
 *
 *  18-Mar-2016 Matira Thanetkulabut P0250394 DFT0061192 T82487
 *              - improve logic to check permission add/mod/delete the records.
 *              - syncSize for popup fund rule maintenance.
 *              - improve details screen.
 *
 *  25-Mar-2016 Matira Thanetkulabut P0250394 DFT0061365 T82478
 *              - add new column baycom and class description for fund/class level.
 *
 *  22-Nov-2016 Zeljko Bajic P0257851 T84326 CHG0047691_MinInvestment
 *              - Added new implementation as required.
 *
 *  21-Dec-2016 Matira Thanetkulabut P0257851 DFT0070489 T84552
 *              - Fixed currency field in modify mode.
 *
 *  04-Jan-2017 Matira Thanetkulabut P0257851 DFT0070590 T84590
 *              - Fixed assetLevel field in modify mode.
 *
 *  06-Jan-2017 Matira Thanetkulabut P0257853 T84533 Minimum Investment
 *              - Added amount type field.
 *
 *  14-Mar-2017 Matira Thanetkulabut P0264163 T85069 Unusual Trading
 *              - Added ruletype 72 to support currency field
 *				- Added rule for show/hide Amount type field.
 *
 *  25-Apr-2017 Nopphawan Hatthaseriphong P0264164 T85370 Diamond Share Class Restriction
 *			    - Removed hard-coding _withCurr, _withAmtType, _withAssetLv, _withAssetType
 *
 *  17-Aug-2017 Matira Thanetkulabut P0264163 T86110 DFT0076448 Unusual Trading
 *              - Removed allowDecimals: false for overrideDec.
 *              
 * 	11-Dec-2017 Sreejith A 	P0274726 P0266789-1871
 * 			   - Added Reason and remarks fields
 *
 * 	13-Feb-2018 Sreejith A 	P0274726 P0274726-83
 * 			   - Removed Reason and remarks fields
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
    var _controller = ctrlr;
    var _translationMap = DesktopWeb.Translation.getTranslationMap();

    // content dimensions
    var _layoutHeight = 630;
    var _layoutWidth  = 680;

    // **** fields **** 
    var _fields = {
        onlineEWI: new DesktopWeb.Controls.Label(
        {
            fieldLabel: _translationMap['OnlineEWI']
            ,width: 80
        })
        ,cycleEWI: new DesktopWeb.Controls.Label(
        {
            fieldLabel: _translationMap['CycleEWI']
            ,width: 80
        })
        ,esgEWI: new DesktopWeb.Controls.Label(
        {
            fieldLabel: _translationMap['ESGEWI']
            ,width: 80
        })
        
        ,taxJurisDecl: new DesktopWeb.Controls.Label(
        {
            fieldLabel: _translationMap['TaxJurisdiction']
            ,text: ''
            ,style: 'font-size: 13px; margin-bottom: 3px'
        })
        ,provResDecl: new DesktopWeb.Controls.Label(
        {
            fieldLabel: _translationMap['ProvinceofResidence']
            ,text: ''
            ,style: 'font-size: 13px; margin-bottom: 3px'
        })		
        ,accountTypeDecl: new DesktopWeb.Controls.Label(
        {
            fieldLabel: _translationMap['AccountType']
            ,text: ''
            ,style: 'font-size: 13px; margin-bottom: 3px'
        })		
        ,taxTypeDecl: new DesktopWeb.Controls.Label(
        {
            fieldLabel: _translationMap['TaxType']
            ,text: ''
            ,style: 'font-size: 13px; margin-bottom: 3px'
        })		
        ,acctDesigDecl: new DesktopWeb.Controls.Label(
        {
            fieldLabel: _translationMap['AccountDesignation']
            ,text: ''
            ,style: 'font-size: 13px; margin-bottom: 3px'
        })
        
        ,ruleType: new DesktopWeb.Controls.SMVComboBox(
        {
            fieldLabel: _translationMap['RuleType']
            ,width: 230
            ,allowBlank: false
			,editable: false
            ,tabIndex: 1
            ,listeners: 
            {
                select: function(fld, record, index)
                {
                    _controller.populateDropdowns(fld.getValue());
                }
            }
        })    
        ,ruleLevel: new DesktopWeb.Controls.SMVComboBox(
        {
            fieldLabel: _translationMap['RuleLevel']
            ,width: 180
			,editable: false
            ,tabIndex: 2
            ,listeners: 
            {
                change: function(fld, newValue)
                {        
                    _controller.onChangeMainRuleLv();
                }
            }
        })   
        ,fundFld: new DesktopWeb.Controls.SuggestField(
        {
            fieldLabel: _translationMap['Fund']
            ,width: 230
            ,smartview: 'fundOnlySearch'	
            ,addtlSearchParams: [{name: 'inclInactive', valueFn: function(){return 'yes'}}]
            ,fields: ['fndDisp', 'fundCode','fundName']						
            ,valueField: 'fundCode'
            ,displayField: 'fndDisp'		
            ,disabled: true	
            ,tabIndex: 3            
            ,listeners: 
            {
                populated: function(fld, record)
                {
                    if(_fields['ruleLevel'].getValue() == '01')
                    _controller.loadClass(record.data['fundCode']);
                }
                ,cleared: function()
                {				
                    _fields['classFld'].reset();		
                    _fields['classFld'].disable();          
                }	
            }		
        })    
        ,classFld: new DesktopWeb.Controls.ComboBox(
        {
            fieldLabel: _translationMap['Class']
            ,width: 100
            ,autoSelect: true
            ,disabled: true	
            ,tabIndex: 4
            ,editable: false
            ,store: new Ext.data.XmlStore(
            {
                record: 'ClassInfo'
                ,fields: ['classCode']
                ,listeners: 
                {
                    load: function(store, records)
                    {
                        if (records.length > 0)
                        { 
                            _fields['classFld'].enable();
                            _fields['classFld'].setValue(records[0].data['classCode']);
                        }
                    }
                }
            })
            ,valueField: 'classCode'
            ,displayField: 'classCode'      
        })
        
        ,fundGroup: new DesktopWeb.Controls.SMVComboBox(
        {
            fieldLabel: _translationMap['FundGroup']
            ,width: 230
            ,tabIndex: 5
            ,disabled: true	
        })

        , fundSponsor: new DesktopWeb.Controls.SMVComboBox(
        {
            fieldLabel: _translationMap['FundSponsor']
            , width: 230
            , tabIndex: 6
            , disabled: true
        })

        ,activeBox: new DesktopWeb.Controls.Checkbox(
        {
            boxLabel: _translationMap['OnlyActive']
            ,checked: true
            ,tabIndex: 6
        })
      }
  
    // **** buttons ****
	var _buttons = {	
        searchBtn: new DesktopWeb.Controls.ActionButton(
        {
            style: 'margin-bottom: 3px'
            ,text: _translationMap['Search']
            ,disabled: true
            , handler: function()
            {
                if(_fields['ruleType'].isValid()){
                    if(_controller.updatesFlag){
                        DesktopWeb.Util.displayDiscardPrompt(handlePromptMsg)
                                                        
                        function handlePromptMsg(btn){
                            if(btn){
                                _controller.updatesFlag = false;
                                _controller.search();
                            }
                        }
                    }else{
                        _controller.search();
                    }
                }
            }  
        })
  }
  
	// **** grids ****
	var _grids = {
        fundRule: new DesktopWeb.AdvancedControls.GridPanel(
        {
            autoScroll: true
            ,height: 200
            ,width: _layoutWidth
            ,autoExpandColumn: 'ruleType'
            ,store: new Ext.data.XmlStore(
            {
                record: 'FundRule'
                , fields: ['errMsg', 'runMode', 'uuid', 'ruleType', 'ruleLevel', 'fundGroup', 'fund', 'class', 'fundSponsor', 'baycom', 'classE', 'startDate', 'stopDate', 'overrideDec', 'overrideLog', 'overrideChar', 'assetLevel', 'assetType','currency','onlineEWI', 'cycleEWI', 'esgEWI', 'taxJuris', 'provRes', 'acctType', 'taxType', 'acctDesignation', 'userName', 'processDate', 'modUser', 'modDate', 'version', 'allowMod', 'allowDel', 'amountType']
                ,listeners: 
                {
                    load: function(store, records)
                    {		
                        Ext.each(records, function(record)
                        {
                            record.data.startDate = DesktopWeb.Util.getDateDisplayValue(record.data.startDate);
                            record.data.stopDate = DesktopWeb.Util.getDateDisplayValue(record.data.stopDate);
                        });
                        
                        store.filterBy(function(record){
                            return (record.data.runMode != _controller.DEL);										
						});
                        
                        store.fireEvent('datachanged', store);
                    }
                    ,update: function(store)
                    {								
                        store.filterBy(function(record){return record.data.runMode != _controller.DEL});
                    }	
                }          
            })
            ,selModel: new Ext.grid.RowSelectionModel(
            {					
                singleSelect: true
                ,listeners: 
                {
                    rowselect: function(selModel, index, record)
                    {
                        _controller.populateDetails(record);
                    }
                    ,rowdeselect: function()
                    {
                        _controller.clearDetails();
                    }
                }
            })
            ,colModel: new Ext.grid.ColumnModel(
            {
                defaults: 
                {
                    menuDisabled: true
                }
                ,columns: [
                {
                    width: 22
                    ,id: 'errMsg'
                    ,renderer: function(val)
                    {
                        return (val ? DesktopWeb.Util.buildErrorFlag(val) : '');
                    }
                }
                ,{
                    header: _translationMap['RuleType']
                    ,id: 'ruleType'
                    ,dataIndex: 'ruleType'
                    ,width: 100
                    ,renderer: function(value)
                    {
                        return _controller.getListValueDesc('RuleTypeList', value, null);
                    }
                }
                ,{
                    header: _translationMap['Level']
                    ,id: 'ruleLevel'
                    ,dataIndex: 'ruleLevel'
                    ,width: 75
                    ,renderer: function(value,metadata,record)
                    {
                        return _controller.getListValueDesc('RuleLevelList', value, record.data.ruleType);
                    }
                }
                ,{
                    header: _translationMap['FundGroup']
                    ,id: 'fundGroup'
                    ,dataIndex: 'fundGroup'
                    ,width: 60
                }
                ,{
                    header: _translationMap['Fund']
                    ,id: 'fund'
                    ,dataIndex: 'fund'
                    ,width: 40
                }
                ,{
                    header: _translationMap['Class']
                    ,id: 'class'
                    ,dataIndex: 'class'
                    ,width: 42
                }
                ,{
                    header: _translationMap['FundSponsor']
                    , id: 'fundSponsor'
                    , dataIndex: 'fundSponsor'
                    , width: 60
                }
                ,{
                    header: _translationMap['Baycom']
                    ,id: 'baycom'
                    ,dataIndex: 'baycom'
                    ,width: 50
                    ,hidden: true
                }
                ,{
                    header: _translationMap['ClassE']
                    ,id: 'classE'
                    ,dataIndex: 'classE'
                    ,width: 70
                    ,hidden: true
                }
                ,{
                    header: _translationMap['StartDate']
                    ,id: 'startDate'
                    ,dataIndex: 'startDate'
                    ,width: 68
                }
                ,{
                    header: _translationMap['StopDate']
                    ,id: 'stopDate'
                    ,dataIndex: 'stopDate'
                    ,width: 68
                }
                ,{
                    header: _translationMap['OverrideValue']
                    ,id: 'value'
                    ,width: 85
                    ,hidden: true
                    ,renderer: function(value,metadata,record)
                    {
                        var ruleType = record.get('ruleType');
                        var overrideType = _controller.getRuleTypeOverrideType(ruleType);
                        
                        if (overrideType == 'overrideLog'){
                            return record.get('overrideLog');
                        }else if (overrideType == 'overrideDec'){
                            return record.get('overrideDec');
                        }else if (overrideType == 'overrideChar'){
                            return record.get('overrideChar');
                        }else{
                            return "";
                        }
                    }
                }
                ,{
                    header: _translationMap['AssetLevel']
                    ,id: 'assetLevel'
                    ,dataIndex: 'assetLevel'
                    ,width: 100
                    ,renderer: function(value,metadata,record)
                    {
                        return _controller.getListValueDesc('AssetLevelList', value, record.data.ruleType);
                    }
                }
                ,{
                header: _translationMap['AssetType']
                    ,id: 'assetType'
                    ,dataIndex: 'assetType'
                    ,width: 100
                    ,renderer: function(value,metadata,record)
                    {
                        return _controller.getListValueDesc('AssetTypeList', value, record.data.ruleType);
                    }
                }
                ,{
                header: _translationMap['Currency']
                    ,id: 'currency'
                    ,dataIndex: 'currency'
                    ,width: 80
				}
                ,{
                header: _translationMap['AmountType']
                    ,id: 'amountType'
                    ,dataIndex: 'amountType'
                    ,width: 80
            }]
        })
            ,buttons: [					
                new DesktopWeb.Controls.ActionButton(
                {
                    itemId: 'addBtn'								
                    ,text: _translationMap['Add']
                    ,disabled: true
                    ,handler: function()
                    {
                        _controller.openActionPopup(_controller.ADD);
                    }														
                })
                ,new DesktopWeb.Controls.ActionButton(
                {
                    itemId: 'modBtn'								
                    ,text: _translationMap['Modify']
                    ,disabled: true
                    ,handler: function()
                    {
                        _controller.openActionPopup(_controller.MOD);
                    }													
                })
                ,new DesktopWeb.Controls.ActionButton(
                {
                    itemId: 'delBtn'								
                    ,text: _translationMap['Delete']
                    ,disabled: true
                    ,handler: function()
                    {
                        _controller.openActionPopup(_controller.DEL);
                    }													
                })
                ,new DesktopWeb.Controls.ActionButton(
                {
                    itemId: 'dtlBtn'								
                    ,text: _translationMap['Details']
                    ,disabled: true	   
                    ,handler: function()
                    {
                        _controller.openFundClassPopup();
                    }
                })
                ,new DesktopWeb.Controls.ActionButton(
                {
                    itemId: 'adminBtn'
                    ,text: _translationMap['Admin']
                    ,disabled: true
                    ,handler: function()
                    {
                        _controller.openAdminPopup();
                    }
                    })
                ,new DesktopWeb.Controls.ActionButton(
                {
                    itemId: 'historicalBtn'
                    ,text: _translationMap['Historical']
                    ,disabled: true
                    ,handler: function()
                    {
                        _controller.openHistoryPopup();
                    }
                })
                ,new DesktopWeb.Controls.ActionButton(
                {
                    itemId: 'moreBtn'
                    ,text: _translationMap['More']
                    ,disabled: true
                    ,handler: function()
                    {
                        _controller.doReload();
                    }
                })
            ]}    
        )
        ,appCate: new DesktopWeb.AdvancedControls.GridPanel(
        {
            height: 180
            ,store: new Ext.data.XmlStore(
            {
                record: 'AppCate'
                ,fields: ['cateCode', 'cateDesc', 'value']          
            })
            ,selModel: new Ext.grid.RowSelectionModel(
            {					
                singleSelect: true
            })
            ,colModel: new Ext.grid.ColumnModel(
            {
                defaults: 
                { menuDisabled: true }
                ,columns: [
                {
                    header: _translationMap['ApplicationCategory']
                    ,width: 150
                    ,dataIndex: 'cateDesc'
                }
                ,{
                    header: _translationMap['Value']
                    ,dataIndex: 'value'
                    ,width: 508
                }]
            })      
            ,buttons: [					
                new DesktopWeb.Controls.ActionButton(
                {
                    itemId: 'edit'								
                    ,text: _translationMap['Edit']
                    ,disabled: true
                    ,style: 'margin-right: 5'		
                    ,handler: function()
                    {
                        _controller.openDetailsPopup(_grids['appCate'].getSelectedRecord().data['cateCode']);
                    }
                })
            ]
        })
        ,fndClsDisp: new DesktopWeb.AdvancedControls.GridPanel(
        {
            height: 200
            ,autoExpandColumn: 'fndClsDisp'
            ,store: new Ext.data.XmlStore(
            {
                record: 'PossibleMatch'
                ,fields: ['fndClsDisp']
            })
            ,selModel: new Ext.grid.RowSelectionModel(
            {					
                singleSelect: true
            })
            ,colModel: new Ext.grid.ColumnModel(
            {
                defaults: { menuDisabled: true }
                ,columns: [
                {
                    header: _translationMap['fund']
                    ,id: 'fndClsDisp'
                    ,dataIndex: 'fndClsDisp'
                }]
            })
        })
    }     
  
  // **** popups ****
    var _popups = {
        fundRule: new DesktopWeb.AdvancedControls.PopupWindow(
        {
            width: 500
            ,modal: true
            ,autoHeight: true
            ,forceLayout: true
            ,defaults: {  border:false  }
            ,listeners: 
            {
                beforeshow: function(){_popups['fundRule'].init()}
            }
            ,items:[
            {
                html: _translationMap['DeleteConfirmMsg']							
                ,style: 'text-align:center; color: red'														
            }
            ,{
                itemId: 'popupLayout1'						
                ,layout: 'column'
                ,defaults: {border:false}
                ,style: 'margin-top:5px; margin-left:5px'
                ,items: [
                {
                    layout: 'form'
                    ,labelWidth: 90
                    ,items :[
                        new DesktopWeb.Controls.SMVComboBox(
                        {
                            itemId: 'ruleType'
                            ,fieldLabel: _translationMap['RuleType']
                            ,width: 300
                            ,allowBlank: false
							,editable: false
                            ,listeners: {
                                change: function(fld, newValue){
                                    _popups['fundRule'].populateDropdowns(newValue);
                                }
								,select : function(fld, rec, index) 
                                {
                                    var popup = _popups['fundRule'];
									var ruleType = fld.value;
									var ovrType = _controller.getRuleTypeOverrideType(ruleType);
                                    
                                    popup.getField('ruleLevel').reset();
                                    popup.getField('overrideLog').hideField();
									                  popup.getField('overrideChar').hideField();
                                    popup.getField('overrideDec').hideField();
									                  popup.getField('assetLevel').reset();
                                    popup.getField('assetLevel').hideField();
                                    popup.getField('assetType').reset();
                                    popup.getField('assetType').hideField();
                                    popup.getField('currency').hideField();
									popup.getField('amountType').hideField();
                                    
                                    if (ovrType == "overrideLog")
                                    {
                                        popup.getField('overrideLog').reset();
                                        popup.getField('overrideLog').setValue('yes');
                                        popup.getField('overrideLog').showField();
                                    }
                                    else if (ovrType == "overrideDec")
                                    {
                                        popup.getField('overrideDec').reset();
                                        popup.getField('overrideDec').showField();
                                        
										_controller.populateDataList('fundRule', 'amountType', 'AmountTypeList' + ruleType);
										popup.getField('amountType').setValue(_controller.defaultValue['amountType']);
                                        
										if (_controller.getRuleTypeCurrencyDisplay(ruleType) == _controller.YES) {
                                            popup.getField('currency').reset();
                                            popup.getField('currency').showField();
                                        }
                                    }
                                    
                                    else if (ovrType == "overrideChar")
                                    {
                                        popup.getField('overrideChar').reset();
                                        popup.getField('overrideChar').setValue('');
                                        popup.getField('overrideChar').showField();
                                    }

                                	_controller.populateDataList('fundRule', 'assetLevel', 'AssetLevelList' + ruleType);
                                	_controller.populateDataList('fundRule', 'assetType', 'AssetTypeList' + ruleType);

                                    if (popup.rendered) popup.syncSize();
                                }
                            }
                        })
                        ,new DesktopWeb.Controls.SMVComboBox(
                        {
                            itemId: 'ruleLevel'
                            ,fieldLabel: _translationMap['RuleLevel']
                            ,width: 180
                            ,allowBlank: false
							,editable: false
                            ,listeners: 
                            {
                                select: function(fld, record, index)
                                {        
                                    _popups['fundRule'].onChangeRuleLv('fundRule');
                                    if (_popups['fundRule'].rendered) _popups['fundRule'].syncSize();
                                }
                            }
                        })
                    ]
                }]          
            }
            ,{
                itemId: 'popupLayout2'							
                ,layout: 'column'
                ,defaults: {border:false}
                ,style: 'margin-left:5px'
                ,items: [
                {
                    layout: 'form'
                    ,labelWidth: 90
                    ,items :[
                        new DesktopWeb.Controls.SuggestField(
                        {
                            itemId: 'fundItem'
                            ,fieldLabel: _translationMap['Fund']
                            ,width: 300
                            ,smartview: 'fundOnlySearch'	
                            ,addtlSearchParams: [{name: 'inclInactive', valueFn: function(){return 'yes'}}]
                            ,fields: ['fndDisp', 'fundCode','fundName']						
                            ,valueField: 'fundCode'
                            ,displayField: 'fndDisp'		
                            ,disabled: false		
                            ,allowBlank: false
                            ,listeners: 
                            {
                                populated: function(fld, record)
                                {
                                    // search class for fund/class ruleLevel
                                    if(_popups['fundRule'].getField('ruleLevel').getValue() == '01')
                                    { 
                                        _controller.loadClass(record.data['fundCode'],'fundRule');
                                    }
                                }
                                ,cleared: function()
                                {				
                                    _popups['fundRule'].getField('classItem').reset();		
                                    _popups['fundRule'].getField('classItem').disable();          
                                }	
                            }		
                        })
                        ,new DesktopWeb.Controls.ComboBox(
                        {
                            itemId: 'classItem'
                            ,fieldLabel: _translationMap['Class']
                            ,width: 80
                            ,autoSelect: true
                            ,disabled: true	
                            ,editable: false
                            ,store: new Ext.data.XmlStore(
                            {
                                record: 'ClassInfo'
                                ,fields: ['classCode']
                                ,listeners: 
                                {
                                    load: function(store, records)
                                    {
                                        if (records.length > 0)
                                        { 
                                            _popups['fundRule'].getField('classItem').enable();
                                            _popups['fundRule'].getField('classItem').setValue(records[0].data['classCode']);
                                        }
                                    }
                                }
                            })
                            ,valueField: 'classCode'
                            ,displayField: 'classCode' 
                        })
                        ,new DesktopWeb.Controls.SMVComboBox(
                        {
                            itemId: 'fundGroup'
                            ,fieldLabel: _translationMap['FundGroup']
                            ,width: 300
                            ,disabled: true	
                            ,allowBlank: false
                        })
                        , new DesktopWeb.Controls.SMVComboBox(
                        {
                            itemId: 'fundSponsor'
                            , fieldLabel: _translationMap['FundSponsor']
                            , width: 180
                            , disabled: true
                            , allowBlank: false
                            , editable: false
                        })
                    ]
                }]
            }
            , {
                itemId: 'popupLayout3'							
                ,layout: 'column'
                ,style: 'margin-left:5px'
                ,defaults: {border:false}
                ,items: [
                {
                    layout: 'form'
                    ,columnWidth: 0.60
                    ,labelWidth: 90
                    ,items :[
                        new DesktopWeb.Controls.DateField(
                        {
                            itemId: 'startDate'
                            ,fieldLabel: _translationMap['StartDate']
                            ,width: 120
                            ,allowBlank: false
                            ,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
                            ,altFormats : DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
                        })
                        ,new DesktopWeb.Controls.DateField(
                        {
                            itemId: 'stopDate'
                            ,fieldLabel: _translationMap['StopDate']
                            ,width: 120
                            ,allowBlank: false
                            ,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
                            ,altFormats : DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
                        })
						,new DesktopWeb.Controls.SMVComboBox(
                        {
                            itemId: 'assetLevel'
                            ,fieldLabel: _translationMap['AssetLevel']
							,editable: false
                            ,width: 150
                        })
                        , new DesktopWeb.Controls.SMVComboBox(
                        {
                            itemId: 'assetType'
                            , fieldLabel: _translationMap['AssetType']
							, editable: false
                            , width: 150
                        })
                        ,new DesktopWeb.Controls.YesNoComboBox(
                        {
                            itemId: 'overrideLog'
                            ,width: 110
                            ,fieldLabel: _translationMap['OverrideValue']	
                        })
                        ,new DesktopWeb.Controls.NumberField(
                        {
                            itemId: 'overrideDec'
                            ,width: 120	
                            ,fieldLabel: _translationMap['OverrideValue']
                            ,validator: function(value)
                            {
                                if (this.isVisible() && value != "")
                                {
                                    return true;
                                }
                                else
                                {
                                    return _translationMap['FldRequired'];
                                }
                            }
                        })
                        ,new DesktopWeb.Controls.TextField(
                        {
                            itemId: 'overrideChar'
                            ,width: 120	
                            ,fieldLabel: _translationMap['OverrideValue']
                            ,validator: function(value)
                            {
                                if (this.isVisible() && value != "")
                                {
                                    return true;
                                }
                                else
                                {
                                    return _translationMap['FldRequired']	
                                }
                            }
                        })
						, new DesktopWeb.Controls.SMVComboBox(
                        {
                            itemId: 'amountType'
                            , fieldLabel: _translationMap['AmountType']
                            , editable: false
                            , width: 80
                            ,autoLoad: true
                            , listeners: {
                                select: function(fld){
                                    if (fld.getValue() == 'D')
                                    {
                                        _popups['fundRule'].getField('currency').showField();
                                    }
                                    else
                                    {
                                        _popups['fundRule'].getField('currency').hideField();
                                        _popups['fundRule'].getField('currency').reset();
                                    }
                                    
                                    if (_popups['fundRule'].rendered)
                                        _popups['fundRule'].syncShadow();
                                }
                            }
						})
                        , new DesktopWeb.Controls.SMVComboBox(
                        {
                            itemId: 'currency'
                            , fieldLabel: _translationMap['Currency']
							, editable: false
                            , width: 150
                        })
                    ]
                }
                ,{
                    xtype: 'fieldset'
                    ,title: _translationMap['Severity']  
                    ,columnWidth: 0.40
                    ,style: 'margin-left:5px'
                    ,border: true
                    ,items: [
                    {
                        layout: 'form'
                        ,labelWidth: 80
                        ,defaults: {border:false}
                        ,border: false
                        ,items: [
                            new DesktopWeb.Controls.SMVComboBox(
                            {
                                itemId: 'onlineEWI'
                                ,fieldLabel: _translationMap['OnlineEWI']				
                                ,width: 80	
								,editable: false
                            })
                            ,new DesktopWeb.Controls.SMVComboBox(
                            {
                                itemId: 'cycleEWI'
                                ,fieldLabel: _translationMap['CycleEWI']				
                                ,width: 80		
								,editable: false
                            })
                            ,new DesktopWeb.Controls.SMVComboBox(
                            {
                                itemId: 'esgEWI'
                                ,fieldLabel: _translationMap['ESGEWI']				
                                ,width: 80			
                                ,editable: false
                            })								
                        ]												
                    }]
                }]
            }]
            ,buttons: [
                new DesktopWeb.Controls.ActionButton(
                {
                    text: _translationMap['OK']
                    ,handler: function()
                    {
                        if (_popups['fundRule'].isValid())
                        {
                            _controller.doValidateFundRule(_popups['fundRule'].action, _popups['fundRule'].getData());	
                        }
                    }
                })
                ,new DesktopWeb.Controls.ActionButton(
                {
                    text: _translationMap['Cancel']
                    ,handler: function()
                    {
                        _controller.closePopup('fundRule');
                    }
                })
            ]
            ,setAction: function(action)
            {
                this.action = action
            }
            ,init: function()
            {	
                this.get(0).hide(); 
                this.clearAllFields();
                switch(this.action)
                {
                    case _controller.ADD:
                    {
                        this.setTitle(_translationMap['fndRuleAdd']);
                        this.enableAllFields();
                        break;
                    }
                    case _controller.MOD:
                    {
                        this.setTitle(_translationMap['fndRuleMod']);
                        this.toggleOverrideType();
                        this.populateWithSelectedRecord();	            
                        break;
                    }
                    case _controller.DEL:
                    {							
                        this.setTitle(_translationMap['fndRuleDel']);
                        this.disableAllFields();
                        this.toggleOverrideType();
                        this.populateWithSelectedRecord();            
                        this.get(0).show();
                        break;
                    }
                }					
            }
            ,getData: function()
            {				
                var rec = _grids['fundRule'].getSelectedRecord();
                var data = {};	
                
                data["runMode"] = this.action;
                data["ruleType"] = this.getField('ruleType').getValue();
                data["ruleLevel"] = this.getField('ruleLevel').getValue();
                data["fundGroup"] =  this.getField('fundGroup').getValue();
                data["fund"] =  this.getField('fundItem').getValue();
                data["class"] = this.getField('classItem').getValue();
                data["fundSponsor"] = this.getField('fundSponsor').getValue();
                data["startDate"] = this.getField('startDate').getDisplayDateString();
                data["stopDate"] =  this.getField('stopDate').getDisplayDateString();
                data["overrideDec"] =  this.getField('overrideDec').getValue();
                data["overrideLog"] =  this.getField('overrideLog').getValue();
                data["overrideChar"] =  this.getField('overrideChar').getValue();
                data["assetLevel"] =  this.getField('assetLevel').getValue();
                data["assetType"] = this.getField('assetType').getValue();
                data["currency"] = this.getField('currency').getValue();
                data["onlineEWI"] = this.getField('onlineEWI').getValue();
                data["cycleEWI"] =  this.getField('cycleEWI').getValue();
                data["esgEWI"] =  this.getField('esgEWI').getValue();	
                data["amountType"] = this.getField('amountType').getValue();
                
                if (this.action==_controller.ADD){
                    data["uuid"] = _controller.getNewUUID();
                    data["taxJuris"] = "*";
                    data["provRes"] =  "*";
                    data["acctType"] = "*";
                    data["taxType"] =  "*";
                    data["acctDesignation"] = "*";	
                    data["version"] = 0;
                    
                    var ovrType = _controller.getRuleTypeOverrideType(data['ruleType']);
                    if(ovrType == 'nonOverride'){
                        data["overrideLog"] =  'yes';
                    }
                }else{
                    data["uuid"] = rec.data['uuid'];
                    data["taxJuris"] = rec.data['taxJuris'];
                    data["provRes"] =  rec.data['provRes'];	
                    data["acctType"] = rec.data['acctType'];
                    data["taxType"] =  rec.data['taxType'];
                    data["acctDesignation"] = rec.data['acctDesignation'];	
                    data["version"] = rec.data['version'];
                }
                
                return data;
            }
            ,populateWithSelectedRecord: function()
            {
                var rec = _grids['fundRule'].getSelectedRecord();
                var appCates = _grids['appCate'].getAllRecords();
                
                this.getField('ruleType').setValue(rec.data['ruleType']);
				_popups['fundRule'].populateDropdowns(rec.data['ruleType']);
                this.getField('ruleLevel').setValue(rec.data['ruleLevel']);
                
                this.getField('startDate').setValue(rec.data['startDate']);
                this.getField('stopDate').setValue(rec.data['stopDate']);
                this.getField('overrideDec').setValue(rec.data['overrideDec']);
                this.getField('overrideLog').setValue(rec.data['overrideLog']);	
                this.getField('overrideChar').setValue(rec.data['overrideChar']);
                			
                this.getField('fundItem').setValue(rec.data['fund']);			
                this.getField('classItem').setValue(rec.data['class']);
                this.getField('fundSponsor').setValue(rec.data['fundSponsor']);
                this.getField('fundGroup').setValue(rec.data['fundGroup']);
                this.getField('onlineEWI').setValue(rec.data['onlineEWI']);			
                this.getField('cycleEWI').setValue(rec.data['cycleEWI']);			
                this.getField('esgEWI').setValue(rec.data['esgEWI']);	

                var ruleType = this.getField('ruleType').getValue();

                _controller.populateDataList('fundRule', 'amountType', 'AmountTypeList' + ruleType);
				
				this.getField('amountType').setValue(rec.data['amountType']);
					
				if (this.getField('amountType').store.getCount() > 0 
						&& rec.data['amountType'] == 'D'
						&& _controller.getRuleTypeCurrencyDisplay(ruleType) == _controller.YES)
                {
                    this.getField('currency').reset();
					this.getField('currency').setValue(rec.data['currency']);
                    this.getField('currency').showField();
                }
                
                _controller.populateDataList('fundRule', 'assetLevel', 'AssetLevelList' + ruleType);
                this.getField('assetLevel').setValue(rec.data['assetLevel']);
                
				_controller.populateDataList('fundRule', 'assetType', 'AssetTypeList' + ruleType);
                this.getField('assetType').setValue(rec.data['assetType']);
                
                this.getField('ruleType').disable();
                this.getField('ruleLevel').disable();

                switch(rec.data['ruleLevel'])
                {
                    // fund class level
                    case "01":
                        this.getField('fundItem').showField(); 
                        this.getField('classItem').showField();  
                        this.getField('fundItem').disable(); 
                        this.getField('classItem').disable();  
                        break;
                    // fund level
                    case "02": 
                        this.getField('fundItem').showField(); 
                        this.getField('fundItem').disable(); 
                        break;
                    // fundGroup level
                    case "03":
                        this.getField('fundGroup').showField(); 
                        this.getField('fundGroup').disable(); 
                        break;
                    // fundSponsor level
                    case "05":
                        this.getField('fundSponsor').showField();
                        this.getField('fundSponsor').disable();
                        break;
                }
                Ext.each(appCates, function(appCate)
                {
                    rec.data[appCate.get('cateCode')] =  this.action==_controller.ADD ? "*": appCate.get('value');
                });
            }
            ,populateDropdowns: function(newValue)
            {
                var ruleLv = "RuleLevelList" + newValue;
                _popups['fundRule'].getField('ruleLevel').setValue("");
                _popups['fundRule'].getField('ruleLevel').loadData(_controller.removeBlankRuleLv(ruleLv));
                
                var fundGrp = "FundGroupList" + newValue;
                _popups['fundRule'].getField('fundGroup').setValue("");
                _popups['fundRule'].getField('fundGroup').loadData(_controller.getDetailsListXML(fundGrp));
            }
			
            ,toggleOverrideType: function()
            {					
                var ovrType = _controller.getRuleTypeOverrideType(_grids['fundRule'].getSelectedRecord().data['ruleType']);
                var popup = _popups['fundRule'];
                popup.getField('overrideLog').hideField(); 
                popup.getField('overrideChar').hideField();
                popup.getField('overrideDec').hideField();
                
                if (ovrType == "overrideLog")
                {
                    popup.getField('overrideLog').reset();
                    popup.getField('overrideLog').setValue('yes');
                    popup.getField('overrideLog').showField();
                }
                else if (ovrType == "overrideDec")
                {
                    popup.getField('overrideDec').reset();
                    popup.getField('overrideDec').setValue(0);
                    popup.getField('overrideDec').showField();
                }
                else if (ovrType == "overrideChar")
                {
                    popups['fundRule'].getField('overrideChar').reset();
                    popups['fundRule'].getField('overrideChar').setValue('');
                    popups['fundRule'].getField('overrideChar').showField();
                }
            }
            , onChangeRuleLv: function ()
            {
                var popup = _popups['fundRule'];
                clearField('fundGroup');  
                clearField('fundItem');   
                clearField('classItem');
                clearField('fundSponsor');
                var ruleLv = popup.getField('ruleLevel').getValue();
                
                switch(ruleLv)
                {
                    // fund class level
                    case "01":
                        popup.getField('fundItem').showField(); 
                        popup.getField('classItem').showField();  
                        popup.getField('fundSponsor').hideField();
                        break;
                        
                    // fund level
                    case "02": 
                        popup.getField('fundItem').showField(); 
                        break;
                        
                    // fund group level
                    case "03":
                        popup.getField('fundGroup').showField(); 
                        break;

                    // fund sponsor level
                    case "05":
                        popup.getField('fundItem').hideField();
                        popup.getField('classItem').hideField();
                        _controller.populateDataList('fundRule', 'fundSponsor', 'FundSponsorList');
                        popup.getField('fundSponsor').showField();
                        break;
                }
                if (popup.rendered) popup.syncSize();
                
                function clearField(name)
                {
                    popup.getField(name).reset();
                    popup.getField(name).disable();
                    popup.getField(name).hide();
                }
            }
            ,getListValueDesc: function(listName, value)
            {
                if(listName == 'RuleTypeList'){ 
                    var listName2 = listName;    
                }
                else{
                    var listName2 = listName + _popups['fundRule'].getField('ruleType').getValue();
                }
                
                return _controller.getNodeValue(listName2,value);
            }
            ,clearAllFields: function()
            {
                this.getField('ruleType').reset();
                this.getField('ruleLevel').reset();
                this.getField('ruleLevel').getStore().removeAll();
                this.getField('startDate').reset();
                this.getField('stopDate').reset();
                this.getField('overrideDec').reset();
                this.getField('overrideLog').reset();
                this.getField('overrideChar').reset();
                this.getField('assetLevel').reset();
                this.getField('assetLevel').getStore().removeAll();
                this.getField('assetType').reset();
                this.getField('assetType').getStore().removeAll();
                this.getField('currency').reset();
				this.getField('amountType').reset();
                this.getField('fundItem').reset();
                this.getField('classItem').reset();
                this.getField('fundGroup').reset();
                this.getField('onlineEWI').reset();
                this.getField('cycleEWI').reset();
                this.getField('esgEWI').reset();
                this.getField('ruleType').enable();
                this.getField('ruleLevel').enable();
                this.getField('overrideLog').hideField();
                this.getField('overrideChar').hideField();
                this.getField('overrideDec').hideField();	
                this.getField('fundGroup').hideField();	
                this.getField('fundItem').hideField();	
                this.getField('classItem').hideField();	
                this.getField('fundSponsor').hideField();
                this.getField('assetLevel').hideField();
                this.getField('assetType').hideField();
                this.getField('currency').hideField();
				this.getField('amountType').hideField();
                this.enableAllFields();
            }
        })
    
        ,appCate: new DesktopWeb.AdvancedControls.PopupWindow(
        {
            width: 580
            ,fieldToEdit: null
            ,fieldList: null
            ,autoHeight: true            
            ,modal: true
            ,listeners: 
            {
                beforeshow: function()
                {
                    this.init();
                } 
            }
            ,defaults: {border:false, style: 'padding: 4px;'}
            ,items: [
            {
                layout: 'form'					
                ,labelWidth: 110																						
                ,items: [
                    new DesktopWeb.Controls.ComboBox(
                    {
                        itemId: 'inclExcl'			
                        ,width: 120							
                        ,fieldLabel: _translationMap['Chooseoptionsto']
                        ,allowBlank: false
                        ,store: new Ext.data.ArrayStore(
                        {
                            id: 0,
                            fields: ['myId', 'displayText' ],
                            data: 
                            [
                                ['include', _translationMap['Include']]
                                ,['exclude', _translationMap['Exclude']]
                            ]
                        })				
                        ,valueField: 'myId'
                        ,displayField: 'displayText'
                        ,value: 'include'
                    })				
                    ,new DesktopWeb.AdvancedControls.ItemSelector(
                    {
                        itemId: 'optionsSelector'
                        ,listName: null
                        ,height: 300
                        ,width: 540
                        ,style: 'margin-left:10px; margin-bottom: 10px'		
                        ,allowReordering: false		
                        ,availableGridProperties: 
                        {
                            width: 230				
                            ,autoExpandColumn: 'options'	
                            ,store: new Ext.data.XmlStore(
                            {
                                record: 'Element'					
                                ,fields: ['code', 'value']																							
                            })						
                            ,columns: [
                            {
                                id: 'options'					
                                ,header: _translationMap['Options']
                                ,dataIndex: 'code' 
                                ,renderer: function(value)
                                {											
                                    return value + " - " + _controller.getNodeValue(_popups['appCate'].getField('optionsSelector').listName, value);
                                }
                            }]	
                        }
                        ,selectedGridProperties: 
                        {
                            width: 230
                            ,autoExpandColumn: 'options'		         
                            ,store: new Ext.data.XmlStore(
                            {
                                record: 'Element'					
                                ,fields: ['code', 'value']														
                            })
                            ,columns: [
                            { 
                                id: 'options'
                                ,header: _translationMap['Options']
                                ,dataIndex: 'code'
                                ,renderer: function(value)
                                {											
                                    return value + " - " + _controller.getNodeValue(_popups['appCate'].getField('optionsSelector').listName, value);
                                }
                            }]
                        }
                    })	         
                ]
            }]
            ,buttons: [
                new DesktopWeb.Controls.ActionButton(
                {
                    text: _translationMap['OK']
                    ,handler: function()
                    {
                        _controller.saveDetailsUpdate(_popups['appCate'].fieldToEdit, _popups['appCate'].getData());	
                        _controller.closePopup('appCate');
                    }	
                })
                ,new DesktopWeb.Controls.ActionButton(
                {
                    text: _translationMap['Cancel']
                    ,handler: function()
                    {
                        _controller.closePopup('appCate');
                    }
                })
            ]
            ,setEditDetails: function(field, listName)
            {
                this.fieldToEdit = field;
                this.fieldList = listName;
            }
            ,init: function()
            {
                this.getField('optionsSelector').listName = this.fieldList;	            
                this.getField('optionsSelector').loadAvailableData(_controller.getDetailsListXML(this.fieldList));
                this.getField('optionsSelector').removeAllFromSelected();
                
                var curValue = _grids['appCate'].getSelectedRecord().data['value'];	
               
                if (curValue.indexOf("*") == 0)
                {
                    this.getField("inclExcl").setValue('exclude');
                    curValue = (curValue.length > 1 ? curValue.substring(2) : "");
                    curValue = curValue.replace(/!/g, '');
                   
                    if (curValue.length > 0)
                    {
                        this.getField('optionsSelector').setSelectedByData('code', curValue.split(","));
                    }
                }
                else
                {
                    this.getField("inclExcl").setValue('include');
                    if (curValue.length > 0)
                    {
                        this.getField('optionsSelector').setSelectedByData('code', curValue.split(","));
                    }
                }
                                
                switch(this.fieldToEdit)
                {
                    case 'taxJuris':
                    {
                        this.setTitle(_translationMap['TaxJurisdiction']+ ' - ' +_translationMap['Edit']);
                        break;		
                    }
                    case 'provRes':
                    {
                        this.setTitle(_translationMap['ProvinceofResidence']+ ' - ' +_translationMap['Edit']);
                        break;		
                    }
                    case 'acctType':
                    {
                        this.setTitle(_translationMap['AccountType']+ ' - ' +_translationMap['Edit']);
                        break;		
                    }
                    case 'taxType':
                    {
                        this.setTitle(_translationMap['TaxType']+ ' - ' +_translationMap['Edit']);
                        break;		
                    }
                    case 'acctDesignation':
                    {
                        this.setTitle(_translationMap['AccountDesignation']+ ' - ' +_translationMap['Edit']);
                        break;		
                    }					
                }																													
            }
            ,getData: function()
            {
                var value = "";
                
                var selectedRecords = this.getField("optionsSelector").getSelectedRecords();
                
                if (this.getField("inclExcl").getValue() == "include")
                {					
                    for (var i = 0; i < selectedRecords.length; i++)
                    {
                        value += (i > 0 ? "," : "") + selectedRecords[i].data['code']; 
                    }
                    if (value == "") value = "*";
                }
                else
                {
                    value = "*";
                    for (var i = 0; i < selectedRecords.length; i++)
                    {
                        value += ",!" + selectedRecords[i].data['code']; 
                    }
                }
                
                return value;
            }			
        })
        
        ,admin: new DesktopWeb.AdvancedControls.PopupWindow(
        {
            width: 395
            ,closeAction: 'hide'
            ,modal: true
            ,defaults: {border:false}
            ,items: [
            {
                layout: 'column'
                ,style: 'padding:4px'
                ,defaults: {border: false, labelWidth:80}
                ,items: [
                {
                    width: 185
                    ,layout: 'form'
                    ,defaults: {width:80}
                    ,items: [
                        new DesktopWeb.Controls.Label(
                        {
                            itemId: 'userName'
                            ,fieldLabel: _translationMap['Username']
                        })
                        ,new DesktopWeb.Controls.Label(
                        {
                            itemId: 'modUser'
                            ,fieldLabel: _translationMap['ModUser']
                        })
                    ]
                }
                ,{
                    width: 185
                    ,layout: 'form'
                    ,defaults: {width: 80}
                    ,items: 
                    [
                        new DesktopWeb.Controls.Label(
                        {
                            itemId: 'procDate'
                            ,fieldLabel: _translationMap['ProcessDate']
                        })
                        ,new DesktopWeb.Controls.Label(
                        {
                            itemId: 'modDate'
                            ,fieldLabel: _translationMap['ModDate']
                        })
                    ]
                }]
            }]
            ,buttons: [
                new DesktopWeb.Controls.ActionButton({
                    text: _translationMap['OK']
                    ,handler: function()
                    {
                        _popups['admin'].hide();
                    }
                })
            ]
            ,init: function(title, data)
            {
                this.setTitle(title);
                this.getField('procDate').setValue(data['procDate']);
                this.getField('modDate').setValue(data['modDate']);
                this.getField('userName').setValue(data['userName']);
                this.getField('modUser').setValue(data['modUser']);
            }
        })
        ,history: new DesktopWeb.AdvancedControls.HistoryPopup()
        
        ,detail: new DesktopWeb.AdvancedControls.PopupWindow(
        {
            width: 395
            ,closeAction: 'hide'
            ,modal: true
            ,autoHeight: true
            ,defaults: {border:false}
            ,items: [ _grids['fndClsDisp'] ]
            ,buttons: [
                new DesktopWeb.Controls.ActionButton({
                    text: _translationMap['Close']
                    ,handler: function()
                    {
                        _popups['detail'].hide();
                    }
                })
            ]
            ,init: function(title)
            {
                _grids['fndClsDisp'].getStore().removeAll();
                this.setTitle(title);
            }
        })
        
    }  
      
    // PUBLIC ITEMS
    return {
        layoutWidth: _layoutWidth

        ,layoutHeight: _layoutHeight

        ,fields: _fields

        ,grids: _grids

        ,popups: _popups

        ,buttons: _buttons

        ,layout: new Ext.Container(
        {
            height: _layoutHeight
            ,width: _layoutWidth
            ,items: [
            {
                itemId: 'mainLayout1'
                ,style: 'padding-left:5px; padding-right:10px'							
                 ,layout: 'column'
                ,items: [
                {
                    layout: 'form'
                    ,columnWidth: 0.55
                    ,labelWidth: 100
                    ,items :[
                        _fields['ruleType']
                        ,_fields['fundFld']
                    ]
                }
                ,{
                    layout: 'form'
                    ,columnWidth: 0.45
                    ,labelWidth: 100
                    ,items :[
                        _fields['ruleLevel']
                        ,_fields['classFld']
                    ]
                }]          
            }
            ,{
                itemId: 'mainLayout2'
                ,style: 'padding-left:5px; padding-right:10px; margin-bottom: 5px'							
                ,layout: 'column'
                ,items: [
                {
                    layout: 'form'
                    ,columnWidth: 0.55
                    ,labelWidth: 100
                    ,items :[
                        _fields['fundGroup']
                    ]
                }
                ,{
                    layout: 'auto'
                    ,columnWidth: 0.45
                    ,labelWidth: 80
                    ,items :[
                        _fields['activeBox']
                    ]
                }]          
            }
            , {
                itemId: 'mainLayout3'
                , style: 'padding-left:5px; padding-right:10px; margin-bottom: 5px'
                , layout: 'column'
                , items: [
                {
                    layout: 'form'
                    , columnWidth: 0.55
                    , labelWidth: 100
                    , items: [
                        _fields['fundSponsor']
                    ]
                }
                , {
                    layout: 'form'
                    , columnWidth: 0.45
                    , labelWidth: 150
                    , items: [
                        _buttons['searchBtn']
                    ]
                }]
            }
            , _grids['fundRule']
            ,{
                xtype: 'fieldset'
                ,title: _translationMap['Severity']									
                ,layout: 'column'         
                ,items: [
                {
                    layout: 'form'
                    ,columnWidth: 0.33
                    ,labelWidth: 80
                    ,items: [_fields['onlineEWI']]
                }
                ,{
                    layout: 'form'
                    ,columnWidth: 0.33
                    ,labelWidth: 80
                    ,items: [_fields['cycleEWI']]
                }
                ,{
                    layout: 'form'
                    ,columnWidth: 0.33
                    ,labelWidth: 80
                    ,items: [_fields['esgEWI']]				
                }]
            }
            ,{
                xtype: 'fieldset'
                ,title: _translationMap['ApplicableTo']
                ,items: [
                {
                    layout: 'column'																
                    ,items: [_grids['appCate']]
                }]
            }]
        })
        ,screenButtons: [			
            new DesktopWeb.Controls.ScreenButton({
                text: _translationMap['OK']
                ,handler: function(){
                    if (_controller.updatesFlag){
                        _controller.doValidate();
                    }else{
                        DesktopWeb.Util.cancelScreen();
                    }
                }
            })
            ,new DesktopWeb.Controls.ScreenButton({
                text: _translationMap['Cancel']
                ,handler: function(){
                    if (_controller.updatesFlag){
                        DesktopWeb.Util.displayDiscardPrompt(cancelScreen);
                    }else{
                        cancelScreen(true);
                    }
                    function cancelScreen(confirm){
                        if (confirm) 
                            DesktopWeb.Util.cancelScreen();
                    }
                }
            })
        ]			
    }
}