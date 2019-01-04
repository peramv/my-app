var FormItems = {};

FormItems.Util = {
	
	OPT_SMF_CTRL_PROP: 'optional'
	
	,REQD_SMF_CTRL_PROP: 'required'
	
	,checkRequiredProperties: function(givenProps, completePropsList)
	{		
		var missingProps = [];
				
		for (var i in completePropsList)
		{
			if (completePropsList[i] == FormItems.Util.REQD_SMF_CTRL_PROP
				&& (givenProps[i] == null || givenProps[i] == ""))
			{
				missingProps.push(i);								
			}	
		}		
		
		return missingProps;
	}
	
	,parseCustomListeners: function(customListeners)
	{
		var formItemListeners = {};		
		var eventArray = customListeners.split("|");
		for (var i = 0; i < eventArray.length; i++)
		{
			var name_code = eventArray[i].split(":");
			formItemListeners[name_code[0]] = name_code[1];
		}
		
		return formItemListeners;
	}
			
	,showControlError: function(control, text)
	{
		control.markInvalid(text);	
	}
	
	,getControlPagePosition: function(control)
	{
		var pos = [];
		var control_top = (isNaN(parseInt(control.getResizeEl().dom.style.top)) ? 0 : parseInt(control.getResizeEl().dom.style.top))
		var control_left = (isNaN(parseInt(control.getResizeEl().dom.style.left)) ? 0 : parseInt(control.getResizeEl().dom.style.left))
		
		var section_top = (isNaN(parseInt(control.ownerCt.getResizeEl().dom.style.top)) ? 0 : parseInt(control.ownerCt.getResizeEl().dom.style.top))
		var section_left = (isNaN(parseInt(control.ownerCt.getResizeEl().dom.style.left)) ? 0 : parseInt(control.ownerCt.getResizeEl().dom.style.left))
		
		pos[0] = control_left + section_left;	
		pos[1] = control_top + section_top;
		return pos;
	}
	
	,getContainerSection: function(control)
	{
		return control.ownerCt;
	}
	
	,runFormItemListener: function(control, eventName)
	{			
		try{
			eval(control.formItemListeners[eventName])
		}
		catch(e){
			throw new Error("Form item listener error: " + e.description);
		}
	}
	
	,toggleControlVisible: function(control, makeVisible)
	{		
		if (makeVisible)
		{			
			control.show();
		}
		else
		{
			control.hide();			
		}		
	}
};


// Section class
FormItems.Section = Ext.extend( Ext.Container, {
		
	layout: 'absolute'		
	,x: 0
	,style: 'border: 0px solid red'					
		
	,initComponent: function()
	{	
		this.controlsByTabIndex = [];		
		FormItems.Section.superclass.initComponent.apply(this, arguments);			
	}
	
	,onRender: function(ct, position)
	{
		FormItems.Section.superclass.onRender.call(this, ct, position);
		
		this.controlsByTabIndex = this.findBy(function(item){
			return item.tabIndex && item.dataMapping != null && item.dataMapping != "" }
		);
				
		this.controlsByTabIndex.sort(function(item1, item2){
			return item1.tabIndex - item2.tabIndex}
		);
	}
	
	,add: function(ctrl)
	{
		FormItems.Section.superclass.add.call(this, ctrl);				
	}
	
	,focus: function()
	{	
		for( var i = 0; i < this.controlsByTabIndex.length; i++)
		{
			if (this.controlsByTabIndex[i].isVisible() && !this.controlsByTabIndex[i].disabled)
			{
				this.controlsByTabIndex[i].focus();
				return this.controlsByTabIndex[i];
			}
		}
		return null;		
	}	
});


//**************** SMARTFORM CONTROLS *********************** 

