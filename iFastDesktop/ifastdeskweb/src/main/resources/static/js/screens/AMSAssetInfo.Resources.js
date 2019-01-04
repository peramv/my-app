/*********************************************************************************************
 * @file	AMSAssetInfo.Resources.js
 * @author	Siva Chandran
 * @desc	Resources JS file for AMS Asset Informstion screen
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
		shareholder: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Shareholder']	
		})	
		, account: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Account']
		})
		, name: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Name']
		})
		,searchType: new DesktopWeb.Controls.ComboBox({
			fieldLabel: 'Search Type'
			,valueField: 'code'
			,width: 100
			,displayField: 'value'
			,allowBlank: false
			,store: new Ext.data.ArrayStore({
				idIndex: 0			
				,fields: ['code', 'value']
				,data: [
					['fund', _translationMap['Fund']]
					,['asset', _translationMap['Asset']]
					,['subasset', _translationMap['SubAsset']]
				]
			})
			,listeners: {
				select: function(){
					_controller.onChangeSearchType();
				}
				,change: function(){
					_controller.onChangeSearchType();
				}
			} 
		})			
	}
	
	
	// **** grids ****
	var _grids = {
		fundInfo: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth
			,height: 125				
			,autoScroll: true
			,disableSelection: true						
			,store: new Ext.data.XmlStore({
				record: 'AssetDetl'
				,fields: ['fund','fundNm','asset','subAsst','mv','split','current','var']												
			})				
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [	
					{header: _translationMap['FundNo'], dataIndex: 'fund', width:60}
					,{id:'fundName', header: _translationMap['FundName'], dataIndex: 'fundNm', width: 175}
					,{header: _translationMap['Asset'], dataIndex: 'asset', width:80}
					,{header: _translationMap['SubAsset'], dataIndex: 'subAsst', width:80}
					,{header: _translationMap['MVC'], dataIndex: 'mv', width:75}
					,{header: _translationMap['Split'], dataIndex: 'split', width:75}
					,{header: _translationMap['Current'], dataIndex: 'current', width:75}
					,{header: _translationMap['Variance'], dataIndex: 'var', width:80}					
				]
			})
		})
		,assetInfo: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth
			,height: 125				
			,autoScroll: true
			,disableSelection: true
			,hidden: true
			,autoExpandColumn: 'asset'				
			,store: new Ext.data.XmlStore({
				record: 'AssetDetl'
				,fields: ['fund','fundNm','asset','subAsst','mv','split','current','var']												
			})				
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [						
					{id: 'asset', header: _translationMap['Asset'], dataIndex: 'asset', width:80}
					,{header: _translationMap['MVC'], dataIndex: 'subAsst', width:80}
					,{header: _translationMap['Split'], dataIndex: 'mv', width:80}
					,{header: _translationMap['Current'], dataIndex: 'split', width:80}
					,{header: _translationMap['Variance'], dataIndex: 'current', width:80}									
				]
			})
		})
		,subassetInfo: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth
			,height: 125				
			,autoScroll: true
			,disableSelection: true
			,autoExpandColumn: 'asset'
			,hidden: true				
			,store: new Ext.data.XmlStore({
				record: 'AssetDetl'
				,fields: ['fund','fundNm','asset','subAsst','mv','split','current','var']												
			})				
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [						
					{id: 'asset', header: _translationMap['Asset'], dataIndex: 'asset', width:80}
					,{header: _translationMap['SubAsset'], dataIndex: 'subAsst', width:80}
					,{header: _translationMap['MVC'], dataIndex: 'mv', width:80}
					,{header: _translationMap['Split'], dataIndex: 'split', width:80}
					,{header: _translationMap['Current'], dataIndex: 'current', width:80}
					,{header: _translationMap['Variance'], dataIndex: 'var', width:80}					
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
		
		,layout: new Ext.Container(		
			{
				height: _layoutHeight
				,width: _layoutWidth				
				,items: [	
					{
						layout: 'form'
						,style: 'padding-left: 10px'											
						,items: [							
							_fields['shareholder']
							,_fields['account']
							,_fields['name']
							,_fields['searchType']							
						]						
					}
					,_grids['fundInfo']								
					,_grids['assetInfo']
					,_grids['subassetInfo']
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
	