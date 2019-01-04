/*********************************************************************************************
 * @file	IFDS.SuggestField.js
 * @author  Rod Walker
 * @desc	Class for creating suggest field out of EXT JS combobox  	
 *********************************************************************************************/
/*
 * History  :  
 *		22 May 2014 N. Suanlamyai P0225140 T55105
 *					- Add arguments for 'populated' event
 *
 */

IFDS.SuggestField = Ext.extend( Ext.form.ComboBox,
	{    										
		resizable: true
		,loadingText: "loading ..."
		,nextText: "next"
		,prevText: "previous"
		,delay: 1000
		
		//request attributes 
		,urlGeneratorFn: null
		,requestXMLGeneratorFn: null
		,fieldSearchParam: null
		,resultLimitParam:null
		,resultLimit: 10
		,startRecordParam: null
		,addtlSearchParams: null
		
		//response attributes
		,statusPath: null		
		,record: null
		,fields: null
		,displayField: null
		,valueField: null
		,errorPath: null
		,rangeStartPath: null		
		,nextStartRecNumPath: null
		,forceSelection: true			
						
		,initComponent: function()
		{			
			if (!IFDS.Xml)
			{
				throw new Error('IFDS.Xml library not found');
			}						
			
			this.activeSeachObj = null;
			this.prevSearchVal = "";
			this.fieldTextBeforeKeyPress = "";		
			this.prevStartRecNum = null;			
			this.nextStartRecNum = null			
			this.store = new Ext.data.XmlStore(
				{				  
					url: 'blah', //mandatory param, but not being used here
					record: this.record,
					fields: this.fields
				}
			);
			this.selectedRecord = null;
			this.searchFactory = new IFDS.SuggestField.SearchFactory(
				{
					delay: this.delay
					,searchURL: this.urlGeneratorFn()
					,requestXMLGenerator: this.requestXMLGeneratorFn
					,suggestFld: this
				}
			);
									
			var config = {				
				triggerAction: 'all'				
				,autoSelect:false
				,mode: 'remote'		
				,typeAhead: false
				,selectOnFocus: true
				,hideTrigger: true								
				,enableKeyEvents: true
				,lazyInit: false													
			}
		
			Ext.apply(this, config);
			Ext.apply(this.initialConfig, config);
			IFDS.SuggestField.superclass.initComponent.apply(this, arguments);
			
			this.addEvents({'populated' : true}, {'cleared' : true});	
		}
		
		,onRender: function(ct, position)
		{			
			IFDS.SuggestField.superclass.onRender.call(this, ct, position);
			
			this.addListener('beforequery', function(){return false});
			this.store.addListener('load', this.loadHandler, this);
			this.addListener('keydown', this.keydownHandler, this);									
			this.addListener('keyup', this.keyupHandler, this);			
			this.addListener('select', this.selectHandler, this);
			this.addListener('expand', this.expandHandler, this);
			this.addListener('blur', this.blurHandler, this);				
			this.getEl().on('paste',  function() 
				{
					var self = this;
					
					setTimeout(function(e) {
						self.pasteHandler(self);
					}, 0);
				}, this);
			
			if (this.nextStartRecNumPath)
			{
				this.buildToolbar();
			}				
		}
		
		,blurHandler: function()
		{
			this.prevSearchVal = this.getRawValue();
			
			if (this.activeSearch) 
			{
				this.activeSearch.cancel();
				this.activeSearch = null;
			}
		}
		
		,buildToolbar: function()
		{
			var cls = 'x-combo-list';
			
			var toolbarConfig = {};
			toolbarConfig['items'] = [];
									
			var footer = this.list.createChild({
				cls: cls + '-ft'
			});
			toolbarConfig['renderTo'] = footer;
			
			if (this.rangeStartPath)
			{			
				var prevBtn = new Ext.Button({				
					text: this.prevText,		
					iconCls: "x-tbar-page-prev"
				});					
				prevBtn.addListener('click', this.clickHandler_prevBtn, this);
				toolbarConfig['prevBtn'] = prevBtn;
				toolbarConfig.items[0] = prevBtn; 				
			}
			
			toolbarConfig.items[toolbarConfig.items.length] = new Ext.Toolbar.Fill();
			
			var nextBtn = new Ext.Button({					
				text: this.nextText
				,iconAlign: 'right'
				,iconCls: "x-tbar-page-next"
			});						
			nextBtn.addListener('click', this.clickHandler_nextBtn, this);
			toolbarConfig['nextBtn'] = nextBtn;
			toolbarConfig.items[toolbarConfig.items.length] = nextBtn;								
						
			this.toolbar = new Ext.Toolbar(toolbarConfig);
			this.assetHeight += footer.getHeight();
			this.innerList.setStyle('margin-bottom', '0px');
		}
		
		,expandHandler: function()
		{
			if (this.toolbar)
			{
				this.updateToolbar();
			}						
		}
		
		,updateToolbar: function()
		{
			if (this.rangeStartPath)
			{										
				if (this.prevStartRecNum) 
				{
					this.enablePreviousBtn();
				}
				else 
				{
					this.disablePreviousBtn();
				}
			}
							
			if (this.nextStartRecNum) 
			{
				this.enableNextBtn();
			}
			else 
			{
				this.disableNextBtn();
			}
			this.toolbar.show();							
		}
		
		,selectHandler: function(fld, record)
		{			
			this.selectedRecord = record;				
			this.prevSearchStr = fld.getRawValue();			
			this.fireEvent('populated', this, this.selectedRecord);						
		}
		
		,disablePreviousBtn: function()
		{
			this.toolbar.prevBtn.disable();
		}
		
		,enablePreviousBtn: function()
		{
			this.toolbar.prevBtn.enable();
		}
		
		,disableNextBtn: function()
		{
			this.toolbar.nextBtn.disable();
		}
		
		,enableNextBtn: function()
		{
			this.toolbar.nextBtn.enable();
		}
		
		,loadHandler: function(store, records, options)
		{
			if (this.isExpanded() && this.toolbar)
			{
				this.updateToolbar();
			}
						
			if (records.length == 1)
			{							
				this.setRawValue(records[0].data[this.displayField]);				
				this.fireEvent('select', this, records[0]);				
				this.collapse();				
				//prevent default action, ie. opening dropdown
				return false;
			}
		}
		
		,keydownHandler: function(fld, e)
		{
			this.fieldTextBeforeKeyPress = fld.getRawValue();
		}
		
		,keyupHandler: function(fld, e)
		{									
			//ENTER key
			if (e.getKey() == 13)   
			{
				if (this.activeSearch)
				{
					this.activeSearch.force();		
				}
				else if (this.selectedRecord != null)
				{
					return false;
				}
				else if (this.selectedIndex == -1)
				{					
					this.expand();
				}
			}			
			else if (fld.getRawValue() != this.fieldTextBeforeKeyPress) 			
			{				
				this.selectedRecord = null;
				this.fireEvent('cleared');				
				
				var fldVal = fld.getRawValue().trim();
				if (fldVal == "" || fldVal != this.prevSearchVal)			
				{					
					if (this.activeSearch) 
					{
						this.activeSearch.cancel();
						this.activeSearch = null;
					}
					
					if (fldVal == "")
					{					
						this.collapse();	
					}
					else
					{
						this.activeSearch = this.searchFactory.createSearch(this.buildSearchParamMap(fldVal));					 							
					}
					this.prevSearchVal = fldVal;					
				}
			}
			else
			{
				return false;
			}					
		}
				
		,pasteHandler: function(fld)
		{
			var currentElementIdent = document.activeElement.id;
			var searchValue = document.getElementById(currentElementIdent).value.trim();
			
			if (searchValue != "")
			{
				if (this.activeSearch) 
				{
					this.activeSearch.cancel();
					this.activeSearch = null;
				}
				
				this.activeSearch = 
						this.searchFactory.createSearch(this.buildSearchParamMap(searchValue));
				
				this.prevSearchVal = searchValue;
			}
			else
			{
				this.collapse();
			}
		}

		,buildSearchParamMap: function(fldValue, startRecNum)
		{
			var searchParamMap = {};
			searchParamMap[this.fieldSearchParam] = fldValue;
			searchParamMap[this.resultLimitParam] = this.resultLimit;			
			searchParamMap[this.startRecordParam] = (startRecNum ? startRecNum : 1);
			
			if (this.addtlSearchParams)
			{
				for (var i = 0; i < this.addtlSearchParams.length; i++)
				{
					searchParamMap[this.addtlSearchParams[i].name] = this.addtlSearchParams[i].valueFn(); 
				}
			}
			return Ext.apply(searchParamMap);						
		}
		
		,clickHandler_nextBtn: function() 
	    { 			
			var searchParamMap = this.buildSearchParamMap(this.prevSearchVal, this.nextStartRecNum)
	      	this.activeSearch = this.searchFactory.createSearch(searchParamMap);
	     }
     
     	,clickHandler_prevBtn: function() 
	    { 
			var searchParamMap = this.buildSearchParamMap(this.prevSearchVal, this.prevStartRecNum)
	      	this.activeSearch = this.searchFactory.createSearch(searchParamMap);  
	   	}
		
		,searchCallback: function(responseXML)
		{	
			this.updateMetaData(responseXML);
			this.displayResult(responseXML);																
			this.activeSearch = null;								  
		}
		
		,updateMetaData: function(xml) 
		{
			this.nextStartRecNum = null;
			try
			{						
				this.nextStartRecNum = (this.nextStartRecNumPath != null ? 
										IFDS.Xml.getNodeValue(xml, this.nextStartRecNumPath) : null);
			}
			catch(e)
			{
				throw new Error('Error reading nextStartRecNum from suggest response - ' + e.description);
			}
			
			var rangeStart = null;				
			try
			{						
				rangeStart = (this.rangeStartPath ? IFDS.Xml.getNodeValue(xml, this.rangeStartPath) : null);;
			}
			catch(e)
			{
				throw new Error('Error reading resultRangeStart from suggest response - ' + e.description);
			}
			
			this.prevStartRecNum = null;
			if (rangeStart)
			{
				this.prevStartRecNum = (rangeStart > 1 ? Math.max(rangeStart - this.resultLimit, 1) : null);
			}
		}
		
		,displayResult: function(xml)
		{
			var success = false;
			try
			{
				success = IFDS.Xml.getNodeValue(xml, this.statusPath).toLowerCase() == 'success';						
			}
			catch(e)
			{
				throw new Error('Error reading status from suggest response - ' + e.description);
			}
			
			if (success)
			{					
				this.store.loadData(xml);
			}
			else
			{
				var errorDesc = "";
				try
				{
					errorDesc = IFDS.Xml.getNodeValue(xml, this.errorPath + '/text');
				}
				catch(e)
				{
					throw new Error('Error reading error details from suggest response - ' + e.description);
				}
				this.displayMsg(errorDesc);
			}			
		}
		
		,showLoading: function()
		{			
			this.displayMsg(this.loadingText);
		}		
		
		,hideLoading: function()
		{
			this.hideMsg();
		}
		
		,displayMsg: function(str)		
		{									
			this.innerList.update('<div class="x-dlg-icon" style="padding:5px"><div class="ext-mb-icon ext-mb-error"></div>' + str + '</div>');
			this.restrictHeight();
			this.selectedIndex = -1;
			this.expand();
		}
		
		,hideMsg: function(){
			this.collapse();
		}
		
		,prepopulate: function(value, display)
		{
			this.prevSearchVal = value;
			var xml = IFDS.Xml.newDocument("data");
			var possibleMatchXML = IFDS.Xml.addSingleNode(IFDS.Xml.addSingleNode(xml, 'PossibleMatches'), 'PossibleMatch');
			
			IFDS.Xml.addSingleNode(possibleMatchXML, this.valueField, value);
			IFDS.Xml.addSingleNode(possibleMatchXML, this.displayField, display);			
			this.store.loadData(xml);
			this.setValue(value);				
		}		
	}	
);

