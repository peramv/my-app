/*********************************************************************************************
 * @file	ClassSetup_TradeDayCtrls.Controller.js	
 * @author	Rod Walker
 * @desc	Controller file for Trade Day Controls screen, part of Class Setup flow
 *********************************************************************************************/
/*
 *  History : 
 *
 *  27 Dec 2013 G. Thawornwachirakun P0181067 CHG0035028 T54651
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *   4 May 2015 WutiPong P0181067,CHG0039560,T80662,
 *              Default the Redemption Cut-Off Time to empty instead of '0000'. 
 *              This prevents the Redemption is always cut-off in non-PF environment.
 *
 *	21 May 2015 Winnie Cheng P0241128 T80810
 *			   - Added one field "Redemption Notice Period". 
 *
 *	 8 Jan 2018	Sreejith A P0274727 P0274727-1
 *			   - Added purchase payment lead days and
 *				  different settlement currency fields
 *
 *	23 Jan 2018	Sreejith A P0274733 P0274733-156
 *			   - Added MFR payment lead days
 *
 *	22 Mar 2018 Sreejith.A P0274727 P0274727-88
 *			   - T+0 Project P0274727 changes revert from 18.3
 *  
 *	12 Jun 2018 Sreejith.A P0277704 P0277704-17
 *			- T+0 Project put back reverted changes for trade control and settle date control
 * 	
 * 	11 Jan 2018 Umamahesh P0277997 P0277997-126
 *			- Trade Day Delay field will be accepting negative values
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _addMode = null;
	var _screenId = "TradeDayCtrls";
	var _screenIndex = null;
	var _initDataXML = null;
	var _screenDefListXML = null;
	var _existingClassDataXML = null;
	var _updatedClassDataXML = null;	
	var _changeFlag = false;
	var _perfFeeFlag = false;
	
	
	// PRIVATE METHODS ****************************************
	function setHeader()
	{
		var fundCode = null;
		var classCode = null;
		if (_addMode)
		{
			fundCode = IFDS.Xml.getNodeValue(_updatedClassDataXML, '//fundCode');
			classCode = IFDS.Xml.getNodeValue(_updatedClassDataXML, '//classCode');			
			if (classCode == "")
			{
				classCode = "*" + _translationMap['New'].toUpperCase() + "*";
			}
			else 
			{
				classCode = "*" + classCode + "*";
			}
		}
		else
		{
			fundCode = IFDS.Xml.getNodeValue(_existingClassDataXML, 'fundCode');
			classCode = IFDS.Xml.getNodeValue(_existingClassDataXML, 'classCode');	
		}
		
		var screenLabel = IFDS.Xml.getNodeValue(_screenDefListXML, 'Screen[id = "' + _screenId + '"]/label')
		_resources.header.setText(screenLabel + ' - ' + _translationMap['Fund'] + ': ' + fundCode + ', ' + _translationMap['Class'] + ': ' + classCode);
	}
	
	function populateBreadCrumbList()
	{
		var screenDefNodes = IFDS.Xml.getNodes(_screenDefListXML, 'Screen');
				
		for (var i = 0; i < screenDefNodes.length; i++)
		{
			var id = IFDS.Xml.getNodeValue(screenDefNodes[i], 'id');			
			_resources.breadCrumbList.addItem(id, IFDS.Xml.getNodeValue(screenDefNodes[i], 'label'));
			
			if (id == _screenId)
			{
				_screenIndex = i;
			}							
		}		
		
		if (_addMode)
		{
			_resources.breadCrumbList.disableAll();
			for (var i = 0; i <= _screenIndex; i++)
			{	
				 var id = IFDS.Xml.getNodeValue(screenDefNodes[i], 'id') 
				_resources.breadCrumbList.enableItem(id);										
			}
		}
		else
		{						
			_resources.breadCrumbList.enableAll();
		}
		_resources.breadCrumbList.setActiveItem(_screenId);
	}
	
	function displayScreenButtons()
	{
		if (_addMode)
		{			
			var screenDefNodes = IFDS.Xml.getNodes(_screenDefListXML, 'Screen');
			if (_screenIndex != 0)
			{
				//not the first
				Ext.getCmp('prevBtn').enable();
			}
			
			if (_screenIndex < screenDefNodes.length - 1)
			{				
				Ext.getCmp('nextBtn').setText(_translationMap['Next']);
			}
			else
			{
				Ext.getCmp('nextBtn').setText(_translationMap['Summary']);
			}
			Ext.getCmp('prevBtn').show();
			Ext.getCmp('cancelBtn').show();
			Ext.getCmp('nextBtn').show();			
		}
		else
		{
			Ext.getCmp('summaryBtn').show();
		}
	}
	
	function populateDropdowns()
	{
		_resources.fields['cutOffDays']['pur']['dayType'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'DayTypes']"));				
		_resources.fields['cutOffDays']['red']['dayType'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'DayTypes']"));
		_resources.fields['cutOffDays']['exchIn']['dayType'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'DayTypes']"));
		_resources.fields['cutOffDays']['exchOut']['dayType'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'DayTypes']"));
		_resources.fields['purchase']['purchasePmtLdDays']['AmountDayType'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'DayTypes']"));
		_resources.fields['purchase']['purchasePmtLdDays']['UnitDayType'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'DayTypes']"));
		_resources.fields['purchase']['diffSettleCurr']['AmountDayType'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'DayTypes']"));
		_resources.fields['purchase']['diffSettleCurr']['UnitDayType'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'DayTypes']"));
		_resources.fields['pymtLeadDays']['dayType'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'DayTypes']"));
		_resources.fields['mfrPymtLeadDays']['dayType'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'DayTypes']"));
		_resources.fields['tradeDayDelay']['dayType'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'DayTypes']"));
	}	
	
	function populateScreen()
	{
		var tradeDayCtrlsXML = IFDS.Xml.getNode(_updatedClassDataXML, 'TradeDayControls');
		
		var cutOffDaysXML = IFDS.Xml.getNode(tradeDayCtrlsXML, 'CutOffDays');
		setInitialFieldValue(_resources.fields['cutOffDays']['pur']['numDays'], IFDS.Xml.getNodeValue(cutOffDaysXML, 'Purchase/numDays'));		
		setInitialFieldValue(_resources.fields['cutOffDays']['pur']['dayType'], IFDS.Xml.getNodeValue(cutOffDaysXML, 'Purchase/dayType')); 		
		setInitialFieldValue(_resources.fields['cutOffDays']['red']['numDays'], IFDS.Xml.getNodeValue(cutOffDaysXML, 'Redemption/numDays'));		
		setInitialFieldValue(_resources.fields['cutOffDays']['red']['dayType'], IFDS.Xml.getNodeValue(cutOffDaysXML, 'Redemption/dayType'));
		setInitialFieldValue(_resources.fields['cutOffDays']['exchIn']['numDays'], IFDS.Xml.getNodeValue(cutOffDaysXML, 'ExchangeIn/numDays'));		
		setInitialFieldValue(_resources.fields['cutOffDays']['exchIn']['dayType'], IFDS.Xml.getNodeValue(cutOffDaysXML, 'ExchangeIn/dayType'));
		setInitialFieldValue(_resources.fields['cutOffDays']['exchOut']['numDays'], IFDS.Xml.getNodeValue(cutOffDaysXML, 'ExchangeOut/numDays'));		
		setInitialFieldValue(_resources.fields['cutOffDays']['exchOut']['dayType'], IFDS.Xml.getNodeValue(cutOffDaysXML, 'ExchangeOut/dayType'));		
		
		if (!_perfFeeFlag)
		{
			_resources.fields['cutOffDays']['red']['cutOffTime'].reset();
			Ext.getCmp('cutOffHeaderCompFld').setWidth(200);
			Ext.getCmp('cutOffRedCompFld').setWidth(200);

		}else{
			var redCutOffTime = IFDS.Xml.getNodeValue(cutOffDaysXML, 'Redemption/cutOffTime');
			
			if (redCutOffTime != '')
			{
				String.prototype.splice = function( idx, rem, s ) { return (this.slice(0,idx) + s + this.slice(idx + Math.abs(rem))); }; 
				redCutOffTime = redCutOffTime.splice(2, 0, ':');
				_resources.fields['cutOffDays']['red']['cutOffTime'].setValue(redCutOffTime);
			}else{
				_resources.fields['cutOffDays']['red']['cutOffTime'].reset();
			}
		}
		setInitialFieldValue(_resources.fields['pymtLeadDays']['numDays'], IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'pymtLeadDays'));
		setInitialFieldValue(_resources.fields['pymtLeadDays']['dayType'], 'B');
		
		setInitialFieldValue(_resources.fields['mfrPymtLeadDays']['numDays'], IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'mfrPymtLeadDays'));
		setInitialFieldValue(_resources.fields['mfrPymtLeadDays']['dayType'], 'B');
		
		setPurchaseFieldValues(_resources.fields['purchase']['purchasePmtLdDays'], IFDS.Xml.getNode(tradeDayCtrlsXML, 'PurchaseDays/PurPymtLeadDays'));
		setPurchaseFieldValues(_resources.fields['purchase']['diffSettleCurr'], IFDS.Xml.getNode(tradeDayCtrlsXML, 'PurchaseDays/DiffSettleCurr'));


		setInitialFieldValue(_resources.fields['tradeDayDelay']['numDays'], IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'TradeDayDelay/numDays'));
		setInitialFieldValue(_resources.fields['tradeDayDelay']['dayType'], IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'TradeDayDelay/dayType'));

		for (var i in _resources.fields)
		{			
			if (i != 'cutOffDays' && i !="purchase" && i != "tradeDayDelay" && i !="pymtLeadDays" && i !="mfrPymtLeadDays")
			{
				if (_resources.fields[i] instanceof DesktopWeb.ScreenResources.DateField)
					setInitialFieldValue(_resources.fields[i], DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(tradeDayCtrlsXML, i)));
				else
					setInitialFieldValue(_resources.fields[i], IFDS.Xml.getNodeValue(tradeDayCtrlsXML, i));
			}

		}
		
		/**
		 ** DISABLE AND HIDE FIELDS SECTION
		 **/
		_resources.fields['lastDivdDate'].disableField();
		_resources.fields['lastCrysDate'].disableField();
		_resources.fields['redNoticePeriod'].disableField();
		
		var redNotiePeriod = IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'redNoticePeriod'); //Populate data
		if (redNotiePeriod != null) {
			_resources.fields['redNoticePeriod'].setValue(redNotiePeriod);
		}
		else {
			_resources.fields['redNoticePeriod'].setValue('0');
		}

		if (!_perfFeeFlag)
		{
			_resources.fields['cutOffDays']['red']['cutOffTime'].hide();
			_resources.fields['lastCrysDate'].hide();
		}
		if (IFDS.Xml.getNodeValue(_initDataXML, 'Controls/tfrApplicable') == 'yes')
		{
			_resources.fields['lastTFRDate'].enableField();
		}else{
			_resources.fields['lastTFRDate'].disableField();
		}
		
		function setInitialFieldValue(fld, val)
		{			
			if (val != "") {		
				fld.setValue(val);
			} else {
				fld.reset();
			}	
		}
		
		function setPurchaseFieldValues(fld, values) {	
			if(_addMode) {
				fld['AmountType'].setValue(true);
				fld['AmountDays'].hide();
				fld['AmountDays'].setValue('');
				fld['AmountDaysLabel'].hide();
				fld['AmountDayType'].hide();
				fld['AmountDayType'].setValue('');
				fld['UnitDaysLabel'].setValue('');
			}
			
			if (values != undefined) {		
				fld['UnitDays'].setValue(IFDS.Xml.getNodeValue(values, 'unitDays'));
				fld['AmountDays'].setValue(IFDS.Xml.getNodeValue(values, 'amountDays'));
				fld['UnitDayType'].setValue(IFDS.Xml.getNodeValue(values, 'unitDayType'));
				fld['AmountDayType'].setValue(IFDS.Xml.getNodeValue(values, 'amountDayType'));
				var amtTypVal =  IFDS.Xml.getNodeValue(values, 'amountType');
				if (amtTypVal=='*') {
					fld['AmountType'].setValue(true);
					fld['AmountDays'].hide();
					fld['AmountDays'].setValue('');
					fld['AmountDaysLabel'].hide();
					fld['AmountDayType'].hide();
					fld['AmountDayType'].setValue('');
					fld['UnitDaysLabel'].setValue('');
				} else {
					fld['AmountType'].setValue(false);
					fld['AmountDays'].show();
					fld['AmountDayType'].show();
					fld['AmountDaysLabel'].show();
					fld['UnitDaysLabel'].setValue(_translationMap['UnitDays']);
				}
			}	
		}
	}
	
	function addChangeHandlers()
	{		
		for (var i in _resources.fields)
		{
			if (i != "cutOffDays" && i !="purchase" && i !="mfrPymtLeadDays" && i !="pymtLeadDays" && i != "tradeDayDelay")
			{
				addHandler(_resources.fields[i]);
			}									
		}
		
		addHandler(_resources.fields['cutOffDays']['pur']['numDays']);		
		addHandler(_resources.fields['cutOffDays']['pur']['dayType']); 		
		addHandler(_resources.fields['cutOffDays']['red']['numDays']);		
		addHandler(_resources.fields['cutOffDays']['red']['dayType']);
		addHandler(_resources.fields['cutOffDays']['exchIn']['numDays']);		
		addHandler(_resources.fields['cutOffDays']['exchIn']['dayType']);
		addHandler(_resources.fields['cutOffDays']['exchOut']['numDays']);		
		addHandler(_resources.fields['cutOffDays']['exchOut']['dayType']);
		
		addHandler(_resources.fields['cutOffDays']['red']['cutOffTime']);
		_resources.fields['cutOffDays']['red']['cutOffTime'].addListener('change', function(fld, newVal, oldVal){handleChangedTimeField(fld, newVal)});

		addHandler(_resources.fields['pymtLeadDays']['numDays']);
		addHandler(_resources.fields['pymtLeadDays']['dayType']);
		_resources.fields['pymtLeadDays']['numDays'].addListener('change', function(fld, newVal, oldVal){validateDayField(fld, newVal.toString())});
		
		addHandler(_resources.fields['mfrPymtLeadDays']['numDays']);
		addHandler(_resources.fields['mfrPymtLeadDays']['dayType']);
		_resources.fields['mfrPymtLeadDays']['numDays'].addListener('change', function(fld, newVal, oldVal){validateDayField(fld, newVal.toString())});

		addHandler(_resources.fields['tradeDayDelay']['numDays']);
		addHandler(_resources.fields['tradeDayDelay']['dayType']);
		_resources.fields['tradeDayDelay']['numDays'].addListener('change', function(fld, newVal, oldVal){validateDayField(fld, newVal.toString())});
		
		addHandler(_resources.fields['purchase']['purchasePmtLdDays']['UnitDayType']);
		addHandler(_resources.fields['purchase']['purchasePmtLdDays']['AmountDayType']);
		addHandler(_resources.fields['purchase']['purchasePmtLdDays']['UnitDays']);
		addHandler(_resources.fields['purchase']['purchasePmtLdDays']['AmountDays']);
		_resources.fields['purchase']['purchasePmtLdDays']['UnitDays'].addListener('change',
				function(fld, newVal, oldVal){
					validateDayField(fld, Math.abs(newVal).toString());
					_resources.fields['purchase']['purchasePmtLdDays']['AmountDays'].clearInvalid();
					_resources.fields['purchase']['purchasePmtLdDays']['UnitDayType'].clearInvalid();
					_resources.fields['purchase']['purchasePmtLdDays']['AmountDayType'].clearInvalid();
					});
		_resources.fields['purchase']['purchasePmtLdDays']['AmountDays'].addListener('change',
				function(fld, newVal, oldVal){
					validateDayField(fld, Math.abs(newVal).toString());
					_resources.fields['purchase']['purchasePmtLdDays']['UnitDays'].clearInvalid();
					_resources.fields['purchase']['purchasePmtLdDays']['AmountDayType'].clearInvalid();
					_resources.fields['purchase']['purchasePmtLdDays']['UnitDayType'].clearInvalid();
					});
		
		addHandler(_resources.fields['purchase']['diffSettleCurr']['UnitDayType']);
		addHandler(_resources.fields['purchase']['diffSettleCurr']['AmountDayType']);
		addHandler(_resources.fields['purchase']['diffSettleCurr']['UnitDays']);
		addHandler(_resources.fields['purchase']['diffSettleCurr']['AmountDays']);
		_resources.fields['purchase']['diffSettleCurr']['UnitDays'].addListener('change',
				function(fld, newVal, oldVal){
					validateDayField(fld, Math.abs(newVal).toString());
					_resources.fields['purchase']['diffSettleCurr']['AmountDays'].clearInvalid();
					_resources.fields['purchase']['diffSettleCurr']['AmountDayType'].clearInvalid();
					_resources.fields['purchase']['diffSettleCurr']['UnitDayType'].clearInvalid();
				});
		_resources.fields['purchase']['diffSettleCurr']['AmountDays'].addListener('change',
				function(fld, newVal, oldVal){
					validateDayField(fld, Math.abs(newVal).toString());
					_resources.fields['purchase']['diffSettleCurr']['UnitDays'].clearInvalid();
					_resources.fields['purchase']['diffSettleCurr']['AmountDayType'].clearInvalid();
					_resources.fields['purchase']['diffSettleCurr']['UnitDayType'].clearInvalid();
				});
		
		function addHandler(fld)
		{
			if (fld instanceof Ext.form.Checkbox)
			{
				fld.addListener('check', function(){setChangeFlag()})
			}
			else if (fld instanceof DesktopWeb.Controls.ComboBox)
			{
				fld.addListener('select', function(){setChangeFlag()})
			}
			else
			{
				fld.addListener('change', function(){setChangeFlag()})
			}
		}		
	}
	
	function setChangeFlag()
	{
		_changeFlag = true;
		Ext.getCmp('resetBtn').enable();
		Ext.getCmp('saveBtn').enable();
	}
	
	function clearChangeFlag()
	{
		_changeFlag = false;
		Ext.getCmp('resetBtn').disable();
		Ext.getCmp('saveBtn').disable();
	}
	
	function handleChangedTimeField(fld, val)
	{
		if (fld.isValid() && val.length > 0)
		{
			if (val.indexOf(':') > -1)
			{
				if (val.length == 4)
				{
					val = '0' + val;
				}
			}else{
				if (val.length == 3)
				{
					val = '0' + val;
				}
				String.prototype.splice = function( idx, rem, s ) { return (this.slice(0,idx) + s + this.slice(idx + Math.abs(rem))); }; 
				val = val.splice(2, 0, ':');
			}
			fld.setValue(val);
		}
	}

	function updateXML()
	{
		var tradeDayCtrlsXML = IFDS.Xml.getNode(_updatedClassDataXML, 'TradeDayControls');
		
		var xmlWriteFn = null; 
		if (_addMode)
		{
			writeNewValueToXML('runMode', _self.ADD);			
			xmlWriteFn = writeNewValueToXML;
		}
		else
		{
			writeNewValueToXML('runMode', _self.MOD);
			xmlWriteFn = writeUpdatedValueToXML;
		}
		
		for (var i in _resources.fields)
		{			
			if (i != 'cutOffDays' && i != 'purchase' && i!='pymtLeadDays' && i !="mfrPymtLeadDays" && i != 'tradeDayDelay' && i != 'lastCrysDate')
			{
				if (_resources.fields[i].getValue() instanceof Date)
				{
					xmlWriteFn(i, _resources.fields[i].getSMVDateString());
				}
				else
				{
					xmlWriteFn(i, _resources.fields[i].getValue());
				}					
			}
		}
		xmlWriteFn('pymtLeadDays', 
			_resources.fields['pymtLeadDays']['numDays'].getValue());
		xmlWriteFn('mfrPymtLeadDays', 
				_resources.fields['mfrPymtLeadDays']['numDays'].getRawValue());
		xmlWriteFn('numDays', 
			_resources.fields['cutOffDays']['pur']['numDays'].getValue(), 
			IFDS.Xml.getNode(tradeDayCtrlsXML, 'CutOffDays/Purchase'));
		xmlWriteFn('dayType', 
			_resources.fields['cutOffDays']['pur']['dayType'].getValue(), 
			IFDS.Xml.getNode(tradeDayCtrlsXML, 'CutOffDays/Purchase'));
		xmlWriteFn('numDays', 
			_resources.fields['cutOffDays']['red']['numDays'].getValue(), 
			IFDS.Xml.getNode(tradeDayCtrlsXML, 'CutOffDays/Redemption'));
		xmlWriteFn('dayType', 
			_resources.fields['cutOffDays']['red']['dayType'].getValue(), 
			IFDS.Xml.getNode(tradeDayCtrlsXML, 'CutOffDays/Redemption'));
		xmlWriteFn('cutOffTime', 
			_resources.fields['cutOffDays']['red']['cutOffTime'].getValue().replace(':', ''), 
			IFDS.Xml.getNode(tradeDayCtrlsXML, 'CutOffDays/Redemption'));
		xmlWriteFn('numDays', 
			_resources.fields['cutOffDays']['exchIn']['numDays'].getValue(), 
			IFDS.Xml.getNode(tradeDayCtrlsXML, 'CutOffDays/ExchangeIn'));
		xmlWriteFn('dayType', 
			_resources.fields['cutOffDays']['exchIn']['dayType'].getValue(), 
			IFDS.Xml.getNode(tradeDayCtrlsXML, 'CutOffDays/ExchangeIn'));
		xmlWriteFn('numDays', 
			_resources.fields['cutOffDays']['exchOut']['numDays'].getValue(), 
			IFDS.Xml.getNode(tradeDayCtrlsXML, 'CutOffDays/ExchangeOut'));
		xmlWriteFn('dayType', 
			_resources.fields['cutOffDays']['exchOut']['dayType'].getValue(), 
			IFDS.Xml.getNode(tradeDayCtrlsXML, 'CutOffDays/ExchangeOut'));

		var purPymtLeadDaysNode = IFDS.Xml.getNode(tradeDayCtrlsXML, 'PurchaseDays/PurPymtLeadDays');
		var diffSettleCurrNode = IFDS.Xml.getNode(tradeDayCtrlsXML, 'PurchaseDays/DiffSettleCurr');
		xmlWriteFn('unitDays', 
			_resources.fields['purchase']['purchasePmtLdDays']['UnitDays'].getRawValue(),purPymtLeadDaysNode);
		xmlWriteFn('unitDayType', 
			_resources.fields['purchase']['purchasePmtLdDays']['UnitDayType'].getValue(),purPymtLeadDaysNode);
		xmlWriteFn('amountDays', 
			_resources.fields['purchase']['purchasePmtLdDays']['AmountDays'].getRawValue(),purPymtLeadDaysNode);
		xmlWriteFn('amountDayType', 
				_resources.fields['purchase']['purchasePmtLdDays']['AmountDayType'].getValue(),purPymtLeadDaysNode);
		xmlWriteFn('amountType', 
				getAmtTypVal(_resources.fields['purchase']['purchasePmtLdDays']),purPymtLeadDaysNode);
		xmlWriteFn('unitDays', 
			_resources.fields['purchase']['diffSettleCurr']['UnitDays'].getRawValue(),diffSettleCurrNode);
		xmlWriteFn('unitDayType', 
			_resources.fields['purchase']['diffSettleCurr']['UnitDayType'].getValue(),diffSettleCurrNode);
		xmlWriteFn('amountDays', 
			_resources.fields['purchase']['diffSettleCurr']['AmountDays'].getRawValue(),diffSettleCurrNode);
		xmlWriteFn('amountDayType', 
				_resources.fields['purchase']['diffSettleCurr']['AmountDayType'].getValue(),diffSettleCurrNode);
		xmlWriteFn('amountType', 
				getAmtTypVal(_resources.fields['purchase']['diffSettleCurr']),diffSettleCurrNode);


		var tradeDayDelayNode = IFDS.Xml.getNode(tradeDayCtrlsXML, 'TradeDayDelay');
		if (!tradeDayDelayNode) tradeDayDelayNode = IFDS.Xml.addSingleNode(tradeDayCtrlsXML, 'TradeDayDelay');
		xmlWriteFn('numDays', 
			_resources.fields['tradeDayDelay']['numDays'].getValue(),tradeDayDelayNode);
		xmlWriteFn('dayType', 
			_resources.fields['tradeDayDelay']['dayType'].getValue(),tradeDayDelayNode);

		if (_perfFeeFlag)
		{
			xmlWriteFn('lastCrysDate', _resources.fields['lastCrysDate'].getSMVDateString());
		}
					
		function writeUpdatedValueToXML(fldName, value, context)
		{
			context = (context == null ? tradeDayCtrlsXML : context);
			var node = IFDS.Xml.getNode(context, fldName);
			if (!node) node = IFDS.Xml.addSingleNode(context, fldName, '');
			if (IFDS.Xml.getNodeValue(node, '.') != value)
			{
				IFDS.Xml.setNodeValue(node, value);
				IFDS.Xml.addAttribute(node, "status", _self.MOD);
			}
		}
		
		function writeNewValueToXML(fldName, value, context)
		{
			context = (context == null ? tradeDayCtrlsXML : context);
			var node = IFDS.Xml.getNode(context, fldName);
			IFDS.Xml.replaceSingleNode(context, fldName, value);
		}	
		
		function getAmtTypVal(fld) {
			if(fld['AmountType'].getValue()== true) {
				return '*';
			} else {
				return '';
			}
		}
	}
	
	function validateDayField(fld, val) {
		if (Math.abs(val) > 999) {
			DesktopWeb.Util.displayError(_translationMap['DaysMoreThan3DigitsErrMsg']);
			fld.markInvalid(_translationMap['Exceeds3Digits']);
		} else if (val.length > 2 && parseInt(val) > 99) {
			DesktopWeb.Util.displayWarning(_translationMap['DaysMoreThan99WarningMsg']);
		}
	}
	
	function validateScreen()
	{
		var isValid = true;
		
		amountTypVldn(_resources.fields['purchase']['purchasePmtLdDays']);
		amountTypVldn(_resources.fields['purchase']['diffSettleCurr']);
		isValid = isValid && _resources.fields['purchase']['purchasePmtLdDays']['UnitDays'].isValid();
		isValid = isValid && _resources.fields['purchase']['purchasePmtLdDays']['AmountDays'].isValid();
		isValid = isValid && _resources.fields['purchase']['diffSettleCurr']['UnitDays'].isValid();
		isValid = isValid && _resources.fields['purchase']['diffSettleCurr']['AmountDays'].isValid();
		
		for (var i in _resources.fields)
		{	
			if (_resources.fields[i].isValid)
			{
				isValid = _resources.fields[i].isValid() && isValid;
			}								
		}
		
		var purNumDayFld = _resources.fields['cutOffDays']['pur']['numDays'];
		var purDayTypeFld = _resources.fields['cutOffDays']['pur']['dayType'];
		if (purNumDayFld.isValid() && purNumDayFld.getValue() != 0 && purDayTypeFld.getValue() == '')
		{
			isValid = false;
			purDayTypeFld.markInvalid(_translationMap['RequiredDayType']);
		}
		
		var redNumDayFld = _resources.fields['cutOffDays']['red']['numDays'];
		var redDayTypeFld = _resources.fields['cutOffDays']['red']['dayType'];
		var redCutOffTimeFld = _resources.fields['cutOffDays']['red']['cutOffTime'];
		if (redNumDayFld.isValid() && redNumDayFld.getValue() != 0)
		{
			if (redDayTypeFld.getValue() == '')
			{
				isValid = false;
				redDayTypeFld.markInvalid(_translationMap['RequiredDayType']);
			}
			
			if (_perfFeeFlag && redDayTypeFld.isValid() && redCutOffTimeFld.getValue() == '')
			{
				isValid = false;
				redCutOffTimeFld.markInvalid(_translationMap['RequiredRedemptionCutOffTime']);
			}
		}

		var exInNumDayFld = _resources.fields['cutOffDays']['exchIn']['numDays'];
		var exInDayTypeFld = _resources.fields['cutOffDays']['exchIn']['dayType'];
		if (exInNumDayFld.isValid() && exInNumDayFld.getValue() != 0 && exInDayTypeFld.getValue() == '')
		{
			isValid = false;
			exInDayTypeFld.markInvalid(_translationMap['RequiredDayType']);
		}
		
		var exOutNumDayFld = _resources.fields['cutOffDays']['exchOut']['numDays'];
		var exOutDayTypeFld = _resources.fields['cutOffDays']['exchOut']['dayType'];
		if (exOutNumDayFld.isValid() && exOutNumDayFld.getValue() != 0 && exOutDayTypeFld.getValue() == '')
		{
			isValid = false;
			exOutDayTypeFld.markInvalid(_translationMap['RequiredDayType']);
		}
		
		isValid = Ext.getCmp('cutOffPurCompFld').isValid() && isValid;
		isValid = Ext.getCmp('cutOffRedCompFld').isValid() && isValid;
		isValid = Ext.getCmp('cutOffExInCompFld').isValid() && isValid;
		isValid = Ext.getCmp('cutOffExOutCompFld').isValid() && isValid;
		isValid = Ext.getCmp('pymtCompFld').isValid() && isValid;
		isValid = Ext.getCmp('trdDayDelayCompFld').isValid() && isValid;
		
		isValid = dayTypVldn(_resources.fields['purchase']['purchasePmtLdDays']) && isValid;
		isValid = dayTypVldn(_resources.fields['purchase']['diffSettleCurr']) && isValid;
		
		isValid = dayDelayVldn(_resources.fields['tradeDayDelay']['numDays']) && isValid;
		isValid = dayDelayVldn(_resources.fields['pymtLeadDays']['numDays']) && isValid;
		isValid = dayDelayVldn(_resources.fields['mfrPymtLeadDays']['numDays']) && isValid;
		isValid = dayDelayVldn(_resources.fields['purchase']['purchasePmtLdDays']['UnitDays']) && isValid;
		isValid = dayDelayVldn(_resources.fields['purchase']['purchasePmtLdDays']['AmountDays']) && isValid;
		isValid = dayDelayVldn(_resources.fields['purchase']['diffSettleCurr']['UnitDays']) && isValid;
		isValid = dayDelayVldn(_resources.fields['purchase']['diffSettleCurr']['AmountDays']) && isValid;		
		
		return isValid;
		
		function amountTypVldn(fields) {
			var amtDaysVal = fields['AmountDays'].getRawValue();
			var unitDaysVal = fields['UnitDays'].getRawValue();
			if(fields['AmountType'].getValue()== false) {
				if(unitDaysVal =="" && amtDaysVal !="") {
					fields['UnitDays'].markInvalid(_translationMap['FldRequired']);
					isValid = false;
				}
				if(amtDaysVal =="" && unitDaysVal !="") {
					fields['AmountDays'].markInvalid(_translationMap['FldRequired']);
					isValid = false;
				}
			}
		}
		
		function dayTypVldn(field) {
			if(field['UnitDays'].getValue()!='' && field['UnitDayType'].getValue()=='') {
				 field['UnitDayType'].markInvalid(_translationMap['RequiredDayType']);
				 return false;
			}
			if(field['AmountDays'].getValue()!='' && field['AmountDayType'].getValue()=='') {
				field['AmountDayType'].markInvalid(_translationMap['RequiredDayType']);
				 return false;
			}
			return true;
		}
		
		function dayDelayVldn(field) {
			if(field.getValue()!='' && Math.abs(field.getValue()) > 999) {
				 field.markInvalid(_translationMap['DaysMoreThan3DigitsErrMsg']);
				 return false;
			}
			return true;
		}		
	}
	
	function goToScreen(screenName)
	{
		var urlParams = {};
		urlParams['jobname'] = 'DisplayScreen';
		urlParams['screen'] = 'ClassSetup_' + screenName;
		urlParams['envName'] = DesktopWeb._SCREEN_PARAM_MAP['envName'];
		urlParams['ruserId'] = DesktopWeb._SCREEN_PARAM_MAP['ruserId'];
		urlParams['dateFormat'] = DesktopWeb._SCREEN_PARAM_MAP['dateFormat'];
		urlParams['dateFormatDisplay'] = DesktopWeb._SCREEN_PARAM_MAP['dateFormatDisplay'];
		urlParams['sessionId'] = DesktopWeb._SCREEN_PARAM_MAP['sessionId'];
		urlParams['prevScreen'] = _screenId;
		urlParams['locale'] = DesktopWeb._SCREEN_PARAM_MAP['locale'];
		
		if (screenName == "Search")
		{
			urlParams['createCache'] = 'true';	
		}
		else
		{
			urlParams['tidx'] = DesktopWeb._SCREEN_PARAM_MAP['tidx'];	
		}			
									
		window.location = DesktopWeb.Ajax.buildURL(urlParams);
	}
		
	// PUBLIC ITEMS *************************************
	return {
		ADD: 'a', MOD: 'm', DEL: 'd'		
						
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			DesktopWeb.Ajax.doRetrieveCache(['InitData', 'ScreenDefList', 'ExistingClassData', 'UpdatedClassData'], responseHandler, _translationMap['ProcMsg_Loading'])
			 								
			function responseHandler(responseXML)
			{
				_initDataXML = IFDS.Xml.getNode(responseXML, 'InitData/*');
				_screenDefListXML = IFDS.Xml.getNode(responseXML, 'ScreenDefList/*');	
				_existingClassDataXML = IFDS.Xml.getNode(responseXML, 'ExistingClassData/*');				
				_updatedClassDataXML = IFDS.Xml.getNode(responseXML, 'UpdatedClassData/data');
				
				if (_initDataXML == null || _screenDefListXML == null || _updatedClassDataXML == null)
				{
					throw new Error("Error retrieving cached data");
				}				
								
				_addMode = (_existingClassDataXML == null);								
					
				if (!_addMode)
				{												
					if (!IFDS.Xml.getNode(_updatedClassDataXML, 'TradeDayControls'))
					{										
						IFDS.Xml.appendNode(_updatedClassDataXML, 
							IFDS.Xml.cloneDocument(IFDS.Xml.getNode(_existingClassDataXML, 'TradeDayControls')));
					}
				}
				
				var feeConfigNode = (_updatedClassDataXML && IFDS.Xml.getNode(_updatedClassDataXML, 'FeeConfiguration') ? 
				IFDS.Xml.getNode(_updatedClassDataXML,'FeeConfiguration') : 
				IFDS.Xml.getNode(_existingClassDataXML,'FeeConfiguration'));
				_perfFeeFlag = (IFDS.Xml.getNodeValue(feeConfigNode, 'perfFeeFlag') == 'yes');
				
				setHeader();
				populateBreadCrumbList();
				displayScreenButtons();
				populateDropdowns();
				addChangeHandlers();				
				populateScreen();
				clearChangeFlag();						
			}
		}
	
		,onAmountTypeChange : function(value,fld) {
			_changeFlag = true;
			Ext.getCmp('resetBtn').enable();
			Ext.getCmp('saveBtn').enable();
			if(value){
				fld['AmountDays'].hide();
				fld['UnitDays'].clearInvalid();
				fld['AmountDaysLabel'].hide();
				fld['AmountDayType'].hide();
				fld['UnitDaysLabel'].setValue('');
				fld['AmountDays'].setValue('');
				fld['AmountDayType'].setValue('');
			} else {
				fld['AmountDays'].show();
				fld['AmountDaysLabel'].show();
				fld['UnitDaysLabel'].setValue(_translationMap['UnitDays']);
				fld['AmountDayType'].show();
			}
		}
		
		,changeScreen: function(screenName)		
		{
			if (screenName != _screenId)
			{			
				if (_changeFlag)
				{
					DesktopWeb.Util.displayDiscardPrompt(callback)
				}
				else
				{
					goToScreen(screenName)
				}
			}
			
			function callback(discard)
			{
				if (discard)
				{
					goToScreen(screenName);
				}
			}
		}
		
		,previous: function()		
		{
			var screenDefNodes = IFDS.Xml.getNodes(_screenDefListXML, 'Screen');
			goToScreen(IFDS.Xml.getNodeValue(screenDefNodes[_screenIndex - 1], 'id'));	
		}
		
		,next: function()		
		{
			if (validateScreen())
			{
				if (_changeFlag)
				{		
					updateXML();
					DesktopWeb.Ajax.doUpdateCache({UpdatedClassData: _updatedClassDataXML}, callback, _translationMap['ProcMsg_Saving']);
				}
				else
				{
					callback();
				}
			}						
			
			function callback()
			{
				clearChangeFlag();
				var screenDefNodes = IFDS.Xml.getNodes(_screenDefListXML, 'Screen');
				if (_screenIndex < screenDefNodes.length - 1)
				{				
					goToScreen(IFDS.Xml.getNodeValue(screenDefNodes[_screenIndex + 1], 'id'));
				}
				else
				{
					goToScreen('Summary');
				}	
			}	
		}
		
		,reset: function()
		{
			DesktopWeb.Util.displayDiscardPrompt(callback);
			
			function callback(discard)
			{
				if (discard)
				{
					populateScreen();
					clearChangeFlag();
				}
			}
		}
		
		,save: function()
		{			
			if (validateScreen())
			{		
				updateXML();					
				DesktopWeb.Ajax.doUpdateCache({UpdatedClassData: _updatedClassDataXML}, callback, _translationMap['Saving']);
			}
			
			function callback()
			{
				clearChangeFlag();	
			}			
		}	
		
		,cancel: function()
		{
			DesktopWeb.Util.displayDiscardPrompt(callback);
			
			function callback(discard)
			{
				if (discard)
				{
					goToScreen('Search');
				}
			}
		}
	}	
}	