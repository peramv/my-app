/*********************************************************************************************
 * @file	RESPDiploma.Resources.js
 * @author	Manoj Kumar
 * @desc	Resources JS file for RESP Diploma Screen
 *********************************************************************************************/
 /*
 *  History : 
 *
 *  04 Nov 2013 A. Mongkonrat P0181067 CHG0034430 T54444
 *					- Fix display date format follows dateFormatDisplay parameter
 */

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 400;
	var _layoutWidth = 440;
	
	// **** buttons ****
	var _buttons = {
	}
	
	// **** fields ****
	var _fields = {
		allocationType: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['AllocationType']			
			,width: 175
		})		
		,maxIssued: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['MaxIssued']		
			,width: 100
		})
		,parentFund: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['ParentFund']			
			,width: 100
		})
		,allocation: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['Allocation']
			,width: 150
			,editable: false
			//,allowBlank: false
			,emptyText: _translationMap['SelectAllocation']
			,listeners: {
				select : function(fld, rec, index) {					
					_controller.updateSearchAge();
				}
			}
		})		
		,age: new DesktopWeb.Controls.SMVComboBox({	
			fieldLabel: _translationMap['Age']
			,width: 150
			,editable: false
			,allowBlank: false
			,emptyText: _translationMap['SelectAge']
			,disabled: true
			,listeners: {
				select : function(fld, rec, index) {					
					_controller.populateAllocPercentList(rec.data.code);					
				}				
			}
		})		
	}
	
	// **** grids ****
	var _grids = {
		respDiplomaList: new DesktopWeb.AdvancedControls.GridPanel({
			style: "margin-bottom:15px"
			,autoScroll: true
			,height: 125
			,width: 440
			,autoExpandColumn: 'desc'
			,store: new Ext.data.XmlStore({
				record: 'Element'
				,fields: ['name','desc','stopDate','maxIssued','parentFund']
				,listeners: {
					load: function(store, records) {	
						Ext.each(records, function(record){
									record.data.stopDate = DesktopWeb.Util.getDateDisplayValue(record.data.stopDate);									
						});

						store.fireEvent('datachanged', store); //to set data in grid again									
					}
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){
						_controller.updateRespDiplomaDetails();
					}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [
					{header: _translationMap['Name'], dataIndex: 'name', width:150}
					,{header: _translationMap['Description'], id:'desc', dataIndex: 'desc', width:200}
					,{header: _translationMap['StopDate'], dataIndex: 'stopDate', width:100}
				]
			})
		})
		,allocPercentageList: new DesktopWeb.AdvancedControls.GridPanel({
			style: "margin-bottom:15px"
			,autoScroll: true
			,height: 125
			,width: 440
			,autoExpandColumn: 'fund/class'
			,disableSelection: true
			,store: new Ext.data.XmlStore({
				record: 'Element'

				//incident #2864346 changes to get RESP diploma selection and filter accordinly 
				,fields: ['ageLower','ageUpper','sequence','Fund','class','percent', 'commitCode']
				,listeners: {
					load: function(store, records){
						store.filterBy(function(record){
							return ((record.data.ageLower == _controller.ageLower) && (record.data.commitCode == _controller.commitCode))
							});
					}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [
					{header: _translationMap['FundClass'], id:'fund/class', dataIndex: 'Fund', width:300, renderer: function(val, metaData, record){return (record.data['Fund'] + '/' + record.data['class'])}}
					,{header: _translationMap['Percent'], dataIndex: 'percent', width:150, renderer: function(val, metaData, record){return (record.data['percent'] + '%')}}							
				]
			})
		})
	}
	
	// **** popups ****
	var _popups = {	
	}
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,fields: _fields
		
		,grids: _grids
		
		,popups: _popups
		
		,layout: new Ext.Container({
			height: _layoutHeight
			,width: _layoutWidth
			,items: [
				_grids['respDiplomaList']
				,{	
					layout: 'form'						
					,items: [
						_fields['allocationType']							
						,_fields['maxIssued']
						,_fields['parentFund']
						,_fields['allocation']
						,_fields['age']
					]
				}					
				,_grids['allocPercentageList']									
			]				
		})		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['OK']
				,handler: function(){						
					DesktopWeb.Util.cancelScreen()
				}
			})			
		]			
	}
}