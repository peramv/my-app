/*********************************************************************************************
 * @file 	DesktopWeb.Controls.js
 * @author  Rod Walker 
 * @desc	Contains DesktopWeb specific controls, extended from ExtJS widgets, 
 * 			for reuse in screens
 *********************************************************************************************/
/*
 * History : 
 *
 *  16 Jun 2015 Narin Suanlamyai P0241773 T81011
 *                    - Add TreeGrid object
 *
 *  23 Sep 2016 Narin Suanlamyai P0256381 T83741 CHG0045765 Fund Broker Linkage for Germany
 *                    - Add showButton/hideButton for GridPanel
 *
 *  14 Jun 2017 Gomoot T. P0263240 CHG0048754 T85926
 *          - Add enableAllButtons to GridPanel
 */

Ext.namespace("DesktopWeb.AdvancedControls");

/*********************************************************************************************
 * TreeGrid extended from Ext.ux.tree.TreeGrid
 *********************************************************************************************/
DesktopWeb.AdvancedControls.TreeGrid = Ext.extend(Ext.ux.tree.TreeGrid, {
    enableSort: false,
    enableHdMenu: false,
	autoScroll: true,
    bodyCssClass: 'x-tree-noicon DesktopWeb-TreeGrid-Body',
    renderTo: Ext.getBody()
});


/*********************************************************************************************
 * GridPanel extended from Ext.grid.GridPanel 
 *********************************************************************************************/
DesktopWeb.AdvancedControls.GridPanel = Ext.extend( Ext.grid.GridPanel, {
	bodyCssClass: 'DesktopWeb-Grid-Body'
	
	,viewConfig: {
		selectedRowClass: 'DesktopWeb-Grid-Selected-Row'
	}
	
	,disableButton: function(btn)
	{
		this.getFooterToolbar().get(btn).disable();
	}
	
	,enableButton: function(btn)
	{
		this.getFooterToolbar().get(btn).enable();
	}
	
	,showButton: function(btn)
	{
		this.getFooterToolbar().get(btn).show();
	}
	
	,hideButton: function(btn)
	{
		this.getFooterToolbar().get(btn).hide();
	}
	
	,disableAllButtons: function()
	{
		if (this.buttons)
		{
			for (var i = 0; i < this.buttons.length; i++)
			{
				this.buttons[i].disable();
			}
		}
	}
  ,enableAllButtons: function()
	{
		if (this.buttons)
		{
			for (var i = 0; i < this.buttons.length; i++)
			{
				this.buttons[i].enable();
			}
		}
	}
	
	
	,showColumn: function(index)
	{
		this.getColumnModel().setHidden(index, false);
	}
	
	,hideColumn: function(index)
	{
		this.getColumnModel().setHidden(index, true);
	}
	
	,focusRow: function(index)
	{
		this.getView().focusRow(index);
	}
	
	,setSelectedRecord: function(index)
	{
		this.getSelectionModel().selectRow(index);	
		this.focusRow(index);	
	}
	
	,selectFirstRecord: function()
	{
		this.getSelectionModel().selectFirstRow();
		this.focusRow(0);					
	}
	
	,selectLastRecord: function()
	{		
		this.getSelectionModel().selectLastRow();
		this.focusRow(this.getStore().getCount() - 1);					
	}
	
	,getSelectedRecord: function()
	{	
		return this.getSelectionModel().getSelected();					
	}
	
	,getRecordIndex: function(record)
	{
		return this.getStore().indexOf(record);
	}
	
	,clearSelectedRecord: function()
	{
		this.getSelectionModel().clearSelections();				
	}	
	
	,addRecord: function(data)
	{
		var store = this.getStore();
		var recConstructor = store.recordType;
		var rec = new recConstructor(data)
		store.add([rec]);
		return rec;
	}
	
	,updateSelectedRecord: function(data)
	{
		var rec = this.getSelectedRecord();
		for (var i in data)
		{
			rec.data[i] = data[i];
		}		
		rec.commit();
	}
	
	,removeSelectedRecord: function()
	{
		var rec = this.getSelectedRecord();
		this.getSelectionModel().clearSelections();		
		this.getStore().remove(rec);		
	}
	
	,loadData: function(xml, buttonsToEnable)
	{		
		this.getStore().loadData(xml);
		if (this.rendered)
		{
			this.selectFirstRecord();
		}
		
		if (buttonsToEnable != null)
		{		
			for (var i = 0; i < buttonsToEnable.length; i++)
			{
				this.enableButton(buttonsToEnable[i]);	
			}
		}
	}
	
	,appendData: function(xml)
	{
		this.getStore().loadData(xml, true);		
		this.selectFirstRecord();
	}
	
	,clearData: function()
	{
		if(this.getSelectionModel() != null)
		{
			this.getSelectionModel().clearSelections();	
		}
		this.getStore().removeAll();
		this.disableAllButtons();		
	}
	
	,initComponent: function()
	{		
		DesktopWeb.AdvancedControls.GridPanel.superclass.initComponent.apply(this, arguments);
	}
	
	,onRender: function(ct, position)
	{
		DesktopWeb.AdvancedControls.GridPanel.superclass.onRender.call(this, ct, position);
	}		
	
	,setColumnHeaderText: function(index,newHeaderText)
	{
		this.getColumnModel().setColumnHeader(index, newHeaderText);
	}	
	
	,hideColumn: function(index)
	{
		this.getColumnModel().setHidden(index, true);
	}
	
	,showColumn: function(index)
	{
		this.getColumnModel().setHidden(index, false);
	}
	
	,getAllRecords: function()
	{
		var store = this.getStore();
		var records = [];
		var results = store.query(store.fields[0], /.*/)
		for (var i = 0; i < results.getCount(); i++)
		{
			records.push(results.itemAt(i));
		}               
		return records;         
    }
			
	,disable: function()
	{
		this.clearSelectedRecord();
		this.getSelectionModel().lock();
		this.disableAllButtons();
		DesktopWeb.AdvancedControls.GridPanel.superclass.disable.call(this);
	}
	
	,enable: function()
	{	
		this.getSelectionModel().unlock();		
		DesktopWeb.AdvancedControls.GridPanel.superclass.enable.call(this);
	}
});


