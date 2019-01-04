/*********************************************************************************************
 * @file 	DesktopWeb.Controls.js
 * @author  Rod Walker 
 * @desc	Contains DesktopWeb specific controls, extended from ExtJS widgets, 
 * 			for reuse in screens
 *********************************************************************************************/
/*
 * History : 
 *
 * 05-Mar-2014 Gomoot T. P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to reset BoxLable.
 *
 * 28-Jun-2017 Gomoot T. P0268835 CHG0050132 Order Transmission T85761
 *             - Add cleared event to SMVComboBox
 *
 * 04-Jul-2017 Gomoot T. P0268199 CHG0049877 CRM2 Compensation Report T85814 
 *             - Add cleared event to SMVComboBox
 */
 
Ext.namespace("DesktopWeb.Controls");

// Without this .hide() method on a form field will not hide the field label
Ext.layout.FormLayout.prototype.trackLabels = true;

/*********************************************************************************************
 * ScreenButton extended from Ext.Button, for use at the bottom 
 * button toolbar of a DesktopWeb screen
 *********************************************************************************************/
DesktopWeb.Controls.ScreenButton = Ext.extend( Ext.Button, {
	
	setText: function(text)
	{
		DesktopWeb.Controls.ScreenButton.superclass.setText.apply(this, 
			["<span style='font-weight:bold; font-size:13px'>" + text + "</span>"]);
	}
	
	,initComponent: function(){
		var config = {
			cls: 'ScreenBtn'
			,minWidth: 80
			,height: 26
			,itemCls: 'ScreenBtn'			
		};
		
		Ext.apply(this, Ext.apply(this.initialConfig, config));	
		DesktopWeb.Controls.ScreenButton.superclass.initComponent.apply(this, arguments);
	}
});


/*********************************************************************************************
 * ScreenButton extended from Ext.Button, for use within content of screen and popups
 *********************************************************************************************/
DesktopWeb.Controls.ActionButton = Ext.extend( Ext.Button, {
	minWidth: 60
	
	,initComponent: function()
	{			
		DesktopWeb.Controls.ActionButton.superclass.initComponent.apply(this, arguments);
	}
	
	,onRender: function(ct, position)
	{
		DesktopWeb.Controls.ActionButton.superclass.onRender.call(this, ct, position);
	}
});

Ext.override(Ext.form.Field,
	{
		setFieldLabel: function(text) 
		{
		    if (this.rendered) 
			{
		      this.el.up('.x-form-item', 10, true).child('.x-form-item-label').update(text);
		    }
		    this.fieldLabel = text;
		}
	}
);

/*********************************************************************************************
 * Override of Ext.form.TextField, so that following methods will be available 
 * in controls that extend Ext.form.TextField (ie. combox, datepicker, etc)
 *********************************************************************************************/
Ext.override(Ext.form.TextField,
	{
		// this method is now deprecated, because of the 'trackLabels=true' property added to form layout
		hideField: function()
		{
			if (this.rendered)
			{
				this.disable();
				this.hide();
				this.getEl().up('.x-form-item').setDisplayed(false); //hide label
			}
			else
			{
				this.addListener('render', function(fld){fld.hideField()});
			}
		}
		
		// this method is now deprecated, because of the 'trackLabels=true' property added to form layout
		,showField: function()
		{
			if (this.rendered)
			{
				this.enable();
				this.show();
				this.getEl().up('.x-form-item').setDisplayed(true); //show label
			}
			else
			{
				this.addListener('render', function(fld){fld.showField()});
			}
		}
		
		,disableField: function()
		{
			this.setReadOnly(true);
			Ext.getCmp(this.id).removeClass('DesktopWeb-Disabled-Field');
			Ext.getCmp(this.id).addClass('DesktopWeb-Disabled-Field');				
		}
		
		,enableField: function()
		{
			this.setReadOnly(false);						
			Ext.getCmp(this.id).removeClass('DesktopWeb-Disabled-Field');
		}
		
		,clearField: function()
		{
			this.reset();
		}
		
		,msgTarget: 'side'
		
		,initComponent: function()		
		{
			if (this.hiddenField)
			{			
				this.addListener('render', function(fld){fld.hideField()});
			}
			
			if (this.disabledField)
			{
				this.addListener('render', function(fld){fld.disableField()});
			}
		}
				
  		,setFieldLabel: function(text) 
		{
		    if (this.rendered) 
			{
		      this.el.up('.x-form-item', 10, true).child('.x-form-item-label').update(text);
		    }
		    this.fieldLabel = text;
		}		
	}
);


