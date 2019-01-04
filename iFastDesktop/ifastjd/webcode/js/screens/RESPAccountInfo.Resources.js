/*********************************************************************************************
 * @file	RESPAccountInfo.Resources.js
 * @author	Narin Suanlamyai
 * @desc	Resources JS file for RESP Account Information screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  01 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54333
 *					- Fix display date format follows dateFormatDisplay parameter
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 490;
	var _layoutWidth = 800;
	
	// **** fields ****
	var _fields = {		
		planNo: new DesktopWeb.Controls.Label(
			{
				fieldLabel: _translationMap['planNo']
			}
		)
		,matureDt: new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['matureDt']
				,allowBlank: false
				,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				,listeners: {
					change: function(field, newVal, oldVal){
						if(_controller.getOriginalMatualDate() &&
							DesktopWeb.Util.stringToDate(_controller.getOriginalMatualDate()) < newVal)
						{
							DesktopWeb.Util.displayWarning(_translationMap['invalidMatureDate']);
						}
						_controller.activeUpdatesFlag();
					}
				}
			}
		)
		,grandFather: new DesktopWeb.Controls.Label(
			{
				fieldLabel: _translationMap['grandFather']
				,style: "text-transform:uppercase"
			}
		)
		,repHRDC: new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['repHRDC']
				,editable: false
				,width: 90
				,listeners: {
					change: function(val){
						_controller.activeUpdatesFlag();
					}
				}
			}
		)
		,pre98Contr: new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['pre98Contr']
				,editable: false
				,width: 90
				,listeners: {
					change: function(val){
						_controller.activeUpdatesFlag();
					}
				}
			}
		)
		,respStat: new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['respStat']
				,editable: false
				,width: 90
				,listeners: {
					change: function(val){
						_controller.activeUpdatesFlag();
					}
				}
			}
		)
		,incepDt: new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['incepDt']
				,allowBlank: false
				,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				,listeners: {
					change: function(val){
						_controller.activeUpdatesFlag();
					}
				}
			}
		)
		,siblingOnly: new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['siblingOnly']
				,editable: false
				,width: 90
				,listeners: {
					select: function(val){
						_controller.activeUpdatesFlag();
						_controller.doSiblingOnlyValidation();
					}
				}
			}
		)
		,repReqd: new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['repReqd']
				,editable: false
				,width: 90
				,listeners: {
					change: function(val){
						_controller.activeUpdatesFlag();
					}
				}
			}
		)
	}
	
	// **** grids ****
	var _grids = {
		benDetlGrid: new DesktopWeb.AdvancedControls.GridPanel(
			{							
				width: 787
				,title: ''
				,autoScroll: true
				,height: 150
				,autoExpandColumn: 'benName'
				,store: new Ext.data.XmlStore(
					{
						record: 'BeneficiaryDetails'
						,fields: ['benName', 'allocPrcnt', 'reltn', 'dtBirth', 'terminDt', 'repHRDC', 'taxjuris', 'tainted', 'taintendDt']
						,listeners: {
							load: function(store, records)
							{
								Ext.each(records, function(record){
									record.data.dtBirth = DesktopWeb.Util.getDateDisplayValue(record.data.dtBirth);
									record.data.terminDt = DesktopWeb.Util.getDateDisplayValue(record.data.terminDt);
									record.data.taintendDt = DesktopWeb.Util.getDateDisplayValue(record.data.taintendDt);									
								});
						
								store.fireEvent('datachanged', store); //to set data in grid again

								_grids['benDetlGrid'].getSelectionModel().lock();
							}
						}
					}
				)
				,selModel: new Ext.grid.RowSelectionModel(
					{
						
					}
				)
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
							,sortable: false
						}
						,columns: [
							{id: 'benName', header: _translationMap['benName'], dataIndex: 'benName'}
							,{header: _translationMap['allocation'], dataIndex: 'allocPrcnt', width: 75}
							,{header: _translationMap['relationship'], dataIndex: 'reltn', width: 80}
							,{header: _translationMap['dob'], dataIndex: 'dtBirth', width: 75}
							,{header: _translationMap['termDateContrib'], dataIndex: 'terminDt', width: 100}
							,{header: _translationMap['repHRDC2'], dataIndex: 'repHRDC', width: 65}
							,{header: _translationMap['taxJuris'], dataIndex: 'taxjuris', width: 85}
							,{header: _translationMap['tainted'], dataIndex: 'tainted', width: 50}
							,{header: _translationMap['taintedEndDate'], dataIndex: 'taintendDt', width: 80}
						]							
					}
				)
				,buttons: [
				]
			}
		)
		,regInfoGrid: new DesktopWeb.AdvancedControls.GridPanel(
			{							
				width: 621
				,title: ''
				,autoScroll: true
				,height: 75
				,autoExpandColumn: 'rejReason'
				,store: new Ext.data.XmlStore(
					{
						record: 'RegistrationStatusDetail'
						,fields: ['regStat', 'rejReason', 'procDate']
						,listeners: {
							load: function(store, records)
							{
								Ext.each(records, function(record){									
									record.data.procDate = DesktopWeb.Util.getDateDisplayValue(record.data.procDate);									
								});
						
								store.fireEvent('datachanged', store); //to set data in grid again
								_grids['regInfoGrid'].getSelectionModel().lock();
							}
						}
					}
				)
				,selModel: new Ext.grid.RowSelectionModel(
					{
						
					}
				)
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true							
							,sortable: false
						}
						,columns: [
							{header: _translationMap['regStat'], dataIndex: 'regStat', width: 150}
							,{id: 'rejReason', header: _translationMap['rejReason'], dataIndex: 'rejReason'}
							,{header: _translationMap['procDate'], dataIndex: 'procDate', width: 150}
						]							
					}
				)
				,buttons: [
				]
			}
		)
	}
	
	// **** popups ****
	var _popups = {					
		history: new DesktopWeb.AdvancedControls.HistoryPopup()
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
						xtype:'fieldset'
						,title: _translationMap['titleAcctInfo']
						,layout: 'column'
						,style: 'margin-bottom:20px;padding-left:15px;padding-right:15px;text-align:right'
						,width: _layoutWidth
						,items: [{
								// Column#1
								layout: 'form'
								,columnWidth: 0.35
								,autoHeight:true
								,labelWidth: 150
								,items :[
									_fields['planNo']
									,_fields['matureDt']
									,_fields['grandFather']
									,_fields['repHRDC']
									,_fields['pre98Contr']
								]
							}
							,{
								// Column#2 - Empty column
								layout: 'form'
								,columnWidth: 0.2
								,autoHeight:true
								,items :[
								]
							}
							,{
								// Column#3
								layout: 'form'
								,columnWidth: 0.35
								,autoHeight:true
								,labelWidth: 150
								,items :[
									_fields['respStat']
									,_fields['incepDt']
									,_fields['siblingOnly']
									,_fields['repReqd']
								]
							}
						]
					}
					,{
						xtype: 'fieldset'
						,title: _translationMap['titleBenInfo']
						,style: "margin-bottom:20px"
						,width: _layoutWidth
						,items: _grids['benDetlGrid']
					}
					,{
						xtype: 'fieldset'
						,title: _translationMap['titleRegStat']
						,style: "margin-bottom:20px"
						,width: 633
						,items: _grids['regInfoGrid']
					}
				]																				
			}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['Historical']
					,handler: function(){_controller.openHistoryPopup(DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);}
				}
			)
			,new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['OK']
					,handler: function(){
						if(_controller.screenModified()){
							_controller.doQuestionPrompt();
						}
						else
						{							
							DesktopWeb.Util.commitScreen();
						}
					}
				}
			)
			,new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['Cancel']
					,handler: function(){
						if(_controller.updatesFlag){
							DesktopWeb.Util.displayDiscardPrompt(cancelScreen);
						}else{
							cancelScreen(true);
						}
						function cancelScreen(discard){
							if(discard){
								DesktopWeb.Util.cancelScreen();
							}
						}
					}
				}
			)
		]			
	}
}