//TextField
FormItems.TextField = Ext.extend( DesktopWeb.Controls.TextField, {
		
	hideLabel: true
	,msgTarget: 'side'	
	,cls: 'FormItem'
	,hideMode: 'visibility'	
		
	,initComponent: function()
	{
		this.x = this.initialConfig.left;
		this.y = this.initialConfig.top;			
				
		this.dataStoreNode = null;		
		this.tabIndex = this.initialConfig.tabIndex;
		this.maskRe = (this.initialConfig.mask ? new RegExp(this.initialConfig.mask) : null);
		
		if (this.maskRe != null)
		{		
			this.validator = function(val){
				if (val == "" || this.maskRe.test(val))
				{
					return true;
				}
				else
				{
					return "Invalid value"
				} 
			}
		}
		
		this.formItemListeners = null;
		if (this.initialConfig.customListeners != null)
		{
			this.formItemListeners = FormItems.Util.parseCustomListeners(this.initialConfig.customListeners);			
		}												
		
		this.dataStoreNode = SmartFormsApp.DataStore.getNode(this.initialConfig.dataMapping);
		if (this.dataStoreNode == null)
		{
			throw new Error("Invalid dataMapping - " + this.initialConfig.dataMapping);								
		}
											
		this.dataStoreNode.addListener('updated', function(node){this.setValue(node.getValue())},this);			
		this.dataStoreNode.addListener('failedvalidation', function(error){FormItems.Util.showControlError(this, error.text);}, this);
		
		this.emptyText = this.dataStoreNode.apiReference.description;						
		
		FormItems.TextField.superclass.initComponent.apply(this, arguments);
		
		this.addListener('change', this.onChange, this);							
	}
	
	,onRender: function(ct, position)
	{
		FormItems.TextField.superclass.onRender.call(this, ct, position);
		if (this.dataStoreNode)
		{
			this.setRawValue(this.dataStoreNode.getValue());
		}
		
		if (this.formItemListeners && this.formItemListeners['render'])
		{
			FormItems.Util.runFormItemListener(this, 'render');
		}
	}
	
	,onChange: function(fld, newValue, oldValue)
	{		
		if (this.dataStoreNode)
		{		
			this.dataStoreNode.setValue(newValue.toUpperCase());
		}
		
		if (this.formItemListeners && this.formItemListeners['change'])
		{					
			FormItems.Util.runFormItemListener(this, 'change');
		}
	}
	
	,getPagePosition: function()
	{
		return FormItems.Util.getControlPagePosition(this);
	}		
});

FormItems.TextField.SmartFormProperties = {
	controlType: FormItems.Util.REQD_SMF_CTRL_PROP
	,dataMapping: FormItems.Util.REQD_SMF_CTRL_PROP
	,top: FormItems.Util.REQD_SMF_CTRL_PROP
	,left: FormItems.Util.REQD_SMF_CTRL_PROP
	,width: FormItems.Util.REQD_SMF_CTRL_PROP
	,tabIndex: FormItems.Util.REQD_SMF_CTRL_PROP
	,mask: FormItems.Util.OPT_SMF_CTRL_PROP
	,customListeners: FormItems.Util.OPT_SMF_CTRL_PROP
}


//Hidden Field 
FormItems.HiddenField = Ext.extend( DesktopWeb.Controls.TextField, {
		
	hideLabel: true	
		
	,initComponent: function()
	{	
		this.dataStoreNode = null;		
		this.tabIndex = this.initialConfig.tabIndex;				
		FormItems.HiddenField.superclass.initComponent.apply(this, arguments);		
	}
	
	,onRender: function(ct, position)
	{
		FormItems.HiddenField.superclass.onRender.call(this, ct, position);
		
		this.dataStoreNode = SmartFormsApp.DataStore.getNode(this.initialConfig.dataMapping);
		if (this.dataStoreNode == null)
		{
			throw new Error("Invalid dataMapping - " + this.initialConfig.dataMapping);
		}
			
		if (this.initialConfig.value)
		{
			this.dataStoreNode.setValue(this.initialConfig.value);
		}						
				
		this.hide();		
	}
});

FormItems.HiddenField.SmartFormProperties = {
	controlType: FormItems.Util.REQD_SMF_CTRL_PROP
	,dataMapping: FormItems.Util.REQD_SMF_CTRL_PROP	
	,value: FormItems.Util.REQD_SMF_CTRL_PROP	
}


