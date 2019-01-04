/*********************************************************************************************
 * @file	GrantContrib.Resources.js	
 * @author	Rod Walker
 * @desc	Resources JS file for Grant Contributions screen
 *
 * History  : 
 *
 *      14 Nov 2013 N. Kanjanawaikoon PP0181067 FN01 CHG0034430 T54444
 *          - Getting the date format from DesktopWeb.Util.getDateDisplayValue to show
 *            all date with correct format from registry field
 *********************************************************************************************/

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 280;
	var _layoutWidth = 715;
	
	// **** fields ****
	var _fields = {
	}
	
	// **** grids ****
	var _grids = {
		grantContrib: new DesktopWeb.AdvancedControls.GridPanel({
			width: 700
			,style: "padding-top:5px; padding-left:5px"
			,autoScroll: true
			,height: 240
			,store: new Ext.data.XmlStore({
				record: 'GrantContribRec'
				,fields: ['entName'
						 ,'transID'
						 ,'transNumber'
						 ,'hrdcTransID'
						 ,'tradeDt'
						 ,'transType'
						 ,'redDepCode'
						 ,'ucAmt'
						 ,'acAmt'
						 ,'grossAmt'
						 ,'grantAmt'
						 ,'rcvdAmt'
						 ,'benefID'
						 ,'origTransId'
						 ,'entityID'
						 ,'SAGESUCAmt'
						 ,'SAGESACAmt'
						 ,'SAGESID']		
				, listeners: {
						load: function(store, records) 
						{
							Ext.each(records, function(record){
								record.data['tradeDt'] = DesktopWeb.Util.getDateDisplayValue(record.data['tradeDt']);											
							});						
							
							store.fireEvent('datachanged', store); //to set data in grid again							
						}
					}						 
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true				
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [													
					{header: _translationMap['EntityName'], dataIndex: 'entName', width:135}
					,{header: _translationMap['TransId'], dataIndex: 'transID', width:75}
					,{header: _translationMap['TransNum'], dataIndex: 'transNumber', width:80}
					,{header: _translationMap['HRDCTransId'], dataIndex: 'hrdcTransID', width:80}
					,{header: _translationMap['SAGESID'], dataIndex: 'SAGESID', width:80}	
					,{header: _translationMap['TradeDate'], dataIndex: 'tradeDt', width:85}
					,{header: _translationMap['TransType'], dataIndex: 'transType', width:70}
					,{header: _translationMap['RedDepCode'], dataIndex: 'redDepCode', width:100}
					,{header: _translationMap['UCAmount'], dataIndex: 'usAmt', width:80}
					,{header: _translationMap['UCSAGES'], dataIndex: 'SAGESUCAmt', width:80}
					,{header: _translationMap['ACAmount'], dataIndex: 'acAmt', width:80}
					,{header: _translationMap['ACSAGES'], dataIndex: 'SAGESACAmt', width:80}
					,{header: _translationMap['GrossAmount'], dataIndex: 'grossAmt', width:80}
					,{header: _translationMap['GrantAmount'], dataIndex: 'grantAmt', width:80}
					,{header: _translationMap['ReceivedAmount'], dataIndex: 'rcvdAmt', width:80}					
				]							
			})			
			,buttons: [					
				new DesktopWeb.Controls.ActionButton({
					itemId: 'moreBtn'								
					,text: _translationMap['More']						
					,handler: function(){_controller.doReload(true);}
					,disabled: true
				})				
			]			
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
				{
					xtype: 'fieldset'																
					,title: _translationMap['ChooseOriginating']							
					,items: [
						_grids['grantContrib']								
					]
				}
			]																					
		})
				
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['OK']
				,handler: function(){
					if (_grids['grantContrib'].getSelectedRecord() != null)
					{
						DesktopWeb.Util.commitScreen()
					}
					else
					{
						DesktopWeb.Util.displayError(_translationMap['NoRecordSelected']);
					}
				}
			})
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Cancel']
				,handler: function(){DesktopWeb.Util.cancelScreen()}
			})
		]			
	}
}