/*********************************************************************************************
 * Override of Ext.form.Checkbox, so that following methods will be available 
 * in controls that extend Ext.form.Checkbox (ie. checkbox, radio, etc)
 *********************************************************************************************/
Ext.override(Ext.form.Checkbox,
	{
		disableField: function()
		{
			this.disable();
							
		}
		
		,enableField: function()
		{
			this.enable();
		}
		
		,setBoxLabel: function(boxLabel){
			this.boxLabel = boxLabel;
			if(this.rendered)
			{
				if (this.wrap.child('.x-form-cb-label'))
					this.wrap.child('.x-form-cb-label').update(boxLabel);
				else
					this.wrap.createChild({tag: 'label', htmlFor: this.el.id, cls: 'x-form-cb-label', html: this.boxLabel});	
			}
		}
	}
);


/*********************************************************************************************
 * Override of Ext.form.ComboBox, so that following methods will be available 
 * in controls that extend Ext.form.ComboBox 
 *********************************************************************************************/
Ext.override(Ext.form.ComboBox,
	{
		getSelectedRecord: function()
		{				
			var store = this.getStore();
			var selectedRecord = null;			
			if (this.getValue() != "")
			{
				selectedRecord = store.getAt(store.findExact(this.valueField, this.getValue()));				
			}						
			return selectedRecord;		
		}
	}
);


/*********************************************************************************************
 * TextField extended from Ext.form.TextField
 *********************************************************************************************/
DesktopWeb.Controls.TextField = Ext.extend(Ext.form.TextField, {
	style: 'text-transform: uppercase'
	,listeners: {
		change: function(fld, newVal, oldVal)
		{
			fld.setRawValue(newVal.toUpperCase());
		}
	}
	
	,initComponent: function()
	{			
		DesktopWeb.Controls.TextField.superclass.initComponent.apply(this, arguments);
	}
	
	,onRender: function(ct, position)
	{
		DesktopWeb.Controls.TextField.superclass.onRender.call(this, ct, position);
	}	
});


/*********************************************************************************************
 * Label extended from Ext.form.Label
 *********************************************************************************************/
DesktopWeb.Controls.Label = Ext.extend(Ext.form.Label, {
	style: "position:relative; top:3px;"
	
	,hideField: function()
	{
		this.disable();
		this.hide();
		this.getEl().up('.x-form-item').setDisplayed(false); //hide label
	}
		
	,showField: function()
	{
		this.enable();
		this.show();
		this.getEl().up('.x-form-item').setDisplayed(true); //hide label
	}
	
	,setValue: function(text)
	{
		this.setText(text);
	}
	
	,getValue: function()
	{
		if (this.rendered)
		{
			return this.el.dom.innerText;
		}
		return null;
	}
	
	,reset: function()
	{
		this.setText('');
	}
	
	,initComponent: function()
	{			
		DesktopWeb.Controls.Label.superclass.initComponent.apply(this, arguments);
	}
	
	,onRender: function(ct, position)
	{
		DesktopWeb.Controls.Label.superclass.onRender.call(this, ct, position);
	}
	
	,setFieldLabel: function(text) 
	{
	    if (this.rendered) 
		{
	      this.el.up('.x-form-item', 10, true).child('.x-form-item-label').update(text);
	    }
	    this.fieldLabel = text;
	}	
});


/*********************************************************************************************
 * Basic ComboBox extended from Ext.form.ComboBox 
 *********************************************************************************************/
DesktopWeb.Controls.ComboBox = Ext.extend(Ext.form.ComboBox, {
	selectedClass: 'DesktopWeb-ComboBox-Selected'
	,typeAhead: false	
	,triggerAction: 'all'
	,mode: 'local'	
	,forceSelection: true
		
	,loadData: function(data)
	{
		this.getStore().loadData(data);
	}
	
	,initComponent: function()
	{				
		DesktopWeb.Controls.ComboBox.superclass.initComponent.apply(this, arguments);
	}
	
	,onRender: function(ct, position)
	{
		DesktopWeb.Controls.ComboBox.superclass.onRender.call(this, ct, position);
	}		
});


/*********************************************************************************************
 * Basic ComboBox extended from Ext.form.ComboBox 
 *********************************************************************************************/