//API Combobox class
FormItems.APIComboBox = Ext.extend( DesktopWeb.Controls.APIComboBox, {
		
	hideLabel: true	
	,triggerClass: 'ComboboxTrigger'
	,msgTarget: 'title'
	,cls: 'FormItem'
	,resizable: true
	,hideMode: 'visibility'	
		
	,initComponent: function()
	{
		this.x = this.initialConfig.left;
		this.y = this.initialConfig.top - 2;			
					
		this.dataStoreNode = null;		
		this.validator = this.validateField;	
		this.tabIndex = this.initialConfig.tabIndex;
		this.listWidth = this.initialConfig.listWidth;
		
		this.formItemListeners = null;
		if (this.initialConfig.customListeners != null)
		{
			this.formItemListeners = FormItems.Util.parseCustomListeners(this.initialConfig.customListeners);			
		}
		
		this.dataStoreNode = SmartFormsApp.DataStore.getNode(this.initialConfig.dataMapping);		
		if (this.dataStoreNode == null)
		{
			throw new Error("Invalid dataMapping - " + this.initialConfig.dataMapping);
		}	
		
		if (this.dataStoreNode.apiReference.dataType != 'listValue')
		{
			throw new Error("Invalid dataMapping - " + this.dataStoreNode.apiReference.description + " does not have list associated");
		}
		
		this.emptyText = this.dataStoreNode.apiReference.description;
		
		this.dataStoreNode.addListener('updated', function(node){this.setValue(node.getValue())}, this);
		this.dataStoreNode.addListener('failedvalidation', function(error){FormItems.Util.showControlError(this, error.text);}, this);		
		
		if (this.initialConfig.dropdownMasking)
		{			
			this.tpl = '<tpl for="."><div class="x-combo-list-item">' + this.initialConfig.dropdownMasking + '</div></tpl>'
		}
		
		if (this.initialConfig.displayItem)
		{
			this.displayField = this.initialConfig.displayItem;
		}
		
		FormItems.APIComboBox.superclass.initComponent.apply(this, arguments);		
				
		this.addListener('change', this.onChange, this);		
		
		SmartFormsApp.addListener('run', this.onRun, this);		
	}
	
	,onRender: function(ct, position)
	{				
		FormItems.APIComboBox.superclass.onRender.call(this, ct, position);
		if (this.dataStoreNode)
		{
			this.setRawValue(this.dataStoreNode.getValue());
		}
		
		if (this.formItemListeners && this.formItemListeners['render'])
		{
			FormItems.Util.runFormItemListener(this, 'render');
		}
	}
	
	,onRun: function()
	{
		if (this.dataStoreNode)
		{	
			var listXML = IFDS.Xml.getNode(SmartFormsApp.initViewXML, "//List[ListValues/listName = '" + this.dataStoreNode.apiReference.listName + "']");
			if (listXML)
			{		
				this.getStore().loadData(listXML);
				if (this.getValue())
				{				
					this.setValue(this.getValue());
				}
			}
		}		
	}
	
	,onChange: function(fld, newValue, oldValue)
	{
		if ((this.allowBlankOption && this.allowBlankOption.toLowerCase() == 'false') && newValue == "")
		{
			this.setValue(oldValue);	
		}
		else
		{
			if (this.dataStoreNode)
			{		
				this.dataStoreNode.setValue(newValue);
			}
			
			if (this.formItemListeners && this.formItemListeners['change'])
			{
				FormItems.Util.runFormItemListener(this, 'change');
			}
		}
	}
	
	,getPagePosition: function()
	{
		return FormItems.Util.getControlPagePosition(this);
	}
});

FormItems.APIComboBox.SmartFormProperties = {
	controlType: FormItems.Util.REQD_SMF_CTRL_PROP
	,dataMapping: FormItems.Util.REQD_SMF_CTRL_PROP	
	,top: FormItems.Util.REQD_SMF_CTRL_PROP
	,left: FormItems.Util.REQD_SMF_CTRL_PROP
	,width: FormItems.Util.REQD_SMF_CTRL_PROP
	,tabIndex: FormItems.Util.REQD_SMF_CTRL_PROP
	,customListeners: FormItems.Util.OPT_SMF_CTRL_PROP
	,listWidth: FormItems.Util.OPT_SMF_CTRL_PROP
	,displayItem: FormItems.Util.OPT_SMF_CTRL_PROP
	,dropdownMasking: FormItems.Util.OPT_SMF_CTRL_PROP
	,allowBlankOption: FormItems.Util.OPT_SMF_CTRL_PROP
}


