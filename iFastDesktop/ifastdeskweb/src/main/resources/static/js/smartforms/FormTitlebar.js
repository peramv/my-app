FormTitlebar = Ext.extend(Ext.Panel, {
	
	initComponent: function()
	{
		var formDescHTML = "<span class='formDesc'>NO FORM LOADED</span>";
		if (this.initialConfig.formDetails != null)
		{
			formDescHTML = "<span class='formDesc'>" 
								+ this.initialConfig.formDetails.description + " [" + this.initialConfig.formDetails.name + "]" 
								+ "</span>"
		}	
		
		var sourceDescHTML = "";
		if (this.initialConfig.sourceDetails != null)
		{
			sourceDescHTML = "<span class='sourceDesc'>" 
								+ this.initialConfig.sourceDetails.createDateTime 
								+ " - " +  this.initialConfig.sourceDetails.businessArea
								+ "/" +  this.initialConfig.sourceDetails.workType
								+ "/" +  this.initialConfig.sourceDetails.status
								+ "</span>";
		}
		
		this.infoDisplay = new Ext.Container(
			{
				autoEl: {}
				,region: 'center'
				,id: 'formInformation'								
				,html: formDescHTML + sourceDescHTML 					
			}
		)
		
		this.formComboBox = new DesktopWeb.Controls.ComboBox(
			{
				fieldLabel: 'Alternate Forms'									
				,labelWidth: 95
				,labelStyle: 'margin-left: 10px;'							
				,width: 220
				,tabIndex: 0	
				,submitValue: false
				,emptyText: (this.initialConfig.altFormList.length == 0 ? "No alternate forms for this client" : "")	
				,disabled: this.initialConfig.altFormList.length == 0
				,store: new Ext.data.ArrayStore({
					fields: ['desc']
					,data: this.initialConfig.altFormList
				})
				,valueField: 'desc'
				,displayField: 'desc'
				,listeners: {
					select: function(fld, rec, index)
					{								
						if (index != null)
						{
							Ext.getCmp('changeFormBtn').enable();
						}
					}					
				}															
			}
		)
		
		this.changeFormBtn = new DesktopWeb.Controls.ActionButton(
			{
				text: 'Change Form'
				,id: 'changeFormBtn'
				,style: 'position:absolute; top: 0px; right: 6px;'
				,disabled: true									
			}
		)
	
		var selectorFields = [this.formComboBox, this.changeFormBtn];
		
		for (var i in DesktopWeb._SCREEN_PARAM_MAP)
		{
			selectorFields.push(new Ext.form.Hidden({name:i, value: DesktopWeb._SCREEN_PARAM_MAP[i]}));
		}
		
		this.selector = new Ext.FormPanel(
			{
				autoEl: {}
				,region: 'east'
				,id: "changeFormFrm"
				,url: DesktopWeb._SERVLET_PATH + "?cz=" + DesktopWeb._SCREEN_PARAM_MAP['cz'] + "&jobname=LoadSmartForm"
				,width: 425
				,standardSubmit: true						
				,border: false
				,style: 'padding-top:2px'																	
				,items: selectorFields					
			}
		);
			
		var config = {
			autoEl: {}		
			,height: 29
			,layout: 'border'
			,border: false
			,style: 'border-bottom: 1px solid #d0d0d0'		
			,split: false
			,items: [this.infoDisplay, this.selector]			
		}
		
		Ext.apply(this, Ext.apply(this.initialConfig, config));	
		FormTitlebar.superclass.initComponent.apply(this, arguments);
		
		this.changeFormBtn.addListener('click', this.onClickChangeForm, this);
	}
	
	,changeForm: function()
	{
		var frm = Ext.getCmp('changeFormFrm');
		var formName = frm.get(0).getValue();						
		frm.find('name', 'formName')[0].setValue(formName);											
		frm.getForm().submit();
	}
	
	,onClickChangeForm: function()
	{
		Notifications.prompt(Notifications.buildChangeFormWarningDisplay(), callbackFn);
		var self = this;
		function callbackFn(buttonId)
		{
			if (buttonId == 'ok')
			{
				self.changeForm();
			}
		}
	}	
}); 

