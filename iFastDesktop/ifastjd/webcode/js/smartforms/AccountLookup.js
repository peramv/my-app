AccountLookup = Ext.extend(Ext.Window, {
	initComponent: function(){
		
		var self = this;
		this.toolbarBtn = SmartFormsApp.Toolbar.smfButtons['lookup'];		
		
		this.lookupFld = new DesktopWeb.Controls.TextField({
			width: 300
			,fieldLabel: 'Lookup Value'				
			,enableKeyEvents: true		
			,listeners: {
				keyup: function(fld, evt)
				{											
					if (fld.getValue() != "")
					{
						self.lookupBtn.enable();
						
						if (evt.getKey() == 13)
						{
							self.doLookup(self.lookupFld.getValue());
						}
					}
				}
			}		
		});
		
		this.lookupBtn = new DesktopWeb.Controls.ActionButton({																						
			text: 'Lookup'														
			,style: 'position:absolute; right:160px; top:0px;'
			,disabled: true			
			,handler: function()
			{
				self.doLookup(self.lookupFld.getValue());
			}										 																			
		});
		
		this.lookupStatus = new Ext.form.Label({			
			width: 615			
			,style: 'font-style:italic; text-align:right; padding-top:2px; padding-right:10px'
		})
								
		this.resultsGrid = new DesktopWeb.AdvancedControls.GridPanel(
			{							
				width: 615				
				,autoScroll: true							
				,height: 150
				,style: 'padding-top: 5px;'		
				,autoExpandColumn: 'displayValue'		
				,disableSelection: true												
				,store: new Ext.data.XmlStore(
					{
						record: 'PossibleMatch'					
						,fields: ['displayValue', 'addr1', 'brkAcct']											
					}
				)
								
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
						}
						,columns: [																			
							{header: 'Account', dataIndex: 'displayValue', id:'displayValue'}
							,{header: 'Address', dataIndex: 'addr1', width: 150}
							,{header: 'Dealer Account', dataIndex: 'brkAcct', width: 95}																																											
						]							
					}
				)												
			}
		)
		
		var config = {
			title: 'Account Lookup'
			,id: 'AccountLookup'
			,width:650			
			,height: 275
			,resizable: false						
			,layout: 'fit'			
			,closable: true
			,closeAction: 'hide'
			,items: [
				{					
					layout: 'form'																											
					,labelWidth: 90
					,style: 'padding-top:10px; padding-left:10px;'					
					,border: false
					,items: [
						this.lookupFld
						,this.lookupBtn
						,this.resultsGrid
						,this.lookupStatus																				
					]												
				}								
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: 'Close'
					,handler: function(){SmartFormsApp.AccountLookup.hide()}								
				})
			]			
		};
		
		Ext.apply(this, Ext.apply(this.initialConfig, config));	
		AccountLookup.superclass.initComponent.apply(this, arguments);
		
		this.toolbarBtn.addListener('toggle', this.onToolbarToggle, this);
		this.addListener('hide', this.onHide, this);
		this.addListener('show', this.onShow, this);
		
		
	}
	
	,onRender: function(ct, position)
	{		
		AccountLookup.superclass.onRender.call(this, ct, position);
	}
	
	,onToolbarToggle: function(btn, pressed)
	{
		if (pressed)
		{
			this.show();
		}
		else
		{
			this.hide();
		}
	}
	
	,onHide: function()
	{		
		this.toolbarBtn.toggle(false);
	}
	
	,onShow: function()
	{
		this.lookupFld.setValue("");
		this.resultsGrid.clearData();
		this.lookupStatus.setText("");		
		this.toolbarBtn.toggle(true);
				
		(function(){this.lookupFld.focus()}).defer(5, this);
	}
	
	,clearResultsGridStatus: function()
	{		
		this.resultsGrid.setTitle(this.gridBaseTitle);
	}
	
	,doLookup: function(lookupStr)
	{
		var viewParamXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(viewParamXML, 'searchValue', lookupStr);
		this.lookupStatus.setText("Searching ...");						
		DesktopWeb.Ajax.doSmartviewAjax('accountSearch', {ignoreErrorCode: '199'}, viewParamXML, responseHandler); 		
		
		var self = this;				
		function responseHandler(success, responseXML)
		{							
			if (success)
			{
				if (IFDS.Xml.getNode(responseXML, '//Error'))
				{
					self.showNoResults();	
				}
				else
				{
					self.loadResults(responseXML);
				}										
			}
		}
	}
	
	,loadResults: function(responseXML)
	{
		this.resultsGrid.loadData(responseXML);
		var resultCount = this.resultsGrid.getStore().getTotalCount();		
		this.lookupStatus.setText(resultCount + " match" + (resultCount > 1 ? "es " : " ") + "returned.");
	}
	
	,showNoResults: function(responseXML)
	{		
		this.resultsGrid.clearData();
		this.lookupStatus.setText("No matches returned.");										
	}
});