/*********************************************************************************************
 * PopupWindow extended from Ext.Window, used for form popups within DesktopWeb screen 
 *********************************************************************************************/
DesktopWeb.AdvancedControls.PopupWindow = Ext.extend( Ext.Window, {
	resizable: false
	
	,closeAction: 'hide'
	
	,disableButton: function(btn)
	{
		this.getFooterToolbar().get(btn).disable();
	}
	
	,enableButton: function(btn)
	{
		this.getFooterToolbar().get(btn).enable();
	}
	
	,getField: function(fldId)
	{
		return this.find('itemId', fldId)[0];
	}
	
	,disableAllFields: function()
	{
		function fn(cmp)
		{
			return (cmp.itemId != null && cmp.itemId.length != 0);
		}
		var fields = this.findBy(fn);
		for (var i = 0; i < fields.length; i++)
		{
			if (fields[i].disableField)
			{			
				fields[i].disableField();
			}			
		}		
	}
	
	,disablePopupFields: function()
	{
		function fn(cmp)
		{
			return (cmp.itemId != null && cmp.itemId.length != 0);
		}
		var fields = this.findBy(fn);
		for (var i = 0; i < fields.length; i++)
		{						
			if (fields[i].disable && !(fields[i] instanceof DesktopWeb.Controls.Label))
			{			
				fields[i].disable();
			}			
		}		
	}
	
	,isValid: function()
	{
		var valid = true;
		function fn(cmp)
		{
			return (cmp.itemId != null && cmp.itemId.length != 0);
		}
		var fields = this.findBy(fn);
		for (var i = 0; i < fields.length; i++)
		{
			valid = (fields[i].isValid ? fields[i].isValid() : true) && valid;
		}
		
		return valid;		
	}
	
	,enableAllFields: function()
	{
		function fn(cmp)
		{
			return (cmp.itemId != null && cmp.itemId.length != 0);
		}
		var fields = this.findBy(fn);		
		for (var i = 0; i < fields.length; i++)
		{			
			if (fields[i].enableField && fields[i].clearInvalid)
			{			
				fields[i].enableField();
				fields[i].clearInvalid();
			}
		}		
	}
	
	,enablePopupFields: function()
	{
		function fn(cmp)
		{
			return (cmp.itemId != null && cmp.itemId.length != 0);
		}
		var fields = this.findBy(fn);		
		for (var i = 0; i < fields.length; i++)
		{			
			if (fields[i].enable)
			{			
				fields[i].enable();
			}
			if (fields[i].clearInvalid)
			{
				fields[i].clearInvalid();
			}
		}		
	}		
	
	,clearAllFields: function()
	{
		function fn(cmp)
		{
			return (cmp.itemId != null && cmp.itemId.length != 0);
		}
		var fields = this.findBy(fn);
		for (var i = 0; i < fields.length; i++)
		{
			if (fields[i].rendered)
			{
				if (fields[i].clearField)
				{
					fields[i].clearField();
				}
				else
				{
					fields[i].reset();
				}
				
				if (fields[i].enableField)
				{			
					fields[i].enableField();					
				}
				
				if (fields[i].clearInvalid)
				{
					fields[i].clearInvalid();					
				}
			}
		}
	}
	
	,clearPopupFields: function()
	{		
		function fn(cmp)
		{
			return (cmp.itemId != null && cmp.itemId.length != 0);
		}
		var fields = this.findBy(fn);
		for (var i = 0; i < fields.length; i++)
		{			
			if (fields[i].rendered)
			{				
				if (fields[i].reset)
				{														
					fields[i].reset();														
				}												
			}
		}
	}	
	
	,initComponent: function()
	{		
		DesktopWeb.AdvancedControls.PopupWindow.superclass.initComponent.apply(this, arguments);
	}
	
	,onRender: function(ct, position)
	{
		DesktopWeb.AdvancedControls.PopupWindow.superclass.onRender.call(this, ct, position);
	}		
});