DesktopWeb.Controls.YesNoComboBox = Ext.extend(DesktopWeb.Controls.ComboBox, {
	
	store: new Ext.data.ArrayStore(
		{
			idIndex: 0			
			,fields: ['code', 'value']
			,data: [['yes', DesktopWeb.Translation.getTranslation('Yes').toUpperCase()], ['no', DesktopWeb.Translation.getTranslation('No').toUpperCase()]]
		}
	)
	
	,valueField: 'code'
	,displayField: 'value'
	,width: 90
	
	,initComponent: function()
	{			
		DesktopWeb.Controls.YesNoComboBox.superclass.initComponent.apply(this, arguments);
	}
	
	,onRender: function(ct, position)
	{
		DesktopWeb.Controls.YesNoComboBox.superclass.onRender.call(this, ct, position);
	}		
});


/*********************************************************************************************
 * ComboBox extended from DesktopWeb.Controls.ComboBox, to be used with xml list 
 * provided by Smartview response (ie. <List><Element><Code><Value></Element>...</List>)
 *********************************************************************************************/
DesktopWeb.Controls.SMVComboBox = Ext.extend( DesktopWeb.Controls.ComboBox, {					
	valueField: 'code'
	,displayField: 'value'
	,showCode: false
	,tpl: '<tpl for=".">' + '<div class="x-combo-list-item">' + '{value}&nbsp;' + '</div></tpl>'
	
	,initComponent: function()
	{	
    	this.store = new Ext.data.XmlStore(
			{
				record: 'Element'
				,fields: ['code', 'value']
			}
		)
	   
        if(this.initialConfig.showCode){	   
			this.store.addListener('load'
			    ,function(aStore, records){ 
					Ext.each(records,function(item){
						if((item.get('code') != "") && (item.get('value') != "")){
							item.set('value', item.get('code') + ' - ' + item.get('value'));
						} 
					});
			    }
				, this
			); 
	    }
		
		DesktopWeb.Controls.SMVComboBox.superclass.initComponent.apply(this, arguments);
		this.addEvents({'cleared' : true});
	}
	
	,getValueDesc: function()
	{
		var record = this.findRecord(this.valueField, this.getValue());		
		return (record != null ? record.get(this.displayField) : null);
	}
	
	,onRender: function(ct, position)
	{
		DesktopWeb.Controls.SMVComboBox.superclass.onRender.call(this, ct, position);
		
		this.addListener('keyup', this.keyupHandler, this);
	}
	
	,keyupHandler: function(fld, e)
	{
		if (!!fld) {
			if (fld.getRawValue() == '' )
				this.fireEvent('cleared', fld);			
		}
	}
});


/*********************************************************************************************
 * ComboBox extended from DesktopWeb.Controls.ComboBox, to be used with xml list 
 * provided by API response (ie. <List><ListValues><listName/><listValue/><listDesc/></ListValues>...</List>)
 *********************************************************************************************/
DesktopWeb.Controls.APIComboBox = Ext.extend( DesktopWeb.Controls.ComboBox, {					
	valueField: 'listValue'
	,displayField: 'listDesc'
	
	,initComponent: function()
	{	
		this.store = new Ext.data.XmlStore(
			{
				record: 'ListValues'
				,fields: ['listValue', 'listDesc']
			}
		)	
		DesktopWeb.Controls.APIComboBox.superclass.initComponent.apply(this, arguments);
	}
	
	,onRender: function(ct, position)
	{
		DesktopWeb.Controls.APIComboBox.superclass.onRender.call(this, ct, position);
	}
});


/*********************************************************************************************
 * DateField extended from Ext.form.DateField 
 *********************************************************************************************/