IFDS.SuggestField.SearchFactory = function(config)
{
	var _suggestFld = config.suggestFld;
	var _searchURL = config.searchURL
	var _delay = config.delay;
	var _requestXMLGenerator = config.requestXMLGenerator
		
	return {
		createSearch: function(searchParamMap)		
		{					
			var searchXML = IFDS.Xml.newDocument('data');
			for (var i in searchParamMap)
			{
				IFDS.Xml.addSingleNode(searchXML, i, searchParamMap[i]);				
			}										
			return new IFDS.SuggestField.Search(_suggestFld, _searchURL, _requestXMLGenerator(searchXML), _delay);
		}
	}
}

IFDS.SuggestField.Search = function(suggestFld, searchURL, searchXML, delay)
{
	var _suggestFld = suggestFld;
	var _responseXML = null;
	var _timerId = null;	
	var _cancelled = false;
	
	function sendSearchRequest()
	{
		Ext.Ajax.request(
			{
				method: 'POST'
				,url: searchURL
				,timeout: 90000
				,success: successHandler
				,xmlData: searchXML								
			}	
		)
		_suggestFld.showLoading();
	}
	
	_timerId = sendSearchRequest.defer(delay, this);
	
	function successHandler(response)
	{
		if (!_cancelled)
		{
			_suggestFld.hideLoading();
			_responseXML = response.responseXML;			
			_suggestFld.searchCallback(_responseXML);	
		}
	}	
	
	return {
		getResponse: function()
		{
			return _responseXML;
		}
		
		,force: function()
		{
			clearTimeout(_timerId);
			sendSearchRequest();
		}
		
		,cancel: function()
		{			
			_cancelled = true;
			clearTimeout(_timerId);			
		}
	}
}