/*********************************************************************************************
 * HistoryPopup extended from DesktopWeb.AdvancedControls.PopupWindow, used for 
 * building history popups used frequently in desktop web screens 
 *********************************************************************************************/
DesktopWeb.AdvancedControls.HistoryPopup = Ext.extend( DesktopWeb.AdvancedControls.PopupWindow, {					
	width: 580
		
	,historyView: null
	
	,viewParam: null
	
	,nextStartRecNum: null
		
	,closeAction: 'hide'
							
	,defaults: {border:false}
	
	,modal: true
	
	,useDisplayDate : false
	
	,buttons:[
		new DesktopWeb.Controls.ActionButton({
			text: DesktopWeb.Translation.getTranslation('More')
			,itemId: 'moreBtn'							
			,handler: function(btn)
			{
				var windowRef = btn.ownerCt.ownerCt;					
				windowRef.doHistoryCall(windowRef.nextStartRecNum, successHandler)					
				function successHandler(xml)
				{								
					windowRef.populate(xml, true);
				}								
			}							
		})
		
		,new DesktopWeb.Controls.ActionButton({
			text: DesktopWeb.Translation.getTranslation('Close')
			,handler: function(btn)
			{
				var windowRef = btn.ownerCt.ownerCt;
				windowRef.hide();
			}
		})					
	]	
	
	,init: function(dataLabel, viewName, viewParam, useDisplayDate)
	{
		this.setTitle(dataLabel);
		this.historyView = viewName;
		this.viewParam = viewParam;
		this.useDisplayDate = (useDisplayDate == true);
		
		this.doHistoryCall(1, successHandler);
		var self = this;		
				
		function successHandler(xml)
		{								
			self.populate(xml, false);
		}
	}
	
	,doHistoryCall: function(startRecNum, successCallback)
	{
		var requestXML = IFDS.Xml.newDocument("data");
		IFDS.Xml.addSingleNode(requestXML, 'startRecNum', startRecNum);
		IFDS.Xml.addSingleNode(requestXML, 'requestRecNum', 25);
		for (var i in this.viewParam)
		{
			IFDS.Xml.addSingleNode(requestXML, i, this.viewParam[i]);
		}
		DesktopWeb.Ajax.doSmartviewAjax(this.historyView, {ignoreErrorCode: '15'}, requestXML, responseHandler);
		
		function responseHandler(success, responseXML)
		{
			if (success)
			{
				successCallback(responseXML);							
			}							
		}				
	}
	
	,populate: function(xml, append)
	{						
		this.get(0).getStore().loadData(xml, append);
		var nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(xml);		
		if (nextStartRecNum)
		{
			this.nextStartRecNum = nextStartRecNum;
			this.enableButton('moreBtn');
		}
		else
		{
			this.disableButton('moreBtn');
		}
	}
	
	,initComponent: function()
	{	
		DesktopWeb.AdvancedControls.HistoryPopup.superclass.initComponent.apply(this, arguments);
	}
	
	,onRender: function(ct, position)
	{
		var convertDate = this.useDisplayDate;		
		var grid = new DesktopWeb.AdvancedControls.GridPanel({																					
			autoScroll: true										
			,height: 125
			,disableSelection: true
			,trackMouseOver: false							
			,store: new Ext.data.XmlStore({
				record: 'HistoricalInfo'					
				,fields: ['fldLbl', 'prevDisp', 'newDisp', 'modUsr', 'modDt', 'modTime']									
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [
					{header: DesktopWeb.Translation.getTranslation('Field'), dataIndex: 'fldLbl', width:100}
					,{header: DesktopWeb.Translation.getTranslation('PreviousValue'), dataIndex: 'prevDisp', width:100}
					,{header: DesktopWeb.Translation.getTranslation('NewValue'), dataIndex: 'newDisp', width:100}																				
					,{header: DesktopWeb.Translation.getTranslation('User'), dataIndex: 'modUsr', width:80}
					,{header: DesktopWeb.Translation.getTranslation('Date'), dataIndex: 'modDt', width:80
						,renderer: function(val, metaData, record){
							return convertDate == true ? DesktopWeb.Util.getDateDisplayValue(val) : val;
						}
					}
					,{header: DesktopWeb.Translation.getTranslation('Time'), dataIndex: 'modTime', width:80}
				]		
			})
		});
		
		this.add(grid);
		
		this.addListener('beforehide', function(){this.get(0).getStore().removeAll();}, this); 
		DesktopWeb.AdvancedControls.HistoryPopup.superclass.onRender.call(this, ct, position);			
	}	
});


