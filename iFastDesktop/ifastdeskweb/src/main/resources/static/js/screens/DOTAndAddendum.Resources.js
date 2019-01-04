/*********************************************************************************************
 * @file	DOTAndAddendum.Resources.js
 * @author 	Narin Suanlamyai
 * @desc	Resources JS file for Declaration of Trust and Addendum screen.
 *
 * History
 * 06 Jun 2017 Narin Suanlamyai P0263049 NetServer Modernization
 *             Replace xsl style to ExtJS style
 *********************************************************************************************/

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 325;
	var _layoutWidth = 500;
	
	// **** fields ****
	var _fields = {}
    
	// **** grids ****
	var _grids =  {
		dotGrid : new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth - 35
			,height: 300
			,autoScroll: true
			,autoExpandColumn: 'fileType'
			,style: 'margin-top:20px;margin-left:10px'
			,store: new Ext.data.XmlStore({
				record: 'OutputAction'
				,fields: ['fileType','fileTypeDesc', 'Deff', 'userName']
				,listeners: {
					load: function(store, records)
					{
						Ext.each(records, function(record){
							record.data.Deff = DesktopWeb.Util.getDateDisplayValue(record.data.Deff);
						});
						store.fireEvent('datachanged', store); //to set data in grid again
					}
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){
						//_controller.checkModifyButton();
					}
				}
			})

			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}

				,columns: [	
					{header: _translationMap['fileType'], dataIndex: 'fileTypeDesc' ,id: 'fileType'},
					{header: _translationMap['dateOfIssue'], width: 100, dataIndex: 'Deff'},
					{header: _translationMap['Username'], width: 120, dataIndex: 'userName'}
				]
			})

			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'moreBtn'
					,text: _translationMap['More']
					,disabled: true
					,handler: function(){_controller.clickHandle_moreBtn();}
				})
			]
		})
	};	
		
		
	// **** popups ****
	var _popups = {}

	//**** buttons ****

	 return {
   		
   		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,fields: _fields
		
		,grids: _grids

		,popups: _popups
		
		,layout: new Ext.Container(
			{																							
				height: _layoutHeight
				,width: _layoutWidth
				,items: [
					{
						xtype: 'fieldset'
						,items:[
							_grids['dotGrid']
						]
					}
				]
					
			}
		)
		,screenButtons : [
			new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['Close']
					,handler: function(){
							DesktopWeb.Util.cancelScreen();
					}
				}
			)
		]	 			
	} 
	
}

