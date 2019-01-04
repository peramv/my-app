 /*********************************************************************************************
 * @file	ShrStmtSched.Resources.js
 * @author	Cherdsak Sangkasen
 * @desc	Resources JS file for Shareholder Statement Schedule screen
 *********************************************************************************************/

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	
	// content dimensions
	var _layoutHeight = 285;
	var _layoutWidth = 615;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// **** fields ****
	var _fields = {		
	}
	
	var _buttons = {
	}	
	
	// **** grids ****
	var _grids = {
		grdStmtSched: new DesktopWeb.AdvancedControls.GridPanel
		(
			{
				width: _layoutWidth
				, style: "margin-top:15px;margin-bottom:15px;"
				, autoScroll: true
				, height: 250
				, store: new Ext.data.XmlStore
				(
					{
						record: 'StmtSchedDetl'
						, fields: ['FundGroup', 
									'StatementType',
									'HardCopy']
					}				
				)
				, selModel: new Ext.grid.RowSelectionModel
				(
					{
						singleSelect: true
					}
				)
				, colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
						}
						, columns: [	
							{header: _translationMap["FundGroup"], dataIndex: 'FundGroup', width:200}
							, {header: _translationMap["StatementType"], dataIndex: 'StatementType', width:200}
							, {header: _translationMap["HardCopy"], dataIndex: 'HardCopy', width:200}
						]
					}
				)			
			}
		)
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
		
		,buttons: _buttons
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				, width: _layoutWidth
				, layout: 'form'
				, items: [
					{					
						layout: 'form'
						, items: [
							_grids['grdStmtSched']
						]
					}
				]				
			}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap["Close"]
					, handler: function(){DesktopWeb.Util.cancelScreen()}
				}
			)
		]			
	}
}