/*********************************************************************************************
 * 
 *********************************************************************************************/
DesktopWeb.AdvancedControls.ItemSelector = Ext.extend(Ext.Container, {
	allowReordering: false
	
	,initComponent: function()
	{
		this.availableGrid = new DesktopWeb.AdvancedControls.GridPanel(Ext.apply(this.availableGridProperties,
			{ 
				title: DesktopWeb.Translation.getTranslation('Available')
				,height: this.initialConfig.height
				,enableHdMenu: false
				,enableColumnMove: false						
			}				
		));		
		this.availableGrid.getSelectionModel().addListener('selectionchange',
			function(selectionModel){
				if (selectionModel.getCount() > 0)
				{
					this.addBtn.enable();
				}
				else
				{
					this.addBtn.disable();
				}
			},
			this
		);
		
		this.selectedGrid = new DesktopWeb.AdvancedControls.GridPanel(Ext.apply(this.selectedGridProperties,
			{ 
				title: DesktopWeb.Translation.getTranslation('Selected')
				,height: this.initialConfig.height
				,enableHdMenu: false
				,enableColumnMove: false								
			}				
		));
		this.selectedGrid.getSelectionModel().addListener('selectionchange',
			function(selectionModel){
				if (selectionModel.getCount() > 0)
				{
					this.removeBtn.enable();					
					if (this.allowReordering)
					{
						var store = this.selectedGrid.getStore();
						var selections = selectionModel.getSelections();
						selections.sort(function(item1, item2){return store.indexOf(item1) - store.indexOf(item2)})
						var firstRec = selections[0]
						if (store.indexOf(firstRec) > 0)
						{						
							this.moveUpBtn.enable();
						}
						else
						{
							this.moveUpBtn.disable();
						}
						var lastRec = selections[selectionModel.getCount() - 1]
						if (store.indexOf(lastRec) < store.getCount() - 1)
						{						
							this.moveDownBtn.enable();
						}
						else
						{
							this.moveDownBtn.disable();
						}						
					}
				}
				else
				{
					this.removeBtn.disable();
					if (this.allowReordering)
					{
						this.moveUpBtn.disable();
						this.moveDownBtn.disable();
					}
				}
			},
			this);
		
		this.addBtn = new DesktopWeb.Controls.ActionButton({
			text: DesktopWeb.Translation.getTranslation('Add') + ' &raquo;'
			,disabled: true										
		});
		this.addBtn.addListener('click',
			function()
			{							
				this.addToSelected(this.availableGrid.getSelectionModel().getSelections());
			},
			this);
		
		this.removeBtn = new DesktopWeb.Controls.ActionButton({
			text: '&laquo; ' + DesktopWeb.Translation.getTranslation('Remove')
			,disabled: true			
		});
		this.removeBtn.addListener('click',
			function()
			{							
				this.removeFromSelected(this.selectedGrid.getSelectionModel().getSelections());
			},
			this);
						
		if (this.allowReordering)
		{
			this.moveUpBtn = new DesktopWeb.Controls.ActionButton({
				text: DesktopWeb.Translation.getTranslation('Up')
				,disabled: true			
			});
			this.moveUpBtn.addListener('click', 
				function()
				{
					this.moveUpSelected(this.selectedGrid.getSelectionModel().getSelections());	
				},
				this);
			this.selectedGrid.addButton(this.moveUpBtn);
						
			this.moveDownBtn = new DesktopWeb.Controls.ActionButton({
				text: DesktopWeb.Translation.getTranslation('Down')
				,disabled: true			
			});
			this.moveDownBtn.addListener('click', 
				function()
				{
					this.moveDownSelected(this.selectedGrid.getSelectionModel().getSelections());	
				},
				this);
			this.selectedGrid.addButton(this.moveDownBtn);		
		}		
		
		var config = {
			layout: 'column'
			,items: [
				this.availableGrid
				,new Ext.Container({
					width: this.initialConfig.width - this.availableGridProperties.width - this.selectedGridProperties.width
					,height: this.initialConfig.height
					,style: "padding-top:" + ((this.initialConfig.height - 50) / 2) + "px; text-align: center"
					,defaults: {
						width: 65
						,style: 'margin-bottom: 5px'						
					}
					,items: [
						this.addBtn
						,this.removeBtn
					]
				})
				,this.selectedGrid
			]
		}
		
		this.addEvents({
			'change' : true					
		});

		Ext.apply(this, Ext.apply(this.initialConfig, config));							
		DesktopWeb.AdvancedControls.ItemSelector.superclass.initComponent.apply(this, arguments);
	}
	
	,onRender: function(ct, position)
	{
		DesktopWeb.AdvancedControls.ItemSelector.superclass.onRender.call(this, ct, position);
				
		this.availableGrid.getStore().addListener('load', 
			function(store, records){
				for (var r = 0; r < records.length; r++)
				{
					records[r].selected = false;
				}	
			}
		);
	}
	
	,loadAvailableData: function(availableData)
	{
		this.availableGrid.getStore().loadData(availableData);
	}
	
	,setSelectedByData: function(fieldName, values)
	{
		var indexes = [];
		var availableGridStore = this.availableGrid.getStore();		
		for (var i = 0; i < values.length; i++)
		{
			indexes.push(availableGridStore.findExact(fieldName, values[i]));			
		}
				
		this.setSelectedByIndexes(indexes);					
	}
		
	,setSelectedByIndexes: function(selectedIndexes)
	{
		if (Ext.isArray(selectedIndexes))
		{
			var selectedRows = [];
			for (var i = 0; i < selectedIndexes.length; i++)
			{				
				selectedRows.push(this.availableGrid.getStore().getAt(selectedIndexes[i]));
			}		
			if (selectedRows.length > 0)
			{
				this.addToSelected(selectedRows);
			}
		}
		else
		{
			throw new Error("DesktopWeb.AdvancedControls.ItemSelector init() error - selectedIndexes is not an array");
		}		
	}
	
	,getSelectedRecords: function()
	{
		return this.selectedGrid.getAllRecords();
	}

	,addToSelected: function(recordsToAdd)
	{
		Ext.each(recordsToAdd, function(item){item.selected = true});			
		this.availableGrid.getStore().filterBy(function(record){return !record.selected;});		
		this.selectedGrid.getStore().add(recordsToAdd);
		this.fireEvent('change');		
	}
	
	,removeFromSelected: function(recordsToRemove)
	{
		Ext.each(recordsToRemove, function(item){item.selected = false});			
		this.availableGrid.getStore().filterBy(function(record){return !record.selected;});			
		this.selectedGrid.getStore().remove(recordsToRemove);
		this.fireEvent('change');
	}
	
	,removeAllFromSelected: function()
	{
		Ext.each(this.getSelectedRecords(), function(rec){this.removeFromSelected(rec)}, this);
	}
	
	,moveUpSelected: function(recordsToMove)
	{
		var store = this.selectedGrid.getStore();
		recordsToMove.sort(function(item1, item2){return store.indexOf(item1) - store.indexOf(item2)});
		var destIndex = store.indexOf(recordsToMove[0]) - 1;
		this.moveSelected(destIndex, recordsToMove);		
	}
	
	,moveDownSelected: function(recordsToMove)
	{
		var store = this.selectedGrid.getStore();
		recordsToMove.sort(function(item1, item2){return store.indexOf(item1) - store.indexOf(item2)});
		var destIndex = store.indexOf(recordsToMove[recordsToMove.length - 1]) + 1 - recordsToMove.length + 1;
		this.moveSelected(destIndex, recordsToMove);				
	}
	
	,moveSelected: function(destIndex, recordsToMove)
	{
		var store = this.selectedGrid.getStore();
		var selectionModel = this.selectedGrid.getSelectionModel();
		recordsToMove.sort(function(item1, item2){return store.indexOf(item2) - store.indexOf(item1)});
		store.remove(recordsToMove);		
		store.insert(destIndex, recordsToMove);
		selectionModel.selectRange(destIndex, destIndex + (recordsToMove.length - 1));
		this.fireEvent('change');
	}
	
	,disable: function(){		
		this.availableGrid.disable();		
		this.selectedGrid.disable();
	}
	
	,enable: function(){		
		this.availableGrid.enable();		
		this.selectedGrid.enable();
	}
});


