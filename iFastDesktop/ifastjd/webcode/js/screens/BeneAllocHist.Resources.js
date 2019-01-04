/*********************************************************************************************
 * @file	BeneAllocHist.Resources.js
 * @author	Rod Walker
 * @desc	Resources JS file for Beneficiary Allocation History screen.
 * History:
 *      06 Nov 2013 Supareuk S. PETP0181067 FN01 CHG0034430 T54444
 *          		- Correct the format of all date fields based on registry edit
 *                    ,called displayMark
 *********************************************************************************************/
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 250;
	var _layoutWidth = 600;
	
	// **** fields ****
	var _fields = {	
						
	}
		
	// **** grids ****
	var _grids = {	
		allocHistory: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth			
			,autoScroll: true
			,height: 100
			,autoExpandColumn: 'beneName'
			,store: new Ext.data.XmlStore({
				record: 'BeneficiaryAllocDetail'
				,fields: ['beneName' 
						  ,'deff'
						  ,'modDate' 
						  ,'moduser']				
				,listeners: {
					load: function(store, records)
					{
						Ext.each(records, function(record){
							record.data.deff = DesktopWeb.Util.getDateDisplayValue(record.data.deff);
							record.data.modDate = DesktopWeb.Util.getDateDisplayValue(record.data.modDate);
						});

						store.fireEvent('datachanged', store); //to set data in grid again
						
					}
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(){
						_controller.updateSelectedAllocRecord();							
					}
					,rowdeselect: function(){
						_controller.updateSelectedAllocRecord();
					}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [					
					{
						header: _translationMap['Beneficiaries']
						,id:'beneName'
						,renderer: function(value, metaData, record){							
							var recNodes = IFDS.Xml.getNodes(record.node, 'BeneficiaryAllocRec');
							var str = "";													
							for (var i = 0; i < recNodes.length; i++)
							{
								if (Number(IFDS.Xml.getNodeValue(recNodes[i], 'amt')) > 0)
								{
									str += (str.length > 0 ? "; " : "") + IFDS.Xml.getNodeValue(recNodes[i], 'beneName');
								}
							}
							return str;	
						}
					}
					,{header: _translationMap['EffDate'], dataIndex: 'deff', width: 90}
					,{header: _translationMap['ModDate'], dataIndex: 'modDate', width:90}
					,{header: _translationMap['ModUser'], dataIndex: 'moduser', width:100}
				]
			})			
		})
		,allocDetails: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth	- 16		
			,autoScroll: true
			,height: 110
			,style: 'padding-bottom: 8px;'
			,disableSelection: true
			,store: new Ext.data.XmlStore({
				record: 'BeneficiaryAllocRec'
				,fields: ['beneName' 
						  ,'deff' 
						  ,'modDate' 
						  ,'moduser'
						  ,'prcnt'
						  ,'amt'
						  ,'reported']				
				,listeners: {
					load: function(store, records)
					{
						Ext.each(records, function(record){
							record.data.deff = DesktopWeb.Util.getDateDisplayValue(record.data.deff);
							record.data.modDate = DesktopWeb.Util.getDateDisplayValue(record.data.modDate);
						});

						store.fireEvent('datachanged', store); //to set data in grid again
					}
				}
			})			
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [					
					{header: _translationMap['BeneficiaryName'], dataIndex: 'beneName', width: 150}
					,{header: _translationMap['EffDate'], dataIndex: 'deff', width: 90}
					,{header: _translationMap['Percent'], dataIndex: 'prcnt', width:80}
					,{header: _translationMap['Amount'], dataIndex: 'amt', width:80}
					,{header: _translationMap['Reported'], dataIndex: 'reported', width:75}
					,{header: _translationMap['ModDate'], dataIndex: 'modDate', width:90}
					,{header: _translationMap['ModUser'], dataIndex: 'moduser', width:100}
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
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth
				,items: [			
					_grids['allocHistory']
					,{
						xtype: 'fieldset'
						,title: _translationMap['AllocationDetails']
						,style: 'margin-top:5px;'
						,items: [
							_grids['allocDetails']
						]
					}					
				]																				
			}
		)		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton({
				 text: _translationMap['Close']	
				,handler: function(){DesktopWeb.Util.cancelScreen()}
			})
		]			
	}
}