DesktopWeb.Controls.DateField = Ext.extend( Ext.form.DateField, {
	
	format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb._SCREEN_PARAM_MAP['dateFormat'])
	,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb._SCREEN_PARAM_MAP['dateFormat']))
	
	,initComponent: function()
	{	
		var tempAltFormat = DesktopWeb.Util.getAltDateFormats(this.format);
		
		if (tempAltFormat != this.altFormats)
			this.altFormats = tempAltFormat;
				
		if (this.emptyText == null || this.emptyText == undefined)
			this.emptyText = DesktopWeb.Util.getDateFormatTemplate(this.format);
		
		DesktopWeb.Controls.DateField.superclass.initComponent.apply(this, arguments);		
	}
	
	,onRender: function(ct, position)
	{
		DesktopWeb.Controls.DateField.superclass.onRender.call(this, ct, position);
	}

	,getDisplayDateString: function()
	{
		var dateDisplayObj = this.getValue();
		
		if (dateDisplayObj == null || dateDisplayObj == undefined || dateDisplayObj == "")
			return "";
		else //this.getDateDisplayFormat()
			return dateDisplayObj.format(this.format).trim();
	}
	
	,getSMVDateString: function ()
	{
		var dateDisplayObj = this.getValue();
		
		if (dateDisplayObj == null || dateDisplayObj == undefined || dateDisplayObj == "")
			return "";
		else
			return dateDisplayObj.format(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb._SCREEN_PARAM_MAP['dateFormat'])).trim();
	}
});


/*********************************************************************************************
 * Checkbox extended from Ext.form.Checkbox 
 *********************************************************************************************/
DesktopWeb.Controls.Checkbox = Ext.extend( Ext.form.Checkbox, {
	
	hideLabel: true
	
	,initComponent: function()
	{		
		DesktopWeb.Controls.Checkbox.superclass.initComponent.apply(this, arguments);
	}
	
	,onRender: function(ct, position)
	{
		DesktopWeb.Controls.Checkbox.superclass.onRender.call(this, ct, position);
	}		
});


/*********************************************************************************************
 * CheckboxGroup extended from Ext.form.CheckboxGroup 
 *********************************************************************************************/
DesktopWeb.Controls.CheckboxGroup = Ext.extend( Ext.form.CheckboxGroup, {
	
	hideLabel: true
	
	,initComponent: function()
	{		
		DesktopWeb.Controls.CheckboxGroup.superclass.initComponent.apply(this, arguments);
	}
	
	,onRender: function(ct, position)
	{
		DesktopWeb.Controls.CheckboxGroup.superclass.onRender.call(this, ct, position);
	}
});