/*********************************************************************************************
 * 
 *********************************************************************************************/
DesktopWeb.AdvancedControls.BreadCrumbList = Ext.extend(Ext.Container, {
	separator: '&raquo;'
	,style: 'padding-bottom:5px;'
	
	,initComponent: function()
	{
		this.breadCrumbItems = {};
		
		var config = {										
		}

		Ext.apply(this, Ext.apply(this.initialConfig, config));							
		DesktopWeb.AdvancedControls.BreadCrumbList.superclass.initComponent.apply(this, arguments);
		
		this.addEvents({
			'itemclicked' : true					
		});
	}
	
	,onRender: function(ct, position)
	{
		DesktopWeb.AdvancedControls.BreadCrumbList.superclass.onRender.call(this, ct, position);
		
		if (this.initialConfig.breadCrumbItems)
		{
			for( var i = 0; i < this.initialConfig.breadCrumbItems.length; i++)
			{
				this.addItem(this.initialConfig.breadCrumbItems[i].id, this.initialConfig.breadCrumbItems[i].label)
			}
		}		
	}
	
	,addItem: function(id, label)
	{			
		var self = this;
		this.breadCrumbItems[id] = new DesktopWeb.Controls.Label({
			cls: 'DesktopWeb-BreadCrumbItem'
			,html: this.separator + ' <span>' + label + "</label"
			,disabled: true
			,listeners: {
				render: function(c){
					c.getEl().addListener('click', function(){this.fireEvent('itemclicked', id)}, self); 
				}
			}			
		});		
		this.add(this.breadCrumbItems[id]);
		this.doLayout();		
	}
	
	,insertItem: function(id, label, index)
	{			
		var self = this;
		this.breadCrumbItems[id] = new DesktopWeb.Controls.Label({
			cls: 'DesktopWeb-BreadCrumbItem'
			,html: this.separator + ' <span>' + label + "</label"
			,disabled: true
			,listeners: {
				render: function(c){
					c.getEl().addListener('click', function(){this.fireEvent('itemclicked', id)}, self); 
				}
			}			
		});		
		this.insert(index, this.breadCrumbItems[id]);
		this.doLayout();		
	}
	
	,removeItem: function(id)
	{			
		this.remove(this.breadCrumbItems[id]);
		this.doLayout();		
	}
	
	,enableAll: function()
	{
		for (var i in this.breadCrumbItems)
		{
			this.enableItem(i);
		}
	}
	
	,disableAll: function()
	{
		for (var i in this.breadCrumbItems)
		{
			this.disableItem(i);
		}
	}
	
	,disableItem: function(id)
	{
		this.breadCrumbItems[id].removeClass("DesktopWeb-BreadCrumbItem-Enabled");
		this.breadCrumbItems[id].disable();		
	}
	
	,enableItem: function(id)
	{
		this.breadCrumbItems[id].addClass("DesktopWeb-BreadCrumbItem-Enabled");
		this.breadCrumbItems[id].enable();
	}
	
	,setActiveItem: function(id)
	{
		for (var i in this.breadCrumbItems)
		{
			this.breadCrumbItems[i].removeClass("DesktopWeb-BreadCrumbItem-Active");
		}
		this.breadCrumbItems[id].addClass("DesktopWeb-BreadCrumbItem-Active");
	}

	,getItemIndex: function(id)
	{
		var index = 0;
		for (var i in this.breadCrumbItems)
		{
			if(i == id)return index;
			index++;
		}
		return -1;
	}

});	

