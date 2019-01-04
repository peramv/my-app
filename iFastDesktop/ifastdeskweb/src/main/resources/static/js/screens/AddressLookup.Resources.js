/*********************************************************************************************
 * @file	AddressLookup.Resources.js	
 * @author	Narin Suanlamyai
 * @desc	Resources JS file file for Address Lookup screen
 *********************************************************************************************
 * Purpose  : Lookup an address by postal code
 *             
 * Notes    : Account Details Information --> Attributes --> Address/Mailing Assignments --> Shareholder/Entity
 *
 * History  :  
 *		06 Jun 2014 N. Suanlamyai P0231196 - CCS - Postal Code Look-up Enhancement T55248
 *					- Created
 *
 *		21 Aug 2014 N. Suanlamyai P0231196 DFT0038679 T55597
 *					- Fixed missing Route Info column for PO Box address type
 *
 *		19 Sep 2014 N. Suanlamyai P0231196 DFT0041009 T55746
 *					- Fixed caution label is not displayed on Windows 7.
 *
 *********************************************************************************************/
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 500;
	var _layoutWidth = 625;
	
	var _gridSize = 155;
	var _addAddrFieldWidth = 110;
	
	// **** buttons ****
	var _buttons = {
		searchBtn: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Search']
			,handler: function(){
				if (_controller.searchIsValid())
				{
					_controller.doSearch();
				}
			}
		})
	}
	
	// **** fields ****
	var _fields = {
		pstlCodeFld: new DesktopWeb.Controls.TextField({
			fieldLabel: _translationMap['PostalCode']
			,allowBlank: false
			,width: 80
			,listeners:{
			}
		})

		,addrTypeFld: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['AddressType']
			,width: 190
			,autoSelect: true
			,listeners:{
				select: function(fld, record, index){_controller.selectHandler_AddressTypeFld(record.get('code'));}
			}
		})

		,stNumFld: new DesktopWeb.Controls.NumberField({
			fieldLabel: _translationMap['StreetNumber']
			,width: _addAddrFieldWidth
			,allowDecimals: false
			,allowNegative: false
			,oddeven: null
			,listeners:{
				change: function(fld, newVal, oldVal){
					if (fld.isValid()) _controller.changeHandle_stNumFld(fld, newVal);
				}
			}
		})

		,suffixFld: new DesktopWeb.Controls.TextField({
			fieldLabel: _translationMap['Suffix']
			,width: _addAddrFieldWidth
			,listeners:{
				change: function(fld, newVal, oldVal){
					if (fld.isValid()) _controller.changeHandle_suffixFld(fld, newVal);
				}
			}
		})

		,unitNumFld: new DesktopWeb.Controls.NumberField({
			fieldLabel: _translationMap['UnitNumber']
			,width: _addAddrFieldWidth
			,allowDecimals: false
			,allowNegative: false
			,listeners:{
				change: function(fld, newVal, oldVal){
					if (fld.isValid()) _controller.changeHandle_unitNumFld(fld, newVal);
				}
			}
		})

		,unitDescFld: new DesktopWeb.Controls.TextField({
			fieldLabel: _translationMap['UnitDescription']
			,width: _addAddrFieldWidth
			,listeners:{
				change: function(fld, newVal, oldVal){
					if (fld.isValid()) _controller.changeHandle_unitDescFld(fld, newVal);
				}
			}
		})

		,POBoxFld: new DesktopWeb.Controls.NumberField({
			fieldLabel: _translationMap['POBox']
			,width: _addAddrFieldWidth
			,allowDecimals: false
			,allowNegative: false
			,listeners:{
				change: function(fld, newVal, oldVal){
					if (fld.isValid()) _controller.changeHandle_POBoxFld(fld, newVal);
				}
			}
		})
		
		,cautionLabel: new Ext.form.DisplayField({
			value: ''
			,hideLabel: true
			,hidden: true
			,style: 'color:red; text-align:right; display:block; padding-top:0px;'
		})
		
		,addr1Fld: new Ext.form.DisplayField({
			fieldLabel: _translationMap['Address1']
			,text: ''
		})
		
		,addr2Fld: new Ext.form.DisplayField({
			fieldLabel: _translationMap['Address2']
			,text: ''
		})
		,addr3Fld: new Ext.form.DisplayField({
			fieldLabel: _translationMap['Address3']
			,text: ''
		})
		
		,cityFld: new Ext.form.DisplayField({
			fieldLabel: _translationMap['City']
			,text: ''
		})
		
		,provinceFld: new Ext.form.DisplayField({
			fieldLabel: _translationMap['Province']
			,text: ''
		})
		
		,cntryCodeFld: new Ext.form.DisplayField({
			hidden: true
		})
	}
	
	// **** grids ****
	var _grids = {
		POBoxGrid: new DesktopWeb.AdvancedControls.GridPanel({
			autoScroll: true							
			,height: _gridSize
			,hidden: false
			,autoExpandColumn: 'delArea'				
			,store: new Ext.data.XmlStore({
				record: 'AddressRec'
				,fields: [
						  'pobFrom'
						  ,'pobTo' 
						  ,'delArea'
						  ,'routeInfo'
						  ,'city'
						  ]
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){_controller.selectHandle_POBoxGrid(record);}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [													
					{header: _translationMap['POBoxFrom'], dataIndex: 'pobFrom'}
					,{header: _translationMap['POBoxTo'], dataIndex: 'pobTo'}
					,{id: 'delArea', header: _translationMap['DeliveryArea'], dataIndex: 'delArea', width: 225}
					,{header: _translationMap['RouteInfo'], dataIndex: 'routeInfo', width:200}
				]
			})				
			,buttons: []
			,cntryCode: null
			,province: null
			,pstlCode: null
		})
		,CivicGrid: new DesktopWeb.AdvancedControls.GridPanel({
			autoScroll: true							
			,height: _gridSize
			,hidden: true
			,autoExpandColumn: 'stName'				
			,store: new Ext.data.XmlStore({
				record: 'AddressRec'
				,fields: [
						  'stFrom'
						  ,'stTo'
						  ,'oddeven' 
						  ,'stSfxFrom'
						  ,'stSfxTo'
						  ,'stName'
						  ,'unitFrom'
						  ,'unitTo'
						  ,'city'
						  ]
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){_controller.selectHandle_CivicGrid(record);}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [													
					{header: _translationMap['StNoFrom'], dataIndex: 'stFrom', width:70}
					,{header: _translationMap['StNoTo'], dataIndex: 'stTo', width:70}
					,{header: _translationMap['StNoSfxFrom'], dataIndex: 'stSfxFrom', width:70}
					,{header: _translationMap['StNoSfxTo'], dataIndex: 'stSfxTo', width:70}
					,{id: 'stName', header: _translationMap['StName'], dataIndex: 'stName'}
					,{header: _translationMap['UnitFrom'], dataIndex: 'unitFrom', width:70}
					,{header: _translationMap['UnitTo'], dataIndex: 'unitTo', width:70}
				]
			})				
			,buttons: []			
		})
		,GeneralGrid: new DesktopWeb.AdvancedControls.GridPanel({
			autoScroll: true							
			,height: _gridSize
			,hidden: true
			,autoExpandColumn: 'delInstall'				
			,store: new Ext.data.XmlStore({
				record: 'AddressRec'
				,fields: [
						  'delArea'
						  ,'delInstall'
						  ,'city' 
						  ]
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){_controller.selectHandle_GeneralGrid(record);}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [													
					{header: _translationMap['DeliveryArea'], dataIndex: 'delArea', width:200}
					,{id: 'delInstall', header: _translationMap['DeliveryInstallation'], dataIndex: 'delInstall'}
				]
			})				
			,buttons: []			
		})
		,RuralRouteGrid: new DesktopWeb.AdvancedControls.GridPanel({
			autoScroll: true							
			,height: _gridSize
			,hidden: true
			,autoExpandColumn: 'routeInfo'				
			,store: new Ext.data.XmlStore({
				record: 'AddressRec'
				,fields: [
						  'delArea'
						  ,'routeInfo'
						  ,'city' 
						  ]
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){_controller.selectHandle_RuralRouteGrid(record);}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [													
					{header: _translationMap['DeliveryArea'], dataIndex: 'delArea', width:200}
					,{id: 'routeInfo', header: _translationMap['RouteInfo'], dataIndex: 'routeInfo'}
				]
			})				
			,buttons: []			
		})
		,StRouteGrid: new DesktopWeb.AdvancedControls.GridPanel({
			autoScroll: true							
			,height: _gridSize
			,hidden: true
			,autoExpandColumn: 'stName'				
			,store: new Ext.data.XmlStore({
				record: 'AddressRec'
				,fields: [
						  'stFrom'
						  ,'stTo'
						  ,'oddeven'
						  ,'stSfxFrom'
						  ,'stSfxTo'
						  ,'stName'
						  ,'routeInfo'
						  ,'city' 
						  ]
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){_controller.selectHandle_StRouteGrid(record);}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [													
					{header: _translationMap['StNoFrom'], dataIndex: 'stFrom', width:70}
					,{header: _translationMap['StNoTo'], dataIndex: 'stTo', width:70}
					,{header: _translationMap['StNoSfxFrom'], dataIndex: 'stSfxFrom', width:70}
					,{header: _translationMap['StNoSfxTo'], dataIndex: 'stSfxTo', width:70}
					,{id: 'stName', header: _translationMap['StName'], dataIndex: 'stName'}
					,{header: _translationMap['RouteInfo'], dataIndex: 'routeInfo', width:70}
				]
			})				
			,buttons: []			
		})
	}
	
	// **** popups ****
	var _popups = {} 
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,buttons: _buttons
		
		,fields: _fields
		
		,grids: _grids
		
		,popups: _popups
		
		,layout: new Ext.Container({
			height: _layoutHeight
			,width: _layoutWidth
			//,style: 'padding-left:12px; padding-right:10px;overflow-y:auto;'
			,items: [					
				{
					layout: 'column'
					,style: "padding:5px"
					,defaults: {
						layout: 'form'
						,labelWidth: 75
					}
					,items: [
						{								
							columnWidth: 0.30
							,items: [
								_fields['pstlCodeFld']
							]
						}
						,{
							columnWidth: 0.7
							,labelWidth: 65
							,items: [
								_buttons['searchBtn']
							]
						}
					]
				}
				,{
					xtype: 'fieldset'
					,title: _translationMap['SearchResult']
					,width: _layoutWidth
					,labelWidth: 85
					,items: [
						_fields['addrTypeFld']
						,_grids['POBoxGrid']
						,_grids['CivicGrid']
						,_grids['GeneralGrid']
						,_grids['RuralRouteGrid']
						,_grids['StRouteGrid']
					]
				}
				,{
					layout: 'column'
					,height: 500
					,items: [
						{								
							columnWidth: 0.42
							,style: "padding-right:10px;padding-bottom:0px"
							,items: [
								{
									xtype: 'fieldset'
									,title: _translationMap['AdditionalAddressInfo']
									,labelWidth: 105
									,items: [
										_fields['stNumFld']
										,_fields['suffixFld']
										,_fields['unitNumFld']
										,_fields['unitDescFld']
										,_fields['POBoxFld']
									]
								}
								,{
									layout: 'form'
									,items:[
										_fields['cautionLabel']
									]
								}
							]
						}
						,{
							columnWidth: 0.58
							,items: [
								{
									xtype: 'fieldset'
									,title: _translationMap['AddressInfo']
									,labelWidth: 65
									,items: [
										_fields['addr1Fld']
										,_fields['addr2Fld']
										,_fields['addr3Fld']
										,{
											layout: 'column'
											,defaults: {
												layout: 'form'
												,labelWidth: 65
											}
											,items:[
												{
													columnWidth: 0.6
													,items:[
														_fields['cityFld']
													]
												}
												,{
													columnWidth: 0.4
													,items:[
														_fields['provinceFld']
													]
												}
											]
										}
									]
								}
							]
						}
					]
				}									
			]																				
		})
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['OK']
				,handler: function(){
					if ( _controller.screenIsValid() )
					{
						DesktopWeb.Util.commitScreen()
					}
				}
			})
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Cancel']
				,handler: function(){
					DesktopWeb.Util.cancelScreen();
					/*
					if(_controller.updatesFlag){
						DesktopWeb.Util.displayDiscardPrompt(handlePromptMsg)
													
						function handlePromptMsg(btn){
							if(btn){
								DesktopWeb.Util.cancelScreen();
							}
						}
					}else{
						DesktopWeb.Util.cancelScreen();
					}
					*/
				}
			})
		]				
	}
}