//DateField class
FormItems.DateField = Ext.extend( DesktopWeb.Controls.DateField, {
	
	hideLabel: true
	,msgTarget: 'title'
	,cls: 'FormItem'
	,format: 'd/m/Y'
	,altFormats: 'Ymd'
	,hideMode: 'visibility'	
		
	,initComponent: function()
	{		
		this.y = this.initialConfig.top - 2;
		this.x = this.initialConfig.left
		this.tabIndex = this.initialConfig.tabIndex;					
						
		this.dataStoreNode = null;
		this.validator = this.validateField;
		
		this.formItemListeners = null;
		if (this.initialConfig.customListeners != null)
		{
			this.formItemListeners = FormItems.Util.parseCustomListeners(this.initialConfig.customListeners);			
		}	
				
		this.dataStoreNode = SmartFormsApp.DataStore.getNode(this.initialConfig.dataMapping);
		if (this.dataStoreNode == null)
		{
			throw new Error("Invalid dataMapping - " + this.initialConfig.dataMapping);
		}
		this.emptyText = this.dataStoreNode.apiReference.description;	
		this.dataStoreNode.addListener('updated', function(node){this.setValue(node.getValue())}, this);
		this.dataStoreNode.addListener('failedvalidation', function(error){FormItems.Util.showControlError(this, error.text);}, this);						
		
		FormItems.DateField.superclass.initComponent.apply(this, arguments);
		
		this.addListener('change', this.onChange, this);	
	}
	
	,onRender: function(ct, position)
	{
		FormItems.DateField.superclass.onRender.call(this, ct, position);	
		if (this.dataStoreNode)
		{			
			this.setRawValue(this.dataStoreNode.getValue());			
		}	
		
		if (this.formItemListeners && this.formItemListeners['render'])
		{
			FormItems.Util.runFormItemListener(this, 'render');
		}
	}
	
	,onChange: function(fld, newValue, oldValue)
	{
		if (this.dataStoreNode)
		{				
			this.dataStoreNode.setValue(DesktopWeb.Util.getDateString(newValue, 'ymd'));
		}
		
		if (this.formItemListeners && this.formItemListeners['change'])
		{
			FormItems.Util.runFormItemListener(this, 'change');
		}
	}
	
	,getPagePosition: function()
	{
		return FormItems.Util.getControlPagePosition(this);
	}
});

FormItems.DateField.SmartFormProperties = {
	controlType: FormItems.Util.REQD_SMF_CTRL_PROP
	,dataMapping: FormItems.Util.REQD_SMF_CTRL_PROP	
	,top: FormItems.Util.REQD_SMF_CTRL_PROP
	,left: FormItems.Util.REQD_SMF_CTRL_PROP
	,width: FormItems.Util.REQD_SMF_CTRL_PROP
	,tabIndex: FormItems.Util.REQD_SMF_CTRL_PROP
	,customListeners: FormItems.Util.OPT_SMF_CTRL_PROP	
}


// Checkbox class
FormItems.Checkbox = Ext.extend( DesktopWeb.Controls.Checkbox, {
		
	hideLabel: true
	,hideMode: 'visibility'		
		
	,initComponent: function()
	{				
		this.y = this.initialConfig.top - 7;
		this.x = this.initialConfig.left - 3;
		
		this.formItemListeners = null;
		if (this.initialConfig.customListeners != null)
		{
			this.formItemListeners = FormItems.Util.parseCustomListeners(this.initialConfig.customListeners);			
		}
		
		this.dataStoreNode = null;
		this.tabIndex = this.initialConfig.tabIndex;			
		FormItems.Checkbox.superclass.initComponent.apply(this, arguments);
		
		this.addListener('check', this.onCheck, this);
	}
	
	,onRender: function(ct, position)
	{
		FormItems.Checkbox.superclass.onRender.call(this, ct, position);
		if (this.initialConfig.dataMapping)
		{				
			this.dataStoreNode = SmartFormsApp.DataStore.getNode(this.initialConfig.dataMapping);
			if (this.dataStoreNode == null)
			{
				throw new Error("Invalid dataMapping - " + this.initialConfig.dataMapping);
			}	
			this.dataStoreNode.addListener('updated', function(node){this.setValue((node.getValue()) && (node.getValue().toLowerCase() == 'y'))}, this);			
		}
		else
		{
			FormItems.Util.setToUnmappedControl(this);
		}
		
		if (this.formItemListeners && this.formItemListeners['render'])
		{
			FormItems.Util.runFormItemListener(this, 'render');
		}
	}
	
	,onCheck: function(chkbox, checked)
	{
		if (this.dataStoreNode)
		{
			if (checked)
			{
				this.dataStoreNode.setValue('y');	
			}		
			else
			{
				this.dataStoreNode.setValue('n');
			}			
		}
		
		if (this.formItemListeners && this.formItemListeners['change'])
		{
			FormItems.Util.runFormItemListener(this, 'change');
		}
	}
	
	,getPagePosition: function()
	{
		return FormItems.Util.getControlPagePosition(this);
	}
});

