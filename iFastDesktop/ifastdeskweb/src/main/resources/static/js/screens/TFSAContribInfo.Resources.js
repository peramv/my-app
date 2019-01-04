/*********************************************************************************************
 * @file	TFSAContribInfo.Resources.js
 * @author	
 * @desc	Resources JS file for TFSA Contribution Information screen.
 *********************************************************************************************/

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 225;
	var _layoutWidth = 730;
		
	// **** grids ****
	var _grids = {
		tfsaAcctContribInfo: new DesktopWeb.AdvancedControls.GridPanel({							
			width: _layoutWidth
			,style: "margin-bottom:15px"
			,autoScroll: true							
			,height: 215		
			,autoExpandColumn: 'year'								
			,store: new Ext.data.XmlStore({						
				record:'AcctContrib'
				,fields: ['ytmContrib', 'ytmWithdrawal', 'ltdContrib', 'ltdWithdrawal', 'Deff']											
			})				
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true,sortable:false
				}
				,columns: [													
					{id: 'year', header: _translationMap['Year'], dataIndex: 'Deff'}																			
					,{header: _translationMap['YTDContrib'], dataIndex:'ytmContrib', width:150}
					,{header: _translationMap['YTDWithdrawal'], dataIndex: 'ytmWithdrawal', width:150}
					,{header: _translationMap['LTDContrib'], dataIndex:'ltdContrib', width:150}
					,{header: _translationMap['LTDWithdrawal'], dataIndex: 'ltdWithdrawal', width:150}
				]							
			})							
		})		
	}	
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight			
		
		,grids: _grids			
		
		,layout: new Ext.Container({
			height: _layoutHeight
			,width: _layoutWidth																
			,items: [
				_grids['tfsaAcctContribInfo']																	
			]				
		})
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton({		
				text: _translationMap['Close']
				,handler: function(){DesktopWeb.Util.cancelScreen()}
			})			
		]			
	}
}