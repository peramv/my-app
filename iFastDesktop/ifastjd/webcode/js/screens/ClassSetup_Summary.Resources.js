/*********************************************************************************************
 * @file	ClassSetup_Summary.Resources.js	
 * @author	Rod Walker
 * @desc	Resources file for Summary screen, part of Class Setup flow
 *********************************************************************************************/
/*
 *  History : 
 *
 *  27 Dec 2013 G. Thawornwachirakun P0181067 CHG0035028 T54651
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *  05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 670;
	var _layoutWidth = 750;
	
	// **** buttons ****
	var _buttons = {
		expandAll: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['ExpandAll']
			,style: 'position:absolute; right:86px; top:47px; height: 15px; font-size: 8px'
			,handler: function(){
				_controller.expandAllDataPanels();
			}
		})
		
		,collapseAll: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['CollapseAll']
			,style: 'position:absolute; right:14px; top:47px'
			,handler: function(){
				_controller.collapseAllDataPanels();
			}
		})						
	}
	
	// **** fields ****
	var _fields = {
		header: new DesktopWeb.Controls.Label({													
			text: _translationMap['ClassSummary']
			,style: 'font-weight: bold; font-size: 13px; padding-bottom: 8px;'
		})
		
		,fund: new DesktopWeb.Controls.Label({															
			fieldLabel: _translationMap['Fund']
		})
		
		,fundSponsor: new DesktopWeb.Controls.Label({															
			fieldLabel: _translationMap['FundSponsor']
		})	

		,verifyStatus: new DesktopWeb.Controls.Label({															
			id: 'verifyStatus'
			,text: _translationMap['VerifyStatus']
			,style: 'font-weight: bold; font-size: 13px; padding-bottom: 8px;'
			,hidden: true
		})	
	}
	
	// **** grids ****
	var _grids = {		
	}
		
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,fields: _fields
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth								
				,items: [
					{
						layout: 'column'
						,style: "margin-bottom:10px;"
						,defaults: {labelWidth: 80}	
						,items: [
							{
								width: _layoutWidth / 2
								,layout: 'form'
								,items: [
									_fields['header']
								]
							}
							, {
								width: _layoutWidth / 2
								,layout: 'form'
								,style: 'text-align:right;padding-right:12px'
								,items: [
									_fields['verifyStatus']
								]
							}
											
						]
						
					}					
					,{
						layout: 'form'
						,columnWidth: 0.5
						,labelWidth: 120
						,style: 'padding-left:12px; padding-bottom:3px;'
						,items: [								
							_fields['fund']
							,_fields['fundSponsor']		
						]
					}																	
					,_buttons['expandAll']
					,_buttons['collapseAll']		
					,new Ext.Container({
						height: _layoutHeight - 80
						,width: _layoutWidth - 20
						,id: 'dataPanelContainer'										
						,style: 'margin-left:10px; border: 1px solid #d0d0d0; overflow-y:scroll; background:white'
						,items: [						
						]
					})					
				]																			
			}
		)

		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton({
				id: "verify"
				,text: _translationMap['Verify']
				,hidden: true
				,handler: function(){_controller.verify()}					
			})
			, new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['OK']
				,handler: function(){_controller.ok()}					
			})
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Cancel']
				,handler: function(){_controller.cancel()}					
			})
		]			
	}
}

DesktopWeb.ScreenResources.DataPanel = Ext.extend( Ext.Panel, {	
	DATETYPE : 'date'
	
	,initComponent: function(){
		this.addEvents({'edit' : true});
		
		
		this.leftGrid = new DesktopWeb.ScreenResources.DataGrid({
			columnWidth: 0.5
		}) 
		
		this.rightGrid = new DesktopWeb.ScreenResources.DataGrid({
			columnWidth: 0.5
		}) 
		
		var config = {
			bodyStyle: 'border: 1px solid #d0d0d0'							
			,collapsible: true
			,collapsed: true																			
			,tools:[
				{
			    	id:'edit'
			    	,qtip: DesktopWeb.Translation.getTranslationMap()['Edit'] + ' ' + this.initialConfig.title						   
			    	,handler: function(event, toolEl, panel){
						panel.fireEvent('edit', panel.id);
					}
				}				
			]
			,toolTemplate: new Ext.XTemplate(
				'<tpl if="id==\'edit\'">',
					'<div class="edit-link">{[this.fieldNames("Edit")]}</div>',
				'</tpl>',
				'<tpl if="id!=\'edit\'">',
					'<div class="x-tool x-tool-{id}">&#160;</div>',
				'</tpl>',
				{
					fieldNames: function(fieldName)
					{
						return DesktopWeb.Translation.getTranslationMap()[fieldName];
					}
				}
			)						
			,layout: 'form'
			,items:[
				{
					layout: 'column'
					,items:[
						this.leftGrid
						,this.rightGrid
					]
				}
			]			
		}

		Ext.apply(this, Ext.apply(this.initialConfig, config));							
		DesktopWeb.ScreenResources.DataPanel.superclass.initComponent.apply(this, arguments);
	}
	
	,hideEditLink: function(value)
	{
		this.tools[0].hidden = value;
	}
	
	,onRender: function(ct, position)
	{
		DesktopWeb.ScreenResources.DataPanel.superclass.onRender.call(this, ct, position);		
	}
	
	,addSubHeader: function(text)
	{
		this.leftGrid.addItem(text, 'data-subheader');
		this.rightGrid.addItem(text, 'data-subheader-hidden');	
	}
	
	,addField: function(label, value, status, indent, valueType)
	{			
		valueType = ((valueType == undefined || valueType == null) ? "" : valueType);
		
		var tempValue = "";
		if (typeof(value) === 'string' || value instanceof String)
		{
			tempValue = value.toLowerCase();
		
			if (tempValue == 'yes')
				value = DesktopWeb.Translation.getTranslationMap()['Yes'].toLowerCase();
			else if (tempValue == 'no')
				value = DesktopWeb.Translation.getTranslationMap()['No'].toLowerCase();
		}
			
		var grid = (this.leftGrid.getCount() == this.rightGrid.getCount() ? this.leftGrid : this.rightGrid);		
		grid.addItem(label, 'data-label' + (indent ? ' indent' : ''), value, status, valueType);
	}
	
	,addDateField: function(label, value, status, indent)
	{	
		this.addField(label, value, status, indent, this.DATETYPE);
	}

	,addFieldValue: function(value1, status1, value2, status2, valueType)
	{			
		valueType = ((valueType == undefined || valueType == null) ? "" : valueType);
		
		var tempValue = "";
		if (typeof(value2) === 'string' || value2 instanceof String)
		{
			tempValue = value2.toLowerCase();
			if (tempValue == 'yes')
				value2 = DesktopWeb.Translation.getTranslationMap()['Yes'].toLowerCase();
			else if (tempValue == 'no')
				value2 = DesktopWeb.Translation.getTranslationMap()['No'].toLowerCase();
		}
			
		var grid = (this.leftGrid.getCount() == this.rightGrid.getCount() ? this.leftGrid : this.rightGrid);		
		grid.addItem(value1, status1, value2, status2, valueType);
	}
	
	,addDateFieldValue: function(value1, status1, value2, status2)
	{		
		this.addFieldValue(value1, status1, value2, status2, this.DATETYPE);
	}
	
	,addSubField: function(label, value, status, valueType)
	{
		this.addField(label, value, status, true, valueType);
	}
	
	,addSubFieldDate: function(label, value, status)
	{
		this.addSubField(label, value, status, this.DATETYPE);
	}
	
	,addSpacer: function()
	{
		this.addField("", "");
	}
});

DesktopWeb.ScreenResources.DataGrid = Ext.extend( Ext.grid.PropertyGrid, {
	initComponent: function()
	{
		var config = {
			autoScroll: false
			,height: 1
			,disableSelection: true			
			,enableColumnResize: true
			,enableColumnHide: false
			,enableHdMenu: false
			,hideHeaders: false
			,viewConfig: {scrollOffset: 1, autoFill: true, forceFit: true}
			,listeners: {
				beforeedit: function(){return false}
				,render: function(grid){grid.getSelectionModel().lock()}
			}
			
		};		
		Ext.apply(this, Ext.apply(this.initialConfig, config));							
		DesktopWeb.ScreenResources.DataGrid.superclass.initComponent.apply(this, arguments);			
	}
	
	,onRender: function(ct, position)
	{
		this.getStore().sortInfo = undefined;
		this.colModel.getColumnById('name').sortable = false;		
		this.colModel.getColumnById('name').header = DesktopWeb.Translation.getTranslationMap()['Property'];
			
		DesktopWeb.ScreenResources.DataGrid.superclass.onRender.call(this, ct, position);		
	}
	
	,addItem: function(property, propertyClass, value, valueClass, valueType)
	{
		if (!this.getSource())
		{
			this.setSource({});
		}	
		propertyClass = (propertyClass ? propertyClass : "");
		valueClass = (valueClass ? valueClass : "");
	
		if (valueType != undefined && valueType != null && valueType.toLowerCase() == 'date')
		{
			value = DesktopWeb.Util.getDateDisplayValue(value);
		}
		
		var propertyName = "<div id='" + this.getCount() + "' class='" + propertyClass + "'>" + property + "</div>";
		this.customRenderers[propertyName] = function(val, meta, rec){
			meta.css += " " + valueClass
			return val;
		}
		this.setProperty(propertyName, value, true);				
		this.setHeight((this.getCount()* 24) + 25);		
	}
	
	,getCount: function()
	{
		return this.getStore().getCount();
	}
});