FormItems.Checkbox.SmartFormProperties = {
	controlType: FormItems.Util.REQD_SMF_CTRL_PROP
	,dataMapping: FormItems.Util.REQD_SMF_CTRL_PROP	
	,top: FormItems.Util.REQD_SMF_CTRL_PROP
	,left: FormItems.Util.REQD_SMF_CTRL_PROP	
	,tabIndex: FormItems.Util.REQD_SMF_CTRL_PROP
	,customListeners: FormItems.Util.OPT_SMF_CTRL_PROP	
}


// Radio button class
FormItems.Radio = Ext.extend( DesktopWeb.Controls.Radio, {
		
	hideLabel: true
	,hideMode: 'visibility'			
		
	,initComponent: function()
	{
		this.y = this.initialConfig.top - 7;
		this.x = this.initialConfig.left - 3;
		this.inputValue = this.initialConfig.apiValue;
		
		this.formItemListeners = null;
		if (this.initialConfig.customListeners != null)
		{
			this.formItemListeners = FormItems.Util.parseCustomListeners(this.initialConfig.customListeners);			
		}
				
		this.dataStoreNode = null;
		this.tabIndex = this.initialConfig.tabIndex;
		// cannot have "[" in radio button names, hence the following text replacement
		this.name = (this.initialConfig.dataMapping ? this.initialConfig.dataMapping.replace(/\[/g, ":").replace(/\]/g, "") : "");
		
		if (this.initialConfig.apiValue)
		{
			this.apiValue = this.initialConfig.apiValue; 
			this.inputValue = this.initialConfig.apiValue;
		}
						
		FormItems.Radio.superclass.initComponent.apply(this, arguments);
		
		this.addListener('check', this.onCheck, this);
	}
	
	,onRender: function(ct, position)
	{
		FormItems.Radio.superclass.onRender.call(this, ct, position);
						
		this.dataStoreNode = SmartFormsApp.DataStore.getNode(this.initialConfig.dataMapping);
		if (this.dataStoreNode == null)
		{
			throw new Error("Invalid dataMapping - " + this.initialConfig.dataMapping);
		}
		
		if (this.initialConfig.defaultChecked)
		{
			this.setValue(true);
		}
			
		this.dataStoreNode.addListener('updated', 
			function(node){
				if (node.getValue())
				{
					this.setValue(node.getValue());
				}
				else
				{						
					this.el.dom.checked = false;
				}
			}, this);		
		
		if (this.formItemListeners && this.formItemListeners['render'])
		{
			FormItems.Util.runFormItemListener(this, 'render');
		}		
	}
	
	,onCheck: function(chkbox, checked)
	{		
		if (this.dataStoreNode)
		{			
			if (checked)
			{
				this.dataStoreNode.setValue(this.apiValue);
			}							
		}
		
		if (this.formItemListeners && this.formItemListeners['change'])
		{
			FormItems.Util.runFormItemListener(this, 'change');
		}
	}
	
	,getPagePosition: function()
	{
		return FormItems.Util.getControlPagePosition(this);
	}
});

