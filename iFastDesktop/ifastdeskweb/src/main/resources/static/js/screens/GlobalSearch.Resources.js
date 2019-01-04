/*********************************************************************************************
 * @file	GlobalSearch.Resources.js	
 * @author	Rod Walker
 * @desc	Resources file for Global Search screen
 *********************************************************************************************/

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 400;
	var _layoutWidth = 650;	
	
	// **** buttons ****
	var _buttons = {
		searchBtn: new DesktopWeb.Controls.ActionButton({																						
			text: _translationMap['Search']
			,id: 'searchBtn'									
			,handler: function(){_controller.doSearch();}
			,style: 'position:absolute; right:125px; top:0px;'
			,disabled: true										 																			
		})		
	}
	
	// **** fields ****
	var _fields = {
		searchValue: new DesktopWeb.Controls.TextField({
			itemId: 'searchValue'
			,width: 340
			,fieldLabel: _translationMap['SearchValue']				
			,enableKeyEvents: true
			,listeners: {
				keyup: function(fld)
				{											
					if (fld.getValue().trim() != "")
					{
						_buttons['searchBtn'].enable();
					}
					else
					{
						_buttons['searchBtn'].disable();
					}
				}
				,change: function(fld)
				{											
					if (fld.getValue().trim() != "")
					{
						_buttons['searchBtn'].enable();
					}
					else
					{
						_buttons['searchBtn'].disable();
					}
				} 
				,keydown: function(fld, evt)
				{
					if (evt.getKey() == 13 && fld.getValue().trim() != "")
					{
						_controller.doSearch();
					}
				}
			}				 													
		})			
	}
	
	// **** grids ****
	var _grids = {		
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
					layout: 'form'
					,style: 'padding-left:20px; padding-bottom:10px;'																								
					,labelWidth: 90
					,items: [
						_fields['searchValue']																	
						,_buttons['searchBtn']
					]												
				}
				,new DesktopWeb.AdvancedControls.GridPanel({
					id: 'searchResultsHeader'																																		
					,height: 24																		
					,enableHdMenu: false
					,enableColumnMove: false											
					,store: new Ext.data.XmlStore({
						record: 'PossibleMatch'					
						,fields: ['displayValue','acctNum',
							'addr1', 'addr2', 'addr3', 'addr4', 'addr5', 
							'broker', 'brokerName', 'branch', 'brnName', 
							'salesRep', 'slsrepName', 'brkAct']				
					})							
					,columns: [																																															
						{header: _translationMap['Account'], width: 370, dataIndex: 'displayValue', resizable: false, fixed: true}
						,{header: _translationMap['Address'],width: 150, dataIndex: 'addr1', resizable: false, fixed: true}
						,{header: _translationMap['Broker'], width: 100, dataIndex: 'brokerName', resizable: false, fixed: true}				
					]											
				})
				,new Ext.Container({
					id: 'searchResultsContainer'
					,height: 325
					,style: 'overflow-y:scroll'																					
					,items: [
						
					]
				})					
																			
			]																				
		})		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['OK']
				,handler: function(){
					if (_controller.getCurrentSelection() != null)
					{
						DesktopWeb.Util.commitScreen()
					}
					else
					{
						DesktopWeb.Util.displayError("No account has been selected");
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

DesktopWeb.ScreenResources.EnvResultsSet = Ext.extend( Ext.form.FieldSet, {
	initComponent: function()
	{
		this.addEvents({'select' : true}, {'more' : true});
					
		var templateText = '<tpl for=".">';
		templateText += '<div class="results-record">'
		for (var i = 0; i < this.initialConfig.columnModel.getColumnCount(); i++)
		{			
			templateText += '<div class="results-field x-grid3-cell-inner" ';
			var colWidth = this.initialConfig.columnModel.getColumnWidth(i);
			if (i == 0)
			{
				colWidth -= 10; 
			}
			else if (i == this.initialConfig.columnModel.getColumnCount() - 1)
			{
				colWidth -= 2;
			}
			templateText += 'style="width:' + colWidth + '">';
			templateText += '{' + this.initialConfig.columnModel.getDataIndex(i) + '}';
			templateText += '</div>';
		}
		templateText += '</div>'
		templateText += '</tpl>';
		
		this.statusText = "";
		
		this.store =  new Ext.data.XmlStore({
			record: 'PossibleMatch'					
			,fields: ['displayValue','acctNum',
				'addr1', 'addr2', 'addr3', 'addr4', 'addr5', 
				'broker', 'brokerName', 'branch', 'brnName', 
				'salesRep', 'slsrepName', 'brkAct']				
		});
		
		this.resultsView = new Ext.DataView({
			tpl: new Ext.XTemplate(templateText)
			,store: this.store
			,itemSelector: 'div.results-record'
			,singleSelect: true
			,selectedClass: 'selected-record'
			,overClass: 'over-record'			
		});
		
		this.resultsView.addListener('selectionchange', function(v, selections){
			this.fireEvent('select', this.initialConfig.envId, this.resultsView.getSelectedRecords()[0])
			}, this);
		
		this.moreBtn = new DesktopWeb.Controls.ActionButton({
			style: "float:right; margin:3px;"
			,text: 'More'
			,hidden: true			
		})
		this.moreBtn.addListener('click', function(){this.fireEvent('more', this.initialConfig.envId)}, this);
		
		var config = {
			collapsible: true
			,collapsed: true
			,disabled: true
			,listeners: {
				beforeexpand: function(){return !this.disabled}				
			}			
			,items: [
				this.resultsView
				,this.moreBtn
			]			
		};		
		Ext.apply(this, Ext.apply(this.initialConfig, config));							
		DesktopWeb.ScreenResources.EnvResultsSet.superclass.initComponent.apply(this, arguments);			
	}
	
	,onRender: function(ct, position)
	{
		DesktopWeb.ScreenResources.EnvResultsSet.superclass.onRender.call(this, ct, position);		
	}
	
	,setStatusText: function(text)
	{
		this.statusText = this.initialConfig.envId + " - " + text;
		this.setTitle(this.statusText);
	}
	
	,populate: function(matchesXML, appendResults, moreAvail)
	{							
		this.store.loadData(matchesXML, appendResults);						
		this.enable();
		
		if (moreAvail)
		{
			this.moreBtn.show();
			this.setStatusText(this.store.getTotalCount() + " result" + (this.store.getTotalCount() > 1 ? "s" : "") + " (more available)");
		}
		else
		{
			this.moreBtn.hide();
			this.setStatusText(this.store.getTotalCount() + " result" + (this.store.getTotalCount() > 1 ? "s" : ""));
		}							
	}
	
	,clearSelection: function()
	{
		this.resultsView.clearSelections(true);
	}
});