Ext.override(Ext.form.CheckboxGroup,
	{
		hideField: function()
		{
			if (this.rendered)
			{
				this.disable();
				this.hide();
				this.getEl().up('.x-form-item').setDisplayed(false); //hide label
			}
			else
			{
				this.addListener('render', function(fld){fld.hideField()});
			}
		}
		
		,showField: function()
		{
			if (this.rendered)
			{
				this.enable();
				this.show();
				this.getEl().up('.x-form-item').setDisplayed(true); //show label
			}
			else
			{
				this.addListener('render', function(fld){fld.showField()});
			}
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
		
		,getNames: function() {
			var n = [];

			this.items.each(function(item) {
			  if (item.getValue()) {
				n.push(item.getName());
			  }
			});

			return n;
		}

		,getValues: function() {
			var v = [];

			this.items.each(function(item) {
			  if (item.getValue()) {
				v.push(item.getRawValue());
			  }
			});

			return v;
		}
		
		,msgTarget: 'side'
		
		,initComponent: function()
		{
			if (this.hiddenField)
			{
				this.addListener('render', function(fld){fld.hideField()});
			}
			
			if (this.disabledField)
			{
				this.addListener('render', function(fld){fld.disableField()});
			}
		}
	}
);


/*********************************************************************************************
 * Radio extended from Ext.form.Radio 
 *********************************************************************************************/
DesktopWeb.Controls.Radio = Ext.extend( Ext.form.Radio, {
	
	hideLabel: true
	
	,initComponent: function()
	{		
		DesktopWeb.Controls.Radio.superclass.initComponent.apply(this, arguments);
	}
	
	,onRender: function(ct, position)
	{
		DesktopWeb.Controls.Radio.superclass.onRender.call(this, ct, position);
	}
});


/*********************************************************************************************
 * RadioGroup extended from Ext.form.RadioGroup 
 *********************************************************************************************/
DesktopWeb.Controls.RadioGroup = Ext.extend( Ext.form.RadioGroup, {
	
	hideLabel: true
	
	,initComponent: function()
	{		
		DesktopWeb.Controls.RadioGroup.superclass.initComponent.apply(this, arguments);
	}
	
	,onRender: function(ct, position)
	{
		DesktopWeb.Controls.RadioGroup.superclass.onRender.call(this, ct, position);
	}
});

Ext.override(Ext.form.RadioGroup,
	{
		hideField: function()
		{
			if (this.rendered)
			{
				this.disable();
				this.hide();
				this.getEl().up('.x-form-item').setDisplayed(false); //hide label
			}
			else
			{
				this.addListener('render', function(fld){fld.hideField()});
			}
		}
		
		,showField: function()
		{
			if (this.rendered)
			{
				this.enable();
				this.show();
				this.getEl().up('.x-form-item').setDisplayed(true); //show label
			}
			else
			{
				this.addListener('render', function(fld){fld.showField()});
			}
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
		
		,msgTarget: 'side'
		
		,initComponent: function()		
		{
			if (this.hiddenField)
			{			
				this.addListener('render', function(fld){fld.hideField()});
			}
			
			if (this.disabledField)
			{
				this.addListener('render', function(fld){fld.disableField()});
			}
		}
	}
);


/*********************************************************************************************
 * SuggestField extended from IFDS.SuggestField 
 *********************************************************************************************/
DesktopWeb.Controls.SuggestField = Ext.extend( IFDS.SuggestField, {
	
	urlGeneratorFn: function(){return DesktopWeb.Ajax.buildSmartviewAjaxURL(this.smartview)}
	,selectedClass: 'DesktopWeb-ComboBox-Selected'	
	,fieldSearchParam: 'searchValue'
	,resultLimitParam: 'maxRecords'
	,startRecordParam: 'startRecordNum'
	
	,statusPath: '/SmartviewResponse/status'	
	,record: 'PossibleMatch'	
	,displayField: 'displayValue'	
	,errorPath: '/SmartviewResponse/Errors/Error'	
	,nextStartRecNumPath: '/SmartviewResponse/*/nextStartRecNum'
	,style: 'text-transform: uppercase'
	,loadingText: DesktopWeb.Translation.getTranslation('Loading').toLowerCase() + "..."		
	,nextText: DesktopWeb.Translation.getTranslation('Next').toLowerCase()
	,prevText: DesktopWeb.Translation.getTranslation('Previous').toLowerCase()
	
	,initComponent: function()
	{
		var smartview = this.smartview;		
		this.requestXMLGeneratorFn =  function(suggestXML){return DesktopWeb.Ajax.buildSmartviewRequestXML(smartview, suggestXML)}		
		DesktopWeb.Controls.SuggestField.superclass.initComponent.apply(this, arguments);
	}
	
	,onRender: function(ct, position)
	{		
		DesktopWeb.Controls.SuggestField.superclass.onRender.call(this, ct, position);
	}		
});


/*********************************************************************************************
 * NumberField extended form Ext.form.NumberField
 *********************************************************************************************/
DesktopWeb.Controls.NumberField = Ext.extend(Ext.form.NumberField, {
	allowNegative: false
	
	,setValue : function(v)
	{
		if (v && v.indexOf && v.indexOf(',') != -1)
		{		
			v = v.replace(/,/g, ''); // strip commas from input value
		}						
    	v = typeof v == 'number' ? v : String(v).replace(this.decimalSeparator, ".");
	    v = isNaN(v) ? '' : String(v).replace(".", this.decimalSeparator);		
	    return Ext.form.NumberField.superclass.setValue.call(this, v);
	}
	
    ,fixPrecision : function(value)
	{
        var nan = isNaN(value);
        if(!this.allowDecimals || this.decimalPrecision == -1 || nan || !value)
		{
           return nan ? '' : value;
        }
	    return parseFloat(value).toFixed(this.decimalPrecision);
    }
	
	,initComponent: function()
	{				
		DesktopWeb.Controls.NumberField.superclass.initComponent.apply(this, arguments);
	}
	
	,onRender: function(ct, position)
	{
		DesktopWeb.Controls.NumberField.superclass.onRender.call(this, ct, position);				
	}	
});


/*********************************************************************************************
 * ColumnPlaceHolder - invisible textfield used as place holder in form/column layout
 *********************************************************************************************/
DesktopWeb.Controls.ColumnPlaceHolder = Ext.extend(Ext.form.TextField, {
	
	initComponent: function()
	{
		this.hideMode = 'visibility'
		this.hidden = true
		this.width = 5				
		DesktopWeb.Controls.ColumnPlaceHolder.superclass.initComponent.apply(this, arguments);
	}
	
	,onRender: function(ct, position)
	{
		DesktopWeb.Controls.ColumnPlaceHolder.superclass.onRender.call(this, ct, position);
	}
});