FormItems.Radio.SmartFormProperties = {
	controlType: FormItems.Util.REQD_SMF_CTRL_PROP
	,dataMapping: FormItems.Util.REQD_SMF_CTRL_PROP	
	,top: FormItems.Util.REQD_SMF_CTRL_PROP
	,left: FormItems.Util.REQD_SMF_CTRL_PROP	
	,tabIndex: FormItems.Util.REQD_SMF_CTRL_PROP
	,apiValue: FormItems.Util.REQD_SMF_CTRL_PROP	
	,customListeners: FormItems.Util.OPT_SMF_CTRL_PROP
	,defaultValue: FormItems.Util.OPT_SMF_CTRL_PROP	
}					


//SuggestField
FormItems.SuggestField = Ext.extend( DesktopWeb.Controls.SuggestField, {
		
	hideLabel: true		
	,msgTarget: 'title'
	,cls: 'FormItem Suggest'
	,hideMode: 'visibility'
		
	,initComponent: function()
	{
		this.x = this.initialConfig.left;
		this.y = this.initialConfig.top - 2;
		this.fields = this.initialConfig.fields.split(",");
				
		this.dataStoreNode = null;
		this.validator = this.validateField;
		this.tabIndex = this.initialConfig.tabIndex;
		this.listWidth = this.initialConfig.listWidth;		
				
		this.forceSelection = (this.initialConfig.forceSelection == undefined ? true : false);
		
		if (this.initialConfig.additionalSearchParams)
		{
			this.addtlSearchParams = [];
			var params = this.initialConfig.additionalSearchParams.split(",");
			for (var i = 0 ; i < params.length; i++)
			{
				var name_mapping = params[i].split(":");				
				this.addtlSearchParams[i] = {
					name: name_mapping[0] 
					,valueFn: function(path){return (function(){return SmartFormsApp.DataStore.getNodeValue(path)})}(name_mapping[1])
				};			
			}			
		}
		
		this.formItemListeners = null;
		if (this.initialConfig.customListeners != null)
		{
			this.formItemListeners = FormItems.Util.parseCustomListeners(this.initialConfig.customListeners);			
		}
				
		this.dataStoreNode = SmartFormsApp.DataStore.getNode(this.initialConfig.dataMapping);
		if (this.dataStoreNode == null)
		{
			throw new Error("Invalid dataMapping - " + this.initialConfig.dataMapping);
		}	
		this.dataStoreNode.addListener('updated', function(node){this.setValue(node.getValue())}, this);
		this.dataStoreNode.addListener('failedvalidation', function(error){FormItems.Util.showControlError(this, error.text);}, this);
		this.emptyText = this.dataStoreNode.apiReference.description;			
						
		FormItems.SuggestField.superclass.initComponent.apply(this, arguments);
		
		this.addListener('change', this.onChange, this);
	}
	
	,onRender: function(ct, position)
	{
		FormItems.SuggestField.superclass.onRender.call(this, ct, position);		
		
		if (this.formItemListeners && this.formItemListeners['render'])
		{
			FormItems.Util.runFormItemListener(this, 'render');
		}
	}
	
	,onChange: function(fld, newValue, oldValue)
	{			
		if (this.dataStoreNode)
		{		
			this.dataStoreNode.setValue(newValue);
		}
		
		if (this.formItemListeners && this.formItemListeners['change'])
		{
			FormItems.Util.runFormItemListener(this, 'change');
		}
		
		if (!this.forceSelection && this.selectedRecord == null)
		{
			Notifications.prompt("You have not selected an existing record.<br/><br/>Are you sure you want to create a new one?", callbackFn);
			var self = this;
			function callbackFn(buttonId)
			{
				if (buttonId != 'ok')
				{
					self.reset();
				}
			}
		}
	}
	
	,getPagePosition: function()
	{
		return FormItems.Util.getControlPagePosition(this);
	}
});

FormItems.SuggestField.SmartFormProperties = {
	controlType: FormItems.Util.REQD_SMF_CTRL_PROP
	,dataMapping: FormItems.Util.REQD_SMF_CTRL_PROP	
	,top: FormItems.Util.REQD_SMF_CTRL_PROP
	,left: FormItems.Util.REQD_SMF_CTRL_PROP
	,width: FormItems.Util.REQD_SMF_CTRL_PROP	
	,tabIndex: FormItems.Util.REQD_SMF_CTRL_PROP
	,fields: FormItems.Util.REQD_SMF_CTRL_PROP
	,valueField: FormItems.Util.REQD_SMF_CTRL_PROP	
	,customListeners: FormItems.Util.OPT_SMF_CTRL_PROP
	,listWidth: FormItems.Util.OPT_SMF_CTRL_PROP
	,additionalSearchParams: FormItems.Util.OPT_SMF_CTRL_PROP
	,forceSelection: FormItems.Util.OPT_SMF_CTRL_PROP
}				


// Verify Combobox
FormItems.VerifyCombobox = Ext.extend( DesktopWeb.Controls.ComboBox, {
		
	hideLabel: true	
	,triggerClass: 'ComboboxTrigger'
	,msgTarget: 'title'
	,cls: 'FormItem'
	,resizable: true
	,valueField: 'value'
	,displayField: 'desc'
	,hideMode: 'visibility'	
		
	,initComponent: function()
	{
		this.x = this.initialConfig.left;
		this.y = this.initialConfig.top;
		
		var options = this.initialConfig.verifyOptions.split('|');
		this.verifyOptions = [];
		for (var i = 0; i < options.length; i++)
		{
			this.verifyOptions.push(options[i].split(":"));
		}				  		
										
		this.tabIndex = this.initialConfig.tabIndex;
		this.listWidth = this.initialConfig.listWidth;
		
		this.formItemListeners = null;
		if (this.initialConfig.customListeners != null)
		{
			this.formItemListeners = FormItems.Util.parseCustomListeners(this.initialConfig.customListeners);			
		}
						
		this.dataStoreNode = {};
		this.dataStoreNode.apiReference = {}
		this.dataStoreNode.apiReference.description = this.initialConfig.description;
		this.dataStoreNode.isAncestor = function(){return false;}
		this.emptyText = this.initialConfig.description;
		
		this.store = new Ext.data.ArrayStore({
			fields: ["value", "desc"]
			,data: this.verifyOptions	
		})
		
		FormItems.VerifyCombobox.superclass.initComponent.apply(this, arguments);
		
		this.addListener('change', this.onChange, this);			
	}
	
	,onRender: function(ct, position)
	{				
		FormItems.VerifyCombobox.superclass.onRender.call(this, ct, position);
		
		if (this.formItemListeners && this.formItemListeners['render'])
		{
			FormItems.Util.runFormItemListener(this, 'render');
		}
	}
	
	,onChange: function(fld, newValue, oldValue)
	{	
		if (this.formItemListeners && this.formItemListeners['change'])
		{
			FormItems.Util.runFormItemListener(this, 'change');
		}
	}
	
	,getPagePosition: function()
	{
		return FormItems.Util.getControlPagePosition(this);
	}
	
	,disableField: function()
	{
		this.setReadOnly(true);
		Ext.getCmp(this.id).addClass('DesktopWeb-Disabled-Field');				
	}
	
	,enableField: function()
	{
		this.setReadOnly(false);						
		Ext.getCmp(this.id).removeClass('DesktopWeb-Disabled-Field');
	}
});

FormItems.VerifyCombobox.SmartFormProperties = {
	controlType: FormItems.Util.REQD_SMF_CTRL_PROP	
	,top: FormItems.Util.REQD_SMF_CTRL_PROP
	,left: FormItems.Util.REQD_SMF_CTRL_PROP
	,width: FormItems.Util.REQD_SMF_CTRL_PROP	
	,tabIndex: FormItems.Util.REQD_SMF_CTRL_PROP
	,description: FormItems.Util.REQD_SMF_CTRL_PROP
	,verifyOptions: FormItems.Util.REQD_SMF_CTRL_PROP	
};	


//Number Field
FormItems.NumberField = Ext.extend( DesktopWeb.Controls.NumberField, {
		
	hideLabel: true
	,msgTarget: 'side'	
	,cls: 'FormItem'
	,hideMode: 'visibility'	
		
	,initComponent: function()
	{
		this.x = this.initialConfig.left;
		this.y = this.initialConfig.top;			
		this.dataStoreNode = null;		
		this.tabIndex = this.initialConfig.tabIndex;
		
		this.formItemListeners = null;
		if (this.initialConfig.customListeners != null)
		{
			this.formItemListeners = FormItems.Util.parseCustomListeners(this.initialConfig.customListeners);			
		}										
		
		this.dataStoreNode = SmartFormsApp.DataStore.getNode(this.initialConfig.dataMapping);
		if (this.dataStoreNode == null)
		{
			throw new Error("Invalid dataMapping - " + this.initialConfig.dataMapping);								
		}
											
		this.dataStoreNode.addListener('updated', function(node){this.setValue(node.getValue())},this);			
		this.dataStoreNode.addListener('failedvalidation', function(error){FormItems.Util.showControlError(this, error.text);}, this);
		
		this.emptyText = this.dataStoreNode.apiReference.description;
		this.decimalPrecision = (this.initialConfig.decimalPrecision != null ?  this.initialConfig.decimalPrecision : 2);						
		
		FormItems.NumberField.superclass.initComponent.apply(this, arguments);
		
		this.addListener('change', this.onChange, this);				
	}
	
	,onRender: function(ct, position)
	{
		FormItems.NumberField.superclass.onRender.call(this, ct, position);
		if (this.dataStoreNode)
		{
			this.setRawValue(this.dataStoreNode.getValue());
		}
		
		if (this.formItemListeners && this.formItemListeners['render'])
		{
			FormItems.Util.runFormItemListener(this, 'render');
		}
	}
	
	,onChange: function(fld, newValue, oldValue)
	{		
		if (this.dataStoreNode)
		{		
			this.dataStoreNode.setValue(newValue);
		}
		
		if (this.formItemListeners && this.formItemListeners['change'])
		{
			FormItems.Util.runFormItemListener(this, 'change');
		}
	}
	
	,getPagePosition: function()
	{
		return FormItems.Util.getControlPagePosition(this);
	}		
});

FormItems.NumberField.SmartFormProperties = {
	controlType: FormItems.Util.REQD_SMF_CTRL_PROP
	,dataMapping: FormItems.Util.REQD_SMF_CTRL_PROP	
	,top: FormItems.Util.REQD_SMF_CTRL_PROP
	,left: FormItems.Util.REQD_SMF_CTRL_PROP
	,width: FormItems.Util.REQD_SMF_CTRL_PROP	
	,tabIndex: FormItems.Util.REQD_SMF_CTRL_PROP
	,decimalPrecision: FormItems.Util.OPT_SMF_CTRL_PROP		
};

// Indicator Checkbox class
FormItems.IndicatorCheckbox = Ext.extend( DesktopWeb.Controls.Checkbox, {
		
	hideLabel: true
	,hideMode: 'visibility'		
		
	,initComponent: function()
	{				
		this.y = this.initialConfig.top - 7;
		this.x = this.initialConfig.left - 3;
		
		this.formItemListeners = null;
		if (this.initialConfig.customListeners != null)
		{
			this.formItemListeners = FormItems.Util.parseCustomListeners(this.initialConfig.customListeners);			
		}
				
		this.tabIndex = this.initialConfig.tabIndex;			
		FormItems.Checkbox.superclass.initComponent.apply(this, arguments);
		this.addListener('check', this.onCheck, this);
	}
	
	,onRender: function(ct, position)
	{
		FormItems.Checkbox.superclass.onRender.call(this, ct, position);
		
		if (this.formItemListeners && this.formItemListeners['render'])
		{
			FormItems.Util.runFormItemListener(this, 'render');
		}
	}
	
	,onCheck: function(chkbox, checked)
	{
		if (this.formItemListeners && this.formItemListeners['change'])
		{
			FormItems.Util.runFormItemListener(this, 'change');
		}
	}
	
	,getPagePosition: function()
	{
		return FormItems.Util.getControlPagePosition(this);
	}
});

FormItems.IndicatorCheckbox.SmartFormProperties = {
	controlType: FormItems.Util.REQD_SMF_CTRL_PROP
	,top: FormItems.Util.REQD_SMF_CTRL_PROP
	,left: FormItems.Util.REQD_SMF_CTRL_PROP	
	,tabIndex: FormItems.Util.REQD_SMF_CTRL_PROP
	,customListeners: FormItems.Util.OPT_SMF_CTRL_PROP	
}		